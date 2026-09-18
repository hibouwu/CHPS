# M1 import report

复制日期：2026-09-18。

- 复制文件：1400 个（包含 PDF、Markdown、报告源码、演示稿和图片），共 836.3 MiB。
- 每个文件均检查源文件与目标文件 SHA-256 相同；原文件未移动、未修改。
- 原有 53 份手写笔记和试卷路径保留；M2 未复制。
- 新目录使用英文名称：Materials、Supplementary-TechMode、Project-Reviews、Programme。
- 同一课程内保留原子目录，避免重排破坏文档配图。源码仓库、环境、构建缓存、数据集未整体复制。
- 检查 Markdown 常见内联链接、Wiki 图片和 TeX includegraphics，共 661 处本地引用；自动补入 25 个可找到的图片依赖。此检查不是完整 Markdown/TeX 编译验证。
- 发现 3 处远程图片引用，保留原文链接，未核验远端可用性。
- 有 78 处本地引用需注意：有些源目录原本缺文件，有些引用代码/未复制资源。详细清单保存在 SiteCHPS/整合记录/M1链接检查.json。
- 本次复制文件内部发现 46 组 SHA-256 相同的副本。为保留课程原目录与链接关系，未自动删除；完整列表见 M1重复文件.json。
- 复制清单 M1复制清单.json 记录源路径、目标路径、大小和 SHA-256。复制脚本与检查脚本保存在 SiteCHPS/整合记录。

## 本地引用问题摘要

- image / missing-in-source：3 处。
- link / missing-in-source：23 处。
- link / source-exists-not-copied：43 处。
- tex-image / missing-in-source：9 处。

## 使用边界

原文内容未改写；老师课件、转换稿、个人解答和项目报告均保留其原有身份，未逐页重新校对。Markdown 中原有缺图、失效链接和远程图床引用并不因复制而自动修复。项目代码可从课程 README 或 PROJECTS.md 的本机入口进入；换电脑后需要另行配置仓库地址。未运行项目、重编译报告或推送 Git。

## 2026-09-18 大文件分章

AISE 的 lecture.pdf（约 55 MiB）已由 10 个分章 PDF 替代，共保留 302 个实际页面；原始文件仍在 Note/AISE/CM。上述复制统计为分章前历史记录。分章范围与校验值见 SiteCHPS/整合记录/AISE章节切分.json。

## PPN 改为外部仓库入口

按用户要求移除 M1/PPN 资料副本及 PPN 独立复盘副本，README 与项目总览直接链接 https://github.com/hibouwu/ppn-mnist-neural-network。原始 Note/ppn-mnist-neural-network 项目及 Note/PROJECT_PPN_TRAINING_SYSTEMS.md 保留。前述复制数量属于历史记录。

## 官方材料入口

GLHPC 的 5 份 PDF 已从官网补齐；GLHPC、TOP 的教师讲义与实验源码见各课程 Official 目录。版本与来源保存在 Official/SOURCES.json。
