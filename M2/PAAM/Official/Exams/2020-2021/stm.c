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
  for(;;) {
    struct node* node;

    /* 1.e: atomic bien placé: 40% (30% si system/free dans la transaction) */
    atomic {
      if(!jobs.head)
        retry;  /* 1.e: retry bien placé: 30% (retry en trop ou mal placé: 0%) */

      node = jobs.head;
      
      if(!strcmp(node->cmd, "quit\n"))
        return NULL;
    
      if(!node->next)
        jobs.tail = NULL;

      jobs.head = node->next;
    }
    
    system(node->cmd);
    free(node);
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

    /* 1.e: atomic bien placé: 40% */
    atomic {
      if(!jobs.head)
        jobs.head = node;
      else
        jobs.tail->next = node;
      jobs.tail = node;

      if(!strncmp(node->cmd, "quit\n", 256))
        return;
    }
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
