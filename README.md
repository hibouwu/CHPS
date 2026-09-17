**English** | [简体中文](README.zh-CN.md) | [Français](README.fr.md)

# CHPS Course Materials

A personal archive of CHPS lecture notes, exercise notes, and past exam papers, including notes exported from Notability. Most notes are handwritten in French, with some explanations in Chinese. PDFs may not contain searchable text.

The collection currently focuses on M1 and contains 53 files: 50 PDFs and 3 exam images. These personal notes and solutions may contain omissions or errors; check them against the instructors' exercises and course materials.

## Browse the collection

| Directory | Current contents |
|---|---|
| [M1/AP](M1/AP/) | Lecture notes 01–04 and exercise notes 01–05 |
| [M1/APD/Note](M1/APD/Note/) | Lecture notes 00–05 and exercise notes 00–07; lecture 00 retains the topic label `graphe` |
| [M1/BaseMath/Notes](M1/BaseMath/Notes/) | Lecture notes 01–04 and exercise notes 01–05 |
| [M1/BaseMath/Examen](M1/BaseMath/Examen/) | PDF exam papers from 2021–2023, two photographed pages of the 2024 exam, and an exam photo labelled 2025 |
| [M1/CN](M1/CN/) | Lecture notes, TD/TP notes, and LU/LDLᵀ factorization notes named by topic |
| [M1/ORO](M1/ORO/) | Lecture notes 01–03, exercise notes 01, and combined exercise notes 02–03 |
| [M1/TM](M1/TM/) | Lecture notes 01–02 and exercise notes 01–02; lecture 03 is missing because I did not attend |

The local `M2/` directory is reserved for future materials and is currently empty. Git does not track empty directories, so it may not appear after cloning.

## File naming

Course abbreviations follow the existing directory names. Filenames use hyphens and two-digit lecture or exercise-set numbers:

```text
AP-Cours-01.pdf
AP-TD-02.pdf
CN-TDTP-04.pdf
APD-Cours-00-graphe.pdf
ORO-TD-02-03.pdf
CN-TDTP-Factorisation-LU-LDLT.pdf
BaseMath-Examen-2024-page-01.png
```

- `Cours` denotes lecture notes, `TD` exercise notes, `TDTP` the combined tutorial/practical-session label, and `Examen` an exam paper.
- Combined exercise sets retain both numbers, as in `TD-02-03`. Existing `00` numbers are preserved.
- When a session number cannot be confirmed, use a topic name rather than infer a number from file order. Lecture compilations need not have a session number either.
- Multiple images of the same exam use `page-01`, `page-02`, and so on. Existing version suffixes such as `a` are preserved.
- The existing `APD/Note` and `BaseMath/Notes` directory names are retained.

## Known gaps and numbering assumptions

- **TM:** Lecture 03 is missing because I did not attend; the existing exercise notes should not be treated as that lecture. The numbers in `Cours-02`, `TD-01`, and `TD-02` were inferred from the sequence of topics and are not explicitly written on the pages. The two lecture files cover differential-equation fundamentals and analytical methods, followed by second-order PDE classification, finite differences, and stability analysis. The two exercise files address the corresponding topics.
- **ORO:** `Cours-03`, originally named `笔记 2026年4月9日.pdf`, covers the big-M method, branch and bound, and integer linear programming. Its number was inferred from the existing lecture sequence and the progression of topics.
- **CN:** `CN-TDTP-04.pdf` explicitly says TD/TP4 in the document. The session number of `CN-TDTP-Factorisation-LU-LDLT.pdf` remains unconfirmed, so it uses a topic name. `CN-Cours.pdf` has no assigned session number.
- **BaseMath:** The two 2024 photos are successive pages of the same exam; the first shows the date 17 October 2024. The photo labelled 2025 is headed `EXAMEN OBHPC`; its year comes from the original filename and has not been confirmed from the photographed text.

## Adding materials

Export notes from Notability as PDFs, place them in the appropriate course directory, and check the first-page title, date, and contents before naming them. For files with matching names or a `(2)` suffix, compare their contents to determine whether they are continuations, exercises, or duplicate exports before deciding how to keep them.

Course PDFs and exam images are the main contents of this repository and should be tracked in Git. The `.gitignore` file excludes system-generated metadata, editor swap files, and temporary conversion output.

If you find these materials helpful, please consider giving this repository a star ⭐. Thank you for your support!
