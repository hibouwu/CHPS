"""Audit Sol provenance, reconcile observed usage, and report four frozen A columns."""
from collections import Counter
import itertools
from run_sol_a100 import A,BASE,MODEL,LEDGER,read,save,sha,name,now
from report_qwen_a100 import compare
from score_candidate import dd_metrics, row_at
import re

def main():
 frozen=read(BASE/'evidence/dataset-audit/heatmap-100.json');cfg=read(A/'protocol.json')
 assert cfg['frozen_sha256']==sha((BASE/'evidence/dataset-audit/heatmap-100.json').read_bytes())=='3e4c226648297ac9585195b9950c74db3dc59a0f5d336e552f667bcc12388546'
 data={};all_ids=[];all_request_ids=[];identities=[]
 for phase,inputs in [('pilot',read(A/'pilots.json')),('rows',read(A/'inputs.json'))]:
  totals=Counter();states=Counter()
  for r in inputs:
   key=name(r);d=A/phase/key;req=read(d/'request.json');disp=read(d/'dispatch.json');g=read(d/'generation.json');raw=read(d/'response.json')
   assert disp['protocol_sha256']==sha((A/'protocol.json').read_bytes())
   assert disp['request_sha256']==sha((d/'request.json').read_bytes())
   assert sha((d/'response.json').read_bytes())==g['response_sha256']
   assert sha((d/'final.txt').read_bytes())==g['answer_sha256']
   assert req['input']==[{'role':'user','content':r['prompt']}]
   assert sha(r['prompt'].encode())==r['prompt_sha256']==disp['prompt_sha256']
   assert req['model']==raw['model']==MODEL and req['reasoning']['effort']==raw['reasoning']['effort']=='medium'
   assert raw['service_tier']==req['service_tier']=='default' and raw['tools']==[]
   assert req['store']==raw['store']==False and req['max_output_tokens']==raw['max_output_tokens']==4096
   u=g['usage'];i=u['input_tokens'];o=u['output_tokens'];c=u['input_tokens_details'].get('cached_tokens',0);w=u['input_tokens_details'].get('cache_write_tokens',0);rr=u['output_tokens_details'].get('reasoning_tokens',0)
   assert i==disp['input_tokens'] and i==read(A/'counts'/(key+'.json'))['body']['input_tokens']
   assert o<=4096 and rr<=o and c+w<=i
   cost=((i-c-w)*2+c*.1+w*2.5+o*10)/1e6
   assert abs(cost-g['cost_standard_estimate_usd'])<1e-10
   score=read(A/('pilot-scores' if phase=='pilot' else 'scores')/(key+'.json'))
   evidence=read(BASE/score['result'])
   assert evidence['raw_sha256']==g['answer_sha256']==score['answer_sha256']
   assert evidence['task']==r['task'] and evidence['task_idx']==r['task_idx'] and evidence['revision']==r['revision']
   assert score['response_id']==raw['id']==g['response_id'] and score['request_id']==g['request_id']
   assert score['usage']==u
   if score['status']!=evidence['status']:assert score['compile_review'] and score['status']=='fail'
   states[g['status']]+=1
   for k,v in dict(requests=1,input_tokens=i,output_tokens=o,reasoning_tokens=rr,cached_tokens=c,cache_write_tokens=w,standard_estimate_usd=cost,conservative_usd=g['cost_conservative_usd']).items():totals[k]+=v
   all_ids.append(g['response_id']);all_request_ids.append(g['request_id'])
   identities.append(dict(key=key,phase=phase,prompt_sha256=r['prompt_sha256'],response_id=g['response_id'],answer_sha256=g['answer_sha256'],score_path=score['result']))
  data[phase]=dict(totals);data[phase]['response_statuses']=dict(states)
 assert len(set(all_ids))==len(set(all_request_ids))==105
 assert len(list(A.glob('rows/*/dispatch.json')))==100 and len(list(A.glob('pilot/*/dispatch.json')))==5
 prior={}
 for model in ('oss120-a100','cl13-a100','qwen-a100'):
  d=BASE/'evidence'/model;manifest=read(d/'sha256.json');bad=[f for f,h in manifest.items() if sha((d/f).read_bytes())!=h]
  assert not bad
  prior[model]=dict(checked=len(manifest),mismatches=bad,manifest_sha256=sha((d/'sha256.json').read_bytes()))
 assert prior==read(A/'prior-integrity-before.json')
 save(A/'integrity.json',dict(verified_at=now(),identities=identities,prior_models=prior,requests=105,formal_rows=100,pilots=5,duplicate_response_ids=0,duplicate_request_ids=0,frozen_sha256=cfg['frozen_sha256'],runner_sha256=sha((BASE/'run_sol_a100.py').read_bytes()),scorer_sha256=sha((BASE/'score_candidate.py').read_bytes())))
 total=data['pilot']['standard_estimate_usd']+data['rows']['standard_estimate_usd'];upper=data['pilot']['conservative_usd']+data['rows']['conservative_usd']
 cost=dict(stage='sol-a100',currency='USD',source='Responses usage and official standard prices; estimate, not account invoice',pilot=data['pilot'],formal=data['rows'],total_estimate_usd=total,conservative_usd=upper,original_worst_case_usd=read(A/'cost-plan.json')['worst_case_usd'],reserved_ceiling_usd=10,unknown_billing_requests=0,retries=0)
 save(A/'cost.json',cost)
 ledger=read(LEDGER)
 assert ledger['paid_jobs_submitted']==105 and abs(ledger['incurred_estimate']-total)<1e-8
 # Keep a conservative regional/cache upper accounting limit, release only unused reserve.
 if not any(t.get('type')=='release' and t.get('stage')=='sol-a100' for t in ledger['transactions']):
  ledger['reserved_maximum']=0;ledger['incurred_conservative_upper']=upper;ledger['last_verified']=now();ledger['transactions'].append(dict(type='release',stage='sol-a100',usd=10,time=now(),incurred_estimate=total,incurred_conservative_upper=upper,unknown_billing_requests=0));save(LEDGER,ledger)
 records=read(BASE/'evidence/qwen-a100/three-models.json')['rows']
 for r in records:
  s=read(A/'scores'/(name(r)+'.json'))
  r['sol']=dict(status=s['status'],reason=s['reason'],category=s['category'],finish_reason=s['finish_status'],score_path=str((A/'scores'/(name(r)+'.json')).relative_to(BASE)),scorer_path=s['result'])
 stats={};paired={};models=('cl','oss','qwen','sol')
 for task in ('FCG','CTG','ITG','APR','DD'):
  rs=[r for r in records if r['task']==task]
  assert len(rs)==20
  stats[task]={m:dict(passed=sum(r[m]['status']=='pass' for r in rs),failed=sum(r[m]['status']=='fail' for r in rs),unknown=sum(r[m]['status'] not in ('pass','fail') for r in rs)) for m in models}
  paired[task]={m:compare(rs,'sol',m) for m in models if m!='sol'}
 dd={m:dd_metrics([r[m]['category'] for r in records if r['task']=='DD' and r[m]['category']]) for m in models}
 save(A/'four-models.json',dict(tasks=stats,paired_sol_minus=paired,dd=dd,cost=cost,rows=records))
 choices=[]
 for r in records:
  if r['task']!='DD':continue
  line=(A/'rows'/name(r)/'final.txt').read_text().strip().splitlines()[0]
  match=re.fullmatch(r'([AB])\.\s+(Yes|No),.*',line)
  assert match and (match[1]=='A')==(match[2]=='Yes')
  label=row_at('DD',r['task_idx'])['defective'];first=match[1]=='A'
  category=('tp' if label else 'fp') if first else ('fn' if label else 'tn')
  choices.append(dict(key=name(r),first_line=line,first_category=category,official_category=r['sol']['category']))
 choice_report=dict(purpose='Offline diagnostic only; formal scores unchanged',rows=choices,unambiguous=len(choices),disagreements=sum(c['first_category']!=c['official_category'] for c in choices),first_choice=dd_metrics([c['first_category'] for c in choices]))
 save(A/'dd-first-choice.json',choice_report)

 lines=['# 冻结 100 题：四模型 A 列单次生成评测','','2026-11-05。题单与前三模型相同，每类 20 题；另有五类各 1 道独立试跑题，不计入正式分数。所有正式题仅请求一次，没有根据测试反馈重写答案。','',
 '| 任务 | CodeLlama-13B | gpt-oss-120b | Qwen2.5-Coder-32B-Instruct | GPT-6.1 Sol |','|---|---:|---:|---:|---:|']
 for t,group in stats.items():
  cells=[f"{group[m]['passed']}/20"+(f"（{group[m]['unknown']} 未决）" if group[m]['unknown'] else '') for m in models];lines.append('| '+t+' | '+' | '.join(cells)+' |')
 lines+=['','FCG：功能代码生成；CTG：基于代码生成测试；ITG：编写复现缺陷的测试；APR：程序修复；DD：缺陷检测。前四项按任务规定检查编译、测试与覆盖，DD 使用官方标签解析。','',
 '## Sol 协议与费用','',
 '正式入口为 `https://api.openai.com/v1/responses`，请求和返回模型标识均为 `gpt-6.1-sol`，标准服务档位 `default`。使用本地已有普通 API 密钥；没有使用 Codex OAuth。原始官方 chat 提示作为单条 user 消息，不加额外 system 提示，不接工具。推理强度为 medium，推理和最终回答共用 4,096 tokens 上限，未指定 temperature 或 seed。最终答案从 Responses 的 final_answer 消息提取，再交给固定版本的官方后处理。','',
 '官方价格为每百万输入 tokens $2、缓存读取 $0.10、缓存写入 $2.50、输出 $10。实际计费估算区分三类输入，并将 reasoning_tokens 包含在 output_tokens 内，避免漏计或重复计费。[官方模型与价格](https://developers.openai.com/api/docs/models/gpt-6.1-sol) · [输入计数接口](https://developers.openai.com/api/docs/guides/token-counting)','',
 f"发送前 105 次请求的输入量由官方接口计数，总预算上界 ${cost['original_worst_case_usd']:.4f}，低于阶段预留 $10。实际用量估算：试跑 ${data['pilot']['standard_estimate_usd']:.6f}，正式 100 题 ${data['rows']['standard_estimate_usd']:.6f}，合计 **${total:.6f}**；保守计费上界 ${upper:.6f}。这是按用量与公开价格计算的金额，未读取账户最终账单。没有未知状态请求，没有重试生成，阶段预留已释放。",'',
 f"正式输入 {data['rows']['input_tokens']:,} tokens，输出 {data['rows']['output_tokens']:,} tokens（含推理 {data['rows']['reasoning_tokens']:,}）；缓存读取 {data['rows']['cached_tokens']:,}，缓存写入 {data['rows']['cache_write_tokens']:,}。结束状态：{data['rows']['response_statuses']}。",'',
 '## 同题差值与未决项','',
 '| 任务 | 参照模型 | 有效配对 | 都通过 | 仅 Sol | 仅参照 | 差值（百分点） | 项目重采样 95% 范围 |','|---|---|---:|---:|---:|---:|---:|---|']
 for task in stats:
  for m in models[:-1]:
   x=paired[task][m];lines.append(f"| {task} | {m} | {x['known']} | {x['both']} | {x['left_only']} | {x['right_only']} | {x['delta_pp']} | {x['cluster95']} |")
 unknown=[(r,m) for r in records for m in models if r[m]['status'] not in ('pass','fail')]
 lines+=['','未决行保持原始 20 题分母，配对差值只用两边均有确定结果的行；完整分母的差值上下界保存在 JSON。','']
 for r,m in unknown:lines.append(f"- {m} {r['task']}-{r['task_idx']}：{r[m]['status']}，{r[m]['reason']}；[原始评分](../../{r[m]['scorer_path']})。")
 lines+=['','Sol 的失败与未决原因（保持原始评分）：','']
 for task in stats:
  reasons=Counter(r['sol']['reason'] or r['sol']['status'] for r in records if r['task']==task and r['sol']['status']!='pass')
  lines.append('- '+task+'：'+('；'.join(f'{k} × {v}' for k,v in reasons.items()) or '无'))
 lines+=['',f"Sol 的 20 道 DD 回复均有明确首选项，其中 {choice_report['disagreements']} 道与官方解析类别不一致。[首选项诊断](dd-first-choice.json)"]
 lines+=['','区间按项目整体重采样 10,000 次，种子 20261105，同一项目及 DD 缺陷/修复配对共同移动。每类只有 20 题，一题就是 5 个百分点；这些是固定子集上的描述性比较，不代表全部 2,239 题或全模型能力排序。','',
 '不同模型的提示格式、权重精度、解码和输出预算不同。CodeLlama 为 completion，输出上限 256；Qwen 为 chat，4,096 回答 tokens；gpt-oss 和 Sol 为 chat，推理与回答共用 4,096。不能把差值全部归因于模型能力，更不能据此宣称复现了论文的多样本统计。Sol 的公开模型标识没有提供独立的日期快照，本轮保留请求时间和服务返回标识，不能把它视为已固定服务端权重。当前只完成 A 列；B–E 工程配置及全量评测尚未执行。','',
 '## 可追溯记录','',
 '[协议](protocol.json) · [试跑放行](pilot-gate.json) · [预算上界](cost-plan.json) · [费用](cost.json) · [身份与完整性核验](integrity.json) · [四模型逐题结果](four-models.json) · [运行日志](formal-run.log)','',
 '每题目录保留 request、dispatch、原始 response、final、generation 文件。dispatch 在请求发送前落盘，发生传输不确定时停止新请求并保留最大可能费用；本轮未触发。评分记录引用独立的编译与测试日志。前三模型已发布清单的哈希在本轮前后完全一致。']
 (A/'四模型对照.md').write_text('\n'.join(lines)+'\n')
 # Hash all Sol evidence and the scripts; exclude the manifest itself and runtime lock.
 files=[p for p in A.rglob('*') if p.is_file() and p.name not in ('sha256.json','dispatch.lock')]
 manifest={str(p.relative_to(A)):sha(p.read_bytes()) for p in sorted(files)}
 manifest['../../run_sol_a100.py']=sha((BASE/'run_sol_a100.py').read_bytes());manifest['../../report_sol_a100.py']=sha((BASE/'report_sol_a100.py').read_bytes())
 save(A/'sha256.json',manifest)
 print(json_summary(stats,total,upper),flush=True)
def json_summary(stats,total,upper):
 import json
 return json.dumps(dict(tasks=stats,usd=total,conservative_usd=upper),ensure_ascii=False)
if __name__=='__main__':main()
