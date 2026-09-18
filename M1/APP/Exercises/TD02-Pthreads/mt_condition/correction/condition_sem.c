#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

sem_t sem;

volatile int valB = 0;


int work(int valeur)
{   
   /* Fait semblant de bosser */
   sleep(rand()%5);
   
   return valeur+1;;
}

void * runA(void * arg)
{
   int valA = 0;
   
   valA = work(valA);
   
   printf("*A* En attente du résultat de B\n");
   sem_wait(&sem); 
   
   printf("*A* Valeur de A: %d Valeur de B: %d\n", valA, valB);
   return NULL;
}


void * runB(void * arg)
{
   valB = work(valB);
   
   /*Signale à A que j'ai calculé valB*/
   sem_post(&sem);
   printf("*B* Valeur calculée %d \n", valB);
   
   return NULL;
}


int main(int argc, char ** argv)
{  
   pthread_t threadA, threadB;
   
   srand(time(0));
  
   if (sem_init(&sem, /*pshared*=*/0, /*value=*/0) == -1)
   {
       printf("Echec lors de la creation du semaphore\n");
       return 1;
   } 

   pthread_create(&threadA, NULL, runA, NULL);
   pthread_create(&threadB, NULL, runB, NULL);
      
   pthread_join(threadA, NULL);
   pthread_join(threadB, NULL);    
  
   sem_destroy(&sem);

   return 0;
}
