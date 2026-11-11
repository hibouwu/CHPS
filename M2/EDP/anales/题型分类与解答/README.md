# EDP 题型分类与逐步解答

已核对 TD1、TD3、TD4，以及 2023、2025 两套历年试卷。下表逐项覆盖 24 个来源题组，保留子题；Gustafson 和柱面重复题合并标注来源。每道完整大题只收录一次，放入一个主类别，保留全部题干、数据、小问及答案；跨类别小问在题旁标注关联类别。被关联类别开头只列交叉索引，写明来源、相关小问、完整题解文档及分册／合订本页码。

题目和解答采用法语在前、中文在后，同一行以空格隔开，撇号统一为 ASCII 直撇号。公式与数据表共用。原题数据保留；已有题面中的统计概念错误在方法和答案中订正。题解是经核对的学习答案，不是教师官方标准答案。

## 打印入口

优先打印 [全部题型合订本](pdf/00_全部题型合订本.pdf)，A4、100% 实际尺寸、黑白即可。也可按类别打印下列 PDF。每个类别保留可编辑 Markdown。

| 分类 | 内容 | PDF | 可编辑正文 |
|---|---|---|---|
| 01 | Accélération et vectorisation 加速比与向量化 | [打印版](pdf/01_加速比与向量化.pdf) | [Markdown](01_加速比与向量化.md) |
| 02 | MIPS CPI et benchmarks 指令吞吐与基准比较 | [打印版](pdf/02_指令吞吐与基准比较.pdf) | [Markdown](02_指令吞吐与基准比较.md) |
| 03 | Karp Flatt et passage à l'échelle Karp Flatt 与扩展性 | [打印版](pdf/03_Karp_Flatt与扩展性.pdf) | [Markdown](03_Karp_Flatt与扩展性.md) |
| 04 | Réseaux de files et optimisation 排队网络与资源优化 | [打印版](pdf/04_排队网络与资源优化.pdf) | [Markdown](04_排队网络与资源优化.md) |
| 05 | Intervalles de confiance 置信区间与测量精密度 | [打印版](pdf/05_置信区间与测量精密度.pdf) | [Markdown](05_置信区间与测量精密度.md) |
| 06 | Tests du khi deux 卡方拟合优度检验 | [打印版](pdf/06_卡方拟合优度检验.pdf) | [Markdown](06_卡方拟合优度检验.md) |
| 07 | Kolmogorov Smirnov K S 检验与分布校准 | [打印版](pdf/07_KS检验与分布校准.pdf) | [Markdown](07_KS检验与分布校准.md) |

## 全题覆盖清单

| 来源及题号 | 题型内容 | 分类册 |
|---|---|---|
| TD1 §1.1 | 4% 串行比例 | 01 |
| TD1 §1.2 | 两程序反求串行比例 | 01 |
| TD1 §1.3(a–c) | Amdahl 一般式与问题规模 | 01 |
| TD1 §1.4(a–d) | 向量化与硬件提升 | 01 |
| TD1 §2.1(a–d) | Whetstone 与 CPI | 02 |
| TD1 §2.2(a–e) | 浮点协处理器 | 02 |
| TD1 §3.1 | Gustafson 八处理器 | 01 |
| TD1 §3.2 | Gustafson 十处理器 | 01 |
| TD1 §4.1(a–c) | Cray Karp–Flatt | 03 |
| TD1 §4.2(a–b) | Aliant Karp–Flatt | 03 |
| TD3 ex.1 Q1–6 | 路由、稳定性、时间与复制 | 04 |
| TD3 ex.2 I Q1–3 | 相同磁盘 | 04 |
| TD3 ex.2 II Q1–3 | 异构磁盘与不稳定 | 04 |
| TD4 ex.1 Q1–2 | Student 区间与精密度 | 05 |
| TD4 ex.2 application | 骰子卡方检验 | 06 |
| TD4 ex.3 | 生成器频数卡方检验 | 06 |
| TD4 ex.4 Q1–3 | 指数寿命与拟合参数 K–S | 07 |
| TD4 ex.5 Q1–2 | 离散柱面 K–S 与卡方 | 07 |
| 2023 ex.1 Q1–3 | 双计算单元和双磁盘 | 04 |
| 2023 ex.2 Q1–2 | 基准平均 MIPS 与加速比 | 02 |
| 2023 ex.3 Q1–2 | 柱面数据和检验假设 | 07 |
| 2025 ex.1 Q1–9，含子题 | 四资源替换与收益 | 04 |
| 2025 ex.2 Q1–2 | Gustafson，重复 TD1 §3 | 01 |
| 2025 ex.3 Q1–4 | 均匀生成器 K–S 与卡方 | 07 |

## 使用时注意的答案口径

- 2023 年排队题：到达率 1000 时 Disk1 过载，先处理稳定性，再讨论等待与服务时间比较。
- 2025 年排队题：主解按对系统平均时间的访问加权贡献选资源，先升级 R1，再升级 R4；题面未明确的局部时延口径另列完整计算分支。
- TD3 的 8.33 ms：正文保留题面精度，同时给出先将服务率舍入为 120 时的课堂近似结果。
- Whetstone 每次浮点操作的整数指令成本：区分约 185 条仿真指令的条件性推导，与含背景工作的约 193.20 条总指令摊销。
- K–S：连续已知分布、估计参数后的分布、离散类别分别校准。柱面数据的严格离散结论与连续查表近似分开展示。
- 2025 年均匀生成器卡方题：每组期望频数为 4，除课堂渐近答案外另给多项分布精确尾概率。0.60 归入 [0.6,0.8)。

## 原始资料与复现

原题与现有 TD 答案保留原位。`TD/td1_transcript.md` 是课堂转录，内容对应 TD1 已有题目，没有作为另一套题重复计入；统计表属于参考资料。现有目录没有 TD2，本汇编的覆盖范围是当前实际存在的题目。

- [TD1 原卷](../../TD/td1_metrics.pdf)
- [TD3 原卷](../../TD/TD3_2627.pdf)
- [TD4 原卷](../../TD/td4.pdf)
- [2023 年原题及照片入口](../edp_examen_2023-11-14.md)
- [2025 年原题及照片入口](../edp_examen_2025-11-14.md)
- [数值计算脚本](sources/calculations.py)及[核对结果](sources/verified_results.json)
- [文档生成脚本](sources/build_materials.py)及[排版脚本](sources/render_print.py)

在课程目录内运行（依赖安装在所用 Python 环境中）：

```bash
python3 anales/题型分类与解答/sources/calculations.py
python3 TD/td4_calculs.py
python3 anales/题型分类与解答/sources/build_network_figures.py
python3 anales/题型分类与解答/sources/build_materials.py
python3 anales/题型分类与解答/sources/render_print.py
python3 anales/题型分类与解答/sources/stabilize_print.py
```

最后一步会从已排版 PDF 中读取实际页码，更新索引并重新排版需要变更的分册，直到交叉页码稳定。

计算依赖 NumPy、SciPy；排版依赖 Pandoc、XeLaTeX、Fandol 字体、pypdf、ReportLab。网络图源文件和固定题面摘录保存在 `sources/`。
