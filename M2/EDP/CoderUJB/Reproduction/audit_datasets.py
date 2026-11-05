"""Verify local pinned HF snapshots and index task rows without exporting solutions."""
import collections
import hashlib
import json
from pathlib import Path
import pyarrow.parquet as pq
import requests

root = Path('/data/jianyeshi/coderujb-reproduction/datasets')
out = Path(__file__).resolve().parent / 'evidence/dataset-audit'
datasets = [
 ('FCG','code_ucb_complete','78cb042ad6abab321de85fe159f0c65b8aa47d36',238),
 ('CTG','code_ujb_testgen','b77050662a33cf6096c118bfd24d2bc2a8086103',140),
 ('ITG','code_ujb_testgenissue','9d01e6322844ba29a9b26b13e175a5fc0db95e81',451),
 ('APR','code_ujb_repair','99a9d802b33ab1389d0969eab96b5b2737489f08',470),
 ('DD','code_ujb_defectdetection','3cf751c87067c3c3d8cf32155e48c7fe87b6db23',940)]
out.mkdir(exist_ok=True, parents=True)
audit = {}; index = []; pool = {}; seen_families=set()
for task,name,rev,n in datasets:
    p = root / f'{name}-{rev}.parquet'
    upstream = requests.get(f'https://huggingface.co/api/datasets/ZHENGRAN/{name}/revision/{rev}',params={'blobs':'true'},timeout=30)
    upstream.raise_for_status()
    file = next(x for x in upstream.json()['siblings'] if x['rfilename']=='data/train-00000-of-00001.parquet')
    digest=hashlib.sha256(p.read_bytes()).hexdigest()
    assert digest == file['lfs']['sha256'] and p.stat().st_size == file['size']
    cols=['task_id','project','bug_id','prompt_chat','prompt_complete']
    rows=pq.read_table(p,columns=cols+(['defective'] if task=='DD' else [])).to_pylist()
    assert len(rows)==n
    records=[]; families=collections.defaultdict(list)
    for i,row in enumerate(rows):
        rec={'task':task,'revision':rev,'task_idx':i,**{k:row[k] for k in cols[:3]}}
        for mode in ('chat','complete'):
            prompt=row['prompt_'+mode].strip()
            assert prompt
            rec[mode+'_sha256']=hashlib.sha256(prompt.encode()).hexdigest()
        records.append(rec); families[row['project'],str(row['bug_id'])].append(i)
        if task=='FCG' and i<8:seen_families.add((row['project'],str(row['bug_id'])))
    item={'repo':'ZHENGRAN/'+name,'revision':rev,'file_sha256':digest,'verified_lfs':True,'n':n,'projects':len({r['project'] for r in rows}),'families':len(families),'unique_task_ids':len({r['task_id'] for r in rows})}
    if task=='DD':
        assert len(families)==470 and all(sorted(rows[i]['defective'] for i in g)==[False,True] for g in families.values())
        for key in ('task_id','chat_sha256','complete_sha256'):
            groups=collections.defaultdict(list)
            for r in records:groups[r[key]].append(r['task_idx'])
            item[key+'_collisions']=[{'indices':g,'mixed_labels':len({rows[i]['defective'] for i in g})>1} for g in groups.values() if len(g)>1]
    audit[task]=item; index.extend(records)
    units=list(families.values()) if task=='DD' else [[i] for i in range(n)]
    pool[task]=[(records[g[0]]['project'],str(records[g[0]]['bug_id']),g) for g in units]
def rank(task, value):
    return hashlib.sha256(f'20261105/{task}/{value}'.encode()).hexdigest()
subset=[]
for task,units in pool.items():
    byproject=collections.defaultdict(list)
    for proj,bug,g in units:
        if (proj,bug) not in seen_families: byproject[proj].append(g)
    for gs in byproject.values():gs.sort(key=lambda g:rank(task,g))
    projects=sorted(byproject,key=lambda proj:rank(task,proj))
    selected=[]
    while len(selected)<20:
        for proj in projects:
            if byproject[proj] and len(selected)<20:selected.extend(byproject[proj].pop(0))
    subset.extend(r for r in index if r['task']==task and r['task_idx'] in selected)
assert len(index)==2239 and len(subset)==100
for name,obj in [('audit',audit),('row-index',index),('heatmap-100',subset)]:
    (out/(name+'.json')).write_text(json.dumps(obj,indent=2)+'\n')
print({k:(v['n'],v['unique_task_ids']) for k,v in audit.items()})
