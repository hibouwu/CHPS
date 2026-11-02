# Immc：平台中文笔记

来源：EasyNote 笔记正文，2026-10-19 导出。这是平台生成的整理笔记，**不是教师逐字 transcript**，其中物理公式、术语与数值尚未逐条核对。请以教师课件为准。

```
# 连续介质中的变形测量与描述


## 变形的基本概念


* 变形（déformation）：材料或流体在受力或流动时，内部质点位置发生变化，导致距离和角度的改变。
* 连续介质（milieu continu）：假设物质连续分布，无空隙，适用于固体和流体的宏观描述。
* 变形的两种视角：
  + 拉格朗日视角（Lagrangian）：跟踪每个质点随时间的运动，关注质点的初始位置和变形后的坐标变化。
  + 欧拉视角（Eulerian）：关注空间中固定点的速度和变形率，强调变形的时间导数，即变形率（taux de déformation）。


---


## 拉格朗日视角下的变形描述


### 1. 变换函数与梯度


* 变换函数 ​\phi$\phi$​：描述质点从初始位置 ​\mathbf{X}$\mathbf{X}$​ 到当前实际位置 ​\mathbf{x}$\mathbf{x}$​ 的映射关系
  + 数学表达：​\mathbf{x} = \phi(\mathbf{X}, t)$\mathbf{x} = \phi(\mathbf{X}, t)$​
* 梯度（Gradient）：对变换函数 ​\phi$\phi$​ 关于空间变量求导，得到变形的局部性质
  + 公式：​d\mathbf{x} = \nabla \phi \cdot d\mathbf{X}$d\mathbf{x} = \nabla \phi \cdot d\mathbf{X}$​
  + 作用：反映质点间距离和角度的变化，区别于单纯的位移


### 2. 质点对的距离与角度变化


* 双质点（biparticule）：
  + 观察两质点间距离变化
  + 距离不变 → 无变形（刚体运动）
  + 距离变化 → 存在变形
* 三质点（triparticule）：
  + 观察三质点形成的角度变化
  + 角度变化 → 形状发生扭曲（如图像的拉伸、剪切）
  + 角度不变但距离变化 → 纯拉伸或压缩


### 3. 变形的类型示例


| 变形类型 | 描述 | 物理意义 | 示例 |
| --- | --- | --- | --- |
| 膨胀（dilatation） | 距离均匀增加 | 体积增大 | 泡沫膨胀 |
| 剪切（cisaillement） | 角度变化，形状扭曲 | 形状改变但体积不变 | 图像变成菱形 |
| 刚体运动 | 距离和角度均不变 | 无变形，仅平移或旋转 | 物体整体移动 |


---


## 小变形假设与线性化处理


* 小扰动假设（petites perturbations）：
  + 变形量很小，允许线性近似
  + 使得变形测量和数学处理简化，适用于大多数工程问题
* 优点：
  + 方程线性，易于求解
  + 适用范围广（超过95%的实际情况）
* 限制：
  + 大变形或非线性材料需更复杂模型


---


## 变形测量的数学表达


* 变形梯度张量：​\mathbf{F} = \nabla \phi$\mathbf{F} = \nabla \phi$​


  + 描述从初始配置到当前配置的局部变换
* 位置微分关系：


  ```
  d\mathbf{x} = \mathbf{F} \cdot d\mathbf{X}
  ```


  ```
  

$$
d\mathbf{x} = \mathbf{F} \cdot d\mathbf{X}
$$


  ```
* 通过 ​\mathbf{F}$\mathbf{F}$​，可以计算：


  + 距离变化：​|d\mathbf{x}|$|d\mathbf{x}|$​ 与 ​|d\mathbf{X}|$|d\mathbf{X}|$​ 的比值
  + 角度变化：通过内积和夹角计算


---


## 实际应用示例


* 泡沫材料：观察气泡间距和形状变化，判断材料的弹性和塑性变形
* 流体流动：利用欧拉视角测量局部变形率，分析剪切流和涡旋结构
* 图像处理：通过三质点角度变化模拟图像的几何变形，应用于图像校正和变形检测


---


> 注意：变形的定量测量依赖于对变换函数的空间导数计算，且在小变形假设下，线性模型足以描述大部分工程问题，复杂情况需引入非线性理论。


---


# 术语汇总


| 法语术语 | 中文翻译 | 说明 |
| --- | --- | --- |
| déformation | 变形 | 物体形状或尺寸的变化 |
| milieu continu | 连续介质 | 假设物质连续分布的模型 |
| transformation | 变换函数 | 描述质点位置变化的映射 |
| gradient de la transformation | 变换梯度 | 变换函数的空间导数 |
| taux de déformation | 变形率 | 变形随时间的变化速率 |
| petites perturbations | 小扰动假设 | 线性化处理的前提条件 |


---


# 关键公式总结


| 公式 | 说明 |
| --- | --- |
| ​​\mathbf{x} = \phi(\mathbf{X}, t)$\mathbf{x} = \phi(\mathbf{X}, t)$​ | 变换函数，质点位置映射 |
| ​​d\mathbf{x} = \nabla \phi \cdot d\mathbf{X}$d\mathbf{x} = \nabla \phi \cdot d\mathbf{X}$​ | 位置微分关系，描述局部变形 |
| ​​\mathbf{F} = \nabla \phi$\mathbf{F} = \nabla \phi$​ | 变形梯度张量 |


---


# 学习建议


* 掌握拉格朗日与欧拉两种视角的区别及应用场景
* 熟悉变形梯度的计算与物理意义
* 理解小变形假设的适用范围及其简化作用
* 通过实际案例（如泡沫、流体剪切）加深对变形类型的理解


---


# 张量与变换梯度


## 1. 张量的引入与定义


* 张量（tenseur）：推广向量的数学对象，表示多阶线性映射。
* 二阶张量：用双杠符号表示，如 ​\mathbf{F}$\mathbf{F}$​，表示变换的梯度张量。
* 变换梯度张量 ​\mathbf{F}$\mathbf{F}$​：定义为变换函数的梯度，即
  + ​​\mathbf{F} = \nabla \varphi$\mathbf{F} = \nabla \varphi$​，其中 ​\varphi$\varphi$​ 是向量值函数。
  + 作用：描述空间中点的变换局部性质。


### 梯度的阶数关系


| 输入函数类型 | 梯度结果类型 | 说明 |
| --- | --- | --- |
| 标量函数 | 向量 | 如温度梯度，指示最大变化方向 |
| 向量函数 | 二阶张量（矩阵） | 变换梯度张量​\mathbf{F}$\mathbf{F}$​ |
| 二阶张量 | 三阶张量 | 更高阶的梯度 |


> 梯度操作使阶数增加一级。


---


## 2. 梯度的物理意义与坐标系


* 梯度的求导变量：
  + 在拉格朗日描述中，梯度是对初始位置坐标 ​M_0$M_0$​ 求导。
  + 在欧拉描述中，梯度是对当前空间坐标求导。
* 变换梯度张量 ​\mathbf{F}$\mathbf{F}$​ 表示从初始配置到当前配置的局部变换性质。


---


## 3. 变换梯度张量 ​\mathbf{F}$\mathbf{F}$​ 的性质


| 性质 | 说明 |
| --- | --- |
| 无量纲 | 位置的导数对位置求导，单位相互抵消，结果无单位 |
| 无变形时为单位张量 | 无变形且无旋转时，​\mathbf{F} = \mathbf{I}$\mathbf{F} = \mathbf{I}$​（单位矩阵） |
| 旋转时为正交矩阵 | 纯刚体旋转时，​\mathbf{F}$\mathbf{F}$​ 是旋转矩阵，保持长度和角度不变 |
| 对称性 | 无旋转时，​\mathbf{F}$\mathbf{F}$​ 对称；有旋转时，含非对称成分 |


> 通过 ​\mathbf{F}$\mathbf{F}$​ 的对称性和结构，可以判断变换中是否存在旋转。


---


## 4. 变换梯度张量的计算与应用


### 4.1 变换的微分表达


* 设初始点 ​M_0$M_0$​，邻近点 ​N_0$N_0$​，变换后对应点为 ​M$M$​ 和 ​N$N$​。
* 变换函数：​M = \varphi(M_0)$M = \varphi(M_0)$​，​N = \varphi(N_0)$N = \varphi(N_0)$​。
* 近似表达：


  ```
  \overrightarrow{MN} \approx \mathbf{F} \cdot \overrightarrow{M_0 N_0}
  ```


  ```
  

$$
\overrightarrow{MN} \approx \mathbf{F} \cdot \overrightarrow{M_0 N_0}
$$


  ```


  其中，​\mathbf{F} = \nabla \varphi$\mathbf{F} = \nabla \varphi$​ 是变换梯度张量。


### 4.2 物理意义


* 该表达式表示，初始两个极近点之间的向量经过变换梯度张量线性映射，得到当前两个点间的向量。
* 这是局部线性近似，类似泰勒展开的一级项，忽略高阶导数。


---


## 5. 长度变化的比较


* 研究变形时常比较初始长度和变形后长度的平方：
  + 初始长度平方：​|\overrightarrow{M_0 N_0}|^2$|\overrightarrow{M_0 N_0}|^2$​
  + 变形后长度平方：​|\overrightarrow{MN}|^2$|\overrightarrow{MN}|^2$​
* 利用 ​\mathbf{F}$\mathbf{F}$​，长度变化可写为：

  ```
  |\overrightarrow{MN}|^2 = (\mathbf{F} \cdot \overrightarrow{M_0 N_0}) \cdot (\mathbf{F} \cdot \overrightarrow{M_0 N_0}) = \overrightarrow{M_0 N_0}^T \mathbf{F}^T \mathbf{F} \overrightarrow{M_0 N_0}
  ```


  ```
  

$$
|\overrightarrow{MN}|^2 = (\mathbf{F} \cdot \overrightarrow{M_0 N_0}) \cdot (\mathbf{F} \cdot \overrightarrow{M_0 N_0}) = \overrightarrow{M_0 N_0}^T \mathbf{F}^T \mathbf{F} \overrightarrow{M_0 N_0}
$$


  ```
* 该表达式用于分析局部变形性质，如拉伸、压缩。


---


## 6. 变换梯度张量的实际应用示例


* 材料力学：描述材料在受力后的局部变形状态。
* 流体力学：描述流体微元的变形和旋转。
* 计算机图形学：模拟物体变形和动画中的局部变换。
* 机器人学：分析机械臂末端执行器的位姿变化。


---


# 术语总结


| 术语 | 定义与说明 |
| --- | --- |
| 张量（tenseur） | 多阶线性映射的数学对象，推广向量和矩阵 |
| 变换梯度张量​\mathbf{F}$\mathbf{F}$​ | 变换函数的梯度，描述局部变换性质的二阶张量 |
| 拉格朗日描述 | 以物质点初始位置为参考系描述运动 |
| 欧拉描述 | 以空间固定点为参考系描述运动 |
| 旋转矩阵 | 正交矩阵，描述刚体旋转 |
| 单位张量​\mathbf{I}$\mathbf{I}$​ | 对角线为1的单位矩阵，表示无变形无旋转 |


---


> 注意：理解变换梯度张量的物理意义和数学性质，是分析连续介质力学和变形问题的基础。


# 变形梯度张量与长度变化分析


## 位置矢量与变形梯度张量关系


* 设粒子 N 当前的位置矢量为 ​\vec{r}_N$\vec{r}_N$​，原点到粒子 M 的位置矢量为 ​\vec{r}_M$\vec{r}_M$​，两者初始位置分别为 ​\vec{r}_{N0}$\vec{r}_{N0}$​ 和 ​\vec{r}_{M0}$\vec{r}_{M0}$​。
* 对于无限接近的粒子对 ​(M, N)$(M, N)$​，有：


  ```
  \vec{r}_N = \vec{r}_M + \mathbf{F} \cdot (\vec{r}_{N0} - \vec{r}_{M0})
  ```


  ```
  

$$
\vec{r}_N = \vec{r}_M + \mathbf{F} \cdot (\vec{r}_{N0} - \vec{r}_{M0})
$$


  ```


  其中，​\mathbf{F}$\mathbf{F}$​ 是在点 ​M_0$M_0$​ 处的变形梯度张量，描述了从初始配置到当前配置的局部变形。
* 通过分解路径（如Shal关系），可以将从 ​M$M$​ 到 ​N$N$​ 的矢量表示为起点到 ​M$M$​ 的矢量加上 ​M$M$​ 到 ​N$N$​ 的矢量，进而引入变形梯度张量。


---


## 长度平方的表达与变形梯度张量


* 目标：将当前两粒子间矢量的长度平方与初始长度平方联系起来。
* 设当前矢量为 ​\vec{r}_{MN} = \vec{r}_N - \vec{r}_M$\vec{r}_{MN} = \vec{r}_N - \vec{r}_M$​，初始矢量为 ​\vec{r}_{M0N0} = \vec{r}_{N0} - \vec{r}_{M0}$\vec{r}_{M0N0} = \vec{r}_{N0} - \vec{r}_{M0}$​。
* 当前长度平方：


  ```
  \|\vec{r}_{MN}\|^2 = \vec{r}_{MN}^T \vec{r}_{MN}
  ```


  ```
  

$$
\|\vec{r}_{MN}\|^2 = \vec{r}_{MN}^T \vec{r}_{MN}
$$


  ```
* 代入变形梯度张量表达：


  ```
  \vec{r}_{MN} = \mathbf{F} \cdot \vec{r}_{M0N0}
  ```


  ```
  

$$
\vec{r}_{MN} = \mathbf{F} \cdot \vec{r}_{M0N0}
$$


  ```


  则


  ```
  \|\vec{r}_{MN}\|^2 = (\mathbf{F} \cdot \vec{r}_{M0N0})^T (\mathbf{F} \cdot \vec{r}_{M0N0}) = \vec{r}_{M0N0}^T \mathbf{F}^T \mathbf{F} \vec{r}_{M0N0}
  ```


  ```
  

$$
\|\vec{r}_{MN}\|^2 = (\mathbf{F} \cdot \vec{r}_{M0N0})^T (\mathbf{F} \cdot \vec{r}_{M0N0}) = \vec{r}_{M0N0}^T \mathbf{F}^T \mathbf{F} \vec{r}_{M0N0}
$$


  ```
* 初始长度平方：


  ```
  \|\vec{r}_{M0N0}\|^2 = \vec{r}_{M0N0}^T \vec{r}_{M0N0}
  ```


  ```
  

$$
\|\vec{r}_{M0N0}\|^2 = \vec{r}_{M0N0}^T \vec{r}_{M0N0}
$$


  ```
* 计算长度变化：


  ```
  \|\vec{r}_{MN}\|^2 - \|\vec{r}_{M0N0}\|^2 = \vec{r}_{M0N0}^T (\mathbf{F}^T \mathbf{F} - \mathbf{I}) \vec{r}_{M0N0}
  ```


  ```
  

$$
\|\vec{r}_{MN}\|^2 - \|\vec{r}_{M0N0}\|^2 = \vec{r}_{M0N0}^T (\mathbf{F}^T \mathbf{F} - \mathbf{I}) \vec{r}_{M0N0}
$$


  ```


  其中，​\mathbf{I}$\mathbf{I}$​ 是单位张量。


> 关键点：​\mathbf{C} = \mathbf{F}^T \mathbf{F}$\mathbf{C} = \mathbf{F}^T \mathbf{F}$​ 称为右Cauchy-Green变形张量，它是一个对称张量，描述了变形引起的长度和角度变化。


---


## 右Cauchy-Green变形张量 ​\mathbf{C}$\mathbf{C}$​


| 特性 | 说明 |
| --- | --- |
| 定义 | ​​\mathbf{C} = \mathbf{F}^T \mathbf{F}$\mathbf{C} = \mathbf{F}^T \mathbf{F}$​ |
| 对称性 | ​​\mathbf{C} = \mathbf{C}^T$\mathbf{C} = \mathbf{C}^T$​ |
| 物理意义 | 描述材料点的局部拉伸（长度变化）和角度变化 |
| 主对角线元素 | ​​C_{11}, C_{22}, C_{33}$C_{11}, C_{22}, C_{33}$​ 表示沿基向量方向的拉伸平方 |
| 非对角线元素 | 反映初始方向间角度的变化 |


### 拉伸与变形的关系


* 拉伸（dilatation）定义为当前长度与初始长度的比值：


  ```
  \lambda = \frac{\text{当前长度}}{\text{初始长度}}
  ```


  ```
  

$$
\lambda = \frac{\text{当前长度}}{\text{初始长度}}
$$


  ```
* 拉伸平方即为 ​\lambda^2$\lambda^2$​，对应 ​\mathbf{C}$\mathbf{C}$​ 的特征值。
* 例子：


  + 若长度加倍，拉伸 ​\lambda = 2$\lambda = 2$​，拉伸平方为 ​4$4$​。
  + 若长度不变，​\lambda = 1$\lambda = 1$​，​\mathbf{C} = \mathbf{I}$\mathbf{C} = \mathbf{I}$​。
  + 若长度缩短，​\lambda < 1$\lambda < 1$​，表示收缩。


> 注意：​\mathbf{C} = \mathbf{I}$\mathbf{C} = \mathbf{I}$​ 表示无变形，只有刚体运动（旋转和平移）。


---


## 变形的几何解释


* 无变形条件：


  ```
  \mathbf{F}^T \mathbf{F} = \mathbf{I} \implies \text{刚体运动}
  ```


  ```
  

$$
\mathbf{F}^T \mathbf{F} = \mathbf{I} \implies \text{刚体运动}
$$


  ```
* 变形存在时：


  + ​​\mathbf{C}$\mathbf{C}$​ 的特征值不全为1，表示不同方向的拉伸或压缩。
  + 非对角元素非零，表示角度变化（剪切变形）。


---


## 公式总结


| 量 | 表达式 | 说明 |
| --- | --- | --- |
| 变形梯度张量 | ​​\mathbf{F}$\mathbf{F}$​ | 描述从初始到当前的局部变形 |
| 右Cauchy-Green张量 | ​​\mathbf{C} = \mathbf{F}^T \mathbf{F}$\mathbf{C} = \mathbf{F}^T \mathbf{F}$​ | 对称张量，描述拉伸和角度变化 |
| 当前长度平方 | ​​\|\vec{r}_{MN}\|^2 = \vec{r}_{M0N0}^T \mathbf{C} \vec{r}_{M0N0}$|\vec{r}_{MN}|^2 = \vec{r}_{M0N0}^T \mathbf{C} \vec{r}_{M0N0}$​ | 变形后长度的平方 |
| 长度变化量 | ​​\Delta = \vec{r}_{M0N0}^T (\mathbf{C} - \mathbf{I}) \vec{r}_{M0N0}$\Delta = \vec{r}_{M0N0}^T (\mathbf{C} - \mathbf{I}) \vec{r}_{M0N0}$​ | 长度平方的变化 |


---


## 实际应用示例


* 材料力学：通过测量变形前后粒子间距离，利用 ​\mathbf{C}$\mathbf{C}$​ 判断材料的局部拉伸和压缩情况。
* 图像变形：在图像处理中的形变分析，​\mathbf{F}$\mathbf{F}$​ 和 ​\mathbf{C}$\mathbf{C}$​ 用于描述像素点的局部变形。
* 生物力学：分析组织或细胞的形变，判断其受力状态。


---


> 重要提示：理解变形梯度张量及其派生的右Cauchy-Green张量是连续介质力学中描述变形的核心，掌握它们有助于深入理解材料的力学行为和变形特性。


# 变形张量与Green-Lagrange变形算子


## 关键概念


* 变形梯度张量 ​F$F$​：描述物体从初始配置到当前配置的变形映射，无单位。
* 右Cauchy-Green变形张量 ​C = F^T F$C = F^T F$​：
  + 描述变形的拉伸和旋转成分。
  + 是一个对称张量，反映了变形的平方伸长。
  + 单位同样无量纲。
* Green-Lagrange变形张量 ​E$E$​：
  + 定义为

    ```
    E = \frac{1}{2}(C - I) = \frac{1}{2}(F^T F - I)
    ```


    ```
    

$$
E = \frac{1}{2}(C - I) = \frac{1}{2}(F^T F - I)
$$


    ```
  + 通过减去单位张量​I$I$​，去除初始配置的影响，只保留变形部分。
  + 对称张量，反映了相对长度的平方变化和角度变化。
  + 对角线元素表示沿空间三个方向的相对长度变化（平方）。
  + 非对角线元素表示纤维间角度的变化。


> 注意：Green-Lagrange变形张量中的因子​\frac{1}{2}$\frac{1}{2}$​容易被忽略，但非常重要。


---


## 变形张量的物理意义


| 张量 | 物理意义 | 主要特征 | 备注 |
| --- | --- | --- | --- |
| ​​F$F$​ | 变形梯度 | 无单位，包含旋转和拉伸 | 基础变形描述 |
| ​​C = F^T F$C = F^T F$​ | 右Cauchy-Green张量 | 对称，无单位，描述平方伸长 | 包含旋转信息 |
| ​​E = \frac{1}{2}(C - I)$E = \frac{1}{2}(C - I)$​ | Green-Lagrange变形张量 | 对称，描述纯变形（拉伸和角度变化） | 去除初始配置影响 |


* 当​E=0$E=0$​时，表示刚体运动（无变形）。
* ​​E$E$​的对角线元素为长度的相对平方变化，例如50%变形对应长度变化的平方约为0.5。
* 非对角线元素反映角度变化，描述纤维间的剪切变形。


---


## 位移与变形梯度的关系


* 位移向量 ​\mathbf{U}$\mathbf{U}$​：表示粒子从初始位置​\mathbf{M}_0$\mathbf{M}_0$​到当前位移位置​\mathbf{M}$\mathbf{M}$​的矢量差


  ```
  \mathbf{U} = \mathbf{M} - \mathbf{M}_0
  ```


  ```
  

$$
\mathbf{U} = \mathbf{M} - \mathbf{M}_0
$$


  ```
* 位移不反映路径，只反映初末位置差，适用于小扰动分析。
* 变形梯度张量​F$F$​可以分解为：


  ```
  F = I + \nabla \mathbf{U}
  ```


  ```
  

$$
F = I + \nabla \mathbf{U}
$$


  ```


  其中，​\nabla \mathbf{U}$\nabla \mathbf{U}$​是位移场的梯度张量。
* 变形张量​E$E$​可用位移梯度表示为：


  ```
  E = \frac{1}{2} \left[ (I + \nabla \mathbf{U})^T (I + \nabla \mathbf{U}) - I \right]
  ```


  ```
  

$$
E = \frac{1}{2} \left[ (I + \nabla \mathbf{U})^T (I + \nabla \mathbf{U}) - I \right]
$$


  ```


---


## 公式与符号说明


| 符号 | 含义 | 备注 |
| --- | --- | --- |
| ​​F$F$​ | 变形梯度张量 | 描述变形映射 |
| ​​F^T$F^T$​ | ​​F$F$​的转置 |  |
| ​​C = F^T F$C = F^T F$​ | 右Cauchy-Green张量 | 对称张量 |
| ​​I$I$​ | 单位张量 | 初始配置 |
| ​​E = \frac{1}{2}(C - I)$E = \frac{1}{2}(C - I)$​ | Green-Lagrange变形张量 | 纯变形描述 |
| ​​\mathbf{U}$\mathbf{U}$​ | 位移向量 | 粒子位置变化 |
| ​​\nabla \mathbf{U}$\nabla \mathbf{U}$​ | 位移梯度 | 描述局部变形 |


---


## 实际应用示例


* 泡沫材料拉伸：假设泡沫沿某方向拉伸50%，则Green-Lagrange张量对应方向的对角线元素约为0.5，反映长度平方的相对变化。
* 刚体运动判定：若​E=0$E=0$​，则无变形，仅刚体平移或旋转。
* 小变形假设：位移​\mathbf{U}$\mathbf{U}$​较小，​\nabla \mathbf{U}$\nabla \mathbf{U}$​也小，​E$E$​可近似线性化，简化计算。


---


> 重要提示：
>
>
>
> * Green-Lagrange变形张量适用于大变形分析，能准确描述非线性变形。
> * 位移和变形梯度的关系是理解材料变形的基础，尤其在有限元分析和连续介质力学中广泛应用。


# 小扰动假设下的变形张量分析


---


## 1. 变形梯度与张量乘积展开


* 设有位移场梯度 ​\nabla \mathbf{U}$\nabla \mathbf{U}$​，单位张量为 ​\mathbf{I}$\mathbf{I}$​。
* 计算乘积时，得到以下项：


  + ​​\mathbf{I} \times \mathbf{I} = \mathbf{I}$\mathbf{I} \times \mathbf{I} = \mathbf{I}$​
  + ​​\mathbf{I} \times \nabla \mathbf{U} = \nabla \mathbf{U}$\mathbf{I} \times \nabla \mathbf{U} = \nabla \mathbf{U}$​
  + ​​(\nabla \mathbf{U})^T \times \mathbf{I} = (\nabla \mathbf{U})^T$(\nabla \mathbf{U})^T \times \mathbf{I} = (\nabla \mathbf{U})^T$​
  + ​​(\nabla \mathbf{U})^T \times \nabla \mathbf{U}$(\nabla \mathbf{U})^T \times \nabla \mathbf{U}$​（二次项）
  + 减去 ​\mathbf{I}$\mathbf{I}$​，单位张量相互抵消
* 剩余项：


  + 一阶项：​\nabla \mathbf{U} + (\nabla \mathbf{U})^T$\nabla \mathbf{U} + (\nabla \mathbf{U})^T$​
  + 二阶项：​(\nabla \mathbf{U})^T \times \nabla \mathbf{U}$(\nabla \mathbf{U})^T \times \nabla \mathbf{U}$​


> 二阶项为非线性项，通常在小扰动假设下可忽略。


---


## 2. 小扰动假设（Hypothèse des petites perturbations, HPP）


### 定义与条件


* 小扰动：位移和变形均很小，意味着变换接近单位变换，​\mathbf{F} \approx \mathbf{I}$\mathbf{F} \approx \mathbf{I}$​。
* 位移场梯度的范数 ​\|\nabla \mathbf{U}\|$\|\nabla \mathbf{U}\|$​ 很小。
* 结构的初始配置与当前配置几乎重合。
* 变换为无限小（infinitésimales），即数学上趋近于零。


### 范数定义


* 使用无穷范数（max范数）：


  ```
  \|\mathbf{A}\|_\infty = \max_{i,j} |A_{ij}|
  ```


  ```
  

$$
\|\mathbf{A}\|_\infty = \max_{i,j} |A_{ij}|
$$


  ```
* 该范数用于判断张量分量是否足够小，保证模型适用。


### 物理含义


* 小扰动意味着：
  + 位移小
  + 变形小
  + 旋转小（后续详细讨论）


> 注意：小变形不等于小变换。大旋转可导致大变换，即使变形小。


---


## 3. 变形张量的不同表达形式


### 3.1 Green-Lagrange变形张量


* 定义：


  ```
  \mathbf{E} = \frac{1}{2} \left( \nabla \mathbf{U} + (\nabla \mathbf{U})^T + (\nabla \mathbf{U})^T \nabla \mathbf{U} \right)
  ```


  ```
  

$$
\mathbf{E} = \frac{1}{2} \left( \nabla \mathbf{U} + (\nabla \mathbf{U})^T + (\nabla \mathbf{U})^T \nabla \mathbf{U} \right)
$$


  ```
* 其中：


  + ​​\nabla \mathbf{U}$\nabla \mathbf{U}$​：位移梯度张量
  + ​​(\nabla \mathbf{U})^T \nabla \mathbf{U}$(\nabla \mathbf{U})^T \nabla \mathbf{U}$​：非线性二阶项
* 适用于大变形分析。


### 3.2 线性化变形张量（无限小变形张量）


* 在小扰动假设下，忽略二阶项：


  ```
  \boldsymbol{\varepsilon} = \frac{1}{2} \left( \nabla \mathbf{U} + (\nabla \mathbf{U})^T \right)
  ```


  ```
  

$$
\boldsymbol{\varepsilon} = \frac{1}{2} \left( \nabla \mathbf{U} + (\nabla \mathbf{U})^T \right)
$$


  ```
* 该张量为对称张量，称为线性化变形张量或无限小变形张量。


---


## 4. 张量的对称与反对称分解


* 任意二阶张量 ​\mathbf{A}$\mathbf{A}$​ 可分解为：


  ```
  \mathbf{A} = \mathbf{A}_\text{sym} + \mathbf{A}_\text{antisym}
  ```


  ```
  

$$
\mathbf{A} = \mathbf{A}_\text{sym} + \mathbf{A}_\text{antisym}
$$


  ```
* 其中：


  + 对称部分：


    ```
    \mathbf{A}_\text{sym} = \frac{1}{2} (\mathbf{A} + \mathbf{A}^T)
    ```


    ```
    

$$
\mathbf{A}_\text{sym} = \frac{1}{2} (\mathbf{A} + \mathbf{A}^T)
$$


    ```
  + 反对称部分：


    ```
    \mathbf{A}_\text{antisym} = \frac{1}{2} (\mathbf{A} - \mathbf{A}^T)
    ```


    ```
    

$$
\mathbf{A}_\text{antisym} = \frac{1}{2} (\mathbf{A} - \mathbf{A}^T)
$$


    ```
* 应用到位移梯度：


  | 部分 | 物理意义 |
  | --- | --- |
  | ​​\boldsymbol{\varepsilon} = \mathbf{A}_\text{sym}$\boldsymbol{\varepsilon} = \mathbf{A}_\text{sym}$​ | 变形（拉伸、压缩、剪切） |
  | ​​\boldsymbol{\omega} = \mathbf{A}_\text{antisym}$\boldsymbol{\omega} = \mathbf{A}_\text{antisym}$​ | 小旋转 |


> 小扰动假设中，变形由对称部分描述，旋转由反对称部分描述。


---


## 5. 物理与数学联系


| 术语 | 符号 | 物理意义 | 数学表达式 |
| --- | --- | --- | --- |
| 位移梯度张量 | ​​\nabla \mathbf{U}$\nabla \mathbf{U}$​ | 位移场的空间变化率 | ​​\frac{\partial U_i}{\partial X_j}$\frac{\partial U_i}{\partial X_j}$​ |
| Green-Lagrange张量 | ​​\mathbf{E}$\mathbf{E}$​ | 大变形下的变形度 | ​​\frac{1}{2}(\nabla \mathbf{U} + (\nabla \mathbf{U})^T + (\nabla \mathbf{U})^T \nabla \mathbf{U})$\frac{1}{2}(\nabla \mathbf{U} + (\nabla \mathbf{U})^T + (\nabla \mathbf{U})^T \nabla \mathbf{U})$​ |
| 线性化变形张量 | ​​\boldsymbol{\varepsilon}$\boldsymbol{\varepsilon}$​ | 小变形假设下的变形 | ​​\frac{1}{2}(\nabla \mathbf{U} + (\nabla \mathbf{U})^T)$\frac{1}{2}(\nabla \mathbf{U} + (\nabla \mathbf{U})^T)$​ |
| 旋转张量 | ​​\boldsymbol{\omega}$\boldsymbol{\omega}$​ | 小旋转 | ​​\frac{1}{2}(\nabla \mathbf{U} - (\nabla \mathbf{U})^T)$\frac{1}{2}(\nabla \mathbf{U} - (\nabla \mathbf{U})^T)$​ |


---


## 6. 实际应用与注意事项


* 小扰动假设简化了非线性问题，便于线性化处理和求解。
* 适用于工程中微小变形分析，如结构弹性变形、微小振动等。
* 验证条件：需检查位移梯度范数是否足够小，确保模型有效。
* 误区警示：
  + 小变形不代表小旋转，旋转可能导致非线性效应。
  + 线性化模型不适用于大变形、大旋转情况。


---


## 7. 数学符号补充


* Kronecker delta ​\delta_{ij}$\delta_{ij}$​：


  ```
  \delta_{ij} = \begin{cases}
  1 & i = j \\
  0 & i \neq j
  \end{cases}
  ```


  ```
  

$$
\delta_{ij} = \begin{cases}
1 & i = j \\
0 & i \neq j
\end{cases}
$$


  ```
* 用于表示单位张量的分量。


---


# 公式汇总


```
\begin{aligned}
&\mathbf{E} = \frac{1}{2} \left( \nabla \mathbf{U} + (\nabla \mathbf{U})^T + (\nabla \mathbf{U})^T \nabla \mathbf{U} \right) \\
&\boldsymbol{\varepsilon} = \frac{1}{2} \left( \nabla \mathbf{U} + (\nabla \mathbf{U})^T \right) \\
&\boldsymbol{\omega} = \frac{1}{2} \left( \nabla \mathbf{U} - (\nabla \mathbf{U})^T \right) \\
&\|\mathbf{A}\|_\infty = \max_{i,j} |A_{ij}| \\
&\delta_{ij} = \begin{cases}
1 & i = j \\
0 & i \neq j
\end{cases}
\end{aligned}
```


```


$$
\begin{aligned}
&\mathbf{E} = \frac{1}{2} \left( \nabla \mathbf{U} + (\nabla \mathbf{U})^T + (\nabla \mathbf{U})^T \nabla \mathbf{U} \right) \\
&\boldsymbol{\varepsilon} = \frac{1}{2} \left( \nabla \mathbf{U} + (\nabla \mathbf{U})^T \right) \\
&\boldsymbol{\omega} = \frac{1}{2} \left( \nabla \mathbf{U} - (\nabla \mathbf{U})^T \right) \\
&\|\mathbf{A}\|_\infty = \max_{i,j} |A_{ij}| \\
&\delta_{ij} = \begin{cases}
1 & i = j \\
0 & i \neq j
\end{cases}
\end{aligned}
$$


```


---


# 例题提示


* 给定位移场 ​\mathbf{U}$\mathbf{U}$​，计算其梯度 ​\nabla \mathbf{U}$\nabla \mathbf{U}$​。
* 判断是否满足小扰动假设（计算无穷范数）。
* 计算线性化变形张量 ​\boldsymbol{\varepsilon}$\boldsymbol{\varepsilon}$​ 和旋转张量 ​\boldsymbol{\omega}$\boldsymbol{\omega}$​。
* 分析变形与旋转对结构的影响。


---


> 重要：理解张量的对称与反对称分解是掌握小扰动假设下变形分析的关键。切勿将小变形等同于小变换，旋转效应需单独考虑。


# 小变形假设与线性应变张量


## 小变形假设（Petites perturbations）


* 定义：假设变形和旋转都很小，忽略二次及以上的小量项。
* 注意事项：
  + 若存在较大旋转，使用线性应变张量可能导致非零应变结果，而实际应变应为零。
  + 线性应变张量只适用于小变形条件，超出该范围时需使用完整的应变张量形式。


---


# 工程应变（Déformation de l'ingénieur）


* 定义：工程应变是线性化应变张量的对角线分量，表示长度变化的相对量。
* 公式：


  ```
  \varepsilon = \frac{L - L_0}{L_0}
  ```


  ```
  

$$
\varepsilon = \frac{L - L_0}{L_0}
$$


  ```


  其中，


  + ​​L_0$L_0$​：初始长度
  + ​​L$L$​：变形后长度
* 特点：


  + 适用于小变形，计算简单。
  + 工程师常用此简化模型进行线性计算。


---


# 应变张量与位移场的关系


## 应变张量的计算


* 位移场：​\mathbf{u} = (u_1, u_2, u_3)$\mathbf{u} = (u_1, u_2, u_3)$​，三分量向量场。
* 应变张量：对位移场求梯度并取对称部分，得到对称的6分量应变张量。


  ```
  \varepsilon_{ij} = \frac{1}{2} \left( \frac{\partial u_i}{\partial x_j} + \frac{\partial u_j}{\partial x_i} \right)
  ```


  ```
  

$$
\varepsilon_{ij} = \frac{1}{2} \left( \frac{\partial u_i}{\partial x_j} + \frac{\partial u_j}{\partial x_i} \right)
$$


  ```
* 维度关系：


  | 物理量 | 维度 | 分量数 |
  | --- | --- | --- |
  | 位移场​\mathbf{u}$\mathbf{u}$​ | 向量 | 3 |
  | 应变张量​\varepsilon$\varepsilon$​ | 对称张量 | 6 |


## 逆问题：从应变场恢复位移场


* 不是所有应变场都对应一个连续的位移场。
* 应变场必须满足兼容性条件，才能保证存在对应的位移场。


---


# 应变兼容性条件（Équations de compatibilité）


## 物理意义


* 位移场必须连续，导致应变场满足一定的偏微分方程。
* 兼容性条件保证应变场是由某个连续位移场产生的。


## 数学表达


* 兼容性条件可简化为：


  ```
  \nabla \times (\nabla \times \varepsilon^T) = 0
  ```


  ```
  

$$
\nabla \times (\nabla \times \varepsilon^T) = 0
$$


  ```


  其中，​\varepsilon^T$\varepsilon^T$​为应变张量的转置，​\nabla \times$\nabla \times$​为旋度算子。
* 该条件源自施瓦茨定理（Théorème de Schwartz），即二阶偏导数的交换性。


## 兼容性方程的数量


* 由于对称性和定理限制，兼容性方程共有6个独立条件。


---


# 兼容应变场的典型形式


| 应变场类型 | 兼容性 | 说明 |
| --- | --- | --- |
| 零应变场 | 总是兼容 | ​​\varepsilon = 0$\varepsilon = 0$​，无变形，兼容性显然满足 |
| 常数应变场 | 总是兼容 | 各分量空间导数为零，兼容条件自动满足 |
| 线性（仿射）应变场 | 总是兼容 | 分量为空间坐标的一次多项式，兼容性成立 |
| 高阶多项式应变场 | 可能不兼容 | 需逐项验证兼容性方程 |


> 提示：只要应变场是空间坐标的二次以下多项式（常数、线性、仿射），兼容性自动满足，无需复杂计算。


---


# 应用示例


* 工程设计：常用线性应变模型简化计算，适用于小变形结构分析。
* 数值模拟：保证输入的应变场满足兼容性条件，确保位移场存在且连续。
* 材料力学：通过应变兼容性判断材料变形是否合理，避免非物理解。


---


# 关键公式汇总


| 公式 | 说明 |
| --- | --- |
| ​​\varepsilon_{ij} = \frac{1}{2} \left( \frac{\partial u_i}{\partial x_j} + \frac{\partial u_j}{\partial x_i} \right)$\varepsilon_{ij} = \frac{1}{2} \left( \frac{\partial u_i}{\partial x_j} + \frac{\partial u_j}{\partial x_i} \right)$​ | 线性应变张量定义 |
| ​​\varepsilon = \frac{L - L_0}{L_0}$\varepsilon = \frac{L - L_0}{L_0}$​ | 工程应变定义 |
| ​​\nabla \times (\nabla \times \varepsilon^T) = 0$\nabla \times (\nabla \times \varepsilon^T) = 0$​ | 应变兼容性条件 |


---


> 注意：使用线性应变张量时，必须确认小变形假设成立，且应变场满足兼容性条件，否则计算结果可能不准确或无物理意义。


# 材料变形与应力关系


## 关键概念


* **应变场（champ de déformation）**描述材料内部微小变形的分布，是位移场梯度的函数。
* **位移场（champ de déplacement）**材料点的实际移动，变形场通过积分得到位移场。
* **应力（contrainte）**作用在单位面积上的力，单位通常为帕斯卡（Pa）。
* **弹性极限（limite d'élasticité）**材料从弹性变形转变为塑性变形的临界点。
* **塑性变形（plasticité）**超过弹性极限后产生的不可逆变形。
* **延展性（ductilité）**材料在超过弹性极限后仍能继续变形的能力。
* 脆性材料（matériau fragile）
  几乎无塑性变形，超过弹性极限即断裂。


---


## 材料变形行为示例


| 材料类型 | 弹性变形范围（应变） | 塑性变形范围（应变） | 特点 | 典型材料示例 |
| --- | --- | --- | --- | --- |
| 延展性材料 | 约0.1% - 1% | 1% - 10% | 可产生较大塑性变形，断裂前变形明显 | 软钢、铝 |
| 脆性材料 | 极小（约0.1%以下） | 无 | 超过弹性极限即断裂，无塑性变形 | 玻璃、石灰石、混凝土 |


* 延展性材料：如软钢，能在弹性极限后继续拉伸，产生塑性变形，适合成形加工。
* 脆性材料：如混凝土，几乎不产生塑性变形，受拉即断裂，需配筋增强。


---


## 弹性与塑性阶段


* 弹性阶段应力与应变呈线性关系，变形可完全恢复。

  ```
  \sigma = E \varepsilon $$  
  其中，$\sigma$为应力，$E$为弹性模量，$\varepsilon$为应变。
  ```


  ```
  

$$
\sigma = E \varepsilon $$  
其中，$\sigma$为应力，$E$为弹性模量，$\varepsilon$为应变。
$$


  ```
* 塑性阶段
  超过弹性极限后，应力-应变关系非线性，产生不可逆变形。
  不同材料塑性阶段变形范围差异大。


> 注意：设计时应避免超过弹性极限，以防止材料永久变形或断裂。


---


## 混凝土与钢筋的复合应用


* 混凝土抗压强度较高，但抗拉强度极低，且几乎无塑性变形。
* 通过在混凝土中加入钢筋（钢缆），利用钢筋的高延展性承担拉应力，防止混凝土断裂。
* 预应力混凝土：钢缆在浇筑前被拉紧，浇筑后释放，钢缆对混凝土施加预压应力，提高混凝土抗拉能力和整体性能。


---


## 变形测量方法


| 方法 | 原理与特点 | 应用示例 |
| --- | --- | --- |
| 激光位移测量 | 利用激光束测量材料表面微小位移 | 高精度位移监测 |
| 机械比较仪 | 弹簧压头接触表面，测量相对位移 | 实验室材料变形测试 |
| 应变计（Extensomètre） | 粘贴于试样表面，测量长度变化 | 拉伸试验中测量局部应变 |
| 网格法（Méthode des grilles） | 在材料表面印制网格，观察网格变形（长度和角度变化） | 图像相关分析，二维应变场测量 |
| 电阻应变计 | 铜丝或金属丝制成蛇形线圈，变形时电阻变化测量应变 | 工业结构监测，动态应变测量 |


* 应变计原理：变形导致导体长度和截面积变化，进而改变电阻，电阻变化与应变成正比。


---


## 变形的两种基本特征


* 长度变化：相邻材料点间距离的变化，反映拉伸或压缩。
* 角度变化：相邻材料点间角度的变化，反映剪切变形。


---


> 关键点：理解材料的弹性极限和塑性行为对工程设计至关重要，合理选择材料及预应力技术能有效提升结构安全性和耐久性。


---


# 变形测量方法与基本变形类型


## 变形测量技术


### 应变计（Jauge）测量


* 原理：通过校准曲线，测量单点在单一方向上的变形。
* 局限：只能测量一个方向的应变，需多个应变计组合才能获得完整的应变张量。


### 图像相关法（2D）


* 原理：利用表面上的随机斑点（白斑、黑斑等）追踪变形前后的图像，计算位移场。
* 应用：通过寻找变形图像与初始图像之间的位移场，反推变形情况。
* 类似于网格法，但更灵活，能捕捉不同尺度的变形。


### X射线衍射法


* 适用材料：主要用于金属材料。
* 原理：利用布拉格条件测量原子平面间距变化，推断微观变形。
* 技术复杂，但能提供晶格层面的变形信息。


---


## 网格法变形分析


* 网格变形通过分析网格单元的角度和长度变化，推导局部变形。
* 变形类型包括：
  + 平移：无长度变化，无旋转，整体移动。
  + 旋转：绕某中心点旋转，角度为​\alpha$\alpha$​。
  + 简单剪切（Glissement simple）：
    - 体积不变（不可压缩）。
    - 角度变化，纤维间角度发生改变。
    - 类似“推移一叠扑克牌”的滑动。
  + 纯剪切（Glissement pur）：
    - 无整体旋转。
    - 一方向收缩，另一方向拉伸。
    - 纤维轻微旋转。
  + 各向同性膨胀：所有方向均匀膨胀。
  + 各向异性膨胀：不同方向膨胀率不同。


---


## 变形类型对比表


| 变形类型 | 体积变化 | 旋转 | 角度变化 | 纤维方向变化 | 说明 |
| --- | --- | --- | --- | --- | --- |
| 平移 | 无 | 无 | 无 | 无 | 整体平移，无变形 |
| 旋转 | 无 | 有 | 无 | 无 | 绕中心点旋转 |
| 简单剪切 | 无 | 有 | 有 | 有 | 角度变化，类似扑克牌滑动 |
| 纯剪切 | 无 | 无 | 有 | 有 | 一方向拉伸，另一方向收缩 |
| 各向同性膨胀 | 有 | 无 | 无 | 无 | 各方向均匀膨胀 |
| 各向异性膨胀 | 有 | 无 | 无 | 无 | 不同方向膨胀率不同 |


---


## 术语解释与物理意义


### Glissement（滑移）


* 法语术语，英文对应为“simple shear”或“pure shear”。
* 也可称为“distorsion”（畸变）。
* 在塑性变形中，指晶体平面间的相对滑动。
* 物理机制：
  + 原子层沿晶面滑动，产生位错（dislocations）。
  + 体积保持不变，但形状发生改变。
* 典型应用：钢铁等合金的塑性变形。


---


## 变形的数学与物理描述


* 简单剪切：角度变化，存在旋转分量。
* 纯剪切：无旋转，形变为拉伸与压缩的组合。
* 变形可以通过组合多个简单剪切实现纯剪切。
* 弹性变形中，加载路径对最终状态影响较小；非线性变形中则不同。


---


> 注意：变形测量方法各有优缺点，选择时需结合材料类型、变形尺度及实验条件。


---


# 变形示意图与实例（建议课件中查看）


* 网格变形示意：通过网格单元的角度和边长变化直观理解变形类型。
* 实际应用示例：
  + 工程结构中应变计布置测量局部应变。
  + 材料科学中利用X射线衍射分析微观晶格变形。
  + 图像相关法用于复杂表面变形的全场测量。


---


# 相关公式（简要）


* 应变张量（二维）：


```
\varepsilon = \begin{bmatrix}
\varepsilon_{xx} & \varepsilon_{xy} \\
\varepsilon_{yx} & \varepsilon_{yy}
\end{bmatrix}
```


```


$$
\varepsilon = \begin{bmatrix}
\varepsilon_{xx} & \varepsilon_{xy} \\
\varepsilon_{yx} & \varepsilon_{yy}
\end{bmatrix}
$$


```


* 简单剪切应变：


```
\gamma = \tan \theta \approx \theta
```


```


$$
\gamma = \tan \theta \approx \theta
$$


```


其中，​\theta$\theta$​为角度变化。


* 体积变化：


```
\Delta V = V_{final} - V_{initial}
```


```


$$
\Delta V = V_{final} - V_{initial}
$$


```


> 简单剪切和纯剪切均为体积不变变形。


---


# 术语对照表


| 法语术语 | 英文术语 | 中文解释 |
| --- | --- | --- |
| Glissement | Simple shear / Pure shear | 滑移 / 剪切变形 |
| Distorsion | Distortion | 畸变 |
| Jauge | Strain gauge | 应变计 |
| Corrélation d'image | Image correlation | 图像相关法 |


---


# 实际应用联系


* 材料力学：理解滑移机制有助于解释金属塑性变形和疲劳。
* 结构监测：应变计和图像相关法用于桥梁、建筑等结构健康监测。
* 微观分析：X射线衍射揭示晶格层面变形，指导材料设计。


---


# 重要提醒


> 变形测量需结合多种方法，单一技术难以全面描述复杂变形状态。
> 理解不同变形类型的物理意义，有助于深入掌握材料力学和结构力学基础。
```