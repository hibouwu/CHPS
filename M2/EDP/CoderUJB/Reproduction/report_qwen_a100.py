"""Three systems on the same frozen denominator, with project-cluster paired diagnostics."""
from collections import Counter,defaultdict
import json
from math import comb
from pathlib import Path
import random
from score_qwen_a100 import A, PRIOR, FROZEN, name
from score_cl13_a100 import A as CL
from score_candidate import BASE, save, dd_metrics

SYSTEMS={'cl':CL,'oss':PRIOR,'qwen':A}
PAIRS=[('qwen','cl'),('qwen','oss'),('cl','oss')]


def compare(rows,left,right):
    groups=defaultdict(list);cont=Counter()
    for r in rows:
        l=r[left]['status'];v=r[right]['status']
        if l not in ('pass','fail') or v not in ('pass','fail'):continue
        groups[r['project']].append(int(l=='pass')-int(v=='pass'))
        cont[l=='pass',v=='pass']+=1
    both=cont[True,True];a=cont[True,False];b=cont[False,True];neither=cont[False,False]
    n=sum(cont.values());p=1
    if a+b:p=min(1,2*sum(comb(a+b,i) for i in range(min(a,b)+1))/2**(a+b))
    keys=sorted(groups);draws=[];rng=random.Random(20261105)
    summaries={k:(sum(groups[k]),len(groups[k])) for k in keys}
    if keys:
        for _ in range(10000):
            sampled=[summaries[k] for k in rng.choices(keys,k=len(keys))]
            draws.append(100*sum(x for x,_ in sampled)/sum(y for _,y in sampled))
        draws.sort()
    lo=sum(int(r[left]['status']=='pass')-int(r[right]['status']!='fail') for r in rows)
    hi=sum(int(r[left]['status']!='fail')-int(r[right]['status']=='pass') for r in rows)
    return dict(known=n,both=both,left_only=a,right_only=b,neither=neither,delta_pp=round(100*(a-b)/n,2) if n else None,
                delta_all20_bounds=[100*lo/len(rows),100*hi/len(rows)],projects=len(keys),
                cluster95=[round(draws[249],1),round(draws[9749],1)] if draws else None,exact_mcnemar_descriptive=p)


def main():
    records=[]
    for r in FROZEN:
        rec={'task':r['task'],'task_idx':r['task_idx'],'revision':r['revision'],'project':r['project'],'bug_id':r['bug_id']}
        for model,d in SYSTEMS.items():
            f=d/'scores'/(name(r)+'.json')
            s=json.loads(f.read_text()) if f.is_file() else {}
            rec[model]=dict(status=s.get('status','unresolved'),reason=s.get('reason'),category=s.get('category'),
                            finish_reason=s.get('finish_reason'),score_path=str(f.relative_to(BASE)) if f.is_file() else None,
                            scorer_path=s.get('result'))
        records.append(rec)
    stats={};paired={}
    for task in ('FCG','CTG','ITG','APR','DD'):
        rs=[r for r in records if r['task']==task]
        stats[task]={m:dict(passed=sum(r[m]['status']=='pass' for r in rs),failed=sum(r[m]['status']=='fail' for r in rs),
                            unknown=sum(r[m]['status'] not in ('pass','fail') for r in rs),
                            length_stops=sum(r[m]['finish_reason']=='length' for r in rs)) for m in SYSTEMS}
        paired[task]={l+'-'+r:compare(rs,l,r) for l,r in PAIRS}
    costs=json.loads((A/'cost.json').read_text())
    dd={m:dd_metrics([r[m]['category'] for r in records if r['task']=='DD' and r[m]['category']]) for m in SYSTEMS}
    save(A/'three-models.json',dict(tasks=stats,paired=paired,dd=dd,cost=costs,rows=records))
    lines=['# 冻结 100 题的三模型单次生成对照','','每类 20 题，采用各任务官方提取和判分规则。','',
           '| 任务 | CodeLlama-13B | gpt-oss-120b | Qwen2.5-Coder-32B-Instruct |','|---|---:|---:|---:|']
    for t,group in stats.items():
        cells=[f"{group[m]['passed']}/20"+(f"（{group[m]['unknown']} 未决）" if group[m]['unknown'] else '') for m in SYSTEMS]
        lines.append('| '+t+' | '+' | '.join(cells)+' |')
    lines+=['','同题配对中，差值按 Qwen 减参照模型计算。每项百分比基于两边都有确定结果的行。','',
            '| 任务 | 参照模型 | 有效对 | 都通过 | 仅 Qwen | 仅参照 | 都失败 | 差值（百分点） | 项目重采样 95% 范围 |',
            '|---|---|---:|---:|---:|---:|---:|---:|---|']
    for t in stats:
        for other,title in [('cl','CodeLlama'),('oss','gpt-oss')]:
            x=paired[t]['qwen-'+other]
            diff=f"{x['delta_pp']:+.1f}" if x['delta_pp'] is not None else 'NA'
            lines.append(f"| {t} | {title} | {x['known']} | {x['both']} | {x['left_only']} | {x['right_only']} | {x['neither']} | {diff} | {x['cluster95']} |")
    if stats['APR']['qwen']['unknown']:
        lines+=['','Qwen 的 APR 第 410 行两次在测试类初始化时报告 Europe/London 时区不可识别，目标断言尚未执行。该题保留未决，APR 的全 20 题通过数范围为 2–3，对 gpt-oss 的差值范围为 -20 至 -15 个百分点。对应版本的参考对照此前通过。']
    ddcheck=json.loads((A/'dd-first-choice.json').read_text())
    lines+=['',f"Qwen 的 DD 官方判分为 {ddcheck['official']['correct']}/20。按独立诊断规则，{ddcheck['unambiguous']} 条在首行有清晰的 A/Yes 或 B/No 选项，其中 {ddcheck['disagreements_on_unambiguous']} 条与官方解析的类别不同。[Qwen 的 DD 首行复核](dd-first-choice.json)"]
    lines+=['','区间按项目整体抽样 10,000 次（种子 20261105）；同项目的题、DD 的缺陷/修复配对一起移动。每类 20 行中，一题相差 5 个百分点。FCG 与 CodeLlama 比较时一题因目标测试超时未决，逐行文件另给全分母差值上下界。这些区间反映选中项目上的波动。','',
            'Qwen 使用 BF16 权重与固定 revision 的原生 chat 模板，温度 0.2，最多新生成 4,096 个回答 tokens。gpt-oss 使用 MXFP4，推理与回答共用 4,096 tokens；CodeLlama 使用 completion 提示，输出上限 256 tokens。相同题单上的差异，同时包含模型、提示形式、解码和预算的差异。','',
            '评分时保留每题原始输出。CodeLlama 的 APR 有 5 道提交只剩未完注释；DD 的回复可能继续生成下一题，官方解析器对肯定关键词的优先级会改变判定。首选项分析只列为离线诊断。','',
            f"Qwen 正式批次生成 {costs['formal_generated']}/100 个回答，正式输入 {costs['input_tokens']:,} tokens、输出 {costs['output_tokens']:,} tokens。ROMEO 单卡作业合计 {costs['slurm_seconds']//60} 分 {costs['slurm_seconds']%60} 秒（含暂存、独立调试和等待本地放行），付费 API 支出 $0。",'',
            '[逐题配对、原因和评分日志](three-models.json) · [输入及权重核验](integrity.json) · [协议](protocol.json) · [独立调试题](pilot-score.json) · [资源与费用](cost.json)']
    (A/'三模型对照.md').write_text('\n'.join(lines)+'\n')

if __name__=='__main__':
    main()
