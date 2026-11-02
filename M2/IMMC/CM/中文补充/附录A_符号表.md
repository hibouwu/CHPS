# 附录 A：符号表

原表：[Annexe 1 PDF](../IMMC_CM_Annexe1_2025-2026.pdf)。梯度和缩并采用本课程的约定。

| 符号 | Français / 中文含义 |
|---|---|
| $x_i$ | Coordonnées spatiales eulériennes courantes<br>欧拉描述中的当前空间坐标 |
| $X_i$ | Coordonnées lagrangiennes initiales<br>拉格朗日描述中的初始坐标 |
| $a$、$a(t,M)$ | Variable scalaire ; champ scalaire dépendant du temps et de la position<br>标量；依赖时间和位置的标量场 |
| $\mathbf a$ | Vecteur, ou tenseur d’ordre un<br>向量，即一阶张量 |
| $\mathbf A$ | Tenseur d’ordre deux, représenté dans une base<br>二阶张量，其分量随基底变化 |
| $\mathbf I$、$\delta_{ij}$ | Identité d’ordre deux ; symbole de Kronecker<br>二阶单位张量；Kronecker 符号 |
| $\epsilon_{ijk}$ | Symbole de Levi-Civita<br>Levi-Civita 符号，用于叉积等运算 |
| $\dot{(\bullet)},\ddot{(\bullet)}$ | Dérivées particulaires première et seconde en temps<br>沿物质粒子的时间一阶、二阶导数 |
| $\partial_t(\bullet)$ | Dérivée partielle en temps à coordonnées de description fixées<br>固定描述坐标下的时间偏导数 |
| $d(\bullet)/dt$ | Dérivée particulaire, ou matérielle<br>随体导数、物质导数 |
| $(\bullet)_{,i}$ | Dérivée partielle suivant la coordonnée spatiale indiquée<br>对第 $i$ 个空间坐标求偏导；须先确定使用 $x_i$ 还是 $X_i$ |
| $\llbracket\bullet\rrbracket_\Sigma$ | Saut à travers une interface<br>穿过界面 $\Sigma$ 时该量的跳跃 |
| $\mathbf A^{\mathsf T},\mathbf A^{-1},\mathbf A^{-\mathsf T}$ | Transposée, inverse, transposée de l’inverse<br>转置、逆、逆的转置 |
| $\mathbf A\mathbf b$ | Produit contracté simple tenseur–vecteur<br>张量与向量的单缩并，结果是向量 |
| $\mathbf A:\mathbf B$ | Produit doublement contracté ; convention du cours à vérifier pour les tenseurs non symétriques<br>两个二阶张量的双缩并；此课程采用 $\operatorname{tr}(\mathbf A\mathbf B)$ 约定，详见附录 B |
| $\operatorname{grad}a=\nabla a$ | Gradient d’un scalaire : vecteur<br>标量梯度，结果为向量 |
| $\operatorname{grad}\mathbf a$ | Gradient d’un vecteur : tenseur d’ordre deux<br>向量梯度，结果为二阶张量 |
| $\operatorname{div}\mathbf a$ | Divergence d’un vecteur : scalaire<br>向量散度，结果为标量 |
| $\operatorname{div}\mathbf A$ | Divergence d’un tenseur : vecteur<br>张量散度，结果为向量 |
| $\operatorname{rot}\mathbf a$ | Rotationnel d’un vecteur en trois dimensions<br>向量旋度；三维中结果为向量 |
| $\operatorname{rot}\mathbf A$ | Rotationnel d’un tenseur selon la convention indicielle du cours<br>二阶张量旋度，须按课程指标约定逐分量使用 |
| $\Delta a,\Delta\mathbf a,\Delta\mathbf A$ | Laplacien scalaire, vectoriel ou tensoriel<br>标量、向量、张量的 Laplace 算子 |

> **译注：**原符号表对冒号一行的法文写为“单缩并”，但两个二阶张量的该运算结果为标量，附录 B 将其称为双缩并；这里统一为“双缩并”。
