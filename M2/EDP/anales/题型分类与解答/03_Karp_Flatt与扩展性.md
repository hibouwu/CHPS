# Karp Flatt et passage à l'échelle Karp Flatt 与扩展性

## Index des exercices croisés 交叉题索引

Les exercices ci-dessous restent entiers dans leur catégorie principale ; seules les questions associées sont indexées ici. 下列大题完整收录于各自主类别，本处只列相关小问的索引，不重复题干或答案。

- **TD1 §1.2** — questions associées 关联小问：Calcul de la fraction effective et commentaire 串行比例计算与并行行为解释（原题未分编号）。

  Corrigé complet 完整题解：[《01_加速比与向量化》](pdf/01_加速比与向量化.pdf)；pages du fascicule 分册第 **2–3** 页；pages du recueil 合订本第 **3–4** 页。

Partir des temps mesurés pour séparer vitesse, efficacité et fraction séquentielle effective. 从实测时间出发，区分加速比、效率与有效串行比例。

Corrigés de travail vérifiés, distincts d'un corrigé officiel. Les hypothèses utiles sont précisées avec chaque solution. 本资料为经计算核对的学习题解，不是教师标准答案。各题解答中写明所用假设。

## Méthode commune 通用方法


$$
S=T_1/T_P,\quad E=S/P,\quad e=\frac{1/S-1/P}{1-1/P}=\frac{PT_P/T_1-1}{P-1}.
$$

Calculer e seulement pour P>1. Il absorbe sérialisation et surcoûts observés. 只对 P>1 计算 e；它吸收串行化及观测到的并行开销。

## 1 Cray Y MP 8

Source : TD1 §4.1(a–c), PDF p.4 来源：TD1 §4.1(a–c), PDF p.4

### Énoncé 题目

Soit le tableau ci-dessous, regroupant les temps d'exécution mesurés pour un code P durant ses exécutions sur la machine Cray Y-MP/8 avec différents nombres de processeurs. 下表给出程序 P 在 Cray Y-MP/8 机器上使用不同数量的处理器运行时，测得的执行时间。

| Nombre de processeurs P 处理器数量 P | Temps d'exécution (s) 执行时间（s） |
| --- | --- |
| 1 | 2.170 |
| 2 | 1.110 |
| 3 | 0.754 |
| 4 | 0.577 |
| 8 | 0.312 |

**(a)** Calculez l'accélération, l'efficacité et le facteur e de Karp-Flatt pour chacun des quatre cas (P = 2, 3, 4 et 8) 对于 $P=2,3,4,8$ 这四种情况，分别计算加速比、并行效率和 Karp–Flatt 因子 $e$。 **(Catégorie associée : Accélération et vectorisation 关联类别：加速比与向量化)**

**(b)** Que pensez-vous des accélérations et efficacités obtenues ? Argumentez votre réponse. 你如何评价得到的加速比和并行效率？请说明理由。 **(Catégorie associée : Accélération et vectorisation 关联类别：加速比与向量化)**

**(c)** Qu'indiquent les valeurs du facteur e dans ce cas ? 在这个例子中，因子 $e$ 的数值说明了什么？

### Corrigé détaillé 逐步解答

| P | T (s) | S | E (%) | e |
|---|---|---|---|---|
| 2 | 1.11 | 1.954955 | 97.7477 | 0.023041 |
| 3 | 0.754 | 2.877984 | 95.9328 | 0.021198 |
| 4 | 0.577 | 3.760832 | 94.0208 | 0.021198 |
| 8 | 0.312 | 6.955128 | 86.9391 | 0.021461 |

Les accélérations augmentent, avec efficacité de 97.75 % à 86.94 %. Le facteur e reste proche de 2.1–2.3 % : les mesures sont compatibles avec une fraction effective presque constante. 加速比持续增大，效率从 97.75% 降至 86.94%；e 约为 2.1%–2.3%，与近似固定的有效串行比例相符。

Cela soutient un bon passage à l'échelle sur la plage mesurée, sans identifier à lui seul la cause des coûts. Une extrapolation idéale donnerait environ 1/0.0214 ≈ 46.7, à condition de conserver ce modèle. 这支持测量范围内扩展良好的判断，但单靠 e 不能定位开销来源。若模型继续成立，理想外推上界约为 $1/0.0214\approx46.7$。

## 2 Aliant FX 40

Source : TD1 §4.2(a–b), PDF p.4–5 来源：TD1 §4.2(a–b), PDF p.4–5

### Énoncé 题目

Soit le tableau ci-dessous, regroupant les temps d'exécution mesurés pour un code P durant ses exécutions sur la machine Aliant FX/40 avec différents nombres de processeurs. 下表给出程序 P 在 Aliant FX/40 机器上使用不同数量的处理器运行时，测得的执行时间。

| Nombre de processeurs P 处理器数量 P | Temps d'exécution (s) 执行时间（s） |
| --- | --- |
| 1 | 66.1 |
| 2 | 34.8 |
| 3 | 24.9 |
| 4 | 20.5 |

**(a)** Calculez l'accélération, l'efficacité et le facteur e de Karp-Flatt pour chacun des trois cas (P = 2, 3 et 4). 对于 $P=2,3,4$ 这三种情况，分别计算加速比、并行效率和 Karp–Flatt 因子 $e$。 **(Catégorie associée : Accélération et vectorisation 关联类别：加速比与向量化)**

**(b)** Interprétez la variation de l'efficacité puis faites de même pour le facteur e. 解释并行效率的变化，再解释因子 $e$ 的变化。 **(Catégorie associée : Accélération et vectorisation 关联类别：加速比与向量化)**

### Corrigé détaillé 逐步解答

| P | T (s) | S | E (%) | e |
|---|---|---|---|---|
| 2 | 34.8 | 1.899425 | 94.9713 | 0.052950 |
| 3 | 24.9 | 2.654618 | 88.4873 | 0.065053 |
| 4 | 20.5 | 3.224390 | 80.6098 | 0.080182 |

L'efficacité diminue de 94.97 % à 80.61 % tandis que e augmente de 5.295 % à 8.018 %. Les surcoûts effectifs deviennent plus importants avec P. 效率从 94.97% 降到 80.61%，e 从 5.295% 增至 8.018%，表明随 P 增大，有效额外成本的影响上升。

Le code peut être inchangé : e n'est pas une mesure directe de sa fraction intrinsèquement séquentielle. Communications, synchronisation et déséquilibre sont des causes à examiner. 代码本身可以未变；e 不是固有串行代码比例的直接测量。通信、同步和负载不均衡是需要进一步检查的原因。

