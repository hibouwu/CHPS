"""Rebuild fixed-denominator multi-candidate metrics from saved candidate verdicts."""
from pathlib import Path
from math import comb
from collections import Counter
import json,os,xml.etree.ElementTree as ET
RUN=Path(os.environ.get('CODERUJB_RUN',str(Path(__file__).resolve().parents[1]/'evidence/cl13-full20-20261105')))
SCORE_ROOT=RUN/'remote-primary'
def read(p):return json.loads(p.read_text())
def passk(n,c,k):return 1.0 if n-c<k else 1-comb(n-c,k)/comb(n,k)
def coverage(results):
 universe=set();hit=set();legacy=set();files=set()
 for r in results:
  if not r.get('result'):continue
  p=SCORE_ROOT/r['result'];s=read(p)
  # Match the task's successful-test gate before taking coverage; failed ITG tests do not contribute.
  if s['task']=='ITG' and not s.get('tests',{}).get('buggy-test-0',{}).get('failed'):continue
  xml=p.parent/'coverage.xml'
  if not xml.exists() or str(xml) in files:continue
  files.add(str(xml))
  for c in ET.parse(xml).findall('.//class'):
   for line in c.findall('./lines/line'):
    key=(c.get('name'),c.get('filename'),line.get('number'));h=int(line.get('hits','0'))>0
    universe.add(key);legacy.add((*key,h))
    if h:hit.add(key)
 return dict(covered_lines=len(hit),tested_lines=len(universe),union=len(hit)/len(universe) if universe else 0,
             legacy_tuple_union=sum(x[-1] for x in legacy)/len(legacy) if legacy else 0)
def main():
 manifest=read(RUN/'manifest.json');out={};perrow=[]
 for row in manifest:
  rs=[read(p) for p in sorted((SCORE_ROOT/'scores'/row['key']).glob('candidate-*.json'))]
  assert len({r['candidate_index'] for r in rs})==len(rs)
  n=row['candidates'];c=sum(r['status']=='pass' for r in rs);f=sum(r['status']=='fail' for r in rs);u=n-c-f
  item=dict(key=row['key'],task=row['task'],task_idx=row['task_idx'],planned=n,scored=len(rs),pass_count=c,fail_count=f,unknown=u,
      pass1_bounds=[c/n,(c+u)/n],pass10_bounds=[passk(n,c,10),passk(n,c+u,10)],count_bounds=[int(c>0),int(c+u>0)],statuses=dict(Counter(r['status'] for r in rs)))
  if row['task'] in ('CTG','ITG'):item['coverage']=coverage(rs)
  if row['task']=='DD':item['dd_categories']=[r.get('category') for r in rs];item['dd_first_category']=next((r.get('category') for r in rs if r['candidate_index']==0),None)
  perrow.append(item)
 for task in ('FCG','CTG','ITG','APR','DD'):
  rows=[r for r in perrow if r['task']==task];m=len(rows)
  a=dict(questions=m,planned=sum(r['planned'] for r in rows),scored=sum(r['scored'] for r in rows),
   passes=sum(r['pass_count'] for r in rows),failures=sum(r['fail_count'] for r in rows),unknown=sum(r['unknown'] for r in rows),
   pass_all_at_1_bounds=[sum(r['pass1_bounds'][i] for r in rows)/m for i in (0,1)],
   pass_all_at_10_bounds=[sum(r['pass10_bounds'][i] for r in rows)/m for i in (0,1)],
   count_all_at_n_bounds=[sum(r['count_bounds'][i] for r in rows) for i in (0,1)])
  if task in ('CTG','ITG'):
   a['coverage_union_at_20_lower']=sum(r['coverage']['union'] for r in rows)/m
   a['coverage_legacy_tuple_union_observed']=sum(r['coverage']['legacy_tuple_union'] for r in rows)/m
   a['coverage_complete']=not a['unknown']
  if task=='DD':
   for key in ('pass_all_at_1_bounds','pass_all_at_10_bounds','count_all_at_n_bounds'):a.pop(key)
   def dd(cats,planned):
    cc=Counter(cats);known=sum(cc[k] for k in ('tp','tn','fp','fn','error'));valid=known-cc['error'];correct=cc['tp']+cc['tn']
    return dict(counts=dict(cc),planned=planned,known=known,unknown=planned-known,acc_valid=correct/valid if valid else None,acc_all_observed=correct/known if known else None,acc_all_planned_bounds=[correct/planned,(correct+planned-known)/planned])
   a['all_candidates']=dd([x for r in rows for x in r['dd_categories'] if x is not None],a['planned'])
   a['first_candidate']=dd([r['dd_first_category'] for r in rows if r['dd_first_category'] is not None],m)
  out[task]=a
 result=dict(version='full20-paper-recipe-v1',planned_questions=2239,planned_candidates=35380,
   scored_candidates=sum(x['scored'] for x in out.values()),determinate_candidates=sum(x['passes']+x['failures'] for x in out.values()),tasks=out,rows=perrow,
   note='Bounds encode unresolved/missing outcomes, not statistical confidence intervals. Coverage union follows paper definition; legacy tuple union additionally reproduces published code behavior. Pilot/control answers excluded.')
 p=RUN/'summary.json';t=p.with_suffix('.tmp');t.write_text(json.dumps(result,indent=2)+'\n');t.replace(p)
 print('scored',result['scored_candidates'],'determinate',result['determinate_candidates'],'of 35380')
 for task,s in out.items():print(task,s['scored'],s['passes'],s['unknown'],s.get('pass_all_at_1_bounds',s.get('all_candidates',{}).get('acc_all_planned_bounds')))
if __name__=='__main__':main()
