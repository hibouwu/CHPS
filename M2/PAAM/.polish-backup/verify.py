#!/usr/bin/env python3
"""Compare backup vs edited Chinese lecture files on the properties that must not change."""
import re, sys, os, collections

BK = os.path.join(os.path.dirname(os.path.abspath(__file__)), "zh")
NW = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                  "Official/Lectures")
FILES = ["01-welcome_zh.md", "01-threads_zh.md", "02-locks_zh.md",
         "03-non-blocking_zh.md", "04-stm_zh.md", "05-numa_zh.md",
         "06-nvmm_zh.md", "README.md"]

FENCE = re.compile(r"^```[^\n]*\n.*?^```[^\n]*$", re.S | re.M)
INLINE = re.compile(r"`[^`\n]+`")
MATHBLOCK = re.compile(r"^\$\$.*?^\$\$", re.S | re.M)
INLINE_MATH = re.compile(r"(?<!\\)\$[^$\n]+\$")
LINK = re.compile(r"\]\(([^)]*)\)")
IMG = re.compile(r"!\[[^\]]*\]\(([^)]*)\)")
ANCHOR = re.compile(r"<a id=\"[^\"]*\"></a>")
NUM = re.compile(r"\d+(?:[.,]\d+)*")
LABEL = re.compile(r"\*\*[^*\n]{0,40}：\*\*")


def feats(p):
    s = open(p, encoding="utf-8").read()
    d = {}
    d["fences"] = FENCE.findall(s)
    d["inline_code"] = INLINE.findall(s)
    d["math_block"] = MATHBLOCK.findall(s)
    d["inline_math"] = INLINE_MATH.findall(s)
    d["links"] = LINK.findall(s)
    d["images"] = IMG.findall(s)
    d["anchors"] = ANCHOR.findall(s)
    d["labels"] = collections.Counter(LABEL.findall(s))
    d["bold_all"] = collections.Counter(re.findall(r"\*\*[^*\n]+\*\*", s))
    d["num_raw"] = collections.Counter(NUM.findall(s))
    d["num_norm"] = collections.Counter(
        x.replace(",", "").replace(".", ".") for x in NUM.findall(s))
    d["lines"] = s.count("\n")
    d["table_rows"] = [l for l in s.split("\n") if l.startswith("|")]
    return d


def cmp(name, a, b, label, soft=False):
    if a == b:
        print(f"  OK   {label}")
        return True
    print(f"  DIFF {label}")
    if isinstance(a, collections.Counter):
        for k in set(a) | set(b):
            if a[k] != b[k]:
                print(f"       -{a[k]} +{b[k]}  {k!r}")
    else:
        for i, (x, y) in enumerate(zip(a, b)):
            if x != y:
                print(f"       idx {i}: -{x!r} +{y!r}")
        if len(a) != len(b):
            print(f"       len {len(a)} -> {len(b)}")
    return soft


ok = True
for f in FILES:
    A, B = feats(os.path.join(BK, f)), feats(os.path.join(NW, f))
    print("=" * 70)
    print(f)
    for key, label in [("fences", "公式/代码块 ```…``` 列表"),
                       ("inline_code", "行内代码 `…` 列表"),
                       ("math_block", "$$ 数学块列表"),
                       ("inline_math", "行内数学 $…$ 列表"),
                       ("links", "链接目标列表"),
                       ("images", "图片路径列表"),
                       ("anchors", "锚点列表"),
                       ("labels", "加粗来源标签 **…：** 多重集")]:
        if not cmp(f, A[key], B[key], label):
            ok = False
    if A["num_raw"] != B["num_raw"]:
        print("  DIFF 数字 token 多重集（原始串）")
        for k in set(A["num_raw"]) | set(B["num_raw"]):
            if A["num_raw"][k] != B["num_raw"][k]:
                print(f"       -{A['num_raw'][k]} +{B['num_raw'][k]}  {k!r}")
        if A["num_norm"] == B["num_norm"]:
            print("  OK   数字 token 多重集（按数值归一后）")
        else:
            print("  FAIL 数字 token 多重集（按数值归一后）也不同")
            ok = False
    else:
        print("  OK   数字 token 多重集（原始串）")
    if not cmp(f, A["lines"], B["lines"], "换行数"):
        ok = False
    print(f"  信息 加粗 span 总数: {sum(A['bold_all'].values())} -> "
          f"{sum(B['bold_all'].values())}")

print("=" * 70)
print("RESULT:", "ALL HARD CHECKS PASS" if ok else "SOME CHECKS FAILED")
sys.exit(0 if ok else 1)
