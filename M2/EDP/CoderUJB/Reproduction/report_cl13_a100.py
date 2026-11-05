"""Compare both systems on identical rows; compute project-cluster paired uncertainty."""
from collections import Counter, defaultdict
from datetime import datetime
from math import comb
import random
from statistics import mean
import json
from pathlib import Path
from heatmap_a100 import FROZEN, name, A as OSS
from score_cl13_a100 import A
from score_candidate import save, sha, dd_metrics


def summarize():
    pairs=[]
    for row in FROZEN:
        k=name(row)
        cfile=A/'scores'/(k+'.json')
        cl=json.loads(cfile.read_text()) if cfile.exists() else {}
        oss=json.loads((OSS/'scores'/(k+'.json')).read_text())
        pairs.append(dict(task=row['task'],revision=row['revision'],task_idx=row['task_idx'],project=row['project'],bug_id=row['bug_id'],
                          cl=cl.get('status','unresolved'),oss=oss['status'],cl_score=str(cfile.relative_to(A)) if cl else None,
                          cl_reason=cl.get('reason'),oss_reason=oss.get('reason'),cl_finish_reason=cl.get('finish_reason'),
                          oss_finish_reason=oss['finish_reason'],cl_category=cl.get('category'),oss_category=oss['category'],
                          cl_evaluator=cl.get('result'),oss_evaluator=oss['result'],
                          cl_input_sha256=row['complete_sha256'],oss_input_sha256=row['chat_sha256']))
    tasks={}
    for t in ('FCG','CTG','ITG','APR','DD'):
        allrows=[r for r in pairs if r['task']==t]
        valid=[r for r in allrows if r['cl'] in ('pass','fail') and r['oss'] in ('pass','fail')]
        category=Counter((r['cl']=='pass',r['oss']=='pass') for r in valid)
        both=category[True,True]; cl_only=category[True,False]; oss_only=category[False,True]; neither=category[False,False]
        groups=defaultdict(list)
        for r in valid:groups[r['project']].append(int(r['cl']=='pass')-int(r['oss']=='pass'))
        # Resample whole projects so that repeated rows, including the two DD partners, stay together.
        keys=sorted(groups); dist=[]; rng=random.Random(20261105)
        if groups:
            for _ in range(10000):
                diffs=[d for k in rng.choices(keys,k=len(keys)) for d in groups[k]]
                dist.append(mean(diffs)*100)
            dist.sort()
        n=cl_only+oss_only
        p=min(1,2*sum(comb(n,j) for j in range(min(cl_only,oss_only)+1))/2**n)
        tasks[t]=dict(planned=len(allrows),paired=len(valid),projects=len(keys),
                      cl_pass=sum(r['cl']=='pass' for r in allrows),oss_pass=sum(r['oss']=='pass' for r in allrows),
                      cl_unresolved=sum(r['cl'] not in ('pass','fail') for r in allrows),
                      oss_unresolved=sum(r['oss'] not in ('pass','fail') for r in allrows),
                      both_pass=both,cl_only=cl_only,oss_only=oss_only,both_fail=neither,
                      cl_frozen_bounds=[sum(r['cl']=='pass' for r in allrows),sum(r['cl']!='fail' for r in allrows)],
                      delta_frozen_bounds_pp=[100*(sum(r['cl']=='pass' for r in allrows)-sum(r['oss']=='pass' for r in allrows))/len(allrows),
                                              100*(sum(r['cl']!='fail' for r in allrows)-sum(r['oss']=='pass' for r in allrows))/len(allrows)],
                      cl_minus_oss_pp=100*(cl_only-oss_only)/len(valid) if valid else None,
                      cluster_bootstrap_95_pp=[round(dist[249],1),round(dist[9749],1)] if dist else None,
                      mcnemar_exact_descriptive=p,
                      cl_length=sum(r['cl_finish_reason']=='length' for r in valid),
                      cl_length_pass=sum(r['cl_finish_reason']=='length' and r['cl']=='pass' for r in valid),
                      oss_length=sum(r['oss_finish_reason']=='length' for r in valid))
    return pairs,tasks


def main():
    pairs,tasks=summarize()
    scores=[json.loads(p.read_text()) for p in (A/'scores').glob('*.json')]
    dd=dd_metrics([r['cl_category'] for r in pairs if r['cl_category']])
    acc=(A/'slurm-accounting.txt').read_text().splitlines()[1] if (A/'slurm-accounting.txt').is_file() else None
    cost=dict(paid_api_usd=0,slurm=acc,input_tokens=sum(r['input_tokens'] for r in scores),
              output_tokens=sum(r['output_tokens'] for r in scores),input_truncated=sum(r['input_truncated'] for r in scores),
              output_length=sum(r['output_truncated'] for r in scores),
              output_length_and_pass=sum(r['output_truncated'] and r['status']=='pass' for r in scores))
    save(A/'paired.json',dict(date=datetime.now().astimezone().isoformat(),tasks=tasks,dd=dd,cost=cost,rows=pairs))
    lines=['# 同题单次生成对照：CodeLlama-13B 与 gpt-oss-120b','',
           '两套系统各自在冻结的 100 题上生成一次。表内差值按 CodeLlama 减 gpt-oss 计算。','',
           '| 任务 | CodeLlama 通过/20 | gpt-oss 通过/20 | 已判定配对 | 都通过 | 仅 CodeLlama | 仅 gpt-oss | 都失败 | 有效配对差（百分点） | 项目重采样 95% 范围（百分点） |',
           '|---|---:|---:|---:|---:|---:|---:|---:|---:|---|']
    for t,c in tasks.items():
        lines.append(f"| {t} | {c['cl_pass']} | {c['oss_pass']} | {c['paired']} | {c['both_pass']} | {c['cl_only']} | {c['oss_only']} | {c['both_fail']} | {c['cl_minus_oss_pp']:+.1f} | {c['cluster_bootstrap_95_pp']} |")
    for t,c in tasks.items():
        if c['cl_unresolved']:
            lo,hi=c['cl_frozen_bounds']; dlo,dhi=c['delta_frozen_bounds_pp']
            lines.append(f"\n{t} 有 {c['cl_unresolved']} 条 CodeLlama 未决；全 20 题的通过数范围 {lo}–{hi}，差值范围 {dlo:+.0f} 至 {dhi:+.0f} 个百分点。")
    if tasks['FCG']['cl_unresolved']:
        lines+=['','FCG 第 116 行在同一目标测试两次达到 180 秒上限，正式统计沿用超时未决规则。参考实现同一测试耗时约 1.1 秒。生成的 parseSimpleToken 直接返回 token，调用者在 token 类型为 INVALID 时继续循环；两份 JVM 栈都停在该调用处。[源码与栈快照](diagnostics/FCG-116/)']
    dd_sensitivity=json.loads((A/'dd-first-choice.json').read_text())['systems']
    cl_dd=dd_sensitivity['cl']; oss_dd=dd_sensitivity['oss']
    lines+=['',f"DD 的官方判分读取整段续写，并优先匹配肯定关键词。CodeLlama 在 {cl_dd['disagreements']} 题开头明确选 B，随后续写另一道题并出现选项 A 的 Yes；发布解析器将这些行判成有缺陷。作为离线诊断，只读开头的选项时 CodeLlama 正确 {cl_dd['first_choice']['correct']}/20，gpt-oss 正确 {oss_dd['first_choice']['correct']}/20。主表仍使用官方规则。[逐行首选项核对](dd-first-choice.json)"]
    reviews=[r for r in scores if r.get('reason')=='official_extraction_missing_method']
    if reviews:
        lines+=['',f"APR 有 {len(reviews)} 个原始提交经官方提取后只剩未结束的注释，调用方无法编译。第 109 行的原始生成包含 value(double) 方法，但发布提取器在 Javadoc 的代码标记处提前停止。判定保留原始答案、提取文本、javac 错误与参考对照。[第 109 行原始补全](rows/APR-109-99a9d802b33ab1389d0969eab96b5b2737489f08/continuation.txt)"]
    lines+=['','每类 20 题，一题相当于 5 个百分点。对相同题目成对计算差值，按项目整体有放回重采样 10,000 次，同项目内的题和 DD 配对共同移动。区间描述这批项目上的波动，不能用于推断 2,239 题的总体结果。逐题配对文件还列出精确 McNemar 描述值；它假定不一致对独立，项目内相关及五项比较会限制解释。','',
            'CodeLlama 使用基础版权重和官方 completion 提示，BF16，按题号设随机种子，最多保留末尾 4,096 个输入 tokens，新生成 256 tokens。评分器接收原样解码的完整序列，并调用官方 completion 提取函数。gpt-oss 使用 chat 提示和 Harmony 模板，MXFP4，medium 推理，种子 4，推理和回答共用 4,096 个输出 tokens。差值反映这两套运行配置在同一题单上的表现；其中包含提示形式、采样和预算差异。','',
            f"CodeLlama 输入被截断 {cost['input_truncated']} 题；新生成达到长度上限 {cost['output_length']} 题，其中 {cost['output_length_and_pass']} 题通过。补全模型可能已输出完整目标方法，然后继续写后续代码，所以到达上限与通过测试可以同时发生。DD 正确 {dd['correct']}/{dd['total']}，不可解析 {dd['error']}，TP/TN/FP/FN 为 {dd['tp']}/{dd['tn']}/{dd['fp']}/{dd['fn']}。",'',
            f"CodeLlama 共使用 {cost['input_tokens']:,} 个输入 tokens，生成 {cost['output_tokens']:,} 个 tokens。付费 API 支出 $0。资源记录见 Slurm 回执。",'',
            '发布的本地配方通常每题生成 20 个候选，DD 为 10 个；本次每题 1 个。发布代码使用 FastChat 0.2.36 / Transformers 4.38.1 加载模型，本次直接使用 Transformers 4.53.3 / tokenizers 0.21.4。基础版 checkpoint 固定，但作者的精确 revision 未得到独立确认。论文表 4 的全量、多样本复现仍待执行。','',
            '[逐题差异和评分路径](paired.json) · [CodeLlama 生成协议](protocol.json) · [评分与输入复核](integrity.json) · [Slurm 资源](slurm-accounting.txt) · [输入与权重清单](weights-receipt.json) · [gpt-oss A 列报告](../oss120-a100/报告.md)']
    (A/'对照报告.md').write_text('\n'.join(lines)+'\n')


if __name__=='__main__':
    main()
