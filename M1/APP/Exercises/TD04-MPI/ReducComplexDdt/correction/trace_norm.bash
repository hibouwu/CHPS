#!/bin/bash

# tail -n 1 pts_max | awk '{printf("%.6e\n", sqrt($1*$1 + $2*$2))}'
P="$1"
if [ -z "$P" ]
then
    echo "Mettre le nombre de processus en argument. Abort"
    exit 1
fi
echo "$P processus"

iglob=0
rm -f trace_norm.pts
for(( i=0 ; i<P ; i++ ))
do
    fic_i=$(printf "pts_P%05d" $i)
    if [ ! -f $fic_i ]
    then
        echo "Le fichier $fic_i est inexistant. Abort"
        exit 1
    fi
    fic_awk=$(mktemp)
    echo "BEGIN {iglob=$iglob}" > $fic_awk
    echo "{printf(\"%d %.6e\\n\", iglob, sqrt(\$1*\$1 + \$2*\$2)); iglob += 1; }" >> $fic_awk
    cat $fic_i | awk -f $fic_awk >> trace_norm.pts
    echo "" >> trace_norm.pts
    nbl=$(cat $fic_i | wc -l)
    iglob=$(expr $iglob + $nbl)
    rm -f $fic_awk
done

# Recuperation de la norme max
if [ ! -f "pts_max" ]
then
    echo "Fichier pts_max absent. Abort"
    exit 1
fi
norm_max=$(tail -n 1 pts_max | awk '{printf("%.6e\n", sqrt($1*$1 + $2*$2))}')
echo "Norme max : $norm_max"
str_gnu="plot \"trace_norm.pts\" w lp, $norm_max w l"

output_gnu="trace_norm.gnu"
echo "Creation du fichier $output_gnu"
echo -e $str_gnu > $output_gnu
echo "pause -1" >> $output_gnu

