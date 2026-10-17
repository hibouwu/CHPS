#!/usr/bin/env python3
"""Assemble the paired study guides and export their printable PDF versions."""
from pathlib import Path
import argparse
import json
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
PARTS = ["00_orientation", "01_fondements", "02_cuda", "03_multigpu",
         "03b_openmp", "04_exercices", "05_autotest"]
TITLES = {
    "fr": "APM : Révision du DST",
    "zh": "APM 期中笔试复习讲义",
}
SUBTITLES = {
    "fr": "Cours, exercices corrigés et autoévaluation · 22 octobre 2026",
    "zh": "课程整理、习题解答与考前自测 · 2026 年 10 月 22 日",
}


def build(language, export_pdf=True):
    body = "\n\n".join(
        (ROOT / "sections" / f"{part}_{language}.md").read_text().strip()
        for part in PARTS
    ) + "\n"
    markdown = ROOT / f"APM_Revision_{language}.md"
    markdown.write_text(f"# {TITLES[language]}\n\n{SUBTITLES[language]}\n\n" + body)
    if not export_pdf:
        return
    metadata = {
        "title": TITLES[language],
        "subtitle": SUBTITLES[language],
        "date": "15 octobre 2026" if language == "fr" else "整理日期：2026 年 10 月 15 日",
        "documentclass": "article", "fontsize": "10pt", "papersize": "a4",
        "geometry": ["top=20mm", "bottom=20mm", "left=18mm", "right=18mm"],
        "mainfont": "DejaVuSerif.ttf",
        "mainfontoptions": ["Path=/usr/share/fonts/dejavu-serif-fonts/",
                            "BoldFont=DejaVuSerif-Bold.ttf", "ItalicFont=DejaVuSerif-Italic.ttf",
                            "BoldItalicFont=DejaVuSerif-BoldItalic.ttf"],
        "monofont": "LiberationMono-Regular.ttf",
        "monofontoptions": ["Path=/usr/share/fonts/liberation-mono-fonts/",
                            "BoldFont=LiberationMono-Bold.ttf", "ItalicFont=LiberationMono-Italic.ttf",
                            "BoldItalicFont=LiberationMono-BoldItalic.ttf", "Scale=0.88"],
        "CJKmainfont": "NotoSansCJK-Regular.ttc",
        "CJKoptions": ["Path=/usr/share/fonts/google-noto-sans-cjk-fonts/",
                       "FontIndex=2", "BoldFont=NotoSansCJK-Bold.ttc"],
        "colorlinks": True, "linkcolor": "teal", "urlcolor": "teal",
        "toc-title": "Table des matières" if language == "fr" else "目录",
    }
    out = ROOT / "output" / "pdf" / f"APM_Revision_{language}.pdf"
    out.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix="apm-pdf-") as temp_dir:
        tmp = Path(temp_dir)
        (tmp / "body.md").write_text(body)
        (tmp / "metadata.json").write_text(json.dumps(metadata, ensure_ascii=False))
        command = ["pandoc", str(tmp / "body.md"), "--standalone", "--from=markdown-implicit_figures",
                   "--pdf-engine=xelatex", "--toc", "--toc-depth=2", "--shift-heading-level-by=-1",
                   "--metadata-file", str(tmp / "metadata.json"),
                   "--include-in-header", str(ROOT / "tools" / "pdf_header.tex"),
                   "--lua-filter", str(ROOT / "tools" / "pdf_links.lua"),
                   "--resource-path", str(ROOT), "-o", str(out)]
        result = subprocess.run(command, cwd=ROOT, text=True, capture_output=True)
        log = ROOT / "output" / "pdf" / f"build_{language}.log"
        log.write_text(result.stdout + result.stderr)
        if result.returncode:
            raise RuntimeError(f"PDF generation failed; see {log}\n{result.stderr[-6000:]}")
    print(out)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--language", choices=["fr", "zh", "both"], default="both")
    parser.add_argument("--markdown-only", action="store_true")
    args = parser.parse_args()
    for lang in (["fr", "zh"] if args.language == "both" else [args.language]):
        build(lang, not args.markdown_only)
