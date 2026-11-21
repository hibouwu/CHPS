# Threads and Synchronization

## Exercise I: My First Threads

### Question 1

Write a C application that creates $N$ threads using `pthread_create`, where $N$ is the first argument passed to the application.
Each thread must write `"[tid] Hello, World i!!!"` to the terminal, where:
* `tid` is the thread identifier returned by `pthread_self`,
* `i` is a number incremented by `main` for each thread (0 for the first thread, 1 for the second, and so on).

### Question 2

The `main` function must now print `Main quitting` at the end of the function. Run your application several times with 3 threads. Why does the application sometimes write "Main quitting" before the three "Hello, World" messages?

### Question 3

Start your application several times with 20 threads. Why does the application often print "Hello, World" fewer than 20 times?

### Question 4

Add a call to `pthread_exit` at the end of `main`. Why does the application now systematically write "Hello, World" 20 times when you start it with 20 threads?

### Question 5

Ensure now that the application writes "Main quitting" after all the "Hello, World" messages.

---

## Exercise II: A Shared Counter

### Question 1
First, add a global variable called `counter`, initialized to 0, to your application.
Then, ensure that each thread increments this variable after printing its "Hello, World" message.
Finally, modify the application to print the value of `counter` before calling `pthread_exit` in `main`.

When you run your application with 100 threads, why is the printed counter value often smaller than 100? Modify your application to ensure that the counter equals the number of threads at the end of execution.


### Question 2
Modify your application to print "Main quitting" only when the counter is equal to the number of threads.

---

## Exercise III: Producer/Consumer

In this exercise, we want to implement a producer/consumer model.
Specifically, the main thread (referred to as the *producer*) reads lines from the standard input and pushes them into a queue.
The other threads (referred to as *consumers*) take these lines from the queue in FIFO (First-In, First-Out) order and print them.

We want to implement the queue as a linked list. The first node of the list is the oldest enqueued line (first in), while the last node is the newest enqueued line (last in).
To avoid traversing the entire linked list to enqueue a new node, keep pointers to both the first and last nodes.

### Question 1
First, implement a unicast queue: only a single consumer processes messages from the queue. Ensure that a consumer thread sleeps using `pthread_cond_wait` when the queue is empty. Do not forget to free a node of the linked list after it is consumed.

### Question 2 (optional, 1/2)

Modify your application to implement a multicast queue: each consumer must receive and print every line (in FIFO order).
In this step, also ensure you free the nodes of the linked list.

### Question 3 (optional, 2/2)

With the broadcast mechanism in place, try to ensure that each consumer can consume a node even if the previous nodes in the list are not consumers, fully desynchronizing the consumers (in your initial version, all consumers likely consumed a node before moving on together to the next).

---

## Solutions

* Exercice I:
  * [hello.c](hello.c)
* Exercice III:
  * Question 1:
    * [Makefile](Makefile)
    * [spsc.c](spsc.c)
  * Question 3:
    * [mpmc.c](mpmc.c)

