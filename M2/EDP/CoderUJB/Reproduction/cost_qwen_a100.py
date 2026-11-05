import json
from pathlib import Path
from score_qwen_a100 import A,BASE
from score_candidate import save

seconds=0
jobs=(A/'jobs.txt').read_text().splitlines()
runtimes=[]
for job in jobs:
    line=(A/f'slurm-{job}.txt').read_text().splitlines()[1]
    h,m,s=map(int,line.split('|')[3].split(':'))
    seconds+=3600*h+60*m+s
    path=A/f'runtime-{job}.json'
    if path.is_file():runtimes.append(json.loads(path.read_text()))
scores=[json.loads(f.read_text()) for f in (A/'scores').glob('*.json')]
generations=list((A/'rows').glob('*/generation.json'))
results=[(BASE/r['result']).parents[1] for r in scores]
attempts={f for d in results for f in d.glob('attempt-*/result.json')}
save(A/'cost.json',dict(jobs=jobs,slurm_seconds=seconds,allocations='1 GH200, 8 CPUs, 192 GiB requested RAM',paid_api_calls=0,paid_api_spend=0,
 formal_generated=len(generations),formal_scored=len(scores),input_tokens=sum(json.loads((f.parent/'dispatch.json').read_text())['input_tokens'] for f in generations),
 output_tokens=sum(json.loads(f.read_text())['output_tokens'] for f in generations),pilot_output_tokens=json.loads(next((A/'pilot').glob('*/generation.json')).read_text())['output_tokens'],
 peak_cuda_allocated=max((r.get('peak_cuda_allocated_bytes',0) for r in runtimes),default=0),
 peak_cuda_reserved=max((r.get('peak_cuda_reserved_bytes',0) for r in runtimes),default=0),
 scorer_attempts=len(attempts),command_seconds=sum(c['elapsed_seconds'] for f in attempts for c in json.loads(f.read_text())['commands']),
 paid_ledger='../dataset-audit/窗口预算.json'))
