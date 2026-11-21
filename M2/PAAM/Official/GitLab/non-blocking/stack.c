#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <pthread.h>
#include <stdbool.h>

#define asm_pause()

struct node {
  struct node* _Atomic next;
  int value;
};

struct stack {
  struct node* _Atomic head;
};

struct state {
}* states;

bool _Atomic go = false;
struct stack* stack;
unsigned int ne;

double gettime() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec*1e0 + ts.tv_nsec*1e-9;
}

void push(struct stack* stack, int value) {
  struct node* node = malloc(sizeof(*node));
  struct node* expected;

  node->value = value;
  
  do {
    expected = atomic_load(&stack->head);
    node->next = expected;
  } while(!atomic_compare_exchange_strong(&stack->head, &expected, node));
}

int pop(struct stack* stack) {
  struct node* expected;

  do {
    expected = atomic_load(&stack->head);
  } while(!atomic_compare_exchange_strong(&stack->head, &expected, expected->next));

  int res = expected->value;

  free(expected);

  return res;
}

void* push_pop(void* _arg) {
  while(!atomic_load(&go))
    asm_pause();

  for(unsigned int i=0; i<ne; i++)
    push(stack, i);
  
  for(unsigned int i=0; i<ne; i++)
    pop(stack);
  
  return NULL;
}

int main(int argc, char** argv) {
  if(argc != 3) {
    fprintf(stderr, "Usage: %s nb-threads nb-elements\n", argv[0]);
    return 1;
  }
  
  unsigned int nt = atoi(argv[1]);
  ne = atoi(argv[2]);
  pthread_t tids[nt];

  stack = calloc(sizeof(*stack), 1);
  states = calloc(sizeof(*states), nt);
  
  for(unsigned int i=0; i<nt; i++) {
    pthread_create(&tids[i], NULL, push_pop, &states[i]);
  }

  printf("Running with %u threads and %u elements\n", nt, ne);
  
  double start = gettime();

  atomic_store(&go, true);

  for(unsigned int i=0; i<nt; i++)
    pthread_join(tids[i], NULL);

  double end = gettime();
  
  printf("Elapsed: %lfs (head: %p)\n", end - start, stack->head);

  return 0;
}
