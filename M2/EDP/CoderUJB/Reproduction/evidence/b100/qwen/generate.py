"""Run Qwen on a separate pilot and the fixed four-row batches allowed by the local gate."""
import hashlib
import json
import os
import shutil
import socket
import sys
import time
from datetime import datetime
from pathlib import Path

import torch
import transformers
from transformers import AutoModelForCausalLM, AutoTokenizer
from stage_weights import stage_snapshot

root=Path.cwd()
protocol=json.loads((root/'protocol.json').read_text())
weights=json.loads((root/'weights.json').read_text())
job=os.environ['SLURM_JOB_ID']
protocol_hash=hashlib.sha256((root/'protocol.json').read_bytes()).hexdigest()
assert protocol['revision']==weights['revision']
assert protocol['weights_manifest_sha256']==hashlib.sha256((root/'weights.json').read_bytes()).hexdigest()

def save(path,obj):
    tmp=path.with_suffix('.tmp')
    tmp.write_text(json.dumps(obj,indent=2,ensure_ascii=False)+'\n')
    tmp.replace(path)

def exclusive(path,obj):
    with path.open('x') as file:
        json.dump(obj,file,ensure_ascii=False,indent=2)
        file.flush()
        os.fsync(file.fileno())

def key(r):
    return f"{r['task']}-{r['task_idx']}-{r['revision']}"

start=time.monotonic()
tmp=Path(os.environ['CODERUJB_JOB_TMP'])
assert shutil.disk_usage(tmp).free > sum(f['size'] for f in weights['files']) + 2_000_000_000
receipts=stage_snapshot(weights,tmp/'weights')
save(root/f'weights-receipt-{job}.json',receipts)
tokenizer=AutoTokenizer.from_pretrained(tmp/'weights',local_files_only=True)
tokenizer.padding_side='left'
model=AutoModelForCausalLM.from_pretrained(tmp/'weights',torch_dtype=torch.bfloat16,local_files_only=True,
                 low_cpu_mem_usage=False,attn_implementation='sdpa').to('cuda').eval()
assert next(model.parameters()).dtype==torch.bfloat16
assert all(p.device.type=='cuda' and p.dtype==torch.bfloat16 for p in model.parameters())
meta=dict(job_id=job,node=socket.gethostname(),gpu=torch.cuda.get_device_name(0),torch=torch.__version__,
          transformers=transformers.__version__,cuda=torch.version.cuda,precision=str(next(model.parameters()).dtype),
          parameters=sum(p.numel() for p in model.parameters()),attention=model.config._attn_implementation,
          staging_load_seconds=time.monotonic()-start,generation_defaults=model.generation_config.to_dict(),
          template_sha256=hashlib.sha256(tokenizer.chat_template.encode()).hexdigest(),
          memory_allocated=torch.cuda.memory_allocated(),input_limit=protocol['max_input_tokens'])
save(root/f'runtime-{job}.json',meta)
print('model_loaded',meta['parameters'],meta['memory_allocated'],flush=True)

def run_group(rows,group,pilot=False):
    parent=root/('pilot' if pilot else 'rows');parent.mkdir(exist_ok=True)
    markers=root/'groups';markers.mkdir(exist_ok=True)
    marker=markers/(group+'.json')
    if marker.exists():return
    rendered=[]
    for r in rows:
        assert set(r)=={'task','task_idx','revision','prompt','prompt_sha256'}
        assert hashlib.sha256(r['prompt'].encode()).hexdigest()==r['prompt_sha256']
        messages=[{'role':'system','content':protocol['system']},{'role':'user','content':r['prompt']}]
        text=tokenizer.apply_chat_template(messages,add_generation_prompt=True,tokenize=False)
        assert text=='<|im_start|>system\n'+protocol['system']+'<|im_end|>\n<|im_start|>user\n'+r['prompt']+'<|im_end|>\n<|im_start|>assistant\n'
        rendered.append(text)
    enc=tokenizer(rendered,padding=True,add_special_tokens=False,return_tensors='pt')
    lengths=enc.attention_mask.sum(dim=1).tolist()
    assert max(lengths)<=protocol['max_input_tokens']
    exclusive(marker,dict(rows=list(map(key,rows)),seed=protocol['seed'],job=job,protocol_sha256=protocol_hash))
    for pos,r in enumerate(rows):
        d=parent/key(r);d.mkdir(exist_ok=False)
        (d/'template.txt').write_text(rendered[pos])
        exclusive(d/'dispatch.json',dict(job=job,key=key(r),group=group,position=pos,protocol_sha256=protocol_hash,
                 prompt_sha256=r['prompt_sha256'],input_tokens=lengths[pos],input_ids=enc.input_ids[pos,-lengths[pos]:].tolist(),
                 left_padding=enc.input_ids.shape[1]-lengths[pos],seed=protocol['seed']))
    torch.manual_seed(protocol['seed'])
    began=time.monotonic()
    try:
        with torch.inference_mode():
            outputs=model.generate(**enc.to('cuda'),max_new_tokens=protocol['max_new_tokens'],do_sample=True,
                                   temperature=protocol['temperature'],top_k=protocol['top_k'],top_p=protocol['top_p'],
                                   repetition_penalty=protocol['repetition_penalty'],num_return_sequences=1,
                                   pad_token_id=tokenizer.pad_token_id)
        torch.cuda.synchronize()
        elapsed=time.monotonic()-began
        ends=model.generation_config.eos_token_id
        ends={ends} if isinstance(ends,int) else set(ends)
        for pos,r in enumerate(rows):
            d=parent/key(r)
            ids=outputs[pos,enc.input_ids.shape[1]:].tolist()
            stop=next((i for i,n in enumerate(ids) if n in ends),None)
            reason='length' if stop is None else 'eos'
            ids=ids if stop is None else ids[:stop+1]
            if reason=='length':assert len(ids)==protocol['max_new_tokens']
            final=tokenizer.decode(ids,skip_special_tokens=True,clean_up_tokenization_spaces=False)
            (d/'final.txt').write_text(final)
            save(d/'generation.json',dict(output_ids=ids,output_tokens=len(ids),finish_reason=reason,
                    answer_sha256=hashlib.sha256(final.encode()).hexdigest(),batch_elapsed_seconds=elapsed))
            print(group,key(r),len(ids),reason,flush=True)
    except RuntimeError as error:
        for r in rows:save(parent/key(r)/'unresolved.json',dict(error=repr(error),group=group))
        raise

rows=json.loads((root/'inputs.json').read_text())
assert len(rows)==len({key(r) for r in rows})==100
job_end=int(os.environ.get('SLURM_JOB_END_TIME',str(int(time.time()+3500))))
absolute_end=datetime.fromisoformat(protocol['b_generation_cutoff']).timestamp()
for i in range(0,len(rows),protocol['group_size']):
    if time.time()+420>=min(job_end,absolute_end):
        print('admission cutoff',i,flush=True);break
    run_group(rows[i:i+protocol['group_size']],f'b{i//protocol["group_size"]:02d}')
meta.update(total_seconds=time.monotonic()-start,peak_cuda_allocated_bytes=torch.cuda.max_memory_allocated(),
            peak_cuda_reserved_bytes=torch.cuda.max_memory_reserved())
save(root/f'runtime-{job}.json',meta)
