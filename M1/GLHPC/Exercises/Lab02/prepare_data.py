from pathlib import Path
import gzip, hashlib, shutil
ROOT = Path(__file__).resolve().parent
FILES = [('images/image1.bmp.gz', 'images/image1.bmp', '51844ba6e849e273fa907b4e143594c6fc967e50187903ed41af5af9c6610344'), ('scripts/reference.bmp.gz', 'scripts/reference.bmp', '70a43d9386b182ce4e208d601cb8f1f0a54f40fba32365f56ecefbe6fcaf7e12')]
for packed, output, expected in FILES:
    target = ROOT / output
    if target.exists():
        with target.open('rb') as f:
            assert hashlib.file_digest(f, 'sha256').hexdigest() == expected, target
        continue
    target.parent.mkdir(parents=True, exist_ok=True)
    with gzip.open(ROOT / packed, 'rb') as src, target.open('xb') as dst:
        shutil.copyfileobj(src, dst)
    with target.open('rb') as f:
        assert hashlib.file_digest(f, 'sha256').hexdigest() == expected, target
    print(output)
