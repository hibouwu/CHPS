"""Exercise the pinned upstream DD evaluator using labelled synthetic controls."""
import ast
import hashlib
import json
import re
from pathlib import Path
from types import SimpleNamespace
base=Path(__file__).resolve().parent
source=base/'ujb/code_ujb/tasks/code_ujb_defectdetection.py'
module=ast.parse(source.read_text())
cls=next(n for n in module.body if isinstance(n,ast.ClassDef) and n.name=='CodeUJBDefectDetection')
methods=[x for x in cls.body if getattr(x,'name','') in ('evaluate','_stop_at_function','postprocess_chat_generation')]
for x in methods:x.decorator_list=[]
ns={'re':re,'tqdm':lambda it,**kw:it}
exec(compile(ast.Module(body=methods,type_ignores=[]),str(source),'exec'),ns)
report={'synthetic_only':True,'official_sha256':hashlib.sha256(source.read_bytes()).hexdigest(),'cases':{}}
def check(name,rows):
    labels=[{'defective':label} for label,_ in rows]
    task=SimpleNamespace(get_dataset=lambda:labels,_stop_at_function=ns['_stop_at_function'])
    data=[{'task_idx':i,'outputs':[ns['postprocess_chat_generation'](task,answer,i)]} for i,(_,answer) in enumerate(rows)]
    try:
        out=ns['evaluate'](task,data)['results_one']
    except ZeroDivisionError:
        out={'official_error':'ZeroDivisionError'}
    report['cases'][name]={'inputs':rows,'result':out}
    return out
r=check('mixed',[(True,'Yes'),(False,'No'),(True,'No'),(False,'Uncertain')])
assert (r['correct'],r['error'],r['fn'],r['acc'],r['acc_w_error'])==(2,1,1,2/3,.5)
for name,rows in [('no_predicted_positives',[(True,'No'),(False,'No')]),('all_unparseable',[(True,'Uncertain'),(False,'Uncertain')])]:
    assert check(name,rows)=={'official_error':'ZeroDivisionError'}
p=base/'evidence/dataset-audit/dd-controls.json';p.write_text(json.dumps(report,indent=2)+'\n')
