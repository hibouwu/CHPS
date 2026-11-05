# CoderUJB — 法语汇报 LaTeX 版

- [演示 PDF（32 页）](CoderUJB_Equipe6_FR.pdf)
- [LaTeX Beamer 源码](CoderUJB_Equipe6_FR.tex)
- [第五部分单独版（4 页，沿用总稿页码 24–27）](CoderUJB_Partie5_FR.pdf)

## 内容和版式

以现有法语 PPT 为基础，总共 32 页：第 1 页是总封面，第 2 页是目录，之后按六位演讲者分段，每段先放一张分段首页，包含 1–6 的段落编号、主题与姓名。目录仅列出六段的编号和主题，不显示姓名。正文标题不加序号。原来的四张开场正文完整保留在第 4–7 页，其讲稿备注也恢复到对应正文页。第二张正文采用“栏目标题—解释文字—两条并列要点”的层级；第三、四张正文恢复原稿的横排任务与三项对照结构。版式按用户指定的 `sildeS2Groupe1.pdf` 调整，采用其对应 `rapportS2_beamer.tex` 中的原生 Beamer 设置：16:9 白底、Latin Modern 无衬线字体、与正文左边缘对齐并增加顶部留白的蓝色标题、黑色正文、蓝色三角列表标记。

参考文件：`/home/jianyeshi/Note/ppn-mnist-neural-network/ProjetRapportlatex/sildeS2Groupe1.pdf`。仅采用排版设置，不导入参考项目的内容、作者或标识。

底部仅显示 1 至 32 的页码，没有来源栏、关键词、作者栏和导航图标。原 PPT 的讲稿、来源和说明保留在每页的 `\note{...}` 中，默认通过 `hide notes` 隐藏，不计入这 32 页。

本次为版式重制；正文数字沿用原汇报，未重新运行论文实验。原 PPT 与讲稿 PDF 位于上一层目录。

## 汇报人顺序

1. Wei WEI：第 3 页为分段首页，第 4–7 页为正文。
2. Hao QIAN：第 8 页为分段首页，第 9–12 页为正文。
3. Jianye SHI：第 13 页为分段首页，第 14–17 页为正文。
4. Xiang BIAN：第 18 页为分段首页，第 19–22 页为正文。
5. Zijie Fang：第 23 页为分段首页，第 24–27 页为正文。
6. Yupan Huang：第 28 页为分段首页，第 29–32 页为正文。

姓名及顺序由用户确认，讲稿备注也已标注对应姓名，并更新为新页码。总封面与目录不属于新增的六张分段首页；原 PPT 和讲稿 PDF 保留原有页码。

## 编译

需要 TeX Live 或 MiKTeX，包含 Beamer、Babel French、Booktabs、Latin Modern 与 T1 字体。源码不依赖外部图片或私有字体。

在此目录执行：

```sh
make
```

或：

```sh
latexmk -pdf -interaction=nonstopmode -halt-on-error CoderUJB_Equipe6_FR.tex
```

也可将 `.tex` 上传到 Overleaf，选择 pdfLaTeX 编译。`make clean` 清理编译辅助文件。

## 第五部分内容更新（2026-11-05）

按用户提供的 `CoderUJB_Partie5_Slides17-20_Simplifiees.pdf` 更新第五部分四张正文，对应总稿第 24–27 页，采用简化后的标题、要点和结语。参考 PDF 已归档在上一层目录。采用现有统一的蓝色标题和白底版式，讲稿备注经核对与新要点一致。总稿仍为 32 页，逐页渲染比较确认变化仅在这四页。第五部分单独版保留总稿页码，供单独分享。

## 第三部分口语化更新（2026-11-05）

第 14–17 页的标题、说明和讲稿采用更简单的法语。第 15 页标题改为 `Un écart plus marqué en réparation`，讲稿直接解释不同任务的分数差距。第三部分讲稿约 287 词，实际时长需按数字读法与停顿计时。所有表格百分比逐页核对一致。完整 PDF 渲染差异仅在第 14–17 页。

- [第三部分单独版](CoderUJB_Partie3_FR.pdf)
- [法语讲稿 PDF（每页对应一张幻灯片）](CoderUJB_Partie3_Script_FR.pdf)
- [法语讲稿 Markdown](CoderUJB_Partie3_Script_FR.md)

独立讲稿与完整演示稿的第三部分备注一致。讲稿 PDF 可从同名 `.tex` 用 pdfLaTeX 编译。
