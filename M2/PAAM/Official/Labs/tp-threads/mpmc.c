#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX_LENGTH 256
#define xstr(s) str(s)
#define str(s) #s

struct node {
  char msg[MAX_LENGTH];
  struct node* next;
  size_t cpt;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
};

struct thread_arg {
  struct node* fake;
  size_t id;
};

struct node* new_node(size_t n) {
  struct node* node = malloc(sizeof(*node));
  
  node->next = NULL;
  node->cpt = n;
  pthread_mutex_init(&node->mutex, NULL);
  pthread_cond_init(&node->cond, NULL);

  return node;
}

struct thread_arg* new_arg(size_t id, struct node* fake) {
  struct thread_arg* arg = malloc(sizeof(*arg));

  arg->fake = fake;
  arg->id = id;
  
  return arg;
}

void* consumer(void* _arg) {
  struct thread_arg* arg = _arg;
  struct node* cons = arg->fake;
  size_t id = arg->id;

  free(arg);

  for(;;) {
    bool was_free = false;
    
    pthread_mutex_lock(&cons->mutex);
    while(cons->next == NULL)
      pthread_cond_wait(&cons->cond, &cons->mutex);
    char buf[MAX_LENGTH];
    strncpy(buf, cons->msg, MAX_LENGTH);
    struct node* tmp = cons->next;
    if(--cons->cpt == 0) {
      was_free = true;
      free(cons);
    }
    pthread_mutex_unlock(&cons->mutex);

    cons = tmp;

    if(strncmp(buf, "exit", MAX_LENGTH) == 0) {
      printf("===== [%zu] exiting ======\n", id);
      pthread_exit(NULL);
    } else {
      printf("[%zu] receive: %s%s\n", id, buf, was_free ? " (free the node)" : "");
      // simulate different speeds, consummer i is faster than consummer i+1
      //usleep((id-1)*100000);
    }
  }
}

// here, the thread_arg is just here if we want to test with multiple producers
void producer(struct thread_arg* _arg) {
  struct thread_arg* arg = _arg;
  struct node* prod = arg->fake;
  size_t id = arg->id;

  free(arg);

  char* poeme[] =
    {
      "Avec", "ses", "quatre", "dromadaires",
      "Don", "Pedro", "d’Alfaroubeira",
      "courut", "le", "monde", "et", "l’admira",
      "il", "fit", "ce", "que", "je", "voudrais", "faire",
      "si", "j’avais", "quatre", "dromadaires",
      "exit"
    };
  size_t i = 0;
  
  for(;;) {
    //char msg[MAX_LENGTH];
    //scanf("%"xstr(MAX_LENGTH)"s", msg);
    char* msg = poeme[i++];
    
    struct node* next = new_node(prod->cpt);

    pthread_mutex_lock(&prod->mutex);
    printf("[%zu] produce: %s\n", id, msg);
    prod->next = next;
    strncpy(prod->msg, msg, MAX_LENGTH);
    pthread_cond_broadcast(&prod->cond);
    pthread_mutex_unlock(&prod->mutex);

    if(strncmp(msg, "exit", MAX_LENGTH) == 0)
      return;

    prod = next;
  }
}

int main(int argc, char** argv) {
  if(argc != 2) {
    fprintf(stderr, "Usage: %s nb-threads\n", argv[0]);
    exit(1);
  }

  int n = atoi(argv[1]);
  pthread_t tids[n];

  struct node* list = new_node(n);
  
  for(int i=0; i<n; i++)
    pthread_create(tids + i, NULL, consumer, new_arg(i + 1, list)); // 1...n are the consummers

  producer(new_arg(0, list)); // 0 is the producer
  
  for(int i=0; i<n; i++) {
    void* retval;
    pthread_join(tids[i], &retval);
  }

  printf("Main quitting\n");
  
  return 0;
}
