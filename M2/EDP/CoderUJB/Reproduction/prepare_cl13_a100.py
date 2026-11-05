import json,sys,re,hashlib,xml.etree.ElementTree as ET
from datetime import datetime
from pathlib import Path
from heatmap_a100 import A, FROZEN, name
from score_candidate import BASE, sha, save, row_at, D4J
out=BASE/'evidence/cl13-a100'
report=json.loads((A/'report.json').read_text())
audit=json.loads((A/'input-audit.json').read_text())
assert audit['completed']==audit['unique_dispatched']==len({name(r) for r in FROZEN})==100
refs=[]
for r in FROZEN:
 k=name(r); p=json.loads((A/'preflight'/(k+'.json')).read_text())
 assert p['eligible'] and p['task_id']==r['task_id']
 if r['task']=='DD':
  refs.append(dict(key=k,check='boolean label and official DD controls'));continue
 f=BASE/p['log']; rec=json.loads(f.read_text()); assert rec['status']=='pass'
 for c in rec['commands']:
  assert not c['timeout'] and c['exit_code']==0
  assert (f.parent/c['stderr']).is_file() and (f.parent/c['stdout']).is_file()
 tests=rec['tests']; assert tests
 for label,test in tests.items():
  failures=(f.parent/(label+'.failing_tests.txt')).read_text()
  junit=(f.parent/(label+'.stdout.log')).read_text()
  if label.startswith('buggy'):
   assert r['task']=='ITG' and test['failed']==[test['selected']] and 'Failing tests: 1' in junit
   assert test['selected'] in failures and test['selected'].replace('::','.')+'(' in failures
  else:
   assert test['failed']==[] and 'Failing tests: 0' in junit and not failures.strip()
 if r['task'] in ('FCG','APR'):assert 'suite' in tests
 if r['task'] in ('CTG','ITG'):
  cov=rec['coverage']; xml=ET.parse(f.parent/'coverage.xml')
  hit=sum(int(n.get('hits'))>0 for c in xml.findall('.//class') if c.get('name') in cov['classes'] for n in c.findall('./lines/line'))
  assert hit==cov['instrumented_lines_hit']>0 and cov['line_pct']>0
 if r['task']=='ITG':assert 'fixed-test-0' in tests and 'buggy-test-0' in tests
 refs.append(dict(key=k,reference_result=p['log'],command_count=len(rec['commands']),tests=list(tests)))
assert len(report['projects'])==17
save(out/'prior-review.json',dict(official_commit='e7b69a0b4f79d0d1896046079f6926d955f31452',
  verified_rows=len(refs),java=80,dd=20,projects=17,prior_controls=refs,prior_model_inputs_audited=100))
protocol=dict(name='cl13-A-completion-256-v1',frozen_at=datetime.now().astimezone().isoformat(),
 model='codellama/CodeLlama-13b-hf',revision='8da65ff4ee20f74ecd107ca9d54f9f121b279860',
 selection_sha256=sha((BASE/'evidence/dataset-audit/heatmap-100.json').read_bytes()),
 source_commit='e7b69a0b4f79d0d1896046079f6926d955f31452',
 official_generator_sha256=sha((BASE/'ujb/code_ujb/generate_hf.py').read_bytes()),
 recipe='scripts/run_code_ujb.sh local_gen and generate_hf.py get_answers',input='prompt_complete.strip()',mode='complete',
 model_dtype='bfloat16',attention='eager',input_tokens=4096,truncation='keep rightmost 4096 ids (official completion mode)',
 max_new_tokens=256,temperature=0.2,seed='torch.manual_seed(task_idx) separately for each row',
 candidates=1,num_return_sequences=1,batch_size=1,do_sample=True,
 postprocessing='Decode the full actually used input + generated token sequence with skip_special_tokens=True as official generate_hf does. Feed raw full decoded text unchanged to the pinned mode-specific official extractor.',
 on_limit='Record input truncation and output stopping independently; grade the one extracted candidate even at length cap.',
 recovery='Dispatch marker exclusive per revision/task/task_idx, completed rows reused; ambiguous in-flight generations are unresolved and never repeated.',
 comparison='Same frozen 100 rows, scoring and project environments. Prompt mode, weights/precision, reasoning strategy, seed rule, inference implementation, and generation budget differ. This is a paired observed system comparison.',
 uncertainty='Per-task paired binary outcomes; two-sided exact McNemar conditional on discordant pairs shown descriptively; project-cluster paired percentile bootstrap 10000 draws seed 20261105, keep DD partners together; 20/task, no correction or population claim.',
 paid_api_usd=0)
if (out/'protocol.json').exists():
    prior=json.loads((out/'protocol.json').read_text())
    protocol['frozen_at']=prior['frozen_at']
    assert prior==protocol, 'protocol is frozen'
else:
    save(out/'protocol.json',protocol)
inputs=[]
for r in FROZEN:
 row=row_at(r['task'],r['task_idx'])
 prompt=row['prompt_complete'].strip()
 assert sha(prompt.encode())==r['complete_sha256']
 inputs.append(dict(task=r['task'],task_idx=r['task_idx'],revision=r['revision'],prompt_sha256=r['complete_sha256'],prompt=prompt))
save(out/'inputs.json',inputs)
print(len(inputs),sha((out/'protocol.json').read_bytes()))
