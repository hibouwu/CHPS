"""Stage verified raw answers, run four isolated CPU scoring shards, collect primary evidence."""
from pathlib import Path
from datetime import datetime,timezone
import json,subprocess,time,fcntl,hashlib
BASE=Path(__file__).resolve().parents[1];RUN=BASE/'evidence/cl13-full20-20261105';OUT=RUN/'remote-primary'
REMOTE='/scratch_p/hibouwu/coderujb/full20-eval-aeV81g';RR=REMOTE+'/repro/run'
TERMINAL={'COMPLETED','FAILED','TIMEOUT','CANCELLED','OUT_OF_MEMORY','PREEMPTED','NODE_FAIL','BOOT_FAIL','DEADLINE'}
def read(p):return json.loads(p.read_text())
def save(p,x):
 p.parent.mkdir(exist_ok=True,parents=True);t=p.with_suffix('.tmp');t.write_text(json.dumps(x,indent=2)+'\n');t.replace(p)
def ssh(c):return subprocess.check_output(['ssh','-o','BatchMode=yes','-o','ConnectTimeout=15','romeo',c],text=True,timeout=60).strip()
def rsync(args):subprocess.run(['rsync','-aq','--exclude=*.tmp',*args],check=True,timeout=120)
def main():
 with (OUT/'controller.lock').open('a') as lock:
  fcntl.flock(lock,fcntl.LOCK_EX|fcntl.LOCK_NB)
  assert read(OUT/'environment-gate.json')['allowed']
  manifest=read(RUN/'manifest.json');sent=set(read(OUT/'sent.json')) if (OUT/'sent.json').exists() else set()
  while True:
   new=[r for r in manifest if r['key'] not in sent and (RUN/'ready'/(r['key']+'.json')).exists()]
   new=new[:25]  # Bound each transfer; stage data before publishing ready markers.
   if new:
    paths=[];markers=[]
    for r in new:
     m=RUN/'ready'/(r['key']+'.json');g=RUN/read(m)['generation'];obj=read(g)
     assert hashlib.sha256(g.read_bytes()).hexdigest()==read(m)['sha256']
     paths.extend(str(p.relative_to(RUN)) for p in g.parent.iterdir() if p.is_file() and p.suffix!='.tmp')
     markers.append(str(m.relative_to(RUN)))
    for label,items in [('raw',paths),('ready',markers)]:
     f=OUT/(label+'-files.txt');f.write_text('\n'.join(items)+'\n')
     rsync(['--files-from='+str(f),str(RUN)+'/',f'romeo:{RR}/'])
    sent.update(r['key'] for r in new);save(OUT/'sent.json',sorted(sent))
   # Pull candidate score indexes and their raw execution evidence together.
   rsync([f'romeo:{RR}/scores/',str(OUT/'scores')+'/'])
   rsync([f'romeo:{RR}/scoring/',str(OUT/'scoring')+'/'])
   states={};jobs=[]
   for shard in range(4):
    d=OUT/f'cpu-shard-{shard}';d.mkdir(exist_ok=True)
    submissions=sorted(d.glob('submission-*.json'))
    state='NONE'
    if submissions:
     job=read(submissions[-1])['job'];s=ssh(f'sacct -Xj {job} -nP -o State');state=s.splitlines()[0].split('|')[0].split()[0].rstrip('+') if s else 'UNKNOWN'
     states[shard]=dict(job=job,state=state)
     if state in TERMINAL and not (d/f'accounting-{job}.txt').exists():(d/f'accounting-{job}.txt').write_text(ssh(f'sacct -j {job} -P -o JobID,State,ExitCode,Elapsed,AllocTRES,MaxRSS')+'\n')
    rows=[r for i,r in enumerate(manifest) if i%4==shard]
    ready=[r for r in rows if r['key'] in sent and not (OUT/'scores'/r['key']/'complete.json').exists()]
    if ready and (state=='NONE' or state in TERMINAL):
     if len(submissions)>=8:raise RuntimeError('CPU shard allocation bound reached')
     if state in ('FAILED','OUT_OF_MEMORY','NODE_FAIL','BOOT_FAIL'):raise RuntimeError(f'CPU shard {shard} needs diagnosis: {state}')
     num=len(submissions)+1;started=d/f'submission-{num:02d}.started'
     if started.exists():raise RuntimeError('Uncertain CPU submission')
     started.touch(exist_ok=False)
     job=ssh(f'cd {REMOTE} && sbatch --parsable -A r260073 -p short -C x64cpu --cpus-per-task=16 --mem=48G --time=08:00:00 -J ujb-f20-cpu-{shard} repro/full20/cpu_job.sh {shard}').split(';')[0];assert job.isdigit()
     save(d/f'submission-{num:02d}.json',dict(job=job,time=time.time(),shard=shard));print('CPU submitted',shard,job,flush=True)
   done=sum((OUT/'scores'/r['key']/'complete.json').exists() for r in manifest)
   save(OUT/'progress.json',dict(time=datetime.now(timezone.utc).isoformat(),staged_groups=len(sent),scored_groups=done,planned_groups=2239,jobs=states))
   subprocess.run(['python',str(BASE/'full20/summarize.py')],check=True)
   print('CPU progress',len(sent),done,states,flush=True)
   if done==len(manifest):break
   if (RUN/'STOP-CPU-CONTROLLER').exists():break
   time.sleep(60)
if __name__=='__main__':main()
