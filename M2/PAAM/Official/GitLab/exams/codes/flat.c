#include <stdbool.h>
#include <stdatomic.h>

typedef void (*job_t)();

struct node {
  struct node* _Atomic next;
  job_t _Atomic job;
  int _Atomic is_combiner;
};

_Thread_local struct node my;
struct node* _Atomic lock = NULL;

void cs(job_t job) {
  my.next = NULL;
  my.job = job;
  my.is_combiner = 0;

  struct node* p = atomic_exchange(&lock, &my);

  if(p) {
    /* p != NULL => a combiner exists */
    p->next = &my;

    do {
      if(!atomic_load(&my.job)) /* my job was executed by a combiner */
        return;
    }
    while(!atomic_load(&my.is_combiner)); /* the combiner released the lock without executing my job */
  }

  /* execute my job */
  job();

  int n = 1; /* one job executed */
  struct node* cur = &my;
  struct node* expected;
  
 restart:
  /* if cur is the last, not combiner anymore and release the lock */
  expected = cur;
  if(atomic_compare_exchange_strong(&lock, &expected, NULL)) /* nobody behind cur */
    return; /* nobody else */

  /* a new thread tries to enqueue its node, but the node is not yet enqueued */
  while(!atomic_load(&cur->next)) { }

  /* ok, I'm done */
  if(n++ >= 256) {
    atomic_store(&cur->is_combiner, true);
    return;
  }
  
  cur = cur->next;
  cur->job();
  atomic_store(&cur->job, NULL);

  goto restart;
}
