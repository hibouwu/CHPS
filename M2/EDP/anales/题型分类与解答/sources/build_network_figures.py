"""Draw compact black and white routing diagrams for A4 printing."""
from pathlib import Path
import subprocess
R=Path(__file__).resolve().parent
base='''digraph G {
graph [rankdir=TB,bgcolor=white,nodesep=.35,ranksep=.38,dpi=200];
node [shape=box,fontname="DejaVu Sans",fontsize=15,margin=".10,.06"];
edge [fontname="DejaVu Sans",fontsize=13,arrowsize=.7];
'''
def draw(stem,body):
 p=R/(stem+'.dot');p.write_text(base+body+'\n}\n');subprocess.run(['dot','-Tpng',str(p),'-o',str(R/(stem+'.png'))],check=True)
draw('network2025','''
in [shape=plaintext,label="Entrée λ"];out [shape=plaintext,label="Sortie"];
R1 [label="R1 + file\\nμ=400"];R2 [label="R2 + file\\nμ=180"];
R3 [label="R3 + file\\nμ=550"];R4 [label="R4 + file\\nμ=125"];
{rank=same;in;R1;} {rank=same;R2;R3;} {rank=same;R4;out;}
in->R1 [label="λ",constraint=false];
R1->R2 [label="0.3; 0.3 λ"];R1->R3 [label="0.7; 0.7 λ"];
R2->R4 [label="0.8; 0.24 λ"];R2->out [label="0.2; 0.06 λ"];
R4->R3 [label="1; 0.24 λ",constraint=false];R3->out [label="1; 0.94 λ"];
''')
for stem,mus,probs,arr in [('td3_identical',['120.048']*3,['0.1']*3,['110']*3),('td3_heterogeneous',['166.667','250','120.048'],['0.024','0.15','0.126'],['26.4','165','138.6'])]:
 body='''in [shape=plaintext,label="Entrée: λ=1100"];out [shape=plaintext,label="Sortie"];
CPU [label="CPU + file\\nμ=10000; λ=1100"];
in->CPU [label="1"];
'''
 for i,(m,p,a) in enumerate(zip(mus,probs,arr),1):
  body+=f'D{i} [label="D{i} + file\\nμ={m}; λ={a}"];CPU->D{i} [label="{p}"];D{i}->out [label="1"];\n'
 body+='CPU->out [label="0.7"];{rank=same;D1;D2;D3;}'
 draw(stem,body)
draw('td3_duplicated','''
in [shape=plaintext,label="Entrée: λ=800"];out [shape=plaintext,label="Sortie"];
L1 [label="L1 + file\\nμ=500; λ=240"];L2 [label="L2 + file\\nμ=300; λ=48"];
D [label="D groupe: D1 / D2\\n2 files, répartition égale\\nChaque file: μ=250; λ=82.4"];
C [label="Cal groupe: Cal1 / Cal2\\n2 files, répartition égale\\nChaque file: μ=1000; λ=319.68"];
in->L1 [label="0.3"];in->D [label="0.2"];in->C [label="0.5"];
L1->L2 [label="0.2"];L1->C [label="0.7"];L1->out [label="0.1"];
L2->D [label="0.1"];L2->C [label="0.8"];L2->out [label="0.1"];
D->C [label="0.2"];D->out [label="0.8"];C->out [label="1"];
''')
