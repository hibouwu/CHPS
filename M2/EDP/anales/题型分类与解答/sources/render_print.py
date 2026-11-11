from pathlib import Path
import json,subprocess,re,shutil,sys
R=Path(__file__).resolve().parents[1]
docs=json.loads((R/'sources/documents.json').read_text())
for stem,title in docs:
 if len(sys.argv)>1 and stem[:2] not in sys.argv[1:]:continue
 cmd=['pandoc',str(R/(stem+'.md')),'--from=markdown+tex_math_dollars-smart','--standalone','--pdf-engine=xelatex','--resource-path='+str(R),'-H',str(R/'sources/print_header.tex'),'--lua-filter='+str(R/'sources/fit_math.lua'),'-V','papersize=a4','-V','fontsize=11pt','-V','geometry:top=18mm,bottom=18mm,left=17mm,right=17mm','-V','mainfont=TeX Gyre Pagella','-V','sansfont=TeX Gyre Heros','-V','monofont=Latin Modern Mono','-V','linestretch=1.08','-o',str(R/'pdf'/(stem+'.pdf'))]
 result=subprocess.run(cmd,cwd=R,capture_output=True,text=True)
 (R/'sources'/(stem+'.render.log')).write_text(result.stdout+result.stderr)
 if result.returncode:raise RuntimeError(stem+'\n'+result.stderr[-6000:])
 print(stem,'rendered',flush=True)
# Assemble the combined copy with an index and continuous page numbers.
import sys
subprocess.run([sys.executable,str(R/'sources/merge_print.py')],check=True)
