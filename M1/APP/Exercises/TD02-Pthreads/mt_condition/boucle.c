#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int valB = 0;


int work(int valeur)
{   
   /* Fait semblant de bosser */
   sleep(rand()%5);
   
   return valeur+1;;
}

void * runA(void * arg)
{
   int valA = 0;
   while(1)
   {
      valA = work(valA);
    
      pthread_mutex_lock(&mutex);
   
      printf("*A* En attente de B\n");
      pthread_cond_wait(&cond, &mutex);
      
      pthread_mutex_unlock(&mutex);
      
      /* Les deux valeurs devraient toujours être égales */
      printf("*A* Valeur de A: %d Valeur de B: %d\n", valA, valB);
   }
   return NULL;
}


void * runB(void * arg)
{
   while(1)
   {
      valB = work(valB);
      
      /*Signale à A que j'ai calculé valB*/
      pthread_cond_signal(&cond);     
      printf("*B* Valeur calculée %d \n", valB);
   }
   return NULL;
}


int main(int argc, char ** argv)
{  
   pthread_t threadA, threadB;
   
   srand(time(0));
   
   pthread_create(&threadA, NULL, runA, NULL);
   pthread_create(&threadB, NULL, runB, NULL);
      
   pthread_join(threadA, NULL);
   pthread_join(threadB, NULL);    
   
   return 0;
}
