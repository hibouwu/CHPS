#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdatomic.h>

struct cs {
  void         (*func)(int);
  int          arg;
  _Atomic bool completed;
};

int n;
_Thread_local struct cs* request;
struct cs* pendings;
int var;

void pause() {
  asm volatile("pause");
}

void add(int val) {
  printf("add %d\n", val);
  var += val;
}

void* slave(void* _arg) {
  int i = (int)(uintptr_t)_arg;
  request = pendings + i;
  
  for(;;) {
    request->arg = 2;
    request->func = add;
    atomic_store(&request->completed, 0);
    while(!atomic_load(&request->completed))
      pause();

    request->arg = 1;
    request->func = add;
    atomic_store(&request->completed, 0);
    while(!atomic_load(&request->completed))
      pause();
  }
}

void master() {
  for(;;) {
    for(int i=0; i<n; i++) {
      if(!atomic_load(&pendings[i].completed)) {
        pendings[i].func(pendings[i].arg);
        atomic_store(&pendings[i].completed, 1);
      }
    }
    pause();
  }
}

int main(int argc, char** argv) {
  if(argc < 2) {
    fprintf(stderr, "usage: %s nb-threads\n", argv[0]);
    exit(1);
  }

  n = atoi(argv[1]);
  pthread_t tids[n];

  pendings = malloc(n * sizeof(*pendings));
  
  for(int i=0; i<n; i++) {
    pendings[i].completed = 1;
    pthread_create(&tids[i], NULL, slave, (void*)(uintptr_t)i);
  }

  master();

  for(int i=0; i<n; i++) {
    void* ret;
    pthread_join(tids[i], &ret);
  }
  
  return 0;
}
