"""Verify the exact rendered prompts, row-key uniqueness and artifacts on all finished jobs."""
import json
from collections import Counter
from pathlib import Path
from heatmap_a100 import A, PROTOCOL, FROZEN, name
from score_candidate import sha, save

index={name(r):r for r in FROZEN}
seen=set()
job_ids=[]
records=[]
for folder in sorted((A/'batches').iterdir()):
    inputs=folder/'inputs.json'
    if not inputs.is_file(): continue
    if not (folder/'verification.log').exists(): continue
    hashes=(folder/'remote-sha256.txt').read_text().splitlines()
    for line in hashes:
        digest,path=line.split('  ',1)
        assert sha((folder/path).read_bytes())==digest
    assert (A/'protocol.json').read_bytes()==(folder/'protocol.json').read_bytes()
    job=(folder/'slurm-id.txt').read_text().strip()
    assert job not in job_ids
    job_ids.append(job)
    for r in json.loads(inputs.read_text()):
        assert set(r)=={'task','task_idx','revision','chat_sha256','prompt'}
        key=name(r)
        assert key not in seen and key in index
        seen.add(key)
        fixed=index[key]
        assert sha(r['prompt'].encode())==fixed['chat_sha256']==r['chat_sha256']
        assert json.loads((A/'preflight'/(key+'.json')).read_text())['eligible']
        out=folder/key
        req=json.loads((out/'request.json').read_text())
        expected=dict(messages=[{'role':'system','content':PROTOCOL['system']},{'role':'user','content':r['prompt']}],
                      seed=PROTOCOL['seed'],temperature=PROTOCOL['temperature'],max_tokens=PROTOCOL['max_tokens'],
                      n=1,stream=False)
        assert req==expected
        template=json.loads((out/'template.json').read_text())['prompt']
        user_tag='<|start|>user<|message|>'
        assert template.count(user_tag)==1
        assert template.split(user_tag)[1].split('<|end|>')[0]==r['prompt']
        dispatch=json.loads((out/'dispatch.json').read_text())
        assert dispatch['protocol_sha256']==sha((A/'protocol.json').read_bytes())
        result_file=out/'generation.json'
        if result_file.is_file():
            g=json.loads(result_file.read_text())
            assert g['job_id']==job and g['final_sha256']==sha((out/'final.txt').read_bytes())
            assert g['prompt_sha256']==fixed['chat_sha256']
            record=dict(key=key,job=job,complete=True,usage=g['usage'],finish_reason=g['finish_reason'])
        else:
            record=dict(key=key,job=job,complete=False)
        records.append(record)
save(A/'input-audit.json',dict(protocol_sha256=sha((A/'protocol.json').read_bytes()),unique_dispatched=len(seen),
     completed=sum(r['complete'] for r in records),jobs=job_ids,
     all_inputs_match_frozen_chat_hash=True,only_fixed_system_and_official_user_message=True,
     output_by_row=records))
print('verified unique requests:',len(seen))
