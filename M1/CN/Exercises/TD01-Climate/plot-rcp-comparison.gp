set xlabel "Année"
set ylabel "Température (K)"
set title "Comparaison des scénarios RCP"
set key top left
plot "output_constant.dat" with lines title "CO2 constant (370 ppm)", \
     "output_rcp26.dat" with lines title "RCP2.6 (mitigation forte)", \
     "output_rcp60.dat" with lines title "RCP6.0 (émissions élevées)"
pause -1