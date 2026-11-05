"""Freeze Qwen's BF16 protocol and export only the official user text."""
import json
from datetime import datetime
from heatmap_a100 import FROZEN, HEATMAP, name
from score_candidate import BASE, row_at, sha, save
A=BASE/'evidence/qwen-a100'
weights=json.loads((A/'weights.json').read_text())
protocol=dict(name='qwen25-coder-32b-instruct-A-chat-bf16-4096-v1',frozen_at=datetime.now().astimezone().isoformat(),
 repo=weights['repo'],revision=weights['revision'],weights_manifest_sha256=sha((A/'weights.json').read_bytes()),
 sample_sha256=sha(HEATMAP.read_bytes()),mode='chat',precision='bfloat16',backend='Transformers 4.53.3 / torch 2.7.1+cu128 / SDPA',
 system='You are Qwen, created by Alibaba Cloud. You are a helpful assistant.',template='snapshot apply_chat_template(add_generation_prompt=True); no tools',
 input='prompt_chat.strip() unchanged; retain full template. Max rendered input 8192 ids; overlength row unresolved without truncation.',
 max_input_tokens=8192,max_new_tokens=4096,temperature=0.2,top_p=0.8,top_k=20,repetition_penalty=1.05,
 seed=4,seed_rule='torch.manual_seed(4) reset at each fixed microbatch, with fixed row order and left padding',
 group_size=4,order='original heatmap-100 order; contiguous groups of four',n_candidates=1,
 decoder='first official end token or model length limit; score continuation only with original chat function extractor',
 comparison='Qwen 4096 new answer tokens; GPT-OSS 4096 tokens shared by reasoning and answer; CodeLlama 256 new tokens after completion prefix.',
 cost_estimate='At 40-90 ms per batch decode step, 25 microbatches of 500-1000 steps typically 8-38 minutes plus staging. At 4096 steps each, 68-154 minutes total; stop admitting groups before each allocation ends, resume only untouched groups. No paid API.',
 gate='Prior to formal dispatch: separate public FCG-4 pilot, actual extraction and project scoring by local evaluator; terminal model failure counts as a tested pipeline, an infrastructure failure blocks admission.',
 no_resampling=True,deadline='2026-11-05T07:22:00+01:00',paid_api_usd=0)
f=A/'protocol.json'
if f.exists():
 existing=json.loads(f.read_text());protocol['frozen_at']=existing['frozen_at'];assert protocol==existing
else:save(f,protocol)
def export(task,idx,rev):
 row=row_at(task,idx);prompt=row['prompt_chat'].strip()
 return dict(task=task,task_idx=idx,revision=rev,prompt_sha256=sha(prompt.encode()),prompt=prompt)
inputs=[export(r['task'],r['task_idx'],r['revision']) for r in FROZEN]
assert all(x['prompt_sha256']==r['chat_sha256'] for x,r in zip(inputs,FROZEN,strict=True))
assert len(inputs)==len({name(r) for r in inputs})==100
save(A/'inputs.json',inputs)
pilot=export('FCG',4,next(r['revision'] for r in FROZEN if r['task']=='FCG'))
assert name(pilot) not in {name(r) for r in FROZEN}
save(A/'pilot-input.json',pilot)
