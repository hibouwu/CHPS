from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
import zipfile, requests, os, hashlib, shutil
target=Path('/data/jianyeshi/coderujb-reproduction/runtime/defects4j-2.0.1/framework/lib/build_systems/gradle')
for name,n in [('dists',100684048),('deps',45094176)]:
 url='https://defects4j.org/downloads/defects4j-gradle-'+name+'.zip'
 archive=target/('defects4j-gradle-'+name+'.zip')
 with archive.open('wb') as f:
  fd=f.fileno();os.ftruncate(fd,n)
  def fetch(a):
   b=min(n,a+4*1024**2)-1
   for attempt in range(2):
    try:
     r=requests.get(url,headers={'Range':f'bytes={a}-{b}'},timeout=(10,110))
     assert r.status_code==206 and r.headers['Content-Range']==f'bytes {a}-{b}/{n}' and len(r.content)==b-a+1
     assert os.pwrite(fd,r.content,a)==b-a+1
     return
    except Exception:
     if attempt:raise
  with ThreadPoolExecutor(max_workers=4) as pool:list(pool.map(fetch,range(0,n,4*1024**2)))
 with zipfile.ZipFile(archive) as z:
  assert z.testzip() is None
  dest=target/'dists' if name=='dists' else target
  for i in z.infolist():
   assert '..' not in Path(i.filename).parts and not Path(i.filename).is_absolute()
   p=Path(z.extract(i,dest))
   if i.external_attr>>16&0o111:p.chmod(0o755)
 print(name,archive.stat().st_size,hashlib.sha256(archive.read_bytes()).hexdigest(),flush=True)
