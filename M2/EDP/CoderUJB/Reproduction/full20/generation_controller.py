"""Bounded four-job ROMEO controller. Resumes only undispatched groups; no API calls."""
from pathlib import Path
from datetime import datetime,timezone
import fcntl,hashlib,json,subprocess,time,shutil
BASE=Path(__file__).resolve().parents[1]
RUN=BASE/'evidence/cl13-full20-20261105'
TERMINAL={'COMPLETED','FAILED','TIMEOUT','CANCELLED','OUT_OF_MEMORY','PREEMPTED','NODE_FAIL','BOOT_FAIL','DEADLINE'}
def load(p):return json.loads(p.read_text())
def save(p,o):
 p.parent.mkdir(exist_ok=True,parents=True);t=p.with_suffix('.tmp');t.write_text(json.dumps(o,indent=2)+'\n');t.replace(p)
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def command(argv,timeout=90):return subprocess.check_output(argv,text=True,timeout=timeout).strip()
def ssh(c):return command(['ssh','-o','BatchMode=yes','-o','ConnectTimeout=15','romeo',c])
def state(job):
 s=ssh(f'sacct -Xj {job} -nP -o State');return s.splitlines()[0].split('|')[0].split()[0].rstrip('+') if s else 'UNKNOWN'
def sync(d):
 remote=(d/'remote.txt').read_text().strip()
 subprocess.run(['rsync','-aq','--exclude=*.tmp',f'romeo:{remote}/',str(d)+'/'],check=True,timeout=90)
 for g in (d/'rows').glob('*/generation.json'):
  obj=load(g)
  for c in obj['candidates']:assert sha(g.parent/c['raw_file'])==c['raw_sha256']
  # Once all candidate files are locally verified, this marks the group available for scoring.
  marker=RUN/'ready'/(obj['key']+'.json')
  if not marker.exists():save(marker,dict(batch=d.name,generation=str(g.relative_to(RUN)),sha256=sha(g)))
def submit(d):
 attempts=sorted(d.glob('submission-*.json'));attempt=len(attempts)+1
 if attempt>3:raise RuntimeError('Batch exceeded three allocations: '+d.name)
 pending=d/f'submission-{attempt:02d}.started'
 if pending.exists():raise RuntimeError('Uncertain prior sbatch; inspect by unique job name before resuming: '+str(pending))
 if not (d/'remote.txt').exists():
  remote=ssh('mktemp -d /scratch_p/hibouwu/coderujb/full20-'+d.name+'-XXXXXX');(d/'remote.txt').write_text(remote+'\n')
 remote=(d/'remote.txt').read_text().strip();assert remote.startswith('/scratch_p/hibouwu/coderujb/full20-')
 for f in ('generate.py','job.sh','weights.json','protocol.json'):shutil.copyfile(RUN/f,d/f)
 subprocess.run(['scp','-q',*[str(d/f) for f in ('generate.py','job.sh','weights.json','protocol.json','inputs.json')],f'romeo:{remote}/'],check=True,timeout=90)
 pending.touch(exist_ok=False)
 job=ssh(f'cd {remote} && sbatch --parsable -A r260073 -p short --gres=gpu:1 -C armgpu --cpus-per-task=8 --mem=192G --time=04:00:00 -J ujb-f20-{d.name} job.sh').split(';')[0]
 assert job.isdigit()
 save(d/f'submission-{attempt:02d}.json',dict(job=job,time=datetime.now(timezone.utc).isoformat(),remote=remote,attempt=attempt))
 print('submitted',d.name,job,flush=True)
 return job

def main():
 with (RUN/'generation-controller.lock').open('a') as lock:
  fcntl.flock(lock,fcntl.LOCK_EX|fcntl.LOCK_NB)
  assert load(RUN/'capacity-gate.json')['allowed']
  frozen=load(RUN/'generation-freeze.json')
  for f,h in frozen['files'].items():assert sha(RUN/f)==h,f
  dirs=sorted((RUN/'batches').iterdir())
  while True:
   active=[];todo=[];complete=0;errors=[];generated=0;observations={}
   for d in dirs:
    expected=load(d/'inputs.json');n=len(expected)
    attempts=sorted(d.glob('submission-*.json'))
    if attempts:
     rec=load(attempts[-1]);job=rec['job']
     try:
      s=state(job)
      if not (d/'collected-terminal.json').exists():sync(d)
      observations[d.name]=dict(job=job,state=s)
     except (subprocess.SubprocessError,OSError) as e:
      errors.append(dict(batch=d.name,type=type(e).__name__));active.append(d);continue
     got=list((d/'rows').glob('*/generation.json'));generated+=sum(len(load(p)['candidates']) for p in got)
     if s not in TERMINAL:active.append(d);continue
     if not (d/'collected-terminal.json').exists():
      acc=ssh(f'sacct -j {job} -P -o JobID,State,ExitCode,Elapsed,AllocTRES,MaxRSS');(d/f'accounting-{job}.txt').write_text(acc)
     if len(got)==n:
      if not (d/'collected-terminal.json').exists():save(d/'collected-terminal.json',dict(job=job,state=s,groups=n,time=time.time()))
      complete+=1;continue
     # A started but incomplete group is never silently replaced.
     unknown=[p.parent.name for p in (d/'rows').glob('*/dispatch.json') if not (p.parent/'generation.json').exists()]
     if unknown:raise RuntimeError('Incomplete dispatched groups require diagnosis: '+str((d.name,unknown)))
     todo.append(d)
    else:todo.append(d)
   save(RUN/'generation-progress.json',dict(time=datetime.now(timezone.utc).isoformat(),completed_batches=complete,total_batches=len(dirs),generated_candidates=generated,planned_candidates=35380,active=len(active),observations=observations,observation_errors=errors))
   print('progress',complete,len(dirs),generated,'active',len(active),'observe_errors',len(errors),flush=True)
   if complete==len(dirs):break
   if (RUN/'STOP-GENERATION').exists():break
   for d in todo[:max(0,4-len(active))]:submit(d)
   time.sleep(45)
if __name__=='__main__':main()
