#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/futex.h>
#include <time.h>
#include <stdio.h>
#include "futexlock.h"

long futex(void *addr1, int op, int val1, struct timespec *timeout,
           void *addr2, int val3) {
  return syscall(SYS_futex, addr1, op, val1, timeout, addr2, val3);
}

void futex_wait(void* addr, int val) {
  futex(addr, FUTEX_WAIT, val, NULL, NULL, 0); /* wait if *addr == val */
}

void futex_wake(void* addr, int nb_threads) {
  futex(addr, FUTEX_WAKE, nb_threads, NULL, NULL, 0);
}

void futex_lock(futex_lock_t* lock) {
  uint64_t expected = FREE;

  if(!atomic_compare_exchange_strong(&lock->state, &expected, BUSY_NO_WAITER)) {
  restart:
    if(expected == BUSY_WITH_WAITERS || atomic_compare_exchange_strong(&lock->state, &expected, BUSY_WITH_WAITERS))
      futex_wait(&lock->state, BUSY_WITH_WAITERS);
    
    expected = FREE;
    if(!atomic_compare_exchange_strong(&lock->state, &expected, BUSY_WITH_WAITERS)) /* take the lock and we don't know if we have waiters */
      goto restart;
  }
}

void futex_unlock(futex_lock_t* lock) {
  uint64_t expected = BUSY_NO_WAITER;

  if(!atomic_compare_exchange_strong(&lock->state, &expected, FREE)) {
    /* I have waiters */
    atomic_store(&lock->state, FREE);
    futex_wake(&lock->state, 1);
  }
}

