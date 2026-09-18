set grid
set logscale
#plot "telaps_bcast_48" w lp, "telaps_linear_48" w lp, "telaps_btreev1_48" w lp, "telaps_btreev2_48" w lp, "telaps_btopo_48" w lp
plot "telaps_allalgos_48" u 1:2 w lp t "bcast", "" u 1:3 w lp t "linear", "" u 1:4 w lp t "btreev1", "" u 1:5 w lp t "btreev2", "" u 1:6 w lp t "btopo"

