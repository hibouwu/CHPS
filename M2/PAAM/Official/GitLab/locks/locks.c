#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "futexlock.h"

#define asm_pause() asm volatile("pause")

uint32_t z = 0;

uint32_t n;
uint32_t it;
uint32_t csd;
uint32_t cd;

void (*ze_lock)();
void (*ze_unlock)();

/*
 *    spin lock
 */
int slock = 0;

void spin_lock() {
  while(atomic_exchange(&slock, 1)) { asm_pause(); }
}

void spin_unlock() {
  atomic_store(&slock, 0);
}

/*
 *    tocket lock
 */
struct {
  uint64_t _Atomic counter;
  uint64_t _Atomic screen;
} ticket = { 0, 0 };

void ticket_lock() {
  uint64_t my = atomic_fetch_add(&ticket.counter, 1);
  while(atomic_load(&ticket.screen) < my) { asm_pause(); }
}

void ticket_unlock() {
  atomic_fetch_add(&ticket.screen, 1);
}

/*
 *    MCS lock
 */
struct node { struct node* _Atomic next; bool _Atomic is_free; };
_Thread_local struct node my;
struct node* _Atomic lock = NULL;

void mcs_lock() {
  my.next = NULL;
  my.is_free = false;
  
  struct node* p = atomic_exchange(&lock, &my);
  if(p) {
    atomic_store(&p->next, &my);
    while(!atomic_load(&my.is_free)) { asm_pause(); }
  }
}

void mcs_unlock() {
  struct node* expected = &my;
  if(!atomic_load(&my.next) && 
     atomic_compare_exchange_strong(&lock, &expected, NULL))
    return;
  while(!atomic_load(&my.next)) { asm_pause(); }
  atomic_store(&my.next->is_free, true);
}

/*
 *   POSIX lock
 */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void posix_lock() {
  pthread_mutex_lock(&mutex);
}

void posix_unlock() {
  pthread_mutex_unlock(&mutex);
}

/*
 *   Home-made POSIX lock
 */
futex_lock_t flock;

void test_futex_lock() { futex_lock(&flock); }
void test_futex_unlock() { futex_unlock(&flock); }

/*
 *   Benchmark
 */ 

int _Atomic nb_started = 0;
struct {
  pthread_t  tid;
  double     elapsed;
}* stats;

double gettime() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec*1e0 + ts.tv_nsec*1e-9;
}

double delay(double from, uint32_t d) {
  if(d) {
    double res;

    do {
      res = gettime();
    } while(res < from + d*1e-9);

    return res;
  } else
    return from;
}

void* f(void* _arg) {
  uint32_t self = (uint32_t)(uintptr_t)_arg;
  atomic_fetch_add(&nb_started, 1);
  while(atomic_load(&nb_started) < n) { asm_pause(); }

  double start = gettime();
  double cur = start;
  
  for(int i=0; i<it; i++) {
    ze_lock();
    z++;
    cur = delay(cur, csd);
    ze_unlock();
    cur = delay(cur, cd);
  }
  
  stats[self].elapsed = gettime() - start;
  
  return 0;
}

int main(int argc, char** argv) {
  if(argc < 6) {
    fprintf(stderr, "Usage: %s nb-threads it csd cd algo\n", argv[0]);
    exit(1);
  }
  n = atoi(argv[1]);
  it = atoi(argv[2]);
  csd = atoi(argv[3]);
  cd = atoi(argv[4]);
  char* algo = argv[5];
  
  stats = calloc(n, sizeof(*stats));
  
  printf("=== test with %s lock ===\n", algo);
  if(strcmp(algo, "spinlock") == 0) {
    ze_lock = spin_lock;
    ze_unlock = spin_unlock;
  } else if(strcmp(algo, "ticket") == 0) {
    ze_lock = ticket_lock;
    ze_unlock = ticket_unlock;
  } else if(strcmp(algo, "mcs") == 0) {
    ze_lock = mcs_lock;
    ze_unlock = mcs_unlock;
  } else if(strcmp(algo, "posix") == 0) {
    ze_lock = posix_lock;
    ze_unlock = posix_unlock;
  } else if(strcmp(algo, "futex") == 0) {
    ze_lock = test_futex_lock;
    ze_unlock = test_futex_unlock;
  } else {
    fprintf(stderr, "unknow lock: %s\n", algo);
    exit(1);
  }
  
  for(int i=0; i<n; i++)
    pthread_create(&stats[i].tid, NULL, f, (void*)(uintptr_t)i);

  for(int i=0; i<n; i++) {
    void* retval;
    pthread_join(stats[i].tid, &retval);
  }

  double total = 0;
  for(int i=0; i<n; i++)
    total += stats[i].elapsed;

  double av = (total*1e9 / (n * it)) - cd;
  printf("Average: %0.0lf ns per loop (with a delay of %u ns => %0.0lf ns)\n", av, csd, av - csd);

  if(z != n * it)
    printf("Integrity check failed: %u for %u\n", z, n * it);

  return 0;
}
