#ifndef _FUTEX_LOCK_H_
#define _FUTEX_LOCK_H_

#include <stdbool.h>
#include <stdatomic.h>
#include <stdint.h>
#include <pthread.h>

enum {
      FREE = 0,                /* the lock is free */
      BUSY_NO_WAITER = 1,      /* the lock is BUSY and I don't have waiters => no futex_wake at the end of unlock */
      BUSY_WITH_WAITERS = 2    /* the lock is BUSY and I have waiters => futex_wake at the end of unlock */
};

typedef struct {
  uint64_t _Atomic state;
} futex_lock_t;

extern void futex_lock(futex_lock_t* lock);
extern void futex_unlock(futex_lock_t* lock);

#endif
