#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 20

void* hello(void* _arg) {
  int* p = _arg;
  printf("[%llx] Hello from %d\n", (unsigned long long)pthread_self(), *p);
  free(p);
  return NULL;
}

int main(int argc, char* argv[]) {
  pthread_t tid[N];
  void* retval;

  for(int i=0; i<N; i++) {
    int* p = malloc(sizeof(*p));
    *p = i;
    pthread_create(&tid[i], NULL, hello, p);
  }

  for(int i=0; i<N; i++)
    pthread_join(tid[i], &retval);

  printf("Quitting\n");
  
  pthread_exit(NULL);
  return 0;
}
