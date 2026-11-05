"""Diagnose literal leading DD labels without changing official classification."""
import json
import re
from score_qwen_a100 import A,FROZEN,name
from score_candidate import row_at,dd_metrics,save

cases=[]
for r in FROZEN:
    if r['task']!='DD':continue
    k=name(r);scorefile=A/'scores'/(k+'.json')
    if not scorefile.is_file():continue
    score=json.loads(scorefile.read_text())
    raw=(A/'rows'/k/'final.txt').read_text().strip()
    first=raw.splitlines()[0] if raw else ''
    # Diagnostic requires a plain, explicit leading option. Leave prose or markup ambiguous.
    choice=re.match(r'^\s*([AB])[.)]\s*(Yes|No)\b',first,re.I)
    label=row_at('DD',r['task_idx'])['defective']
    cat='error'
    if choice and ((choice[1].upper()=='A')==(choice[2].lower()=='yes')):
        positive=choice[1].upper()=='A'
        cat=('tp' if label else 'fp') if positive else ('fn' if label else 'tn')
    cases.append(dict(key=k,first_line=first[:220],first_category=cat,official_category=score['category'],label=label))
save(A/'dd-first-choice.json',dict(diagnostic_only=True,unambiguous=sum(x['first_category']!='error' for x in cases),
    disagreements_on_unambiguous=sum(x['first_category']!='error' and x['first_category']!=x['official_category'] for x in cases),
    first_choice=dd_metrics([x['first_category'] for x in cases]),official=dd_metrics([x['official_category'] for x in cases]),rows=cases))
