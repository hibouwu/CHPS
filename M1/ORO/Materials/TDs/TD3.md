# TD3

## Exercice 1 练习 1

Une entreprise fabrique deux produits $P_1$ et $P_2$. La fabrication de ces produits nécessite du temps de travail (main d'oeuvre), du temps-machine et de la matière première. Les coefficients techniques de production ainsi que les prix de vente par unité de produit sont fournis dans le tableau suivant : 一家企业生产两种产品 $P_1$ 和 $P_2$。生产这些产品需要劳动时间、机器时间和原材料。生产技术系数以及每单位产品的销售价格如下表所示：

|  | $P_1$ | $P_2$ |
| --- | --- | --- |
| Quantité de "travail" (exprimés en heures) nécessaire à la fabrication d'une unité 制造 1 单位产品所需劳动时间 | 0.75 h | 0.5 h |
| Quantité de "temps-machine" (en h.) nécessaire à la fabrication d'une unité 制造 1 单位产品所需机器时间 | 1.5 h | 0.8 h |
| Quantité de matière première (exprimée en nombre d'unité $u$) nécessaire à la fabrication d'une unité de produit 制造 1 单位产品所需原材料数量 | 2u | 1u |
| Prix de vente par unité (exprimé en unités monétaires : u.m) 每单位销售价格 | 15 u.m | 8 u.m |

Chaque semaine $400$ unités de matière première au plus peuvent être achetées à un prix de $1{,}5$ u.m par unité. 每周最多可以买入 $400$ 单位原材料，每单位价格为 $1.5$ 货币单位。

L'entreprise emploie $4$ personnes qui travaillent chacune $40$ heures par semaine. La nature de leur travail est la main d'oeuvre. Ces personnes peuvent effectuer des heures supplémentaires qui sont payées à $6$ u.m. l'unité. 企业雇佣了 $4$ 名工人，每人每周工作 $40$ 小时。他们的工作属于人工劳动。工人可以加班，加班按每单位 $6$ 货币单位支付。

Chaque semaine, la disponibilité en temps machine est de $320$ h. 每周可用机器时间为 $320$ 小时。

En absence de publicité, la demande hebdomadaire du produit $P_1$ serait de $50$ unités, celle de $P_2$ de $60$ unités ; mais on peut réaliser de la publicité pour développer les ventes, chaque unité monétaire dépensée en publicité sur $P_1$ (respectivement sur $P_2$) augmente la demande hebdomadaire de $P_1$ (resp. $P_2$) de $10$ unités (resp. de $15$ unités). Les frais de publicité ne doivent pas dépasser $100$ u.m par semaine. 如果不做广告，产品 $P_1$ 的周需求量为 $50$ 单位，$P_2$ 的周需求量为 $60$ 单位；但企业可以通过广告促进销售，在 $P_1$（分别在 $P_2$）上的每花费 1 个货币单位的广告费，会使 $P_1$（分别 $P_2$）的周需求增加 $10$ 单位（分别 $15$ 单位）。广告费每周不得超过 $100$ 货币单位。

Les quantités de $P_1$ et $P_2$ fabriquées doivent rester inférieures ou égales à la demande réelle (compte tenu de la publicité). $P_1$ 和 $P_2$ 的产量必须小于或等于实际需求量（考虑广告影响后）。

On définit les $6$ variables suivantes : 定义以下 $6$ 个变量：

- $x_1$ : nombre d'unités du produit 1 fabriquées par semaine 每周生产的产品 1 数量
- $x_2$ : nombre d'unités du produit 2 fabriquées par semaine 每周生产的产品 2 数量
- $HS$ : nombre total d'heures supplémentaires effectuées par semaine 每周总加班时数
- $MP$ : nombre d'unités de matière première achetées par semaine 每周购买的原材料单位数
- $PUB1$ : nombre d'unités monétaires dépensées en publicité sur $P_1$ 在 $P_1$ 上投入的广告费
- $PUB2$ : nombre d'unités monétaires dépensées en publicité sur $P_2$ 在 $P_2$ 上投入的广告费

L'entreprise désire fixer la valeur de chacun de ces variables de manière à maximiser son bénéfice : 企业希望确定这些变量的取值，使利润最大化：

$$
\text{Bénéfice}=\text{Chiffre de vente}-\text{Somme des coûts variables}
$$

Le salaire (coût des heures normales) des quatre personnes est un coût fixe pour l'entreprise. 四名员工的正常工资（正常工时成本）属于企业的固定成本。

Question : modéliser le problème à l'aide des six variables qui sont proposées, sous forme de programme linéaire. La résolution n'est pas demandée. 问题：使用上述六个变量，把这个问题建模为一个线性规划。不要求求解。

## Exercice 2 练习 2

Un fabricant désire produire $100$ kg d'une préparation de base pour crème glacée. Cette préparation doit contenir $21{,}5$ kg de matière grasse, $21$ kg de sucre, $1{,}2$ kg d'oeuf et $56{,}3$ kg d'eau. Les ingrédients dont il dispose figurent en tête des colonnes du tableau ci-dessous ; les constituants figurent en ligne. Ce tableau précise également les pourcentages (en poids) de chaque constituant dans chaque ingrédient ainsi que le coût, au kg, de chaque ingrédient. 一家生产商希望生产 $100$ kg 冰淇淋基料。该配方必须包含 $21.5$ kg 脂肪、$21$ kg 糖、$1.2$ kg 鸡蛋和 $56.3$ kg 水。可用原料列在下表的列标题中，各组成成分列在行中。表中还给出了各成分在每种原料中的质量百分比以及每公斤原料的成本。

| Constituants 成分 | Crème 奶油 | Jaune d'oeuf 蛋黄 | Lait entier en poudre 全脂奶粉 | Jaune d'oeuf surgelé et sucré 冷冻加糖蛋黄 | Sirop de sucre de canne 甘蔗糖浆 | Eau 水 |
| --- | --- | --- | --- | --- | --- | --- |
| Matière grasse 脂肪 | 40 | 50 | 12 | 30 |  |  |
| Sucre 糖 |  |  |  | 14 | 70 |  |
| Oeuf 鸡蛋 |  | 40 |  | 40 |  |  |
| Eau 水 | 60 | 10 | 88 | 16 | 30 | 100 |
| Coût au kg (en u.m.) 每公斤成本 | 3 | 4 | 1 | 2 | 0,80 | 0,00 |

Le fabricant désire déterminer la composition du mélange de coût minimal. Ecrire le programme linéaire correspondant à ce problème. 生产商希望确定成本最小的混合配方。请写出对应的线性规划模型。

## Exercice 3 练习 3

Une raffinerie peut traiter trois pétroles bruts n°1, n°2 et n°3. 一座炼油厂可以处理 1 号、2 号和 3 号三种原油。

Par distillation fractionnée dans les "toppings" ces bruts donnent des coupes qui sont des ensembles d'hydrocarbures ayant des températures d'ébullition comprises entre les limites fixées. 这些原油经过常压蒸馏后，会得到若干馏分，它们是沸点落在给定范围内的烃类混合物。

On obtient par exemple : 例如可以得到：

- des gaz 气体
- une gazoline $0$-$80^\circ$C 汽油馏分 $0$-$80^\circ$C
- une benzine $80$-$130^\circ$C 轻汽油 $80$-$130^\circ$C
- un naphta léger $130$-$160^\circ$C 轻石脑油 $130$-$160^\circ$C
- un naphta lourd $160$-$190^\circ$C 重石脑油 $160$-$190^\circ$C
- un kérosène $190$-$230^\circ$C 煤油 $190$-$230^\circ$C
- un gasoil léger $230$-$310^\circ$C 轻柴油 $230$-$310^\circ$C
- un gasoil lourd $310$-$400^\circ$C 重柴油 $310$-$400^\circ$C
- un fuel-oil $>400^\circ$C 燃料油 $>400^\circ$C

Ces coupes subissent ensuite des traitements complémentaires (épuration, désulfuration, cracking, reforming catalytique) pour devenir des bases qui, convenablement mélangées, permettront d'obtenir les produits commerciaux désirés. 这些馏分随后还要经过进一步处理（净化、脱硫、裂化、催化重整），变成可以混配成商业产品的基础油品。

C'est ainsi que la raffinerie considérée fabrique cinq catégories de produits finis : 因此，这家炼油厂生产五类最终产品：

- des gaz et des gaz liquéfiés 气体和液化气
- des essences 汽油
- du pétrole 煤油/石油产品
- du gasoil 柴油
- du fuel-oil 燃料油

Les rendements de pétroles bruts traités sont précisés dans le tableau ci-après (qui explicite les quantités produites à partir d'une tonne de brut) : 下表给出了原油处理后的产率（即每处理 1 吨原油可得到的产品数量）：

| Production en t. 产量（吨） | Brut n°1 Afrique 1 号非洲原油 | Brut n°2 Moyen-Orient 2 号中东原油 | Brut n°3 Amérique 3 号美洲原油 |
| --- | --- | --- | --- |
| Gaz et gaz liquéfiés 气体和液化气 | 0,02 | - | 0,06 |
| Essences 汽油 | 0,20 | 0,25 | 0,30 |
| Pétrole 煤油/石油产品 | 0,08 | - | 0,04 |
| Gasoil 柴油 | 0,40 | 0,25 | 0,30 |
| Fuel-oil 燃料油 | 0,30 | 0,50 | 0,30 |
| Total 合计 | 1 | 1 | 1 |

La raffinerie peut produire au maximum, au cours d'une année : 炼油厂一年内最多可以生产：

- `300 000` t. de gaz et gaz liquéfiés `300000` 吨气体和液化气
- `1 050 000` t. d'essences `1050000` 吨汽油
- `180 000` t. de pétrole `180000` 吨煤油/石油产品
- `1 350 000` t. de gasoil `1350000` 吨柴油
- `1 800 000` t. de fuel-oil `1800000` 吨燃料油

Sa production est limitée par la capacité de certaines unités de traitement, par les possibilités de ventes et par les stockages disponibles. 产量受到部分处理装置能力、销售能力以及库存容量的限制。

La raffinerie réalise un bénéfice de `4` unités monétaires par tonne de brut n°1, de `5` unités monétaires par tonne de brut n°2 et de `5` unités monétaires par tonne de brut n°3. 炼油厂处理每吨 1 号原油可获得 `4` 个货币单位利润，处理每吨 2 号和 3 号原油各可获得 `5` 个货币单位利润。

Formuler ce problème par un programme linéaire. 请把这个问题表述成一个线性规划。

## Exercice 4 练习 4

On désire déterminer la composition, à coût minimal, d'un aliment pour bétail qui est obtenu en mélangeant au plus trois produits bruts : 我们希望确定一种牲畜饲料的最低成本配方，该饲料由至多三种原料混合得到：

- orge 大麦
- arachide 花生
- sésame 芝麻

L'aliment ainsi conditionné devra comporter (pour se conformer aux exigences de la clientèle) au moins : 该饲料为了满足客户要求，至少应包含：

- `22%` de protéines `22%` 的蛋白质
- `3.6%` de graisses `3.6%` 的脂肪

On a indiqué ci-dessous les pourcentages de protéines et de graisses contenues, respectivement, dans l'orge, les arachides et le sésame, ainsi que le coût par tonne de chacun des produits bruts : 下表给出了大麦、花生和芝麻中的蛋白质与脂肪含量，以及每吨原料的成本：

| produit brut 原料 | orge 大麦 | arachides 花生 | sésame 芝麻 | pourcentage requis 要求比例 |
| --- | --- | --- | --- | --- |
| pourcentages de protéines 蛋白质比例 | 12% | 52% | 42% | 22% |
| pourcentages de graisses 脂肪比例 | 2% | 2% | 10% | 3.6% |
| coût par tonne 每吨成本 | 25 | 41 | 39 |  |

Questions : 问题：

1. On notera $x_j=(j=1,2,3)$ la fraction de tonne de produit brut $j$ contenu dans une tonne d'aliment. Formuler le problème algébriquement. 记 $x_j=(j=1,2,3)$ 为 1 吨饲料中第 $j$ 种原料所占的吨数比例。请把该问题写成代数形式。
2. Montrer qu'il est possible de réduire la dimension du problème. 说明这个问题可以降维。

## Exercice 5 练习 5

Un atelier peut fabriquer trois types d'articles : 一个车间可以生产三种产品：

- l'article $A_1$ à la cadence de $35$ objets à l'heure 产品 $A_1$ 的生产节拍为每小时 $35$ 件
- l'article $A_2$ à la cadence de $45$ objets à l'heure 产品 $A_2$ 的生产节拍为每小时 $45$ 件
- l'article $A_3$ à la cadence de $20$ objets à l'heure 产品 $A_3$ 的生产节拍为每小时 $20$ 件

Cette fabrication utilise une machine-outil unique, disponible $200$ heures par mois. 生产只使用一台机床，每月可用时间为 $200$ 小时。

Le bénéfice unitaire pour l'article $A_1$ est de $60$ euros par objet, pour $A_2$ de $40$ euros, pour $A_3$ de $80$ euros. 单位利润分别为：产品 $A_1$ 每件 $60$ 欧元，$A_2$ 每件 $40$ 欧元，$A_3$ 每件 $80$ 欧元。

Ces objets sont vendus en totalité à des grossistes ; on a observé qu'on ne pouvait écouler, par mois, plus de $4900$ objets du type $A_1$, ni plus de $5400$ objets du type $A_2$, ni plus de $2000$ objets du type $A_3$. 这些产品全部卖给批发商；经观察，每月最多只能销售 $4900$ 件 $A_1$、$5400$ 件 $A_2$ 和 $2000$ 件 $A_3$。

D'autre part, chaque objet doit être vérifié avant sa commercialisation ; une équipe de trois techniciens est chargée de cette mission ; chaque technicien travaille $170$ heures par mois. La vérification d'un objet du type $A_1$ prend quatre minutes, du type $A_2$, trois minutes, du type $A_3$, deux minutes. 此外，每件产品在销售前都必须检验；这项工作由 3 名技术员承担，每人每月工作 $170$ 小时。检验一件 $A_1$ 需要 4 分钟，一件 $A_2$ 需要 3 分钟，一件 $A_3$ 需要 2 分钟。

Question 1 : Montrer qu'une contrainte est redondante (c'est-à-dire qu'elle est impliquée par une ou plusieurs autres). Interpréter géométriquement cette redondance. 问题 1：证明其中一个约束是冗余的（也就是说它由一个或多个其他约束推出）。并从几何角度解释这种冗余。

Question 2 : Classer alors les produits par bénéfice horaire décroissants et faire une résolution économique de ce problème. 问题 2：按单位工时利润从高到低对产品排序，并对该问题作经济意义下的求解。
