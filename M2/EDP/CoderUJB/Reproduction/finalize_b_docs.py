"""Synchronize final B results into the user-facing workspace documents."""
from pathlib import Path
import json
BASE=Path(__file__).resolve().parent;B=BASE/'evidence/b100'
r=json.loads((B/'paired-results.json').read_text());cost=r['cost'];labels={'cl':'CodeLlama-13B','qwen':'Qwen2.5-Coder-32B-Instruct','oss':'gpt-oss-120b','sol':'GPT-6.1 Sol'}
assert all(x['B']['scored']==20 for m in r['stats'].values() for x in m.values())
table=['| 模型 | FCG | CTG | ITG | APR | DD |','|---|---:|---:|---:|---:|---:|']
for m,title in labels.items():
 cells=[]
 for t in ('FCG','CTG','ITG','APR','DD'):
  x=r['stats'][m][t];cells.append(f"{x['A']['passed']} → {x['B']['passed']}"+(f"（A 未决 {x['A']['unknown']}）" if x['A']['unknown'] else '')+(f"（B 未决 {x['B']['unknown']}）" if x['B']['unknown'] else ''))
 table.append('| '+title+' | '+' | '.join(cells)+' |')
ledger=json.loads((BASE/'evidence/dataset-audit/窗口预算.json').read_text())
block='''## B 列结果：固定输出约束

四模型均已完成同一固定 100 题的 B 列生成和评分，每题一次，共新增 400 次正式生成。下表为每类 20 题中的通过/答对数，箭头表示 A → B；未决行保留原分母。

'''+ '\n'.join(table)+f'''

Sol B 的用量估算为 ${cost['standard_estimate_usd']:.7f}，连同 A 正式请求和试跑，本窗口合计估算 ${ledger['incurred_estimate']:.7f}，保守费用上界 ${ledger['incurred_conservative_upper']:.7f}。两个阶段的预留均已释放，无计费状态不明请求。上述不是账户最终账单；三个 ROMEO 模型未调用付费 API。

这是在看过 A 结果后冻结的探索性工程比较。只增加任务级输出格式约束，公开权重模型的权重与运行设置保持一致，Sol 使用同一模型别名与参数。每类只有 20 题、每题一次生成，不能据此宣称普遍提高模型能力或完成原论文全量复现。原 A 列两道未决题未重试或改判，B 的新答案独立评分；不同模型/任务的改善与退步都保留。

[完整 A/B 热力图与配对统计](evidence/b100/A-B对照报告.md) · [逐题改善/退步与格式诊断](evidence/b100/paired-results.json) · [实际输入增量及丢弃记录](evidence/b100/actual-input-deltas.json) · [完整性核验](evidence/b100/integrity.json) · [费用](evidence/b100/cost.json)
'''
p=BASE/'实验设计.md';s=p.read_text();marker='\n## B 列结果：固定输出约束\n'
if marker in s:s=s[:s.index(marker)]
s=s.rstrip()+'\n\n'+block
s=s.replace('原论文的全量、多样本对照与 B–E 工程列仍待执行。','B 列固定输出约束对照也已完成；原论文的全量、多样本对照与 C–E 工程列仍待执行。')
p.write_text(s)
p=BASE.parent/'README.md';s=p.read_text();old='B 列正在按冻结规则执行：只增加任务级固定输出约束，复用 A 列结果和原评分器。'
s=s.replace(old,'B 列的四模型 400 次生成与评分也已完成：只增加任务级固定输出约束，复用 A 列结果和原评分器。')
s=s.replace('2,239 题全量、多次采样与 B–E 工程对照尚未执行。','2,239 题全量、多次采样与 C–E 工程对照尚未执行；B 列见下方入口。')
s=s.replace('累计付费 API 用量估算 **$0.561186**（包含五道独立试跑题，非账户最终账单），本轮预留已释放。',f"A 列及五道独立试跑题的付费 API 用量估算为 $0.561186；加上 B 列后，本窗口累计估算 **${ledger['incurred_estimate']:.7f}**（非账户最终账单），两个阶段的预留均已释放。")
needle='- [ ] CodeLlama-13B 完成 2,239 题'
if '- [x] 四模型完成固定 100 题的 B 列' not in s:s=s.replace(needle,'- [x] 四模型完成固定 100 题的 B 列单次生成与 A/B 配对，产出五类任务热力图和格式/测试效果诊断。\n'+needle)
p.write_text(s)
print('README and experimental design synchronized to final B results')
