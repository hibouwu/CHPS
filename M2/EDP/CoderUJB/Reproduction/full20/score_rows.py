"""Score saved full20 groups; reference controls stay outside model inputs and metrics."""
import os,json,hashlib,re,time,fcntl,argparse
from pathlib import Path
from types import SimpleNamespace
from concurrent.futures import ThreadPoolExecutor
from collections import Counter
from scorer import BASE,row_at,official,evaluate,save,sha
RUN=Path(os.environ['CODERUJB_RUN'])

def read(p):return json.loads(p.read_text())
def score_one(row):
 key=row['key'];dest=RUN/'scores'/key;dest.mkdir(parents=True,exist_ok=True)
 with (dest/'lock').open('a') as lock:
  fcntl.flock(lock,fcntl.LOCK_EX)
  if (dest/'complete.json').exists():return
  ready=read(RUN/'ready'/(key+'.json'));p=RUN/ready['generation']
  assert sha(p.read_bytes())==ready['sha256']
  gen=read(p);assert gen['key']==key and len(gen['candidates'])==row['candidates']
  data=row_at(row['task'],row['task_idx']);ns=official(row['task']);obj=SimpleNamespace(dataset={'train':{row['task_idx']:data}},_stop_at_function=ns['_stop_at_function'])
  control=None
  if row['task']!='DD':
   reference=data['fix'] if row['task']=='APR' else data['function']
   cp=evaluate(row['task'],row['task_idx'],reference,'extracted','reference_control');control=read(cp)
   save(dest/'reference.json',dict(status=control['status'],reason=control.get('reason'),path=str(cp.relative_to(RUN)),role='environment control, excluded from formal answers'))
  results=[]
  for c in gen['candidates']:
   target=dest/f"candidate-{c['candidate_index']:02d}.json"
   if target.exists():results.append(read(target));continue
   raw=(p.parent/c['raw_file']).read_bytes().decode();assert sha(raw.encode())==c['raw_sha256']
   patch=ns['postprocess_complete_generation'](obj,raw,row['task_idx'])
   common=dict(key=key,task=row['task'],task_idx=row['task_idx'],revision=row['revision'],candidate_index=c['candidate_index'],raw_sha256=c['raw_sha256'],raw_path=str((p.parent/c['raw_file']).relative_to(RUN)),candidate_sha256=sha(patch.encode()),finish_reason=c['finish_reason'],output_tokens=c['output_tokens'])
   # Invalid candidate text can be assessed independently, but environment failures are not attributed to a model.
   if control is not None and control['status']!='pass':
    rec=dict(common,status='infrastructure_unresolved',reason='reference_control_not_passed',reference_status=control['status'])
   else:
    sp=evaluate(row['task'],row['task_idx'],patch,'extracted','model');s=read(sp)
    rec=dict(common,status=s['status'],reason=s.get('reason'),category=s.get('category'),coverage=s.get('coverage'),result=str(sp.relative_to(RUN)),reference_passed=control is None or control['status']=='pass')
    if s['status']=='timeout_unresolved':
     # Declared up front: published wall-time budget is part of this new benchmark protocol.
     rec.update(status='fail',reason='published_timeout_budget_exceeded',raw_status=s['status'])
    if s['status']=='infrastructure_unresolved' and any(x.get('exit_code') for x in s['commands']):
     diagnostics='\n'.join((sp.parent/x['stderr']).read_text(errors='replace') for x in s['commands'] if x.get('exit_code'))
     if re.search(r'\[javac\].*:\d+: error:',diagnostics):
      rec.update(status='fail',reason='candidate_compile_with_passing_reference',raw_status=s['status'])
    if row['task']=='ITG' and rec['status']=='pass':
     trace=(sp.parent/'buggy-test-0.failing_tests.txt').read_text();case=data['testmethod'].strip()
     frame=re.search(r'^\s*at '+re.escape(case.replace('::','.'))+r'\([^:]+:(\d+)\)',trace,re.M)
     lo=data['start_buggy']+1;hi=data['start_buggy']+len(patch.split('\n'))
     if not frame or not lo<=int(frame[1])<=hi:rec.update(status='infrastructure_unresolved',reason='failure_not_located_in_inserted_test')
     else:rec['buggy_assertion_source_line']=int(frame[1])
   save(target,rec);results.append(rec)
  assert len(results)==row['candidates'] and sorted(x['candidate_index'] for x in results)==list(range(row['candidates']))
  save(dest/'complete.json',dict(key=key,candidates=len(results),statuses=dict(Counter(x['status'] for x in results)),time=time.time()))
  print(key,'scored',dict(Counter(x['status'] for x in results)),flush=True)

def main():
 p=argparse.ArgumentParser();p.add_argument('--workers',type=int,default=2);p.add_argument('--once',action='store_true');p.add_argument('--owner',choices=['local','remote']);p.add_argument('--idle-exit-seconds',type=int,default=0);p.add_argument('--shard',type=int,default=0);p.add_argument('--shards',type=int,default=1);a=p.parse_args()
 rows=[x for i,x in enumerate(read(RUN/'manifest.json')) if i%a.shards==a.shard]
 if a.owner:
  owners=read(RUN/'ownership.json');rows=[r for r in rows if owners[r['key']]==a.owner]
 (RUN/'scores').mkdir(exist_ok=True)
 with (RUN/f'scorer-{a.shard}-of-{a.shards}.lock').open('a') as lock:
  fcntl.flock(lock,fcntl.LOCK_EX|fcntl.LOCK_NB)
  idle_since=time.time()
  while True:
   ready=[r for r in rows if (RUN/'ready'/(r['key']+'.json')).exists() and not (RUN/'scores'/r['key']/'complete.json').exists()]
   if ready:idle_since=time.time()
   with ThreadPoolExecutor(max_workers=a.workers) as pool:list(pool.map(score_one,ready))
   count=sum((RUN/'scores'/r['key']/'complete.json').exists() for r in rows)
   save(RUN/f'scoring-progress-{a.shard}.json',dict(completed_groups=count,planned_groups=len(rows),time=time.time(),workers=a.workers))
   if count==len(rows) or a.once or (a.owner!='remote' and (RUN/'STOP-SCORING').exists()) or (a.idle_exit_seconds and not ready and time.time()-idle_since>a.idle_exit_seconds):break
   time.sleep(30)
if __name__=='__main__':main()
