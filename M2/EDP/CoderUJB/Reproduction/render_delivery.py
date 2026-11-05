"""Render the reviewed evidence. Offline: no generation, Java execution, or network."""
from pathlib import Path
import csv
import json
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np

BASE = Path(__file__).resolve().parent
OUT = BASE / 'evidence/final-review'
MODELS = {'cl': 'CodeLlama-13B', 'qwen': 'Qwen2.5-Coder-32B',
          'oss': 'gpt-oss-120b', 'sol': 'GPT-6.1 Sol'}
TASKS = ('FCG', 'CTG', 'ITG', 'APR', 'DD')


def main():
    r = json.loads((OUT/'recomputed.json').read_text())
    table = []
    for task in TASKS:
        for model in MODELS:
            for col in ('A', 'B'):
                c = r['stats'][model][task][col]
                p = c.get('pass', 0); f = c.get('fail', 0); u = 20-p-f
                table.append(dict(task=task, model=model, column=col, passed=p,
                                  failed=f, unknown=u, planned=20, determinate=p+f,
                                  lower_percent=5*p, upper_percent=5*(p+u)))
    with (OUT/'cells.csv').open('w') as f:
        w = csv.DictWriter(f, fieldnames=list(table[0])); w.writeheader(); w.writerows(table)
    paired = []
    for model in MODELS:
        for task in TASKS:
            p = r['paired'][model][task]
            paired.append(dict(model=model, task=task, determinate_pairs=p['known'],
                               both_pass=p['both'], gain=p['left_only'], loss=p['right_only'],
                               both_fail=p['neither'], unknown_pairs=20-p['known'],
                               delta_pp=p['delta_pp'], cluster95=p['cluster95']))
    with (OUT/'paired.csv').open('w') as f:
        w = csv.DictWriter(f, fieldnames=list(paired[0])); w.writeheader(); w.writerows(paired)

    # Use English figure labels for portable fonts. The handoff explains the columns in Chinese.
    fig, axes = plt.subplots(3, 2, figsize=(13.5, 12))
    cmap = plt.get_cmap('YlGnBu').copy(); cmap.set_bad('#e6e6e6')
    for ax, task in zip(axes.flat, TASKS):
        values = np.full((4, 5), np.nan)
        for i, model in enumerate(MODELS):
            for j, col in enumerate(('A', 'B')):
                c = next(x for x in table if (x['task'], x['model'], x['column']) == (task, model, col))
                values[i, j] = c['lower_percent']
        im = ax.imshow(values, cmap=cmap, vmin=0, vmax=100, aspect='auto')
        ax.set_title(task, loc='left', weight='bold', pad=10)
        ax.set_yticks(range(4), MODELS.values()); ax.set_xticks(range(5), ['A', 'B', 'C', 'D', 'E'])
        ax.tick_params(length=0, pad=7)
        for i, model in enumerate(MODELS):
            for j, col in enumerate(('A', 'B', 'C', 'D', 'E')):
                if j >= 2: label='Not run'; color='#777777'
                else:
                    c=next(x for x in table if (x['task'], x['model'], x['column']) == (task, model, col))
                    label=f"{c['passed']}/20 ({c['lower_percent']}%)"
                    if c['unknown']: label+=f"\n{c['unknown']} unknown"
                    elif col=='B':
                        a=r['stats'][model][task]['A']; d=c['passed']-a.get('pass',0)
                        # Delta explicitly uses paired denominator, not treating an unknown as a failure.
                        p=r['paired'][model][task]
                        label+=f"\nΔ {p['delta_pp']:+.1f} pp"
                        if p['known']!=20:label+=f"\n({p['known']} pairs)"
                    color='white' if c['lower_percent']>=60 else '#142735'
                ax.text(j,i,label,ha='center',va='center',fontsize=8.2,color=color)
        for s in ax.spines.values():s.set_visible(False)
    axes.flat[-1].axis('off')
    axes.flat[-1].text(0,1,
        'Reviewed v2 · 800 saved formal answers\n'
        '798 determinate answers · 398 determinate A/B pairs\n\n'
        'A: official task prompt\nB: fixed output constraint\nC–E: NOT RUN (gray)\n\n'
        'Cells: passes / 20 planned; unknowns remain unknown.\n'
        'Color uses the observed lower bound, not known-only accuracy.\n'
        'B delta: paired B − A; each task has 19 or 20 known pairs.\n\n'
        'CTG correction: CodeLlama B 4 → 5 passes.\n'
        'The added pass is an empty test credited for enum initialization.\n'
        'Benchmark pass does not establish test usefulness.\n\n'
        'Exploratory follow-up after seeing A;\none generation per cell.\n'
        'Different model formats and output budgets; not a causal\n'
        'estimate of model age, nor the full paper reproduction.',
        transform=axes.flat[-1].transAxes,va='top',fontsize=10,linespacing=1.5)
    fig.suptitle('CoderUJB · frozen 100 tasks · A/B reviewed results',fontsize=17,y=.99)
    fig.tight_layout(rect=(0,.08,1,.975),h_pad=2,w_pad=2)
    cax=fig.add_axes((.25,.04,.5,.013));fig.colorbar(im,cax=cax,orientation='horizontal',label='Observed passes / 20 planned (%)')
    for ext in ('png','svg','pdf'):fig.savefig(OUT/f'heatmap-reviewed.{ext}',dpi=180,bbox_inches='tight')
    plt.close(fig)

    chosen=[('FCG','sol',11),('FCG','sol',53),('CTG','sol',21),('CTG','cl',21),
            ('ITG','sol',22),('ITG','cl',22),('APR','sol',1),('APR','cl',50),
            ('DD','sol',98),('DD','sol',215),('CTG','cl',48)]
    notes=[
        '目标测试与完整项目套件都为 0 失败。',
        '3 个目标测试均通过，但完整套件有 36 个失败；不能只看目标测试或退出码 0。',
        'Base64 测试正确比较 byte[]；目标测试通过，覆盖 53/148 行（35.8%）。',
        '将 String 与 byte[] 直接比较，目标断言失败；不能算有效测试。',
        '固定版通过；缺陷版编译成功后，插入测试第 117 行断言期望 42、实际 null；覆盖 92/343 行。',
        '只检查字符串值，两版本都通过，未触发 issue 中的非字符串值缺陷。',
        '补丁通过指定回归测试和完整项目套件。',
        'Base64 输出意外带换行；指定回归测试期望无换行，判失败。',
        '原始回答 B/No，数据标签 defective=false；官方解析为 tn。',
        '原始回答 A/Yes，数据标签 defective=false；官方解析为 fp。',
        'v1→v2 唯一修正；测试体为空。7 行覆盖来自两个内部枚举类初始化，满足官方正覆盖门槛，不证明测试有用。']
    samples=[]
    for (task,model,idx),note in zip(chosen,notes):
        x=next(x for x in r['rows'] if (x['task'],x['model'],x['task_idx'],x['column'])==(task,model,idx,'B'))
        samples.append(dict(task=task,model=model,column='B',task_idx=idx,status=x['status'],
                            note=note,result=x['result'],raw_source=x['raw_source'],details=x['details']))
    for task in TASKS:assert {s['status'] for s in samples if s['task']==task}=={'pass','fail'}
    (OUT/'samples.json').write_text(json.dumps(samples,ensure_ascii=False,indent=2)+'\n')
    print('Rendered 40 observed cells; 60 gray unrun cells; 20 paired comparisons; 11 inspected samples.')


if __name__=='__main__':main()
