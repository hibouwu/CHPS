"""Verify dispatched row identities, template rendering, token ids, raw final answers and scoring provenance."""
from pathlib import Path
from types import SimpleNamespace
import hashlib
import json
import sys
from jinja2.sandbox import ImmutableSandboxedEnvironment
from score_qwen_a100 import A, PRIOR, FROZEN, cfg, formal_inputs, name
from score_candidate import BASE, row_at, official, sha, save

runtime=Path('/data/jianyeshi/coderujb-reproduction/runtime')
sys.path.insert(0,str(runtime/'cl13-tokenizer-check/lib'))
from tokenizers import Tokenizer


def main():
    tok_dir=runtime/'qwen-tokenizer-check'
    tok=Tokenizer.from_file(str(tok_dir/'tokenizer.json'))
    template_text=json.loads((tok_dir/'tokenizer_config.json').read_text())['chat_template']
    engine=ImmutableSandboxedEnvironment(trim_blocks=True,lstrip_blocks=True)
    template=engine.from_string(template_text)
    ends=set(json.loads((tok_dir/'generation_config.json').read_text())['eos_token_id'])
    jobs=(A/'jobs.txt').read_text().splitlines()
    for job in jobs:
        for line in (A/f'remote-sha256-{job}.txt').read_text().splitlines():
            digest,file=line.split('  ',1)
            # The last receipt is the final remote snapshot; earlier allocations may have fewer rows.
            assert sha((A/file).read_bytes())==digest
        receipts=json.loads((A/f'weights-receipt-{job}.json').read_text())
        meta=json.loads((A/'weights.json').read_text())
        assert len(receipts)==len(meta['files'])
        for f,rec in zip(meta['files'],receipts,strict=True):
            assert rec['file']==f['rfilename'] and rec['size']==f['size']
            if f.get('lfs'):assert rec['sha256']==f['lfs']['sha256']
            if (tok_dir/f['rfilename']).exists():assert sha((tok_dir/f['rfilename']).read_bytes())==rec['sha256']
        runtime_meta=json.loads((A/f'runtime-{job}.json').read_text())
        assert runtime_meta['template_sha256']==sha(template_text.encode()) and runtime_meta['precision']=='torch.bfloat16'
    declared=set()
    for marker in (A/'groups').glob('b*.json'):
        g=json.loads(marker.read_text()); base=int(marker.stem[1:])*cfg['group_size']
        assert g['rows']==[name(r) for r in FROZEN[base:base+cfg['group_size']]]
        assert not declared.intersection(g['rows'])
        declared.update(g['rows'])
    checked=[]
    for r in FROZEN:
        k=name(r)
        if k not in declared:continue
        d=A/'rows'/k; row=row_at(r['task'],r['task_idx']); inp=formal_inputs[k]
        assert set(inp)=={'task','task_idx','revision','prompt_sha256','prompt'}
        assert inp['prompt']==row['prompt_chat'].strip() and sha(inp['prompt'].encode())==r['chat_sha256']
        messages=[{'role':'system','content':cfg['system']},{'role':'user','content':inp['prompt']}]
        rendered=template.render(messages=messages,tools=None,add_generation_prompt=True)
        assert rendered==(d/'template.txt').read_bytes().decode()
        ids=tok.encode(rendered,add_special_tokens=False).ids
        dispatch=json.loads((d/'dispatch.json').read_text())
        assert ids==dispatch['input_ids'] and dispatch['key']==k and dispatch['input_tokens']==len(ids)<=cfg['max_input_tokens']
        if not (d/'generation.json').is_file():continue
        gen=json.loads((d/'generation.json').read_text()); out=gen['output_ids']
        assert gen['output_tokens']==len(out) and not any(x in ends for x in out[:-1])
        assert (gen['finish_reason']=='eos')==(out[-1] in ends)
        assert gen['finish_reason']=='eos' or len(out)==cfg['max_new_tokens']
        raw=tok.decode(out,skip_special_tokens=True)
        assert raw==(d/'final.txt').read_bytes().decode() and sha(raw.encode())==gen['answer_sha256']
        score=json.loads((A/'scores'/(k+'.json')).read_text()); result=BASE/score['result']
        ns=official(r['task'])
        task=SimpleNamespace(dataset={'train':{r['task_idx']:row}},_stop_at_function=ns['_stop_at_function'])
        patch=ns['postprocess_chat_generation'](task,raw,r['task_idx'])
        assert patch==(result.parent/'candidate.txt').read_bytes().decode()
        assert json.loads((PRIOR/'preflight'/(k+'.json')).read_text())['eligible']
        checked.append(dict(key=k,group=dispatch['group'],prompt_sha256=r['chat_sha256'],answer_sha256=gen['answer_sha256'],
                            extracted_sha256=sha(patch.encode()),score_path=score['result']))
    save(A/'integrity.json',dict(planned=100,unique_dispatched=len(declared),outputs_verified=len(checked),
         typed_messages_per_row=['system','user'],paid_api_calls=0,protocol_sha256=sha((A/'protocol.json').read_bytes()),
         rows=checked,pilot_separate=True,template_and_token_ids_replayed=True,raw_outputs_and_official_extractions_replayed=True))
    print(len(declared),'dispatched;',len(checked),'verified')

if __name__=='__main__':
    main()
