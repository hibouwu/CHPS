"""Prepare the dependency graph and photo archive; edit the single Markdown directly."""
from pathlib import Path
import json,hashlib
import fitz
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from matplotlib.patches import Circle,FancyArrowPatch

ROOT=Path(__file__).resolve().parents[1]
positions={'A':(0,2),'C':(1.3,2),'F':(2.6,2),'I':(3.9,2),'K':(5.2,2),'D':(1.3,1),'G':(2.6,1),'J':(3.9,1),'B':(0,0),'E':(1.3,0),'H':(2.6,0)}
same=[('A','C'),('C','F'),('F','I'),('I','K'),('D','G'),('G','J'),('B','E'),('E','H')]
cross=[('A','D'),('D','H'),('G','I'),('H','J'),('J','K')]
plt.rcParams['svg.fonttype']='none'
fig,ax=plt.subplots(figsize=(8,3.9))
for start,end in same+cross:
 ax.add_patch(FancyArrowPatch(positions[start],positions[end],arrowstyle='-|>',mutation_scale=15,shrinkA=17,shrinkB=17,lw=1.6,color='#303030'))
for name,xy in positions.items():
 ax.add_patch(Circle(xy,.22,facecolor='white',edgecolor='#303030',lw=1.8));ax.text(*xy,name,ha='center',va='center',size=13,weight='bold')
for y,n in [(2,0),(1,1),(0,2)]:ax.text(-.45,y,f'STREAM {n}',ha='right',va='center',size=10)
ax.set(xlim=(-1.5,5.6),ylim=(-.5,2.5),aspect='equal');ax.axis('off');fig.tight_layout()
fig.savefig(ROOT/'Images/kernel_dependencies.png',dpi=200,bbox_inches='tight');fig.savefig(ROOT/'Images/kernel_dependencies.svg',bbox_inches='tight');plt.close(fig)
manifest=[];pdf=fitz.open()
for i,name in enumerate(['粘贴的图像.png','粘贴的图像 (2).png','粘贴的图像 (3).png','粘贴的图像 (4).png'],1):
 p=ROOT/name;pix=fitz.Pixmap(str(p));page=pdf.new_page(width=595.28,height=841.89);page.insert_image(page.rect,filename=str(p),keep_proportion=True)
 manifest.append({'page':i,'file':name,'sha256':hashlib.sha256(p.read_bytes()).hexdigest()})
pdf.set_metadata({'title':'APM 2025-2026 - CC1 - Photos originales','author':'Sujet enseignant fourni par l’utilisateur'});pdf.save(ROOT/'output/pdf/APM_CC1_2025_Photos.pdf');pdf.close()
(ROOT/'source_manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n')
