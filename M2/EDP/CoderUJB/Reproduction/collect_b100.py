"""Collect isolated remote jobs and score available B outputs with two total Java workers."""
import datetime,json,subprocess,time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
from score_b100 import B,MODELS,score,read
from score_candidate import BASE,save
from heatmap_a100 import FROZEN,name
TERMINAL={'COMPLETED','FAILED','TIMEOUT','CANCELLED','NODE_FAIL','OUT_OF_MEMORY','PREEMPTED','BOOT_FAIL','DEADLINE'}
ADMISSION=datetime.datetime.fromisoformat('2026-11-05T07:10:00+01:00').timestamp()

def remote_sync(model):
 d=B/model;remote=(d/'remote.txt').read_text().strip();job=(d/'slurm-id.txt').read_text().strip()
 assert remote.startswith('/scratch_p/hibouwu/coderujb/') and job.isdigit()
 p=subprocess.run(['ssh','-o','BatchMode=yes','-o','ConnectTimeout=15','romeo','sacct','-Xj',job,'-nPo','State'],capture_output=True,text=True,timeout=30)
 if p.returncode:return 'OBSERVATION_ERROR'
 state=p.stdout.strip().splitlines()[0].split('|')[0].split()[0]
 subprocess.run(['rsync','-aq','--exclude=*.tmp',f'romeo:{remote}/',str(d)+'/'],check=True,timeout=120)
 if state.split('+')[0] in TERMINAL and not (d/'terminal-accounting.txt').exists():
  acc=subprocess.check_output(['ssh','-o','BatchMode=yes','romeo','sacct','-j',job,'-P','-o','JobID,State,ExitCode,Elapsed,AllocTRES,MaxRSS'],text=True,timeout=30);(d/'terminal-accounting.txt').write_text(acc)
 return state

def main():
 pending={};seen=set();states={}
 with ThreadPoolExecutor(max_workers=2) as pool:
  while True:
   for model in ('cl','oss','qwen'):
    if (B/model/'slurm-id.txt').exists():
     try:states[model]=remote_sync(model)
     except (subprocess.SubprocessError,OSError) as exc:states[model]='OBSERVATION_ERROR';print(model,type(exc).__name__,flush=True)
   # Fixed model order then frozen row order; do not select by scores.
   if time.time()<ADMISSION:
    for model in MODELS:
     earlier=list(MODELS)[:list(MODELS).index(model)]
     def finished(m):
      generated=len(list((B/m/'rows').glob('*/generation.json')))
      terminal=(states.get(m,'').split('+')[0] in TERMINAL) if m!='sol' else (B/'sol/generation-terminal.json').exists()
      return (terminal or generated==100) and len(list((B/m/'scores').glob('*.json')))==generated
     if not all(finished(m) for m in earlier):break
     for r in FROZEN:
      k=(model,name(r))
      if k in seen or (B/model/'scores'/(name(r)+'.json')).exists():continue
      if (B/model/'rows'/name(r)/'generation.json').exists():
       seen.add(k);pending[pool.submit(score,model,r)]=k
   for f in list(pending):
    if f.done():f.result();pending.pop(f)
   n={m:len(list((B/m/'scores').glob('*.json'))) for m in MODELS}
   save(B/'progress.json',dict(time=datetime.datetime.now(datetime.timezone.utc).isoformat(),remote=states,scored=n,in_flight=len(pending)))
   print('progress',states,n,len(pending),flush=True)
   all_terminal=all(states.get(m,'').split('+')[0] in TERMINAL for m in ('cl','oss','qwen')) and (B/'sol/generation-terminal.json').exists()
   if not pending and (all_terminal or time.time()>=ADMISSION):break
   time.sleep(20)
if __name__=='__main__':main()
