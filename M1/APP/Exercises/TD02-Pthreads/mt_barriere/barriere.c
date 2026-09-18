#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


typedef struct
{
      /*A compléter*/ 
      pthread_cond_t cond;
      
}my_barrier_t;



/* Initialise une barrière pour num threads*/
int my_barrier_init(my_barrier_t * barrier, int num)
{
      /*A compléter*/ 
}

/* Bloque tant que tous les threads ne sont pas arrivés */
int my_barrier_wait(my_barrier_t * barrier)
{
      /*A compléter*/ 
}


my_barrier_t barrier;

void * run(void * arg)
{
    long rank = (long)arg;
    int i;
    for(i = 0 ; i < 5 ; i++)
    {
        sleep( rand()%5 );
        printf("*Iter %d,Thread %ld* AVANT \n", i, rank);
        my_barrier_wait(&barrier);
        printf("*Iter %d,Thread %ld* APRES \n", i, rank);
    }
    return NULL;
}



#define NUM_THREADS 5

int main(int argc, char ** argv)
{  
   pthread_t threads[NUM_THREADS];
   long i;
   
   my_barrier_init(&barrier, NUM_THREADS);
      
   srand(time(0));
   
   for(i=0; i < NUM_THREADS; ++i)
      pthread_create(&threads[i], NULL, run, (void*)i);
   
   for(i=0; i < NUM_THREADS; ++i)
      pthread_join(threads[i], NULL);
      
   return 0;
}
