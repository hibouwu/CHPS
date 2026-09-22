#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>

#define MAX_LENGTH 256
#define xstr(s) str(s)
#define str(s) #s

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

struct node {
  struct node* next;
  char msg[MAX_LENGTH];
};

struct node* head = NULL;
struct node* tail = NULL;

void* consumer(void* _arg) {
  int i = (int)(uintptr_t)_arg;

  for(;;) {
    pthread_mutex_lock(&mutex);
    while(head == NULL)
      pthread_cond_wait(&cond, &mutex);

    struct node* n = head;
    head = n->next;
    if(!head)
      tail = NULL;
    pthread_mutex_unlock(&mutex);

    printf("[%d] Receive: %s\n", i, n->msg);
    free(n);
  }

  return 0;
}

void producer() {
  for(;;) {
    struct node* cur = malloc(sizeof(*cur));

    scanf("%"xstr(MAX_LENGTH)"s", cur->msg);

    if(strncmp(cur->msg, "exit", MAX_LENGTH) == 0)
      exit(0);

    cur->next = NULL;
    
    pthread_mutex_lock(&mutex);
    if(tail)
      tail->next = cur;
    else
      head = cur;
    tail = cur;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
  }
}

int main(int argc, char** argv) {
  if(argc != 2) {
    fprintf(stderr, "Usage: %s nb-threads\n", argv[0]);
    exit(1);
  }

  int n = atoi(argv[1]);
  pthread_t tids[n];

  for(int i=0; i<n; i++)
    pthread_create(tids + i, NULL, consumer, (void*)(uintptr_t)i);

  producer();
  
  for(int i=0; i<n; i++) {
    void* retval;
    pthread_join(tids[i], &retval);
  }

  printf("Main quitting\n");
  
  return 0;
}
