#include <stdbool.h>
#include <stdatomic.h>

typedef void (*job_t)();

struct node {
  struct node* _Atomic next;
  bool _Atomic is_busy;
};

_Thread_local struct node my;
struct node* _Atomic lock = NULL;

void execute_in_cs(job_t job) {
  my.next = NULL;
  my.is_busy = true;
  
  struct node* p = atomic_exchange(&lock, &my);

  if(p) {
    atomic_store(&p->next, &my);
    while(atomic_load(&my.is_busy)) {
    }
  }

  job();

  struct node* expected = &my;

  if(atomic_compare_exchange_strong(&lock, &expected, NULL))
    return;
  while(!atomic_load(&my.next)) {
  }
  
  atomic_store(&my.next->is_busy, true);
}
