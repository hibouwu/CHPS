"""Verify completion against the bounded B goal, without regenerating or rerunning tests."""
import csv,datetime,json,re,subprocess
from pathlib import Path
from score_b100 import B,MODELS,read
from score_candidate import BASE,sha,save
from heatmap_a100 import FROZEN,name

def main():
 integ=read(B/'integrity.json');pairs=read(B/'paired-results.json');remote=read(B/'remote-integrity.json');freeze=read(B/'freeze.json')
 assert freeze['a_results_seen'] and freeze['max_formal_generations']==400
 assert sha((BASE/'evidence/dataset-audit/heatmap-100.json').read_bytes())==freeze['frozen_sample_sha256']
 logs=set();unknown=[];resources={};actual=read(B/'actual-input-deltas.json')
 active_jobs=set(subprocess.check_output(['ssh','-o','BatchMode=yes','romeo','squeue','-h','-u','hibouwu','-o','%A'],text=True).split())
 assert len(actual)==400 and all(r['discarded_input_tokens']==0 and r['discarded_text']=='' for r in actual)
 assert len(pairs['rows'])==400
 assert 'B 列的四模型 400 次生成与评分也已完成' in (BASE.parent/'README.md').read_text()
 assert '## B 列结果：固定输出约束' in (BASE/'实验设计.md').read_text()
 frozen_code_at=datetime.datetime.fromisoformat(read(B/'implementation-freeze.json')['time'])
 for dispatch in (B/'sol/rows').glob('*/dispatch.json'):
  assert datetime.datetime.fromisoformat(read(dispatch)['time'])>=frozen_code_at
 for model in MODELS:
  m=integ['models'][model];assert m['dispatched']==m['generated']==m['scored']==100
  assert m['a_manifest_unchanged'] and m['protocol_inherited'] and m['input_truncated']==0
  assert len(list((B/model/'rows').glob('*/dispatch.json')))==100
  assert len(list((B/model/'scores').glob('*.json')))==100
  for r in FROZEN:
   s=read(B/model/'scores'/(name(r)+'.json'));p=BASE/s['result'];v=read(p)
   assert v['task']==r['task'] and v['revision']==r['revision'] and v['task_idx']==r['task_idx'] and v['origin']=='model'
   assert v['scorer_sha256']==freeze['scorer_sha256'] and v['raw_sha256']==s['scorer_input_sha256']
   assert s['answer_untouched'] and (s['mode']=='complete')==(model=='cl')
   for c in v.get('commands',[]):
    for f in ('stdout','stderr'):assert (p.parent/c[f]).is_file();logs.add(str(p.parent/c[f]))
   if s['status']=='pass' and r['task']!='DD':
    assert v['commands'] and all(c['exit_code']==0 and not c['timeout'] for c in v['commands'])
    assert v['tests']
    for label,t in v['tests'].items():
     count=int(re.search(r'^Failing tests:\s*(\d+)\s*$',(p.parent/(label+'.stdout.log')).read_text(),re.M)[1])
     assert count==len(t['failed'])
     assert (t['failed']==[t['selected']]) if label.startswith('buggy') else count==0
    if r['task'] in ('FCG','APR'):assert 'suite' in v['tests']
    if r['task'] in ('CTG','ITG'):assert v['coverage']['instrumented_lines_hit']>0 and (p.parent/'coverage.xml').exists()
    if r['task']=='ITG':assert any(x.startswith('buggy-test') for x in v['tests'])
   if s['status'] not in ('pass','fail'):unknown.append(dict(model=model,key=name(r),status=s['status'],reason=s['reason'],result=s['result']))
  if model!='sol':
   rr=remote['models'][model];assert rr['state']=='COMPLETED'
   lifecycle=list(csv.DictReader((B/model/'lifecycle-utc.txt').read_text().splitlines(),delimiter='|'))[0]
   submitted=datetime.datetime.fromisoformat(lifecycle['Submit']).replace(tzinfo=datetime.timezone.utc)
   assert submitted>=datetime.datetime.fromisoformat(read(B/'implementation-freeze.json')['time'])>=datetime.datetime.fromisoformat(freeze['frozen_at'])
   table=list(csv.DictReader((B/model/'terminal-accounting.txt').read_text().splitlines(),delimiter='|'));job=next(x for x in table if x['JobID']==rr['job'])
   assert job['State']=='COMPLETED' and job['ExitCode']=='0:0' and 'gres/gpu=1' in job['AllocTRES']
   hours,mins,secs=map(int,job['Elapsed'].split(':'));resources[model]=dict(job=rr['job'],elapsed=job['Elapsed'],gpu_seconds=hours*3600+mins*60+secs,alloc_tres=job['AllocTRES'])
   for line in (B/model/'remote-sha256-final.txt').read_text().splitlines():
    h,file=line.split('  ',1);assert sha((B/model/file).read_bytes())==h
   assert rr['job'] not in active_jobs
 cost=read(B/'cost.json');old=read(BASE/'evidence/sol-a100/cost.json');ledger=read(BASE/'evidence/dataset-audit/窗口预算.json')
 assert cost['formal_requests']==cost['responses']==100 and cost['unknown_billing_reserve']==0 and not cost['uncertain']
 assert cost['standard_estimate_usd']<=cost['conservative_usd']<=cost['worst_case_usd']<10
 assert ledger['paid_jobs_submitted']==205 and ledger['reserved_maximum']==0
 assert abs(ledger['incurred_estimate']-cost['standard_estimate_usd']-old['total_estimate_usd'])<1e-8
 assert ledger['incurred_conservative_upper']<30
 assert read(BASE/'evidence/cl13-a100/scores'/('FCG-116-'+next(r['revision'] for r in FROZEN if r['task']=='FCG')+'.json'))['status']=='timeout_unresolved'
 assert read(BASE/'evidence/qwen-a100/scores'/('APR-410-'+next(r['revision'] for r in FROZEN if r['task']=='APR')+'.json'))['status']=='infrastructure_unresolved'
 save(B/'resources.json',dict(models=resources,total_gpu_seconds=sum(x['gpu_seconds'] for x in resources.values()),note='Three jobs overlapped; sum is allocated single-GPU job time including model staging, not wall-clock duration or monetary cost.'))
 for ext in ('png','svg','pdf'):assert (B/f'heatmap-ab.{ext}').stat().st_size>1000
 md=(B/'A-B对照报告.md').read_text();assert '探索性' in md and '双方可解析' in md and 'C–E' in md
 for target in re.findall(r'\]\(([^)]+)\)',md):
  if not target.startswith(('https:','http:','#')):assert (B/target).exists(),target
 assert datetime.datetime.now(datetime.timezone.utc)<datetime.datetime.fromisoformat(freeze['absolute_stop'])
 save(B/'completion-audit.json',dict(status='complete',verified_at=datetime.datetime.now(datetime.timezone.utc).isoformat(),models=integ['models'],formal_generations=400,synthetic_model_requests=0,command_logs_verified=len(logs),unknown_B=unknown,prior_A_unchanged=True,prior_unknown_A_preserved=True,window_paid_estimate_usd=ledger['incurred_estimate'],window_paid_conservative_usd=ledger['incurred_conservative_upper'],reserved_usd=0,remote_jobs_terminal=True,scope_excluded=['C-E','2239-row full run']))
 files=[p for p in B.rglob('*') if p.is_file() and p.name!='sha256.json' and not p.name.endswith('.lock')]
 manifest={str(p.relative_to(B)):sha(p.read_bytes()) for p in sorted(files)}
 for script in ['prepare_b100.py','stage_b100.py','run_sol_b100.py','score_b100.py','collect_b100.py','collect_b100_final.py','verify_b100.py','report_b100.py','finalize_b_docs.py','audit_b100_completion.py']:manifest['../../'+script]=sha((BASE/script).read_bytes())
 save(B/'sha256.json',manifest)
 assert all(sha((B/p).read_bytes())==h for p,h in read(B/'sha256.json').items())
 print(json.dumps(dict(status='complete',generations=400,unknown_B=len(unknown),files_verified=len(manifest),logs=len(logs),window_estimate=ledger['incurred_estimate']),ensure_ascii=False))
if __name__=='__main__':main()
