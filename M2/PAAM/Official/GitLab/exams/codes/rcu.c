// https://concurrencyfreaks.blogspot.com/2016/09/a-simple-userspace-rcu-in-java.html
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#include <unistd.h>

#define N 10
#define M 100

struct thread {
  pthread_t tid;
  _Atomic int is_reader;
} threads[N];

_Thread_local struct thread* self;

_Atomic size_t nb_deleted = 0;
_Atomic size_t nb_visited = 0;

void rcu_read_lock() {
  atomic_store(&self->is_reader, 1);
}

void rcu_read_unlock() {
  atomic_store(&self->is_reader, 0);
}

void synchronize_rcu() {
  for(size_t i=0; i<N; i++)
    while(atomic_load(&threads[i].is_reader)) {
    }
}

struct node {
  struct node* _Atomic next;
  int value;
}* _Atomic head;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* worker(void* addr) {
  self = addr;
  
  for(size_t i=0; i<M; i++) {
    atomic_fetch_add(&nb_visited, 1);
    
    if(rand() % N) {
      rcu_read_lock();
      for(struct node* cur=head; cur; cur=cur->next) {
      }
      rcu_read_unlock();
    } else {
      pthread_mutex_lock(&lock);
      rcu_read_lock();

      struct node* cur = head;
      struct node* deleted = NULL;
      
      while(cur) {
        if(!deleted && !(rand() % 10) && cur->next) {
          deleted = cur->next;
          cur->next = deleted->next;
        }
        
        cur = cur->next;
      }

      rcu_read_unlock();
      pthread_mutex_unlock(&lock);
      
      synchronize_rcu();
      
      if(deleted) {
        atomic_fetch_add(&nb_deleted, 1);
        free(deleted);
      }
    }
  }
  
  return NULL;
}

int main(int argc, char* argv[]) {
  srand(getpid());
  
  for(size_t i=0; i<M; i++) {
    struct node* node = malloc(sizeof(*node));
    node->value = M - i;
    node->next = head;
    head = node;
  }
  
  for(size_t i=0; i<N; i++) {
    threads[i].is_reader = 0;
    pthread_create(&threads[i].tid, NULL, worker, &threads[i]);
  }

  for(size_t i=0; i<N; i++) {
    void* retval;
    pthread_join(threads[i].tid, &retval);
  }

  size_t total = 0;
  for(struct node* cur=head; cur; cur=cur->next) {
    printf("%d\n", cur->value);
    total ++;
  }

  printf("nb visited: %zu\nnb deleted: %zu\nnb total %zu\n", nb_visited, nb_deleted, nb_deleted + total);
  
  return 0;
}
