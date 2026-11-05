import urllib.request, json, os, sys,time
from pathlib import Path
base='http://127.0.0.1:'+os.environ['PORT']; started=time.monotonic()
for _ in range(300):
 try:
  with urllib.request.urlopen(base+'/health',timeout=2) as r: break
 except OSError:
  os.kill(int(sys.argv[1]),0);time.sleep(2)
else: raise RuntimeError('server startup timed out')
prompt=Path('prompt.txt').read_text().strip()
data={'messages':[{'role':'system','content':'Reasoning: medium'},{'role':'user','content':prompt}],'seed':4,'temperature':0.2,'max_tokens':2048,'stream':False}
# Capture the actual chat-template rendering without issuing a second generation.
try:
 req=urllib.request.Request(base+'/apply-template',data=json.dumps({'messages':data['messages']}).encode(),headers={'Content-Type':'application/json'})
 rendered=json.load(urllib.request.urlopen(req,timeout=10))
 Path('rendered-template.json').write_text(json.dumps(rendered,ensure_ascii=False,indent=2)+'\n')
except (OSError,ValueError) as error:
 print('template capture unavailable',type(error).__name__,flush=True)
request=urllib.request.Request(base+'/v1/chat/completions',data=json.dumps(data).encode(),headers={'Content-Type':'application/json'})
r=json.load(urllib.request.urlopen(request,timeout=600));choice=r['choices'][0];final=choice['message']['content']
assert final and final.strip()
Path('final.txt').write_text(final)
Path('generation.json').write_text(json.dumps({'job_id':os.environ['SLURM_JOB_ID'],'node':os.uname()[1],'finish_reason':choice['finish_reason'],'usage':r['usage'],'token_budget':2048,'temperature':0.2,'seed':4,'reasoning':'medium','timings':r.get('timings'),'elapsed_seconds':time.monotonic()-started,'prompt_file':'prompt.txt','final_file':'final.txt'},indent=2)+'\n')
print('final received',r['usage'],flush=True)
