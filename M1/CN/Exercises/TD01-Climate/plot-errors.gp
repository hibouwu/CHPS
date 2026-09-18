set xlabel "Nombre d'itérations"
set ylabel "Erreur"
set title "Evolution de l'erreur numérique"
set logscale xy 2
set grid
plot "errors.dat" using 1:2 with linespoints title "Erreur vs Reference"
pause -1