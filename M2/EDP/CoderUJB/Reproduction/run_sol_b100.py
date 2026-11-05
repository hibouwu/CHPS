"""One Sol request per B row, using the verified A request and accounting path."""
import argparse,datetime,fcntl,json,time,uuid
from concurrent.futures import ThreadPoolExecutor
import requests
from run_sol_a100 import BASE,LEDGER,MODEL,headers,payload,read,save,sha,name,now
A=BASE/'evidence/b100/sol'
DEADLINE=datetime.datetime.fromisoformat('2026-11-05T07:05:00+01:00')
def generate(r,pilot):
 dest=A/('pilot' if pilot else 'rows')/name(r)
 with (A/'dispatch.lock').open('a') as lock:
  fcntl.flock(lock,fcntl.LOCK_EX)
  if (dest/'dispatch.json').exists():return
  if (A/'STOP').exists():return
  if datetime.datetime.now(datetime.timezone.utc)>DEADLINE:return
  count=read(A/'counts'/(name(r)+'.json'))['body']['input_tokens'];upper=1.1*(count*2.5+4096*10)/1e6
  prior=list(A.glob('pilot/*/dispatch.json'))+list(A.glob('rows/*/dispatch.json'))
  assert sum(read(p)['reserved_usd'] for p in prior)+upper<=10
  req=payload(r);assert r['prompt_sha256']==sha(r['prompt'].encode())
  dest.mkdir(parents=True,exist_ok=True);save(dest/'request.json',req)
  client_id=str(uuid.uuid4())
  save(dest/'dispatch.json',dict(time=now(),key=name(r),client_request_id=client_id,input_tokens=count,reserved_usd=upper,prompt_sha256=r['prompt_sha256'],protocol_sha256=sha((A/'protocol.json').read_bytes()),request_sha256=sha((dest/'request.json').read_bytes())))
  ledger=read(LEDGER);ledger['paid_jobs_submitted']+=1;ledger['transactions'].append(dict(type='dispatch',stage='sol-b100',key=name(r),client_request_id=client_id,reserved_usd=upper,time=now()));save(LEDGER,ledger)
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
   fcntl.flock(lock,fcntl.LOCK_EX);ledger=read(LEDGER);ledger['incurred_estimate']+=meta['cost_standard_estimate_usd'];ledger['transactions'].append(dict(type='settled_usage',stage='sol-b100',key=name(r),usd=meta['cost_standard_estimate_usd'],conservative_usd=meta['cost_conservative_usd'],time=now()));save(LEDGER,ledger)
  print(name(r),obj['status'],i,o,round(meta['cost_standard_estimate_usd'],6),flush=True)
 except Exception as e:
  save(dest/'transport-error.json',dict(type=type(e).__name__,time=now(),possible_billing_reserved=upper));(A/'STOP').write_text('Uncertain dispatch: '+name(r));print(name(r),'uncertain',type(e).__name__,flush=True)
def count():
 rows=read(A/'inputs.json')
 def one(r):
  p=A/'counts'/(name(r)+'.json')
  if p.exists():return
  body=payload(r);body={k:v for k,v in body.items() if k in ('model','input','reasoning')}
  res=requests.post('https://api.openai.com/v1/responses/input_tokens',headers=headers(),json=body,timeout=60)
  save(p,dict(http_status=res.status_code,body=res.json(),request_id=res.headers.get('x-request-id'),prompt_sha256=r['prompt_sha256']))
 with ThreadPoolExecutor(max_workers=4) as pool:list(pool.map(one,rows))
 counts=[read(A/'counts'/(name(r)+'.json')) for r in rows]
 assert all(c['http_status']==200 for c in counts)
 n=sum(c['body']['input_tokens'] for c in counts);upper=1.1*(n*2.5+100*4096*10)/1e6
 assert upper<10
 save(A/'cost-plan.json',dict(stage='sol-b100',requests=100,input_tokens=n,max_output_tokens=409600,worst_case_usd=upper,reserved_usd=10,retries=0))
 l=read(LEDGER)
 assert l['reserved_maximum']==0 and l.get('incurred_conservative_upper',l['incurred_estimate'])+10<=30
 l['reserved_maximum']=10;l['transactions'].append(dict(type='reserve',stage='sol-b100',usd=10,time=now()));save(LEDGER,l)
 print('B Sol bounded plan',n,upper)
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('action',choices=['count','run']);a=p.parse_args().action
 if a=='count':count()
 else:
  assert (A/'cost-plan.json').exists() and (A.parent/'implementation-freeze.json').exists()
  with ThreadPoolExecutor(max_workers=2) as pool:list(pool.map(lambda r:generate(r,False),read(A/'inputs.json')))
