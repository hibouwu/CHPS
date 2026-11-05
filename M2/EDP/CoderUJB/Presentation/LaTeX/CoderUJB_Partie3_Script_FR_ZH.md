# Troisième partie — Résultats : contexte et modèles
# 第三部分——实验结果：上下文与模型

- **Présentateur / 演讲者：** Jianye SHI
- **Diapositives / 对应幻灯片：** 14–17
- **Utilisation / 使用方法：** Lire uniquement les paragraphes en français pendant la présentation. Les traductions chinoises servent à comprendre et à répéter. / 演讲时只读法语段落；中文用于理解和练习。

## Diapositive 14 — Le contexte du projet aide la génération
## 第 14 页——项目上下文有助于代码生成

**Français**

Ici, les auteurs comparent trois façons de présenter une question au modèle. On donne soit un exemple, soit quatre exemples, soit du contexte du projet, comme les signatures des méthodes et les champs de la classe.

**中文**

这里，作者比较了向模型提供题目的三种方式：给一个示例，给四个示例，或者给出项目的上下文，例如方法签名和类中的字段。

**Français**

Pour CodeLlama-13B, le score passe d’environ 13 % avec un exemple à 22 % avec le contexte du projet. Quatre exemples donnent environ 15 %.

**中文**

对于 CodeLlama-13B，给一个示例时，得分约为 13%；提供项目上下文后，得分提高到约 22%。给四个示例时，得分约为 15%。

**Français**

Sur cette tâche, les informations sur le projet aident donc davantage que les exemples.

**中文**

因此，在这项任务中，项目本身的信息比这些示例更有帮助。

## Diapositive 15 — Un écart plus marqué en réparation
## 第 15 页——修复任务中的差距更明显

**Français**

Dans ce tableau, FCG signifie générer une fonction, et APR signifie réparer une fonction. Les scores utilisent tous pass-all à un.

**中文**

在这张表中，FCG 指生成一个函数，APR 指修复一个函数。这些得分都使用 pass-all@1 指标。

**Français**

Pour générer une fonction, CodeLlama-34B et GPT-3.5 sont très proches, autour de 23 %. GPT-4 atteint environ 31 %.

**中文**

在函数生成任务中，CodeLlama-34B 和 GPT-3.5 的成绩很接近，都在 23% 左右。GPT-4 则达到约 31%。

**Français**

Pour réparer une fonction, CodeLlama obtient environ 5 %, GPT-3.5 environ 9 %, et GPT-4 environ 19 %. Les écarts sont donc plus grands en réparation.

**中文**

在函数修复任务中，CodeLlama 的得分约为 5%，GPT-3.5 约为 9%，GPT-4 约为 19%。因此，模型之间的差距在修复任务中更大。

**Français**

Ce sont les versions évaluées dans l’article de 2024.

**中文**

这里比较的是这篇 2024 年论文所评测的模型版本。

## Diapositive 16 — GPT-4 : des scores différents selon la tâche
## 第 16 页——GPT-4 在不同任务上的得分不同

**Français**

Regardons maintenant les quatre tâches pour GPT-4. Le score est d’environ 31 % pour compléter une fonction, et de 24 % pour écrire un test à partir du code.

**中文**

现在来看 GPT-4 在四种任务上的表现。补全函数的得分约为 31%，根据代码编写测试的得分约为 24%。

**Français**

Pour écrire un test qui reproduit un bug décrit dans un rapport, il est de 6,66 %. Pour réparer une fonction, il atteint environ 19 %.

**中文**

根据缺陷报告编写一个能够复现该缺陷的测试，得分为 6.66%；修复函数的得分则约为 19%。

**Français**

Les critères de réussite changent selon la tâche. Ces résultats montrent surtout pourquoi il faut évaluer plusieurs activités de programmation.

**中文**

不同任务的成功标准并不一样。这些结果主要说明，评估模型时，需要考察多种编程活动。

## Diapositive 17 — Détecter les bugs reste difficile
## 第 17 页——检测缺陷仍然很困难

**Français**

Pour la détection, le modèle doit dire si une fonction contient un bug. Il y a 470 fonctions avec un bug et 470 versions corrigées.

**中文**

在缺陷检测任务中，模型需要判断一个函数是否存在缺陷。数据中有 470 个含缺陷的函数，以及 470 个修正后的版本。

**Français**

Répondre toujours la même chose donnerait donc 50 % de bonnes réponses. GPT-4 obtient 52,16 %, un résultat proche de cette référence.

**中文**

所以，即使始终回答同一个类别，也能得到 50% 的准确率。GPT-4 的准确率为 52.16%，接近这个参考值。

**Français**

Certains modèles donnent aussi des réponses que le script ne peut pas interpréter.

**中文**

有些模型还会给出评测脚本无法解析的回答。

**Français**

Après ces résultats, Xiang va présenter l’effet de l’entraînement sur les performances.

**中文**

介绍完这些结果后，接下来由 Xiang 讲解训练对模型表现的影响。

---

## Notes de préparation / 备讲说明

**Français**

Les chiffres présentés proviennent de Zeng et al., ISSTA 2024, tableaux 3 et 4. Les versions comparées sont GPT-3.5-Turbo-0301 et GPT-4-0314.

**中文**

上述数据来自 Zeng 等人发表于 ISSTA 2024 的论文，见表 3 和表 4。这里比较的 GPT 版本为 GPT-3.5-Turbo-0301 和 GPT-4-0314。

**Repères de lecture / 数字读法（练习用，不需要额外念出来）**

| Écriture / 写法 | Lecture en français / 法语读法 |
| --- | --- |
| 6,66 % | six virgule soixante-six pour cent |
| 52,16 % | cinquante-deux virgule seize pour cent |
| pass-all@1 | pass-all à un |

Les pourcentages arrondis facilitent la présentation orale. Les diapositives conservent les valeurs précises. / 讲稿中的部分百分比采用近似值，方便口头表达；幻灯片保留精确数值。
