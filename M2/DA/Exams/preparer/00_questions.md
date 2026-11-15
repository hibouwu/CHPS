# 自测题（74 题，只有题目）

## 1. 泛化、误差分解与偏差—方差

### 1.1 What is the bias–variance trade-off? 偏差—方差权衡是什么？ ★★★★

### 1.2 What are the approximation and estimation errors, and how is the trade-off between them solved? 近似误差和估计误差是什么？二者的权衡如何处理？ ★★

### 1.3 What is the generalization error and how is it related to overfitting? 什么是泛化误差？它和过拟合有什么关系？ ★

### 1.4 What is the role of penalization in machine learning? 惩罚项（正则化）在机器学习中起什么作用？ ★

### 1.5 Are generalization error and overfitting relevant for clustering? 泛化误差和过拟合的概念适用于聚类吗？ ★

### 1.6 What is the impact of computation time (fixed resources) when the sample size grows? 计算资源固定时，样本量增大对计算时间有什么影响？ ★

## 2. 三大算法家族与 SVM

### 2.1 What is the principle of local methods? Give an example and its hyperparameters. 局部方法的原理是什么？举一个例子并说明超参数。 ★★★

### 2.2 What is the principle of global methods? Give an example. 全局方法的原理是什么？举一个例子。 ★★★

### 2.3 What are the two main ingredients of ensemble methods? Give an example. 集成方法的两个主要要素是什么？举一个例子。 ★★★

### 2.4 What are the two key principles of SVM? SVM 的两个核心原理是什么？ ★★

### 2.5 Why are convex losses sometimes used in learning? 为什么学习中有时使用凸损失？ ★

### 2.6 What other choices of loss lead to practical methods? 还有哪些损失选择能得到实用的方法？ ★

### 2.7 Can SVM be used for regression? SVM 能用于回归吗？ ★

## 3. 模型评估与超参数校准

### 3.1 Give an example of a hyperparameter and explain how to calibrate it. 举一个超参数的例子并说明如何校准。 ★★★

### 3.2 What are the stakes and difficulties of hyperparameter calibration? 超参数校准的意义和难点是什么？ ★★

### 3.5 Define the ROC curve. 给出 ROC 曲线的定义。 ★★

### 3.6 What is the interest of the ROC curve and the AUC? ROC 曲线和 AUC 有什么用？ ★★

### 3.3 Can hyperparameter calibration be solved by an optimization technique? 超参数校准能用优化方法解决吗？ ★

### 3.4 Which parameters are chosen by the data scientist and which are learned by the algorithm? 哪些参数由数据科学家选择，哪些由算法学得？ ★

### 3.7 Which evaluation criteria can be used for classification data? 分类数据可以用哪些评价准则？ ★

### 3.8 How do you measure classification performance with a train–test split (N = 700 + 300)? 如何用训练／测试划分评估分类性能（700＋300）？ ★

### 3.9 How do you measure classification performance with k-fold cross-validation? 如何用 k 折交叉验证评估分类性能？ ★

## 4. 决策树

### 4.1 What are the hyperparameters of decision trees? 决策树有哪些超参数？ ★★★★

### 4.2 What is a decision tree (representation), e.g. for binary classification? 什么是决策树（表示方式），例如在二分类中？ ★★

### 4.3 How is a decision tree built / trained (pseudocode)? 决策树如何构建／训练（伪代码）？ ★★

### 4.4 What label does a decision tree assign to a new point x? 决策树给新点 x 赋什么标签？ ★★

### 4.5 What are the advantages of decision trees over most other algorithms? 与大多数其他算法相比，决策树有哪些优点？ ★★

### 4.6 A tree was trained for f. Can it be reused for f₁(5x)=f(x), f₂(x)=5f(x), f₃(x)=f(x)⁵, without retraining? 为 f 训练好的树，能否不重新训练就用于这些变换后的函数？ ★★

### 4.7 What are the drawbacks of decision trees? 决策树有哪些缺点？ ★

### 4.8 Is it possible to solve the drawbacks of decision trees? 能否克服决策树的缺点？ ★

### 4.9 Give at least two stopping rules for training a decision tree. 至少给出两条决策树训练的停止规则。 ★

### 4.10 Is it possible to monitor the number of cells of the tree using the training data? 能否用训练数据控制树的单元（叶）数量？ ★

### 4.11 Give a 2D example where the classes are separable but a tree is not efficient. 给出一个二维例子：类别可分，但决策树效率不高。 ★

## 5. 线性模型、OLS 与逻辑回归

### 5.1 Describe the logistic regression model. 描述逻辑回归模型。 ★★★

### 5.2 What decisions / uses does logistic regression allow (classification, scoring, other problems)? 逻辑回归能支持哪些决策／用途？ ★★★

### 5.3 Explain how Ordinary Least Squares (OLS) fits a line / a linear model. 说明 OLS 如何拟合直线／线性模型。 ★★★

### 5.4 How do you use logistic regression for a classification problem? 如何把逻辑回归用于分类问题？ ★★

### 5.5 Explain the principle of Ridge regression. 解释岭回归的原理。 ★

### 5.6 How do you estimate a sparse linear model? 如何估计稀疏线性模型？ ★

### 5.7 With N = 50 data points and d = 200 features, which regression method would you prefer? How could you still use OLS? N=50、d=200 时选哪种回归方法？如果必须用 OLS 怎么办？ ★

### 5.8 Which polynomial models would you try on 4 data points, and what is the most complex meaningful one? 4 个数据点上可以尝试哪些多项式模型？最复杂且有意义的是哪个？ ★

## 6. 深度学习与数值优化

### 6.1 What optimization strategy is used to train / calibrate deep learning architectures? 深度学习采用什么优化策略？ ★★

### 6.2 How is numerical optimization achieved in machine learning methods? Give an example. 机器学习方法如何做数值优化？举一个例子。 ★

### 6.3 What is the mathematical space of functions of deep feedforward neural networks? 深度前馈神经网络对应怎样的函数空间？ ★

### 6.4 What are the hyperparameters of deep neural networks? 深度神经网络有哪些超参数？ ★

### 6.5 What is the fundamental difference between deep and shallow learning? 深度学习与浅层学习的根本区别是什么？ ★

## 7. 聚类（k-means、软 k-means、层次聚类）

### 7.1 Give the k-means objective function and the pseudocode of the algorithm. 给出 k-means 的目标函数和算法伪代码。 ★★★★

### 7.2 Why does the k-means procedure converge? k-means 为什么会收敛？ ★★★

### 7.3 Why are multiple (re)runs suggested? How can k-means approximate the globally optimal solution? 为什么建议多次运行？如何用 k-means 逼近全局最优？ ★★★

### 7.4 How do you validate the choice of the number of clusters? 如何验证聚类数目的选择？ ★★

### 7.5 Propose a soft k-means with probabilistic assignments: definition, pseudocode, convergence. 设计一种概率分配的软 k-means：定义、伪代码、是否收敛。 ★★

### 7.6 If k-means is initialized with the soft k-means solution, will the clusters change? Is it a local minimum of hard k-means? 用软 k-means 的解初始化 k-means，簇会变吗？它是硬 k-means 的局部极小吗？ ★★

### 7.7 Compare hard and soft k-means. When is soft k-means preferable? 比较硬 k-means 和软 k-means。什么时候软 k-means 更合适？ ★★

### 7.8 Summarize the dataset by two "typical" examples (the centers): how well does each center represent its cluster? 用两个"典型"样本（中心）概括数据：每个中心代表其簇的效果如何？ ★★

### 7.9 During k-means, how can a cluster become empty? Give heuristics to continue without reducing k. k-means 中簇为什么会变空？给出不减少 k 的处理办法。 ★

### 7.10 What if the initial clusters are formed by assigning each point uniformly at random? Will it converge, faster or slower? 如果初始化时把每个点等概率随机分到某个簇，会收敛吗？更快还是更慢？ ★

### 7.11 Give three linkage criteria for hierarchical agglomerative clustering, with formulas. 给出层次凝聚聚类的三种连接准则及公式。 ★

### 7.12 Use bootstrapped k-means solutions to compute an outlier score; compare with Isolation Forest. 用多次 bootstrap 的 k-means 解计算离群分数，并与 Isolation Forest 比较。 ★

## 8. 稳健估计（RANSAC）与概率图模型

### 8.1 Describe the standard RANSAC method and algorithm for linear regression. 详细描述用于线性回归的标准 RANSAC 方法和算法。 ★★★

### 8.7 Give the graphical model of the battery–sensor–alarm system and write the joint distribution. 给出电池—传感器—报警系统的概率图模型并写出联合分布。 ★★

### 8.8 Are a and b independent? (conditional vs marginal independence) a 和 b 独立吗？（条件独立与边际独立） ★★

### 8.9 How do you compute P(battery fails | no alarm) from the model? 如何用模型计算"没听到报警时电池失效"的概率？ ★★

### 8.2 How sensitive is RANSAC to its parameters? RANSAC 对参数的敏感性如何？ ★

### 8.3 What is the difference between RANSAC and a typical bootstrap estimation procedure? RANSAC 与典型的 bootstrap 估计有什么区别？ ★

### 8.4 How can the internal RANSAC models "grade" datapoints as outliers, and the datapoints "grade" each model? RANSAC 内部的模型如何给数据点"打分"（是否离群），数据点又如何给模型打分？ ★

### 8.5 Develop a generalized RANSAC to fit a circle C(c, r). 用广义 RANSAC 拟合圆 C(c, r)。 ★

### 8.6 Robustly estimate δ = ‖μ − m‖ (mean vs medoid) with RANSAC when each instance has a quality indicator qᵢ. 每个样本带质量指标 qᵢ 时，用 RANSAC 稳健估计 δ = ‖μ − m‖（均值与 medoid 之差）。 ★

## 9. 学习问题的基本概念与实际应用

### 9.1 What are the links between machine learning and numerical simulation / HPC? Give two examples. 机器学习与数值模拟（高性能计算）有哪些联系？举两个例子。 ★★★

### 9.2 What is the difference between classification data and a classification problem? 分类数据与分类问题有什么区别？ ★★

### 9.3 What is the difference between supervised and unsupervised learning? Give two examples of each. 监督学习与无监督学习有什么区别？各举两个例子。 ★

### 9.4 What is the difference between classification data and regression data? 分类型数据与回归型数据有什么区别？ ★

### 9.5 Give two concrete implementation issues in real applications (supervised anomaly detection on an instrumented production line). 实际应用中的两个具体实施问题（以生产线上的监督式异常检测为例）。 ★

### 9.6 Describe a data science pipeline to deploy a predictive model (e.g. energy consumption peaks). 描述部署预测模型的数据科学流程（如能耗峰值预测）。 ★

### 9.7 Which points need attention because of the time dimension in the data? 由于数据带有时间维度，需要注意哪些问题？ ★
