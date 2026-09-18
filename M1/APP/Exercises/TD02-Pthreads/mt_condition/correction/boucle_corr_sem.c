#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>


sem_t sem_Bover;
sem_t sem_AR;

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
    
      printf("*A* En attente de B\n");
      sem_wait(&sem_Bover);
      
      /* Les deux valeurs devraient toujours être égales */
      printf("*A* Valeur de A: %d Valeur de B: %d\n", valA, valB);

      /* debloque B */
      sem_post(&sem_AR);
   }
   return NULL;
}


void * runB(void * arg)
{
   while(1)
   {
      valB = work(valB);
      
      /*Signale à A que j'ai calculé valB*/
      sem_post(&sem_Bover);
      printf("*B* Valeur calculée %d \n", valB);
      sem_wait(&sem_AR);
   }
   return NULL;
}


int main(int argc, char ** argv)
{  
   pthread_t threadA, threadB;
   
   srand(time(0));

   sem_init(&sem_Bover, /*pshared*/0, /*vini*/0);
   sem_init(&sem_AR, /*pshared*/0, /*vini*/0);
   
   pthread_create(&threadA, NULL, runA, NULL);
   pthread_create(&threadB, NULL, runB, NULL);
      
   pthread_join(threadA, NULL);
   pthread_join(threadB, NULL);    

   sem_destroy(&sem_Bover);
   sem_destroy(&sem_AR);
   
   return 0;
}
