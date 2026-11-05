"""Compare the released whole-text DD parser to the explicit first choice; never replace the score."""
import json
import re
from heatmap_a100 import FROZEN, name, A as OSS
from score_cl13_a100 import A
from score_candidate import row_at, save, dd_metrics

cases=[]
for r in FROZEN:
    if r['task']!='DD':continue
    k=name(r); label=row_at('DD',r['task_idx'])['defective']
    rec=dict(key=k,defective=label)
    for m,p,text in [('cl',A,A/'rows'/k/'continuation.txt'),('oss',OSS,next((OSS/'batches').glob('*/'+k+'/final.txt')))]:
        score=json.loads((p/'scores'/(k+'.json')).read_text())
        line=text.read_text().strip().splitlines()[0]
        match=re.fullmatch(r"([AB])\.\s+(Yes|No),.*",line)
        assert match and (match[1]=='A')==(match[2]=='Yes')
        first=match[1]=='A'
        category=('tp' if label else 'fp') if first else ('fn' if label else 'tn')
        rec[m]=dict(first_line=line,first_class=category,released_class=score['category'],
                    changed=category!=score['category'],source=str(text.relative_to(p)))
    cases.append(rec)
report={}
for m in ('cl','oss'):
    report[m]=dict(released=dd_metrics([r[m]['released_class'] for r in cases]),
                   first_choice=dd_metrics([r[m]['first_class'] for r in cases]),disagreements=sum(r[m]['changed'] for r in cases))
save(A/'dd-first-choice.json',dict(purpose='Post-run scorer diagnostic only. Formal paired scores are unchanged.',systems=report,rows=cases))
