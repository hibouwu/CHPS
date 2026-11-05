"""Run the protocol on given eligible prompts inside one ROMEO batch."""
import hashlib
import json
import os
from pathlib import Path
import sys
import time
import urllib.request
from datetime import datetime, timezone

root = Path.cwd()
protocol = json.loads((root/'protocol.json').read_text())
protocol_hash = hashlib.sha256((root/'protocol.json').read_bytes()).hexdigest()
base = 'http://127.0.0.1:' + os.environ['PORT']


def store(path, data):
    tmp=path.with_suffix('.tmp')
    tmp.write_text(json.dumps(data,ensure_ascii=False,indent=2)+'\n')
    tmp.replace(path)


def post(endpoint, data, timeout):
    req=urllib.request.Request(base+endpoint,data=json.dumps(data).encode(),headers={'Content-Type':'application/json'})
    with urllib.request.urlopen(req,timeout=timeout) as response:
        return json.load(response)


for _ in range(150):
    try:
        with urllib.request.urlopen(base+'/health',timeout=2):
            break
    except OSError:
        os.kill(int(sys.argv[1]),0)
        time.sleep(2)
else:
    raise RuntimeError('model startup timed out')
for row in json.loads((root/'inputs.json').read_text()):
    assert set(row) == {'task','task_idx','revision','chat_sha256','prompt'}
    prompt=row['prompt']
    assert hashlib.sha256(prompt.encode()).hexdigest()==row['chat_sha256']
    name=f"{row['task']}-{row['task_idx']}-{row['revision']}"
    out=root/name
    out.mkdir(exist_ok=True)
    if (out/'dispatch.json').exists() or (out/'generation.json').exists():
        continue
    request=dict(messages=[{'role':'system','content':protocol['system']},{'role':'user','content':prompt}],
                 seed=protocol['seed'],temperature=protocol['temperature'],max_tokens=protocol['max_tokens'],
                 n=1,stream=False)
    store(out/'request.json',request)
    try:
        rendered=post('/apply-template',{'messages':request['messages']},30)
        assert prompt in rendered['prompt'] and rendered['prompt'].count('<|start|>user<|message|>')==1
        store(out/'template.json',rendered)
        tokens=post('/tokenize',{'content':rendered['prompt'],'add_special':False,'parse_special':True},30)['tokens']
        if len(tokens)+protocol['max_tokens']>protocol['context_window']:
            raise ValueError('input and output reservation exceed fixed context')
        # Exclusive marker is durable even if the HTTP response is lost. Never resample a dispatched row.
        with (out/'dispatch.json').open('x') as f:
            json.dump(dict(job=os.environ['SLURM_JOB_ID'],time=datetime.now(timezone.utc).isoformat(),
                           protocol_sha256=protocol_hash,template_tokens=len(tokens)),f)
            f.flush()
            os.fsync(f.fileno())
        resp=post('/v1/chat/completions',request,360)
        choice=resp['choices'][0]
        final=choice['message'].get('content') or ''
        (out/'final.txt').write_text(final)
        store(out/'generation.json',dict(job_id=os.environ['SLURM_JOB_ID'],node=os.uname()[1],protocol_sha256=protocol_hash,
              prompt_sha256=row['chat_sha256'],final_sha256=hashlib.sha256(final.encode()).hexdigest(),
              finish_reason=choice['finish_reason'],usage=resp['usage'],timings=resp.get('timings')))
        print(name,choice['finish_reason'],resp['usage'],flush=True)
    except (OSError,ValueError,KeyError,AssertionError) as exc:
        store(out/'unresolved.json',dict(reason=repr(exc),dispatched=(out/'dispatch.json').exists()))
        print(name,'unresolved',repr(exc),flush=True)
