"""Keep complete exercises unique; annotate mixed subquestions and locate printed cross-references."""
from pathlib import Path
import json,re,sys,subprocess,unicodedata
R=Path(__file__).resolve().parents[1]
SPECS=[
 dict(key='td1_1.2',to='03',source='TD1 §1.2',parts='Calcul de la fraction effective et commentaire 串行比例计算与并行行为解释（原题未分编号）',patterns=[r'^Calculer la fraction séquentielle']),
 dict(key='td1_2.2',to='01',source='TD1 §2.2',parts='(e)',patterns=[r'^\*\*\(e\)']),
 dict(key='exam2023_2',to='01',source='Examen 2023 ex.2 2023 年第 2 题',parts='Q2',patterns=[r'^2\. Calculez l.accélération moyenne']),
 dict(key='td1_4.1',to='01',source='TD1 §4.1',parts='(a–b)',patterns=[r'^\*\*\(a\)',r'^\*\*\(b\)']),
 dict(key='td1_4.2',to='01',source='TD1 §4.2',parts='(a–b)',patterns=[r'^\*\*\(a\)',r'^\*\*\(b\)']),
 dict(key='exam2025_1',to='01',source='Examen 2025 ex.1 2025 年第 1 题',parts='Q8',patterns=[r'^8\. Après ces deux remplacements']),
 dict(key='cylinders_combined',to='06',source='TD4 ex.5 TD4 第 5 题',parts='Q2',patterns=[r'^2\. Pouvez-vous confirmer']),
 dict(key='exam2025_3',to='06',source='Examen 2025 ex.3 2025 年第 3 题',parts='Q3–4',patterns=[r'^3\. En découpant',r'^4\. Peut-on confirmer'])
]
LABELS={'01':('Accélération et vectorisation','加速比与向量化'),'03':('Karp-Flatt et passage à l\'échelle','Karp–Flatt 与扩展性'),'06':('Test du khi-deux','卡方拟合优度检验')}
def apply(root=R):
 docs=json.loads((root/'sources/documents.json').read_text());items=json.loads((root/'sources/exercise_manifest.json').read_text());bykey={x['key']:x for x in items}
 assert len(items)==len(bykey)==20
 locpath=root/'sources/exercise_locations.json';loc=json.loads(locpath.read_text()) if locpath.exists() else {}
 for stem,title in docs:
  p=root/(stem+'.md');s=p.read_text()
  for spec in SPECS:
   item=bykey[spec['key']]
   if item['stem']!=stem:continue
   start=s.index('## '+item['title']+'\n');qstart=s.index('### Énoncé 题目',start);qend=s.index('### Corrigé détaillé 逐步解答',qstart)
   q=s[qstart:qend];fr,zh=LABELS[spec['to']];marker=f' **(Catégorie associée : {fr} 关联类别：{zh})**'
   for pattern in spec['patterns']:
    q,n=re.subn('('+pattern+r'[^\n]*)',lambda m:m.group(1)+marker,q,flags=re.M);assert n==1,(spec['key'],pattern,n)
   s=s[:qstart]+q+s[qend:]
  inbound=[x for x in SPECS if x['to']==stem[:2]]
  if inbound:
   index='## Index des exercices croisés 交叉题索引\n\nLes exercices ci-dessous restent entiers dans leur catégorie principale ; seules les questions associées sont indexées ici. 下列大题完整收录于各自主类别，本处只列相关小问的索引，不重复题干或答案。\n\n'
   for spec in inbound:
    item=bykey[spec['key']];v=loc.get(spec['key'],{});pages=v.get('pages','00–00');combined=v.get('combined','00–00');name=item['stem']+'.pdf'
    index+=f"- **{spec['source']}** — questions associées 关联小问：{spec['parts']}。\n\n  Corrigé complet 完整题解：[《{item['stem']}》](pdf/{name})；pages du fascicule 分册第 **{pages}** 页；pages du recueil 合订本第 **{combined}** 页。\n\n"
   pos=s.index('\n\n')+2;s=s[:pos]+index+s[pos:]
  p.write_text(s)
 (root/'sources/cross_reference_manifest.json').write_text(json.dumps(SPECS,ensure_ascii=False,indent=2))
def update_locations(root=R):
 from pypdf import PdfReader
 docs=json.loads((root/'sources/documents.json').read_text());items=json.loads((root/'sources/exercise_manifest.json').read_text())
 manifest=json.loads((root/'sources/page_manifest.json').read_text());starts={x['stem']:x['combined_first'] for x in manifest}
 compact=lambda s:re.sub(r'\s+','',unicodedata.normalize('NFKC',s))
 loc={}
 for stem,title in docs:
  pdfpath=root/'pdf'/(stem+'.pdf');pages=PdfReader(pdfpath).pages
  raw=subprocess.check_output(['pdftotext',str(pdfpath),'-']).decode();texts=[compact(t) for t in raw.split('\f')[:len(pages)]]
  local=[x for x in items if x['stem']==stem];first=[]
  for item in local:
   hits=[i+1 for i,t in enumerate(texts) if compact(item['title']) in t];assert len(hits)==1,(item['key'],hits)
   first.append(hits[0])
  for i,item in enumerate(local):
   a=first[i];b=first[i+1] if i+1<len(local) else len(pages)
   # If the following exercise begins at the top of a fresh page, exclude that page.
   if i+1<len(local):
    nexttitle=compact(local[i+1]['title']);prefix=texts[b-1].split(nexttitle)[0]
    prefix=re.sub(r'EDPExercicesclassésetcorrigés','',prefix)
    if not prefix.strip():b-=1
   assert b>=a
   c=a+starts[stem]-1;d=b+starts[stem]-1
   loc[item['key']]=dict(stem=stem,pages=str(a) if a==b else f'{a}–{b}',combined=str(c) if c==d else f'{c}–{d}')
 p=root/'sources/exercise_locations.json';old=p.read_text() if p.exists() else '';new=json.dumps(loc,ensure_ascii=False,indent=2);p.write_text(new)
 print('Exercise page references:',len(loc),'changed:',new!=old)
 return new!=old
if __name__=='__main__':
 if len(sys.argv)>1 and sys.argv[1]=='update':update_locations()
 else:apply()
