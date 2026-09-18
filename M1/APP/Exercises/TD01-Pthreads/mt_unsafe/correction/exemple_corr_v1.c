#include <pthread.h>
#include <stdio.h>


#define COUNT_PER_THREAD 1000000
#define NUM_THREADS 10

unsigned long count = 0;

void *  parallel_count(void *args){
   pthread_mutex_t *p_mut_count = (pthread_mutex_t*)args;
   int i;
   int count_loc = 0;
   
   for(i=0; i < COUNT_PER_THREAD; ++i){
      ++count_loc;
   }

   pthread_mutex_lock(p_mut_count);
   count += count_loc;
   pthread_mutex_unlock(p_mut_count);
   
   return NULL;
}


int main(int argc, char** argv)
{
   int i;
   pthread_t pid[NUM_THREADS];
   pthread_mutex_t mut_count = PTHREAD_MUTEX_INITIALIZER; 
   
   
   for(i = 0; i < NUM_THREADS; ++i){
      pthread_create(&pid[i], NULL, parallel_count, &mut_count);
   }
   
   for(i = 0; i < NUM_THREADS; ++i){
      pthread_join(pid[i], NULL);
   }
   
   printf("Valeur finale de count %ld \n", count);
   
   return 0;
}
