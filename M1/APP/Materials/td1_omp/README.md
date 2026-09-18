# Rappels sur utilisation OpenMP

Pour compiler un programme C utilisant OpenMP avec le compilateur `gcc` :
```
% gcc -fopenmp  source.c  -o monprog
```

La variable d'environnement `OMP_NUM_THREADS` permet de spécifier le nombre de threads OpenMP :
```
# Possibilité 1 :  
% export OMP_NUM_THREADS=4  ;  ./monprog

# Possibilité 2 :  
% OMP_NUM_THREADS=4  ./monprog
```

La variable d'environnement `OMP_PROC_BIND` permet d'attacher les threads OpenMP sur les coeurs logiques du noeud de calcul :
```
# Binding par défaut
% export OMP_PROC_BIND=true

# ou bien, par ordre croissant des numéros des coeurs logiques
% export OMP_PROC_BIND=close 

# ou bien, en répartissant le plus possible sur le noeud de calcul
% export OMP_PROC_BIND=spread 
```

