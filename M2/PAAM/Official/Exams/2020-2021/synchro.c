#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

struct node {
  struct node* next;
  char         cmd[256];
};

struct queue {
  struct node* head;
  struct node* tail;
};

struct queue jobs = { NULL, NULL };
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* slave(void* unused) {
  pthread_mutex_lock(&mutex);

  for(;;) {
    while(!jobs.head)
      pthread_cond_wait(&cond, &mutex);

    struct node* node = jobs.head;

    if(!strcmp(node->cmd, "quit\n")) {
      pthread_mutex_unlock(&mutex);
      return NULL;
    }

    if(!node->next)
      jobs.tail = NULL;
    jobs.head = node->next;

    pthread_mutex_unlock(&mutex);

    system(node->cmd);
    free(node);

    pthread_mutex_lock(&mutex);
  }
}

void master() {
  for(;;) {
    struct node* node = malloc(sizeof(*node));
    node->next = NULL;
    printf("> ");
    fflush(stdout);

    if(!fgets(node->cmd, 256, stdin))
      return;

    pthread_mutex_lock(&mutex);

    if(!jobs.head)
      jobs.head = node;
    else
      jobs.tail->next = node;
    jobs.tail = node;

    if(!strncmp(node->cmd, "quit\n", 256)) {
      pthread_cond_broadcast(&cond);
      pthread_mutex_unlock(&mutex);
      return;
    } else
      pthread_cond_signal(&cond);
      pthread_mutex_unlock(&mutex);
  }
}

int main(int argc, char** argv) {
  if(argc < 2) {
    fprintf(stderr, "usage: %s nb-threads\n", argv[0]);
    exit(1);
  }

  int n = atoi(argv[1]);
  pthread_t tids[n];

  for(int i=0; i<n; i++)
    pthread_create(&tids[i], NULL, slave, NULL);

  master();

  for(int i=0; i<n; i++) {
    void* ret;
    pthread_join(tids[i], &ret);
  }

  return 0;
}
