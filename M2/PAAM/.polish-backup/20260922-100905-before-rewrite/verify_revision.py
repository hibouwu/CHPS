from pathlib import Path
import re,json,hashlib,difflib,collections
from urllib.parse import unquote,urlsplit
from markdown_it import MarkdownIt
R=Path('/home/jianyeshi/Note/SiteCHPS/CHPS/M2/PAAM/Official/Lectures');B=Path(__file__).resolve().parent
checks={};errors=[];md=MarkdownIt();nlinks=0
for old in sorted(B.glob('*.md')):
 p=R/old.name;a=old.read_text();b=p.read_text()
 fields={
 'headings_and_order':lambda t:re.findall(r'^#{1,6} .+$',t,re.M),
 'fenced_code':lambda t:re.findall(r'```[^\n]*\n.*?```',t,re.S),
 'math':lambda t:re.findall(r'\$\$.*?\$\$|(?<!\$)\$[^$\n]+\$',t,re.S),
 'tables':lambda t:re.findall(r'^\|.*$',t,re.M),
 'links_and_images':lambda t:re.findall(r'!?\[[^]]*\]\([^)]*\)',t),
 'anchors':lambda t:re.findall(r'<a id="[^"]+"></a>',t),
 'self_check':lambda t:t.split('<a id="self-check"></a>')[-1] if 'self-check' in t else ''}
 row={k:f(a)==f(b) for k,f in fields.items()}
 for k,v in row.items():
  if not v:errors.append((old.name,k))
 # Numeric-value multiset differences are a review aid, not automatic failure.
 num=lambda t:collections.Counter(re.findall(r'\d+(?:\.\d+)?',t))
 row['removed_number_occurrences']=dict(num(a)-num(b));row['added_number_occurrences']=dict(num(b)-num(a))
 row['characters_before']=len(a);row['characters_after']=len(b)
 row['current_sha256']=hashlib.sha256(p.read_bytes()).hexdigest()
 checks[old.name]=row
 for t in md.parse(b):
  for c in t.children or []:
   if c.type not in ('image','link_open'):continue
   u=urlsplit(c.attrGet('src' if c.type=='image' else 'href'))
   if u.scheme:continue
   target=(p.parent/unquote(u.path)) if u.path else p;nlinks+=1
   if not target.exists():errors.append(('missing',p.name,str(target)))
   elif u.fragment and f'id="{u.fragment}"' not in target.read_text():errors.append(('anchor',p.name,u.fragment))
 if sum(t.type=='heading_open' for t in md.parse(b))!=len(re.findall(r'^#{1,6} ',b,re.M)):errors.append(('heading_parse',p.name))
 if re.search(r'[\x00-\x08\x0b\x0c\x0e-\x1f]',b):errors.append(('control_char',p.name))
 if re.search(r'!\[[^]]*\]\(https?://',b):errors.append(('remote_image',p.name))
 if b.count('```')%2:errors.append(('fence',p.name))
 if len(re.findall(r'^\$\$$',b,re.M))%2:errors.append(('math_fence',p.name))
protected=json.loads((B/'protected_files.json').read_text());changed=[]
for name,h in protected.items():
 p=R.parents[1]/name
 if hashlib.sha256(p.read_bytes()).hexdigest()!=h:changed.append(name)
assert not changed,changed
report={'backup':str(B),'files':checks,'protected_files_unchanged':len(protected),'local_links_and_anchors_checked':nlinks,'errors':errors}
(B/'revision_validation.json').write_text(json.dumps(report,ensure_ascii=False,indent=2))
diffs=[]
for old in sorted(B.glob('*.md')):diffs.extend(difflib.unified_diff(old.read_text().splitlines(True),(R/old.name).read_text().splitlines(True),fromfile='before/'+old.name,tofile='after/'+old.name))
(B/'revision.diff').write_text(''.join(diffs));print(json.dumps(report,ensure_ascii=False,indent=2))
assert not errors,errors
