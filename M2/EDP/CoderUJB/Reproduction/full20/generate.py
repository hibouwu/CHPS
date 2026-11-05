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
weight_dir.mkdir(exist_ok=True)
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


import argparse
parser=argparse.ArgumentParser();parser.add_argument('--probe',action='store_true');args=parser.parse_args()
job=os.environ['SLURM_JOB_ID']
start=time.monotonic()
with ThreadPoolExecutor(max_workers=3) as ex: receipts=list(ex.map(stage_file,weights['files']))
save(root/f'weights-receipt-{job}.json',receipts)
tokenizer=AutoTokenizer.from_pretrained(weight_dir,local_files_only=True)
model=AutoModelForCausalLM.from_pretrained(weight_dir,torch_dtype=torch.bfloat16,local_files_only=True,
        low_cpu_mem_usage=False,attn_implementation=cfg['attention']).to('cuda').eval()
torch.cuda.synchronize()
meta=dict(job_id=job,node=socket.gethostname(),gpu=torch.cuda.get_device_name(0),torch=torch.__version__,
 transformers=transformers.__version__,cuda=torch.version.cuda,dtype=str(next(model.parameters()).dtype),
 attention=model.config._attn_implementation,generation_defaults=model.generation_config.to_dict(),
 staging_load_seconds=time.monotonic()-start,protocol_sha256=digest((root/'protocol.json').read_bytes()),
 generator_sha256=digest(Path(__file__).read_bytes()))
save(root/f'runtime-{job}.json',meta)
print('loaded',json.dumps(meta),flush=True)
if args.probe:
 rows=[dict(key='synthetic-capacity-4096-20',task='PROBE',task_idx=4,candidates=20,
            prompt='// Capacity probe, not a benchmark problem.\n'+'// padding token repeated for memory capacity\n'*1500+'public int answer() { return ')]
else:
 rows=json.loads((root/'inputs.json').read_text())
 assert len(rows)==len({r['key'] for r in rows})
job_end=int(os.environ.get('SLURM_JOB_END_TIME',str(time.time()+3300)))
for row in rows:
 if (root/'STOP').exists():break
 out=root/'rows'/row['key'];out.mkdir(parents=True,exist_ok=True)
 if (out/'dispatch.json').exists():continue
 if time.time()+300>=job_end:
  print('admission stopped before scheduler deadline',flush=True);break
 prompt=row['prompt']
 if not args.probe:assert digest(prompt.encode())==row['prompt_sha256']
 enc=tokenizer([prompt],return_tensors='pt');full=int(enc.input_ids.shape[1])
 ids=enc.input_ids[:,-cfg['input_tokens']:].to('cuda');mask=enc.attention_mask[:,-cfg['input_tokens']:].to('cuda')
 with (out/'dispatch.json').open('x') as f:
  json.dump(dict(key=row['key'],job=job,seed=row['task_idx'],candidates=row['candidates'],
     protocol_sha256=meta['protocol_sha256'],generator_sha256=meta['generator_sha256'],input_sha256=digest(prompt.encode()),
     input_tokens_full=full,input_tokens_used=ids.shape[1],input_truncated=full>ids.shape[1],input_ids=ids[0].tolist(),
     time=time.time(),probe=args.probe),f);f.flush();os.fsync(f.fileno())
 began=time.monotonic();torch.cuda.reset_peak_memory_stats()
 try:
  torch.manual_seed(row['task_idx'])
  with torch.inference_mode():
   output=model.generate(input_ids=ids,attention_mask=mask,temperature=cfg['temperature'],do_sample=True,
      num_return_sequences=row['candidates'],max_new_tokens=cfg['max_new_tokens'],
      prefill_chunk_size=cfg.get('prefill_chunk_size'))
  torch.cuda.synchronize()
  decoded=tokenizer.batch_decode(output,skip_special_tokens=True)
  endings=model.generation_config.eos_token_id;endings={endings} if isinstance(endings,int) else set(endings)
  records=[]
  for i,(seq,raw) in enumerate(zip(output,decoded,strict=True)):
   token_ids=seq[ids.shape[1]:].tolist();stop=next((j for j,t in enumerate(token_ids) if t in endings),None)
   token_ids=token_ids if stop is None else token_ids[:stop+1]
   path=out/f'candidate-{i:02d}.txt';path.write_bytes(raw.encode())
   records.append(dict(candidate_index=i,raw_file=path.name,raw_sha256=digest(raw.encode()),output_ids=token_ids,
      output_tokens=len(token_ids),finish_reason='eos' if stop is not None else 'length'))
  save(out/'generation.json',dict(key=row['key'],job=job,candidates=records,generation_seconds=time.monotonic()-began,
      peak_cuda_allocated_bytes=torch.cuda.max_memory_allocated(),peak_cuda_reserved_bytes=torch.cuda.max_memory_reserved()))
  print(row['key'],'completed',len(records),round(time.monotonic()-began,2),torch.cuda.max_memory_allocated(),flush=True)
  del output
 except RuntimeError as exc:
  save(out/'generation-error.json',dict(type=type(exc).__name__,message=str(exc),elapsed=time.monotonic()-began,
       oom=isinstance(exc,torch.cuda.OutOfMemoryError),job=job))
  print(row['key'],'ERROR',repr(exc),flush=True)
  # Preserve dispatch. Never silently regenerate an interrupted/failed candidate group.
  if args.probe or isinstance(exc,torch.cuda.OutOfMemoryError):raise
 finally:
  del ids,mask,enc
  torch.cuda.empty_cache()
meta['elapsed_seconds']=time.monotonic()-start
save(root/f'runtime-{job}.json',meta)
