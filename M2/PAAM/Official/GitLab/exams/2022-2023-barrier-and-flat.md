# CSC5101 – Exam 2022-2023

**Duration: 2 hours, any document allowed.**

## The barrier (11 points, easy/medium)

The goal of this exercise is to implement a barrier.
A barrier is an object that allows `N` threads to synchronize.
Technically, a barrier mainly provides a `barrier_wait` method.
When a thread calls `barrier_wait`, if the number of threads having reached the barrier is strictly smaller than `N`, the thread waits.
When the `N`<sup>th</sup> thread calls `barrier_wait`, all the threads are unblocked.

A barrier is represented by a `struct barrier`. In this exercise, you must implement the following functions:

- `void barrier_init(struct barrier* b, int n)`: initializes the barrier to `n`, where `n` is the number of participating threads,
- `void barrier_wait(struct barrier* b)`: joins the barrier.

### Question 1 (2 points, easy)

Write a program that:

- Takes `n` as an argument, where `n` is the number of threads to create.
- Starts `n` threads. Each thread must wait for the `n` threads on a barrier before terminating.
- Terminates the program once the `n` threads have terminated.

### Question 2 (3.5 points, easy)

First, we want to implement the barrier using POSIX locks and condition variables.
Give the definition of `struct barrier` and the code for `barrier_init` and `barrier_wait`.
A thread must sleep while waiting for the other threads.

### Question 3 (2 points, easy)

We now want to implement the barrier using only atomic operations.
Give the new definition of `struct barrier` and the code for `barrier_init` and `barrier_wait`.
A thread must busy-wait or sleep while waiting for the other threads.

### Question 4 (2 points, medium)

In our previous implementation, a thread uselessly uses the processor while waiting for the other threads.
We want to improve this behavior by using a futex so that a thread sleeps while waiting.
Give the new definition of `struct barrier` and the code for `barrier_init` and `barrier_wait`.
To use a futex, assume that you can use the following functions:

- `futex_wait(int* ptr, int value)`: the thread sleeps if and only if `*ptr` is equal to `value`. This function is executed atomically.
- `futex_wake(int* ptr, int n)`: wakes up `n` threads waiting on the `ptr` address. This function is executed atomically.

### Question 5 (1.5 points, easy)

Finally, we want to implement a barrier using transactional memory.
Give the new definition of `struct barrier` and the code for `barrier_init` and `barrier_wait`.

---

## Course Questions (2 points, easy)

### Question 1 (1 point)

Why is the Intel's `sfence` (store fence) instruction sufficient to implement the abstract `pfence` instruction?

### Question 2 (1 point)

Why is the Intel's `sfence` (store fence) instruction sufficient to implement the abstract `psync` instruction?

---

## Flat combining (7 points, difficult/very difficult)

In this exercise, our goal is to adapt the MCS lock algorithm to transform it into a so-called flat combining algorithm.
The following code recalls how the MCS algorithm is implemented.
Compared to the lecture notes, the code has been slightly adapted:
First, the condition `isFree` has been inverted and is now `is_busy`.
Second, instead of having one function to acquire the lock and another to release it, the code contains a single function named `execute_in_cs`.
This function takes a pointer to a job function (type `job_t`) as an argument.
The `execute_in_cs` function acquires the lock, executes the job, and releases the lock.

```c
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
```

With the flat combining algorithm, when a thread acquires the lock, we say that it becomes a *combiner*.
In this case, instead of executing only its own job, it also executes the next jobs in the queue.
At a high level, the algorithm becomes:

- Try to acquire the lock,
- If the lock is taken, wait until a combiner has executed its job,
- Otherwise

---

## Solution

* [barrier.c](codes/barrier.c)
* [flat.c](codes/flat.c)

