from pathlib import Path
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle,Circle,FancyArrowPatch
from matplotlib import rcParams
rcParams.update({'font.family':'DejaVu Sans','font.size':12,'svg.fonttype':'none'})
ROOT=Path('/home/jianyeshi/Note/SiteCHPS/CHPS/M2/EDP/TD/Images')
LINE='#b2b2b2'; FILL='#c6c6c6';TEXT='black'
def canvas(w,h):
 fig,ax=plt.subplots(figsize=(w,h))
 ax.set(xlim=(0,w),ylim=(0,h),aspect='equal');ax.axis('off')
 fig.subplots_adjust(left=.02,right=.98,bottom=.035,top=.965)
 return fig,ax

def route(ax,points,prob=None,label=None,end_arrow=True,lw=.75):
 xs,ys=zip(*points);ax.plot(xs,ys,color=LINE,lw=lw,zorder=1)
 if end_arrow:
  a,b=points[-2],points[-1]
  ax.add_patch(FancyArrowPatch(a,b,arrowstyle='-|>',mutation_scale=14,color='black',linewidth=.35,zorder=3,shrinkA=0,shrinkB=0))
 if prob is not None:
  if label is None:
   a,b=points[0],points[1];label=((a[0]+b[0])/2,(a[1]+b[1])/2+.12)
  ax.text(*label,prob,fontsize=11,ha='center',va='center',zorder=5,bbox={'facecolor':'white','edgecolor':'none','pad':.45})

def station(ax,x,y,name,mu,lam=None,width=1.28,r=.33):
 # Queue cells, followed by a circular server, as in the TD figure.
 ax.add_patch(Rectangle((x,y-.27),width,.54,fill=False,edgecolor=LINE,lw=.65,zorder=2))
 for j in range(1,4):ax.plot([x+j*width/4]*2,[y-.27,y+.27],color=LINE,lw=.65,zorder=2)
 cx=x+width+.58
 ax.plot([x+width,cx-r],[y,y],color=LINE,lw=.65)
 ax.add_patch(Circle((cx,y),r,facecolor=FILL,edgecolor=LINE,lw=.7,zorder=4))
 ax.text(cx,y,name,ha='center',va='center',fontsize=12,zorder=5)
 ax.text(cx,y+.61,mu,ha='center',va='center',fontsize=10.5)
 if lam:ax.text(x+width/2,y-.51,lam,ha='center',va='center',fontsize=10.5)
 return (x,y),(cx+r,y)

def save(fig,names):
 for name in names:
  for ext in ['png','svg']:fig.savefig(ROOT/f'{name}.{ext}',dpi=190,facecolor='white')
 plt.close(fig)

# Exercise 1: preserve the original three input branches; duplicate only D and Cal.
fig,ax=canvas(15.7,9.2)
L1,L1out=station(ax,3.0,1.35,'L1',r'$\mu_{L1}=500$',r'$\lambda_{L1}=240$')
L2,L2out=station(ax,9.4,1.35,'L2',r'$\mu_{L2}=300$',r'$\lambda_{L2}=48$')
D1,D1out=station(ax,5.5,8.0,r'$D_1$',r'$\mu_{D_1}=250$',r'$\lambda_{D_1}=82.4$')
D2,D2out=station(ax,5.5,6.75,r'$D_2$',r'$\mu_{D_2}=250$',r'$\lambda_{D_2}=82.4$')
C1,C1out=station(ax,9.4,4.3,r'$\mathrm{Cal}_1$',r'$\mu_{\mathrm{Cal}_1}=1000$',r'$\lambda_{\mathrm{Cal}_1}=319.68$',r=.40)
C2,C2out=station(ax,9.4,3.05,r'$\mathrm{Cal}_2$',r'$\mu_{\mathrm{Cal}_2}=1000$',r'$\lambda_{\mathrm{Cal}_2}=319.68$',r=.40)
E=(1.0,4.3);Ds=(4.7,7.375);Cs=(8.55,3.675)
route(ax,[(.2,4.3),E],end_arrow=False);ax.text(.3,4.65,r'$\lambda=800$',ha='left',fontsize=11)
route(ax,[E,(2.5,7.375),Ds],prob='0.2',label=(2.05,6.45),end_arrow=False)
route(ax,[E,(7.2,4.3),(7.2,3.675),Cs],prob='0.5',label=(3.3,4.43),end_arrow=False)
route(ax,[E,(2.55,1.35),L1],prob='0.3',label=(1.75,2.65))
route(ax,[Ds,(5.05,8.0),D1],prob='1/2',label=(5.0,7.89))
route(ax,[Ds,(5.05,6.75),D2],prob='1/2',label=(5.0,6.96))
route(ax,[D1out,(15.25,8.0)],prob='0.8',label=(11.6,8.13))
route(ax,[D2out,(15.25,6.75)],prob='0.8',label=(11.6,6.88))
# D outputs merge before the equal split towards the two Cal queues.
Dm=(8.0,5.95)
route(ax,[D1out,(8.0,8.0),Dm],prob='0.2',label=(8.22,7.54),end_arrow=False)
route(ax,[D2out,(8.0,6.75),Dm],prob='0.2',label=(8.23,6.24),end_arrow=False)
route(ax,[Dm,(8.0,3.675),Cs],end_arrow=False)
route(ax,[Cs,(9.0,4.3),C1],prob='1/2',label=(8.91,4.08))
route(ax,[Cs,(9.0,3.05),C2],prob='1/2',label=(8.91,3.32))
route(ax,[C1out,(15.25,4.3)],prob='1',label=(13.5,4.44))
route(ax,[C2out,(15.25,3.05)],prob='1',label=(13.5,3.19))
route(ax,[L1out,L2],prob='0.2',label=(7.3,1.49))
route(ax,[L1out,(5.55,1.35),(5.55,2.38),(7.65,2.38),(7.65,3.675),Cs],prob='0.7',label=(6.3,2.5),end_arrow=False)
route(ax,[L1out,(5.55,1.35),(5.55,.55),(15.25,.55)],prob='0.1',label=(7.5,.69))
route(ax,[L2out,(15.25,1.35)],prob='0.1',label=(13.5,1.49))
route(ax,[L2out,(12.4,1.35),(12.4,2.16),(8.25,2.16),(8.25,3.675),Cs],prob='0.8',label=(10.3,2.29),end_arrow=False)
route(ax,[L2out,(12.85,1.35),(12.85,5.65),(4.7,5.65),Ds],prob='0.1',label=(10.9,5.80),end_arrow=False)
# Tiny junction points distinguish merges from simple crossings.
for x,y in [E,Ds,Cs,Dm,(5.55,1.35),(12.4,1.35),(12.85,1.35)]:ax.plot(x,y,'.',color=LINE,markersize=2)
ax.set_xlim(.1,15.45);ax.set_ylim(.25,8.95)
fig.set_size_inches(15.35,8.7)
save(fig,['TD3_2627_ex1_duplicated_zh','TD3_2627_ex1_duplicated_fr'])

# Exercise 2: single CPU queue, followed by three disk queues.
for part in ['I','II']:
 fig,ax=canvas(13.7,7.5)
 cpu,cpuout=station(ax,1.8,3.65,'CPU',r'$\mu_{\mathrm{CPU}}=10000$',r'$\lambda_{\mathrm{CPU}}=1100$',r=.4)
 labels=(['0.1']*3 if part=='I' else ['0.024','0.15','0.126'])
 rates=(['110']*3 if part=='I' else ['26.4','165','138.6'])
 mus=(['120']*3 if part=='I' else ['166.667','250','120'])
 route(ax,[(.35,3.65),cpu],prob='1',label=(1.1,3.81));ax.text(.4,4.10,r'$\lambda=1100$',fontsize=11)
 branch=(4.55,3.65)
 route(ax,[cpuout,branch],end_arrow=False)
 route(ax,[branch,(4.55,6.35),(13.25,6.35)],prob='0.7',label=(6.2,6.51))
 for j,y in enumerate([5.05,3.4,1.75],1):
  equality=r'\approx' if ('.' in mus[j-1] or mus[j-1]=='120') else '='
  din,dout=station(ax,7.45,y,rf'$D_{j}$',rf'$\mu_{{D_{j}}}{equality}{mus[j-1]}$',rf'$\lambda_{{D_{j}}}={rates[j-1]}$',r=.36)
  route(ax,[branch,(6.45,y),din],prob=labels[j-1],label=(5.7,(3.65+y)/2+.18))
  route(ax,[dout,(13.25,y)],prob='1',label=(11.7,y+.17))
 ax.plot(*branch,'.',color=LINE,markersize=2)
 ax.set_xlim(.1,13.5);ax.set_ylim(.95,6.75)
 fig.set_size_inches(13.4,5.8)
 save(fig,[f'TD3_2627_ex2_part{part}_network'])
print('Course-style PNG and SVG diagrams regenerated')
