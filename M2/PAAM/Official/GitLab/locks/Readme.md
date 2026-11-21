# Lock algorithms

**Objective:** This lab aims to measure the performance of basic lock algorithms: the spinlock, the ticket lock, the MCS lock, and the POSIX lock.

## Question 1: Arguments

Start by writing an application that takes the following arguments:

* A number `n` of threads (an integer)
* A number `it` of iterations executed by each thread (an integer)
* A critical section delay `csd` (an integer)
* A compute delay `cd` (an integer)
* A lock algorithm `algo` (a character array / string)

## Question 2: The threads

Create the threads and wait for their termination in the `main` function. Each thread has to execute the function `benchmark`, which executes `it` iterations of a loop that:

* Takes a POSIX lock
* Waits `csd` nanoseconds
* Releases the POSIX lock
* Waits `cd` nanoseconds

In order to wait, you can use the `clock_gettime` function with `CLOCK_MONOTONIC` mode.

## Question 3: Reporting

At the end of the application, report the time taken to acquire and release a lock.

## Question 4: Lock algorithms

Instead of taking a POSIX lock, we want to specify the lock algorithm used in the application as an argument. We consider these algorithms to be valid options:

* `none`: Do not take a lock (used to verify that your application reports correct values)
* `posix`: Take a POSIX lock, as done in the previous question
* `spinlock`: Take a spinlock
* `ticket`: Take a ticket lock
* `mcs`: Take an MCS lock

Implementing at least one of the custom algorithms is mandatory (`spinlock`, `ticket`, or `mcs`). Implementing all three is recommended in order to compare them.

## Question 5: The POSIX lock implementation (optional)

Now, we want to implement our own POSIX lock. For that purpose, we have to use the [futex](https://man7.org/linux/man-pages/man2/futex.2.html) system call provided by the Linux kernel. A thread can call this function either to wait for a variable modification (a lock release) or to wake up threads waiting for a variable modification.

Since the `futex` API is not exposed by default in the standard library, you can copy and paste the following code into your application to gain access to the `futex` function:

`futex.c`

At a high level, `pthread_mutex_lock` should first try to atomically change the lock value from `FREE` to `BUSY`. If the lock is already taken, the thread should wait using a futex, which—unlike the previous algorithms—yields the processor. For that reason, we say that a POSIX lock *passively* waits for the lock, whereas the other algorithms *actively* wait (spin).

In `pthread_mutex_unlock`, if a thread is waiting for the lock, do not forget to use the `futex` function.

## Question 6: The POSIX cond implementation (optional)

By using the `futex` API, try to implement a condition variable.

---

## Solution
* [Makefile](Makefile)
* [locks.c](locks.c)
* [futexlock.h](futexlock.h)
* [futexlock.c](futexlock.c)
