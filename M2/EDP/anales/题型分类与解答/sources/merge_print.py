from pathlib import Path
import json,subprocess,io,tempfile
from pypdf import PdfReader,PdfWriter
from reportlab.pdfgen import canvas
R=Path(__file__).resolve().parents[1];docs=json.loads((R/'sources/documents.json').read_text())
counts=[len(PdfReader(R/'pdf'/(stem+'.pdf')).pages) for stem,title in docs]
coverpages=1
for iteration in range(3):
 offset=coverpages;entries=[]
 for (stem,title),n in zip(docs,counts):
  entries.append(dict(stem=stem,title=title,pages=n,combined_first=offset+1,combined_last=offset+n));offset+=n
 text='# EDP Exercices classés et corrigés 题型分类与解答\n\nImpression A4 en noir et blanc, taille réelle 100 %. A4 黑白打印，使用 100% 实际尺寸。\n\nCorpus : TD1, TD3, TD4, examens 2023 et 2025. 覆盖 TD1、TD3、TD4 与 2023、2025 两套试卷，共 24 个来源题组。\n\nÉnoncés et solutions en français puis en chinois sur la même ligne. 题干与解答均采用法语在前、中文在后的同行对照格式。\n\n| Fascicule 分类册 | Pages 页码 |\n|---|---|\n'
 for e in entries:text+='| '+e['title']+' | '+str(e['combined_first'])+'–'+str(e['combined_last'])+' |\n'
 text+='\nChaque exercice complet figure une seule fois dans sa catégorie principale. Les questions associées portent une étiquette ; leur autre catégorie fournit un index avec le document et les pages. Chaque index distingue pages du fascicule et du recueil. 每道完整大题只收录一次；跨类别小问在题旁标记，其他类别开头给出文档与页码索引，并区分分册与合订本页码。\n\nLes corrigés sont des solutions de travail vérifiées, pas un corrigé officiel. 学习题解已进行计算核对，不是教师官方标准答案。\n\nPour les réseaux : identifier les flux et la stabilité avant les temps ; préciser si une ressource est choisie par sa durée locale ou sa contribution globale. 排队题先求流量、判断稳定性，再计算时间；选择主要资源时须说明局部时延或全局贡献的口径。\n\nPour les statistiques : distinguer table continue, paramètre estimé et distribution discrète. 统计题须区分连续查表、参数估计和离散分布校准。\n'
 with tempfile.TemporaryDirectory() as td:
  md=Path(td)/'index.md';pdf=Path(td)/'index.pdf';md.write_text(text)
  cmd=['pandoc',str(md),'--from=markdown+tex_math_dollars-smart','--standalone','--pdf-engine=xelatex','-H',str(R/'sources/print_header.tex'),'-V','papersize=a4','-V','fontsize=11pt','-V','geometry:margin=17mm','-V','mainfont=TeX Gyre Pagella','-V','sansfont=TeX Gyre Heros','-V','monofont=Latin Modern Mono','-o',str(pdf)]
  subprocess.run(cmd,check=True,capture_output=True)
  cover=pdf.read_bytes();actual=len(PdfReader(io.BytesIO(cover)).pages)
 if actual==coverpages:break
 coverpages=actual
else:raise RuntimeError('Cover page count did not converge')
writer=PdfWriter();writer.append(PdfReader(io.BytesIO(cover)),outline_item='Sommaire 分类目录')
for stem,title in docs:writer.append(str(R/'pdf'/(stem+'.pdf')),outline_item=title)
# Continuous global page numbers for the combined print copy.
total=len(writer.pages)
for i,page in enumerate(writer.pages,1):
 buf=io.BytesIO();c=canvas.Canvas(buf,pagesize=(float(page.mediabox.width),float(page.mediabox.height)))
 c.setFillColorRGB(1,1,1);c.rect(240,0,120,48,fill=1,stroke=0)
 c.setFillColorRGB(0,0,0);c.setFont('Helvetica',9);c.drawCentredString(float(page.mediabox.width)/2,30,f'{i} / {total}');c.save();buf.seek(0)
 page.merge_page(PdfReader(buf).pages[0])
with (R/'pdf/00_全部题型合订本.pdf').open('wb') as f:writer.write(f)
(R/'sources/page_manifest.json').write_text(json.dumps(entries,ensure_ascii=False,indent=2))
print('Combined:',total,'pages; cover:',coverpages,'pages')
