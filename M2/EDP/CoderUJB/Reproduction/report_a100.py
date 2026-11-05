"""Summarize A on the original denominator, including rows that could not be scored."""
from collections import Counter
from pathlib import Path
import json
from datetime import datetime

from heatmap_a100 import A, BASE, FROZEN, name, PROTOCOL
from score_candidate import dd_metrics, save


def read(path):
    return json.loads(path.read_text()) if path.is_file() else {}


def main():
    rows=[]
    totals={}
    projects={}
    batches=[]
    for folder in sorted((A/'batches').glob('*')):
        meta=folder/'slurm-accounting.txt'
        batches.append(dict(name=folder.name, planned=len(read(folder/'inputs.json')),
                            completed=len(list(folder.glob('*/generation.json'))),
                            slurm=meta.read_text().splitlines()[1] if meta.is_file() else None))
    for r in FROZEN:
        key=name(r)
        eligibility=read(A/'preflight'/(key+'.json'))
        score=read(A/'scores'/(key+'.json'))
        record=dict(task=r['task'],revision=r['revision'],task_idx=r['task_idx'],project=r['project'],bug_id=r['bug_id'],
                    eligible=eligibility.get('eligible'),check=eligibility.get('check'),
                    reference_status=eligibility.get('reference_status'),reference_reason=eligibility.get('reason'),
                    reference_log=eligibility.get('log'),status=score.get('status','unresolved'),
                    reason=score.get('reason'),finish_reason=score.get('finish_reason'),truncated=score.get('truncated'),
                    category=score.get('category'),usage=score.get('usage'),score_log=score.get('result'),batch=score.get('batch'),
                    compile_review=score.get('compile_review'))
        rows.append(record)
    for t in sorted({r['task'] for r in rows}):
        group=[r for r in rows if r['task']==t]
        passes=sum(r['status']=='pass' for r in group)
        failures=sum(r['status']=='fail' for r in group)
        unresolved=len(group)-passes-failures
        totals[t]=dict(n=len(group),passed=passes,failed=failures,unresolved=unresolved,
                       generated=sum(r['finish_reason'] is not None for r in group),
                       truncated=sum(bool(r['truncated']) for r in group),
                       lower_pct=round(100*passes/len(group),1),upper_pct=round(100*(passes+unresolved)/len(group),1))
    for project in sorted({r['project'] for r in rows}):
        java=[r for r in rows if r['project']==project and r['task']!='DD']
        projects[project]=dict(java_rows=len(java),verified=sum(r['eligible'] is True for r in java),
                        pending=sum(r['eligible'] is None for r in java),unresolved=sum(r['eligible'] is False for r in java))
    gpu_seconds=0
    for job in batches:
        if job['slurm']:
            elapsed=job['slurm'].split('|')[3]
            h,m,sec=map(int,elapsed.split(':'))
            gpu_seconds+=3600*h+60*m+sec
    phase_seconds={}
    for key in ('reference_log','score_log'):
        logs={r[key] for r in rows if r[key]}
        phase_seconds[key]=round(sum(c['elapsed_seconds'] for log in logs for c in read(BASE/log).get('commands',[])),1)
    tokens={k:sum(r['usage'].get(k,0) for r in rows if r['usage']) for k in ('prompt_tokens','completion_tokens')}
    report=dict(generated_at=datetime.now().astimezone().isoformat(),protocol=PROTOCOL['name'],tasks=totals,
               dd=dd_metrics([r['category'] for r in rows if r['category']]),projects=projects,batches=batches,rows=rows,
               gpu_job_seconds=gpu_seconds,worker_command_seconds=phase_seconds,tokens=tokens,paid_api_usd=0)
    save(A/'report.json',report)
    lines=['# gpt-oss-120b 在冻结 100 题上的 A 列','',report['generated_at'],'',
           '计分保留每类 20 行。区间下界将全部未决行计零，上界将全部未决行计一。DD 用全分母准确率。','',
           '| 任务 | 题数 | 已生成并评分 | 通过 | 失败 | 未决 | 输出截断 | 原分母上的分数区间 |',
           '|---|---:|---:|---:|---:|---:|---:|---:|']
    for t in ('FCG','CTG','ITG','APR','DD'):
        c=totals[t]
        lines.append(f"| {t} | {c['n']} | {c['generated']} | {c['passed']} | {c['failed']} | {c['unresolved']} | {c['truncated']} | {c['lower_pct']}% – {c['upper_pct']}% |")
    d=report['dd']
    lines+=['',f"DD 已判定行的 TP、TN、FP、FN、不可解析数依次为 {d['tp']}、{d['tn']}、{d['fp']}、{d['fn']}、{d['error']}。",'',
            '| 项目 | Java 题 | 原始对照通过 | 对照未决 | 待核验 |','|---|---:|---:|---:|---:|']
    for project,c in projects.items():lines.append(f"| {project} | {c['java_rows']} | {c['verified']} | {c['unresolved']} | {c['pending']} |")
    lines+=['','按行区分原始对照及模型判定。每行受 revision、任务名、行号约束；同名项目按具体缺陷版本核验。','',
            f"各次单卡 Slurm 作业累计 {gpu_seconds//60} 分 {gpu_seconds%60} 秒（含权重暂存及启动）。输入 {tokens['prompt_tokens']:,} tokens，输出 {tokens['completion_tokens']:,} tokens（含推理）。付费 API 支出 $0。",
            f"逐命令耗时之和：参考对照 {phase_seconds['reference_log']/60:.1f} 分钟，模型答案评分 {phase_seconds['score_log']/60:.1f} 分钟；多个评分进程并行执行。",
            '', '[逐行证据索引](report.json) · [实际送模输入校验](input-audit.json) · [协议](protocol.json) · [生成批次](batches/) · [项目安装记录](env/)']
    (A/'报告.md').write_text('\n'.join(lines)+'\n')


if __name__=='__main__':
    main()
