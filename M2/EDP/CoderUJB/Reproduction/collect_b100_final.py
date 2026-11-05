"""After owned jobs terminate, copy and byte-verify their final evidence; no new jobs."""
import subprocess,json,hashlib,datetime
from pathlib import Path
B=Path(__file__).resolve().parent/'evidence/b100'
TERMINAL={'COMPLETED','FAILED','TIMEOUT','CANCELLED','NODE_FAIL','OUT_OF_MEMORY','PREEMPTED','BOOT_FAIL','DEADLINE'}
results=json.loads((B/'remote-integrity.json').read_text())['models'] if (B/'remote-integrity.json').exists() else {}
for model in (__import__('sys').argv[1:] or ['cl','oss','qwen']):
 d=B/model;remote=(d/'remote.txt').read_text().strip();job=(d/'slurm-id.txt').read_text().strip()
 assert job.isdigit() and remote.startswith('/scratch_p/hibouwu/coderujb/') and remote.split('/')[-1].startswith(model+'-b100-')
 state=subprocess.check_output(['ssh','-o','BatchMode=yes','romeo','sacct','-Xj',job,'-nPo','State'],text=True).strip().splitlines()[0].split('|')[0].split()[0]
 assert state.split('+')[0] in TERMINAL,(model,state)
 subprocess.run(['rsync','-aq','--exclude=*.tmp','romeo:'+remote+'/',str(d)+'/'],check=True)
 manifest=subprocess.check_output(['ssh','-o','BatchMode=yes','romeo',f'cd {remote} && find . -type f -print0 | sort -z | xargs -0 sha256sum'],text=True)
 (d/'remote-sha256-final.txt').write_text(manifest)
 n=0
 for line in manifest.splitlines():
  h,file=line.split('  ',1);assert hashlib.sha256((d/file).read_bytes()).hexdigest()==h,(model,file);n+=1
 account=subprocess.check_output(['ssh','-o','BatchMode=yes','romeo','sacct','-j',job,'-P','-o','JobID,State,ExitCode,Elapsed,AllocTRES,MaxRSS'],text=True);(d/'terminal-accounting.txt').write_text(account)
 results[model]=dict(job=job,state=state,files_verified=n,remote=remote,accounting=str((d/'terminal-accounting.txt').relative_to(B)))
(B/'remote-integrity.json').write_text(json.dumps(dict(time=datetime.datetime.now(datetime.timezone.utc).isoformat(),models=results),indent=2)+'\n')
print(results)
