# CC1 题干法语词表（考场对照用）

> 试卷是法语。看不懂题干 = 会做也拿不到分。
> 用法：读题时逐词查这张表，把每个动词翻译成"要写什么"。

---

## 1 指令动词 —— 决定你写什么

| 法语 | 中文 | 卷面上要出现的东西 |
| :--- | :--- | :--- |
| **Montrer que / Démontrer que** | 证明 | 至少两步推导，最后一句 `Donc ...` |
| **En déduire que** | 由此推出 | 直接用上一问的结论，**不要重算** |
| **Justifier** | 说明理由 | 一句依据（定义／定理／边界条件），不用长 |
| **Vérifier que** | 验证 | 代进去算，得到 0 或恒等式 |
| **Calculer** | 计算 | 过程 + 结果（带单位） |
| **Déterminer** | 求 | 给出表达式，能算数值就带数值 |
| **Donner l'expression de** | 写出表达式 | 一个公式就够 |
| **Exprimer ... en fonction de ...** | 用…表示 | 结果里**只能出现**它指定的量 |
| **Tracer / Représenter / Faire un schéma** | 画图 | 坐标轴、箭头、关键点 |
| **Donner l'allure de** | 画大致形状 | 定性曲线，不必精确 |
| **Comparer** | 比较 | 分"相同点"和"不同点"两段 |
| **Commenter / Interpréter** | 评论／解释 | 一句物理意义 |
| **Préciser** | 明确说明 | 补一句限定条件 |
| **Rappeler** | 复述 | 背定义或公式，不推导 |
| **Conclure** | 下结论 | `On conclut que ...` |
| **Discuter** | 讨论 | 按情况分类 |
| **Indiquer / Placer** | 标出 | 在图上标位置或方向 |
| **Établir** | 建立 | 推导出方程 |
| **Montrer que ... s'annule** | 证明为零 | 算出 0 |
| **Montrer que ... est diagonal** | 证明是对角阵 | 非对角元全为 0 |

---

## 2 条件与连接词 —— 决定你用哪条公式

| 法语 | 中文 | 考试含义 |
| :--- | :--- | :--- |
| **Soit** | 设／给定 | 引入已知量 |
| **On considère** | 考虑 | 引入研究对象 |
| **On suppose que** | 假设 | 这是前提，后面可以直接用 |
| **On néglige** | 忽略 | 通常是体积力 → 平衡方程变 $\overrightarrow{\operatorname{div}}\boldsymbol{\sigma}=\vec{0}$ |
| **Sachant que** | 已知 | 白送的条件 |
| **tel que** | 满足／使得 | 后面是约束 |
| **quel que soit / pour tout** | 对任意 | 结论要普遍成立 |
| **à partir de** | 由…出发 | 指定起点 |
| **en utilisant** | 利用 | 指定工具 |
| **d'après** | 根据 | 引用已有结论 |
| **lorsque / quand** | 当…时 | 极限情形 |
| **au voisinage de** | 在…附近 | 局部展开 |
| **en l'absence de** | 没有…时 | 某项置零 |
| **dans le cas où** | 在…情形下 | 分支讨论 |
| **à quelle condition** | 在什么条件下 | 答案是一个不等式或方程 |

---

## 3 整句句式（两年真题里出现过的高频问法）

| 原句 | 你要做的 |
| :--- | :--- |
| `Le mouvement est-il plan ?` | 是非问：先答 Oui／Non，再给两条依据（$V_3=0$；$\partial V/\partial x_3=0$） |
| `Le mouvement est-il stationnaire ?` | 看**欧拉**速度是否显含 $t$ |
| `Préciser la nature du mouvement.` | 把平面／稳态／等体积／无旋／刚体逐条判一遍 |
| `Donner l'unité de α.` | 量纲分析，一句 `[α]=s⁻¹` |
| `Déterminer l'équation des trajectoires.` | 解 ODE 后**消去 $t$** |
| `Tracer le champ de vitesse sur le quadrillage.` | 九个网格点逐点画箭头 + 画几条轨迹 |
| `Quelles sont les similitudes et les différences avec un glissement simple ?` | 分"同"和"异"两段 |
| `Montrer que le champ de contraintes proposé est en équilibre.` | 展开 $\overrightarrow{\operatorname{div}}\boldsymbol{\sigma}$，逐式算 0 |
| `Déterminer les constantes à l'aide des conditions aux limites.` | 写外法向 → 写 $\boldsymbol{\sigma}\cdot\vec{n}$ → 在边界上令其等于 0 或给定值 → 解方程 |
| `Justifier qu'il s'agit d'un état de contraintes planes.` | 三句：分量为 0／上下表面自由／板很薄 |
| `Calculer la résultante et le moment résultant.` | 面积分，先用对称性消一次项 |
| `En déduire la nature du chargement.` | 合力为零 + 有扭矩 → 纯扭转 |
| `Déterminer la valeur maximale de α.` | 找最危险点（通常在 $r=R$ 或边界）→ 令 $\sigma_{\text{eq}}=\sigma_e$ |
| `Calculer le coefficient de sécurité.` | $C_s=\sigma_e/\max\sigma_{\text{eq}}$ |
| `Que peut-on dire de ... ?` | 列性质清单，不用长篇 |

---

## 4 名词（出现就要警觉）

**运动学**
`champ de vitesse 速度场`／`champ de déplacement 位移场`／`trajectoire 轨迹`／`ligne de courant 流线`／`ligne d'émission 脉线`／`point de stagnation 驻点`／`tenseur des déformations 应变张量`／`dilatation 伸长`／`glissement 滑移`／`direction principale 主方向`／`valeur propre 特征值`／`isochore 等体积`／`irrotationnel 无旋`

**应力**
`contraintes planes 平面应力`／`surface libre 自由表面`／`effort 作用力`／`résultante 合力`／`moment 力矩`／`torsion 扭转`／`traction 拉伸`／`compression 压缩`／`cisaillement pur 纯剪切`／`déviateur 偏张量`／`sphérique 球张量`／`critère de limite d'élasticité 屈服准则`／`coefficient de sécurité 安全系数`／`limite d'élasticité 弹性极限`

**几何**
`plaque mince 薄板`／`épaisseur e 厚度`／`rayon intérieur $R_i$ 内半径`／`rayon extérieur $R_e$ 外半径`／`axisymétrie 轴对称`／`section droite 横截面`

---

## 5 每个动词的答题开头句

| 动词 | 开头怎么写 |
| :--- | :--- |
| Montrer | `On calcule ... ; on obtient ... = 0, donc ...` |
| En déduire | `D'après le résultat précédent, ...` |
| Justifier | `En effet, ... (car ...)` |
| Vérifier | `On vérifie : ... = ... = 0.` |
| Déterminer | `On cherche ... tel que ... ; on trouve ...` |
| Exprimer en fonction de | `En remplaçant $X_i$ par ..., on obtient ...` |
| Comparer | `Similitudes : ... ; Différences : ...` |
| Conclure | `On conclut que le mouvement est ...` |

---

## 6 读题顺序（重要）

1. 先扫**动词**：是"证明"还是"求"？决定篇幅。
2. 再扫**给的量**：大写 $X$ 还是小写 $x$？决定拉格朗日还是欧拉。
3. 再扫**限定词**：`on néglige`、`plan`、`stationnaire`、`libre` —— 这些是给你省步骤的。
4. 最后才看具体公式。

**看不懂整句时，先翻译动词和"en fonction de"，80% 的题意就到了。**
