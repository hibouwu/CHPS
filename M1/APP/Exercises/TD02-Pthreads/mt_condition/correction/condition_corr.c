#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int valB = 0;

volatile int compteur = 0;

int work(int valeur)
{   
   /* Fait semblant de bosser */
   sleep(rand()%5);
   
   return valeur+1;
}

void * runA(void * arg)
{
   int valA = 0;
   
   valA = work(valA);
   printf("*A* Valeur calculée %d \n", valA);
    
   pthread_mutex_lock(&mutex);
   
   if (compteur == 0)
   {
       /* A est le premier a passer */

       compteur++; /* le compteur doit etre incremente' 
                      AVANT pthread_cond_wait car celui-ci peut relacher le mutex*/

       printf("*A* En attente du résultat de B\n");
       pthread_cond_wait(&cond, &mutex);
   }
   else
   {
       /* A n'est pas le premier, B n'a pas emis le signal, on n'attend pas */
       printf("*A* n'attend pas le résultat de B\n");
       compteur++;

   }
   
   pthread_mutex_unlock(&mutex);
   
   printf("*A* Valeur de A: %d Valeur de B: %d\n", valA, valB);
   return NULL;
}


void * runB(void * arg)
{


   valB = work(valB);
   printf("*B* Valeur calculée %d \n", valB);
   
   pthread_mutex_lock(&mutex);

   if (compteur != 0)
   {





       /*Signale à A que j'ai calculé valB*/
       pthread_cond_signal(&cond);     
       printf("*B* Signal B termine\n");
   }
   else /* compteur == 0 */
   {
       /* B est le premier a passer :
        pas de signal a envoyer car A n'est pas en attente */
       printf("*B* a termine le premier \n");
   }

   compteur++;
   
   pthread_mutex_unlock(&mutex);

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
