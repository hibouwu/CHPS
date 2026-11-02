# CC1 题型场景库（认题 → 动作 → 公式）

> 考场上一小时，来不及"想"。要做的是认出这是哪一类场景，然后套流程。
> 下面按"题目长什么样"组织，不是按章节。

---

## 0 拿到题先问四句

1. **给的是欧拉还是拉格朗日？** 大写 $X$ → 拉格朗日；小写 $x$ → 欧拉。
2. **问的是场还是单点？** "champ"／"en tout point" → 场；给一个矩阵 → 单点。
3. **问的是微分还是积分？** 梯度／散度／主值 → 微分；合力／力矩／流量 → 积分。
4. **有没有边界或阈值？** 边界 → 定常数；屈服 → 求极限载荷。

这四个答案基本决定了用哪一节。

---

## 1 运动学场景

| # | 题目长这样 | 你要做的动作 | 用哪组公式 |
| :--- | :--- | :--- | :--- |
| A1 | 给 $\vec{V}(x)$，问"nature du mouvement" | 四条判据逐个过：平面／稳态／等体积／无旋 | $\operatorname{div}\vec{V}$、$\mathbb{D}$、$\boldsymbol{\Omega}$ |
| A2 | 给 $\vec{V}(t,x)$，求轨迹 | 解 $\mathrm{d}x_i/\mathrm{d}t=V_i$，代初值，消 $t$ | 分离变量 |
| A3 | 给 $\vec{V}$，求流线 | 冻结 $t$，解 $\mathrm{d}x_1/V_1=\mathrm{d}x_2/V_2$ | 同上但 $t$ 当常数 |
| A4 | 求脉线 | 先求轨迹，再让出发时刻 $\tau$ 变 | 轨迹 + 参数 |
| A5 | 给 $\vec{V}$，求加速度 | 物质导数 | $\vec{\gamma}=\partial_t\vec{V}+(\nabla\vec{V})\cdot\vec{V}$ |
| A6 | 给 $\vec{\phi}(t,X)$，求速度 | 先对 $t$ 求导，再反解 $X_i$ 换成 $x_i$ | ${}^L\vec{V}\to{}^E\vec{V}$ |
| A7 | 给 $\vec{\phi}$，求 $\mathbb{F},J,\rho$ | 对 $X_j$ 求偏导；$\rho J=\rho_0$ | 定义式 |
| A8 | 求 $\mathbb{C},\mathbb{E}$ | $\mathbb{C}=\mathbb{F}^T\mathbb{F}$，$\mathbb{E}=\frac12(\mathbb{C}-\mathbb{I})$ | 定义式 |
| A9 | 求主应变／主方向 | 对角阵直接读；否则解 $2\times2$ | 特征值 |
| A10 | 问 HPP 何时成立 | $\|\nabla_0\vec{u}\|\ll1$ → 时间条件 | $\vert\alpha\vert t\ll1$ |
| A11 | 求线性化 $\boldsymbol{\varepsilon}$ | 一阶展开或对称梯度 | $\frac12(\nabla\vec{u}+\nabla\vec{u}^T)$ |
| A12 | 给 $\mathbb{C}$ 求伸长比 $\lambda(\vec{N})$ | $\lambda=\sqrt{\vec{N}\cdot\mathbb{C}\cdot\vec{N}}$ | 定义式 |
| A13 | 求变形后夹角／剪切角 | $\sin\gamma=C_{12}/\sqrt{C_{11}C_{22}}$ | 定义式 |
| A14 | 判断是否刚体 | 算 $\mathbb{D}$，全零才是 | 判据 |
| A15 | 给 $\boldsymbol{\varepsilon}(x)$ 求 $\vec{u}$ | 验相容性 → 积分 → **加刚体位移** | §附录 |
| A16 | 与标准运动比较 | 列表：同／异 | 基本运动表 |
| A17 | 在网格上画速度场 | 逐点算 $\vec{V}$，画箭头，再画几条轨迹 | 定性 |

**A1 是最常见的送分题**，四条判据背成一句话：
`平面（V₃=0）→ 稳态（欧拉速度不含 t）→ 等体积（div V=0）→ 无旋（Ω=0）→ 刚体（D=0）`。

**A2/A3 的区别只有一句**：轨迹是"跟着质点"，流线是"冻结时间"。稳态时两者重合。

---

## 2 应力场景

| # | 题目长这样 | 你要做的动作 | 用哪组公式 |
| :--- | :--- | :--- | :--- |
| B1 | 给 $\boldsymbol{\sigma}$ 和 $\vec{n}$，求 $\vec{T},\sigma_n,\tau$ | 五步链条 | $\vec{T}=\boldsymbol{\sigma}\vec{n}$… |
| B2 | 给矩阵，问属于哪类状态 | 五判据：迹／常数／零行列／纯剪切／$c\mathbb{I}$ | §3 |
| B3 | 求主应力、主方向、不变量 | 解特征方程 | $I_1,I_2,I_3$ |
| B4 | 求球张量／偏张量／静水压 | 减掉 $\frac13\operatorname{Tr}\boldsymbol{\sigma}\mathbb{I}$ | 分解式 |
| B5 | 给应力场，验证平衡 | 展开 $\overrightarrow{\operatorname{div}}\boldsymbol{\sigma}$ | 直角或柱坐标 |
| B6 | 由边界条件定常数 | 写外法向 → 写 $\boldsymbol{\sigma}\vec{n}$ → 令其等于给定值 | 边界条件 |
| B7 | 求合力／合力矩／扭矩 | 面积分，先对称性消一次项 | 极惯性矩 |
| B8 | 求 Tresca／von Mises 等效应力 | 先写三个主应力（**补 $\sigma_3=0$**） | 两准则 |
| B9 | 求最危险点与极限载荷 | 让 $\sigma_{\text{eq}}$ 最大，令其 $=\sigma_e$ | 单调性 |
| B10 | 求安全系数 | $C_s=\sigma_e/\max\sigma_{\text{eq}}$ | 定义 |
| B11 | 论证 contraintes planes | 三句话 | §4.2 |
| B12 | 求薄壁圆环／圆筒的 $\sigma_{rr},\sigma_{\theta\theta}$ | 径向平衡 + 内外边界 | $\sigma_{\theta\theta}=\sigma_{rr}+r\sigma_{rr}'$ |
| B13 | 由应变经胡克定律求应力 | 代本构 | $\boldsymbol{\sigma}=\lambda\operatorname{Tr}\boldsymbol{\varepsilon}\mathbb{I}+2\mu\boldsymbol{\varepsilon}$ |
| B14 | 判断某应力场是否为自应力场 | 无体力 + 边界自由 + 非零 | 定义 |

**B6 是整道大题的分水岭**。只记一句：**外法向从材料指向外部**。内孔是 $-\vec{e}_r$，外侧面是 $+\vec{e}_r$，上表面 $+\vec{e}_z$，下表面 $-\vec{e}_z$。

---

## 3 跨章组合题（真题的实际形态）

真题不会只考一个场景，通常是条链：

**链 1（2024）**
`给欧拉速度 → 判性质 → 积分求轨迹 → 画图 → 求 F,C,E → HPP 线性化 → 与简单剪切比较`

**链 2（2025）**
`给拉格朗日映射 → 求两种速度 → 判稳态 → 求 F,J,C,E → 主应变 → HPP → 与简单剪切比较`

**链 3（2024）**
`补应力矩阵 → 验平衡 → 边界自由 → 合力/扭矩 → Tresca/VM → 极限 α`

**链 4（2025）**
`论证平面应力 → 径向平衡求 σθθ → 内外边界定常数 → 屈服 → 极限 α`

两条运动学链的差别只有**起点**（欧拉还是拉格朗日），后面 70% 是同一套。两条应力链的共同骨架是：**平衡方程 → 边界条件 → 屈服**。

---

## 4 遇到没见过的题怎么办

三步，不要慌：

1. **找未知量**：题目最后要我给什么？一个常数？一个场？一个临界值？
2. **找已知场**：给的是 $\vec{V}$、$\vec{\phi}$、$\boldsymbol{\sigma}$ 还是 $\boldsymbol{\varepsilon}$？这决定第一步用哪个定义式。
3. **找方程**：只有三类方程可用——
   - 定义式（$\mathbb{F}=\nabla_0\vec{\phi}$，$\vec{T}=\boldsymbol{\sigma}\vec{n}$，$\mathbb{E}=\frac12(\mathbb{C}-\mathbb{I})$）
   - 守恒／平衡（$\rho J=\rho_0$，$\overrightarrow{\operatorname{div}}\boldsymbol{\sigma}+\vec{f}_v=\vec{0}$）
   - 边界与阈值（$\boldsymbol{\sigma}\vec{n}=\vec{T}^d$，$\sigma_{\text{eq}}=\sigma_e$）

**任何新题都是"三类方程 + 题目给的几何"拼出来的。** 想不出下一步时，把这三类方程在草稿上列一遍，看哪一条里还剩未知量。

---

## 5 场景与速查表的对应

| 场景 | 去《CC1考场速查》 |
| :--- | :--- |
| A1、A6、A7、A8、A9、A10、A11、A16 | §2 |
| A2、A3、A5、A12、A13 | §2.1 + 定义 |
| B1、B2、B3、B4 | §3、§4 |
| B5、B12 | §5 |
| B6、B11 | §6 |
| B7 | §7 |
| B8、B9、B10 | §8 |
| A15、B13 | 附录 |
