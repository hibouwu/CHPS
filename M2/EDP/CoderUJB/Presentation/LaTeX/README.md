# CoderUJB — 法语汇报 LaTeX 版

- [演示 PDF（32 页）](CoderUJB_Presentation_FR.pdf)
- [LaTeX Beamer 源码](CoderUJB_Presentation_FR.tex)
- [第五部分单独版（4 页，沿用总稿页码 24–27）](CoderUJB_Partie5_FR.pdf)

## 内容和版式

以现有法语 PPT 为基础，总共 32 页：第 1 页是总封面，第 2 页是目录，之后按六位演讲者分段，每段先放一张分段首页，包含 1–6 的段落编号、主题与姓名。目录仅列出六段的编号和主题，不显示姓名。正文标题不加序号。原来的四张开场正文完整保留在第 4–7 页，其讲稿备注也恢复到对应正文页。第二张正文采用“栏目标题—解释文字—两条并列要点”的层级；第三、四张正文恢复原稿的横排任务与三项对照结构。版式按用户指定的 `sildeS2Groupe1.pdf` 调整，采用其对应 `rapportS2_beamer.tex` 中的原生 Beamer 设置：16:9 白底、Latin Modern 无衬线字体、与正文左边缘对齐并增加顶部留白的蓝色标题、黑色正文、蓝色三角列表标记。

参考文件：`/home/jianyeshi/Note/ppn-mnist-neural-network/ProjetRapportlatex/sildeS2Groupe1.pdf`。仅采用排版设置，不导入参考项目的内容、作者或标识。

底部仅显示 1 至 32 的页码，没有来源栏、关键词、作者栏和导航图标。原 PPT 的讲稿、来源和说明保留在每页的 `\note{...}` 中，默认通过 `hide notes` 隐藏，不计入这 32 页。

本次为版式重制；正文数字沿用原汇报，未重新运行论文实验。原 PPT、原讲稿和同学更新稿统一存放在 `../Sources/`。

## 汇报人顺序

1. Wei WEI：第 3 页为分段首页，第 4–7 页为正文。
2. Hao QIAN：第 8 页为分段首页，第 9–12 页为正文。
3. Jianye SHI：第 13 页为分段首页，第 14–17 页为正文。
4. Xiang BIAN：第 18 页为分段首页，第 19–22 页为正文。
5. Zijie Fang：第 23 页为分段首页，第 24–27 页为正文。
6. Yupan Huang：第 28 页为分段首页，第 29–32 页为正文。

姓名及顺序由用户确认，讲稿备注也已标注对应姓名，并更新为新页码。总封面与目录不属于新增的六张分段首页；原 PPT 和讲稿 PDF 保留原有页码。

## 编译

需要 TeX Live 或 MiKTeX，包含 Beamer、Babel French、Booktabs、Latin Modern 与 T1 字体。源码使用 `assets/` 下的论文原图截取，编译或上传 Overleaf 时需保留该目录；无需私有字体。

在此目录执行：

```sh
make
```

或：

```sh
latexmk -pdf -interaction=nonstopmode -halt-on-error CoderUJB_Presentation_FR.tex
```

也可将 `.tex` 上传到 Overleaf，选择 pdfLaTeX 编译。`make clean` 清理编译辅助文件。

## 第五部分内容更新（2026-11-05）

按用户提供的 `CoderUJB_Partie5_Slides17-20_Simplifiees.pdf` 更新第五部分四张正文，对应总稿第 24–27 页，采用简化后的标题、要点和结语。参考 PDF 已归档在 `../Sources/`。采用现有统一的蓝色标题和白底版式，讲稿备注经核对与新要点一致。总稿仍为 32 页，逐页渲染比较确认变化仅在这四页。第五部分单独版保留总稿页码，供单独分享。

## 第三部分口语化更新（2026-11-05）

第 14–17 页的标题、说明和讲稿采用更简单的法语。第 15 页标题改为 `Un écart plus marqué en réparation`，讲稿直接解释不同任务的分数差距。第三部分讲稿约 287 词，实际时长需按数字读法与停顿计时。所有表格百分比逐页核对一致。完整 PDF 渲染差异仅在第 14–17 页。

- [第三部分单独版](CoderUJB_Partie3_FR.pdf)
- [法语讲稿 PDF（每页对应一张幻灯片）](CoderUJB_Partie3_Script_FR.pdf)
- [法语讲稿 Markdown](CoderUJB_Partie3_Script_FR.md)
- [中文演讲稿 Markdown](CoderUJB_Partie3_Script_ZH.md)

独立讲稿与完整演示稿的第三部分备注一致。讲稿 PDF 可从同名 `.tex` 用 pdfLaTeX 编译。

## 第四部分同步同学更新版（2026-11-05）

按 [同学第四部分更新稿](../Sources/CoderUJB_Equipe6_FR_Training_Updated.pptx) 第 13–16 页同步第四部分，对应总稿第 19–22 页。采用更新版的标题、RQ3/RQ4 说明、StarCoder 语言取舍图、表 5 的语法与编译数据以及总结内容。沿用当前 LaTeX 蓝色标题、白底和简单页码格式；图表用 LaTeX 排版，两个条形图采用相同的线性比例。讲稿备注补上新增数据的解释，并保留 APR 在 k=1 与 k=10 时表现不同的提醒。

- [第四部分单独版（4 页，沿用总稿页码 19–22）](CoderUJB_Partie4_FR.pdf)

总稿仍为 32 页，逐页渲染比较确认仅第 19–22 页变化。其他章节的 LaTeX 内容保持原样。

## 打包与来源

原始来稿见 [Sources 索引](../Sources/README.md)。ZIP 为可生成的交付件，不再作为日常维护文件保存；需要分享完整 LaTeX 材料时运行 `make package`，将在上一层生成 `CoderUJB_Presentation_LaTeX.zip`。

第三部分中法讲稿：[Markdown](CoderUJB_Partie3_Script_FR_ZH.md)。

## 封面与第一部分更新（2026-11-05）

按 [五页来稿](../Sources/CoderUJB_Premieres5Pages_FR.pdf) 更新总稿第 1、4–7 页：封面采用简短法语题名、Zeng et al. 与课程名称；正文补齐 LLM 用途、阅读与执行的区别、HumanEval 和真实项目对照、多任务评估局限及研究问题。保留已有讲稿，内容与更新页对应。

来稿将封面和五项简要目录合在一页；总稿沿用已确认的独立封面、独立六段目录和六位演讲者分段页，不更改后续章节页码。仍为 32 页，沿用蓝色标题、白底和简单页码格式。

- [封面与第一部分单独版（5 页，保留总稿页码 1、4–7）](CoderUJB_Partie1_FR.pdf)

验证：无排版溢出；第二部分起的 LaTeX 内容及全部讲稿保持原样。其他页文字一致，仅部分字形的 PDF 编码舍入产生不超过 0.03 pt 的微小坐标差异。

## Révision du français / 法语表达修订（2026-11-05）

依据本地 `humanizer`、`academic-humanizer` 技能和论文中英对照文档修订全部正文页面及讲稿备注。去掉重复的引入与收尾、泛泛的评价和口号式标题，保留能说明任务、数据和限制的表述。第 22 页改为“L’effet de l’entraînement dépend de la tâche”；第 31 页直接说明 GPT-4 的 ITG 数值在正文与表格之间不一致。

三类有效性威胁、真实任务分类和有依据的比较均保留。表格数字、百分比、模型名称和来源不变；CTG 的成功条件按论文第 3.5 节补充为测试可执行并覆盖被测代码。第三部分保持此前的简短表达，仅微调第 16 页讲稿；中法 Markdown、法语 PDF 与 LaTeX 备注同步。

总稿仍为 32 页，六位演讲者与分段顺序不变。各部分单独 PDF 已从当前总稿重新导出。第三部分讲稿当前约 297 词，实际时长以排练为准。编译无溢出，逐页核对百分比及全部表格数值一致。

## 第 14 页加入论文原图（2026-11-05）

上半页使用论文图 2(a) 的上下文局部，展示 Import、Field 和 Signature Context；下半页保留 CodeLlama-13B 的结果表，数值为 12.84%、14.50%、21.91%。原图仅用于说明上下文包含什么，不将图 2(a) 的对话格式当作 CodeLlama 基础模型的实际调用格式。图下标注论文来源和截取范围。

图像资源为 `assets/coderujb-figure2a-context.pdf`，从原论文 PDF 第 5 页裁切生成并保留矢量文字。`make package` 会将 `assets/` 一起打包；上传 Overleaf 时也需保留此目录。法语、中法及中文讲稿已同步调整开头，先解释图中内容，再讲结果。总稿 32 页，渲染变化仅在第 14 页。

## 第一部分恢复同学版本（2026-11-05）

按用户要求，以 `CoderUJB_Premieres5Pages_FR(1).pdf` 为准，恢复第 4–7 页在法语润色前的措辞和讲稿。该文件与 `Sources/CoderUJB_Premieres5Pages_FR.pdf` 内容及字节一致。第一部分不再采用上述“法语表达修订”中的改写；总封面、六段目录、分段页以及第二部分起的内容保留。总稿与第一部分单独 PDF 已同步。
