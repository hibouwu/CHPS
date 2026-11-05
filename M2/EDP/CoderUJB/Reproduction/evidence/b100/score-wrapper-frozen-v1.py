"""Evaluate B outputs with the unchanged A official scorer, no retries or answer repair."""
import json,re
from pathlib import Path
import javalang
from prepare_b100 import B,MODELS,prefix
from score_candidate import BASE,sha,save,evaluate
from heatmap_a100 import name,caller_compile_error
from score_cl13_a100 import review_compile_diagnostic
from score_qwen_a100 import review_signature

def read(p):return json.loads(p.read_text())
def format_valid(task,path,record):
 if task=='DD':return record.get('category') in ('tp','tn','fp','fn')
 p=path.parent/'candidate.txt'
 if not p.exists():return None
 candidate=p.read_text()
 if candidate.startswith('Can not find target function in answer!'):return False
 try:
  parsed=javalang.parse.parse('class FormatProbe {\n'+candidate+'\n}').types[0]
  return len(parsed.methods)==1
 except (javalang.parser.JavaSyntaxError,javalang.tokenizer.LexerError,IndexError):return False

def score(model,r):
 d=B/model;k=name(r);dest=d/'rows'/k;out=d/'scores'/(k+'.json')
 if out.exists() or not (dest/'generation.json').exists():return
 g=read(dest/'generation.json');dispatch=read(dest/'dispatch.json');cfg=read(d/'protocol.json')
 assert dispatch['protocol_sha256']==sha((d/'protocol.json').read_bytes())
 inp=next(x for x in read(d/'inputs.json') if name(x)==k)
 assert sha(inp['prompt'].encode())==inp['prompt_sha256']
 raw=(dest/('full-decoded.txt' if model=='cl' else 'final.txt')).read_text()
 rawhash=g['raw_sha256'] if model=='cl' else g['final_sha256'] if model=='oss' else g['answer_sha256']
 assert sha(raw.encode())==rawhash
 if model=='cl':
  assert not dispatch['input_truncated'] and raw.startswith(prefix(r['task'],model))
  scored_raw=raw[len(prefix(r['task'],model)):];mode='complete'
  added_removed=prefix(r['task'],model)
 else:scored_raw=raw;mode='chat';added_removed=''
 (dest/'scorer-input.txt').write_text(scored_raw)
 path=evaluate(r['task'],r['task_idx'],scored_raw,mode,'model',retry=False);rec=read(path)
 review=caller_compile_error(r['task'],r['task_idx'],path) or review_compile_diagnostic(r,path) or review_signature(r,path)
 status=rec['status'];reason=rec.get('reason')
 if review:status='fail';reason=review.get('reason','candidate_compile_breaks_caller')
 s=dict(model=model,configuration='B',task=r['task'],task_idx=r['task_idx'],revision=r['revision'],status=status,reason=reason,category=rec.get('category'),coverage=rec.get('coverage'),format_valid=format_valid(r['task'],path,rec),mode=mode,raw_model_sha256=rawhash,scorer_input_sha256=sha(scored_raw.encode()),removed_input_prefix=added_removed,added_prompt_sha256=sha(prefix(r['task'],model).encode()),answer_untouched=True,source=str(dest.relative_to(BASE)),result=str(path.relative_to(BASE)),finish_reason=g.get('finish_reason',g.get('status')),input_truncated=dispatch.get('input_truncated',False),input_tokens=dispatch.get('input_tokens_used',dispatch.get('input_tokens',dispatch.get('template_tokens'))),output_tokens=g.get('output_tokens',g.get('usage',{}).get('output_tokens',g.get('usage',{}).get('completion_tokens'))),compile_review=review)
 save(out,s);print(model,k,status,reason,flush=True)
