"""Run one unmodified official chat prompt per listed row against the job's local server."""
import hashlib
import json
import os
from pathlib import Path
import sys
import time
import urllib.request

root = Path(__file__).resolve().parent
base = 'http://127.0.0.1:' + os.environ['PORT']
for _ in range(150):
    try:
        with urllib.request.urlopen(base+'/health',timeout=2):
            break
    except OSError:
        os.kill(int(sys.argv[1]),0)
        time.sleep(2)
else:
    raise RuntimeError('model startup timed out')


def post(endpoint, data):
    req = urllib.request.Request(base+endpoint, data=json.dumps(data).encode(),
                                 headers={'Content-Type':'application/json'})
    with urllib.request.urlopen(req,timeout=600) as res:
        return json.load(res)


for row in json.loads((root/'prompts.json').read_text()):
    name = row['task'] + '-' + str(row['task_idx'])
    prompt = row['prompt']
    assert hashlib.sha256(prompt.encode()).hexdigest() == row['chat_sha256']
    out = root/name
    out.mkdir(exist_ok=False)
    request = dict(messages=[{'role':'system','content':'Reasoning: medium'},
                             {'role':'user','content':prompt}],
                   seed=4, temperature=0.2, max_tokens=2048, stream=False)
    (out/'request.json').write_text(json.dumps(request,indent=2)+'\n')
    template = post('/apply-template', {'messages':request['messages']})
    (out/'template.json').write_text(json.dumps(template)+'\n')
    r = post('/v1/chat/completions',request)
    choice = r['choices'][0]
    final = choice['message'].get('content') or ''
    (out/'final.txt').write_text(final)
    record = dict(job_id=os.environ['SLURM_JOB_ID'], node=os.uname()[1], prompt_sha256=row['chat_sha256'],
                  finish_reason=choice['finish_reason'], final_sha256=hashlib.sha256(final.encode()).hexdigest(),
                  usage=r['usage'], timings=r['timings'])
    (out/'generation.json').write_text(json.dumps(record,indent=2)+'\n')
    print(name,record,flush=True)
