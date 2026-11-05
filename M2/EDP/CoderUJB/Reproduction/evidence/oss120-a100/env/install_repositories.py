import concurrent.futures, os, zipfile, requests, pathlib, hashlib, json, shutil, subprocess
base=pathlib.Path('/data/jianyeshi/coderujb-reproduction/runtime')
url='https://defects4j.org/downloads/defects4j-repos.zip'
n=439326054
out=base/'defects4j-repos-all.zip'
fd=os.open(out,os.O_CREAT|os.O_RDWR,0o600)
os.ftruncate(fd,n)
def fetch(i):
 a=i*4194304;b=min(n,a+4194304)-1
 for attempt in range(2):
  try:
   r=requests.get(url,headers={'Range':f'bytes={a}-{b}'},timeout=(10,90))
   assert r.status_code==206 and r.headers['content-range']==f'bytes {a}-{b}/{n}' and len(r.content)==b-a+1
   assert os.pwrite(fd,r.content,a)==b-a+1
   return i
  except Exception:
   if attempt: raise
with concurrent.futures.ThreadPoolExecutor(max_workers=6) as pool:
 for j,done in enumerate(concurrent.futures.as_completed([pool.submit(fetch,i) for i in range((n+4194303)//4194304)]),1):
  done.result()
  if j%10==0:print('chunks',j,flush=True)
os.close(fd)
dest=base/'defects4j-2.0.1/project_repos'
stage=base/'archive-verified'
stage.mkdir(exist_ok=True)
with zipfile.ZipFile(out) as z:
 assert z.testzip() is None
 for x in z.infolist():
  name=pathlib.PurePosixPath(x.filename)
  assert '..' not in name.parts and not name.is_absolute()
  if len(name.parts)<3 or name.parts[:2]!=('defects4j','project_repos'): continue
  if name.parts[2] in ('commons-lang.git','README'):continue
  p=stage.joinpath(*name.parts[2:])
  if x.is_dir():p.mkdir(parents=True,exist_ok=True);continue
  p.parent.mkdir(parents=True,exist_ok=True)
  with p.open('wb') as f,z.open(x) as r: shutil.copyfileobj(r,f)
  if x.external_attr>>16 & 0o111:p.chmod(0o755)
 repos=[]
 for p in sorted(stage.iterdir()):
  if p.name.endswith('.git'):
   for x in (p/'refs').rglob('.empty'):
    assert x.stat().st_size==0
    x.unlink()
   r=subprocess.run(['git','-C',str(p),'fsck','--no-dangling'],capture_output=True)
   print(p.name,r.returncode,r.stderr[-900:],flush=True)
   if r.returncode:continue
  if not (dest/p.name).exists():p.rename(dest/p.name)
  repos.append(p.name)
 print('repos',repos,'sha256',hashlib.sha256(out.read_bytes()).hexdigest(),flush=True)
