"""Bounded official Responses evaluation; no SDK retries; durable dispatch before POST."""
import argparse,datetime,fcntl,hashlib,json,re,time,uuid
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
import requests
BASE=Path(__file__).resolve().parent
A=BASE/'evidence/sol-a100'
MODEL='gpt-6.1-sol'
KEYFILE=Path('/home/jianyeshi/Note/openaiAPIKeyGmail.txt')
LEDGER=BASE/'evidence/dataset-audit/窗口预算.json'
DEADLINE=datetime.datetime.fromisoformat('2026-11-05T07:22:00+01:00')
def sha(b):return hashlib.sha256(b).hexdigest()
def save(p,o):
 p.parent.mkdir(parents=True,exist_ok=True); tmp=p.with_suffix('.tmp');tmp.write_text(json.dumps(o,ensure_ascii=False,indent=2)+'\n');tmp.replace(p)
def read(p):return json.loads(p.read_text())
def now():return datetime.datetime.now(datetime.timezone.utc).isoformat()
def name(r):return f"{r['task']}-{r['task_idx']}-{r['revision']}"
def headers():
 key=re.search(r'sk-[A-Za-z0-9_-]{16,}',KEYFILE.read_text()).group()
 return {'Authorization':'Bearer '+key,'Content-Type':'application/json'}
def payload(r):return dict(model=MODEL,input=[dict(role='user',content=r['prompt'])],reasoning={'effort':'medium'},max_output_tokens=4096,service_tier='default',store=False)
def prepare():
 formal=read(BASE/'evidence/qwen-a100/inputs.json')
 frozen=read(BASE/'evidence/dataset-audit/heatmap-100.json')
 assert len(formal)==100 and [(name(r),r['prompt_sha256']) for r in formal]==[(name(r),r['chat_sha256']) for r in frozen]
 pilots=[read(BASE/'evidence/qwen-a100/pilot-input.json')]+read(BASE/'evidence/oss120-task-pilot/prompts.json')
 assert len(pilots)==5 and len({r['task'] for r in pilots})==5
 for r in pilots:r['prompt_sha256']=sha(r['prompt'].encode())
 assert not {name(r) for r in pilots}&{name(r) for r in formal}
 cfg=dict(model=MODEL,endpoint='https://api.openai.com/v1/responses',reasoning_effort='medium',max_output_tokens=4096,service_tier='default',store=False,tools=[],temperature=None,seed=None,prompt='unchanged official chat prompt as one user message; no extra system instruction',candidate_count=1,retries=0,credential_file=str(KEYFILE),frozen_sha256=sha((BASE/'evidence/dataset-audit/heatmap-100.json').read_bytes()),deadline=DEADLINE.isoformat(),stage_ceiling_usd=10,input_per_million=2,cached_input_per_million=.1,cache_write_per_million=2.5,output_per_million=10,upper_cost_note='all input at cache-write rate plus 10% regional buffer; all 4096 output tokens billed including reasoning')
 if (A/'protocol.json').exists():assert read(A/'protocol.json')==cfg
 else:save(A/'protocol.json',cfg);save(A/'inputs.json',formal);save(A/'pilots.json',pilots)
 def count(r):
  p=A/'counts'/(name(r)+'.json')
  if p.exists():return
  data=payload(r);data={k:v for k,v in data.items() if k in ('model','input','reasoning')}
  try:
   res=requests.post('https://api.openai.com/v1/responses/input_tokens',headers=headers(),json=data,timeout=60)
   obj=res.json();save(p,dict(http_status=res.status_code,body=obj,request_id=res.headers.get('x-request-id'),prompt_sha256=r['prompt_sha256']))
  except requests.RequestException as e:raise RuntimeError(type(e).__name__) from None
 with ThreadPoolExecutor(max_workers=4) as pool:list(pool.map(count,pilots+formal))
 counts=[read(A/'counts'/(name(r)+'.json')) for r in pilots+formal]
 assert all(c['http_status']==200 and isinstance(c['body'].get('input_tokens'),int) for c in counts)
 n=sum(c['body']['input_tokens'] for c in counts)
 upper=1.1*(n*2.5+105*4096*10)/1e6
 assert upper<10
 save(A/'cost-plan.json',dict(created=now(),requests=105,pilot=5,formal=100,input_tokens=n,max_output_tokens=105*4096,worst_case_usd=upper,stage_reserved_usd=10,retries=0))
 print(read(A/'cost-plan.json'),flush=True)
def generate(r,pilot):
 dest=A/('pilot' if pilot else 'rows')/name(r)
 with (A/'dispatch.lock').open('a') as lock:
  fcntl.flock(lock,fcntl.LOCK_EX)
  if (dest/'dispatch.json').exists():return
  if (A/'STOP').exists():return
  if datetime.datetime.now(datetime.timezone.utc)>DEADLINE-datetime.timedelta(minutes=10):return
  count=read(A/'counts'/(name(r)+'.json'))['body']['input_tokens'];upper=1.1*(count*2.5+4096*10)/1e6
  prior=list(A.glob('pilot/*/dispatch.json'))+list(A.glob('rows/*/dispatch.json'))
  assert sum(read(p)['reserved_usd'] for p in prior)+upper<=10
  req=payload(r);assert r['prompt_sha256']==sha(r['prompt'].encode())
  dest.mkdir(parents=True,exist_ok=True);save(dest/'request.json',req)
  client_id=str(uuid.uuid4())
  save(dest/'dispatch.json',dict(time=now(),key=name(r),client_request_id=client_id,input_tokens=count,reserved_usd=upper,prompt_sha256=r['prompt_sha256'],protocol_sha256=sha((A/'protocol.json').read_bytes()),request_sha256=sha((dest/'request.json').read_bytes())))
  ledger=read(LEDGER);ledger['paid_jobs_submitted']+=1;ledger['transactions'].append(dict(type='dispatch',stage='sol-a100',key=name(r),client_request_id=client_id,reserved_usd=upper,time=now()));save(LEDGER,ledger)
 started=time.monotonic()
 try:
  h=headers();h['X-Client-Request-Id']=client_id
  res=requests.post('https://api.openai.com/v1/responses',headers=h,json=req,timeout=(30,360))
  (dest/'response.json').write_bytes(res.content)
  obj=res.json()
  meta=dict(http_status=res.status_code,request_id=res.headers.get('x-request-id'),response_id=obj.get('id'),model=obj.get('model'),status=obj.get('status'),service_tier=obj.get('service_tier'),usage=obj.get('usage'),elapsed_seconds=time.monotonic()-started,response_sha256=sha(res.content),finished=now())
  if res.status_code!=200 or obj.get('model')!=MODEL or obj.get('service_tier') not in ('default',None):
   meta['error']=obj.get('error');save(dest/'generation.json',meta);(A/'STOP').write_text('API response requires review: '+name(r));print(name(r),'API stopped',res.status_code,flush=True);return
  messages=[x for x in obj.get('output',[]) if x.get('type')=='message' and x.get('role')=='assistant']
  finals=[x for x in messages if x.get('phase')=='final_answer']
  selected=finals or [x for x in messages if x.get('phase') is None]
  text='\n'.join(c['text'] for x in selected for c in x.get('content',[]) if c.get('type')=='output_text')
  meta['extraction']='final_answer message output_text; unphased assistant messages only when no final_answer'
  meta['message_phases']=[x.get('phase') for x in messages]
  (dest/'final.txt').write_text(text);meta['answer_sha256']=sha(text.encode());meta['incomplete_details']=obj.get('incomplete_details')
  usage=obj['usage'];i=usage['input_tokens'];o=usage['output_tokens'];cached=usage.get('input_tokens_details',{}).get('cached_tokens',0)
  writes=usage.get('input_tokens_details',{}).get('cache_write_tokens',0)
  assert cached+writes<=i
  meta['cost_standard_estimate_usd']=((i-cached-writes)*2+cached*.1+writes*2.5+o*10)/1e6
  meta['cost_conservative_usd']=1.1*(i*2.5+o*10)/1e6
  assert i==count and o<=4096 and meta['cost_conservative_usd']<=upper
  save(dest/'generation.json',meta)
  with (A/'dispatch.lock').open('a') as lock:
   fcntl.flock(lock,fcntl.LOCK_EX);ledger=read(LEDGER);ledger['incurred_estimate']+=meta['cost_standard_estimate_usd'];ledger['transactions'].append(dict(type='settled_usage',stage='sol-a100',key=name(r),usd=meta['cost_standard_estimate_usd'],conservative_usd=meta['cost_conservative_usd'],time=now()));save(LEDGER,ledger)
  print(name(r),obj['status'],i,o,round(meta['cost_standard_estimate_usd'],6),flush=True)
 except Exception as e:
  save(dest/'transport-error.json',dict(type=type(e).__name__,time=now(),possible_billing_reserved=upper));(A/'STOP').write_text('Uncertain dispatch: '+name(r));print(name(r),'uncertain',type(e).__name__,flush=True)
def score(r,pilot):
 from score_candidate import evaluate
 from heatmap_a100 import caller_compile_error
 from score_cl13_a100 import review_compile_diagnostic
 from score_qwen_a100 import review_signature
 dest=A/('pilot' if pilot else 'rows')/name(r);out=A/('pilot-scores' if pilot else 'scores')/(name(r)+'.json')
 if out.exists() or not (dest/'final.txt').exists():return
 gen=read(dest/'generation.json');raw=(dest/'final.txt').read_text();assert sha(raw.encode())==gen['answer_sha256']
 path=evaluate(r['task'],r['task_idx'],raw,'chat','model');rec=read(path)
 review=None if pilot else caller_compile_error(r['task'],r['task_idx'],path) or review_compile_diagnostic(r,path) or review_signature(r,path)
 result=dict(task=r['task'],task_idx=r['task_idx'],revision=r['revision'],status=rec['status'],reason=rec.get('reason'),category=rec.get('category'),coverage=rec.get('coverage'),source=str(dest.relative_to(BASE)),result=str(path.relative_to(BASE)),answer_sha256=gen['answer_sha256'],response_id=gen['response_id'],request_id=gen['request_id'],usage=gen['usage'],finish_status=gen['status'],cost_standard_estimate_usd=gen['cost_standard_estimate_usd'])
 if review:result.update(status='fail',reason=review.get('reason','candidate_compile_breaks_caller'),compile_review=review)
 save(out,result);print(name(r),result['status'],result['reason'],flush=True)
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('action',choices=['prepare','pilot','formal','score-pilot','score']);a=p.parse_args().action
 if a=='prepare':prepare()
 elif a in ('score','score-pilot'):
  pilot=a=='score-pilot';rows=read(A/('pilots.json' if pilot else 'inputs.json'))
  with ThreadPoolExecutor(max_workers=2) as pool:list(pool.map(lambda r:score(r,pilot),rows))
 else:
  pilot=a=='pilot'
  if not pilot:
   assert (A/'pilot-gate.json').exists() and read(A/'pilot-gate.json')['allow_formal']
  rows=read(A/('pilots.json' if pilot else 'inputs.json'))
  if pilot:
   with ThreadPoolExecutor(max_workers=2) as pool:list(pool.map(lambda r:generate(r,pilot),rows))
  else:
   with ThreadPoolExecutor(max_workers=2) as scoring:
    futures=[]
    def one(r):
     generate(r,False)
     futures.append(scoring.submit(score,r,False))
    with ThreadPoolExecutor(max_workers=2) as pool:list(pool.map(one,rows))
    for f in futures:f.result()
