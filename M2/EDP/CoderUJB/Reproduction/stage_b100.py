"""Copy pinned A runtime recipes into isolated B directories; only change input and admission gates."""
from pathlib import Path
import json,shutil
BASE=Path(__file__).resolve().parent;B=BASE/'evidence/b100'
for model,source in [('cl','cl13-a100'),('qwen','qwen-a100')]:
 a=BASE/'evidence'/source;d=B/model
 for f in ['weights.json','job.sh']+(['stage_weights.py'] if model=='qwen' else []):shutil.copyfile(a/f,d/f)
 s=(a/'generate.py').read_text()
 if model=='cl':
  s=s.replace('import time\n','import time\nfrom datetime import datetime\n')
  s=s.replace('for row in rows:\n',"for row in rows:\n    if time.time()+120>=datetime.fromisoformat(cfg['b_generation_cutoff']).timestamp():\n        print('B admission cutoff',flush=True);break\n")
 else:
  start=s.index("pilot=json.loads((root/'pilot-input.json').read_text())")
  end=s.index("job_end=int",start)
  s=s[:start]+"rows=json.loads((root/'inputs.json').read_text())\nassert len(rows)==len({key(r) for r in rows})==100\n"+s[end:]
  s=s.replace("absolute_end=datetime.fromisoformat(protocol['deadline']).timestamp()", "absolute_end=datetime.fromisoformat(protocol['b_generation_cutoff']).timestamp()")
 (d/'generate.py').write_text(s)
a=BASE/'evidence/oss120-a100';d=B/'oss'
for f in ['job.sh']:shutil.copyfile(a/f,d/f)
for f in ['stage.py','manifest.json']:shutil.copyfile(BASE/'evidence/oss120-task-pilot'/f,d/f)
s=(a/'infer.py').read_text();s=s.replace("for row in json.loads((root/'inputs.json').read_text()):", "for row in json.loads((root/'inputs.json').read_text()):\n    if time.time()+360>=datetime.fromisoformat(protocol['b_generation_cutoff']).timestamp():\n        print('B admission cutoff',flush=True);break")
s=s.replace("{'task','task_idx','revision','chat_sha256','prompt'}","{'task','task_idx','revision','prompt_sha256','prompt'}").replace("row['chat_sha256']","row['prompt_sha256']")
s=s.replace("out=root/name", "out=root/'rows'/name").replace('out.mkdir(exist_ok=True)','out.mkdir(exist_ok=True,parents=True)')
# Retain the raw completion response too, beyond A's summary-only receipt.
s=s.replace("choice=resp['choices'][0]", "store(out/'response.json',resp)\n        choice=resp['choices'][0]")
(d/'infer.py').write_text(s)
print('isolated B runtime files staged')
