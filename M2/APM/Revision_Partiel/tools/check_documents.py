#!/usr/bin/env python3
"""Check paired content, local links and the exported PDF structure."""
from pathlib import Path
from urllib.parse import unquote, urlsplit
import json
import re

from markdown_it import MarkdownIt

ROOT = Path(__file__).resolve().parents[1]
parser = MarkdownIt()


def walk(tokens):
    for token in tokens:
        yield token
        if token.children:
            yield from walk(token.children)


def local_links(path):
    links = []
    for token in walk(parser.parse(path.read_text())):
        target = token.attrGet("href") or token.attrGet("src")
        if not target:
            continue
        parts = urlsplit(target)
        if parts.scheme or parts.netloc or not parts.path:
            continue
        resolved = path.parent / unquote(parts.path)
        if not resolved.exists():
            raise AssertionError(f"Broken link in {path}: {target}")
        links.append(target)
    return links


def verify():
    report = {"date": "2026-10-15", "pairs": [], "documents": {}}
    patterns = {
        "heading_numbers": r"^#{2,4}\s+(\d+(?:\.\d+)*)",
        "code_blocks": r"^```[^\n]*\n(.*?)^```",
        "display_formulas": r"\$\$(.*?)\$\$",
    }
    for fr in sorted((ROOT / "sections").glob("*_fr.md")):
        zh = fr.with_name(fr.name.replace("_fr.md", "_zh.md"))
        a, b = fr.read_text(), zh.read_text()
        entry = {"section": fr.stem.removesuffix("_fr")}
        for label, pattern in patterns.items():
            left = re.findall(pattern, a, re.M | re.S)
            right = re.findall(pattern, b, re.M | re.S)
            assert left == right, f"Language mismatch: {fr.name}, {label}"
            entry[label] = len(left)
        report["pairs"].append(entry)
    for language in ["fr", "zh"]:
        path = ROOT / f"APM_Revision_{language}.md"
        text = path.read_text()
        assert text.count("```") % 2 == 0, "Unbalanced code fences"
        assert text.count("$$") % 2 == 0, "Unbalanced display math"
        report["documents"][language] = {
            "local_links_checked": len(local_links(path)),
            "bytes": path.stat().st_size,
        }
        pdf = ROOT / "output" / "pdf" / f"APM_Revision_{language}.pdf"
        if pdf.exists():
            import fitz
            document = fitz.open(pdf)
            assert document.get_toc(), "Missing PDF bookmarks"
            assert all(page.get_text().strip() for page in document), "Empty PDF page"
            assert "\ufffd" not in "".join(page.get_text() for page in document)
            report["documents"][language]["pdf_pages"] = len(document)
            report["documents"][language]["pdf_bookmarks"] = len(document.get_toc())
    local_links(ROOT / "README.md")
    local_links(ROOT.parent / "README.md")
    (ROOT / "verification.json").write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n")
    print(json.dumps(report, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    verify()
