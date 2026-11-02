# IMMC 期中考试（CC1）终极开卷实战小抄表（名词定义讲义 + 保姆级分步解题模板）

> **考试基本信息（据 2024–2025 / 2025–2026 真题卷头）**
> - **时长**：1 小时（时间极紧，看到法语关键词直接查本讲义对应章节抄步骤）
> - **允许携带**：纸质版课程讲义（CM）与习题课笔记（TD），禁止使用计算器与电子设备
> - **试卷结构（固定三大题）**：
>   - **Exercice 1（QCM 多选题，10 题）**：每题可能含 **1 个或多个** 正确选项（无全错题），选不全或错选均扣分
>   - **Exercice 2（运动学与变形大题，约 10–11 问）**：围绕一个具体的二维/三维运动场（给出欧拉速度场 $\vec{V}$ 或拉格朗日轨迹 $\vec{\phi}$），从头算到尾
>   - **Exercice 3（应力、平衡方程与屈服准则大题，约 5–6 问）**：围绕薄板拉伸/剪切或圆柱/圆筒扭转/受压，考对称性、平面应力论证、局部平衡方程、边界条件、合力/合力矩积分、Tresca / von Mises 准则与安全系数

---

## 快速目录索引

1. [第一部分：核心名词定义与物理意义讲义（中法对照 + 定义公式 + 物理直觉 + 易混辨析）](#第一部分核心名词定义与物理意义讲义中法对照--定义公式--物理直觉--易混辨析)
   - [1.1 第 1 章：运动学与观测描述（Cinématique）](#11-第-1-章运动学与观测描述cinématique)
   - [1.2 第 2 章：变形、应变张量与变形率（Déformations）](#12-第-2-章变形应变张量与变形率déformations)
   - [1.3 第 3 章：内力、应力张量与强度准则（Contraintes et Critères de limite）](#13-第-3-章内力应力张量与强度准则contraintes-et-critères-de-limite)
   - [1.4 第 4 章：守恒定律、平衡方程与边界条件（Lois de conservation et CL）](#14-第-4-章守恒定律平衡方程与边界条件lois-de-conservation-et-cl)
   - [1.5 第 5–8 章：本构关系、线弹性、黏性流体与能量定理名词](#15-第-58-章本构关系线弹性黏性流体与能量定理名词)
2. [第二部分：常见基本运动全套结果详解与对比](#第二部分常见基本运动全套结果详解与对比)
3. [第三部分：Exercice 1（QCM 多选题）10 大题型逐项秒杀与反例库](#第三部分exercice-1qcm-多选题10-大题型逐项秒杀与反例库)
4. [第四部分：Exercice 2（运动学与变形大题）11 步保姆级解题模板（含法语标准答题句）](#第四部分exercice-2运动学与变形大题11-步保姆级解题模板含法语标准答题句)
5. [第五部分：Exercice 3（应力、平衡与强度校核大题）8 步保姆级解题模板（含法语标准答题句）](#第五部分exercice-3应力平衡与强度校核大题8-步保姆级解题模板含法语标准答题句)
6. [第六部分：微分算子、应变积分求位移与第 5–8 章大题速查](#第六部分微分算子应变积分求位移与第-58-章大题速查)

---

## 第一部分：核心名词定义与物理意义讲义（中法对照 + 定义公式 + 物理直觉 + 易混辨析）

### 1.1 第 1 章：运动学与观测描述（Cinématique）

#### 1. 时间、观察者与物质质点（Temps, Observateur et Particule matérielle）
- **绝对时间与伽利略观察者（Notion de temps et d'observateur galiléen）**：在经典牛顿力学框架下，时间 $t$ 是绝对的（对所有观察者流逝速率相同）。观察者由一个刚体参考系（赋予原点 $\mathcal{O}$ 与右手标准正交基 $(\vec{e}_1, \vec{e}_2, \vec{e}_3)$）及一台时钟定义。若两个观察者的正交基通过正交变换矩阵 $\mathbb{P}$（满足 $\mathbb{P}^T\mathbb{P} = \mathbb{I}, \ \det\mathbb{P} = +1$）联系，则向量坐标变换满足 $\vec{x}' = \vec{x}_0' + \mathbb{P}\cdot\vec{x}$。
- **物质质点与连续性假设（Particule matérielle et Hypothèse du milieu continu）**：连续介质力学研究宏观尺度下的可变形物体，将物体看作由无数个无穷小体积微元组成的连续集合，每个微元称为一个**物质质点（Particule matérielle / Point matériel）**，记为 $M$（其在初始时刻的位置记为 $M_0$）。
  - **物理含义**：在宏观几何上，$M$ 被视为一个没有体积的几何点；但在微观物理上，$M$ 包含海量分子，使得密度、速度、应力等宏观平均物理量在空间上连续可微。
  - **适用条件**：克努森数 $\text{Kn} = \frac{l}{L} \ll 1$（微观分子平均自由程或晶格特征尺寸 $l$ 远小于宏观结构特征尺寸 $L$）。

#### 2. 构型与运动映射（Configurations et Application de mouvement $\vec{\phi}$）
- **初始构型 / 参考构型（Configuration initiale / de référence，$\Omega_0$）**：在初始参考时刻 $t = t_0$（通常取 $t_0 = 0$），连续体在空间中占据的几何区域 $\Omega_0$（未变形基准状态）。质点在 $\Omega_0$ 中的位置坐标用**大写字母**表示：
  $$\vec{X} = (X_1, X_2, X_3)^T \quad (\text{SI 单位：}\text{m})$$
- **当前构型 / 现实构型（Configuration actuelle / courante / déformée，$\Omega_t$）**：在当前时刻 $t$，连续体变形后在空间中实际占据的几何区域 $\Omega_t$。质点在 $\Omega_t$ 中的空间坐标用**小写字母**表示：
  $$\vec{x} = (x_1, x_2, x_3)^T \quad (\text{SI 单位：}\text{m})$$
- **运动映射 / 输运映射（Mouvement / Application de transport，$\vec{\phi}$）**：将质点的初始位置 $\vec{X} \in \Omega_0$ 映射到时刻 $t$ 的空间位置 $\vec{x} \in \Omega_t$ 的函数：
  $$\vec{x} = \vec{\phi}(t, \vec{X}), \qquad \text{满足初始条件 } \vec{\phi}(0, \vec{X}) = \vec{X}$$
  为了保证物质在变形过程中既不相互穿透、也不撕裂或坍缩为零体积，映射 $\vec{X} \mapsto \vec{\phi}(t, \vec{X})$ 在任意时刻 $t$ 都必须是光滑双射（一阶连续可微且可逆），其雅可比行列式严格为正：$J = \det(\nabla_0\vec{\phi}) > 0$。

#### 3. 拉格朗日描述 vs 欧拉描述（Description de Lagrange vs Description d'Euler）
这是连续介质力学最基础的两种观测视角，两者的同类对比如下：

| 对比维度 | 拉格朗日描述（Description de Lagrange） | 欧拉描述（Description d'Euler） |
| :--- | :--- | :--- |
| **核心自变量** | 时间 $t$ 与**初始物质坐标** $\vec{X}=(X_1, X_2, X_3)$：${}^L f(t, \vec{X})$ | 时间 $t$ 与**当前空间坐标** $\vec{x}=(x_1, x_2, x_3)$：${}^E f(t, \vec{x})$ |
| **物理观测直觉** | **追踪特定质点**：像给运动员穿上球衣号码 $\vec{X}$，全程跟着同一个质点跑并记录其状态 | **固定空间探头**：在桥墩固定空间位置 $\vec{x}$ 安装传感器，记录不同时刻流经该点的质点状态 |
| **空间微分算子** | 对初始坐标 $\vec{X}$ 求导：$\overrightarrow{\operatorname{grad}}_0, \ \operatorname{div}_0, \ \frac{\partial}{\partial X_j}$ | 对当前坐标 $\vec{x}$ 求导：$\overrightarrow{\operatorname{grad}}, \ \operatorname{div}, \ \frac{\partial}{\partial x_j}$ |
| **主要应用领域** | **固体力学**（边界清晰，需追踪相对初始未变形构型的总应变） | **流体力学**（流体变形极大且混合剧烈，只关心固定空间域内的流速与压强） |
| **考卷一眼识别法** | 表达式里出现**大写字母** $(X_1, X_2, X_3)$ 或带下标 0 的 $(x_0, y_0, z_0)$ | 表达式里只有**小写字母** $(x_1, x_2, x_3)$ 或 $(x, y, z)$ |

- **两种描述的等价性与互化关系**：通过运动映射 $\vec{x} = \vec{\phi}(t, \vec{X})$ 及其逆映射 $\vec{X} = \vec{\phi}^{-1}(t, \vec{x})$ 进行变量代换：
  $${}^L f(t, \vec{X}) = {}^E f\big(t, \vec{\phi}(t, \vec{X})\big), \qquad {}^E f(t, \vec{x}) = {}^L f\big(t, \vec{\phi}^{-1}(t, \vec{x})\big)$$

#### 4. 迹线、流线（定义 1.1）与脉线（Trajectoire, Ligne de courant, Ligne d'émission）
- **迹线 / 质点轨迹（Trajectoire）**：**固定一个物质质点 $\vec{X} = \vec{X}_0$**，当时间 $t$ 变化时，该质点在空间中走过的真实路径曲线 $\vec{x} = \vec{\phi}(t, \vec{X}_0)$。
  - **求法**：若已知欧拉速度 $\vec{V}(t, \vec{x})$，解常微分方程组 $\frac{\mathrm{d}x_i}{\mathrm{d}t} = V_i(t, x_1, x_2, x_3)$ 并代入初始条件 $x_i(0) = X_i$，最后消去时间参数 $t$ 得到几何方程 $x_2 = f(x_1)$。
- **流线（Ligne de courant，课程讲义定义 1.1）**：**固定某一个时刻 $t$（将时间 $t$ 冻结视为常数）**，流线是该时刻欧拉速度场 ${}^E\vec{V}(t, M)$ 的包络线（即在空间中处处与该时刻瞬时速度向量相切的曲线）。
  - **求法**：由切线微元 $\mathrm{d}\vec{x}$ 平行于速度向量 $\vec{V}(t, \vec{x}) \wedge \mathrm{d}\vec{x} = \vec{0}$ 得到微分方程（积分时把 $t$ 当常数！）：
    $$\frac{\mathrm{d}x_1}{V_1(t, \vec{x})} = \frac{\mathrm{d}x_2}{V_2(t, \vec{x})} = \frac{\mathrm{d}x_3}{V_3(t, \vec{x})}$$
- **脉线 / 染色线（Ligne d'émission）**：在固定时刻 $t$，将历史上所有先后经过同一个固定空间点 $\vec{x}_0$（在 $0 \le \tau \le t$ 某时刻经过 $\vec{x}_0$）的质点在当前时刻 $t$ 的位置连接起来形成的曲线（如烟囱排出的烟雾条、水中滴入墨水形成的墨水线）。
- **单向蕴含关系（讲义备注 1.7 必考辨析）**：若运动为**稳态运动（Mouvement stationnaire）**，则迹线、流线与脉线三者必然重合；**但逆命题不成立（三者重合不能反推出稳态！）**。例如速度方向恒定但大小随时间变化的单向均匀流动 $\vec{V}(t, \vec{x}) = (a(t), 0, 0)$，每个时刻的流线与每个质点的迹线都沿同一水平直线重合，但运动仍是非稳态的。

#### 5. 物质导数 / 随体导数（Dérivée particulaire / matérielle / totale，$\frac{\mathrm{d}}{\mathrm{d}t}$ 或 $\frac{\mathrm{D}}{\mathrm{D}t}$）
- **定义**：跟随同一个物质质点（保持 $\vec{X}$ 不变）运动时，观测到的某个物理量 $f$ 随时间的变化率（讲义备注 1.6 常简记为 $\dot{f}$）。
- **拉格朗日描述下的计算**：因为自变量本来就是 $(t, \vec{X})$，物质导数就是直接对 $t$ 求偏导：
  $$\dot{f} = \frac{\mathrm{d}f}{\mathrm{d}t} = \left.\frac{\partial {}^L f(t, \vec{X})}{\partial t}\right|_{\vec{X}}, \qquad {}^L\vec{V}(t, \vec{X}) = \frac{\partial \vec{\phi}}{\partial t}, \qquad {}^L\vec{\gamma}(t, \vec{X}) = \frac{\partial^2 \vec{\phi}}{\partial t^2}$$
- **欧拉描述下的计算（链式法则展开）**：因为质点位置 $\vec{x}(t) = \vec{\phi}(t, \vec{X})$ 随时间在变，对复合函数 ${}^E f(t, x_1(t), x_2(t), x_3(t))$ 求时间导数必须加上空间迁移项：
  - 对**标量场** $f(t, \vec{x})$：
    $$\dot{f} = \frac{\mathrm{d}f}{\mathrm{d}t} = \frac{\partial f}{\partial t} + \vec{V}\cdot\overrightarrow{\operatorname{grad}} f = \frac{\partial f}{\partial t} + \sum_{j=1}^3 V_j \frac{\partial f}{\partial x_j}$$
  - 对**向量场** $\vec{A}(t, \vec{x})$（特别地，当 $\vec{A}=\vec{V}$ 时即为**欧拉加速度场 $\vec{\gamma}$ 或 $\vec{\Gamma}$**，讲义式 1.27）：
    $$\frac{\mathrm{d}\vec{A}}{\mathrm{d}t} = \frac{\partial \vec{A}}{\partial t} + (\overrightarrow{\operatorname{grad}}\vec{A})\cdot\vec{V}, \qquad \gamma_i = \frac{\mathrm{d}V_i}{\mathrm{d}t} = \frac{\partial V_i}{\partial t} + \sum_{j=1}^3 V_j \frac{\partial V_i}{\partial x_j}$$
  - **对流加速度的旋度分解公式（Formule de Lamb）**：
    $$(\overrightarrow{\operatorname{grad}}\vec{V})\cdot\vec{V} = \frac{1}{2}\overrightarrow{\operatorname{grad}}\big(\|\vec{V}\|^2\big) + (\overrightarrow{\operatorname{rot}}\vec{V})\wedge\vec{V}$$
- **各项物理名称**：
  - $\frac{\partial f}{\partial t}$ 称为**局部导数（Dérivée locale）**，表示空间固定点处物理量随时间的不稳定性；
  - $(\vec{V}\cdot\overrightarrow{\operatorname{grad}})f$ 称为**对流导数 / 迁移项（Terme convectif）**，表示质点运动到空间不同位置所感受到的变化。
- **考试高频陷阱**：在稳态流动（$\frac{\partial \vec{V}}{\partial t} = \vec{0}$）中，局部加速度虽然为 0，但**仍可能存在非零的对流加速度 $(\overrightarrow{\operatorname{grad}}\vec{V})\cdot\vec{V}$，必须实际做矩阵乘向量运算来判断**！注意两个双向陷阱：① 稳态 $\not\Rightarrow \vec{\gamma}=\vec{0}$（如双曲流 $\vec{V}=(\alpha x_1, -\alpha x_2, 0)$ 稳态，但 $\vec{\gamma}=(\alpha^2 x_1, \alpha^2 x_2, 0)\neq\vec{0}$）；② 速度场空间不均匀 $\overrightarrow{\operatorname{grad}}\vec{V}\neq\mathbb{0} \not\Rightarrow (\overrightarrow{\operatorname{grad}}\vec{V})\cdot\vec{V}\neq\vec{0}$（如简单剪切流 $\vec{V}=(\alpha x_2, 0, 0)$ 有 $\overrightarrow{\operatorname{grad}}\vec{V}\neq\mathbb{0}$，但 $(\overrightarrow{\operatorname{grad}}\vec{V})\cdot\vec{V}=\vec{0}$！）。

#### 6. 特殊运动与特殊流动的分类定义（Mouvements et Écoulements particuliers）
- **稳态运动 / 定常流动（Mouvement / Écoulement stationnaire ou permanent）**：
  - **定义**：在**欧拉描述**下，速度场（及所有物理量）不显含时间 $t$：
    $$\frac{\partial {}^E\vec{V}(t, \vec{x})}{\partial t} = \vec{0} \quad \Longleftrightarrow \quad {}^E\vec{V} = \vec{V}(\vec{x})$$
  - **易错点辨析**：判断稳态**必须看欧拉速度 ${}^E\vec{V}(t,\vec{x})$**，绝不能看拉格朗日速度 ${}^L\vec{V}(t,\vec{X})$！例如 $\vec{V}(\vec{x}) = (\alpha x_1, -\alpha x_2, 0)$ 显然不显含 $t$，是稳态流动；但它的拉格朗日速度 ${}^L\vec{V}(t,\vec{X}) = (\alpha X_1 e^{\alpha t}, -\alpha X_2 e^{-\alpha t}, 0)$ 却显含时间 $t$（因为质点流到了速度更快的地方）！
- **均匀运动（Mouvement uniforme）**：速度场在当前空间各点处处相同，不随空间坐标 $\vec{x}$ 变化：$\overrightarrow{\operatorname{grad}}\vec{V} = \mathbb{0}$，即 $\vec{V} = \vec{V}(t)$。
- **平面运动（Mouvement plan）**：存在固定正交坐标系使得所有质点都平行于 $(O, \vec{e}_1, \vec{e}_2)$ 平面运动，且运动状态与第三坐标 $x_3$ 无关：
  $$V_3 = 0 \quad (\text{即 } x_3 = X_3, \ u_3 = 0), \qquad \frac{\partial V_1}{\partial x_3} = \frac{\partial V_2}{\partial x_3} = 0$$
- **不可压缩流动 / 等体积运动（Écoulement incompressible / Mouvement isochore）**：任意随体物质微元的体积在运动过程中保持不变，等价于：
  $$\det(\mathbb{F}) = J = 1 \quad \Longleftrightarrow \quad \operatorname{div}\vec{V} = \operatorname{Tr}(\mathbb{D}) = 0$$
- **无旋流动 / 无旋运动（Écoulement / Mouvement irrotationnel）**：旋转率张量（或速度旋度）处处为零：
  $$\boldsymbol{\Omega} = \mathbb{0} \quad \Longleftrightarrow \quad \overrightarrow{\operatorname{rot}}\vec{V} = \vec{0} \quad (\text{此时存在速度势 } \varphi \text{ 使 } \vec{V} = \overrightarrow{\operatorname{grad}}\varphi)$$
- **层流（Écoulement laminaire，讲义 2.2.4）**：流体微团沿平滑的分层流线作规则有序的滑移运动，相邻流层之间没有宏观横向混合或随机脉动（发生在雷诺数 $\text{Re} = \frac{\rho V L}{\mu}$ 较低时，与**湍流 Écoulement turbulent** 相对）。
- **蠕动流 / Stokes 流动（Écoulement rampant，讲义 2.2.4）**：流速极慢、特征尺度极小或流体黏度极大的流动（雷诺数 $\text{Re} \ll 1$）。此时流体惯性力（对流加速度项 $\rho(\nabla\vec{V})\cdot\vec{V}$）相比于黏性力 $\mu\Delta\vec{V}$ 完全可以忽略不计。
- **刚体运动（Mouvement de corps rigide）**：
  - **定义**：运动过程中，连续体内任意两个质点 $M, N$ 之间的欧氏距离始终保持不变：$\|\vec{x}_M(t)-\vec{x}_N(t)\| = \|\vec{X}_M-\vec{X}_N\|$。
  - **有限运动表达式**：$\vec{x}(t, \vec{X}) = \vec{x}_0(t) + \mathbb{R}(t)\cdot(\vec{X} - \vec{X}_0)$，其中 $\mathbb{R}(t)$ 为正交旋转张量（$\mathbb{R}^T\mathbb{R} = \mathbb{I}, \ \det\mathbb{R} = +1$）。
  - **速度场分布公式（Varignon 等投影公式）**：存在平移速度 $\vec{V}_0(t)$ 和瞬时旋转角速度向量 $\vec{\omega}(t)$（单位：$\text{rad}\cdot\text{s}^{-1}$），使得：
    $$\vec{V}(t, \vec{x}) = \vec{V}(t, \vec{x}_0) + \vec{\omega}(t) \wedge (\vec{x} - \vec{x}_0)$$
  - **考试充要判据**：一个运动是刚体运动 $\iff \mathbb{D} = \mathbb{0}$（变形率张量恒为零）$\iff \mathbb{C} = \mathbb{I}$（右 Cauchy-Green 张量恒为单位阵）$\iff \mathbb{E} = \mathbb{0}$（Green-Lagrange 应变张量恒为零）。

---

### 1.2 第 2 章：变形、应变张量与变形率（Déformations）

#### 1. 位移向量与位移梯度（Vecteur déplacement $\vec{u}$ et Gradient du déplacement $\nabla_0\vec{u}$）
- **定义**：质点从初始位置 $\vec{X}$ 到当前位置 $\vec{x}$ 的位置变化向量称为**位移向量（Vecteur déplacement）**，SI 单位为 $\text{m}$：
  $$\vec{u}(t, \vec{X}) = \vec{x}(t, \vec{X}) - \vec{X} = \vec{\phi}(t, \vec{X}) - \vec{X}, \qquad u_i = x_i - X_i$$
- **位移梯度张量**：对初始坐标 $\vec{X}$ 求梯度得到无量纲二阶张量 $\overrightarrow{\operatorname{grad}}_0\vec{u}$，其分量为 $(\nabla_0\vec{u})_{ij} = \frac{\partial u_i}{\partial X_j}$。

#### 2. 变换梯度张量与雅可比行列式（Tenseur gradient de la transformation $\mathbb{F}$ et Jacobien $J$）
- **变换梯度张量 $\mathbb{F}$（无量纲）**：运动映射 $\vec{\phi}(t, \vec{X})$ 对初始拉格朗日坐标 $\vec{X}$ 的梯度张量：
  $$\mathbb{F}(t, \vec{X}) = \overrightarrow{\operatorname{grad}}_0\,\vec{\phi} = \mathbb{I} + \overrightarrow{\operatorname{grad}}_0\,\vec{u}, \qquad F_{ij} = \frac{\partial x_i}{\partial X_j} = \delta_{ij} + \frac{\partial u_i}{\partial X_j}$$
  - **物理与几何意义**：将初始构型中的无穷小物质有向线段 $\mathrm{d}\vec{X}$ 线性映射为当前构型中的变形后有向线段 $\mathrm{d}\vec{x}$：
    $$\mathrm{d}\vec{x} = \mathbb{F}\cdot\mathrm{d}\vec{X} \quad \Longleftrightarrow \quad \mathrm{d}x_i = \sum_{j=1}^3 \frac{\partial x_i}{\partial X_j}\,\mathrm{d}X_j$$
  - **矩阵写法口诀**：第 $i$ 行对应当前坐标函数 $x_i$，第 $j$ 列对应对初始坐标 $X_j$ 求偏导。注意：$\mathbb{F}$ **一般不对称**，且同时混杂了纯变形与刚体旋转（例如纯刚体旋转时 $\mathbb{F} = \mathbb{R} \neq \mathbb{I}$）。
- **雅可比行列式 / 体积膨胀比（Jacobien / Dilatation volumique，$J$，无量纲）**：
  $$J(t, \vec{X}) = \det(\mathbb{F}) = \frac{\mathrm{d}\Omega_t}{\mathrm{d}\Omega_0} > 0$$
  - **物理意义**：表示当前微元体积 $\mathrm{d}\Omega_t$ 与初始微元体积 $\mathrm{d}\Omega_0$ 的比值。
    - 当 $J = 1$ 时：微元体积不变，称为**等体积运动 / 不可压缩运动（Transformation isochore / Conservation du volume）**；
    - 当 $J > 1$ 时：微元发生体积膨胀（Dilatation volumique）；
    - 当 $0 < J < 1$ 时：微元发生体积压缩（Contraction volumique）。
  - **Euler 雅可比求导恒等式（连接拉格朗日体积比 $J$ 与欧拉速度散度 $\operatorname{div}\vec{V}$ 的核心公式）**：
    $$\frac{\mathrm{d}J}{\mathrm{d}t} = J\,\operatorname{div}\vec{V} = J\,\operatorname{Tr}(\mathbb{D})$$
- **有向面积微元变换公式（Formule de Nanson）**：初始面积微元 $\vec{N}\,\mathrm{d}S_0$ 变形为当前面积微元 $\vec{n}\,\mathrm{d}S_t$ 的关系为：
  $$\vec{n}\,\mathrm{d}S_t = J\,\mathbb{F}^{-T}\cdot\vec{N}\,\mathrm{d}S_0$$

#### 3. 右 Cauchy-Green 伸长算子 $\mathbb{C}$（定义 2.1）与 Green-Lagrange 应变算子 $\mathbb{E}$（定义 2.2）
为什么不能直接用 $\mathbb{F} - \mathbb{I} = \nabla_0\vec{u}$ 度量变形？因为在有限大旋转下，$\mathbb{F} = \mathbb{R} \neq \mathbb{I}$，$\nabla_0\vec{u} \neq \mathbb{0}$，但物体实际上没有发生任何伸长或剪切变形！为了彻底消除刚体旋转 $\mathbb{R}$ 的干扰（利用正交性 $\mathbb{R}^T\mathbb{R} = \mathbb{I}$），我们考察变形后线段长度的平方 $\mathrm{d}s^2 = \|\mathrm{d}\vec{x}\|^2$：
$$\mathrm{d}s^2 = \mathrm{d}\vec{x}\cdot\mathrm{d}\vec{x} = (\mathbb{F}\cdot\mathrm{d}\vec{X})\cdot(\mathbb{F}\cdot\mathrm{d}\vec{X}) = \mathrm{d}\vec{X}\cdot(\mathbb{F}^T\cdot\mathbb{F})\cdot\mathrm{d}\vec{X}$$

- **右 Cauchy-Green 伸长算子（Opérateur des dilatations de Cauchy-Green droit，$\mathbb{C}$，讲义定义 2.1，无量纲）**：
  $$\mathbb{C} = \mathbb{F}^T\cdot\mathbb{F}, \qquad C_{ij} = \sum_{k=1}^3 \frac{\partial x_k}{\partial X_i}\frac{\partial x_k}{\partial X_j}$$
  - **核心性质**：$\mathbb{C}$ 是**对称正定张量**（$\mathbb{C}^T = \mathbb{C}$）。当且仅当运动是刚体运动时，$\mathbb{C} = \mathbb{I}$。
- **Green-Lagrange 变形算子（Opérateur de déformations de Green-Lagrange，$\mathbb{E}$，讲义定义 2.2，无量纲）**：
  衡量变形前后无穷小线段长度平方之差 $\mathrm{d}s^2 - \mathrm{d}s_0^2 = 2\,\mathrm{d}\vec{X}\cdot(\mathbb{E}\cdot\mathrm{d}\vec{X})$：
  $$\mathbb{E} = \frac{1}{2}(\mathbb{C} - \mathbb{I}) = \frac{1}{2}(\mathbb{F}^T\cdot\mathbb{F} - \mathbb{I})$$
  用位移梯度 $\nabla_0\vec{u}$ 展开（含二次非线性项！）：
  $$\mathbb{E} = \frac{1}{2}\left(\overrightarrow{\operatorname{grad}}_0\,\vec{u} + (\overrightarrow{\operatorname{grad}}_0\,\vec{u})^T + (\overrightarrow{\operatorname{grad}}_0\,\vec{u})^T\cdot\overrightarrow{\operatorname{grad}}_0\,\vec{u}\right)$$
  $$E_{ij} = \frac{1}{2}\left(\frac{\partial u_i}{\partial X_j} + \frac{\partial u_j}{\partial X_i} + \sum_{k=1}^3 \frac{\partial u_k}{\partial X_i}\frac{\partial u_k}{\partial X_j}\right)$$
  - **核心性质**：$\mathbb{E}$ 是**对称张量**（$\mathbb{E}^T = \mathbb{E}$）。无论变形和旋转多大，当且仅当运动为刚体运动时 $\mathbb{E} = \mathbb{0}$。

#### 4. 伸长比 $\lambda$、剪切角畸变 $\gamma$ 与应变测量方法（Dilatation, Glissement et Mesure des déformations）
- **伸长比（Rapport d'allongement / Dilatation linéaire，$\lambda(\vec{N})$，无量纲）**：初始方向沿单位向量 $\vec{N}$（即 $\mathrm{d}\vec{X} = \mathrm{d}s_0\vec{N}$）的微元线段，变形后的长度 $\mathrm{d}s$ 与原长 $\mathrm{d}s_0$ 之比：
  $$\lambda(\vec{N}) = \frac{\|\mathrm{d}\vec{x}\|}{\|\mathrm{d}\vec{X}\|} = \sqrt{\vec{N}\cdot\mathbb{C}\cdot\vec{N}} = \sqrt{1 + 2\,\vec{N}\cdot\mathbb{E}\cdot\vec{N}}$$
  特别地，沿第 $i$ 个坐标轴方向 $\vec{e}_i$ 的伸长比为：
  $$\lambda_i = \sqrt{C_{ii}} = \sqrt{1 + 2E_{ii}} \quad \Longleftrightarrow \quad E_{ii} = \frac{1}{2}(\lambda_i^2 - 1)$$
- **工程名义线应变（Allongement unitaire）**：定义为单位原长的长度改变量 $\frac{\mathrm{d}s - \mathrm{d}s_0}{\mathrm{d}s_0} = \lambda - 1$。
- **角畸变 / 剪切角（Glissement / Distorsion angulaire，$\gamma$）**：初始相互垂直的两个物质方向 $\vec{N}_1 \perp \vec{N}_2$，变形后夹角变为 $\theta = \frac{\pi}{2} - \gamma$（$\gamma$ 为直角减小的弧度数），则由向量点乘可得：
  $$\sin\gamma = \cos\theta = \frac{(\mathbb{F}\cdot\vec{N}_1)\cdot(\mathbb{F}\cdot\vec{N}_2)}{\|\mathbb{F}\cdot\vec{N}_1\|\,\|\mathbb{F}\cdot\vec{N}_2\|} = \frac{C_{12}}{\sqrt{C_{11}}\sqrt{C_{22}}} = \frac{2E_{12}}{\sqrt{1+2E_{11}}\sqrt{1+2E_{22}}}$$
  这说明：应变张量的**对角元**度量线段的**伸长/缩短**，而**非对角元**度量正交线段之间的**夹角改变（剪切变形）**！
- **应变的数量级与实验测量方法（讲义 2.1.4）**：
  - **数量级**：金属与结构材料在弹性极限内的应变极小，约为 $10^{-4} \sim 10^{-3}$（即 $0.01\% \sim 0.1\%$，完全适用 HPP）；而橡胶/弹性体（Élastomères）或金属塑性成形的大应变可达 $1 \sim 5$（即 $100\% \sim 500\%$，必须用 $\mathbb{E}$）。
  - **三大实验测量手段**：① **引伸计（Extensomètre）**：测量试样标距段宏观伸长量；② **电阻应变片（Jauge d'extensométrie）**：利用金属丝电阻随伸长率线性变化的效应测量局部表面正应变（应变花 Rosette 由 3 个不同方向应变片组成，可测平面应变张量的全部 3 个分量 $\varepsilon_{11}, \varepsilon_{22}, \varepsilon_{12}$）；③ **光学全场测量 / 数字图像相关法（Corrélation d'images numériques, DIC）**与光测弹性法（Photoélasticimétrie）：追踪表面散斑图案变形计算全场应变分布。

#### 5. 小扰动假设（HPP）、小应变张量 $\boldsymbol{\varepsilon}$、小旋转张量 $\boldsymbol{\omega}$ 与变形相容性条件
- **小扰动假设（Hypothèse des Petites Perturbations，简称 HPP）**：同时包含两个小量条件：
  1. **小位移（Petits déplacements）**：位移大小远小于物体特征尺寸 $\|\vec{u}\| \ll L$。因此当前构型与初始构型几乎重合（$\Omega_t \approx \Omega_0, \ \vec{x} \approx \vec{X}$），不再区分拉格朗日梯度与欧拉梯度（$\overrightarrow{\operatorname{grad}}_0 \approx \overrightarrow{\operatorname{grad}}$），物质导数简化为局部偏导（$\frac{\mathrm{d}}{\mathrm{d}t} \approx \frac{\partial}{\partial t}$）。
  2. **小应变与小转动（Petites déformations et petites rotations）**：位移梯度张量的范数远小于 1，即 $\|\overrightarrow{\operatorname{grad}}\vec{u}\| \ll 1$。因此在 $\mathbb{E}$ 中可以略去位移梯度的二次非线性项 $(\nabla\vec{u})^T\cdot\nabla\vec{u}$。
- **位移梯度的加法分解（$\overrightarrow{\operatorname{grad}}\vec{u} = \boldsymbol{\varepsilon} + \boldsymbol{\omega}$）**：在 HPP 下，任意二阶张量 $\overrightarrow{\operatorname{grad}}\vec{u}$ 唯一分解为对称部分 $\boldsymbol{\varepsilon}$ 与反对称部分 $\boldsymbol{\omega}$：
  - **线性化小应变张量（Tenseur des petites déformations / déformations linéarisées，$\boldsymbol{\varepsilon}$，无量纲对称张量）**：
    $$\boldsymbol{\varepsilon}(\vec{u}) = \frac{1}{2}\left(\overrightarrow{\operatorname{grad}}\vec{u} + (\overrightarrow{\operatorname{grad}}\vec{u})^T\right), \qquad \varepsilon_{ij} = \frac{1}{2}\left(\frac{\partial u_i}{\partial x_j} + \frac{\partial u_j}{\partial x_i}\right)$$
    - **对角元 $\varepsilon_{ii}$ 的几何意义**：沿 $\vec{e}_i$ 方向的相对线伸长率 $\varepsilon_{ii} \approx \lambda_i - 1 = \frac{\Delta L_i}{L_{i0}}$。
    - **非对角元 $\varepsilon_{ij}\ (i\neq j)$ 的几何意义**：称为**半滑移角（Demi-glissement）**，等于坐标轴 $\vec{e}_i$ 与 $\vec{e}_j$ 之间直角减小量 $\gamma_{ij}$ 的**一半**，即 $\varepsilon_{ij} \approx \frac{1}{2}\gamma_{ij}$。
    - **迹 $\operatorname{Tr}(\boldsymbol{\varepsilon})$ 的几何意义**：称为**体应变 / 体积膨胀率（Dilatation volumique）**。由 $J = \det(\mathbb{I}+\nabla\vec{u}) \approx 1 + \operatorname{Tr}(\nabla\vec{u})$ 可得：
      $$\frac{\Delta V}{V_0} = \frac{\mathrm{d}\Omega_t - \mathrm{d}\Omega_0}{\mathrm{d}\Omega_0} = J - 1 \approx \operatorname{Tr}(\boldsymbol{\varepsilon}) = \operatorname{div}\vec{u} = \varepsilon_{11} + \varepsilon_{22} + \varepsilon_{33}$$
  - **无穷小旋转张量（Tenseur des petites rotations，$\boldsymbol{\omega}$，无量纲反对称张量）**：
    $$\boldsymbol{\omega}(\vec{u}) = \frac{1}{2}\left(\overrightarrow{\operatorname{grad}}\vec{u} - (\overrightarrow{\operatorname{grad}}\vec{u})^T\right), \qquad \omega_{ij} = \frac{1}{2}\left(\frac{\partial u_i}{\partial x_j} - \frac{\partial u_j}{\partial x_i}\right)$$
    其伴随的**无穷小旋转角向量（Vecteur rotation infinitésimale）**为 $\vec{\theta} = \frac{1}{2}\overrightarrow{\operatorname{rot}}\vec{u}$，满足 $\boldsymbol{\omega}\cdot\mathrm{d}\vec{x} = \vec{\theta}\wedge\mathrm{d}\vec{x}$。
- **变形相容性条件 / 圣维南协调方程（Conditions de compatibilité de Saint-Venant，讲义 2.1.3）**：
  - **物理背景**：位移场 $\vec{u}$ 只有 3 个标量分量，却由偏导生成了对称应变张量 $\boldsymbol{\varepsilon}$ 的 6 个分量。因此随意给定的 6 个函数 $\varepsilon_{ij}(\vec{x})$ 未必能积分出一个单值连续的位移场 $\vec{u}(\vec{x})$（几何上微元变形后拼合不能出现裂缝或重叠）。
  - **充要条件**：在单连通域上，对称张量场 $\boldsymbol{\varepsilon}$ 存在单值连续位移场 $\vec{u}$ 的充要条件是满足如下二阶偏微分方程组（三维共 6 个独立方程，二维平面仅 1 个独立方程）：
    $$\forall i,j,k,l \in \{1,2,3\}, \qquad \frac{\partial^2 \varepsilon_{ij}}{\partial x_k \partial x_l} + \frac{\partial^2 \varepsilon_{kl}}{\partial x_i \partial x_j} - \frac{\partial^2 \varepsilon_{ik}}{\partial x_j \partial x_l} - \frac{\partial^2 \varepsilon_{jl}}{\partial x_i \partial x_k} = 0$$
    $$\text{二维 }(x_1,x_2)\text{ 平面形式：}\qquad \frac{\partial^2 \varepsilon_{11}}{\partial x_2^2} + \frac{\partial^2 \varepsilon_{22}}{\partial x_1^2} = 2\frac{\partial^2 \varepsilon_{12}}{\partial x_1 \partial x_2}$$

#### 6. 主应变与主应变方向（Déformations principales et Directions principales）
- **定义**：因为 $\mathbb{E}$（或 $\boldsymbol{\varepsilon}$）是实对称张量，在任意点都存在一组正交归一特征基 $(\vec{N}_{\text{I}}, \vec{N}_{\text{II}}, \vec{N}_{\text{III}})$，在这组基下应变张量矩阵为**纯对角阵**：
  $$\mathbb{E}\cdot\vec{N}_I = E_I\,\vec{N}_I \quad (\text{或 } \boldsymbol{\varepsilon}\cdot\vec{n}_I = \varepsilon_I\,\vec{n}_I), \qquad I \in \{\text{I}, \text{II}, \text{III}\}$$
  特征值 $E_I$（或 $\varepsilon_I$）称为**主应变（Déformations principales）**，对应的单位特征向量称为**主方向（Directions principales）**。
- **物理意义**：沿着三个主方向的无穷小物质微元线段，在变形后**仍然保持相互垂直（不发生任何剪切角畸变，非对角元为 0）**，只发生纯粹的拉长或缩短！

#### 7. 速度梯度、变形率算子 $\mathbb{D}$（定义 2.3）与旋转率算子 $\boldsymbol{\Omega}$（定义 2.4）
在欧拉描述下，对当前速度场 $\vec{V}(t, \vec{x})$ 求空间梯度得到**速度梯度张量** $\mathbb{L} = \overrightarrow{\operatorname{grad}}\vec{V}$（分量 $L_{ij} = \frac{\partial V_i}{\partial x_j}$，SI 单位为 **$\text{s}^{-1}$**）。将其唯一分解为对称部分 $\mathbb{D}$ 与反对称部分 $\boldsymbol{\Omega}$：
$$\overrightarrow{\operatorname{grad}}\vec{V} = \mathbb{D} + \boldsymbol{\Omega}$$
- **变形速率算子 / 应变率张量（Opérateur taux de déformation，$\mathbb{D}$，讲义定义 2.3，单位 $\text{s}^{-1}$）**：
  $$\mathbb{D} = \frac{1}{2}\left(\overrightarrow{\operatorname{grad}}\vec{V} + (\overrightarrow{\operatorname{grad}}\vec{V})^T\right), \qquad D_{ij} = \frac{1}{2}\left(\frac{\partial V_i}{\partial x_j} + \frac{\partial V_j}{\partial x_i}\right)$$
  - **物理意义**：度量当前构型中微元线段的瞬时伸长速率与正交线段夹角的瞬时改变速率：$\frac{\mathrm{d}}{\mathrm{d}t}(\mathrm{d}s^2) = 2\,\mathrm{d}\vec{x}\cdot(\mathbb{D}\cdot\mathrm{d}\vec{x})$。
  - **与变换梯度 $\mathbb{F}$ 及大应变 $\mathbb{E}$ 的精确联系（讲义 2.2.3）**：
    $$\frac{\mathrm{d}\mathbb{F}}{\mathrm{d}t} = (\overrightarrow{\operatorname{grad}}\vec{V})\cdot\mathbb{F}, \qquad \frac{\mathrm{d}\mathbb{E}}{\mathrm{d}t} = \mathbb{F}^T\cdot\mathbb{D}\cdot\mathbb{F} \quad (\text{在 HPP 下简化为 } \mathbb{D} \approx \frac{\partial \boldsymbol{\varepsilon}}{\partial t})$$
  - **迹的意义**：$\operatorname{Tr}(\mathbb{D}) = \operatorname{div}\vec{V} = \frac{1}{J}\frac{\mathrm{d}J}{\mathrm{d}t}$，代表单位当前体积的瞬时体积膨胀率。
- **旋转速率算子 / 涡量张量（Opérateur taux de rotation，$\boldsymbol{\Omega}$，讲义定义 2.4，单位 $\text{s}^{-1}$）**：
  $$\boldsymbol{\Omega} = \frac{1}{2}\left(\overrightarrow{\operatorname{grad}}\vec{V} - (\overrightarrow{\operatorname{grad}}\vec{V})^T\right), \qquad \Omega_{ij} = \frac{1}{2}\left(\frac{\partial V_i}{\partial x_j} - \frac{\partial V_j}{\partial x_i}\right)$$
  - **伴随瞬时旋转角速度向量（Vecteur tourbillon，$\vec{\omega}$）**：
    $$\vec{\omega} = \frac{1}{2}\overrightarrow{\operatorname{rot}}\vec{V}, \qquad \text{满足 } \boldsymbol{\Omega}\cdot\mathrm{d}\vec{x} = \vec{\omega}\wedge\mathrm{d}\vec{x}$$
    在二维平面运动 $(x_1, x_2)$ 中，$\vec{\omega} = \Omega_{21}\vec{e}_3 = -\Omega_{12}\vec{e}_3 = \frac{1}{2}\left(\frac{\partial V_2}{\partial x_1} - \frac{\partial V_1}{\partial x_2}\right)\vec{e}_3$。

---

### 1.3 第 3 章：内力、应力张量与强度准则（Contraintes et Critères de limite）

#### 1. 力旋量（定义 3.1）、滑动矢量（定义 3.2）与外力分类
- **旋量的定义（Notion de torseur，讲义定义 3.1）**：一个**旋量（Torseur）**是满足**等投影性（Équiprojectivité）**的空间向量场 $M \mapsto \vec{H}(M)$，即对空间任意两点 $A, B$ 满足：
  $$\vec{H}(B)\cdot\overrightarrow{AB} = \vec{H}(A)\cdot\overrightarrow{AB} \quad \Longleftrightarrow \quad \vec{H}(B) = \vec{H}(A) + \vec{R}\wedge\overrightarrow{AB} = \vec{H}(A) + \overrightarrow{BA}\wedge\vec{R}$$
  其中常向量 $\vec{R}$ 称为旋量的**合力 / 主矢（Résultante）**，$\vec{H}(A)$（常记为 $\vec{M}_A$）称为旋量在点 $A$ 处的**合力矩（Moment en $A$）**，旋量记作 $[\mathcal{T}]_A = \{\vec{R}, \vec{M}_A\}$。
- **滑动矢量与力偶（Glisseur et Couple，讲义定义 3.2）**：
  - **滑动矢量（Glisseur）**：至少存在空间一点 $A$ 使其合力矩为零（$\vec{M}_A = \vec{0}$）的旋量（此时若 $\vec{R}\neq\vec{0}$，则力矩在中心轴线 $(A, \vec{R})$ 上所有点处均为零；若 $\vec{R}=\vec{0}$ 且 $\vec{M}_A=\vec{0}$，则为**零旋量 Torseur nul**）。
  - **力偶（Couple）**：合力为零（$\vec{R} = \vec{0}$）但合力矩非零（$\vec{M}_A = \vec{C} \neq \vec{0}$）的旋量（由变基点公式可知，力偶的力矩向量在空间所有点处都相等，与基点 $A$ 的选取无关！）。
- **三类外力载荷（Efforts extérieurs，讲义 3.1.3）**：
  1. **体积力 / 远距力（Efforts volumiques / à distance，$\vec{f}_v$）**：直接作用在物体内部每个体积微元 $\mathrm{d}\Omega$ 上的力（如重力 $\vec{f}_v = \rho\vec{g}$、电磁力），力微元为 $\mathrm{d}\vec{F}_{\text{vol}} = \vec{f}_v\,\mathrm{d}\Omega$，SI 单位是 **$\text{N}\cdot\text{m}^{-3}$（即 $\text{Pa}\cdot\text{m}^{-1}$）**。
  2. **表面力 / 接触力（Efforts surfaciques / de contact，$\vec{T}$）**：作用在物体外边界表面 $\partial\Omega$ 或内部虚拟切面 $\Delta S$ 上的短程相互作用力，力微元为 $\mathrm{d}\vec{F}_{\text{surf}} = \vec{T}\,\mathrm{d}S$，SI 单位是 **$\text{Pa}$（即 $\text{N}\cdot\text{m}^{-2}$）**。
  3. **集中力（Efforts concentrés，$\vec{F}_k$）**：作用在离散几何点 $A_k$ 上的理想化集中载荷，SI 单位是 **$\text{N}$**。

#### 2. Cauchy 基本定理、应力算子 $\boldsymbol{\sigma}(M)$（定义 3.3）与应力向量 $\vec{T}(M, \vec{n})$（定义 3.4）
- **Cauchy 应力向量 / 牵引向量（Vecteur contrainte de Cauchy，$\vec{T}(M, \vec{n})$，讲义定义 3.4，单位 $\text{Pa}$）**：
  在连续体内部任取一点 $M$，用一个以单位向量 $\vec{n}$ 为外法向的虚拟平面切开物体（将物体分为法向指向的外侧 $+$ 和内侧 $-$）。外侧部分通过微元面积 $\Delta S$ 对内侧部分施加的单位面积接触力称为点 $M$ 处方向 $\vec{n}$ 上的**应力向量**（且内力分布局部等效为滑动矢量，无微观分布力偶）：
  $$\vec{T}(M, \vec{n}) = \lim_{\Delta S \to 0} \frac{\Delta \vec{F}_{+\to -}}{\Delta S}$$
  由作用力与反作用力定律，当截面法向反向时，应力向量反向：$\vec{T}(M, -\vec{n}) = -\vec{T}(M, \vec{n})$。
- **Cauchy 基本定理与应力算子（Théorème fondamental de Cauchy et Opérateur des contraintes，$\boldsymbol{\sigma}(M)$，讲义定义 3.3，单位 $\text{Pa}$）**：
  Cauchy 四面体动量平衡定理证明：在给定点 $M$ 处，映射 $\vec{n} \mapsto \vec{T}(M, \vec{n})$ **是线性的**！因此存在一个仅依赖于空间点 $M$（而与切面法向 $\vec{n}$ 无关）的二阶线性算子（张量）$\boldsymbol{\sigma}(M)$，称为点 $M$ 处的**应力算子（Opérateur des contraintes）**，使得：
  $$\vec{T}(M, \vec{n}) = \boldsymbol{\sigma}(M)\cdot\vec{n} \quad \Longleftrightarrow \quad T_i = \sum_{j=1}^3 \sigma_{ij}\,n_j$$
  由微元角动量平衡（力矩平衡）可证明，Cauchy 应力张量必为**对称张量**：
  $$\boldsymbol{\sigma}^T = \boldsymbol{\sigma} \quad \Longleftrightarrow \quad \sigma_{ij} = \sigma_{ji} \quad (\text{仅含 6 个独立分量})$$
- **矩阵分量的物理意义**：
  $$\boldsymbol{\sigma} = \begin{pmatrix} \sigma_{11} & \sigma_{12} & \sigma_{13} \\ \sigma_{21} & \sigma_{22} & \sigma_{23} \\ \sigma_{31} & \sigma_{32} & \sigma_{33} \end{pmatrix}$$
  - **列向量的意义**：矩阵的第 $j$ 列就是以 $\vec{e}_j$ 为外法向的坐标平面上的应力向量 $\vec{T}(M, \vec{e}_j) = \boldsymbol{\sigma}\cdot\vec{e}_j = \sigma_{1j}\vec{e}_1 + \sigma_{2j}\vec{e}_2 + \sigma_{3j}\vec{e}_3$。
  - **下标含义**：在 $\sigma_{ij}$ 中，第一个下标 $i$ 表示**力的投影方向** $\vec{e}_i$，第二个下标 $j$ 表示**作用截面的外法向** $\vec{e}_j$。对角元 $\sigma_{11}, \sigma_{22}, \sigma_{33}$ 是三个坐标面上的**正应力**，非对角元 $\sigma_{12}, \sigma_{23}, \sigma_{13}$ 是坐标面上的**切应力（剪应力）**。

#### 3. 法向应力（定义 3.5）、切向应力（定义 3.6）与 Cauchy 互等定理
在过点 $M$、外法向为 $\vec{n}$（注意必须保证 $\|\vec{n}\|=1$）的截面上，将总应力向量 $\vec{T}(M, \vec{n}) = \boldsymbol{\sigma}\cdot\vec{n}$ 沿法向 $\vec{n}$ 和切平面正交分解：
$$\vec{T}(M, \vec{n}) = \vec{T}_n + \vec{T}_t = \sigma_n\,\vec{n} + \vec{T}_t$$
- **法向应力 / 正应力（Contrainte normale，讲义定义 3.5）**：
  - **正应力标量** $\sigma_n$（代数量，可正可负，单位 $\text{Pa}$）：
    $$\sigma_n = \vec{T}(M, \vec{n})\cdot\vec{n} = \vec{n}\cdot(\boldsymbol{\sigma}\cdot\vec{n}) = \sum_{i,j=1}^3 \sigma_{ij} n_i n_j$$
    - **力学符号约定（讲义 3.2.5）**：若 $\sigma_n > 0$，表示截面受**拉伸（Traction / Extension）**；若 $\sigma_n < 0$，表示截面受**压缩（Compression）**。
  - **正应力向量** $\vec{T}_n$：$\vec{T}_n = \sigma_n\,\vec{n}$。
- **切向应力 / 剪应力（Contrainte tangentielle / Cission，讲义定义 3.6）**：
  - **切应力向量** $\vec{T}_t$（位于截面切平面内，与 $\vec{n}$ 正交，永远用减法计算最快！）：
    $$\vec{T}_t = \vec{T}(M, \vec{n}) - \sigma_n\,\vec{n} = \boldsymbol{\sigma}\cdot\vec{n} - (\vec{n}\cdot\boldsymbol{\sigma}\cdot\vec{n})\,\vec{n}$$
  - **切应力标量（大小）** $\tau$（或记为 $\sigma_t$，单位 $\text{Pa}$）：
    $$\tau = \|\vec{T}_t\| = \sqrt{\|\vec{T}\|^2 - \sigma_n^2}$$
- **应力互等定理（Théorème de réciprocité des contraintes，讲义 3.2.3）**：
  由应力算子 $\boldsymbol{\sigma}$ 的对称性，对过同一点 $M$ 的任意两个截面法向 $\vec{n}_1, \vec{n}_2$，恒有：
  $$\vec{n}_1\cdot\vec{T}(M, \vec{n}_2) = \vec{n}_2\cdot\vec{T}(M, \vec{n}_1) \quad \left(\text{特别地，在正交坐标面上 }\sigma_{ij} = \sigma_{ji}\right)$$

#### 4. 主方向（定义 3.7）与主应力（定义 3.8）
- **定义**：在点 $M$ 处，若某个单位截面法向 $\vec{n}_i$ 上的**切向应力恰好为零**（$\vec{T}_t = \vec{0}$），即应力向量 $\vec{T}(M, \vec{n}_i)$ 与法向 $\vec{n}_i$ 完全共线（截面上只有纯拉或纯压的正应力），则称该方向 $\vec{n}_i$ 为应力的**主方向（Direction principale，讲义定义 3.7）**，对应的正应力实特征值 $\sigma_i$ 称为**主应力（Contrainte principale，讲义定义 3.8）**：
  $$\boldsymbol{\sigma}\cdot\vec{n}_i = \sigma_i\,\vec{n}_i \quad \Longleftrightarrow \quad \det(\boldsymbol{\sigma} - \sigma\mathbb{I}) = 0$$
  因为 $\boldsymbol{\sigma}$ 是 $3\times 3$ 实对称矩阵，必存在 3 个实主应力 $\sigma_1, \sigma_2, \sigma_3$（通常按代数值从大到小排序为 $\sigma_{\text{I}} \ge \sigma_{\text{II}} \ge \sigma_{\text{III}}$）以及一组正交归一的主轴基 $(\vec{n}_{\text{I}}, \vec{n}_{\text{II}}, \vec{n}_{\text{III}})$。
- **三个主不变量（Invariants principaux）**：特征方程 $-\sigma^3 + I_1\sigma^2 - I_2\sigma + I_3 = 0$ 的系数不随坐标系旋转而改变：
  $$I_1 = \operatorname{Tr}(\boldsymbol{\sigma}) = \sigma_1 + \sigma_2 + \sigma_3$$
  $$I_2 = \frac{1}{2}\left[(\operatorname{Tr}\boldsymbol{\sigma})^2 - \operatorname{Tr}(\boldsymbol{\sigma}^2)\right] = \sigma_1\sigma_2 + \sigma_2\sigma_3 + \sigma_3\sigma_1$$
  $$I_3 = \det(\boldsymbol{\sigma}) = \sigma_1\sigma_2\sigma_3$$

#### 5. 球应力张量、静水压力与偏应力张量（Partie sphérique, Pression hydrostatique et Déviateur $\boldsymbol{\sigma}^D$）
任意应力张量 $\boldsymbol{\sigma}$ 都可以唯一分解为各向同性的**球张量部分** $\boldsymbol{\sigma}^S$ 与迹为零的**偏张量部分** $\boldsymbol{\sigma}^D$（讲义中亦记作 $\boldsymbol{s}$）：
$$\boldsymbol{\sigma} = \boldsymbol{\sigma}^S + \boldsymbol{\sigma}^D = -p\,\mathbb{I} + \boldsymbol{\sigma}^D$$
- **球应力张量（Partie sphérique，$\boldsymbol{\sigma}^S$）与静水压力（Pression hydrostatique，$p$）**：
  $$\boldsymbol{\sigma}^S = \frac{1}{3}\operatorname{Tr}(\boldsymbol{\sigma})\,\mathbb{I} = -p\,\mathbb{I}, \qquad \text{其中静水压力 } p = -\frac{1}{3}\operatorname{Tr}(\boldsymbol{\sigma}) = -\frac{\sigma_{11}+\sigma_{22}+\sigma_{33}}{3}$$
  - **物理意义**：代表平均各向同性拉压状态（注意压强的符号与正应力相反：受压时 $\operatorname{Tr}\boldsymbol{\sigma}<0 \implies p>0$）。在各向同性材料中，球张量**只引起体积改变（膨胀或压缩），不改变微元的形状，也不会导致金属塑性屈服**。
- **偏应力张量（Tenseur déviateur des contraintes / Partie déviatorique，$\boldsymbol{\sigma}^D$ 或 $\boldsymbol{s}$）**：
  $$\boldsymbol{\sigma}^D = \boldsymbol{\sigma} - \frac{1}{3}\operatorname{Tr}(\boldsymbol{\sigma})\,\mathbb{I} = \begin{pmatrix} \sigma_{11}+p & \sigma_{12} & \sigma_{13} \\ \sigma_{21} & \sigma_{22}+p & \sigma_{23} \\ \sigma_{31} & \sigma_{32} & \sigma_{33}+p \end{pmatrix}, \qquad \text{恒满足 } \operatorname{Tr}(\boldsymbol{\sigma}^D) = 0$$
  - **物理意义**：滤除静水压力后剩下的应力部分，专门负责引起**形状畸变（剪切变形）**，是延性金属材料发生塑性变形（von Mises 准则）的唯一原因。
  - **秒杀判据**：若一个应力张量本身的迹 $\operatorname{Tr}(\boldsymbol{\sigma}) = \sigma_{11}+\sigma_{22}+\sigma_{33} = 0$，则它的球张量部分为 0（$p=0$），它自己就是一个**纯偏应力张量（Tenseur purement déviatorique，$\boldsymbol{\sigma} = \boldsymbol{\sigma}^D$）**！

#### 6. 常见的特殊应力算子完整定义（定义 3.9 至 定义 3.14 + 双轴与自应力场）
- **球形应力算子（Opérateur sphérique / État hydrostatique，讲义定义 3.9）**：
  $$\boldsymbol{\sigma} = \sigma_0\,\mathbb{I} = -p\,\mathbb{I} = \begin{pmatrix} -p & 0 & 0 \\ 0 & -p & 0 \\ 0 & 0 & -p \end{pmatrix}$$
  此时偏应力 $\boldsymbol{\sigma}^D = \mathbb{0}$，三个主应力相等，空间**任意方向都是主方向**，任意截面上的切应力恒为 0。
- **单轴应力算子 / 简单拉压（Opérateur uniaxial / Traction ou compression simple，讲义定义 3.10）**：只有一个主应力非零，其余两个主应力为 0。沿方向 $\vec{e}_1$ 的单轴应力算子为：
  $$\boldsymbol{\sigma} = \sigma\,\vec{e}_1\otimes\vec{e}_1 = \begin{pmatrix} \sigma & 0 & 0 \\ 0 & 0 & 0 \\ 0 & 0 & 0 \end{pmatrix}$$
- **双轴应力状态（État biaxial）**：恰有两个主应力非零，第三个主应力为 0（即 $\det\boldsymbol{\sigma} = 0$，但二阶主子式不全为 0）。
- **平面型应力算子（Opérateur de type plan / État de contraintes planes，讲义定义 3.11）**：与某一坐标轴（如厚度方向 $\vec{e}_3$ 或讲义中的 $\vec{e}_1$）有关的所有应力分量全为零。在 $(O, \vec{e}_1, \vec{e}_2)$ 平面内的平面应力状态为：
  $$\sigma_{13} = \sigma_{23} = \sigma_{33} = 0 \quad \Longleftrightarrow \quad \boldsymbol{\sigma} = \begin{pmatrix} \sigma_{11} & \sigma_{12} & 0 \\ \sigma_{12} & \sigma_{22} & 0 \\ 0 & 0 & 0 \end{pmatrix}$$
  主要出现在上下表面自由且厚度极薄（$e \ll L$）的**薄板结构（Plaque mince）**中。
- **反平面型应力算子（Opérateur de type antiplan，讲义定义 3.12）**：沿某一轴向（如 $\vec{e}_1$ 或 $\vec{e}_3$）的反平面剪切状态，仅有与该轴相关的两个面外切应力分量非零，三个正应力与面内切应力全为零（沿 $\vec{e}_1$ 方向）：
  $$\boldsymbol{\sigma} = \sigma_{12}(\vec{e}_1\otimes\vec{e}_2 + \vec{e}_2\otimes\vec{e}_1) + \sigma_{13}(\vec{e}_1\otimes\vec{e}_3 + \vec{e}_3\otimes\vec{e}_1) = \begin{pmatrix} 0 & \sigma_{12} & \sigma_{13} \\ \sigma_{12} & 0 & 0 \\ \sigma_{13} & 0 & 0 \end{pmatrix}$$
- **纯剪切应力算子（Opérateur de type cisaillement pur / Cission simple，讲义定义 3.13）**：在 $(\vec{e}_1, \vec{e}_2)$ 平面内对角元全为 0 且仅有一对切应力 $\sigma_{12}=\sigma_{21}=\tau$ 非零：
  $$\boldsymbol{\sigma} = \tau(\vec{e}_1\otimes\vec{e}_2 + \vec{e}_2\otimes\vec{e}_1) = \begin{pmatrix} 0 & \tau & 0 \\ \tau & 0 & 0 \\ 0 & 0 & 0 \end{pmatrix} \quad \left(\text{主轴基下为 } \begin{pmatrix} \tau & 0 & 0 \\ 0 & -\tau & 0 \\ 0 & 0 & 0 \end{pmatrix}\right)$$
  其**充要判据**是：三个主应力为 $(\tau, 0, -\tau)$，即同时满足 $\operatorname{Tr}(\boldsymbol{\sigma}) = 0$ 且 $\det(\boldsymbol{\sigma}) = 0$。
- **圆柱纯扭转应力算子（Opérateur de torsion pure，讲义定义 3.14）**：在圆柱坐标系 $(\vec{e}_r, \vec{e}_\theta, \vec{e}_z)$ 下绕轴线 $\vec{e}_z$ 的纯扭转应力状态，切应力位于 $(\vec{e}_\theta, \vec{e}_z)$ 面上：
  $$\boldsymbol{\sigma} = \tau(\vec{e}_\theta\otimes\vec{e}_z + \vec{e}_z\otimes\vec{e}_\theta) = \begin{pmatrix} 0 & 0 & 0 \\ 0 & 0 & \tau \\ 0 & \tau & 0 \end{pmatrix}_{(\vec{e}_r,\vec{e}_\theta,\vec{e}_z)}$$
- **自应力场 / 残余应力场（Champ d'autocontraintes / Contraintes résiduelles）**：在没有任何外部体积力（$\vec{f}_v=\vec{0}$）且边界完全自由不受外力（$\boldsymbol{\sigma}\cdot\vec{n}=\vec{0}$）的情况下，物体内部依然存在的非零静力平衡应力场（通常由不均匀热膨胀、相变、焊接冷却或局部塑性卸载引起）。

#### 7. 结构强度设计准则：von Mises（定义 3.15）、Tresca（定义 3.16）与 Rankine 准则
为了判断处于复杂三维应力状态 $\boldsymbol{\sigma}$ 下的材料是否达到屈服极限（单轴拉伸弹性极限记为 $\sigma_e$），引入标量**等效应力（Contrainte équivalente，$\sigma_{\text{eq}}$）**。当 $\sigma_{\text{eq}} < \sigma_e$ 时材料处于弹性安全区；当 $\sigma_{\text{eq}} = \sigma_e$ 时达到弹性极限开始屈服。**安全系数（Coefficient de sécurité）**定义为：
$$C_s = \frac{\sigma_e}{\max_{M\in\Omega}\sigma_{\text{eq}}(M)} \quad (\text{结构安全设计条件：} C_s \ge 1)$$

- **Rankine 准则（最大主拉应力准则，讲义 3.3.4，适用于脆性材料 Matériaux fragiles）**：
  当最大主拉应力达到材料的单轴拉伸断裂强度 $\sigma_R$（或最大主应力绝对值达到 $\sigma_e$）时发生脆性断裂：
  $$\sigma_{\text{eq}}^{\text{Rankine}} = \max(\sigma_1, \sigma_2, \sigma_3) = \sigma_R \qquad \big(\text{对称拉压下为 } \max(|\sigma_1|, |\sigma_2|, |\sigma_3|) = \sigma_e\big)$$
- **延性金属材料（Matériaux ductiles）两大屈服准则——Tresca（定义 3.16）与 von Mises（定义 3.15）同类对比**：

| 对比维度 | Tresca 准则（最大切应力准则，定义 3.16） | von Mises 准则（最大畸变能准则 / $J_2$ 准则，定义 3.15） |
| :--- | :--- | :--- |
| **物理机理** | 当一点处的**最大切应力** $\tau_{\max} = \frac{1}{2}(\sigma_{\text{I}}-\sigma_{\text{III}})$ 达到单轴拉伸屈服时的最大切应力 $\frac{\sigma_e}{2}$ 时发生屈服 | 当单位体积的**弹性形状畸变能**（由偏应力二阶不变量 $\boldsymbol{\sigma}^D:\boldsymbol{\sigma}^D$ 度量）达到单轴屈服畸变能时发生屈服 |
| **等效应力 $\sigma_{\text{eq}}$ 定义公式** | 必须先求出三个主应力 $(\sigma_1, \sigma_2, \sigma_3)$：$$\sigma_{\text{eq}}^T = \max_{I,J=1,2,3} |\sigma_I - \sigma_J| = \sigma_{\text{I}} - \sigma_{\text{III}}$$ | **无需算主应力**，直接用偏应力或一般分量计算：$$\sigma_{\text{eq}}^{VM} = \sqrt{\frac{3}{2}\,\boldsymbol{\sigma}^D : \boldsymbol{\sigma}^D} = \sqrt{\frac{3}{2}\operatorname{Tr}\big((\boldsymbol{\sigma}^D)^2\big)}$$ |
| **主应力展开式** | $\max\big(|\sigma_1-\sigma_2|, \ |\sigma_2-\sigma_3|, \ |\sigma_3-\sigma_1|\big)$ | $\sqrt{\frac{1}{2}\left[(\sigma_1-\sigma_2)^2 + (\sigma_2-\sigma_3)^2 + (\sigma_3-\sigma_1)^2\right]}$ |
| **一般分量展开式** | 需先对角化矩阵求特征值 | $\sqrt{\frac{1}{2}\left[(\sigma_{11}-\sigma_{22})^2+(\sigma_{22}-\sigma_{33})^2+(\sigma_{33}-\sigma_{11})^2 + 6(\sigma_{12}^2+\sigma_{23}^2+\sigma_{13}^2)\right]}$ |
| **平面应力（$\sigma_{33}=\sigma_{13}=\sigma_{23}=0$）** | $\max\big(|\sigma_1-\sigma_2|, \ |\sigma_1|, \ |\sigma_2|\big)$（**千万别漏掉与 $\sigma_3=0$ 作差！**） | $$\sigma_{\text{eq}}^{VM} = \sqrt{\sigma_{11}^2 + \sigma_{22}^2 - \sigma_{11}\sigma_{22} + 3\sigma_{12}^2}$$ |
| **平面应力屈服轨迹几何形状** | 在 $(\sigma_1, \sigma_2)$ 平面上是**内接于椭圆的六边形（Hexagone）**，更为保守（$\sigma_{\text{eq}}^T \ge \sigma_{\text{eq}}^{VM}$） | 在 $(\sigma_1, \sigma_2)$ 平面上是**长轴倾斜 $45^\circ$ 的椭圆（Ellipse）**：$\sigma_1^2 + \sigma_2^2 - \sigma_1\sigma_2 = \sigma_e^2$ |
| **纯剪切状态（仅 $\sigma_{12}=\tau\neq 0$）** | 主应力为 $(\tau, 0, -\tau) \implies \sigma_{\text{eq}}^T = 2|\tau|$<br>纯剪切屈服极限：$\tau_e^T = \frac{\sigma_e}{2} = 0.5\,\sigma_e$ | $\sigma_{\text{eq}}^{VM} = \sqrt{3}\,|\tau|$<br>纯剪切屈服极限：$\tau_e^{VM} = \frac{\sigma_e}{\sqrt{3}} \approx 0.577\,\sigma_e$ |
| **静水压力状态（$\boldsymbol{\sigma}=-p\mathbb{I}$）** | $\sigma_{\text{eq}}^T = 0$（永不屈服） | $\sigma_{\text{eq}}^{VM} = 0$（永不屈服） |

---

### 1.4 第 4 章：守恒定律、平衡方程、热力学与动能定理（Lois de conservation et CL）

#### 1. 基本局部化引理与雷诺输运定理（Lemme fondamental et Théorème de Reynolds）
- **连续介质力学基本引理（Lemme fondamental）**：若连续函数 $f(M)$ 在连续体 $\Omega_t$ 的**任意**子区域 $\omega \subset \Omega_t$ 上的体积分都等于零（$\forall \omega \subset \Omega_t, \ \int_\omega f\,\mathrm{d}\Omega = 0$），则被积函数在点点处处为零（$\forall M \in \Omega_t, \ f(M) = 0$）。它是把积分形式的物理守恒定律转化为局部偏微分方程的数学基础。
- **雷诺输运定理（Théorème de transport de Reynolds）**：计算随体运动体积域 $\Omega_t$ 上积分的物质导数（第一形式与第二形式）：
  $$\frac{\mathrm{d}}{\mathrm{d}t}\int_{\Omega_t} f(t, \vec{x})\,\mathrm{d}\Omega_t = \int_{\Omega_t} \left(\frac{\partial f}{\partial t} + \operatorname{div}(f\vec{V})\right)\mathrm{d}\Omega_t = \int_{\Omega_t} \left(\frac{\mathrm{d}f}{\mathrm{d}t} + f\operatorname{div}\vec{V}\right)\mathrm{d}\Omega_t$$
  - **带质量密度 $\rho$ 的简化形式（讲义备注 4.1，式 4.8–4.9）**：记质量微元 $\mathrm{d}m = \rho\,\mathrm{d}V$，利用连续性方程可得：
    $$\frac{\mathrm{d}}{\mathrm{d}t}\int_{\Omega_t} \rho f\,\mathrm{d}V = \int_{\Omega_t} \rho\,\frac{\mathrm{d}f}{\mathrm{d}t}\,\mathrm{d}V = \int_{\Omega_t} \frac{\mathrm{d}f}{\mathrm{d}t}\,\mathrm{d}m$$
  - **随体体积的时间导数（讲义备注 4.2，式 4.10–4.11）**：取 $f=1$，得 $\frac{\mathrm{d}}{\mathrm{d}t}\mathcal{V}(\Omega_t) = \int_{\Omega_t}\operatorname{div}(\vec{V})\,\mathrm{d}V$。

#### 2. 质量体密度、连续性方程与移动界面跳跃条件（Conservation de la masse et Équation de saut）
- **质量体密度（Densité volumique de masse / Masse volumique，$\rho$，单位 $\text{kg}\cdot\text{m}^{-3}$）**：微元质量 $\mathrm{d}m$ 与微元体积 $\mathrm{d}\Omega_t$ 之比 $\rho(t, M) = \lim_{\Delta\Omega_t\to 0}\frac{\Delta m}{\Delta\Omega_t} > 0$。
- **质量守恒局部方程（讲义式 4.6）**：任意随体域 $\omega_t$ 内的质量 $\int_{\omega_t} \rho\,\mathrm{d}\Omega_t = \int_{\omega_0} \rho_0\,\mathrm{d}\Omega_0$ 不随时间改变：
  - **拉格朗日局部形式（已知 $\mathbb{F}$ 求当前密度 $\rho$ 时必用）**：
    $$\rho(t, \vec{X})\,\det(\mathbb{F}) = \rho_0(\vec{X}) \quad \Longleftrightarrow \quad \rho\,J = \rho_0$$
  - **欧拉局部形式（连续性方程 Équation de continuité）**：
    $$\frac{\partial \rho}{\partial t} + \operatorname{div}(\rho\vec{V}) = 0 \quad \Longleftrightarrow \quad \frac{\mathrm{d}\rho}{\mathrm{d}t} + \rho\operatorname{div}\vec{V} = 0$$
- **“不可压缩介质”与“不可压缩运动”的严格区分（讲义备注 4.3）**：
  - **不可压缩运动（Mouvement incompressible）**：$\frac{\mathrm{d}\rho}{\mathrm{d}t} = 0 \iff \operatorname{div}\vec{V} = 0$（仅保证同一质点的密度随体不变 $\rho(t, M) = \rho_0(M_0)$，若材料本身非均质，不同质点的密度仍可不同）；
  - **不可压缩介质/材料/流体（Milieu / matériau / fluide incompressible）**：若还满足均质假设，则全场密度为同一个常数 $\rho(t, M) = \rho_0 = \text{cste} \implies \operatorname{div}\vec{V} = 0$。
- **移动间断界面 $\Sigma(t)$ 上的质量守恒跳跃方程与跳跃记号（讲义式 4.7 与备注 4.4）**：
  若两个区域 $\Omega_1, \Omega_2$ 被一个以局部速度 $\vec{W}(M, t)$ 运动的界面 $\Sigma(t)$ 分隔（设界面单位法向 $\vec{n}$ 从 $\Omega_1$ 指向 $\Omega_2$），定义跨界面的**跳跃记号（Saut）**为：
  $$\llbracket f \rrbracket_{\Sigma(t)} = f|_{\partial\Omega_2\cap\Sigma(t)} - f|_{\partial\Omega_1\cap\Sigma(t)} = f_2 - f_1$$
  则界面上的质量守恒表现为如下**跳跃条件（Équation de saut）**：
  $$\llbracket \rho(\vec{V} - \vec{W})\cdot\vec{n} \rrbracket_{\Sigma(t)} = \rho_2(\vec{V}_2 - \vec{W})\cdot\vec{n} - \rho_1(\vec{V}_1 - \vec{W})\cdot\vec{n} = 0$$

#### 3. 动量平衡方程 / 局部运动方程（Principe fondamental de la dynamique / Équation d'équilibre local，定理 4.1）
- **一般动力学局部运动方程（Cauchy 第一运动定律，讲义式 4.12）**：
  $$\overrightarrow{\operatorname{div}}\,\boldsymbol{\sigma} + \vec{f}_v = \rho\,\vec{\Gamma} \quad (\text{或记加速度为 } \vec{\gamma}), \qquad \text{即 } \sum_{j=1}^3 \frac{\partial \sigma_{ij}}{\partial x_j} + f_{v,i} = \rho\,\Gamma_i \quad (\text{SI 单位：}\text{N}\cdot\text{m}^{-3})$$
- **静力学局部平衡方程（Équation d'équilibre statique，$\vec{\Gamma} = \vec{0}$）**：
  $$\overrightarrow{\operatorname{div}}\,\boldsymbol{\sigma} + \vec{f}_v = \vec{0}$$
  当题目声明“忽略体积力（forces de volume négligées，$\vec{f}_v = \vec{0}$）”时，平衡方程简化为**无散度条件（Condition de divergence nulle）**：
  $$\overrightarrow{\operatorname{div}}\,\boldsymbol{\sigma} = \vec{0}$$

#### 4. 标准边界条件与双介质界面条件完整汇总（Conditions aux limites et d'interface，讲义 4.2.2）
设外边界 $\partial\Omega$ 上指向材料外部的**单位外法向**为 $\vec{n}$，或两介质 $\Omega_1, \Omega_2$ 交界面 $\Sigma(t)$ 上从 $\Omega_1$ 指向 $\Omega_2$ 的单位法向为 $\vec{n}$（任意切向单位向量记为 $\vec{t}$，满足 $\vec{t}\cdot\vec{n}=0$）：
1. **给定表面力密度边界条件（講义式 4.14，sur $\partial\Omega_T$）**：
   $$\boldsymbol{\sigma}(M)\cdot\vec{n}(M) = \vec{T}_d(M)$$
   - **特例 A——压力边界条件（Condition en pression $p$，讲义式 4.15，sur $\partial\Omega_p$）**：流体压力始终垂直压向表面内部（与外法向 $\vec{n}$ 方向相反），故：
     $$\boldsymbol{\sigma}(M)\cdot\vec{n}(M) = -p(M)\,\vec{n}(M)$$
     *(注意：这仅规定边界上的表面力向量为 $-p\vec{n}$、切向力为零，并不代表物体内部处处处于球形静水应力状态 $\boldsymbol{\sigma}=-p\mathbb{I}$！)*
   - **特例 B——自由表面条件（Condition de surface libre，讲义式 4.16，sur $\partial\Omega_0$）**：表面不受任何外力，故：
     $$\boldsymbol{\sigma}(M)\cdot\vec{n}(M) = \vec{0}$$
   - **特例 C——合力旋量（主矢与主矩）型积分弱边界条件（Torseur d'effort résultant，讲义式 4.17）**：在截面或边界 $\partial\Omega_T$ 上关于点 $A$：
     $$\int_{\partial\Omega_T} \boldsymbol{\sigma}(M)\cdot\vec{n}(M)\,\mathrm{d}S = \vec{R}, \qquad \int_{\partial\Omega_T} \overrightarrow{AM}\wedge\big(\boldsymbol{\sigma}(M)\cdot\vec{n}(M)\big)\,\mathrm{d}S = \vec{M}_A$$
2. **完全黏结条件 / 粘着接触（Condition d'adhésion parfaite / Contact collant，讲义式 4.18–4.19）**：
   - **两个可变形介质 $\Omega_1, \Omega_2$ 交界面 $\Sigma(t)$ 上（式 4.18）**：应力向量（牵引向量）与位移向量同时连续（零跳跃）：
     $$\llbracket \boldsymbol{\sigma} \rrbracket_{\Sigma(t)}\cdot\vec{n} = (\boldsymbol{\sigma}_2 - \boldsymbol{\sigma}_1)\cdot\vec{n} = \vec{0} \quad \text{且} \quad \llbracket \vec{u} \rrbracket_{\Sigma(t)} = \vec{u}_2 - \vec{u}_1 = \vec{0}$$
     *(易错提示：连续的是牵引向量 $\boldsymbol{\sigma}\cdot\vec{n}$ 的 3 个分量，而非应力张量 $\boldsymbol{\sigma}$ 的全部 6 个分量！)*
   - **可变形介质与固定刚体嵌固边界（Encastrement，式 4.19）**：位移为零 $\vec{u}(M) = \vec{0}$（黏性流体在固壁上则为无滑移条件 $\vec{V}_{\text{fluide}} = \vec{V}_{\text{paroi}}$）。
3. **无摩擦接触条件 / 自由滑移接触（Condition de contact sans frottement / Contact glissant，讲义式 4.20–4.22）**：
   - **两个可变形介质 $\Omega_1, \Omega_2$ 交界面 $\Sigma(t)$ 上（式 4.20–4.21）**：法向正应力连续、法向位移连续（不穿透不脱离），且界面**两侧的切向剪应力各自为零**：
     $$\vec{n}\cdot\llbracket \boldsymbol{\sigma} \rrbracket_{\Sigma(t)}\cdot\vec{n} = \vec{n}\cdot(\boldsymbol{\sigma}_2 - \boldsymbol{\sigma}_1)\cdot\vec{n} = 0 \quad \text{且} \quad \llbracket \vec{u} \rrbracket_{\Sigma(t)}\cdot\vec{n} = (\vec{u}_2 - \vec{u}_1)\cdot\vec{n} = 0$$
     $$\forall \vec{t} \perp \vec{n}, \qquad \vec{t}\cdot\boldsymbol{\sigma}_1\cdot\vec{n} = 0 \quad \text{且} \quad \vec{t}\cdot\boldsymbol{\sigma}_2\cdot\vec{n} = 0$$
   - **可变形介质与光滑刚体边界 / 对称面条件（Condition de symétrie，式 4.22）**：法向位移为零，且切向剪应力为零：
     $$\vec{u}\cdot\vec{n} = 0 \quad \text{且} \quad \forall \vec{t}\perp\vec{n}, \ \vec{t}\cdot\boldsymbol{\sigma}\cdot\vec{n} = 0 \quad (\text{即 }\vec{T}_t = \vec{0})$$

#### 5. 内力功率（定义 4.1）、第二类 Piola–Kirchhoff 应力张量 PK2（备注 4.5）、动能定理（定理 4.2）与热力学原理（讲义 4.3–4.4）
- **内力功率 / 变形功率的欧拉表示（Puissance des efforts intérieurs，$P_{\text{int}}$，讲义定义 4.1，式 4.23，单位 $\text{W}$）**：
  $$P_{\text{int}} = -\int_{\Omega} \operatorname{Tr}(\boldsymbol{\sigma}\mathbb{D})\,\mathrm{d}V = -\int_{\Omega} \boldsymbol{\sigma} : \mathbb{D}\,\mathrm{d}V = -\int_{\Omega} \sum_{i,j=1}^3 \sigma_{ij} D_{ij}\,\mathrm{d}V$$
  - **核心性质**：注意公式自带**负号**！在任意刚体运动中，由于 $\mathbb{D} = \mathbb{0}$，**内力功率恒为零（$P_{\text{int}} = 0$）**。
- **第二类 Piola–Kirchhoff 应力张量（PK2，$\mathbb{S}$）与内力功率的拉格朗日表示（讲义备注 4.5，式 4.24）**：
  在初始参考构型 $\Omega_0$ 上，将内力功率写成与 Green–Lagrange 应变率 $\dot{\mathbb{E}}$ 能量共轭的形式：
  $$P_{\text{int}} = -\int_{\Omega_0} \operatorname{Tr}(\mathbb{S}\dot{\mathbb{E}})\,\mathrm{d}V_0 = -\int_{\Omega_0} \mathbb{S} : \dot{\mathbb{E}}\,\mathrm{d}V_0$$
  其中与 $\dot{\mathbb{E}}$ 共轭的对称拉格朗日应力算子 $\mathbb{S}$ 称为**（第二类）Piola–Kirchhoff 应力张量（Seconde contrainte de Piola–Kirchhoff，简称 PK2）**：
  $$\mathbb{S} = J\,\mathbb{F}^{-1}\cdot\boldsymbol{\sigma}\cdot\mathbb{F}^{-T} = \det(\mathbb{F})\,\mathbb{F}^{-1}\boldsymbol{\sigma}\mathbb{F}^{-T}$$
- **动能定理（Théorème de l'énergie cinétique，讲义定理 4.2，式 4.25）**：
  在伽利略参考系中，连续体动能 $E_{\text{cin}}(\Omega) = \int_{\Omega} \frac{1}{2}\rho\vec{V}^2\,\mathrm{d}V$ 的时间导数（等价于加速度量的功率 $P_{\text{acc}}$）等于外力功率 $P_{\text{ext}}$ 与内力功率 $P_{\text{int}}$ 之和：
  $$\frac{\mathrm{d}}{\mathrm{d}t}E_{\text{cin}}(\Omega) = P_{\text{acc}} = P_{\text{ext}} + P_{\text{int}} = \int_{\Omega} \vec{f}_v\cdot\vec{V}\,\mathrm{d}V + \int_{\partial\Omega} \vec{T}\cdot\vec{V}\,\mathrm{d}S - \int_{\Omega} \operatorname{Tr}(\boldsymbol{\sigma}\mathbb{D})\,\mathrm{d}V$$
- **热力学第一定律（Premier principe de la thermodynamique，讲义 4.3.1）**：
  引入内能 $U = \int_{\Omega}\rho e\,\mathrm{d}V$（$e$ 为比内能），系统在两个状态之间的总能量变化（内能 $U$ + 动能 $E_{\text{cin}}$）等于系统所接受的机械功与所吸收的热量之和（转化为局部形式并表示为温度的函数即得**热传导方程 Équation de la chaleur**）：
  $$\frac{\mathrm{d}}{\mathrm{d}t}(E_{\text{cin}} + U) = P_{\text{ext}} + \mathcal{Q}_{\text{ext}} \quad \underset{\text{消去 } E_{\text{cin}}}{\Longleftrightarrow} \quad \frac{\mathrm{d}U}{\mathrm{d}t} = -P_{\text{int}} + \mathcal{Q}_{\text{ext}} \quad \Longleftrightarrow \quad \rho\frac{\mathrm{d}e}{\mathrm{d}t} = \boldsymbol{\sigma} : \mathbb{D} + r - \operatorname{div}\vec{q}$$
- **热力学第二定律（Second principe et Inégalité de Clausius–Duhem，讲义 4.3.2）**：
  引入熵（Entropie，比熵记为 $s$），通过 Clausius–Duhem 耗散不等式规定系统演化的单向方向并刻画过程的**不可逆性（Irréversibilité）**：
  $$\rho\left(T\frac{\mathrm{d}s}{\mathrm{d}t} - \frac{\mathrm{d}e}{\mathrm{d}t}\right) + \boldsymbol{\sigma} : \mathbb{D} - \frac{\vec{q}\cdot\overrightarrow{\operatorname{grad}}T}{T} \ge 0$$

---

### 1.5 第 5–8 章：本构关系、线弹性、黏性流体与能量定理名词

- **均质介质（Milieu homogène）**：材料力学参数（如密度 $\rho_0$、杨氏模量 $E$、泊松比 $\nu$、黏度 $\mu$）在物体各点均相同，不随空间坐标变化（反义词：**Milieu hétérogène 非均质介质**）。
- **各向同性介质（Milieu isotrope）**：材料在某一点的力学响应在所有空间方向上完全相同，本构方程与坐标系旋转无关（反义词：**Milieu anisotrope 各向异性介质**，如木材、纤维复合材料）。
- **各向同性线弹性胡克定律（Loi de Hooke）**：
  - 用**拉梅常数 $(\lambda, \mu)$** 表示（由应变 $\boldsymbol{\varepsilon}$ 求应力 $\boldsymbol{\sigma}$，单位均为 $\text{Pa}$，其中 $\mu = G$ 为剪切模量 Module de cisaillement）：
    $$\boldsymbol{\sigma} = \lambda\operatorname{Tr}(\boldsymbol{\varepsilon})\,\mathbb{I} + 2\mu\,\boldsymbol{\varepsilon} \quad \Longleftrightarrow \quad \sigma_{ij} = \lambda(\operatorname{div}\vec{u})\,\delta_{ij} + 2\mu\,\varepsilon_{ij}$$
  - 用**工程弹性常数 $(E, \nu)$** 表示（由应力 $\boldsymbol{\sigma}$ 求应变 $\boldsymbol{\varepsilon}$，其中 $E$ 为杨氏模量 Module d'Young，单位 $\text{Pa}$；$\nu$ 为泊松比 Coefficient de Poisson，无量纲）：
    $$\boldsymbol{\varepsilon} = \frac{1+\nu}{E}\,\boldsymbol{\sigma} - \frac{\nu}{E}\operatorname{Tr}(\boldsymbol{\sigma})\,\mathbb{I} \quad \Longleftrightarrow \quad \varepsilon_{ij} = \frac{1+\nu}{E}\sigma_{ij} - \frac{\nu}{E}(\operatorname{Tr}\boldsymbol{\sigma})\,\delta_{ij}$$
  - **弹性常数换算关系**：
    $$\mu = \frac{E}{2(1+\nu)}, \qquad \lambda = \frac{E\nu}{(1+\nu)(1-2\nu)}, \qquad \text{体积模量 } K = \lambda + \frac{2}{3}\mu = \frac{E}{3(1-2\nu)} \ \left(\operatorname{Tr}\boldsymbol{\sigma} = 3K\operatorname{Tr}\boldsymbol{\varepsilon}\right)$$
- **Navier 位移平衡方程与 Beltrami-Michell 应力协调方程（第 6 章）**：
  - **Navier 方程（用位移 $\vec{u}$ 表示的线弹性静力平衡方程）**：
    $$\mu\,\Delta\vec{u} + (\lambda + \mu)\,\overrightarrow{\operatorname{grad}}(\operatorname{div}\vec{u}) + \vec{f}_v = \vec{0}$$
  - **Beltrami-Michell 方程（无体力 $\vec{f}_v=\vec{0}$ 时应力张量满足的相容性方程）**：
    $$\Delta\boldsymbol{\sigma} + \frac{1}{1+\nu}\overrightarrow{\operatorname{grad}}\big(\overrightarrow{\operatorname{grad}}(\operatorname{Tr}\boldsymbol{\sigma})\big) = \mathbb{0} \quad \Longrightarrow \quad \Delta(\operatorname{Tr}\boldsymbol{\sigma}) = 0, \quad \Delta(\operatorname{Tr}\boldsymbol{\varepsilon}) = 0$$
- **不可压缩牛顿黏性流体（Fluide newtonien visqueux incompressible，第 7 章）**：满足不可压缩条件 $\operatorname{div}\vec{V} = \operatorname{Tr}(\mathbb{D}) = 0$，本构关系（Stokes 定律）为：
  $$\boldsymbol{\sigma} = -p\,\mathbb{I} + 2\mu\,\mathbb{D}$$
  其中 $p$ 为热力学/流体静压强（单位 $\text{Pa}$），$\mu$ 为动力黏度（Viscosité dynamique，单位 **$\text{Pa}\cdot\text{s}$**）。代入动量方程即得 **Navier-Stokes 方程**：
  $$\rho\left(\frac{\partial \vec{V}}{\partial t} + (\overrightarrow{\operatorname{grad}}\vec{V})\cdot\vec{V}\right) = -\overrightarrow{\operatorname{grad}}p + \mu\,\Delta\vec{V} + \vec{f}_v$$
  *(当黏度 $\mu = 0$ 时退化为**理想流体 Fluide parfait**：$\boldsymbol{\sigma} = -p\,\mathbb{I}$，满足 Euler 方程)*。

---

## 第二部分：常见基本运动全套结果详解与对比

在 QCM 和 Exercice 2 中，考题均围绕以下 6 种标准运动展开。同类对比速查如下：

| 运动名称（法/中） | 运动映射 $\vec{\phi}(t,\vec{X})$ 与欧拉速度 $\vec{V}(t,\vec{x})$ | 变换梯度 $\mathbb{F}$ 与雅可比 $J=\det\mathbb{F}$ | 右 Cauchy-Green $\mathbb{C}$ 与大应变 $\mathbb{E}$ | 小应变 $\boldsymbol{\varepsilon}$、变形率 $\mathbb{D}$ 与旋转率 $\boldsymbol{\Omega}$ | 关键运动性质总结 |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **1. 刚体平移**<br>*Translation rigide* | $\vec{x} = \vec{X} + \vec{c}(t)$<br>$\vec{V} = \dot{\vec{c}}(t)$ | $\mathbb{F} = \mathbb{I}$<br>$J = 1$ | $\mathbb{C} = \mathbb{I}$<br>$\mathbb{E} = \mathbb{0}$ | $\boldsymbol{\varepsilon} = \mathbb{0}$<br>$\mathbb{D} = \mathbb{0}, \ \boldsymbol{\Omega} = \mathbb{0}$ | 等体积、无旋、无变形、均匀速度场 |
| **2. 绕 $x_3$ 轴刚体旋转**<br>*Rotation rigide*<br>（$\dot{\theta}=\omega$） | $x_1 = X_1\cos\theta - X_2\sin\theta$<br>$x_2 = X_1\sin\theta + X_2\cos\theta$<br>$\vec{V} = (-\omega x_2, \omega x_1, 0)$ | $\mathbb{F} = \begin{pmatrix} \cos\theta & -\sin\theta & 0 \\ \sin\theta & \cos\theta & 0 \\ 0 & 0 & 1 \end{pmatrix}$<br>$J = 1$ | $\mathbb{C} = \mathbb{F}^T\mathbb{F} = \mathbb{I}$<br>$\mathbb{E} = \mathbb{0}$ | $\mathbb{D} = \mathbb{0}$<br>$\boldsymbol{\Omega} = \begin{pmatrix} 0 & -\omega & 0 \\ \omega & 0 & 0 \\ 0 & 0 & 0 \end{pmatrix}$ | 轨迹为同心圆；等体积（$J=1$）；有旋（$\vec{\omega}=\omega\vec{e}_3$）；完全无变形（$\mathbb{E}=\mathbb{0},\mathbb{D}=\mathbb{0}$） |
| **3. 单轴均匀拉伸**<br>*Extension simple*<br>（$\lambda = L/L_0$） | $x_1 = \lambda(t) X_1$<br>$x_2 = X_2, \ x_3 = X_3$<br>$\vec{V} = (\frac{\dot{\lambda}}{\lambda}x_1, 0, 0)$ | $\mathbb{F} = \operatorname{diag}(\lambda, 1, 1)$<br>$J = \lambda \neq 1$ | $\mathbb{C} = \operatorname{diag}(\lambda^2, 1, 1)$<br>$E_{11} = \frac{1}{2}(\lambda^2-1)$ | $\varepsilon_{11} = \lambda - 1$<br>$D_{11} = \dot{\lambda}/\lambda$<br>$\boldsymbol{\Omega} = \mathbb{0}$ | **体积不守恒**（$J=\lambda$）；无旋；当 $\lambda=2$ 时，$\varepsilon_{11}=1$ 但 $E_{11}=1.5$ |
| **4. 指数型平面纯伸缩流**<br>（**2024 CC1 真题**） | $x_1 = X_1 e^{\alpha t}$<br>$x_2 = X_2 e^{-\alpha t}, \ x_3 = X_3$<br>$\vec{V} = (\alpha x_1, -\alpha x_2, 0)$ | $\mathbb{F} = \operatorname{diag}(e^{\alpha t}, e^{-\alpha t}, 1)$<br>$J = 1$ | $\mathbb{C} = \operatorname{diag}(e^{2\alpha t}, e^{-2\alpha t}, 1)$<br>$E_{11} = \frac{1}{2}(e^{2\alpha t}-1)$<br>$E_{22} = \frac{1}{2}(e^{-2\alpha t}-1)$ | $\boldsymbol{\varepsilon} \approx \operatorname{diag}(\alpha t, -\alpha t, 0)$<br>$\mathbb{D} = \operatorname{diag}(\alpha, -\alpha, 0)$<br>$\boldsymbol{\Omega} = \mathbb{0}$ | **稳态**、等体积（$J=1$）、无旋（$\boldsymbol{\Omega}=\mathbb{0}$）；轨迹为双曲线 $x_1 x_2 = X_1 X_2$ |
| **5. 幂律型平面纯伸缩流**<br>（**2025 CC1 真题**） | $x_1 = X_1(1+\alpha t)$<br>$x_2 = \frac{X_2}{1+\alpha t}, \ x_3 = X_3$<br>$\vec{V} = \big(\frac{\alpha x_1}{1+\alpha t}, \frac{-\alpha x_2}{1+\alpha t}, 0\big)$ | $\mathbb{F} = \operatorname{diag}\big(1+\alpha t, \frac{1}{1+\alpha t}, 1\big)$<br>$J = 1$ | $\mathbb{C} = \operatorname{diag}\big((1+\alpha t)^2, (1+\alpha t)^{-2}, 1\big)$<br>$E_{11} = \alpha t + \frac{1}{2}\alpha^2 t^2$<br>$E_{22} = \frac{-\alpha t - \frac{1}{2}\alpha^2 t^2}{(1+\alpha t)^2}$ | $\boldsymbol{\varepsilon} \approx \operatorname{diag}(\alpha t, -\alpha t, 0)$<br>$\mathbb{D} = \frac{\alpha}{1+\alpha t}\operatorname{diag}(1, -1, 0)$<br>$\boldsymbol{\Omega} = \mathbb{0}$ | **非稳态**（欧拉速度含 $t$）、等体积（$J=1$）、无旋（$\boldsymbol{\Omega}=\mathbb{0}$）；轨迹仍是双曲线 $x_1 x_2 = X_1 X_2$ |
| **6. 简单剪切**<br>*Glissement simple*<br>（$\gamma = \alpha t$） | $x_1 = X_1 + \gamma(t) X_2$<br>$x_2 = X_2, \ x_3 = X_3$<br>$\vec{V} = (\dot{\gamma} x_2, 0, 0)$ | $\mathbb{F} = \begin{pmatrix} 1 & \gamma & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{pmatrix}$<br>$J = 1$ | $\mathbb{C} = \begin{pmatrix} 1 & \gamma & 0 \\ \gamma & 1+\gamma^2 & 0 \\ 0 & 0 & 1 \end{pmatrix}$<br>$\mathbb{E} = \begin{pmatrix} 0 & \gamma/2 & 0 \\ \gamma/2 & \gamma^2/2 & 0 \\ 0 & 0 & 0 \end{pmatrix}$ | $\varepsilon_{12} = \varepsilon_{21} = \gamma/2$<br>$D_{12} = D_{21} = \dot{\gamma}/2$<br>$\Omega_{12} = -\Omega_{21} = \dot{\gamma}/2 \neq 0$ | 等体积（$J=1$）；**有旋运动**（等于纯剪切变形 + 刚体旋转！）；轨迹为平行直线 $x_2 = X_2$ |

---

## 第三部分：Exercice 1（QCM 多选题）10 大题型逐项秒杀与反例库

### 题型 1：判断拉格朗日描述 vs 欧拉描述 & 运动四大性质（2024 Q1 / 2025 Q1）
1. **第一步看自变量大小写**：含大写 $(X_1, X_2, X_3)$ 为**拉格朗日描述（Description de Lagrange）**；仅含小写 $(x_1, x_2, x_3)$ 为**欧拉描述（Description d'Euler）**。
2. **第二步逐一排查四个性质**：
   - **稳态（Stationnaire）**：写出**欧拉速度** ${}^E\vec{V}(t, x_1, x_2, x_3)$，检查其中是否显含时间 $t$（不显含 $t$ 即为稳态）。
   - **不可压缩 / 等体积（Incompressible / Isochore）**：检查 $\operatorname{div}\vec{V} = \frac{\partial V_1}{\partial x_1}+\frac{\partial V_2}{\partial x_2}+\frac{\partial V_3}{\partial x_3} = 0$（或 $\det\mathbb{F} = 1$）。
   - **无旋（Irrotationnel）**：检查 $\boldsymbol{\Omega} = \mathbb{0}$，即 $\frac{\partial V_i}{\partial x_j} = \frac{\partial V_j}{\partial x_i}$ 是否对所有 $i \neq j$ 成立。
   - **刚体运动（Mouvement de corps rigide）**：检查变形率张量是否全为零 $\mathbb{D} = \mathbb{0}$。只要有一个对角线偏导 $\frac{\partial V_1}{\partial x_1} \neq 0$，就绝不是刚体运动。

### 题型 2：可变形介质运动的分解 & 保持体积不变的运动（2024 Q2 / 2025 Q1–Q2）
- **运动分解定理**：可变形连续介质微元的一般运动可分解为 **刚体平移（Translation de corps rigide）** + **刚体旋转（Rotation de corps rigide）** + **变形（Déformation）**。
- **始终保持体积不变（$\det\mathbb{F} = 1$）的基本运动**：
  - 必选：**刚体平移（Translation de corps rigide）**、**刚体旋转（Rotation de corps rigide）**、**简单剪切（Glissement simple）**。
  - 必排除：单轴拉伸/压缩（Extension / Contraction simple，$J=\lambda\neq 1$）、各向同性膨胀/收缩（Dilatation / Contraction isotrope，$J=\lambda^3\neq 1$）。

### 题型 3：一维细杆拉长到 $2$ 倍长时的大小应变对比（2024 Q3 / 2025 Q3 原题）
设长 $L_0$ 的杆沿 $\vec{e}_1$ 均匀拉伸至 $L = 2L_0$，则伸长比 $\lambda = \frac{L}{L_0} = 2$，运动映射为 $x_1 = 2X_1$，位移为 $u_1 = X_1$：
- **小变形（HPP 线性化）应变分量**：
  $$\varepsilon_{11} = \frac{\partial u_1}{\partial X_1} = \lambda - 1 = 2 - 1 = 1$$
- **大变形（Green-Lagrange）应变分量**：
  $$E_{11} = \frac{1}{2}(\lambda^2 - 1) = \frac{1}{2}(2^2 - 1) = \frac{3}{2} = 1.5$$

### 题型 4：物理量国际单位（SI）同类对比表（2024 Q4 / 2025 Q4 必考）

| 国际单位（SI） | 等价基本单位分解 | 属于该单位的所有核心物理量 |
| :--- | :--- | :--- |
| **无量纲（Sans unité，$1$）** | $1$（或 $\text{rad}$） | 变换梯度 $\mathbb{F}$、雅可比 $J=\det\mathbb{F}$、右 Cauchy-Green 张量 $\mathbb{C}$、大应变 $\mathbb{E}$、小应变 $\boldsymbol{\varepsilon}$、小旋转 $\boldsymbol{\omega}$、位移梯度 $\nabla\vec{u}$、泊松比 $\nu$、安全系数 $C_s$ |
| **$\text{s}^{-1}$** | $\text{s}^{-1}$ | 速度梯度 $\overrightarrow{\operatorname{grad}}\vec{V}$、变形率张量 $\mathbb{D}$、旋转率张量 $\boldsymbol{\Omega}$、涡量向量 $\vec{\omega}=\frac{1}{2}\overrightarrow{\operatorname{rot}}\vec{V}$、速度散度 $\operatorname{div}\vec{V}$ |
| **$\text{Pa}$** | $\text{N}\cdot\text{m}^{-2} = \text{kg}\cdot\text{m}^{-1}\cdot\text{s}^{-2}$ | Cauchy 应力张量 $\boldsymbol{\sigma}$、PK2 应力张量 $\mathbb{S}$、偏应力 $\boldsymbol{\sigma}^D$、应力向量 $\vec{T}$、正应力 $\sigma_n$、切应力 $\tau$、静水压力 $p$、杨氏模量 $E$、拉梅常数 $(\lambda, \mu)$、体积模量 $K$、弹性极限 $\sigma_e$、等效应力 $\sigma_{\text{eq}}$ |
| **$\text{N}\cdot\text{m}^{-3}$（即 $\text{Pa}\cdot\text{m}^{-1}$）** | $\text{kg}\cdot\text{m}^{-2}\cdot\text{s}^{-2}$ | 应力散度 $\overrightarrow{\operatorname{div}}\boldsymbol{\sigma}$、体积力密度 $\vec{f}_v = \rho\vec{g}$、压强梯度 $\overrightarrow{\operatorname{grad}}p$、惯性力密度 $\rho\vec{\gamma}$ |
| **$\text{N}$（即 $\text{Pa}\cdot\text{m}^2$）** | $\text{kg}\cdot\text{m}\cdot\text{s}^{-2}$ | 截面接触力合力 $\vec{R} = \iint_S (\boldsymbol{\sigma}\cdot\vec{n})\,\mathrm{d}S$ |
| **$\text{N}\cdot\text{m}$（即 $\text{Pa}\cdot\text{m}^3$）** | $\text{kg}\cdot\text{m}^2\cdot\text{s}^{-2} = \text{J}$ | 截面合力矩 / 扭矩 $\vec{M}_O = \iint_S \overrightarrow{OM}\wedge(\boldsymbol{\sigma}\cdot\vec{n})\,\mathrm{d}S$ |
| **$\text{Pa}\cdot\text{s}$** | $\text{kg}\cdot\text{m}^{-1}\cdot\text{s}^{-1}$ | 流体动力黏度 $\mu$（注：运动黏度 $\nu = \mu/\rho$ 单位为 $\text{m}^2\cdot\text{s}^{-1}$） |

### 题型 5：给定一点应力矩阵 $\boldsymbol{\sigma}$ 与截面法向 $\vec{n}$，求 $\vec{T}, \sigma_n, \vec{T}_n, \vec{T}_t, \tau$（2024 Q5–6 / 2025 Q5–6）
- **情况 A：法向沿坐标轴 $\vec{n} = \vec{e}_j$**
  - 应力向量 $\vec{T}(M, \vec{e}_j) = \boldsymbol{\sigma}\cdot\vec{e}_j$ 直接就是矩阵 $\boldsymbol{\sigma}$ 的**第 $j$ 列**；
  - 正应力标量 $\sigma_n = \sigma_{jj}$（第 $j$ 个主对角元），正应力向量 $\vec{T}_n = \sigma_{jj}\vec{e}_j$；
  - 切应力向量 $\vec{T}_t = \vec{T} - \vec{T}_n$ 就是把第 $j$ 列的对角元挖掉（置零）剩下的向量，切应力大小 $\tau = \|\vec{T}_t\| = \sqrt{\sum_{i\neq j}\sigma_{ij}^2}$。
  - **2025 CC1 Q5–Q6 真题实例**：给定 $\boldsymbol{\sigma} = \begin{pmatrix} 1 & 2 & 0 \\ 2 & -1 & -3 \\ 0 & -3 & 0 \end{pmatrix}$，截面法向 $\vec{n} = \vec{e}_1$：
    - 第 1 列即为 $\vec{T}(M, \vec{e}_1) = \vec{e}_1 + 2\vec{e}_2$；
    - 正应力标量 $\sigma_n = \sigma_{11} = 1$，正应力向量 $\vec{T}_n = \vec{e}_1$；
    - 切应力向量 $\vec{T}_t = \vec{T} - \vec{T}_n = 2\vec{e}_2$，切应力标量 $\tau = \|\vec{T}_t\| = 2$。
  - **2024 CC1 Q5–Q6 真题实例**：给定 $\boldsymbol{\sigma} = \begin{pmatrix} 1 & 0 & 2 \\ 0 & 1 & 3 \\ 2 & 3 & -2 \end{pmatrix}$，截面法向 $\vec{n} = \vec{e}_3$：
    - 第 3 列即为 $\vec{T}(M, \vec{e}_3) = 2\vec{e}_1 + 3\vec{e}_2 - 2\vec{e}_3$；
    - 正应力标量 $\sigma_n = \sigma_{33} = -2$，正应力向量 $\vec{T}_n = -2\vec{e}_3$；
    - 切应力向量 $\vec{T}_t = 2\vec{e}_1 + 3\vec{e}_2$，切应力标量 $\tau = \sqrt{2^2+3^2} = \sqrt{13}$。
- **情况 B：一般斜截面法向 $\vec{v}$**
  - 先检查是否单位化：$\vec{n} = \frac{\vec{v}}{\|\vec{v}\|}$；再按顺序算 $\vec{T} = \boldsymbol{\sigma}\cdot\vec{n} \to \sigma_n = \vec{T}\cdot\vec{n} \to \vec{T}_n = \sigma_n\vec{n} \to \vec{T}_t = \vec{T}-\vec{T}_n \to \tau = \|\vec{T}_t\|$。

### 题型 6：给定 $3\times 3$ 应力矩阵判断其所属类型（2024 Q7 / 2025 Q7）
拿到矩阵 $\boldsymbol{\sigma}$，按以下 5 步快速排查所有选项：
1. **算迹 $\operatorname{Tr}(\boldsymbol{\sigma}) = \sigma_{11}+\sigma_{22}+\sigma_{33}$**：若等于 $0$，必选 **déviatorique（偏应力张量）**！
2. **看是否为常数矩阵**：若矩阵里每个元素都是常数（不含坐标 $x,y,z$），偏导全为 $0$，必选 **à divergence nulle（无散度）**！
3. **看是否有一整行和一整列为 0（如第 3 行第 3 列全为 0）**：若有，则必有一个主应力 $\sigma_3 = 0$。此时算剩下 $2\times 2$ 子块的行列式 $\sigma_{11}\sigma_{22}-\sigma_{12}^2$：若不为 $0$，说明另外两个主应力非零，必选 **biaxial（双轴应力状态）**！
4. **判断是否同时满足 $\operatorname{Tr}(\boldsymbol{\sigma})=0$ 且 $\det(\boldsymbol{\sigma})=0$**：若同时满足（主应力为 $(\tau, -\tau, 0)$），必选 **de cisaillement pur（纯剪切状态）**！
   - *例如 2025 CC1 Q7*：$\boldsymbol{\sigma} = \begin{pmatrix} 1 & 2 & 0 \\ 2 & -1 & 0 \\ 0 & 0 & 0 \end{pmatrix}$ 同时满足 $\operatorname{Tr}\boldsymbol{\sigma}=0$、第 3 行列为 0 且 $2\times 2$ 行列式为 $-5\neq 0$、元素为常数，因此同时勾选 **déviatorique**、**de cisaillement pur**、**biaxial**、**à divergence nulle** 四项！
   - *例如 2024 CC1 Q7*：$\boldsymbol{\sigma} = \begin{pmatrix} 1 & 0 & 2 \\ 0 & 1 & 3 \\ 2 & 3 & -2 \end{pmatrix}$ 满足 $\operatorname{Tr}\boldsymbol{\sigma} = 1+1-2 = 0$，且 $\det\boldsymbol{\sigma} = 1(-2-9) - 2(0-2) = -7 \neq 0$（三轴状态，非纯剪切），元素为常数，因此勾选 **déviatorique** 和 **à divergence nulle** 两项！
5. **看是否为单位阵的倍数 $c\,\mathbb{I}$**：若是，勾选 **sphérique（球张量）**。

---

## 第四部分：Exercice 2（运动学与变形大题）11 步保姆级解题模板（含法语标准答题句）

> **大题两种出题模式**：
> - **模式 A（2024 CC1 / 2024 CC2）**：先给出**欧拉速度场** $\vec{V}(t, x_1, x_2, x_3)$，依次求 $\operatorname{div}\vec{V}, \mathbb{D}, \boldsymbol{\Omega}$，再积分微分方程求拉格朗日轨迹映射 $\vec{x}=\vec{\phi}(t,\vec{X})$，最后算 $\mathbb{F}, \mathbb{C}, \mathbb{E}, \boldsymbol{\varepsilon}$。
> - **模式 B（2025 CC1）**：先给出**拉格朗日运动映射** $\vec{x} = \vec{\phi}(t, X_1, X_2, X_3)$，依次求拉格朗日速度 ${}^L\vec{V}$、逆代换求欧拉速度 ${}^E\vec{V}$，再算 $\mathbb{F}, J, \mathbb{C}, \mathbb{E}, \boldsymbol{\varepsilon}, \mathbb{D}, \boldsymbol{\Omega}$。

---

### 步骤 1：确定未知常数 $\alpha$ 的单位 & 说明为什么是平面运动（Mouvement plan）
1. **量纲分析法求常数 $\alpha$ 的单位**：
   - 若给定速度场 $V_1 = \alpha x_1$：左边速度单位 $[V_1] = \text{m}\cdot\text{s}^{-1}$，右边坐标单位 $[x_1] = \text{m}$，故 $[\alpha] = \frac{\text{m}\cdot\text{s}^{-1}}{\text{m}} = \text{s}^{-1}$。
   - 若给定位置映射 $x_1 = X_1(1 + \alpha t)$ 或 $x_1 = X_1 e^{\alpha t}$：无量纲组合 $[\alpha t] = 1$，因为时间 $[t] = \text{s}$，故 $[\alpha] = \text{s}^{-1}$。
   - 若给定抛物线速度场 $V_1 = \alpha x_2^2$：$[V_1] = \text{m}\cdot\text{s}^{-1}$，且 $[x_2^2] = \text{m}^2$，故 $[\alpha] = \text{m}^{-1}\cdot\text{s}^{-1}$。
2. **说明为什么是平面运动（Pourquoi le mouvement est-il plan ?）**：
   - 第一，第三方向无运动：$x_3 = X_3 \iff u_3 = 0 \iff V_3 = 0$；
   - 第二，平面内分量与第三坐标无关：$x_1, x_2$（或 $V_1, V_2$）不依赖于坐标 $x_3$（即 $\frac{\partial V_1}{\partial x_3} = \frac{\partial V_2}{\partial x_3} = 0$）。
   - **法语标准答题句**：
     > **Réponse :** Par analyse dimensionnelle, $[\alpha t] = 1$ (ou $[V] = [\alpha][x]$), donc l'unité de $\alpha$ est $\text{s}^{-1}$. Le mouvement est plan dans le plan $(\vec{e}_1, \vec{e}_2)$ car $V_3 = 0$ ($x_3 = X_3$) et les composantes $V_1, V_2$ ne dépendent pas de la coordonnée $x_3$.

---

### 步骤 2：由拉格朗日映射 $\vec{\phi}(t,\vec{X})$ 求拉格朗日速度 ${}^L\vec{V}$ 与欧拉速度 ${}^E\vec{V}$（2025 CC1 Q1–Q2）
1. **第 1 步——求拉格朗日速度 ${}^L\vec{V}(t, M_0)$**：将初始坐标 $(X_1, X_2, X_3)$ 视为常数，对时间 $t$ 直接求偏导：
   $${}^L V_i(t, \vec{X}) = \left.\frac{\partial \phi_i(t, \vec{X})}{\partial t}\right|_{\vec{X}}$$
   - **2025 CC1 真题演算**：已知 $x_1 = X_1(1+\alpha t), \ x_2 = \frac{X_2}{1+\alpha t}, \ x_3 = X_3$，对 $t$ 求导得：
     $${}^L\vec{V}(t, M_0) = \alpha X_1\,\vec{e}_1 - \frac{\alpha X_2}{(1+\alpha t)^2}\,\vec{e}_2$$
2. **第 2 步——求欧拉速度 ${}^E\vec{V}(t, M)$（核心：消去大写 $X_i$，全部替换成小写 $x_i$！）**：
   - 先从运动方程 $x_i = \phi_i(t, \vec{X})$ 中反解出初始坐标 $X_i$（求逆映射 $\vec{X} = \vec{\phi}^{-1}(t, \vec{x})$）：
     $$X_1 = \frac{x_1}{1+\alpha t}, \qquad X_2 = x_2(1+\alpha t), \qquad X_3 = x_3$$
   - 再将 $X_1, X_2$ 代入刚才算出的 ${}^L\vec{V}(t, M_0)$ 中，化简即得欧拉速度：
     $${}^E V_1 = \alpha\left(\frac{x_1}{1+\alpha t}\right) = \frac{\alpha x_1}{1+\alpha t}, \qquad {}^E V_2 = -\frac{\alpha\big(x_2(1+\alpha t)\big)}{(1+\alpha t)^2} = -\frac{\alpha x_2}{1+\alpha t}, \qquad {}^E V_3 = 0$$
     $$\Longrightarrow \quad {}^E\vec{V}(t, M) = \frac{\alpha x_1}{1+\alpha t}\,\vec{e}_1 - \frac{\alpha x_2}{1+\alpha t}\,\vec{e}_2$$
3. **第 3 步——判断运动是否稳态（Stationnaire）**：
   - 检查**欧拉速度** ${}^E\vec{V}(t, \vec{x})$ 是否显含时间 $t$：
   - 在 2025 CC1 中，${}^E\vec{V}$ 含有分母 $1+\alpha t$，故 $\frac{\partial {}^E\vec{V}}{\partial t} \neq \vec{0}$，运动是**非稳态的（Non stationnaire / Instationnaire）**。
   - 在 2024 CC1 中，$x_1 = X_1 e^{\alpha t}, \ x_2 = X_2 e^{-\alpha t} \implies {}^L V_1 = \alpha X_1 e^{\alpha t} = \alpha x_1, \ {}^L V_2 = -\alpha X_2 e^{-\alpha t} = -\alpha x_2$。化为欧拉坐标后 $e^{\pm\alpha t}$ 刚好被抵消，${}^E\vec{V} = (\alpha x_1, -\alpha x_2, 0)$ 不含 $t$，故运动是**稳态的（Stationnaire）**！

---

### 步骤 3：由欧拉速度 $\vec{V}(t,\vec{x})$ 积分求运动映射 $\vec{\phi}(t,\vec{X})$ 与轨迹方程（2024 CC1 Q5–Q6）
已知欧拉速度分量 $V_i(t, x_1, x_2, x_3)$，建立常微分方程组并代入初始条件 $x_i(t=0) = X_i$：
$$\frac{\mathrm{d}x_1}{\mathrm{d}t} = V_1(t, x_1, x_2, x_3), \qquad \frac{\mathrm{d}x_2}{\mathrm{d}t} = V_2(t, x_1, x_2, x_3), \qquad \frac{\mathrm{d}x_3}{\mathrm{d}t} = V_3(t, x_1, x_2, x_3)$$

#### 三类常考常微分方程积分步骤：
1. **第一类：常系数线性方程 $\frac{\mathrm{d}x_1}{\mathrm{d}t} = \alpha x_1, \ \frac{\mathrm{d}x_2}{\mathrm{d}t} = -\alpha x_2$（2024 CC1 真题）**
   - 分离变量积分：
     $$\frac{\mathrm{d}x_1}{x_1} = \alpha\,\mathrm{d}t \implies \ln\left|\frac{x_1(t)}{x_1(0)}\right| = \alpha t \implies x_1(t) = X_1 e^{\alpha t}$$
     $$\frac{\mathrm{d}x_2}{x_2} = -\alpha\,\mathrm{d}t \implies \ln\left|\frac{x_2(t)}{x_2(0)}\right| = -\alpha t \implies x_2(t) = X_2 e^{-\alpha t}, \qquad x_3(t) = X_3$$
2. **第二类：含时分式方程 $\frac{\mathrm{d}x_1}{\mathrm{d}t} = \frac{\alpha x_1}{1+\alpha t}, \ \frac{\mathrm{d}x_2}{\mathrm{d}t} = -\frac{\alpha x_2}{1+\alpha t}$（2025 CC1 逆过程）**
   - 分离变量积分：
     $$\frac{\mathrm{d}x_1}{x_1} = \frac{\alpha\,\mathrm{d}t}{1+\alpha t} \implies \ln\left|\frac{x_1}{X_1}\right| = \ln(1+\alpha t) \implies x_1(t) = X_1(1+\alpha t)$$
     $$\frac{\mathrm{d}x_2}{x_2} = -\frac{\alpha\,\mathrm{d}t}{1+\alpha t} \implies \ln\left|\frac{x_2}{X_2}\right| = -\ln(1+\alpha t) \implies x_2(t) = \frac{X_2}{1+\alpha t}$$
3. **第三类：耦合方程 $\frac{\mathrm{d}x_1}{\mathrm{d}t} = \alpha x_2, \ \frac{\mathrm{d}x_2}{\mathrm{d}t} = 0$（简单剪切或抛物线流）**
   - 先解第二个方程得 $x_2(t) = X_2$（不随时间变化的常数）；
   - 再把 $x_2 = X_2$ 代入第一个方程：$\frac{\mathrm{d}x_1}{\mathrm{d}t} = \alpha X_2 \implies x_1(t) = X_1 + \alpha X_2 t$。

#### 消去时间参数 $t$ 求质点轨迹几何方程 $x_2 = f(x_1)$（Équation des trajectoires）：
- 在 2024 CC1（$x_1 = X_1 e^{\alpha t}, \ x_2 = X_2 e^{-\alpha t}$）和 2025 CC1（$x_1 = X_1(1+\alpha t), \ x_2 = \frac{X_2}{1+\alpha t}$）中，直接将 $x_1(t)$ 与 $x_2(t)$ **两式相乘**即可消去含 $t$ 的因子：
  $$x_1(t)\cdot x_2(t) = X_1 X_2 = \text{Cte} \quad \Longrightarrow \quad x_2(x_1) = \frac{X_1 X_2}{x_1} \quad (\text{当 } X_1 \neq 0)$$
- **轨迹几何形状描述**：在 $(O, \vec{e}_1, \vec{e}_2)$ 平面内，轨迹族是以坐标轴 $x_1=0$ 和 $x_2=0$ 为渐近线的**双曲线分支（Branches d'hyperboles）**（特殊情况：若初始在坐标轴上 $X_1=0$ 或 $X_2=0$，则轨迹为坐标轴直线本身）。

---

### 步骤 4：在 $3\times 3$ 网格点上画速度向量与轨迹曲线（Représentation graphique，必考作图题）
题目给出网格点 $x_1 \in \{-1, 0, 1\}, \ x_2 \in \{-1, 0, 1\}$（共 9 个点），要求画出 $t=0$ 时刻的速度场与轨迹（设 $\alpha > 0$，在 $t=0$ 时 $\vec{V}(0, x_1, x_2) = (\alpha x_1, -\alpha x_2)$）：
1. **原点 $(0, 0)$**：$\vec{V} = (0, 0)$，速度为零（驻点 Point de stagnation），画一个实心点。
2. **水平轴上的两点 $(1, 0)$ 和 $(-1, 0)$**：
   - 在 $(1, 0)$ 处 $\vec{V} = (\alpha, 0)$，箭头沿 $+x_1$ **水平向右**（背离原点向外拉伸）；
   - 在 $(-1, 0)$ 处 $\vec{V} = (-\alpha, 0)$，箭头沿 $-x_1$ **水平向左**（背离原点向外拉伸）。
3. **竖直轴上的两点 $(0, 1)$ 和 $(0, -1)$**：
   - 在 $(0, 1)$ 处 $\vec{V} = (0, -\alpha)$，箭头沿 $-x_2$ **竖直向下**（指向原点向内压缩）；
   - 在 $(0, -1)$ 处 $\vec{V} = (0, \alpha)$，箭头沿 $+x_2$ **竖直向上**（指向原点向内压缩）。
4. **四个象限角点 $(\pm 1, \pm 1)$**：
   - 第一象限 $(1, 1)$：$\vec{V} = (\alpha, -\alpha)$，箭头指向**右下方**；过该点画第一象限双曲线 $x_2 = 1/x_1$（从上往下贴近 $x_2$ 轴流入，经过 $(1,1)$ 后向右贴近 $x_1$ 轴流出）。
   - 第二象限 $(-1, 1)$：$\vec{V} = (-\alpha, -\alpha)$，箭头指向**左下方**；过该点画第二象限双曲线 $x_2 = -1/x_1$。
   - 第三象限 $(-1, -1)$：$\vec{V} = (-\alpha, \alpha)$，箭头指向**左上方**；过该点画第三象限双曲线 $x_2 = 1/x_1$。
   - 第四象限 $(1, -1)$：$\vec{V} = (\alpha, \alpha)$，箭头指向**右上方**；过该点画第四象限双曲线 $x_2 = -1/x_1$。

---

### 步骤 5：计算速度梯度 $\overrightarrow{\operatorname{grad}}\vec{V}$、变形率 $\mathbb{D}$、旋转率 $\boldsymbol{\Omega}$ 与体积守恒（2024 Q3–4 / 2025 Q9）
1. **计算速度梯度张量 $\overrightarrow{\operatorname{grad}}\vec{V}$**：对欧拉速度分量 $V_i(t, x_1, x_2, x_3)$ 关于小写空间坐标 $x_j$ 求偏导：
   $$\overrightarrow{\operatorname{grad}}\vec{V} = \begin{pmatrix} \dfrac{\partial V_1}{\partial x_1} & \dfrac{\partial V_1}{\partial x_2} & \dfrac{\partial V_1}{\partial x_3} \\[8pt] \dfrac{\partial V_2}{\partial x_1} & \dfrac{\partial V_2}{\partial x_2} & \dfrac{\partial V_2}{\partial x_3} \\[8pt] \dfrac{\partial V_3}{\partial x_1} & \dfrac{\partial V_3}{\partial x_2} & \dfrac{\partial V_3}{\partial x_3} \end{pmatrix}$$
2. **分解求变形率张量 $\mathbb{D}$ 与旋转率张量 $\boldsymbol{\Omega}$**：
   $$\mathbb{D} = \frac{1}{2}\left(\overrightarrow{\operatorname{grad}}\vec{V} + (\overrightarrow{\operatorname{grad}}\vec{V})^T\right), \qquad \boldsymbol{\Omega} = \frac{1}{2}\left(\overrightarrow{\operatorname{grad}}\vec{V} - (\overrightarrow{\operatorname{grad}}\vec{V})^T\right)$$
   - 在 2024 CC1 中：$\mathbb{D} = \begin{pmatrix} \alpha & 0 & 0 \\ 0 & -\alpha & 0 \\ 0 & 0 & 0 \end{pmatrix}, \quad \boldsymbol{\Omega} = \mathbb{0}$。
   - 在 2025 CC1 中：$\mathbb{D}(t) = \frac{\alpha}{1+\alpha t}\begin{pmatrix} 1 & 0 & 0 \\ 0 & -1 & 0 \\ 0 & 0 & 0 \end{pmatrix}, \quad \boldsymbol{\Omega} = \mathbb{0}$。
3. **判断体积守恒（Conservation du volume）、无旋性与刚体性**：
   - 计算速度散度：$$\operatorname{div}\vec{V} = \operatorname{Tr}(\mathbb{D}) = D_{11} + D_{22} + D_{33} = 0$$
   - 由 $\frac{\mathrm{d}J}{\mathrm{d}t} = J\operatorname{div}\vec{V} = 0$ 可知 $J(t) = J(0) = 1$，故**运动保持体积不变（Le mouvement conserve le volume / est isochore）**。
   - 因为 $\boldsymbol{\Omega} = \mathbb{0}$，故**运动是无旋的（Le mouvement est irrotationnel）**。
   - 因为 $\mathbb{D} \neq \mathbb{0}$，故**不是刚体运动（Ce n'est pas un mouvement de corps rigide）**。

---

### 步骤 6：计算变换梯度 $\mathbb{F}$、雅可比 $J=\det\mathbb{F}$ 与质量守恒密度 $\rho(t)$（2024 Q7 / 2025 Q4）
1. **计算变换梯度矩阵 $\mathbb{F} = \overrightarrow{\operatorname{grad}}_0\vec{\phi}$**：用拉格朗日运动方程 $x_i(t, X_1, X_2, X_3)$ 对大写初始坐标 $X_j$ 求偏导：
   - 2024 CC1：$$\mathbb{F}(t) = \begin{pmatrix} e^{\alpha t} & 0 & 0 \\ 0 & e^{-\alpha t} & 0 \\ 0 & 0 & 1 \end{pmatrix} \quad \Longrightarrow \quad J = \det(\mathbb{F}) = e^{\alpha t}\cdot e^{-\alpha t}\cdot 1 = 1$$
   - 2025 CC1：$$\mathbb{F}(t) = \begin{pmatrix} 1+\alpha t & 0 & 0 \\ 0 & \frac{1}{1+\alpha t} & 0 \\ 0 & 0 & 1 \end{pmatrix} \quad \Longrightarrow \quad J = \det(\mathbb{F}) = (1+\alpha t)\cdot\frac{1}{1+\alpha t}\cdot 1 = 1$$
2. **由拉格朗日质量守恒求当前质量密度 $\rho(t)$**：
   - 写出质量守恒公式：$$\rho(t, \vec{X})\,\det(\mathbb{F}) = \rho_0(\vec{X})$$
   - 因为 $\det(\mathbb{F}) = 1$，直接得出结论：$$\rho(t, \vec{X}) = \rho_0(\vec{X}) = \rho_0 \quad (\text{质量密度在运动过程中保持恒定不变})$$

---

### 步骤 7：计算右 Cauchy-Green 张量 $\mathbb{C}$ 与 Green-Lagrange 大应变张量 $\mathbb{E}$（2024 Q8 / 2025 Q5）
1. **计算 $\mathbb{C} = \mathbb{F}^T\cdot\mathbb{F}$**：
   - 2024 CC1：$$\mathbb{C}(t) = \begin{pmatrix} e^{2\alpha t} & 0 & 0 \\ 0 & e^{-2\alpha t} & 0 \\ 0 & 0 & 1 \end{pmatrix}$$
   - 2025 CC1：$$\mathbb{C}(t) = \begin{pmatrix} (1+\alpha t)^2 & 0 & 0 \\ 0 & \frac{1}{(1+\alpha t)^2} & 0 \\ 0 & 0 & 1 \end{pmatrix}$$
2. **计算 Green-Lagrange 大应变张量 $\mathbb{E} = \frac{1}{2}(\mathbb{C} - \mathbb{I})$**：
   - 2024 CC1：
     $$\mathbb{E}(t) = \frac{1}{2}\begin{pmatrix} e^{2\alpha t} - 1 & 0 & 0 \\ 0 & e^{-2\alpha t} - 1 & 0 \\ 0 & 0 & 0 \end{pmatrix}$$
   - 2025 CC1（把 $(1+\alpha t)^2 - 1 = 2\alpha t + \alpha^2 t^2$ 展开化简）：
     $$\mathbb{E}(t) = \frac{1}{2}\begin{pmatrix} (1+\alpha t)^2 - 1 & 0 & 0 \\ 0 & \frac{1}{(1+\alpha t)^2} - 1 & 0 \\ 0 & 0 & 0 \end{pmatrix} = \begin{pmatrix} \alpha t + \frac{1}{2}\alpha^2 t^2 & 0 & 0 \\ 0 & \frac{-\alpha t - \frac{1}{2}\alpha^2 t^2}{(1+\alpha t)^2} & 0 \\ 0 & 0 & 0 \end{pmatrix}$$

---

### 步骤 8：求主应变（Déformations principales）与主方向（Directions principales）（2024 Q9 / 2025 Q6）
- **当 $\mathbb{E}$ 已经是对角矩阵时（2024 和 2025 CC1 真题均是对角阵！）**：
  - 无需解任何方程，直接写出：**主方向（Directions principales）**就是三个坐标轴基向量 $\vec{e}_1, \vec{e}_2, \vec{e}_3$；对应的**主应变（Déformations principales）**就是三个对角线元素 $E_1 = E_{11}, \ E_2 = E_{22}, \ E_3 = E_{33} = 0$。
  - **法语标准答题句**：
    > **Réponse :** Le tenseur $\mathbb{E}$ étant déjà diagonal dans la base $(\vec{e}_1, \vec{e}_2, \vec{e}_3)$, les directions principales sont directement $\vec{e}_1, \vec{e}_2, \vec{e}_3$, et les déformations principales associées sont les termes diagonaux $E_1 = E_{11}$, $E_2 = E_{22}$ et $E_3 = 0$.
- **当 $\mathbb{E}$ 含有非对角剪切项 $E_{12} \neq 0$ 时（平面变形 $E_{13}=E_{23}=E_{33}=0$）**：
  - 第三主方向为 $\vec{e}_3$（对应 $E_3 = 0$）；前两个主应变由 $2\times 2$ 矩阵求根公式给出：
    $$E_{\text{I}, \text{II}} = \frac{E_{11}+E_{22}}{2} \pm \sqrt{\left(\frac{E_{11}-E_{22}}{2}\right)^2 + E_{12}^2}$$
    若 $E_{11}=E_{22}=0$（纯非对角阵 $\begin{pmatrix} 0 & \gamma/2 \\ \gamma/2 & 0 \end{pmatrix}$），则主应变为 $\pm\frac{\gamma}{2}$，主方向为对角线角平分线方向 $\vec{N}_{\text{I},\text{II}} = \frac{1}{\sqrt{2}}(\vec{e}_1 \pm \vec{e}_2)$（即 $\pm 45^\circ$）。

---

### 步骤 9：小扰动假设（HPP）适用条件 & 一阶泰勒展开求小应变 $\boldsymbol{\varepsilon}$（2024 Q10 / 2025 Q7–8）
1. **写出 HPP 成立的时间条件（Condition sur $t$ pour l'HPP）**：
   - 位移梯度 $\|\overrightarrow{\operatorname{grad}}_0\vec{u}\| = \|\mathbb{F} - \mathbb{I}\| \ll 1$ 要求无量纲量 $|\alpha| t \ll 1$，因此时间必须满足：
     $$t \ll \frac{1}{|\alpha|}$$
2. **一阶泰勒展开（Développement limité à l'ordre 1 en $\alpha t$）求 $\boldsymbol{\varepsilon}$**：
   - 利用当 $u = \alpha t \to 0$ 时的一阶展开公式：
     $$e^{2\alpha t} - 1 \approx 2\alpha t, \qquad e^{-2\alpha t} - 1 \approx -2\alpha t$$
     $$(1+\alpha t)^2 - 1 \approx 2\alpha t, \qquad (1+\alpha t)^{-2} - 1 \approx -2\alpha t$$
   - 代入 $\mathbb{E}(t)$ 保留 $\alpha t$ 的一阶线性项（或由线性化位移 $\vec{u} \approx \alpha t X_1\vec{e}_1 - \alpha t X_2\vec{e}_2$ 求对称梯度），两种真题下得到的线性化小应变张量 $\boldsymbol{\varepsilon}$ **完全相同**：
     $$\boldsymbol{\varepsilon}(t) = \begin{pmatrix} \alpha t & 0 & 0 \\ 0 & -\alpha t & 0 \\ 0 & 0 & 0 \end{pmatrix}$$
3. **验证迹 $\operatorname{Tr}(\boldsymbol{\varepsilon}) = 0$ 与变形率关系 $\mathbb{D}(t=0) = \frac{\partial\boldsymbol{\varepsilon}}{\partial t}$**：
   - 体应变：$\frac{\Delta V}{V_0} \approx \operatorname{Tr}(\boldsymbol{\varepsilon}) = \alpha t - \alpha t + 0 = 0$（再次验证小变形下体积守恒！）；
   - 对时间求导：$\frac{\partial\boldsymbol{\varepsilon}}{\partial t} = \operatorname{diag}(\alpha, -\alpha, 0) = \mathbb{D}(t=0)$。

---

### 步骤 10：压轴问答——该运动与“简单剪切（Glissement simple）”的异同点（2024 Q11 / 2025 Q10 必考）
当题目问 *“Quelles sont les similitudes et les différences avec un mouvement de glissement simple ?”* 时，直接分条作答：
1. **相同点（Similitudes）**：
   - **都是平面运动（Mouvements plans）**：都在 $(\vec{e}_1, \vec{e}_2)$ 平面内运动（$V_3 = 0$）。
   - **都是等体积运动（Conservation du volume / Isochores）**：都满足 $\det\mathbb{F} = 1$、$\operatorname{div}\vec{V} = \operatorname{Tr}\mathbb{D} = 0$、$\operatorname{Tr}\boldsymbol{\varepsilon} = 0$。
   - **小变形下应变状态同构（Cisaillement pur）**：在旋转 $45^\circ$ 的坐标系下，本题的对角纯伸缩应变 $\operatorname{diag}(\alpha t, -\alpha t, 0)$ 变为纯非对角剪切应变（即两个正交方向一拉一压等价于 $45^\circ$ 斜截面上的纯剪切）。
2. **不同点（Différences）**：
   - **旋转性完全不同（最核心区别！）**：本题运动是**无旋的（Irrotationnel，$\boldsymbol{\Omega} = \mathbb{0}$）**，主方向始终固定在 $\vec{e}_1, \vec{e}_2$ 不转动；而简单剪切（Glissement simple，$V_1 = \dot{\gamma} x_2, V_2 = 0$）**是有旋的（Rotationnel，$\boldsymbol{\Omega} \neq \mathbb{0}$）**，简单剪切 = 纯剪切变形 + 刚体旋转！
   - **质点轨迹不同**：本题轨迹是**双曲线（Hyperboles，$x_1 x_2 = \text{Cte}$）**；简单剪切轨迹是**平行直线（Droites parallèles，$x_2 = \text{Cte}$）**。
   - **主应变方向不同**：本题主方向沿坐标轴 $\vec{e}_1, \vec{e}_2$；而沿 $\vec{e}_1$ 的简单剪切在小变形下的主方向沿 $\pm 45^\circ$ 对角线方向 $\frac{1}{\sqrt{2}}(\vec{e}_1 \pm \vec{e}_2)$。

---

## 第五部分：Exercice 3（应力、平衡与强度校核大题）8 步保姆级解题模板（含法语标准答题句）

### 步骤 1：利用对称性补全应力矩阵 & 论证平面应力假设（Contraintes planes）
1. **利用对称性补全矩阵中的 $\star$ 号（2024 CC1 Q1）**：
   因为 Cauchy 应力张量必对称（$\boldsymbol{\sigma}^T = \boldsymbol{\sigma}$），故 $\sigma_{ji} = \sigma_{ij}$，直接关于主对角线镜像对称抄写即可。
2. **说明为什么是平面应力状态及其物理合理性（2025 CC1 Q1 必考）**：
   - **定义判据**：因为与板厚方向 $z$ 相关的三个应力分量恒为零（$\sigma_{rz} = \sigma_{\theta z} = \sigma_{zz} = 0$，即第 3 行和第 3 列全为 0），故属于 $(\vec{e}_r, \vec{e}_\theta)$ 平面内的**平面应力状态（État de contraintes planes）**。
   - **物理论证三步曲**：
     1. 薄板的上下两个端面 $z = \pm e/2$（外法向 $\vec{n} = \pm\vec{e}_z$）是不受外力的**自由表面（Surfaces libres）**，由边界条件 $\boldsymbol{\sigma}\cdot(\pm\vec{e}_z) = \vec{0}$ 可知，在上下表面 $z = \pm e/2$ 处严格有 $\sigma_{rz} = \sigma_{\theta z} = \sigma_{zz} = 0$；
     2. 薄板的厚度远小于其面内几何半径（$e \ll R_i, R_e$，即 Plaque très mince）；
     3. 根据应力场的连续性，这三个在上下表面均为零的分量在极薄的厚度方向内无法发展出显著幅值，因此在整个板厚内（$\forall z \in [-e/2, e/2]$）均可近似认为 $\sigma_{rz} = \sigma_{\theta z} = \sigma_{zz} \approx 0$。
   - **法语标准答题句**：
     > **Réponse :** Il s'agit d'un **état de contraintes planes** dans le plan $(\vec{e}_r, \vec{e}_\theta)$ car $\sigma_{rz} = \sigma_{\theta z} = \sigma_{zz} = 0$. Cette hypothèse est justifiée car les faces supérieure et inférieure ($z = \pm e/2$, de normale $\vec{n} = \pm\vec{e}_z$) sont libres d'effort ($\boldsymbol{\sigma}\cdot\vec{e}_z = \vec{0}$), et la plaque étant très mince ($e \ll R_e$), ces composantes restent nulles dans toute l'épaisseur.

---

### 步骤 2：展开局部静力平衡方程 $\overrightarrow{\operatorname{div}}\boldsymbol{\sigma} + \vec{f}_v = \vec{0}$ 并求解未知应力分量（核心必考！）

当题目指出物体处于静力平衡且忽略体积力（$\vec{f}_v = \vec{0}$）时，直接展开 $\overrightarrow{\operatorname{div}}\boldsymbol{\sigma} = \vec{0}$：

#### 1. 直角坐标系 $(x, y, z)$ 下的平衡方程展开（2024 CC1 Q2 真题）：
$$\begin{cases}
\dfrac{\partial \sigma_{xx}}{\partial x} + \dfrac{\partial \sigma_{xy}}{\partial y} + \dfrac{\partial \sigma_{xz}}{\partial z} = 0 \\[8pt]
\dfrac{\partial \sigma_{yx}}{\partial x} + \dfrac{\partial \sigma_{yy}}{\partial y} + \dfrac{\partial \sigma_{yz}}{\partial z} = 0 \\[8pt]
\dfrac{\partial \sigma_{zx}}{\partial x} + \dfrac{\partial \sigma_{zy}}{\partial y} + \dfrac{\partial \sigma_{zz}}{\partial z} = 0
\end{cases}$$
- **2024 CC1 Q2 真题演算**：给定圆柱扭转应力场 $\sigma_{xz} = -\alpha y, \ \sigma_{yz} = \alpha x$（其余分量为 0）：
  - 第 1 式：$\frac{\partial(-\alpha y)}{\partial z} = 0$；
  - 第 2 式：$\frac{\partial(\alpha x)}{\partial z} = 0$；
  - 第 3 式：$\frac{\partial(-\alpha y)}{\partial x} + \frac{\partial(\alpha x)}{\partial y} = 0 + 0 = 0$。
  - **结论**：对于**任意实常数 $\alpha$**，局部静力平衡方程在圆柱内部处处恒成立！

#### 2. 柱坐标系 $(r, \theta, z)$ 下的平衡方程展开（2025 CC1 Q2 真题）：
$$\begin{cases}
\dfrac{\partial \sigma_{rr}}{\partial r} + \dfrac{1}{r}\dfrac{\partial \sigma_{r\theta}}{\partial \theta} + \dfrac{\partial \sigma_{rz}}{\partial z} + \dfrac{\sigma_{rr} - \sigma_{\theta\theta}}{r} = 0 & (\text{径向 } \vec{e}_r) \\[10pt]
\dfrac{\partial \sigma_{\theta r}}{\partial r} + \dfrac{1}{r}\dfrac{\partial \sigma_{\theta\theta}}{\partial \theta} + \dfrac{\partial \sigma_{\theta z}}{\partial z} + \dfrac{2\sigma_{r\theta}}{r} = 0 & (\text{环向 } \vec{e}_\theta) \\[10pt]
\dfrac{\partial \sigma_{zr}}{\partial r} + \dfrac{1}{r}\dfrac{\partial \sigma_{z\theta}}{\partial \theta} + \dfrac{\partial \sigma_{zz}}{\partial z} + \dfrac{\sigma_{zr}}{r} = 0 & (\text{轴向 } \vec{e}_z)
\end{cases}$$
- **2025 CC1 Q2 轴对称问题手把手推导**：
  当 $\boldsymbol{\sigma} = \operatorname{diag}\big(\sigma_{rr}(r), \sigma_{\theta\theta}(r), 0\big)$ 时，环向和轴向方程自动满足（$0=0$），只剩下**径向平衡方程**：
  $$\frac{\mathrm{d}\sigma_{rr}}{\mathrm{d}r} + \frac{\sigma_{rr} - \sigma_{\theta\theta}}{r} = 0 \quad \Longleftrightarrow \quad \sigma_{\theta\theta}(r) = \sigma_{rr}(r) + r\,\frac{\mathrm{d}\sigma_{rr}}{\mathrm{d}r}$$
  - **代入已知的 $\sigma_{rr}(r) = 6\alpha\left(\frac{r}{R_e}\right)^2 + \beta\left(\frac{R_i}{r}\right)^2 + \gamma$ 求 $\sigma_{\theta\theta}(r)$**：
    1. 先对 $r$ 求导数（注意 $\frac{\mathrm{d}(r^2)}{\mathrm{d}r} = 2r$，而 $\frac{\mathrm{d}(r^{-2})}{\mathrm{d}r} = -2r^{-3}$）：
       $$\frac{\mathrm{d}\sigma_{rr}}{\mathrm{d}r} = \frac{12\alpha r}{R_e^2} - \frac{2\beta R_i^2}{r^3}$$
    2. 两边同乘以 $r$：
       $$r\,\frac{\mathrm{d}\sigma_{rr}}{\mathrm{d}r} = 12\alpha\left(\frac{r}{R_e}\right)^2 - 2\beta\left(\frac{R_i}{r}\right)^2$$
    3. 与 $\sigma_{rr}(r)$ 相加即得 $\sigma_{\theta\theta}(r)$：
       $$\sigma_{\theta\theta}(r) = \sigma_{rr}(r) + r\,\frac{\mathrm{d}\sigma_{rr}}{\mathrm{d}r} = 18\alpha\left(\frac{r}{R_e}\right)^2 - \beta\left(\frac{R_i}{r}\right)^2 + \gamma$$

---

### 步骤 3：写出各边界面的单位外法向 $\vec{n}$ 与应力向量 $\vec{T}=\boldsymbol{\sigma}\cdot\vec{n}$，求解待定常数（2024 Q3 / 2025 Q3）

在写边界条件前，必须准确写出指向**材料实体外部**的单位外法向 $\vec{n}$：
- **圆柱 / 圆板外侧面（$r = R_e$ 或 $x^2+y^2=R^2$）**：向外远离轴线，故外法向为：
  $$\vec{n} = +\vec{e}_r = \cos\theta\,\vec{e}_x + \sin\theta\,\vec{e}_y = \frac{x}{R}\vec{e}_x + \frac{y}{R}\vec{e}_y$$
- **圆环板内孔壁面（$r = R_i$）**：从材料实体指向中心空洞内部（朝向圆心！），故外法向必带**负号**：
  $$\vec{n} = -\vec{e}_r$$
- **上底面（$z = L$ 或 $z = +e/2$）**：$\vec{n} = +\vec{e}_z$；**下底面（$z = 0$ 或 $z = -e/2$）**：$\vec{n} = -\vec{e}_z$。

#### 两个真题的完整代入演算：
1. **2024 CC1 Q3（求圆柱外侧面 $r=R$ 与上下底面的应力向量 $\vec{T}$）**：
   - 在外侧面 $r=R$ 上，$\vec{n} = \frac{x}{R}\vec{e}_x + \frac{y}{R}\vec{e}_y$，做矩阵乘法：
     $$\vec{T}(M, \vec{n}) = \boldsymbol{\sigma}\cdot\vec{n} = \begin{pmatrix} 0 & 0 & -\alpha y \\ 0 & 0 & \alpha x \\ -\alpha y & \alpha x & 0 \end{pmatrix}\begin{pmatrix} x/R \\ y/R \\ 0 \end{pmatrix} = \begin{pmatrix} 0 \\ 0 \\ -\frac{\alpha y x}{R} + \frac{\alpha x y}{R} \end{pmatrix} = \vec{0}$$
     因此圆柱外侧面是**自由表面（Surface libre）**！
   - 在上底面 $z=L$ 上（$\vec{n} = +\vec{e}_z$）：$\vec{T}(M, \vec{e}_z) = \boldsymbol{\sigma}\cdot\vec{e}_z = -\alpha y\,\vec{e}_x + \alpha x\,\vec{e}_y$（在柱坐标下即为 $+\alpha r\,\vec{e}_\theta$）。
   - 在下底面 $z=0$ 上（$\vec{n} = -\vec{e}_z$）：$\vec{T}(M, -\vec{e}_z) = \boldsymbol{\sigma}\cdot(-\vec{e}_z) = \alpha y\,\vec{e}_x - \alpha x\,\vec{e}_y$（在柱坐标下即为 $-\alpha r\,\vec{e}_\theta$）。
2. **2025 CC1 Q3（由内外圆周边界 $r=R_i$ 和 $r=R_e$ 自由求常数 $\beta, \gamma$）**：
   - 在内孔壁 $r=R_i$（$\vec{n}=-\vec{e}_r$）：$\vec{T}(R_i) = \boldsymbol{\sigma}(R_i)\cdot(-\vec{e}_r) = -\sigma_{rr}(R_i)\vec{e}_r = \vec{0} \implies \sigma_{rr}(R_i) = 0$；
   - 在外边缘 $r=R_e$（$\vec{n}=+\vec{e}_r$）：$\vec{T}(R_e) = \boldsymbol{\sigma}(R_e)\cdot(+\vec{e}_r) = +\sigma_{rr}(R_e)\vec{e}_r = \vec{0} \implies \sigma_{rr}(R_e) = 0$。
   - 联立方程组：
     $$\begin{cases}
     \sigma_{rr}(R_e) = 6\alpha + \beta\left(\dfrac{R_i}{R_e}\right)^2 + \gamma = 0 \\[8pt]
     \sigma_{rr}(R_i) = 6\alpha\left(\dfrac{R_i}{R_e}\right)^2 + \beta + \gamma = 0
     \end{cases}$$
   - 两式相减消去 $\gamma$：$(6\alpha - \beta)\left[1 - \left(\frac{R_i}{R_e}\right)^2\right] = 0 \implies \beta = 6\alpha$；代回第 1 式得 $\gamma = -6\alpha\left[1 + \left(\frac{R_i}{R_e}\right)^2\right]$。

---

### 步骤 4：积分计算截面上的接触力合力 $\vec{R}$ 与合力矩 $\vec{M}_O$（2024 Q4 / 2025 Q4）
在半径为 $R$ 的圆形横截面 $S$ 上积分时，切换为极坐标 $x = r\cos\theta, \ y = r\sin\theta, \ \mathrm{d}S = r\,\mathrm{d}r\,\mathrm{d}\theta$（$r\in[0,R], \ \theta\in[0,2\pi]$）：
- **利用对称性消去一次项**：圆域上奇函数积分为零，$\iint_S x\,\mathrm{d}S = \iint_S y\,\mathrm{d}S = 0$。
  因此在 2024 CC1 上底面 $z=L$ 上，总合力为：
  $$\vec{R} = \iint_S (-\alpha y\,\vec{e}_x + \alpha x\,\vec{e}_y)\,\mathrm{d}S = \vec{0}$$
- **利用极惯性矩公式计算二次项（合力矩 / 扭矩）**：
  因为 $\overrightarrow{O'M}\wedge\vec{T} = (x\vec{e}_x + y\vec{e}_y)\wedge(-\alpha y\vec{e}_x + \alpha x\vec{e}_y) = \alpha(x^2+y^2)\vec{e}_z = \alpha r^2\vec{e}_z$，积分得：
  $$\vec{M}_{O'} = \iint_S \alpha r^2\,\mathrm{d}S\,\vec{e}_z = \alpha \left(\int_0^{2\pi}\mathrm{d}\theta\right)\left(\int_0^R r^3\,\mathrm{d}r\right)\vec{e}_z = \alpha\cdot 2\pi\cdot\frac{R^4}{4}\,\vec{e}_z = \frac{\pi\alpha R^4}{2}\,\vec{e}_z$$
  合力为零、合力矩为绕圆柱轴线的纯力偶（扭矩 $\mathcal{C} = \frac{\pi\alpha R^4}{2}$），这证明圆柱承受的是**纯扭转加载（Sollicitation de torsion pure）**。

---

### 步骤 5：应用 Tresca 与 von Mises 屈服准则，定位最危险点并求极限载荷（2024 Q5 / 2025 Q5）
1. **使用 Tresca 准则（Critère de Tresca）的完整步骤**：
   - **第 1 步**：写出全部三个主应力 $(\sigma_1, \sigma_2, \sigma_3)$。特别注意：在平面应力问题中，**绝对不能漏掉第三个主应力 $\sigma_3 = \sigma_{zz} = 0$**！
   - **第 2 步**：写出三个主应力两两之差的绝对值：
     $$\sigma_{\text{eq}}^T(M) = \max\Big(|\sigma_1 - \sigma_2|, \ |\sigma_2 - \sigma_3|, \ |\sigma_3 - \sigma_1|\Big)$$
   - **第 3 步**：在题目要求的区域或边界上找出使 $\sigma_{\text{eq}}^T(M)$ 达到最大值的空间位置（最危险点），令 $\max \sigma_{\text{eq}}^T = \sigma_e$ 解出最大允许载荷参数 $\alpha_{\max}$。
     - **2024 CC1 扭转实例**：主应力为 $(+|\alpha|r, \ 0, \ -|\alpha|r)$，故 $\sigma_{\text{eq}}^T(r) = 2|\alpha|r$。最大值出现在圆柱外表面 **$r = R$** 处，$\max\sigma_{\text{eq}}^T = 2|\alpha|R = \sigma_e \implies |\alpha_{\max}^T| = \frac{\sigma_e}{2R}$。
     - **2025 CC1 圆环自由边界实例**：在 $r=R_i$ 和 $r=R_e$ 处均有 $\sigma_{rr}=0$ 且 $\sigma_{zz}=0$，三个主应力为 $(0, \sigma_{\theta\theta}, 0)$，故 Tresca 等效应力直接等于 $|\sigma_{\theta\theta}| = 12|\alpha|\left[1 - \left(\frac{R_i}{R_e}\right)^2\right]$。
2. **使用 von Mises 准则（Critère de von Mises）的完整步骤**：
   - 直接代入分量公式计算 $\sigma_{\text{eq}}^{VM}(M)$：
     $$\sigma_{\text{eq}}^{VM} = \sqrt{\frac{1}{2}\left[(\sigma_{11}-\sigma_{22})^2+(\sigma_{22}-\sigma_{33})^2+(\sigma_{33}-\sigma_{11})^2 + 6(\sigma_{12}^2+\sigma_{23}^2+\sigma_{13}^2)\right]}$$
     - **2024 CC1 扭转实例**：仅 $\sigma_{xz}=-\alpha y, \ \sigma_{yz}=\alpha x$ 非零，故 $\sigma_{\text{eq}}^{VM}(r) = \sqrt{3(\sigma_{xz}^2+\sigma_{yz}^2)} = \sqrt{3}\,|\alpha|\,r$。最大值同样在 **$r = R$** 处，$\max\sigma_{\text{eq}}^{VM} = \sqrt{3}\,|\alpha|R = \sigma_e \implies |\alpha_{\max}^{VM}| = \frac{\sigma_e}{\sqrt{3}\,R}$。
     - **2025 CC1 平面应力对角阵实例**：$\sigma_{\text{eq}}^{VM}(r) = \sqrt{\sigma_{rr}^2 + \sigma_{\theta\theta}^2 - \sigma_{rr}\sigma_{\theta\theta}}$。在 $\sigma_{rr}=0$ 的内外边界上简化为 $|\sigma_{\theta\theta}|$。

---

## 第六部分：微分算子、应变积分求位移与第 5–8 章大题速查

### 6.1 柱坐标 $(r,\theta,z)$ 与球坐标 $(r,\theta,\varphi)$ 核心公式
1. **柱坐标系 $(r, \theta, z)$ 小应变张量 $\boldsymbol{\varepsilon}(\vec{u})$ 分量（把 $\vec{u}$ 换为 $\vec{V}$ 即为变形率 $\mathbb{D}$）**：
   - 三个正应变（注意环向正应变 $\varepsilon_{\theta\theta}$ 含有径向位移项 $\frac{u_r}{r}$！）：
     $$\varepsilon_{rr} = \frac{\partial u_r}{\partial r}, \qquad \varepsilon_{\theta\theta} = \frac{1}{r}\frac{\partial u_\theta}{\partial \theta} + \frac{u_r}{r}, \qquad \varepsilon_{zz} = \frac{\partial u_z}{\partial z}$$
   - 三个剪切应变：
     $$\varepsilon_{r\theta} = \frac{1}{2}\left(\frac{1}{r}\frac{\partial u_r}{\partial \theta} + \frac{\partial u_\theta}{\partial r} - \frac{u_\theta}{r}\right), \qquad \varepsilon_{\theta z} = \frac{1}{2}\left(\frac{\partial u_\theta}{\partial z} + \frac{1}{r}\frac{\partial u_z}{\partial \theta}\right), \qquad \varepsilon_{rz} = \frac{1}{2}\left(\frac{\partial u_r}{\partial z} + \frac{\partial u_z}{\partial r}\right)$$
   - 散度与拉普拉斯算子：
     $$\operatorname{div}\vec{u} = \frac{1}{r}\frac{\partial(r u_r)}{\partial r} + \frac{1}{r}\frac{\partial u_\theta}{\partial \theta} + \frac{\partial u_z}{\partial z}, \qquad \Delta f = \frac{1}{r}\frac{\partial}{\partial r}\left(r\frac{\partial f}{\partial r}\right) + \frac{1}{r^2}\frac{\partial^2 f}{\partial \theta^2} + \frac{\partial^2 f}{\partial z^2}$$
2. **球坐标系 $(r, \theta, \varphi)$ 径向球对称问题（$\vec{u} = u(r)\vec{e}_r$）专用公式**：
   - 球对称应变与散度：
     $$\varepsilon_{rr} = \frac{\mathrm{d}u}{\mathrm{d}r}, \qquad \varepsilon_{\theta\theta} = \varepsilon_{\varphi\varphi} = \frac{u}{r}, \qquad \operatorname{div}\vec{u} = \operatorname{Tr}\boldsymbol{\varepsilon} = \frac{\mathrm{d}u}{\mathrm{d}r} + \frac{2u}{r} = \frac{1}{r^2}\frac{\mathrm{d}(r^2 u)}{\mathrm{d}r}$$
   - 球对称应力静力平衡方程（仅 $\sigma_{rr}(r)$ 与 $\sigma_{\theta\theta}(r)=\sigma_{\varphi\varphi}(r)$ 非零）：
     $$\frac{\mathrm{d}\sigma_{rr}}{\mathrm{d}r} + \frac{2(\sigma_{rr} - \sigma_{\theta\theta})}{r} + f_r = 0$$

---

### 6.2 已知小应变张量 $\boldsymbol{\varepsilon}(x_1, x_2, x_3)$ 积分求位移场 $\vec{u}$ 的标准步骤（TD2 / CC2）
1. **第一步（验证圣维南相容性条件 Compatibilité）**：二维平面问题只需验证 $\frac{\partial^2\varepsilon_{11}}{\partial x_2^2} + \frac{\partial^2\varepsilon_{22}}{\partial x_1^2} = 2\frac{\partial^2\varepsilon_{12}}{\partial x_1 \partial x_2}$。
2. **第二步（对三个对角正应变积分）**：
   $$u_1 = \int \varepsilon_{11}\,\mathrm{d}x_1 + f_1(x_2, x_3), \qquad u_2 = \int \varepsilon_{22}\,\mathrm{d}x_2 + f_2(x_1, x_3), \qquad u_3 = \int \varepsilon_{33}\,\mathrm{d}x_3 + f_3(x_1, x_2)$$
3. **第三步（代入三个非对角剪切应变方程）**：利用 $\frac{\partial u_i}{\partial x_j} + \frac{\partial u_j}{\partial x_i} = 2\varepsilon_{ij}\ (i\neq j)$ 确定附加函数 $f_1, f_2, f_3$。
4. **第四步（加上无穷小刚体位移通解项——必加！）**：
   任何应变积分得到的位移场都必须加上齐次解（即滿足 $\boldsymbol{\varepsilon}=\mathbb{0}$ 的**无穷小刚体位移** $\vec{u}_{\text{rigide}} = \vec{\lambda} + \vec{\Omega}\wedge\vec{x}$，含 3 个平移常数 $\lambda_1,\lambda_2,\lambda_3$ 与 3 个旋转常数 $\Omega_1,\Omega_2,\Omega_3$）：
   $$\vec{u}_{\text{rigide}}(\vec{x}) = \begin{pmatrix} \lambda_1 + \Omega_2 x_3 - \Omega_3 x_2 \\ \lambda_2 + \Omega_3 x_1 - \Omega_1 x_3 \\ \lambda_3 + \Omega_1 x_2 - \Omega_2 x_1 \end{pmatrix} \quad \left(\text{二维平面下为 } \begin{pmatrix} \lambda_1 - \Omega_3 x_2 \\ \lambda_2 + \Omega_3 x_1 \end{pmatrix}\right)$$
5. **第五步（用边界位移和旋转条件定出 6 个常数）**：利用已知点位移 $\vec{u}(M_0) = \vec{0}$ 定出 $\vec{\lambda}$，利用已知点旋转 $\boldsymbol{\omega}(M_0) = \mathbb{0}$（即 $\overrightarrow{\operatorname{rot}}\vec{u}(M_0) = \vec{0}$）定出 $\vec{\Omega}$。

---

### 6.3 不可压缩牛顿黏性流体四大经典层流模型详解（第 7 章 / TD7）

对于平行定常层流 $\vec{V} = u(y)\vec{e}_x$（或圆管内 $\vec{V} = u(r)\vec{e}_z$），连续性方程 $\operatorname{div}\vec{V} = 0$ 自动满足，且**对流加速度项恒为零** $(\overrightarrow{\operatorname{grad}}\vec{V})\cdot\vec{V} = \vec{0}$，Navier-Stokes 方程严格简化为线性常微分方程 $-\overrightarrow{\operatorname{grad}}p + \mu\Delta\vec{V} + \vec{f}_v = \vec{0}$：

#### 1. 平面 Couette 剪切流（两平行平板间无压差剪切流）
- **几何与边界条件**：下板 $y=0$ 固定静止（无滑移 $u(0)=0$），上板 $y=h$ 以恒定速度 $U\vec{e}_x$ 水平拉动（无滑移 $u(h)=U$），无流向压强梯度（$\frac{\partial p}{\partial x} = 0$）。
- **控制方程与速度分布**：$\mu\frac{\mathrm{d}^2 u}{\mathrm{d}y^2} = 0 \implies u(y)$ 为**线性速度剖面**：
  $$u(y) = U\,\frac{y}{h}$$
- **切应力与单位宽度体积流量 $q$**：
  $$\sigma_{xy} = \mu\frac{\mathrm{d}u}{\mathrm{d}y} = \mu\frac{U}{h} = \text{Cte}, \qquad q = \int_0^h u(y)\,\mathrm{d}y = \frac{Uh}{2}$$

#### 2. 平面 Poiseuille 管道流（两固定平行平板间压差驱动流）
- **几何与边界条件**：上下两板固定在 $y = \pm h$（无滑移 $u(\pm h) = 0$，中心对称 $u'(0)=0$），受恒定流向压强梯度 $G = -\frac{\partial p}{\partial x} = \frac{P_e - P_s}{L} > 0$ 驱动。
- **控制方程与速度分布**：$\mu\frac{\mathrm{d}^2 u}{\mathrm{d}y^2} = \frac{\partial p}{\partial x} = -G \implies u(y)$ 为**抛物线速度剖面**：
  $$u(y) = \frac{G}{2\mu}(h^2 - y^2) \qquad \left(\text{若板位于 } y\in[0, h]\text{，则为 } u(y) = \frac{G}{2\mu}y(h-y)\right)$$
- **最大速度、切应力与流量**：
  $$u_{\max} = u(0) = \frac{Gh^2}{2\mu}, \qquad \sigma_{xy}(y) = \mu\frac{\mathrm{d}u}{\mathrm{d}y} = -Gy, \qquad q = \int_{-h}^{h} u(y)\,\mathrm{d}y = \frac{2Gh^3}{3\mu}$$

#### 3. 圆管 Hagen-Poiseuille 流动（半径 $R$、长 $L$ 的圆管压差驱动流）
- **几何与边界条件**：管壁 $r=R$ 处无滑移 $u(R) = 0$；管轴心 $r=0$ 处速度有限且对称 $u'(0) = 0$；轴向压降梯度 $G = -\frac{\mathrm{d}p}{\mathrm{d}z} = \frac{\Delta P}{L} > 0$。
- **柱坐标控制方程与积分步骤**：
  $$\frac{\mu}{r}\frac{\mathrm{d}}{\mathrm{d}r}\left(r\frac{\mathrm{d}u}{\mathrm{d}r}\right) = -G \implies r\frac{\mathrm{d}u}{\mathrm{d}r} = -\frac{G}{2\mu}r^2 + A$$
  由 $r=0$ 处导数有限得 $A = 0$；再积分一次并代入 $u(R)=0$ 得**旋转抛物面速度分布**：
  $$u(r) = \frac{G}{4\mu}(R^2 - r^2) = \frac{\Delta P}{4\mu L}(R^2 - r^2)$$
- **最大速度、平均速度与体积流量（Poiseuille 定律）**：
  $$u_{\max} = u(0) = \frac{\Delta P\,R^2}{4\mu L}, \qquad u_{\text{moy}} = \frac{1}{2}u_{\max}, \qquad Q = \int_0^R u(r)\,2\pi r\,\mathrm{d}r = \frac{\pi R^4 \Delta P}{8\mu L}$$

#### 4. 倾角 $\alpha$ 斜面上的重力驱动自由液膜流（Écoulement d'un film liquide sur un plan incliné）
- **几何与体力**：斜面沿 $\vec{e}_x$ 向下倾斜角 $\alpha$，液膜厚度为 $h$，体积力为重力 $\vec{f}_v = \rho\vec{g} = \rho g\sin\alpha\,\vec{e}_x - \rho g\cos\alpha\,\vec{e}_y$。
- **边界条件**：
  1. 底部固壁 $y=0$（无滑移边界）：$u(0) = 0$；
  2. 顶部自由液面 $y=h$（与大气压 $p_0$ 接触，外法向 $\vec{n}=\vec{e}_y$）：$\boldsymbol{\sigma}\cdot\vec{e}_y = -p_0\vec{e}_y \implies$ 法向给出 $p(h) = p_0$，切向给出**自由面零剪应力条件** $\sigma_{xy}(h) = \mu\frac{\mathrm{d}u}{\mathrm{d}y}(h) = 0$。
- **压强与半抛物线速度分布**：
  - 由 $y$ 向平衡 $-\frac{\partial p}{\partial y} - \rho g\cos\alpha = 0$ 及 $p(h)=p_0$ 得静水压强分布：
    $$p(y) = p_0 + \rho g\cos\alpha\,(h - y)$$
  - 由 $x$ 向平衡 $\mu\frac{\mathrm{d}^2 u}{\mathrm{d}y^2} + \rho g\sin\alpha = 0$ 及 $u(0)=0, \ u'(h)=0$ 得**半抛物线速度分布**：
    $$u(y) = \frac{\rho g\sin\alpha}{2\mu}\,y(2h - y)$$
- **切应力、自由面最大速度与单位宽度流量**：
  $$\sigma_{xy}(y) = \rho g\sin\alpha\,(h - y), \qquad u_{\max} = u(h) = \frac{\rho g\sin\alpha\,h^2}{2\mu}, \qquad q = \int_0^h u(y)\,\mathrm{d}y = \frac{\rho g\sin\alpha\,h^3}{3\mu}$$
