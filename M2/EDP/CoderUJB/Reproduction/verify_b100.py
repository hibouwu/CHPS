"""Replay actual B inputs and official extraction; audit A preservation and generation settings."""
import json,sys
from pathlib import Path
from types import SimpleNamespace
from collections import Counter
from prepare_b100 import B,MODELS,prefix,assemble
from score_candidate import BASE,sha,save,row_at,official
from heatmap_a100 import FROZEN,name
from score_b100 import read
RUNTIME=Path('/data/jianyeshi/coderujb-reproduction/runtime')
sys.path.insert(0,str(RUNTIME/'cl13-tokenizer-check/lib'))
from tokenizers import Tokenizer

def main():
 freeze=read(B/'freeze.json');impl=read(B/'implementation-freeze.json');amendments=read(B/'implementation-amendments.json');amend=amendments[-1]
 assert freeze['a_results_seen'] and freeze['max_formal_generations']==400
 assert sha((BASE/'score_candidate.py').read_bytes())==freeze['scorer_sha256']
 for p,h in impl['files'].items():
  current=sha((BASE/p).read_bytes())
  if p=='score_b100.py':
   assert h==amendments[0]['before_sha256'] and current==amend['after_sha256'] and sha((B/'score-wrapper-frozen-v1.py').read_bytes())==h
   assert all(x['after_sha256']==y['before_sha256'] for x,y in zip(amendments,amendments[1:]))
  else:assert current==h,p
 priors=read(B/'a-snapshots.json');all_records=[];summaries={};tokens={}
 for model,source in MODELS.items():
  a=BASE/'evidence'/source;d=B/model;cfg=read(d/'protocol.json');old=read(a/'protocol.json')
  assert sha((a/'protocol.json').read_bytes())==cfg['a_protocol_sha256']==priors[model]['protocol_sha256']
  assert sha((a/'sha256.json').read_bytes())==priors[model]['manifest_sha256']
  for p,h in priors[model]['manifest'].items():assert sha((a/p).read_bytes())==h,(model,p)
  for k,v in old.items():
   if k!='configuration':assert cfg[k]==v,(model,k)
  assert cfg['configuration']=='B'
  inputs=read(d/'inputs.json');ainputs=read((BASE/'evidence/qwen-a100/inputs.json') if model=='oss' else a/'inputs.json')
  tok=Tokenizer.from_file(str(RUNTIME/('cl13-tokenizer-check' if model=='cl' else 'qwen-tokenizer-check')/'tokenizer.json')) if model in ('cl','qwen') else None
  if model in ('cl','qwen'):
   weightmeta=read(d/'weights.json');receiptfile=d/'weights-receipt.json' if model=='cl' else next(d.glob('weights-receipt-*.json'))
   receipts=read(receiptfile)
   assert sha((d/'weights.json').read_bytes())==sha((a/'weights.json').read_bytes())
   for f in weightmeta['files']:
    rec=next(x for x in receipts if x['file']==f['rfilename']);assert rec['size']==f['size']
    if f.get('lfs'):assert rec['sha256']==f['lfs']['sha256']
   runtimefile=d/'runtime.json' if model=='cl' else next(d.glob('runtime-*.json'));meta=read(runtimefile)
   assert meta.get('dtype',meta.get('precision'))=='torch.bfloat16'
   a_runtime=read(next(a.glob('runtime*.json')))
   for field in ('torch','transformers','cuda','dtype','precision','parameters','attention','generation_defaults'):
    assert meta.get(field)==a_runtime.get(field),(model,field)
  if model=='oss':
   assert cfg['weights']['sha256'] in (d/'stage.log').read_text()
   assert 'offloaded 37/37 layers to GPU' in (d/'server.log').read_text()
   assert sha((d/'manifest.json').read_bytes())==sha((BASE/'evidence/oss120-task-pilot/manifest.json').read_bytes())
  if model=='qwen':
   for p in (d/'groups').glob('b*.json'):
    g=read(p);i=int(p.stem[1:])*4;assert g['rows']==[name(r) for r in FROZEN[i:i+4]] and g['seed']==4
  modelrows=[]
  for r,inp,ain in zip(FROZEN,inputs,ainputs,strict=True):
   k=name(r);dest=d/'rows'/k
   assert name(inp)==name(ain)==k and inp['prompt']==assemble(r['task'],model,ain['prompt'])
   assert sha(inp['prompt'].encode())==inp['prompt_sha256'] and inp['prompt'].endswith(ain['prompt'])
   if not (dest/'dispatch.json').exists():continue
   dispatch=read(dest/'dispatch.json');assert dispatch['protocol_sha256']==sha((d/'protocol.json').read_bytes())
   if model=='cl':
    ids=tok.encode(inp['prompt']).ids;assert ids==dispatch['input_ids'] and len(ids)==dispatch['input_tokens_full']==dispatch['input_tokens_used']<=4096
    assert not dispatch['input_truncated'];b_n=len(ids);a_n=read(a/'rows'/k/'dispatch.json')['input_tokens_used']
   elif model=='qwen':
    expected='<|im_start|>system\n'+cfg['system']+'<|im_end|>\n<|im_start|>user\n'+inp['prompt']+'<|im_end|>\n<|im_start|>assistant\n'
    assert (dest/'template.txt').read_bytes().decode()==expected
    assert tok.encode(expected,add_special_tokens=False).ids==dispatch['input_ids']
    b_n=dispatch['input_tokens'];assert b_n<=8192;a_n=read(a/'rows'/k/'dispatch.json')['input_tokens']
   elif model=='oss':
    req=read(dest/'request.json');assert req==dict(messages=[dict(role='system',content=cfg['system']),dict(role='user',content=inp['prompt'])],seed=4,temperature=.2,max_tokens=4096,n=1,stream=False)
    template=read(dest/'template.json')['prompt'];tag='<|start|>user<|message|>';assert template.count(tag)==1 and template.split(tag)[1].split('<|end|>')[0]==inp['prompt']
    b_n=dispatch['template_tokens'];a_n=read(next((a/'batches').glob('*/'+k+'/dispatch.json')))['template_tokens']
   else:
    req=read(dest/'request.json');oldreq=read(a/'rows'/k/'request.json');assert {x:y for x,y in req.items() if x!='input'}=={x:y for x,y in oldreq.items() if x!='input'}
    assert req['input']==[dict(role='user',content=inp['prompt'])]
    b_n=dispatch['input_tokens'];a_n=read(a/'rows'/k/'dispatch.json')['input_tokens'];assert b_n==read(d/'counts'/(k+'.json'))['body']['input_tokens']
   tokrec=dict(model=model,key=k,a_input_tokens=a_n,b_input_tokens=b_n,added_input_tokens=b_n-a_n,discarded_input_tokens=0,added_text=prefix(r['task'],model),discarded_text='')
   tokens[model+'-'+k]=tokrec
   if not (dest/'generation.json').exists():modelrows.append(dict(key=k,complete=False));continue
   g=read(dest/'generation.json');raw=(dest/('full-decoded.txt' if model=='cl' else 'final.txt')).read_bytes().decode()
   if model=='cl':
    assert tok.decode(dispatch['input_ids']+g['output_ids'],skip_special_tokens=True)==raw
    assert len(g['output_ids'])==g['output_tokens']<=256
    assert (g['finish_reason']=='eos')==(g['output_ids'][-1]==tok.token_to_id('</s>'))
    assert g['finish_reason']=='eos' or len(g['output_ids'])==256
    assert raw.startswith(prefix(r['task'],model));scorer_raw=raw[len(prefix(r['task'],model)):];mode='complete'
   else:
    mode='chat';scorer_raw=raw
    if model=='qwen':
     assert tok.decode(g['output_ids'],skip_special_tokens=True)==raw and len(g['output_ids'])==g['output_tokens']<=4096
     ends=set(read(RUNTIME/'qwen-tokenizer-check/generation_config.json')['eos_token_id'])
     assert not any(x in ends for x in g['output_ids'][:-1])
     assert (g['finish_reason']=='eos')==(g['output_ids'][-1] in ends)
     assert g['finish_reason']=='eos' or len(g['output_ids'])==4096
    if model=='sol':
     response=read(dest/'response.json');assert g['response_sha256']==sha((dest/'response.json').read_bytes())
     assert response['model']=='gpt-6.1-sol' and response['service_tier']=='default' and response['reasoning']['effort']=='medium'
     assert response['usage']['output_tokens']<=4096 and response['usage']['input_tokens']==b_n
     messages=[x for x in response['output'] if x['type']=='message' and x.get('phase')=='final_answer'];assert raw=='\n'.join(c['text'] for x in messages for c in x['content'] if c['type']=='output_text')
   sfile=d/'scores'/(k+'.json')
   if not sfile.exists():modelrows.append(dict(key=k,complete=True,scored=False));continue
   s=read(sfile);path=BASE/s['result'];result=read(path);assert result['raw_sha256']==sha(scorer_raw.encode())==s['scorer_input_sha256']
   assert (dest/'scorer-input.txt').read_bytes().decode()==scorer_raw
   ns=official(r['task']);row=row_at(r['task'],r['task_idx']);obj=SimpleNamespace(dataset={'train':{r['task_idx']:row}},_stop_at_function=ns['_stop_at_function'])
   patch=ns['postprocess_'+mode+'_generation'](obj,scorer_raw,r['task_idx']);assert patch==(path.parent/'candidate.txt').read_bytes().decode()
   assert result['scorer_sha256']==freeze['scorer_sha256'] and result['mode']==mode
   if s['status']!=result['status']:assert s['compile_review'] and s['status']=='fail'
   modelrows.append(dict(key=k,complete=True,scored=True,status=s['status'],finish_reason=s['finish_reason'],candidate_sha256=sha(patch.encode()),result=s['result'],input_tokens=b_n,output_tokens=s['output_tokens']))
  summaries[model]=dict(dispatched=len(modelrows),generated=sum(x['complete'] for x in modelrows),scored=sum(x.get('scored',False) for x in modelrows),output_truncated=sum(x.get('finish_reason') in ('length','incomplete') for x in modelrows),a_manifest_unchanged=True,protocol_inherited=True,input_truncated=0)
  all_records.extend(dict(model=model,**r) for r in modelrows)
 sol_ids=[read(p)['response_id'] for p in (B/'sol/rows').glob('*/generation.json')]
 assert len(sol_ids)==len(set(sol_ids))<=100
 a_ids={read(p)['response_id'] for p in (BASE/'evidence/sol-a100/rows').glob('*/generation.json')}
 assert not set(sol_ids)&a_ids
 save(B/'actual-input-deltas.json',list(tokens.values()));save(B/'integrity.json',dict(models=summaries,rows=all_records,all_prior_A_unchanged=True,implementation_amendment=amend,unmodified_official_scorer=True,synthetic_controls_before_generation=True,checked_at=__import__('datetime').datetime.now(__import__('datetime').timezone.utc).isoformat()))
 print(summaries,flush=True)
if __name__=='__main__':main()
