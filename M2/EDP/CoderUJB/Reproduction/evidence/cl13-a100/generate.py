"""One CodeLlama completion per frozen row. Job receives only input prompts and model metadata."""
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
import hashlib
import json
import os
import socket
import time
import urllib.request
import torch
import transformers
from transformers import AutoModelForCausalLM, AutoTokenizer

root=Path.cwd()
cfg=json.loads((root/'protocol.json').read_text())
weights=json.loads((root/'weights.json').read_text())
assert cfg['revision']==weights['revision']
weight_dir=Path(os.environ['CODERUJB_JOB_TMP'])/'model'
weight_dir.mkdir()
def digest(data):
    return hashlib.sha256(data).hexdigest()
def save(path,value):
    tmp=path.with_suffix('.tmp')
    tmp.write_text(json.dumps(value,indent=2,ensure_ascii=False)+'\n')
    tmp.replace(path)

def stage_file(item):
    name=item['rfilename']
    n=item['size']; path=weight_dir/name
    url=f"https://huggingface.co/{weights['repo']}/resolve/{weights['revision']}/{name}"
    with path.open('wb') as f:
        fd=f.fileno()
        os.ftruncate(fd,n)
        def part(a):
            b=min(a+128*1024**2,n)-1
            for attempt in range(2):
                try:
                    req=urllib.request.Request(url+f'?range={a}-{b}',headers={'Range':f'bytes={a}-{b}','Accept-Encoding':'identity'})
                    with urllib.request.urlopen(req,timeout=60) as res:
                        if res.status==206:
                            assert res.headers['Content-Range']==f'bytes {a}-{b}/{n}'
                        else: assert res.status==200 and a==0 and b+1==n
                        off=a
                        while off<=b:
                            chunk=res.read(min(2**20,b-off+1))
                            if not chunk:raise OSError('short weight range')
                            assert os.pwrite(fd,chunk,off)==len(chunk)
                            off+=len(chunk)
                    return
                except (OSError,AssertionError):
                    if attempt:raise
        with ThreadPoolExecutor(max_workers=4) as ex:list(ex.map(part,range(0,n,128*1024**2)))
    h=hashlib.sha256()
    with path.open('rb') as f:
        for chunk in iter(lambda:f.read(8*1024**2),b''):
            h.update(chunk)
    if item.get('lfs'):
        assert h.hexdigest()==item['lfs']['sha256']
    else:
        assert hashlib.sha1(f'blob {n}\0'.encode()+path.read_bytes()).hexdigest()==item['blobId']
    return dict(file=name,size=n,sha256=h.hexdigest())

start=time.monotonic()
with ThreadPoolExecutor(max_workers=3) as ex: receipts=list(ex.map(stage_file,weights['files']))
save(root/'weights-receipt.json',receipts)
tokenizer=AutoTokenizer.from_pretrained(weight_dir,local_files_only=True)
model=AutoModelForCausalLM.from_pretrained(weight_dir,torch_dtype=torch.bfloat16,local_files_only=True,
                                            low_cpu_mem_usage=False,attn_implementation='eager').to('cuda').eval()
torch.cuda.synchronize()
metadata=dict(job_id=os.environ['SLURM_JOB_ID'],node=socket.gethostname(),gpu=torch.cuda.get_device_name(0),
              torch=torch.__version__,transformers=transformers.__version__,cuda=torch.version.cuda,
              dtype=str(next(model.parameters()).dtype),parameters=sum(p.numel() for p in model.parameters()),
              generation_defaults=model.generation_config.to_dict(),staging_load_seconds=time.monotonic()-start)
save(root/'runtime.json',metadata)
rows=json.loads((root/'inputs.json').read_text())
assert len(rows)==len({(r['task'],r['revision'],r['task_idx']) for r in rows})==100
for row in rows:
    assert set(row)=={'task','task_idx','revision','prompt','prompt_sha256'}
    assert digest(row['prompt'].encode())==row['prompt_sha256']
    key=f"{row['task']}-{row['task_idx']}-{row['revision']}"
    out=root/'rows'/key
    out.mkdir(exist_ok=True,parents=True)
    if (out/'dispatch.json').exists():continue
    enc=tokenizer([row['prompt']],return_tensors='pt')
    ids=enc.input_ids[:,-cfg['input_tokens']:].to('cuda')
    mask=enc.attention_mask[:,-cfg['input_tokens']:].to('cuda')
    full_length=enc.input_ids.shape[-1]; used=ids.shape[-1]
    fs=out/'dispatch.json'
    with fs.open('x') as f:
        json.dump(dict(key=key,job=metadata['job_id'],protocol_sha256=digest((root/'protocol.json').read_bytes()),
                       seed=row['task_idx'],input_sha256=row['prompt_sha256'],input_tokens_full=full_length,
                       input_tokens_used=used,input_truncated=full_length>used,input_ids=ids[0].tolist()),f)
        f.flush()
        os.fsync(f.fileno())
    began=time.monotonic()
    try:
        torch.manual_seed(row['task_idx'])
        with torch.inference_mode():
            output=model.generate(input_ids=ids,attention_mask=mask,temperature=cfg['temperature'],
                                  do_sample=True,num_return_sequences=1,max_new_tokens=cfg['max_new_tokens'])
        torch.cuda.synchronize()
        generated=output[0,used:].tolist()
        raw=tokenizer.batch_decode(output,skip_special_tokens=True)[0]
        (out/'full-decoded.txt').write_text(raw)
        (out/'continuation.txt').write_text(tokenizer.decode(generated,skip_special_tokens=True))
        reason='eos' if generated[-1]==tokenizer.eos_token_id else 'length' if len(generated)==cfg['max_new_tokens'] else 'other'
        save(out/'generation.json',dict(output_tokens=len(generated),output_ids=generated,finish_reason=reason,
                                        raw_sha256=digest(raw.encode()),generation_seconds=time.monotonic()-began))
        print(key,reason,len(generated),flush=True)
    except RuntimeError as e:
        save(out/'unresolved.json',dict(reason=repr(e)))
        torch.cuda.empty_cache()
metadata.update(total_seconds=time.monotonic()-start,peak_cuda_bytes=torch.cuda.max_memory_allocated(),
                peak_reserved_bytes=torch.cuda.max_memory_reserved())
save(root/'runtime.json',metadata)
