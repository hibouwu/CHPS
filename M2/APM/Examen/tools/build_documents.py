#!/usr/bin/env python3
"""Export the single French-Chinese exam document."""
from pathlib import Path
import json
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]

def export():
    stem = 'APM_CC1_2025'
    source = ROOT / f'{stem}.md'
    text = source.read_text()
    title, body = text.split('\n', 1)
    body = '\\clearpage\n' + body
    body = body.replace('\n## V ', '\n\\clearpage\n\\begingroup\\small\n\n## V ', 1)
    body += '\n\\endgroup\n'
    metadata = {
        'title': title.removeprefix('# '),
        'date': 'Français / 中文',
        'documentclass': 'article', 'fontsize': '11pt', 'papersize': 'a4',
        'geometry': ['top=20mm', 'bottom=20mm', 'left=18mm', 'right=18mm'],
        'mainfont': 'DejaVuSerif.ttf',
        'mainfontoptions': ['Path=/usr/share/fonts/dejavu-serif-fonts/',
                            'BoldFont=DejaVuSerif-Bold.ttf', 'ItalicFont=DejaVuSerif-Italic.ttf',
                            'BoldItalicFont=DejaVuSerif-BoldItalic.ttf'],
        'monofont': 'LiberationMono-Regular.ttf',
        'monofontoptions': ['Path=/usr/share/fonts/liberation-mono-fonts/',
                            'BoldFont=LiberationMono-Bold.ttf', 'ItalicFont=LiberationMono-Italic.ttf',
                            'BoldItalicFont=LiberationMono-BoldItalic.ttf', 'Scale=0.9'],
        'CJKmainfont': 'NotoSansCJK-Regular.ttc',
        'CJKoptions': ['Path=/usr/share/fonts/google-noto-sans-cjk-fonts/',
                       'FontIndex=2', 'BoldFont=NotoSansCJK-Bold.ttc'],
        'colorlinks': True, 'linkcolor': 'teal', 'urlcolor': 'teal',
        'toc-title': 'Table des matières / 目录',
    }
    out = ROOT / 'output' / 'pdf' / f'{stem}.pdf'
    out.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix='apm-cc1-') as td:
        tmp = Path(td)
        (tmp/'body.md').write_text(body)
        (tmp/'metadata.json').write_text(json.dumps(metadata, ensure_ascii=False))
        cmd = ['pandoc',str(tmp/'body.md'),'--standalone','--from=markdown-implicit_figures',
               '--pdf-engine=xelatex','--toc','--toc-depth=2',
               '--shift-heading-level-by=-1','--metadata-file',str(tmp/'metadata.json'),
               '--include-in-header',str(ROOT/'tools/pdf_header.tex'),
               '--lua-filter',str(ROOT/'tools/pdf_links.lua'),
               '--resource-path',str(ROOT),'-o',str(out)]
        result = subprocess.run(cmd,cwd=ROOT,text=True,capture_output=True)
        (out.parent/f'{stem}.log').write_text(result.stdout+result.stderr)
        if result.returncode:
            raise RuntimeError(result.stderr[-6000:])
    print(out)

if __name__ == '__main__':
    export()
