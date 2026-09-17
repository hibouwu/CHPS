[English](README.md) | [简体中文](README.zh-CN.md) | **Français**

# Documents de cours CHPS

Archives personnelles de notes de cours, de travaux dirigés et de sujets d'examen du cursus CHPS, comprenant des notes exportées depuis Notability. Les notes sont principalement manuscrites en français, avec quelques explications en chinois. Les PDF ne contiennent pas nécessairement de texte interrogeable.

La collection porte actuellement sur le M1 et comprend 53 fichiers : 50 PDF et 3 images de sujets d'examen. Ces notes et solutions personnelles peuvent comporter des omissions ou des erreurs ; elles sont à vérifier à l'aide des énoncés et des supports fournis par les enseignants.

## Parcourir les documents

| Dossier | Contenu actuel |
|---|---|
| [M1/AP](M1/AP/) | Notes de cours 01–04 et de TD 01–05 |
| [M1/APD/Note](M1/APD/Note/) | Notes de cours 00–05 et de TD 00–07 ; le cours 00 conserve la mention thématique `graphe` |
| [M1/BaseMath/Notes](M1/BaseMath/Notes/) | Notes de cours 01–04 et de TD 01–05 |
| [M1/BaseMath/Examen](M1/BaseMath/Examen/) | Sujets d'examen en PDF de 2021 à 2023, deux pages photographiées du sujet de 2024 et une photo de sujet étiquetée 2025 |
| [M1/CN](M1/CN/) | Notes de cours, de TD/TP et de factorisation LU/LDLᵀ, ces dernières étant nommées par thème |
| [M1/ORO](M1/ORO/) | Notes de cours 01–03, TD 01 et notes regroupées des TD 02–03 |
| [M1/TM](M1/TM/) | Notes de cours 01–02 et de TD 01–02 ; les notes du troisième cours manquent en raison de mon absence |

Le dossier local `M2/` est réservé aux futurs documents et ne contient encore aucun fichier. Git ne suit pas les dossiers vides : il peut donc ne pas apparaître après le clonage.

## Nommage des fichiers

Les abréviations des matières reprennent les noms des dossiers existants. Les noms de fichiers utilisent des traits d'union et des numéros de cours ou de feuilles d'exercices à deux chiffres :

```text
AP-Cours-01.pdf
AP-TD-02.pdf
CN-TDTP-04.pdf
APD-Cours-00-graphe.pdf
ORO-TD-02-03.pdf
CN-TDTP-Factorisation-LU-LDLT.pdf
BaseMath-Examen-2024-page-01.png
```

- `Cours` désigne les notes de cours, `TD` les notes de travaux dirigés, `TDTP` conserve la désignation commune aux travaux dirigés et pratiques, et `Examen` désigne un sujet d'examen.
- Les feuilles regroupées conservent leurs numéros, par exemple `TD-02-03`. Les numéros `00` existants sont conservés.
- Lorsqu'un numéro de séance n'est pas confirmé, le fichier est nommé par thème, sans déduire le numéro de l'ordre des fichiers. Un recueil de cours ne reçoit pas non plus de numéro de séance arbitraire.
- Les images d'un même sujet sont distinguées par `page-01`, `page-02`, etc. Les suffixes de version existants, comme `a`, sont conservés.
- Les noms de dossiers `APD/Note` et `BaseMath/Notes` sont conservés.

## Lacunes connues et numérotation déduite

- **TM :** Les notes du troisième cours manquent en raison de mon absence ; les TD présents ne doivent pas être assimilés à ce cours. Les numéros de `Cours-02`, `TD-01` et `TD-02` ont été déduits de l'enchaînement des thèmes et ne figurent pas explicitement sur les pages. Les deux fichiers de cours portent respectivement sur les bases des équations différentielles et les méthodes analytiques, puis sur la classification des EDP du second ordre, les différences finies et l'analyse de stabilité. Les deux fichiers de TD traitent des thèmes correspondants.
- **ORO :** `Cours-03`, initialement nommé `笔记 2026年4月9日.pdf`, traite de la méthode du grand M, de la séparation et évaluation (branch and bound) et de la programmation linéaire en nombres entiers. Son numéro a été déduit de la suite des cours existants et de la progression des thèmes.
- **CN :** Le document `CN-TDTP-04.pdf` porte explicitement la mention TD/TP4. Le numéro de séance de `CN-TDTP-Factorisation-LU-LDLT.pdf` reste à confirmer ; son nom indique donc le thème. Aucun numéro de séance n'est attribué à `CN-Cours.pdf`.
- **BaseMath :** Les deux photos de 2024 sont deux pages successives du même sujet ; la première porte la date du 17 octobre 2024. La photo étiquetée 2025 porte le titre `EXAMEN OBHPC` ; l'année provient du nom de fichier d'origine et n'a pas été confirmée dans le texte photographié.

## Ajouter des documents

Exporter les notes de Notability au format PDF, les placer dans le dossier de la matière correspondante, puis vérifier le titre de la première page, la date et le contenu avant de les nommer. Si plusieurs fichiers portent le même nom ou un suffixe `(2)`, comparer leur contenu pour déterminer s'il s'agit d'une suite, d'exercices ou d'un export en double avant de choisir comment les conserver.

Les PDF de cours et les images de sujets d'examen constituent le contenu principal de ce dépôt et doivent être suivis par Git. Le fichier `.gitignore` exclut les métadonnées générées par le système, les fichiers temporaires des éditeurs et les résultats temporaires de conversion.

Si ces documents vous sont utiles, pensez à laisser une étoile ⭐ à ce dépôt. Merci pour votre soutien !
