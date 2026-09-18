# Data & Apprentissage

Novembre 2024 

Examen final 

Le sujet est imprim´e sur 3 pages – Dur´ee 2 heures 

Les documents et notes de cours ne sont pas autoris´es. L’utilisation de smartphones et acc`es `a des ressources documentaires sur internet est interdit. L’examen est `a r´ealiser individuellement et toute tentative de collaboration entre ´etudiants sera s´ev´erement sanctionn´ee. 

> **分值核对：** 原 PDF 五道大题标分依次为 4、5、4、3、3，合计 19 分。本转换稿照录原分值，不推定其应为 20 分或自行补分。

## Exercice 1. General course understanding

[4 points] 

Please provide concise replies to each question. 

1. Quote one example ofalgorithm in each ofthe three main categories ofmachine learning methods (local, global, ensemble). 

2. Explain what is the trade-of between estimation error and approximation error in machine learning and how can this be solved ? 

3. What is the optimization strategy in deep learning ? 

4. Give an example of hyperparameter in a specific machine learning method and explain how it can be calibrated. 

## Exercice 2. Course understanding - Decision trees

[5 points] 

1. What is a decision tree in the context of binary classification ? 

2. Consider a new point x, what is the label y assigned by the decision tree ? 

3. Consider a set of supervised classification data. Provide the pseudocode in order to train a decision tree classifier. 

4. Give at least two stopping rules of the training procedure of decision trees. 

5. Give at least two hyperparameters of decision trees. 

6. Is it possible to monitor the number of cells of the tree using the training data ? 

7. What are the pros and cons of decision trees ? 

8. Is it possible to solve the drawbacks of decision trees ? 

## Exercice 3. Graphical models

> **审查注（2026-09-15，非原题）：** 题干没有给出传感器失效时报警保持静默的概率。即使按 $b\to c\to a$ 的链式结构并采用 $a\perp b\mid c$，仍需设 $q=P(a=0\mid c=0)$，不能自行假定它是 0、1 或 0.99。题中已知量给出 $P(c=0)=0.039$，因此 $P(a=0)=0.95139+0.039q$，且 $P(b=0\mid a=0)=(0.0693+0.03q)/(0.95139+0.039q)$。条件概率表中 $c=0$ 的一列及后两问应保留 $q$，或等待补充题面；边际独立性也不能仅由图上存在一条路径就断言。原题正文在下方保留。

[4 points] 

A security system relies on a battery, a sensor, and an alarm. Consider the three respective binary random variables a, b, c. When the alarm fires : a = 1 ; when the battery functions properly : b = 1 ; and when the sensor functions properly : c = 1. Otherwise, those variables take a value equal to 0. The system architecture is very simple : the battery powers the sensor, and the sensor feeds information to the controler of the alarm that decides to fire to signify a threat. The system manual informs us that : 

• the probability for the battery to fail is 0.1 

• the probability for the sensor to fail is 0.01 when the battery is ok, and 0.3 when the battery is not ok. 

• the probability for the alarm to be silent is 0.99, when the sensor works fine. 

a) Give the graphical model that involves the variables of this problem, and translate all the known information given by the manual to proper writing with probabilities (it does not involve calculations). 

b) Give the $2 \times 2$ table of the probability $p ( a = 1 | b , c )$ . Examine if a and b are independent. 

c) Compute the probability for the alarm to be silent. 

d) Suppose we don’t hear any alarm and we have no information about whether the sensor functions correctly. What is the probability of the battery to be disfunctioning? 

## Exercice 4. Regression and robust estimation

[3 points] 

a) Considering the data of Table 1, apply the OLS by making the numerical calculations and report the fitted model and its Root Mean Squared Error (RMSE). 

<table><tr><td>i</td><td>1</td><td>2</td><td>3</td><td>4</td></tr><tr><td>xi</td><td>2.2</td><td>0.9</td><td>0.4</td><td>-0.6</td></tr><tr><td>yi</td><td>1.2</td><td>2</td><td>1</td><td>-1</td></tr></table>


Table 1 – Practical example : data points $P = \{ ( x _ { i } , y _ { i } ) , i = 1 . . . 4 \}$


b) In a given dataset P, the datapoints are assumed to be distributed in a circular shape (e.g. see the figure below). We are interested to learn a circular model $C ( c , r )$ that best fits the data. Recall that the standard equation of a 2D circle centered at $c = ( x _ { c } , y _ { c } )$ and of radius r is : $( x - x _ { c } ) ^ { 2 } + ( y - y _ { c } ) ^ { 2 } = r ^ { 2 }$ . Develop in detail how this problem could be solved with the generalized RANSAC approach. 

![image](<Images/DataML-CHPS-2024-examen/image_001.jpg>)


## Exercice 5. Clustering

> **解题边界提示（非原题）：** 标准 k-means 的交替步骤使目标值不增，多次随机重启有助于寻找更好的解，但不保证有限次重启找到全局最优。软 k-means 的题目要求自行提出概率分配方案；讨论收敛时，应同时说明该方案对应的目标及更新规则。

[3 points] 

a) Give the k-means objective function, the pseudocode of the clustering algorithm, explain with simple arguments : why the procedure converges, and how it can be used to approximate the globally optimal solution containing the best possible centroids. 

b) We are interested about a soft k-means that would use a probabilistic datapoint-tocluster assignment (similar to Gaussian Mixture Modeling). Propose a way to define this probabilistic assignment, give an updated pseudocode for this case, and argue whether or not this would converge. 

c) If we initialize k-means with the solution of soft k-means, would the clusters change or not, and why ? Give elements of comparison for the two aforementioned hard and soft k-means approaches ? Which are the cases where the latter is better to be used ? 

d) Describe a procedure that would use a bootstrap approach, i.e. multiple randomized kmeans solutions, to compute an outlier score for each datapoint. Discuss its properties in perspective with Isolation Forest. 