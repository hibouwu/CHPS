# 逐页答辩问题清单 — Audit de couverture Q&A

基于当前最终答辩材料生成：

- `karman_lbm_20260504_final_readable.pptx` (13 slides)
- `exports/soutenance_partie2_fr.md` (script oral Part 2, slides 8–13)
- `工作记录/优化01.md` … `工作记录/优化26.md`

每个文件格式：
- **可能问题** : 3–6 条，风险级别 HIGH / MEDIUM / LOW
- **已覆盖情况** : PPT 是/否 · Script 是/否 · Gaps
- **建议回答（法语）** : 每题 2–4 句口语化法语，证据薄弱处标注 "à vérifier"
- **证据** : 具体文件路径
- **Phrases à éviter** : PPT/脚本中容易被追问的危险表述

---

## Top 10 questions probables (classées par probabilité et risque)

| # | Slide | Question | Risque | Piège principal |
|---|-------|----------|--------|-----------------|
| 1 | 4 — P1-A | Comment avez-vous localisé le `nanosleep` ? | HIGH | Incapacité à expliquer le mécanisme d'obfuscation (hex encode → dlsym → inline asm) |
| 2 | 10 — AVX-512 | Vous n'avez pas écrit d'intrinsics — comment prouvez-vous qu'AVX-512 est utilisé ? | HIGH | Confondre "zmm dans objdump" avec "FMA prouvé" ou "performance optimale" |
| 3 | 5 — P1-B | Le coût MPI vient de la latence, pas du volume — comment le prouvez-vous ? | HIGH | Dire que le volume a changé (il n'a pas changé) ou surestimer le rôle des barrières |
| 4 | 12 — Résultats | Pourquoi np=1 est-il meilleur que np=2 ? N'est-ce pas une limitation ? | HIGH | Répondre de façon défensive ; l'explication est technique et valide (zéro MPI overhead) |
| 5 | 9 — SoA | Pourquoi SoA donne-t-il d'abord une régression de -22% ? | HIGH | Confondre SoA avec "meilleur layout = gain immédiat" ; la boucle doit être adaptée aussi |
| 6 | 7 — P1-D SIMD | Pourquoi `-march=native + omp simd` dégrade sur Apple M3 ? | HIGH | Affirmer la cause au lieu de dire "diagnostic probable" ; risque de contradiction |
| 7 | 3 — Roadmap | Les gains de Part 1 et Part 2 sont-ils comparables ? | MEDIUM | Citer un facteur ×34 sans caveat non iso-plateforme |
| 8 | 4 — P1-A | La formule MLUPS surestimait par combien et pourquoi ? | MEDIUM | Incapacité à expliquer le bug comm_size sans hésitation |
| 9 | 11 — Halo/OMP | 832 → 905 MLUPS — est-ce un résultat officiel ? | MEDIUM | Présenter une mesure dev comme résultat final |
| 10 | 13 — Conclusion | Quelle est la principale limitation de votre travail ? | MEDIUM | Réponse trop vague ou trop auto-critique ; avoir une réponse calibrée prête |

---

## Fichiers par slide

- [01_cover_questions.md](01_cover_questions.md) — Slide 1 : Page de couverture
- [02_contexte_questions.md](02_contexte_questions.md) — Slide 2 : Contexte physique et FOM
- [03_feuille_de_route_questions.md](03_feuille_de_route_questions.md) — Slide 3 : Feuille de route
- [04_p1a_corrections_questions.md](04_p1a_corrections_questions.md) — Slide 4 : P1-A Corrections de validité
- [05_p1b_mpi_questions.md](05_p1b_mpi_questions.md) — Slide 5 : P1-B Réduction latence MPI
- [06_p1c_openmp_questions.md](06_p1c_openmp_questions.md) — Slide 6 : P1-C Localité mémoire + OpenMP
- [07_p1d_simd_questions.md](07_p1d_simd_questions.md) — Slide 7 : P1-D Diagnostics (ex. SIMD macOS)
- [08_plateforme_p2_questions.md](08_plateforme_p2_questions.md) — Slide 8 : Transition Part 2 + protocole
- [09_p2a_soa_questions.md](09_p2a_soa_questions.md) — Slide 9 : P2-A AoS → SoA
- [10_avx512_resultat_questions.md](10_avx512_resultat_questions.md) — Slide 10 : P2-B AVX-512
- [11_p2cd_halo_omp_questions.md](11_p2cd_halo_omp_questions.md) — Slide 11 : P2-C/D Halo k-major + OMP region
- [12_resultats_finaux_questions.md](12_resultats_finaux_questions.md) — Slide 12 : Résultats finaux
- [13_conclusion_questions.md](13_conclusion_questions.md) — Slide 13 : Conclusion
