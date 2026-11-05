"""Freeze one output-only constraint per task before any B generation."""
from pathlib import Path
from types import SimpleNamespace
from datetime import datetime,timezone
import json,sys
from score_candidate import BASE,official,sha,save
B=BASE/'evidence/b100'
MODELS={'cl':'cl13-a100','oss':'oss120-a100','qwen':'qwen-a100','sol':'sol-a100'}
RULES={
'FCG':'Output only the requested Java method, continuing any answer prefix already provided, and stop after its closing brace; do not include Markdown, explanations, or other declarations.',
'CTG':'Output only the requested Java test method, continuing any answer prefix already provided, and stop after its closing brace; do not include Markdown, explanations, or other declarations.',
'ITG':'Output only the requested Java test method with the provided signature, continuing any answer prefix already provided, and stop after its closing brace; do not include Markdown, explanations, or other declarations.',
'APR':'Output only the complete corrected Java method with the provided signature and stop after its closing brace; do not include Markdown, explanations, or other declarations.',
'DD':"Output exactly one option, 'A. Yes, it has defects' or 'B. No, it doesn\'t have defects', and then stop; do not include an explanation or another question."
}
def read(p):return json.loads(p.read_text())
def prefix(task,model):return ('// ' if model=='cl' else '')+'Output constraint: '+RULES[task]+'\n\n'
def assemble(task,model,prompt):return prefix(task,model)+prompt

def synthetic():
 out=[]
 for task in RULES:
  ns=official(task)
  sig='public int step(int x)' if task in ('FCG','APR') else 'public void testStep()'
  func=sig+' { return x + 1; }' if task in ('FCG','APR') else sig+' { assertEquals(2, step(1)); }'
  head='// Synthetic example outside the benchmark.\n'
  cp=head if task in ('APR','DD') else head+sig+' {'
  chat='Synthetic task; signature: '+sig
  if task=='DD':cp='Synthetic function: int step(int x) { return x + 1; }\nAnswer:';chat=cp;func='B. No, it doesn\'t have defects'
  row=dict(prompt_complete=cp,prompt_complete_with_comment=head,prompt_complete_without_signature=head,function_signature=sig)
  obj=SimpleNamespace(dataset={'train':{0:row}},_stop_at_function=ns['_stop_at_function'])
  continuation=func if task in ('APR','DD') else func[len(sig+' {'):]
  a_raw=cp+continuation;b_input=assemble(task,'cl',cp);b_raw=b_input+continuation
  normalized=b_raw[len(prefix(task,'cl')):]
  a=ns['postprocess_complete_generation'](obj,a_raw,0);b=ns['postprocess_complete_generation'](obj,normalized,0)
  assert a==b and b.strip()==func
  chat_out=ns['postprocess_chat_generation'](obj,func,0);assert chat_out.strip()==func
  assert b_input.endswith(cp) and assemble(task,'sol',chat).endswith(chat)
  out.append(dict(task=task,completion_prefix_preserved=True,official_completion_extraction_unchanged=True,official_chat_extraction_valid=True,input=b_input,synthetic_output=func,extracted=b))
 return out

def main():
 assert not (B/'freeze.json').exists(),'already frozen; do not change B rules'
 frozen=read(BASE/'evidence/dataset-audit/heatmap-100.json')
 controls=synthetic();save(B/'synthetic-controls.json',controls)
 priors={};prompt_manifest=[]
 sys.path.insert(0,'/data/jianyeshi/coderujb-reproduction/runtime/cl13-tokenizer-check/lib')
 from tokenizers import Tokenizer
 tok=Tokenizer.from_file('/data/jianyeshi/coderujb-reproduction/runtime/cl13-tokenizer-check/tokenizer.json')
 for model,source in MODELS.items():
  prior=BASE/'evidence'/source;d=B/model;d.mkdir(exist_ok=True)
  old=read(prior/'protocol.json');cfg=dict(old);cfg['configuration']='B';cfg['b_rule_sha256']=sha(json.dumps(RULES,sort_keys=True).encode());cfg['a_protocol_sha256']=sha((prior/'protocol.json').read_bytes());cfg['b_added_input']='one fixed task-level constraint prepended; original prompt byte suffix preserved'
  # Keep all decoding/weights/runtime settings; descriptive A fields retained as inherited evidence.
  cfg['b_generation_cutoff']='2026-11-05T07:05:00+01:00';save(d/'protocol.json',cfg)
  prior_inputs=read(prior/'inputs.json') if model!='oss' else read(BASE/'evidence/qwen-a100/inputs.json')
  rows=[]
  for r,a in zip(frozen,prior_inputs,strict=True):
   assert (r['task'],r['task_idx'],r['revision'])==(a['task'],a['task_idx'],a['revision'])
   text=assemble(r['task'],model,a['prompt']);row=dict(task=r['task'],task_idx=r['task_idx'],revision=r['revision'],prompt_sha256=sha(text.encode()),prompt=text)
   entry=dict(model=model,task=r['task'],task_idx=r['task_idx'],revision=r['revision'],a_prompt_sha256=sha(a['prompt'].encode()),b_prompt_sha256=row['prompt_sha256'],added_text=prefix(r['task'],model),added_chars=len(prefix(r['task'],model)),discarded_text='',original_suffix_unchanged=True)
   if model=='cl':
    ids=tok.encode(text).ids;entry.update(a_tokens=len(tok.encode(a['prompt']).ids),b_tokens=len(ids),input_truncated=len(ids)>4096)
    # Protect predeclared removal of the added prefix: all B inputs must fit, otherwise stop before any generation.
    assert len(ids)<=4096
    decoded=tok.decode(ids,skip_special_tokens=True);assert decoded==text
   rows.append(row);prompt_manifest.append(entry)
  save(d/'inputs.json',rows)
  priors[model]=dict(directory=str(prior.relative_to(BASE)),protocol_sha256=sha((prior/'protocol.json').read_bytes()),manifest=read(prior/'sha256.json'),manifest_sha256=sha((prior/'sha256.json').read_bytes()))
 save(B/'prompt-deltas.json',prompt_manifest);save(B/'a-snapshots.json',priors)
 freeze=dict(frozen_at=datetime.now(timezone.utc).isoformat(),configuration='B',rules=RULES,model_order=list(MODELS),row_order='unchanged frozen100 order; Qwen original contiguous groups of four',max_formal_generations=400,frozen_sample_sha256=sha((BASE/'evidence/dataset-audit/heatmap-100.json').read_bytes()),a_results_seen=True,interpretation='exploratory follow-up after observing A; not blind or preregistered causal evidence',facts_or_reference_added=False,synthetic_controls='synthetic-controls.json',scorer_sha256=sha((BASE/'score_candidate.py').read_bytes()),completion_adapter='Remove only the exact prepended constraint from full decoded output before invoking unchanged official completion extractor. Original prompt remains intact; preserve existing A offsets and whitespace. No extraction or scoring repairs.',format_metric='Java format-valid iff official target extraction succeeds and candidate parses as a method; DD valid iff original parser returns defect/non-defect. Report paired pass improvements among both-format-valid separately from gains accompanied by format-validity changes; not causal mediation.',generation_cutoff='2026-11-05T07:05:00+01:00',scoring_admission_cutoff='2026-11-05T07:10:00+01:00',absolute_stop='2026-11-05T07:22:00+01:00',no_retries=True,scope_excluded=['C','D','E','2239-row full run'],prior_unresolved_preserved=['cl FCG-116','qwen APR-410'])
 save(B/'freeze.json',freeze)
 print('frozen',len(prompt_manifest),'prompts; synthetic controls',len(controls),'CL max tokens',max(x['b_tokens'] for x in prompt_manifest if x['model']=='cl'))
if __name__=='__main__':main()
