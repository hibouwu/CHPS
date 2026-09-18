#include <stdio.h>
#include <pthread.h>
#include <assert.h>

#define NTHREADS 5

/* 
Function to be run by our threads 
(parameters should always be passed through a void pointer)
*/
void* hello(void *args) {
  int index = *((int *)args); // (in our case, there is only one value)
  pthread_t tid = pthread_self(); // Get the current handle/TID
  printf("[%lu] Hello from %d\n", tid, index);
  
  return NULL;
}

int main(void) {
  int errcode;
  pthread_t threads[NTHREADS];
  int args[NTHREADS]; // To be used as parameters
  
  /* Create all requested threads */
  for(int i=0; i<NTHREADS; ++i) {
    args[i] = i; // Set the thread ID parameter
    /* Create a new thread running helloworld with args as argument */
    errcode = pthread_create(&threads[i], NULL, hello, args+i);
    assert(!errcode);
  }
  /* Wait for all threads to finish */
  for (int i = 0; i < NTHREADS; i++) {
  errcode = pthread_join(threads[i], NULL);
    assert(!errcode);
  }
  return 0;
}
