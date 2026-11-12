"""Exam queueing networks (2023, 2025) drawn in the TD3 course style:
queue cells followed by a grey circular server, mu above, lambda below,
routing probabilities (and flows) on the branches, exits as arrows to the right.
Helpers mirror TD/Images/TD3_2627_diagrams.py."""
from pathlib import Path
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle, Circle, FancyArrowPatch
from matplotlib import rcParams
rcParams.update({'font.family': 'DejaVu Sans', 'font.size': 12, 'svg.fonttype': 'none'})
ROOT = Path(__file__).resolve().parent
LINE = '#b2b2b2'; FILL = '#c6c6c6'

def canvas(w, h):
    fig, ax = plt.subplots(figsize=(w, h))
    ax.set(xlim=(0, w), ylim=(0, h), aspect='equal'); ax.axis('off')
    fig.subplots_adjust(left=.02, right=.98, bottom=.035, top=.965)
    return fig, ax

def route(ax, points, prob=None, label=None, end_arrow=True, lw=.75):
    xs, ys = zip(*points); ax.plot(xs, ys, color=LINE, lw=lw, zorder=1)
    if end_arrow:
        a, b = points[-2], points[-1]
        ax.add_patch(FancyArrowPatch(a, b, arrowstyle='-|>', mutation_scale=14, color='black',
                                     linewidth=.35, zorder=3, shrinkA=0, shrinkB=0))
    if prob is not None:
        if label is None:
            a, b = points[0], points[1]; label = ((a[0]+b[0])/2, (a[1]+b[1])/2+.12)
        ax.text(*label, prob, fontsize=11, ha='center', va='center', zorder=5,
                bbox={'facecolor': 'white', 'edgecolor': 'none', 'pad': .45})

def station(ax, x, y, name, mu, lam=None, width=1.28, r=.33):
    ax.add_patch(Rectangle((x, y-.27), width, .54, fill=False, edgecolor=LINE, lw=.65, zorder=2))
    for j in range(1, 4): ax.plot([x+j*width/4]*2, [y-.27, y+.27], color=LINE, lw=.65, zorder=2)
    cx = x+width+.58
    ax.plot([x+width, cx-r], [y, y], color=LINE, lw=.65)
    ax.add_patch(Circle((cx, y), r, facecolor=FILL, edgecolor=LINE, lw=.7, zorder=4))
    ax.text(cx, y, name, ha='center', va='center', fontsize=12, zorder=5)
    ax.text(cx, y+.61, mu, ha='center', va='center', fontsize=10.5)
    if lam: ax.text(x+width/2, y-.51, lam, ha='center', va='center', fontsize=10.5)
    return (x, y), (cx+r, y)

def dot(ax, *pts):
    for x, y in pts: ax.plot(x, y, '.', color=LINE, markersize=2)

def save(fig, name):
    for ext in ['png', 'svg']: fig.savefig(ROOT/f'{name}.{ext}', dpi=190, facecolor='white')
    plt.close(fig)

XEND = 14.2

# ---------- Examen 2023 : Cal_G, Cal_S, Disk1, Disk2 ----------
fig, ax = canvas(14.6, 7.6)
G, Gout = station(ax, 2.6, 5.4, r'$Cal_G$', r'$\mu_G=1200$', r'$\lambda_G=0.2\lambda$', r=.42)
S, Sout = station(ax, 2.6, 2.2, r'$Cal_S$', r'$\mu_S=2500$', r'$\lambda_S=0.8\lambda$', r=.42)
D1, D1out = station(ax, 9.0, 4.85, r'$D_1$', r'$\mu_{D_1}\approx166.67$', r'$\lambda_{D_1}=\frac{31}{150}\lambda$', r=.36)
D2, D2out = station(ax, 9.0, 2.75, r'$D_2$', r'$\mu_{D_2}=250$', r'$\lambda_{D_2}=\frac{31}{300}\lambda$', r=.36)
E = (1.2, 3.8)
route(ax, [(.2, 3.8), E], end_arrow=False); ax.text(.25, 4.15, r'$\lambda$', fontsize=12)
route(ax, [E, (1.9, 5.4), G], prob=r'$0.2$', label=(1.35, 4.75))
route(ax, [E, (1.9, 2.2), S], prob=r'$0.8$', label=(1.35, 2.85))
# exits from the computing units
route(ax, [Gout, (5.55, 5.4), (5.55, 6.9), (XEND, 6.9)], prob=r'$0.85\;(0.17\lambda)$', label=(7.6, 7.05))
route(ax, [Sout, (5.55, 2.2), (5.55, .7), (XEND, .7)], prob=r'$0.65\;(0.52\lambda)$', label=(7.6, .85))
# towards the storage space, merged then split by capacity (1 TB : 500 GB)
M = (7.6, 3.8)
route(ax, [(5.55, 5.4), (6.4, 5.4), (6.4, 3.8), M], prob=r'$0.15\;(0.03\lambda)$', label=(6.4, 4.75), end_arrow=False)
route(ax, [(5.55, 2.2), (6.4, 2.2), (6.4, 3.8)], prob=r'$0.35\;(0.28\lambda)$', label=(6.4, 2.85), end_arrow=False)
ax.text(7.25, 3.5, r'$0.31\lambda$', fontsize=10.5, ha='center', va='center')
route(ax, [M, (8.4, 4.85), D1], prob=r'$2/3$', label=(8.25, 4.55))
route(ax, [M, (8.4, 2.75), D2], prob=r'$1/3$', label=(8.25, 3.05))
route(ax, [D1out, (XEND, 4.85)], prob=r'$1$', label=(12.8, 5.0))
route(ax, [D2out, (XEND, 2.75)], prob=r'$1$', label=(12.8, 2.9))
dot(ax, E, M, (5.55, 5.4), (5.55, 2.2), (6.4, 3.8))
ax.set_xlim(.1, XEND+.2); ax.set_ylim(.35, 7.45)
fig.set_size_inches(14.3, 7.1)
save(fig, 'network2023_fr')

# ---------- Examen 2025 : R1 -> R2/R3, R2 -> R4/sortie, R4 -> R3 ----------
fig, ax = canvas(14.6, 6.6)
R1, R1out = station(ax, 1.0, 3.6, r'$R_1$', r'$\mu_{R_1}=400$', r'$\lambda_{R_1}=\lambda$')
R2, R2out = station(ax, 4.6, 1.9, r'$R_2$', r'$\mu_{R_2}=180$', r'$\lambda_{R_2}=0.3\lambda$')
R3, R3out = station(ax, 8.9, 5.1, r'$R_3$', r'$\mu_{R_3}=550$', r'$\lambda_{R_3}=0.94\lambda$')
R4, R4out = station(ax, 9.6, 1.9, r'$R_4$', r'$\mu_{R_4}=125$', r'$\lambda_{R_4}=0.24\lambda$')
route(ax, [(.1, 3.6), R1], end_arrow=True); ax.text(.15, 3.95, r'$\lambda$', fontsize=12)
B = (3.75, 3.6)
route(ax, [R1out, B], end_arrow=False)
M3 = (8.2, 5.1)
route(ax, [B, (3.75, 5.1), M3], prob=r'$0.7\;(0.7\lambda)$', label=(5.9, 5.25), end_arrow=False)
route(ax, [M3, R3])
route(ax, [B, (3.75, 1.9), R2], prob=r'$0.3\;(0.3\lambda)$', label=(3.75, 2.75))
B2 = (7.4, 1.9)
route(ax, [R2out, B2], end_arrow=False)
route(ax, [B2, R4], prob=r'$0.8\;(0.24\lambda)$', label=(8.5, 2.05))
route(ax, [B2, (7.4, .6), (XEND, .6)], prob=r'$0.2\;(0.06\lambda)$', label=(10.6, .75))
route(ax, [R4out, (12.3, 1.9), (12.3, 3.55), (8.2, 3.55), M3], prob=r'$1\;(0.24\lambda)$', label=(10.25, 3.7), end_arrow=False)
route(ax, [R3out, (XEND, 5.1)], prob=r'$1\;(0.94\lambda)$', label=(12.6, 5.25))
dot(ax, B, M3, B2)
ax.set_xlim(.05, XEND+.2); ax.set_ylim(.25, 6.15)
fig.set_size_inches(14.3, 6.0)
save(fig, 'network2025_fr')
print('ok')
