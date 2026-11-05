"""Score immutable CodeLlama outputs with the pinned complete-mode extractor and Java/DD evaluator."""
from concurrent.futures import ThreadPoolExecutor
import json
import re
import javalang
from pathlib import Path
from heatmap_a100 import BASE, A as PRIOR, FROZEN, name, caller_compile_error
from score_candidate import evaluate, sha, save, row_at, official

A=BASE/'evidence/cl13-a100'
protocol=json.loads((A/'protocol.json').read_text())
inputs={name(r):r for r in json.loads((A/'inputs.json').read_text())}
assert len(inputs)==len(FROZEN)==100


def review_compile_diagnostic(r,score_path):
    """Tie a javac diagnostic to the submitted line or a missing method with a passing reference."""
    raw=json.loads(score_path.read_text())
    if raw.get('reason')!='fixed-compile' or raw['status']!='infrastructure_unresolved':return None
    row=row_at(r['task'],r['task_idx'])
    suffix='_fixed' if r['task']=='ITG' else ''
    submitted=(score_path.parent/'candidate.txt').read_text()
    candidate=submitted.strip()
    stderr=(score_path.parent/'fixed-compile.stderr.log').read_text(errors='replace')
    ref=json.loads((PRIOR/'preflight'/(name(r)+'.json')).read_text())
    assert ref['reference_status']=='pass'
    start=row['start'+suffix]+1
    for d in re.finditer(re.escape('/'+row['location'+suffix])+r':(\d+): error: ([^\n]+)\n[^\n]*?\] (.*)',stderr):
        pos=int(d[1])-start
        lines=submitted.split('\n')
        if 0<=pos<len(lines) and lines[pos].strip() and lines[pos].strip()==d[3].strip():
            return dict(reason='candidate_compile',original_status=raw['status'],diagnostic=d[0],
                        injected_line=int(d[1]),reference_log=ref['log'])
    only_comment=candidate.startswith('/*') and '*/' not in candidate
    if candidate and not only_comment:return None
    original=(BASE/ref['log']).parent/'candidate.txt'
    unit=javalang.parse.parse('class Probe {\n'+original.read_text()+'\n}')
    method=unit.types[0].methods[0].name
    stderr=(score_path.parent/'fixed-compile.stderr.log').read_text(errors='replace')
    diag=re.search(r'error: cannot find symbol\n(?:[^\n]*\n){1,4}[^\n]*symbol:\s+method '+re.escape(method)+r'\([^\n]*',stderr)
    if not diag:
        diag=re.search(r'error: method does not override or implement a method from a supertype\n[^\n]*\b'+re.escape(method)+r'\s*\([^\n]*',stderr)
    if not diag:
        diag=re.search(r'error: no suitable method found for '+re.escape(method)+r'\([^\n]*',stderr)
    if not diag:
        diag=re.search(r'error: [^\n]*does not override abstract method '+re.escape(method)+r'\([^\n]*',stderr)
    if not diag:return None
    return dict(method=method,reason='official_extraction_missing_method',original_status=raw['status'],
                diagnostic=diag.group(),submitted_bytes=len(candidate.encode()),only_unterminated_comment=only_comment,
                reference_log=ref['log'])


def score(r,retry=False):
    k=name(r)
    out=A/'rows'/k
    if not (out/'generation.json').is_file():return
    cached=A/'scores'/(k+'.json')
    if cached.exists() and not retry:return
    gen=json.loads((out/'generation.json').read_text())
    dispatch=json.loads((out/'dispatch.json').read_text())
    inp=inputs[k]
    assert dispatch['seed']==r['task_idx'] and dispatch['key']==k and dispatch['protocol_sha256']==sha((A/'protocol.json').read_bytes())
    assert inp['prompt_sha256']==r['complete_sha256']==dispatch['input_sha256']==sha(inp['prompt'].encode())
    assert len(dispatch['input_ids'])==dispatch['input_tokens_used']==min(protocol['input_tokens'],dispatch['input_tokens_full'])
    assert gen['output_tokens']==len(gen['output_ids'])<=protocol['max_new_tokens']
    raw=(out/'full-decoded.txt').read_bytes().decode()
    assert sha(raw.encode())==gen['raw_sha256']
    path=evaluate(r['task'],r['task_idx'],raw,'complete','model',retry=retry)
    result=json.loads(path.read_text())
    review=caller_compile_error(r['task'],r['task_idx'],path)
    record=dict(task=r['task'],revision=r['revision'],task_idx=r['task_idx'],project=r['project'],bug_id=r['bug_id'],
                status=result['status'],reason=result.get('reason'),category=result.get('category'),coverage=result.get('coverage'),
                reference_log=json.loads((PRIOR/'preflight'/(k+'.json')).read_text()).get('log'),
                raw_sha256=gen['raw_sha256'],input_sha256=inp['prompt_sha256'],input_tokens=dispatch['input_tokens_used'],
                full_input_tokens=dispatch['input_tokens_full'],input_truncated=dispatch['input_truncated'],
                finish_reason=gen['finish_reason'],output_tokens=gen['output_tokens'],output_truncated=gen['finish_reason']=='length',
                result=str(path.relative_to(BASE)),source=str(out.relative_to(BASE)))
    if review:record.update(status='fail',reason='candidate_compile_breaks_caller',compile_review=review)
    missing=review_compile_diagnostic(r,path)
    if missing:record.update(status='fail',reason=missing['reason'],compile_review=missing)
    if record['category']=='error':record['reason']='DD answer unparseable'
    save(cached,record)
    print(k,record['status'],record['reason'],flush=True)


if __name__=='__main__':
    import argparse
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--retry-unresolved',action='store_true')
    p.add_argument('--review-only',action='store_true',help='Inspect existing diagnostics only; no new generation or tests')
    args=p.parse_args()
    (A/'scores').mkdir(exist_ok=True)
    def one(r):
        path=A/'scores'/(name(r)+'.json')
        if args.review_only:
            if path.is_file():
                snapshot=json.loads(path.read_text())
                missing=review_compile_diagnostic(r,BASE/snapshot['result'])
                if missing:
                    snapshot.update(status='fail',reason=missing['reason'],compile_review=missing)
                    save(path,snapshot)
            return
        retry=args.retry_unresolved and path.is_file() and json.loads(path.read_text())['status'].endswith('unresolved')
        score(r,retry)
    with ThreadPoolExecutor(max_workers=2) as pool:list(pool.map(one,FROZEN))
