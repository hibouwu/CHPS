# 第三部分演讲稿 / Résultats : contexte et modèles

Jianye SHI · 第 14–17 页 · 法语正文约 374 词（目标时长：3 分 15 秒 – 3 分 30 秒，需排练计时）。演讲时读法语，中文用于理解和练习；底部问答不计入正文。

## 14 — Le contexte du projet aide la génération / 项目上下文有助于代码生成

**Français**

Merci Hao. Après la méthode, passons aux résultats. Première question : quelles informations faut-il fournir au modèle pour générer une fonction ? En haut de la diapositive, on voit le contexte extrait de la classe : les imports, les champs et les signatures des autres méthodes.

**中文**

谢谢 Hao。看完方法，我们来看结果。第一个问题是：给模型提供什么信息才能帮它生成函数？幻灯片上方展示了从类中提取的上下文：导入包、成员变量和其他方法签名。

**Français**

Sur le tableau, avec CodeLlama-13B, donner un ou quatre exemples change peu le score : on reste entre 13 et 14,5 %. En revanche, avec le contexte du projet, on grimpe à près de 22 %. Connaître la structure de la classe aide donc bien plus que d'ajouter des exemples.

**中文**

看表格，对于 CodeLlama-13B，给一个或四个示例对分数影响不大，都在 13% 到 14.5% 之间。但提供项目上下文后，得分升至近 22%。因此，了解类的结构比单纯增加示例更有用。

## 15 — Un écart plus marqué en réparation / 修复任务中的差距更明显

**Français**

Voyons maintenant comment les modèles se comparent dans le tableau 4, en prenant CodeLlama-34B face à GPT-3.5 et GPT-4.

**中文**

接下来看表 4 中的模型对比，我们用 CodeLlama-34B 与 GPT-3.5 和 GPT-4 对照。

**Français**

En génération de fonctions, CodeLlama fait jeu égal avec GPT-3.5 autour de 23 %, contre 30,5 % pour GPT-4. Mais en réparation de bugs, tous les scores chutent et l’écart se creuse : CodeLlama tombe à 5 %, contre 9 % pour GPT-3.5 et près de 19 % pour GPT-4. L’écart avec GPT-4 passe ainsi de 8 à près de 14 points.

**中文**

在函数生成中，CodeLlama 与 GPT-3.5 持平（约 23%），GPT-4 为 30.5%。但在缺陷修复中，所有得分都在下降且差距拉大：CodeLlama 跌至 5%，GPT-3.5 约 9%，GPT-4 近 19%。与 GPT-4 的差距从 8 个点扩大到了近 14 个点。

## 16 — GPT-4 : des scores différents selon la tâche / GPT-4 在不同任务上的得分不同

**Français**

Même pour GPT-4, les résultats varient fortement selon la tâche. S'il dépasse 30 % en génération et 24 % pour tester le code, il descend à 19 % en réparation, et chute à 6,66 % en ITG pour reproduire un bug.

**中文**

即便对于 GPT-4，不同任务的表现差异也很大。函数生成超过 30%，代码测试超过 24%，修复降到 19%，而在复现缺陷的 ITG 任务上则暴跌至 6.66%。

**Français**

Pour lire ces scores, il faut aussi tenir compte des critères de réussite. En FCG et APR, il faut passer les tests existants ; en CTG, le test doit s’exécuter et couvrir le code. Mais en ITG, le modèle part du rapport de bug, sans le contexte de classe : son test doit échouer sur la version défectueuse, puis réussir après correction.

**中文**

解读这些得分时，也要考虑各项任务的成功标准。FCG 和 APR 要求通过现有测试，CTG 要求生成的测试能运行并覆盖代码。但在 ITG 中，模型从缺陷报告出发，没有类上下文：生成的测试必须在含缺陷版本上失败，并在修复后通过。

## 17 — Détecter les bugs reste difficile / 检测缺陷仍然很困难

**Français**

Enfin, même détecter un bug reste très difficile. Sur les 940 fonctions — 470 avec bug et 470 corrigées — répondre toujours la même chose donne déjà 50 %.

**中文**

最后，哪怕只是检测缺陷也依然困难。在 940 个函数（470 个含缺陷、470 个已修复）上，始终回答同一个选项就能拿到 50%。

**Français**

Or, GPT-4 atteint seulement 52,16 % d’accuracy, à peine deux points au-dessus de cette référence. Les auteurs l'expliquent par la complexité des erreurs logiques dans de vrais projets.

**中文**

然而 GPT-4 的准确率只有 52.16%，仅比基准高出约两个百分点。作者认为这是因为真实项目中的逻辑错误过于复杂。

**Français**

En résumé, le contexte aide à générer une fonction, mais cela ne garantit pas de savoir réparer ou détecter un bug. L’entraînement spécialisé ou l'instruction tuning permettent-ils de faire mieux ? Je laisse la parole à Xiang.

**中文**

总之，上下文有助于生成函数，但并不能保证模型会修 Bug 或找 Bug。特定语言训练或指令微调能改善表现吗？下面交给 Xiang。

## 备讲（Q&A 锦囊）

以下内容用于回答追问，不需要在正文中逐条念出。

### 为什么第 14 页用 13B，第 15 页换成 34B？

**Français**

Le tableau 3 étudie les prompts avec CodeLlama-13B. Le tableau 4 compare davantage de modèles ; nous y avons retenu la version de base 34B. Ce changement ne constitue pas une expérience contrôlée sur la taille du modèle.

**中文**

表 3 用 CodeLlama-13B 比较提示；表 4 比较更多模型，我们选了其中的基础版 34B。两页不能用来单独证明模型规模的作用，也不应把“最大”说成所有任务都“最强”。

### 第 14 页的图就是模型收到的完整提示吗？

**Français**

C’est un extrait de la figure 2(a), avec des annotations traduites. Il montre le contexte de classe. Le prompt complet contient aussi la description de la tâche, le commentaire et la signature de la fonction à générer. Les modèles de base utilisent le format de complétion.

**中文**

这是图 2(a) 的局部，旁注译成了法语，用来说明类上下文。完整提示还包含任务描述、函数注释和待生成函数的签名。基础模型使用补全格式，不能把这个对话格式示例当作 CodeLlama-13B 的完整输入。

### 为什么说上下文比示例更有帮助？

**Français**

Pour CodeLlama-13B en FCG, le tableau 3 donne 12,84 % avec un exemple, 14,50 % avec quatre exemples et 21,91 % avec le contexte. Cette conclusion porte sur les prompts comparés ; elle ne signifie pas que tous les exemples sont inutiles.

**中文**

依据是表 3 的 FCG / pass-all@1：一个示例 12.84%，四个示例 14.50%，项目上下文 21.91%。结论限于这些提示和任务，不说所有 few-shot 都无效，也不把示例称为“无关示例”。

### ITG 真的只给一段文字、完全没有代码信息吗？

**Français**

Le prompt contient le rapport de bug, la consigne et une signature de fonction. Les auteurs n’ajoutent pas le contexte de classe ni le commentaire de fonction. Un rapport peut lui-même contenir du code : il vaut donc mieux éviter de dire « aucun code ».

**中文**

§3.4 列出 issue 报告、任务描述和函数签名；不提供的是抽象类上下文和函数注释。报告本身可能包含代码，所以不应说“只有自然语言”或“完全没有代码”。

### ITG 的低分就是双重验证造成的吗？

**Français**

La double vérification fait partie du critère de réussite. Elle aide à comprendre les exigences de la tâche, mais les résultats ne permettent pas d’isoler son effet de celui du prompt ou des difficultés propres aux bugs.

**中文**

双重验证属于成功条件，可以帮助理解任务要求，但这些结果没有单独分离它、输入提示和缺陷本身难度的影响。FCG/APR 通过原有测试也不是没有难度。

### pass-all@1、accuracy 和 50% 基线分别是什么？

**Français**

Le pass-all@1 estime la réussite d’une seule proposition, à partir des échantillons générés. L’accuracy est la proportion de classifications correctes en DD. Sur ce jeu équilibré, une réponse constante obtient exactement 50 % ; un choix aléatoire équilibré donne 50 % en espérance.

**中文**

pass-all@1 根据生成样本估计单个候选成功的概率，论文每题采样 20 个候选。accuracy 是 DD 分类正确比例。平衡数据上，固定回答同一类恰好为 50%；均匀随机猜测是期望为 50%，单次结果并不固定。52.16% 比基线高 2.16 个百分点，不是高 2.16%。

### 为什么不用文中出现的 ITG 15.76%？

**Français**

Le tableau 4 indique 6,66 % à k = 1 et 15,76 % à k = 10 pour GPT-4. Nous suivons le tableau, car le texte de RQ2 semble mélanger les deux valeurs.

**中文**

表 4 的 GPT-4 ITG：pass-all@1 为 6.66%，pass-all@10 为 15.76%。正文 RQ2 的列举存在混用，我们按表格和相同 k 值比较。

### 这些结论是否代表今天所有模型的能力？

**Français**

Nous présentons les versions et le protocole de l’article de 2024, notamment GPT-3.5-Turbo-0301 et GPT-4-0314. Les erreurs logiques sont une explication avancée par les auteurs, pas une cause isolée expérimentalement.

**中文**

讨论范围是 2024 年论文中的版本与实验协议，特别是 GPT-3.5-Turbo-0301 和 GPT-4-0314。复杂逻辑错误是作者提出的解释，不是已隔离验证的因果结论；不能外推为当前所有模型“都无能为力”。

来源：Zeng et al., ISSTA 2024，§3.3–3.5、§4.3.1–4.3.2、图 2、表 3–4。见[论文中英对照](../../CoderUJB_中英对照.md)。