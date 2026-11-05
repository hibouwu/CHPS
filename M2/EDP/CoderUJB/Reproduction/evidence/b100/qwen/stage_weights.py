"""Stage and verify pinned files in job-owned RAM, resuming one failed range once."""
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
import hashlib
import os
import urllib.request

def stage_file(item, weights, weight_dir):
    name=item['rfilename']
    n=item['size']; path=weight_dir/name
    url=f"https://huggingface.co/{weights['repo']}/resolve/{weights['revision']}/{name}"
    with path.open('wb') as f:
        fd=f.fileno()
        os.ftruncate(fd,n)
        def part(a):
            b=min(a+128*1024**2,n)-1
            for attempt in range(2):
                try:
                    req=urllib.request.Request(url+f'?range={a}-{b}',headers={'Range':f'bytes={a}-{b}','Accept-Encoding':'identity'})
                    with urllib.request.urlopen(req,timeout=60) as res:
                        if res.status==206:
                            assert res.headers['Content-Range']==f'bytes {a}-{b}/{n}'
                        else: assert res.status==200 and a==0 and b+1==n
                        off=a
                        while off<=b:
                            chunk=res.read(min(2**20,b-off+1))
                            if not chunk:raise OSError('short weight range')
                            assert os.pwrite(fd,chunk,off)==len(chunk)
                            off+=len(chunk)
                    return
                except (OSError,AssertionError):
                    if attempt:raise
        with ThreadPoolExecutor(max_workers=4) as ex:list(ex.map(part,range(0,n,128*1024**2)))
    h=hashlib.sha256()
    with path.open('rb') as f:
        for chunk in iter(lambda:f.read(8*1024**2),b''):
            h.update(chunk)
    if item.get('lfs'):
        assert h.hexdigest()==item['lfs']['sha256']
    else:
        assert hashlib.sha1(f'blob {n}\0'.encode()+path.read_bytes()).hexdigest()==item['blobId']
    return dict(file=name,size=n,sha256=h.hexdigest())


def stage_snapshot(weights, destination):
    destination.mkdir()
    with ThreadPoolExecutor(max_workers=3) as executor:
        return list(executor.map(lambda item:stage_file(item,weights,destination),weights['files']))
