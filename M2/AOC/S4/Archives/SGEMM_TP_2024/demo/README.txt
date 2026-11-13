Pour compiler : make

Pour exécuter avec une taille 300, 2 répétitions de warmup (lors de la première méta) et 10 répétitions de mesure : ./bench 300 2 10

Pour exécuter avec MAQAO :
maqao oneview -R1 xp=ov1_orig -- ./bench 300 2 10

Pour visualiser les résultats :
firefox ov1_orig/RESULTS/bench_one_html/index.html
