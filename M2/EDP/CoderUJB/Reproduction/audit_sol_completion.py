"""Read saved evidence and verify the bounded Sol goal without new model or test runs."""
import datetime,json,re,subprocess
from run_sol_a100 import A,BASE,LEDGER,DEADLINE,read,save,sha,name,now

def main():
 cfg=read(A/'protocol.json');cost=read(A/'cost.json');records=read(A/'four-models.json')['rows']
 assert len(records)==100 and len({name(r) for r in records})==100
 assert not (A/'STOP').exists()
 verified=[];logs=0
 for r in records:
  s=read(A/'scores'/(name(r)+'.json'));p=BASE/s['result'];v=read(p)
  assert s['status'] in ('pass','fail') and v['scorer_sha256']==sha((BASE/'score_candidate.py').read_bytes())
  assert v['mode']=='chat' and v['origin']=='model'
  assert v['raw_sha256']==sha((A/'rows'/name(r)/'final.txt').read_bytes())
  for c in v.get('commands',[]):
   for which in ('stdout','stderr'):assert (p.parent/c[which]).is_file();logs+=1
  if s['status']=='pass' and r['task']!='DD':
   assert v['commands'] and all(c['exit_code']==0 and not c['timeout'] for c in v['commands'])
   tests=v['tests'];assert tests
   for label,t in tests.items():
    text=(p.parent/(label+'.stdout.log')).read_text();n=int(re.search(r'^Failing tests:\s*(\d+)\s*$',text,re.M)[1]);assert n==len(t['failed'])
    if label.startswith('buggy'):assert t['failed']==[t['selected']]
    else:assert n==0
   if r['task'] in ('FCG','APR'):assert 'suite' in tests
   if r['task'] in ('CTG','ITG'):assert v['coverage']['instrumented_lines_hit']>0 and (p.parent/'coverage.xml').exists()
   if r['task']=='ITG':assert any(t.startswith('buggy-test') for t in tests)
  elif r['task']=='DD':assert s['category'] in ('tp','tn','fp','fn')
  verified.append(dict(key=name(r),status=s['status'],scorer_path=s['result']))
 assert cost['pilot']['requests']==5 and cost['formal']['requests']==100 and cost['retries']==0 and cost['unknown_billing_requests']==0
 assert cost['total_estimate_usd']<=cost['conservative_usd']<=cost['original_worst_case_usd']<10
 l=read(LEDGER);assert l['reserved_maximum']==0 and l['paid_jobs_submitted']==105
 assert abs(l['incurred_estimate']-cost['total_estimate_usd'])<1e-8
 assert l['incurred_conservative_upper']<l['supervisor_defined_ceiling']==30
 assert read(A/'dd-first-choice.json')['disagreements']==0
 assert subprocess.check_output(['git','-C',str(BASE/'ujb'),'rev-parse','HEAD'],text=True).strip()=='e7b69a0b4f79d0d1896046079f6926d955f31452'
 assert not subprocess.check_output(['git','-C',str(BASE/'ujb'),'diff','--name-only'],text=True).strip()
 assert datetime.datetime.now(datetime.timezone.utc)<DEADLINE
 linked=[]
 for p in [BASE.parent/'README.md',BASE/'实验设计.md',A/'四模型对照.md']:
  text=p.read_text();assert '0.561186' in text
  for target in re.findall(r'\]\(([^)]+)\)',text):
   if target.startswith(('https:','http:','#')):continue
   if p==A/'四模型对照.md' or 'sol-a100' in target:
    assert (p.parent/target).exists(),target;linked.append(target)
 save(A/'completion-audit.json',dict(verified_at=now(),deadline=DEADLINE.isoformat(),official_api_and_normal_key_verified='access.json plus 105 recorded normal authenticated requests',formal_scored=100,pilots_scored=5,unique_requests=105,score_evidence=verified,command_logs_checked=logs,local_links_checked=len(linked),usd_estimate=cost['total_estimate_usd'],usd_conservative_upper=cost['conservative_usd'],pending_spend=0,reservation_released=True,conditional_qwen_diagnostic='not invoked: API available',scope_pending=['2239-row full evaluation','multi-sample paper protocol','B-E engineering columns'],prior_unresolved=['CodeLlama FCG-116 timeout','Qwen APR-410 test class initialization'],status='complete'))
 files=[p for p in A.rglob('*') if p.is_file() and p.name not in ('sha256.json','dispatch.lock')]
 manifest={str(p.relative_to(A)):sha(p.read_bytes()) for p in sorted(files)}
 for script in ('run_sol_a100.py','report_sol_a100.py','audit_sol_completion.py'):manifest['../../'+script]=sha((BASE/script).read_bytes())
 save(A/'sha256.json',manifest)
 assert all(sha((A/p).read_bytes())==h for p,h in read(A/'sha256.json').items())
 print(json.dumps(dict(status='complete',formal=100,pilots=5,files_verified=len(manifest),command_logs=logs,local_links=len(linked),cost=cost['total_estimate_usd'],deadline=DEADLINE.isoformat()),ensure_ascii=False))
if __name__=='__main__':main()
