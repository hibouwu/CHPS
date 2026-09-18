#!/bin/bash

P="$1"
if [ -z "$P" ]
then
    echo "Mettre le nombre de processus en argument. Abort"
    exit 1
fi
echo "$P processus"

str_gnu="plot \"pts_max\" w lp"
for(( i=0 ; i<P ; i++ ))
do
    fic_i=$(printf "pts_P%05d" $i)
    if [ ! -f $fic_i ]
    then
        echo "Le fichier $fic_i est inexistant. Abort"
        exit 1
    fi
    str_gnu="$str_gnu, \"$fic_i\" w lp"
done

echo "Creation du fichier trace_pts.gnu"
echo -e $str_gnu > trace_pts.gnu
echo "pause -1" >> trace_pts.gnu

