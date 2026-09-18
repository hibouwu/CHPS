#!/bin/bash

str_sched=$1

if [ -n "$2" ]
then
	str_sched="$str_sched,$2"
fi

rm -f iter_T*
./a.out $*

cat iter_T* | sort -nu > sched_$str_sched
echo "Fichier cree : sched_$str_sched"

