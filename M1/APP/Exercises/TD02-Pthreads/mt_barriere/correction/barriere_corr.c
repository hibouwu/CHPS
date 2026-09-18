#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


typedef struct
{
    int cptr;
    int cptr_max;

    pthread_mutex_t mut;
    pthread_cond_t cond;
      
}my_barrier_t;



/* Initialise une barrière pour num threads*/
int my_barrier_init(my_barrier_t * barrier, int num)
{
    pthread_mutex_init(&(barrier->mut),  NULL);
    pthread_cond_init (&(barrier->cond), NULL);

    barrier->cptr     = 0;
    barrier->cptr_max = num;
}

/* Bloque tant que tous les threads ne sont pas arrivés */
int my_barrier_wait(my_barrier_t * barrier)
{
   pthread_mutex_lock(&(barrier->mut));

   barrier->cptr++;

   if (barrier->cptr == barrier->cptr_max)
   {
       barrier->cptr = 0;
       printf("Le dernier débloque la barrière\n");
       pthread_cond_broadcast(&(barrier->cond));
   }
   else
   {
       pthread_cond_wait(&(barrier->cond), &(barrier->mut));
   }

   pthread_mutex_unlock(&(barrier->mut));
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
