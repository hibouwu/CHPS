# Rappels sur les threads POSIX

Les threads POSIX sont créés à partir de la fonction `pthread_create`.

L'attente de la terminaison d'un thread ainsi créé se fait à partir de la fonction `pthread_join`.

Pour compiler un programme C utilisant les threads POSIX avec le compilateur `gcc` :
```
prompt> gcc -pthread  source.c  -o monprog
```

