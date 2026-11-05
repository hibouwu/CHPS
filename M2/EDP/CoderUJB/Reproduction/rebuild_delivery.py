"""Offline reconstruction from 800 saved formal answers and command logs; never calls a model or reruns Java."""
from collections import Counter
from decimal import Decimal
from functools import lru_cache
from pathlib import Path
from types import SimpleNamespace
import argparse,json,re,xml.etree.ElementTree as ET
import javalang
from score_candidate import BASE,sha,save,row_at as load_row,official as load_official
from heatmap_a100 import FROZEN,name,caller_compile_error
from score_cl13_a100 import review_compile_diagnostic
from score_qwen_a100 import review_signature
from report_qwen_a100 import compare
from prepare_b100 import prefix
OUT=BASE/'evidence/final-review'
MODELS={'cl':'cl13-a100','qwen':'qwen-a100','oss':'oss120-a100','sol':'sol-a100'}
TASKS=('FCG','CTG','ITG','APR','DD')
row_at=lru_cache(None)(load_row);official=lru_cache(None)(load_official)
def read(p):return json.loads(p.read_text())
def txt(p):return p.read_bytes().decode()

def coverage(path):
 stdout=txt(path/'coverage.stdout.log')
 total=int(re.search(r'Lines total:\s*(\d+)',stdout)[1]);hit=int(re.search(r'Lines covered:\s*(\d+)',stdout)[1]);pct=float(re.search(r'Line coverage:\s*([\d.]+)%',stdout)[1])
 classes=txt(path/'instrument-classes.txt').splitlines();root=ET.parse(path/'coverage.xml').getroot()
 direct=sum(int(x.get('hits','0'))>0 for c in root.findall('.//class') if c.get('name') in classes for x in c.findall('./lines/line'))
 all_hits=sum(int(x.get('hits','0'))>0 for c in root.findall('.//class') for x in c.findall('./lines/line'))
 assert hit==all_hits and total>=hit and abs(pct-(100*hit/total if total else 0))<.051
 return dict(line_pct=pct,total_lines=total,covered_lines=hit,direct_hits=direct,xml_hits=all_hits,classes=classes,hit_classes={c.get('name'):sum(int(x.get('hits','0'))>0 for x in c.findall('./lines/line')) for c in root.findall('.//class') if any(int(x.get('hits','0')) for x in c.findall('./lines/line'))})

def replay_status(r,patch,p,rec):
 task=r['task'];row=row_at(task,r['task_idx']);cov=None;trace_evidence=[]
 if task=='DD':
  pred,_=official(task)['check_defect'](patch);assert pred in ('defect','nodefect','error')
  cat='error' if pred=='error' else ('tp' if row['defective'] else 'fp') if pred=='defect' else ('fn' if row['defective'] else 'tn')
  return ('pass' if cat in ('tp','tn') else 'fail'),dict(category=cat,defective=row['defective'],parser_prediction=pred)
 if patch.startswith('Can not find target function in answer!'):return 'fail',dict(reason='official extraction missing target function')
 if rec.get('reason')=='candidate_syntax':
  # Recheck the exact injected source; this is parsing only, not a new test run.
  failed=False
  for suffix in (['_fixed','_buggy'] if task=='ITG' else ['']):
   src=row['source'+suffix].split('\n');candidate='\n'.join(src[:row['start'+suffix]]+patch.split('\n')+src[row['end'+suffix]+1:])
   try:javalang.parse.parse(candidate)
   except (javalang.parser.JavaSyntaxError,javalang.tokenizer.LexerError):failed=True;break
  assert failed
  return 'fail',dict(reason='candidate_syntax',syntax_replayed=True)
 tested={};seen_compile=set()
 for c in rec['commands']:
  stdout=txt(p.parent/c['stdout']);stderr=txt(p.parent/c['stderr']);step=c['name']
  if c['timeout']:return 'timeout_unresolved',dict(reason=step)
  if c['exit_code']:
   if step.endswith('compile'):
    suffix=('_buggy' if step.startswith('buggy') else '_fixed') if task=='ITG' else ''
    if re.search(r'\[javac\].*'+re.escape(Path(row['location'+suffix]).name)+r':\d+: error:',stderr+stdout):return 'fail',dict(reason='candidate_compile',exit_code=c['exit_code'])
    review=caller_compile_error(task,r['task_idx'],p) or review_compile_diagnostic(r,p) or review_signature(r,p)
    if review:return 'fail',dict(reason=review.get('reason','candidate_compile_breaks_caller'),review=review)
   return 'infrastructure_unresolved',dict(reason=step,exit_code=c['exit_code'])
  if step.endswith('compile'):seen_compile.add(step)
  if '-test-' in step or step=='suite':
   m=re.search(r'^Failing tests:\s*(\d+)\s*$',stdout,re.M);f=p.parent/(step+'.failing_tests.txt')
   if m is None or not f.exists():return 'infrastructure_unresolved',dict(reason='missing test verdict')
   failures=re.findall(r'^--- (.+)$',txt(f),re.M);assert int(m[1])==len(failures)
   case=c['argv'][c['argv'].index('-t')+1] if '-t' in c['argv'] else None
   assert rec['tests'][step]==dict(selected=case,failed=failures)
   tested[step]=dict(selected=case,failures=failures,log=str(f.relative_to(BASE)))
   if step.startswith('buggy'):
    assert task=='ITG'
    if not failures:return 'fail',dict(reason='test did not detect buggy version',tests=tested)
    if failures!=[case]:return 'infrastructure_unresolved',dict(reason='unexpected failing method',tests=tested)
    frame=re.search(r'^\s*at '+re.escape(case.replace('::','.'))+r'\(([^:]+):(\d+)\)',txt(f),re.M)
    if not frame:return 'infrastructure_unresolved',dict(reason='missing target frame')
    line=int(frame[2]);lo=row['start_buggy']+1;hi=row['start_buggy']+len(patch.split('\n'))
    assert lo<=line<=hi,(name(r),line,lo,hi)
    trace_evidence.append(dict(test=case,file=frame[1],line=line,inserted_range=[lo,hi],candidate_line=patch.split('\n')[line-lo].strip(),error=txt(f).splitlines()[1]))
   elif failures:
    if step!='suite' and case not in failures:return 'infrastructure_unresolved',dict(reason='unexpected failing test',tests=tested)
    return 'fail',dict(reason='project suite failed' if step=='suite' else 'target test failed',tests=tested)
  if step=='coverage':
   if 'WARNING: Some tests failed' in stderr:return 'infrastructure_unresolved',dict(reason='coverage test failure')
   cov=coverage(p.parent)
   expected=row['classes_modified'] if task=='ITG' else sorted({x['be_test_class_name'] for x in row['classmethods']})
   assert set(cov['classes'])==set(expected)
 assert 'fixed-compile' in seen_compile and tested
 if task in ('FCG','APR'):
  assert 'suite' in tested
  assert {v['selected'] for k,v in tested.items() if k!='suite'}=={t.strip() for t in row['testmethods']}
 else:
  assert cov is not None
  if task=='CTG':assert tested['fixed-test-0']['selected']==row['testmethods'][0].strip()
  if task=='ITG':assert 'buggy-compile' in seen_compile and trace_evidence and tested['fixed-test-0']['selected']==row['testmethod'].strip()
  if cov['line_pct']==0 or cov['xml_hits']==0:return 'fail',dict(reason='zero aggregate coverage',coverage=cov,tests=tested)
 return 'pass',dict(coverage=cov,tests=tested,itg_failure_in_inserted_test=trace_evidence)

def api_cost():
 groups={};ids=[];count=0
 rates={'input':Decimal('2'),'cached':Decimal('.1'),'write':Decimal('2.5'),'output':Decimal('10')}
 source=BASE/'evidence/sol-a100/sources/model.md';price=txt(source)
 assert '| Input | $2 |' in price and '| Output | $10 |' in price and '| Cache writes | $2.5 |' in price
 for label,root in [('A_formal',BASE/'evidence/sol-a100/rows'),('A_pilots',BASE/'evidence/sol-a100/pilot'),('B_formal',BASE/'evidence/b100/sol/rows')]:
  total=Decimal(0);upper=Decimal(0);c=Counter()
  for d in sorted(root.iterdir()):
   if not d.is_dir():continue
   response=read(d/'response.json');g=read(d/'generation.json');disp=read(d/'dispatch.json')
   assert response['model']=='gpt-6.1-sol' and response['service_tier']=='default' and response['status']=='completed' and not response['background']
   assert sha((d/'response.json').read_bytes())==g['response_sha256']
   u=response['usage'];i=u['input_tokens'];o=u['output_tokens'];cached=u['input_tokens_details'].get('cached_tokens',0);writes=u['input_tokens_details'].get('cache_write_tokens',0)
   assert cached+writes<=i and o<=4096 and u['output_tokens_details']['reasoning_tokens']<=o
   total+=(Decimal(i-cached-writes)*rates['input']+Decimal(cached)*rates['cached']+Decimal(writes)*rates['write']+Decimal(o)*rates['output'])/Decimal(1000000)
   upper+=(Decimal(i)*rates['write']+Decimal(o)*rates['output'])*Decimal('1.1')/Decimal(1000000)
   c.update(requests=1,input=i,output=o,cached=cached,cache_write=writes,reasoning=u['output_tokens_details']['reasoning_tokens']);ids.append(response['id']);count+=1
  groups[label]=dict(c,usd=str(total),conservative_usd=str(upper))
 assert count==len(set(ids))==205 and groups['A_formal']['requests']==groups['B_formal']['requests']==100 and groups['A_pilots']['requests']==5
 point=sum(Decimal(g['usd']) for g in groups.values());upper=sum(Decimal(g['conservative_usd']) for g in groups.values());ledger=read(BASE/'evidence/dataset-audit/窗口预算.json')
 assert abs(float(point)-ledger['incurred_estimate'])<1e-8 and abs(float(upper)-ledger['incurred_conservative_upper'])<1e-8 and ledger['reserved_maximum']==0
 return dict(groups=groups,usd=str(point),conservative_usd=str(upper),model_requests=205,formal_requests=200,pilot_requests=5,pending_unknown_requests=0,source=str(source.relative_to(BASE)),source_sha256=sha(source.read_bytes()),rates_per_million={k:str(v) for k,v in rates.items()},invoice_read=False)

def main():
 OUT.mkdir(exist_ok=True);rescore=read(OUT/'rescore.json');records=[];changes=[];syntax_errors=[]
 for model,adir in MODELS.items():
  for column in ('A','B'):
   root=BASE/'evidence'/adir if column=='A' else BASE/'evidence/b100'/model
   for r in FROZEN:
    k=name(r);sf=root/'scores'/(k+'.json');s=read(sf)
    dest=next((root/'batches').glob('*/'+k)) if model=='oss' and column=='A' else root/'rows'/k
    g=read(dest/'generation.json');raw=txt(dest/('full-decoded.txt' if model=='cl' else 'final.txt'))
    h=g['raw_sha256'] if model=='cl' else g['final_sha256'] if model=='oss' else g['answer_sha256'];assert sha(raw.encode())==h
    normalized=raw
    if model=='cl' and column=='B':assert raw.startswith(prefix(r['task'],'cl'));normalized=raw[len(prefix(r['task'],'cl')):]
    mode='complete' if model=='cl' else 'chat';row=row_at(r['task'],r['task_idx']);ns=official(r['task']);obj=SimpleNamespace(dataset={'train':{r['task_idx']:row}},_stop_at_function=ns['_stop_at_function'])
    patch=ns['postprocess_'+mode+'_generation'](obj,normalized,r['task_idx'])
    p=BASE/s['result'];rec=read(p);assert rec['raw_sha256']==sha(normalized.encode()) and patch==txt(p.parent/'candidate.txt')
    status,details=replay_status(r,patch,p,rec)
    entry=dict(model=model,column=column,**r,status_v1=s['status'],status=status,reason_v1=s.get('reason'),details=details,raw_source=str(dest.relative_to(BASE)),raw_sha256=h,score_input_sha256=rec['raw_sha256'],candidate_sha256=sha(patch.encode()),v1_score=str(sf.relative_to(BASE)),v1_result=s['result'],result=s['result'])
    if status!=s['status']:
     assert (model,column,r['task'],r['task_idx'])==('cl','B','CTG',48)
     assert s['result']==rescore['old_result'] and rescore['new']['status']==status=='pass' and rescore['old']['raw_sha256']==rescore['new']['raw_sha256']
     entry['result']=rescore['new_result'];entry['revision_note']='v2 aggregate coverage includes inner classes; empty-test caveat applies';changes.append(entry)
    records.append(entry)
 assert len(records)==800 and len({(x['model'],x['column'],name(x)) for x in records})==800 and len(changes)==1
 stats={};paired={}
 for model in MODELS:
  stats[model]={};paired[model]={}
  for task in TASKS:
   stats[model][task]={}
   for col in ('A','B'):
    rs=[r for r in records if (r['model'],r['task'],r['column'])==(model,task,col)];assert len(rs)==20
    stats[model][task][col]=dict(Counter(r['status'] for r in rs))
   rows=[]
   for f in FROZEN:
    if f['task']!=task:continue
    pair=dict(project=f['project'])
    for c in ('A','B'):pair[c]={'status':next(x['status'] for x in records if x['model']==model and x['column']==c and name(x)==name(f))}
    rows.append(pair)
   paired[model][task]=compare(rows,'B','A')
 cost=api_cost();unknown=[r for r in records if r['status'] not in ('pass','fail')];counts=Counter(r['status'] for r in records)
 assert len(unknown)==2 and sum(p['known'] for m in paired.values() for p in m.values())==398
 summary=dict(version='reviewed-v2',formal_answers=800,determinate_answers=798,unknown_answers=2,potential_AB_pairs=400,determinate_AB_pairs=398,counts=dict(counts),stats=stats,paired=paired,changes=changes,unknown=unknown,cost=cost,rows=records,official_commit='e7b69a0b4f79d0d1896046079f6926d955f31452',rebuild_script_sha256=sha(Path(__file__).read_bytes()))
 save(OUT/'recomputed.json',summary)
 print('rebuilt',dict(counts),'changes',len(changes),'ITG passing stacks checked',sum(r['task']=='ITG' and r['status']=='pass' for r in records),'USD',cost['usd'])
if __name__=='__main__':main()
