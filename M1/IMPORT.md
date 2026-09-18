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
