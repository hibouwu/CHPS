"""After an initial render, update cross-reference page numbers until their layout is stable."""
from pathlib import Path
import subprocess,sys,hashlib
from cross_references import update_locations
R=Path(__file__).resolve().parents[1]
for attempt in range(4):
 update_locations(R)
 before={p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in R.glob('0*.md')}
 subprocess.run([sys.executable,str(R/'sources/build_materials.py')],check=True)
 changed=[p.name[:2] for p in R.glob('0*.md') if hashlib.sha256(p.read_bytes()).hexdigest()!=before[p.name]]
 print('Cross-reference pass',attempt+1,'changed booklets:',changed,flush=True)
 if not changed:break
 subprocess.run([sys.executable,str(R/'sources/render_print.py'),*changed],check=True)
else:raise RuntimeError('Cross-reference pagination did not stabilize')
