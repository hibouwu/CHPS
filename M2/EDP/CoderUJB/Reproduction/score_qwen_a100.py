"""Validate a Qwen submission and run the same isolated scorer used by the two comparisons."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import json
import re
import javalang
from heatmap_a100 import FROZEN, name, caller_compile_error, A as PRIOR
from score_candidate import BASE, evaluate, sha, save, row_at
from score_cl13_a100 import review_compile_diagnostic

A=BASE/'evidence/qwen-a100'
cfg=json.loads((A/'protocol.json').read_text())
formal_inputs={name(r):r for r in json.loads((A/'inputs.json').read_text())}

def review_signature(r,path):
    result=json.loads(path.read_text())
    if result.get('reason')!='fixed-compile' or result['status']!='infrastructure_unresolved':return None
    row=row_at(r['task'],r['task_idx'])
    ref=row.get('function') or row.get('fix')
    if not ref:return None
    def parse(text):
        return javalang.parse.parse('class Probe {\n'+text+'\n}').types[0].methods[0]
    try:
        old=parse(ref);new=parse((path.parent/'candidate.txt').read_text())
    except (IndexError,javalang.parser.JavaSyntaxError,javalang.tokenizer.LexerError):return None
    if old.name!=new.name or len(old.parameters)==len(new.parameters):return None
    baseline=json.loads((PRIOR/'preflight'/(name(r)+'.json')).read_text())
    assert baseline['reference_status']=='pass'
    stderr=(path.parent/'fixed-compile.stderr.log').read_text(errors='replace')
    diag=re.search(r'error: method '+re.escape(old.name)+r' [^\n]*cannot be applied to given types;\n(?:[^\n]*\n){0,6}',stderr)
    if not diag:return None
    return dict(reason='candidate_signature_breaks_caller',diagnostic=diag[0],reference_arity=len(old.parameters),
                generated_arity=len(new.parameters),reference_log=baseline['log'],original_status=result['status'])


def score(r,pilot=False,retry=False):
    k=name(r)
    dest=A/('pilot' if pilot else 'rows')/k
    output=(A/'pilot-score.json') if pilot else (A/'scores'/(k+'.json'))
    if output.exists() and not retry:return
    if not (dest/'generation.json').is_file():return
    disp=json.loads((dest/'dispatch.json').read_text()); gen=json.loads((dest/'generation.json').read_text())
    raw=(dest/'final.txt').read_bytes().decode()
    assert gen['answer_sha256']==sha(raw.encode()) and disp['key']==k and disp['protocol_sha256']==sha((A/'protocol.json').read_bytes())
    inp=r if pilot else formal_inputs[k]
    assert inp['prompt_sha256']==disp['prompt_sha256']==sha(inp['prompt'].encode()) and (pilot or disp['prompt_sha256']==r['chat_sha256'])
    expected='<|im_start|>system\n'+cfg['system']+'<|im_end|>\n<|im_start|>user\n'+inp['prompt']+'<|im_end|>\n<|im_start|>assistant\n'
    assert (dest/'template.txt').read_bytes().decode()==expected
    path=evaluate(r['task'],r['task_idx'],raw,'chat','model',retry=retry)
    rec=json.loads(path.read_text())
    before_review=rec['status']
    review=None if pilot else caller_compile_error(r['task'],r['task_idx'],path) or review_compile_diagnostic(r,path) or review_signature(r,path)
    final=dict(task=r['task'],revision=r['revision'],task_idx=r['task_idx'],status=before_review,
               reason=rec.get('reason'),category=rec.get('category'),coverage=rec.get('coverage'),group=disp['group'],
               job=disp['job'],answer_sha256=gen['answer_sha256'],source=str(dest.relative_to(BASE)),
               result=str(path.relative_to(BASE)),finish_reason=gen['finish_reason'],output_truncated=gen['finish_reason']=='length',
               input_tokens=disp['input_tokens'],output_tokens=gen['output_tokens'])
    if review:final.update(status='fail',reason=review.get('reason','candidate_compile_breaks_caller'),compile_review=review)
    if rec.get('category')=='error':final['reason']='DD answer unparseable'
    output.parent.mkdir(exist_ok=True);save(output,final)
    print(k,final['status'],final['reason'],flush=True)

if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--pilot',action='store_true')
    parser.add_argument('--retry',action='store_true')
    parser.add_argument('--review-only',action='store_true')
    args=parser.parse_args()
    if args.pilot:
        score(json.loads((A/'pilot-input.json').read_text()),True,args.retry)
    else:
        def one(r):
            cached=A/'scores'/(name(r)+'.json')
            if args.review_only:
                if cached.is_file():
                    data=json.loads(cached.read_text())
                    review=review_signature(r,BASE/data['result'])
                    if review:
                        data.update(status='fail',reason=review['reason'],compile_review=review)
                        save(cached,data)
                return
            retry=args.retry and cached.is_file() and json.loads(cached.read_text())['status'].endswith('unresolved')
            score(r,retry=retry)
        with ThreadPoolExecutor(max_workers=2) as pool:list(pool.map(one,FROZEN))
