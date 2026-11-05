"""Replay actual token ids locally, verify official extraction and 100 paired row receipts."""
import json
from types import SimpleNamespace
from pathlib import Path
import sys
from score_cl13_a100 import A, PRIOR, FROZEN, inputs, protocol, name, review_compile_diagnostic, caller_compile_error
from score_candidate import official, row_at, sha, save

tokenizer_dir=Path('/data/jianyeshi/coderujb-reproduction/runtime/cl13-tokenizer-check')
sys.path.insert(0,str(tokenizer_dir/'lib'))
from tokenizers import Tokenizer
import tokenizers

def main():
    tok=Tokenizer.from_file(str(tokenizer_dir/'tokenizer.json'))
    meta=json.loads((A/'weights.json').read_text())
    receipts=json.loads((A/'weights-receipt.json').read_text())
    assert sha((tokenizer_dir/'tokenizer.json').read_bytes())==next(x['sha256'] for x in receipts if x['file']=='tokenizer.json')
    assert {f['rfilename'] for f in meta['files']}=={f['file'] for f in receipts}
    for f in meta['files']:
        if f.get('lfs'):assert f['lfs']['sha256']==next(x['sha256'] for x in receipts if x['file']==f['rfilename'])
    for line in (A/'remote-sha256.txt').read_text().splitlines():
        digest,path=line.split('  ',1)
        assert sha((A/path).read_bytes())==digest
    prior_review=[]
    records=[]
    for r in FROZEN:
        k=name(r);inp=inputs[k];d=A/'rows'/k
        row=row_at(r['task'],r['task_idx'])
        assert inp['prompt']==row['prompt_complete'].strip() and sha(inp['prompt'].encode())==r['complete_sha256']
        sent=json.loads((d/'dispatch.json').read_text())
        encoded=tok.encode(inp['prompt']).ids
        assert sent['input_ids']==encoded[-protocol['input_tokens']:] and sent['input_tokens_full']==len(encoded)
        g=json.loads((d/'generation.json').read_text())
        raw=(d/'full-decoded.txt').read_bytes().decode()
        decoded=tok.decode(sent['input_ids']+g['output_ids'],skip_special_tokens=True)
        assert decoded==raw,(k,'full text decode mismatch')
        assert tok.decode(g['output_ids'],skip_special_tokens=True)==(d/'continuation.txt').read_bytes().decode()
        assert sha(raw.encode())==g['raw_sha256']
        if g['finish_reason']=='length':assert len(g['output_ids'])==protocol['max_new_tokens']
        if g['finish_reason']=='eos':assert g['output_ids'][-1]==tok.token_to_id('</s>')
        score=json.loads((A/'scores'/(k+'.json')).read_text())
        result=A.parents[1]/score['result']
        rec=json.loads(result.read_text())
        ns=official(r['task'])
        task=SimpleNamespace(dataset={'train':{r['task_idx']:row}},_stop_at_function=ns['_stop_at_function'])
        extracted=ns['postprocess_complete_generation'](task,raw,r['task_idx'])
        assert (result.parent/'candidate.txt').read_bytes().decode()==extracted and rec['mode']=='complete'
        previous=json.loads((PRIOR/'scores'/(k+'.json')).read_text())
        previous_result=A.parents[1]/previous['result']
        prior_raw=json.loads(previous_result.read_text())
        if prior_raw['status']=='infrastructure_unresolved':
            diagnosed=caller_compile_error(r['task'],r['task_idx'],previous_result) or review_compile_diagnostic(r,previous_result)
            assert diagnosed and previous['status']=='fail'
            prior_review.append(dict(key=k,status='fail',evidence=diagnosed))
        baseline=json.loads((PRIOR/'preflight'/(k+'.json')).read_text())
        assert baseline['eligible'] and baseline.get('log')==score['reference_log']
        records.append(dict(key=k,input_tokens_used=len(sent['input_ids']),input_truncated=sent['input_truncated'],
                            output_tokens=g['output_tokens'],finish_reason=g['finish_reason'],
                            actual_decoded_input_matches_full_prompt=tok.decode(sent['input_ids'])==inp['prompt'],
                            official_extra_prefix_characters=raw[len(inp['prompt']):len(row['prompt_complete'])] if r['task']=='APR' else None,
                            candidate_sha256=sha(extracted.encode()),status=score['status']))
    assert len(records)==len({r['key'] for r in records})==100
    save(A/'integrity.json',dict(verified_unique_rows=len(records),role='generation sees only official completion prompts',
        tokenizer_version=tokenizers.__version__,protocol_hash=sha((A/'protocol.json').read_bytes()),
        input_ids_retokenized=True,full_raw_outputs_redecoded=True,all_official_extractions_verified=True,
        reused_reference_evidence=True,previous_diagnostic_reviews=prior_review,code_review_rows=records))
    print('100 rows, inputs, raw outputs and official extractions verified')

if __name__=='__main__':
    main()
