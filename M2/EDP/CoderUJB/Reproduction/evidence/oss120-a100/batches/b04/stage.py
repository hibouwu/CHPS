import concurrent.futures, hashlib, json, os, time, urllib.request
from pathlib import Path
m=json.loads(Path('manifest.json').read_text()); path=Path(os.environ['WEIGHTS']);url='https://huggingface.co/{repo}/resolve/{revision}/{file}'.format(**m)
n=m['size']; block=256*1024**2
fd=os.open(str(path),os.O_CREAT|os.O_RDWR,0o600); os.ftruncate(fd,n)
def load(i):
 a=i*block;b=min(n,a+block)-1;p=a
 for attempt in range(2):
  try:
   req=urllib.request.Request(url+'?chunk='+str(i)+'&start='+str(p),headers={'Range':f'bytes={p}-{b}'})
   with urllib.request.urlopen(req,timeout=75) as r:
    assert r.status==206 and r.headers['Content-Range'].startswith(f'bytes {p}-{b}/'),r.status
    while p<=b:
     buf=r.read(min(1024**2,b-p+1))
     if not buf: raise IOError('short range')
     assert os.pwrite(fd,buf,p)==len(buf);p+=len(buf)
   return i
  except Exception as e:
   if attempt==1: raise
   print('retry',i,attempt,type(e).__name__,flush=True);time.sleep(1+attempt)
with concurrent.futures.ThreadPoolExecutor(max_workers=12) as ex:
 for count,_ in enumerate(concurrent.futures.as_completed([ex.submit(load,i) for i in range((n+block-1)//block)]),1):
  _.result()
  if count%16==0: print('verified HTTP ranges',count,flush=True)
os.close(fd)
h=hashlib.sha256()
with path.open('rb') as f:
 for x in iter(lambda:f.read(8*1024**2),b''): h.update(x)
assert h.hexdigest()==m['sha256']
print('verified full GGUF sha256',h.hexdigest(),flush=True)
