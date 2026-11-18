#!/usr/bin/env python3
"""从 00_all_in_one.md 生成 00_recite.md（背诵版速查），
再把它和 00_calculations.md 合并成 00_print.md（打印版），
并生成只有题目的 00_questions.md（自测版）。

背诵版只保留：主题标题、每道题的标题（含星级）和"最终版答案"。
合集或计算题改过之后重新运行：python3 make_recite.py
"""
import re
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
SRC = HERE / "00_all_in_one.md"
DST = HERE / "00_recite.md"
CALC = HERE / "00_calculations.md"
PRINT = HERE / "00_print.md"
QUESTIONS = HERE / "00_questions.md"
PAGE_BREAK = '\n\n<div style="page-break-after: always;"></div>\n\n'

ANS = "**最终版答案（背诵版 EN，≤5 行）：**"
EXP = "**解析版（小白也能看懂）：**"

HEADER = "# 背诵版速查（{n} 题）\n"


def main() -> int:
    src = SRC.read_text(encoding="utf-8")
    # 从第一个编号主题开始（跳过合集开头的说明和目录）
    start = re.search(r"^## 1\. ", src, re.M)
    if not start:
        sys.exit("找不到 '## 1.' 主题标题")
    body = src[start.start():]

    out, n, problems = [], 0, []
    # 按 "## 主题" 和 "### 题目" 切块
    blocks = re.split(r"^(?=#{2,3} )", body, flags=re.M)
    for block in blocks:
        if block.startswith("## "):
            out.append(block.splitlines()[0])
            continue
        if not block.startswith("### "):
            continue
        title = block.splitlines()[0]
        i = block.find(ANS)
        if i < 0:
            problems.append(title)
            continue
        ans = block[i + len(ANS):]
        j = ans.find(EXP)  # 解析版在答案后面时截断；在前面时 j < 0
        if j >= 0:
            ans = ans[:j]
        ans = re.split(r"^---\s*$", ans, flags=re.M)[0].strip("\n")
        out.append(f"{title}\n\n{ans}")
        n += 1

    if problems:
        sys.exit("以下题目没有找到最终版答案：\n" + "\n".join(problems))

    recite = HEADER.format(n=n) + "\n" + "\n\n".join(out) + "\n"
    DST.write_text(recite, encoding="utf-8")
    print(f"wrote {DST.name}: {n} questions")

    # 自测版：只有主题和题目，没有答案
    titles = [b.split("\n", 1)[0] for b in out]
    QUESTIONS.write_text(
        f"# 自测题（{n} 题，只有题目）\n\n" + "\n\n".join(titles) + "\n",
        encoding="utf-8",
    )
    print(f"wrote {QUESTIONS.name}: {n} questions, no answers")

    # 打印版：背诵版 + 分页 + 计算题（只保留题目和解答）
    calc = calc_questions_and_answers(CALC.read_text(encoding="utf-8"))
    PRINT.write_text(recite.rstrip("\n") + PAGE_BREAK + calc, encoding="utf-8")
    print(f"wrote {PRINT.name}: recite + {CALC.name} (原题 + 解答 only)")
    return 0


KEEP_START = re.compile(r"^\*\*(原题|解答|关键对比)")
DROP_START = re.compile(r"^\*\*(考场英文写法模板|每一步为什么这样做|解题步骤|画法|每一问用到的工具)")


def calc_questions_and_answers(text: str) -> str:
    """计算题只留：标题、题型／年份小标题、原题、解答（含答案图）。"""
    out, keep = [], False
    for line in text.split("\n"):
        if line.startswith("# "):
            out.append(line)
            keep = False
        elif line.startswith("## "):
            keep = False
            if not line.startswith("## 附"):  # 附录小公式不是题目
                out.append(line)
        elif line.startswith("### "):
            out.append(line)
            keep = False
        elif line.startswith("---"):
            keep = False
        elif KEEP_START.match(line):
            keep = True
            out.append(line)
        elif DROP_START.match(line):
            keep = False
        elif line.startswith(">") or "概念，见合集" in line:
            out.append(line)  # 同一道题的其他小问在合集哪一题、题面缺的条件
        elif re.match(r"^!\[.*\]\(\.\./Answers/", line):
            out.append(line)  # 答案图即使写在模板段落里也保留
        elif keep:
            out.append(line)
        elif not line.strip():
            out.append(line)
    # 合并多余空行
    return re.sub(r"\n{3,}", "\n\n", "\n".join(out)).strip("\n") + "\n"


if __name__ == "__main__":
    raise SystemExit(main())
