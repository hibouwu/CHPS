"""Prepare and score the frozen A subset. Model receives only exported input.json files.

Use PYTHONPATH for the existing Java parser, as in score_candidate.py.
"""
import argparse
from concurrent.futures import ThreadPoolExecutor
from datetime import datetime
import hashlib
import json
import time
import re
import javalang
from pathlib import Path

from score_candidate import AUDIT, BASE, evaluate, row_at, save, sha

A = BASE / 'evidence/oss120-a100'
HEATMAP = BASE / 'evidence/dataset-audit/heatmap-100.json'
PROTOCOL = json.loads((A/'protocol.json').read_text())
assert sha(HEATMAP.read_bytes()) == PROTOCOL['selection_sha256']
FROZEN = json.loads(HEATMAP.read_text())
assert len(FROZEN) == len({(r['task'],r['revision'],r['task_idx']) for r in FROZEN}) == 100


def name(r):
    return f"{r['task']}-{r['task_idx']}-{r['revision']}"


def preflight(r, retry=False):
    idx = r['task_idx']
    origin = 'reference_preflight'
    row = row_at(r['task'],idx)
    assert AUDIT[r['task']]['revision'] == r['revision'] and row['task_id'] == r['task_id']
    assert sha(row['prompt_chat'].strip().encode()) == r['chat_sha256']
    rec = dict(r, checked_at=datetime.now().astimezone().isoformat())
    if r['task'] == 'DD':
        assert type(row['defective']) is bool
        rec.update(eligible=True, check='label_available_parser_controlled')
    else:
        patch = row['fix'] if r['task']=='APR' else row['function']
        result = evaluate(r['task'],idx,patch,'extracted',origin,retry)
        verdict = json.loads(result.read_text())
        rec.update(eligible=verdict['status']=='pass', check='dataset_reference_in_project',
                   reference_status=verdict['status'], reason=verdict.get('reason'), log=str(result.relative_to(BASE)))
    (A/'preflight').mkdir(exist_ok=True)
    save(A/'preflight'/(name(r)+'.json'),rec)
    print(name(r),rec['eligible'],rec.get('reason'),flush=True)
    return rec


def export(batch, limit):
    batch_dir=A/'batches'/batch
    batch_dir.mkdir(parents=True,exist_ok=False)
    scheduled=set()
    for act in (A/'batches').glob('*/inputs.json'):
        scheduled.update(name(r) for r in json.loads(act.read_text()))
    inputs=[]
    for r in FROZEN:
        checked=A/'preflight'/(name(r)+'.json')
        if name(r) in scheduled or not checked.is_file() or not json.loads(checked.read_text())['eligible']:
            continue
        # Never serialize a row, reference verdict, label or project checkout to the backend.
        prompt=row_at(r['task'],r['task_idx'])['prompt_chat'].strip()
        assert sha(prompt.encode())==r['chat_sha256']
        inputs.append({**{k:r[k] for k in ('task','task_idx','revision','chat_sha256')},'prompt':prompt})
        if len(inputs)==limit:break
    if not inputs: raise ValueError('no new eligible rows')
    save(batch_dir/'inputs.json',inputs)
    print(len(inputs))


def caller_compile_error(task, idx, result):
    """Recognize a newly declared checked exception breaking an existing caller."""
    meta=json.loads(result.read_text())
    if meta.get('reason') != 'fixed-compile' or meta['status'] != 'infrastructure_unresolved':
        return None
    row=row_at(task,idx)
    reference=row.get('function') or row.get('fix')
    if not reference:return None
    def signature(method):
        unit=javalang.parse.parse('class Probe {\n'+method+'\n}')
        return unit.types[0].methods[0]
    try:
        original=signature(reference)
        generated=signature((result.parent/'candidate.txt').read_text())
    except (IndexError,javalang.parser.JavaSyntaxError,javalang.tokenizer.LexerError):
        return None
    if original.name != generated.name:return None
    additions={x.split('.')[-1] for x in (generated.throws or [])} - {x.split('.')[-1] for x in (original.throws or [])}
    stderr=(result.parent/'fixed-compile.stderr.log').read_text(errors='replace')
    for exc in additions:
        diagnostic=r'unreported exception (?:[\w.]+\.)?'+re.escape(exc)+r'; must be caught or declared to be thrown'
        found=re.search(diagnostic+r'[^\n]*\n[^\n]*\b'+re.escape(original.name)+r'\s*\(',stderr)
        if found:
            return dict(method=original.name,added_checked_exception=exc,diagnostic=found.group(),
                        raw_status=meta['status'],raw_reason=meta['reason'])
    return None


def score_batch(batch):
    directory=A/'batches'/batch
    rows=json.loads((directory/'inputs.json').read_text())
    def one(r):
        out=directory/name(r)
        if not (out/'generation.json').is_file():
            return
        gen=json.loads((out/'generation.json').read_text())
        raw=(out/'final.txt').read_text()
        assert sha(raw.encode())==gen['final_sha256'] and gen['prompt_sha256']==r['chat_sha256']
        req=json.loads((out/'request.json').read_text())
        assert req['messages']==[{'role':'system','content':PROTOCOL['system']},{'role':'user','content':r['prompt']}]
        assert req['temperature']==PROTOCOL['temperature'] and req['max_tokens']==PROTOCOL['max_tokens']
        if r['task'] != 'DD':
            # Three reference checks can already be building large projects.
            # Let them finish before running another JVM on this workstation.
            while len(list((A/'preflight').glob('*.json'))) < len(FROZEN):
                if datetime.now().astimezone().strftime('%H%M') >= '0700':
                    return
                time.sleep(20)
        path=evaluate(r['task'],r['task_idx'],raw,'chat','model')
        state=json.loads(path.read_text())
        record=dict(task=r['task'],revision=r['revision'],task_idx=r['task_idx'],batch=batch,status=state['status'],
                    reason=state.get('reason'), finish_reason=gen['finish_reason'],truncated=gen['finish_reason']=='length',
                    category=state.get('category'), coverage=state.get('coverage'), result=str(path.relative_to(BASE)),
                    usage=gen['usage'],final_sha256=gen['final_sha256'])
        review=caller_compile_error(r['task'],r['task_idx'],path)
        if review:
            reference=json.loads((A/'preflight'/(name(r)+'.json')).read_text())
            assert reference['reference_status']=='pass'
            record.update(status='fail',reason='candidate_compile_breaks_caller',compile_review=review,
                          reference_log=reference['log'])
        (A/'scores').mkdir(exist_ok=True)
        save(A/'scores'/(name(r)+'.json'),record)
        print(name(r),record['status'],record['reason'],flush=True)
    with ThreadPoolExecutor(max_workers=2) as ex:list(ex.map(one,rows))


if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('action',choices=['preflight','export','score'])
    parser.add_argument('--batch')
    parser.add_argument('--limit',type=int,default=30)
    parser.add_argument('--filter',help='Task or project exact name; default all rows')
    parser.add_argument('--retry',action='store_true')
    parser.add_argument('--workers',type=int,default=2)
    args=parser.parse_args()
    if args.action=='preflight':
        subset=[r for r in FROZEN if not args.filter or args.filter in (r['project'],r['task'])]
        # Previously checked rows are durable; retry only explicitly unresolved cases.
        def check(r):
            f=A/'preflight'/(name(r)+'.json')
            if f.is_file() and (json.loads(f.read_text())['eligible'] or not args.retry):return
            preflight(r,args.retry)
        with ThreadPoolExecutor(max_workers=args.workers) as pool:list(pool.map(check,subset))
    elif args.action=='export':
        export(args.batch,args.limit)
    else:
        score_batch(args.batch)
