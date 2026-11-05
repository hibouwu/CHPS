"""Exploratory within-model A/B report; partial cells remain gray, no model ranking claim."""
from collections import Counter
from pathlib import Path
import datetime,json,re
from score_b100 import B,MODELS,read,format_valid
from score_candidate import BASE,save,sha,dd_metrics
from heatmap_a100 import FROZEN,name
from report_qwen_a100 import compare
LABELS={'cl':'CodeLlama-13B','oss':'gpt-oss-120b','qwen':'Qwen2.5-Coder-32B','sol':'GPT-6.1 Sol'}
TASKS=('FCG','CTG','ITG','APR','DD')
DISPLAY=('cl','qwen','oss','sol') # presentation follows the original design; execution order stays frozen

def record(model,r,column):
 root=(BASE/'evidence'/MODELS[model]) if column=='A' else B/model
 f=root/'scores'/(name(r)+'.json')
 if not f.exists():return dict(status='not_scored',reason='not generated or scoring pending',format_valid=None,compiled=None,score_path=None)
 s=read(f);p=BASE/s['result'];v=read(p)
 syntax=format_valid(r['task'],p,v)
 compile_cmd=next((c for c in v.get('commands',[]) if c['name']=='fixed-compile'),None)
 comp=compile_cmd['exit_code']==0 and not compile_cmd['timeout'] if compile_cmd else (False if syntax is False else None)
 return dict(status=s['status'],reason=s.get('reason'),format_valid=syntax,compiled=comp,category=s.get('category'),candidate_sha256=sha((p.parent/'candidate.txt').read_bytes()) if (p.parent/'candidate.txt').exists() else None,score_path=str(f.relative_to(BASE)),result=s['result'],finish_reason=s.get('finish_reason',s.get('finish_status')),input_truncated=s.get('input_truncated'),output_tokens=s.get('output_tokens'))

def costs():
 root=B/'sol';gs=[read(p) for p in root.glob('rows/*/generation.json')];dispatch=list(root.glob('rows/*/dispatch.json'))
 point=sum(g.get('cost_standard_estimate_usd',0) for g in gs);conservative=sum(g.get('cost_conservative_usd',0) for g in gs)
 uncertain=[]
 for p in dispatch:
  gp=p.parent/'generation.json'
  if not gp.exists() or 'cost_standard_estimate_usd' not in read(gp):uncertain.append(dict(key=p.parent.name,reserved_usd=read(p)['reserved_usd']))
 c=dict(stage='sol-b100',formal_requests=len(dispatch),responses=len(gs),standard_estimate_usd=point,conservative_usd=conservative,uncertain=uncertain,unknown_billing_reserve=sum(x['reserved_usd'] for x in uncertain),worst_case_usd=read(root/'cost-plan.json')['worst_case_usd'],inputs=sum(g.get('usage',{}).get('input_tokens',0) for g in gs),outputs=sum(g.get('usage',{}).get('output_tokens',0) for g in gs),reasoning=sum(g.get('usage',{}).get('output_tokens_details',{}).get('reasoning_tokens',0) for g in gs),cache_writes=sum(g.get('usage',{}).get('input_tokens_details',{}).get('cache_write_tokens',0) for g in gs))
 save(B/'cost.json',c)
 if (root/'generation-terminal.json').exists() and len(gs)==len(dispatch)==100 and not uncertain:
  ledgerfile=BASE/'evidence/dataset-audit/窗口预算.json';l=read(ledgerfile);old=read(BASE/'evidence/sol-a100/cost.json')
  assert abs(l['incurred_estimate']-old['total_estimate_usd']-point)<1e-8
  assert old['conservative_usd']+conservative<30
  if not any(x.get('type')=='release' and x.get('stage')=='sol-b100' for x in l['transactions']):
   l['reserved_maximum']=0;l['incurred_conservative_upper']=old['conservative_usd']+conservative;l['transactions'].append(dict(type='release',stage='sol-b100',usd=10,time=datetime.datetime.now(datetime.timezone.utc).isoformat(),incurred_estimate=point,incurred_conservative_upper=conservative));l['last_verified']=datetime.datetime.now(datetime.timezone.utc).isoformat();save(ledgerfile,l)
 return c

def plot(stats):
 import matplotlib
 matplotlib.use('Agg')
 import matplotlib.pyplot as plt
 import numpy as np
 fig,axes=plt.subplots(1,5,figsize=(15,4.5),layout='constrained')
 cmap=plt.colormaps['YlGnBu'].copy();cmap.set_bad('#dedede')
 for ax,t in zip(axes,TASKS):
  values=np.full((4,2),np.nan)
  for i,m in enumerate(DISPLAY):
   for j,c in enumerate(('A','B')):
    x=stats[m][t][c]
    if x['scored']==20:values[i,j]=100*x['passed']/20
  im=ax.imshow(values,vmin=0,vmax=100,cmap=cmap,aspect='equal')
  ax.set_title(t);ax.set_xticks([0,1],['A','B']);ax.set_yticks(range(4),[LABELS[m] for m in DISPLAY] if ax is axes[0] else ['']*4);ax.tick_params(length=0)
  for i,m in enumerate(DISPLAY):
   for j,c in enumerate(('A','B')):
    x=stats[m][t][c];txt=f"{x['passed']}/20"+(f"\n{x['unknown']} unresolved" if x['unknown'] else '') if x['scored']==20 else f"pending\n{x['scored']}/20 scored"
    ax.text(j,i,txt,ha='center',va='center',fontsize=8,color='white' if np.isfinite(values[i,j]) and values[i,j]>60 else 'black')
 fig.colorbar(im,ax=axes,shrink=.7,label='Passing / full 20-row denominator (%)')
 fig.suptitle('CoderUJB: fixed 100 rows, one candidate per model and configuration\nB = fixed output constraint; exploratory after seeing A',fontsize=13)
 for ext in ('png','svg','pdf'):fig.savefig(B/f'heatmap-ab.{ext}',dpi=180)
 plt.close(fig)

def main():
 rows=[];stats={};pairs={};formats={}
 for model in MODELS:
  rs=[]
  for r in FROZEN:
   rec={k:r[k] for k in ('task','task_idx','revision','project','bug_id')};rec['model']=model;rec['A']=record(model,r,'A');rec['B']=record(model,r,'B');rs.append(rec)
  rows.extend(rs);stats[model]={};pairs[model]={};formats[model]={}
  for task in TASKS:
   group=[r for r in rs if r['task']==task]
   stats[model][task]={c:dict(scored=sum(r[c]['score_path'] is not None for r in group),passed=sum(r[c]['status']=='pass' for r in group),failed=sum(r[c]['status']=='fail' for r in group),unknown=sum(r[c]['status'] not in ('pass','fail') for r in group),format_valid=sum(r[c]['format_valid'] is True for r in group),compiled=sum(r[c]['compiled'] is True for r in group)) for c in ('A','B')}
   pairs[model][task]=compare(group,'B','A')
   known=[r for r in group if r['A']['status'] in ('pass','fail') and r['B']['status'] in ('pass','fail')]
   both_format=[r for r in known if r['A']['format_valid'] is True and r['B']['format_valid'] is True]
   formats[model][task]=dict(known_pairs=len(known),format_recovered=sum(r['A']['format_valid'] is False and r['B']['format_valid'] is True for r in known),format_lost=sum(r['A']['format_valid'] is True and r['B']['format_valid'] is False for r in known),pass_gains_with_format_recovery=sum(r['A']['status']=='fail' and r['B']['status']=='pass' and r['A']['format_valid'] is False and r['B']['format_valid'] is True for r in known),pass_gains_both_format_valid=sum(r['A']['status']=='fail' and r['B']['status']=='pass' for r in both_format),pass_losses_both_format_valid=sum(r['A']['status']=='pass' and r['B']['status']=='fail' for r in both_format),both_format_valid=len(both_format),same_extracted_candidate=sum(r['A']['candidate_sha256'] is not None and r['A']['candidate_sha256']==r['B']['candidate_sha256'] for r in known))
 c=costs();generation_stats={}
 if (B/'actual-input-deltas.json').exists():
  deltas=read(B/'actual-input-deltas.json')
  for model,adir in MODELS.items():
   counts={}
   for column in ('A','B'):
    root=BASE/'evidence'/adir if column=='A' else B/model
    gens=[]
    for r in FROZEN:
     path=next((root/'batches').glob('*/'+name(r)+'/generation.json')) if model=='oss' and column=='A' else root/'rows'/name(r)/'generation.json'
     if path.exists():gens.append(read(path))
    counts[column]=dict(generated=len(gens),output_tokens=sum(g.get('output_tokens',g.get('usage',{}).get('output_tokens',g.get('usage',{}).get('completion_tokens',0))) for g in gens),length_stops=sum(g.get('finish_reason',g.get('status')) in ('length','incomplete') for g in gens))
   counts['input']=dict(a_tokens=sum(r['a_input_tokens'] for r in deltas if r['model']==model),b_tokens=sum(r['b_input_tokens'] for r in deltas if r['model']==model),added_tokens=sum(r['added_input_tokens'] for r in deltas if r['model']==model),discarded_tokens=sum(r['discarded_input_tokens'] for r in deltas if r['model']==model))
   generation_stats[model]=counts
  save(B/'generation-summary.json',generation_stats)
 save(B/'paired-results.json',dict(updated=datetime.datetime.now(datetime.timezone.utc).isoformat(),stats=stats,paired=pairs,format_diagnostics=formats,cost=c,rows=rows));plot(stats)
 lines=['# 固定输出约束：四模型 A/B 探索性比较','','A 为已完成的基线；B 只在原始提示前增加一条任务级固定输出约束。公开权重模型沿用 A 的固定权重、引擎和精度；所有模型沿用各自 A 的上下文与输出预算、解码及推理设置。Sol 使用相同 API 模型别名与服务档位，服务端没有提供可独立核验的权重快照。题单仍为同一冻结 100 行，每类 20 行，每题至多生成一次。','',
 '规则和提示在 B 生成前冻结，但设计时已经看过 A 的结果。这是后续探索性工程比较，不能称为完整盲测或预注册因果结论。','',
 '![各任务 A/B 热力图](heatmap-ab.png)','','灰格表示该模型/任务的 B 尚未全部评分；不是零分。已全部评分的格子保留完整 20 题分母，未决数另行标注。','',
 '| 模型 | 任务 | A 通过/20 | B 通过/20 | B 已评分 | 有效配对 | 改善 | 退步 | 差值（百分点） | 项目重采样 95% 范围 |',
 '|---|---|---:|---:|---:|---:|---:|---:|---:|---|']
 for m in DISPLAY:
  for t in TASKS:
   s=stats[m][t];p=pairs[m][t]
   lines.append(f"| {LABELS[m]} | {t} | {s['A']['passed']} | {s['B']['passed']} | {s['B']['scored']}/20 | {p['known']} | {p['left_only']} | {p['right_only']} | {p['delta_pp']} | {p['cluster95']} |")
 lines+=['','改善表示同题 A 失败、B 通过，退步表示 A 通过、B 失败；只在两边都有确定结果时计数。区间按项目整体重采样 10,000 次，种子 20261105，同项目题和 DD 缺陷/修复配对一起移动。完整分母的未知项差值上下界见 JSON。本次只比较同一个模型的 A/B，不把四模型间不同预算的差异解释为工程因果效应。','',
 '## 格式与测试效果','','“可解析”指官方提取后的 Java 候选能作为一个方法被语法解析，或 DD 原始判别器能解析选项；它不等于编译通过或功能正确。“双方可解析的改善”排除了明显的格式恢复，但仍不是对语义改善的独立因果识别。DD 的“可解析”仅表示原始整段关键词规则能给出标签，不保证标签与回复首选项一致；尤其不能把 DD 的分数变化全部解释为缺陷判断能力变化。','',
 '| 模型 | 任务 | A 可解析 | B 可解析 | 格式恢复 | 格式丢失 | 伴随格式恢复的通过改善 | 双方可解析时改善 | 双方可解析时退步 |',
 '|---|---|---:|---:|---:|---:|---:|---:|---:|']
 for m in DISPLAY:
  for t in TASKS:
   x=formats[m][t];s=stats[m][t];lines.append(f"| {LABELS[m]} | {t} | {s['A']['format_valid']} | {s['B']['format_valid']} | {x['format_recovered']} | {x['format_lost']} | {x['pass_gains_with_format_recovery']} | {x['pass_gains_both_format_valid']} | {x['pass_losses_both_format_valid']} |")
 lines+=['','## 提示与运行边界','','[冻结规则](freeze.json) · [逐题新增文本及 A/B 提示哈希](prompt-deltas.json) · [基准外合成样例](synthetic-controls.json) · [代码冻结](implementation-freeze.json)','',
 'CodeLlama 仍使用 completion。约束以 Java 注释前置，原提示及方法前缀逐字保留；本地分词预检最长 3,179 tokens，低于原 4,096 上限。评分前只移除本轮新增的那段输入前缀，再调用不变的官方 completion 提取器；模型生成的答案没有被改写，A 原有空白和切片偏移也没有修正。chat 模型仍用各自原有模板，只在 user 内容前加同一任务约束。','',
 '所有 A 结果保留复用。CodeLlama FCG-116 超时和 Qwen APR-410 初始化未决不重试、不改判；B 的新答案独立评分，如果答案与 A 完全相同，评分缓存按既定规则复用。未修改原始评分器或官方提取器。管理代码修正均单独留痕：补上预先冻结的评分截止检查，并在哈希校验发现 CRLF 被文本读取规范化后改为逐字节读取。受影响的答案在进入评分前已被拦下，没有重生成或修改答案，也没有修改官方提取器和评分规则。[修正记录](implementation-amendments.json)','',
 '正式生成上限 400 次，无 B 模型试跑请求；提示组装与解析用基准外合成文本检查。固定模型优先顺序为 CodeLlama、gpt-oss、Qwen、Sol，行顺序沿用 frozen100，Qwen 保留原来的每四行分组及每组随机种子。独立 ROMEO 作业并行生成，本地最多两个 Java 评分进程。预定 07:05 停止新生成，07:10 停止接纳新评分，07:22 前汇总与清理。','',
 '## 费用与未决范围','',f"Sol B 已发送 {c['formal_requests']} 次，收到 {c['responses']} 份响应；已知用量估算 ${c['standard_estimate_usd']:.6f}，保守费用 ${c['conservative_usd']:.6f}，未知请求预留 ${c['unknown_billing_reserve']:.6f}。发送前硬上界 ${c['worst_case_usd']:.6f}，阶段最多预留 $10，和 A 的费用共享 $30 窗口。费用按实际普通输入、缓存写入、缓存读取和输出计费，推理计入输出；不等于账户最终账单。ROMEO 没有产生付费 API 请求。",'',
 '[费用与用量](cost.json) · [统一窗口账本](../dataset-audit/窗口预算.json) · [逐题 A/B 及日志路径](paired-results.json) · [进度及队列状态](progress.json) · [PNG 热力图](heatmap-ab.png) · [SVG](heatmap-ab.svg) · [PDF](heatmap-ab.pdf)','',
 '本轮未执行 C–E 工程列或 2,239 题全量评测。每类 20 题，单题改变 5 个百分点，只有一次随机生成；项目重采样不覆盖随机种子变化或 API 后端权重变化。显著性和泛化结论都应保守。']
 unresolved=[]
 for r in rows:
  for column in ('A','B'):
   if r[column]['status'] not in ('pass','fail','not_scored'):
    unresolved.append((r,column))
 lines+=['','实际输入与生成预算使用：','','| 模型 | A 输入 | B 输入 | 新增 tokens | 丢弃 tokens | A 输出 | B 输出 | A/B 达上限次数 |','|---|---:|---:|---:|---:|---:|---:|---:|']
 for m,g in generation_stats.items():
  x=g['input'];lines.append(f"| {LABELS[m]} | {x['a_tokens']} | {x['b_tokens']} | {x['added_tokens']} | {x['discarded_tokens']} | {g['A']['output_tokens']} | {g['B']['output_tokens']} | {g['A']['length_stops']} / {g['B']['length_stops']} |")
 lines+=['','输出 tokens 的口径沿用各模型：CodeLlama/Qwen 为生成序列；gpt-oss/Sol 包含推理及最终答案。不同 tokenizer 的 token 数不直接跨模型比较。[生成用量明细](generation-summary.json)']
 lines+=['','已评分但未决的行：','']
 for r,column in unresolved:
  lines.append(f"- {LABELS[r['model']]} {column} {r['task']}-{r['task_idx']}：{r[column]['status']}，{r[column]['reason']}；[评分证据](../../{r[column]['result']})。")
 if not unresolved:lines.append('无。')
 lines+=['','[实际 A/B 输入 token 增量与丢弃记录](actual-input-deltas.json) · [运行与提取完整性核验](integrity.json)']
 (B/'A-B对照报告.md').write_text('\n'.join(lines)+'\n')
 print('report', {m:sum(stats[m][t]['B']['scored'] for t in TASKS) for m in MODELS},c['standard_estimate_usd'],flush=True)
if __name__=='__main__':main()
