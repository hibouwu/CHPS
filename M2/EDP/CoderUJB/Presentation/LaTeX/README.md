# CoderUJB — 法语演示稿与第三部分讲稿

## 当前文件

- [完整演示 PDF（32 页）](CoderUJB_Presentation_FR.pdf)
- [第三部分 PDF（总稿第 14–17 页）](CoderUJB_Partie3_FR.pdf)
- [完整演示 LaTeX 源码](CoderUJB_Presentation_FR.tex)：包含六部分正文和隐藏的演讲备注；第三部分幻灯片在同一份源码中维护。
- 第三部分讲稿：[法语](CoderUJB_Partie3_Script_FR.md) · [中文](CoderUJB_Partie3_Script_ZH.md) · [中法双语](CoderUJB_Partie3_Script_FR_ZH.md)
- [法语讲稿 LaTeX 源码](CoderUJB_Partie3_Script_FR.tex)：需要打印版时可重新编译。

`assets/coderujb-figure2a-context-fr.pdf` 是第 14 页使用的矢量图片资源，编译时必须保留。它不是额外的演示稿。

## 内容与版式

六位演讲者依次为 Wei WEI、Hao QIAN、Jianye SHI、Xiang BIAN、Zijie Fang、Yupan Huang。采用白底、蓝色标题、独立封面与目录、六张分段页和简单页码。没有已确认的小组编号。

其他五位同学的部分采用整体润色前的表达，其中包含他们提交的第一、四、五部分更新。第 26 页结语按要求为“Pas être généralisés à tous les cas.”。

第三部分采用调整后的图表和简单法语讲稿：第 14 页为论文图 2(a) 的法语旁注摘录，第 15 页比较模型，第 16 页用横向条形图比较任务，第 17 页说明缺陷检测的准确率与基线。法语讲稿约 374 词。数据来自论文，未重新运行实验。

## 编译与打包

使用 pdfLaTeX / TeX Live，包含 Beamer、French Babel、Latin Modern、Booktabs 和 TikZ。上传 Overleaf 时保留 `assets/`。

```sh
make
```

该命令重新编译总稿。第三部分 PDF 从总稿第 14–17 页导出，内容在总稿源码中修改，避免维护两套幻灯片源码。

法语讲稿需要 PDF 时，可执行：

```sh
latexmk -pdf -interaction=nonstopmode -halt-on-error CoderUJB_Partie3_Script_FR.tex
```

`make clean` 清理总稿编译缓存；`make package` 生成交付 ZIP。原始来稿保存在 [Sources](../Sources/README.md)。

## 目录整理（2026-11-05）

当前目录仅保留两份演示 PDF、编辑源码、三种语言形式的讲稿与编译必需资源。第一、四、五部分单独 PDF、法语讲稿生成 PDF、未使用的英文旁注图片和旧文件名的编译缓存已清理。历史修订说明及清理前文件有仓库外备份，位置记录在 `../../sources.json`。

## 现场口语讲稿（2026-11-06）

第三部分讲稿按“上下文效果、模型差距、任务条件、缺陷检测与交棒”重写，法语、中文、中法对照与 LaTeX 备注同步。完整数据与额外限定放入备讲问答。幻灯片可见内容和两份演示 PDF 保持不变。正文词数不包含问答，实际时长需排练计时。

当前采用用户提供的短稿，正文目标为 3 分 15 秒至 3 分 30 秒，具体以排练计时为准；保留 8 个备讲问答。
