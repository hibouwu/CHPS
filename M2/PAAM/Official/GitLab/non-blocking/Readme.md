# Non-blocking algorithms

## Exercice I: The lock-free queue

### Question 1
Write a `main` function that creates $N$ threads, where $N$ is a parameter of the application. The `main` function has to wait for the termination of the threads before exiting.

### Question 2
Implement a queue of integers protected by a `pthread_mutex_lock` (`enqueue` and `dequeue` functions). Modify your application in order to enqueue $K$ nodes and then dequeue $K$ nodes in each thread, where $K$ is a parameter of the application. Run the application with $N = 10$ and $K = 1,000,000$ and verify that the queue is empty at the end of the run.

### Question 3
Implement a lock-free queue of integers by using the algorithm presented during the lecture. Don't forget to identify the atomic operations and to use the adequate C constructs. Run the application with $N = 10$ and $K = 1,000,000$ and verify that the lock-free queue is also empty at the end of the run.

> **Note:** For the moment, don't try to free the nodes when they are removed from the queue. You will see that freeing the nodes complicates the algorithm later.

> **Note:** In order to simplify debugging, you can add a function to print the state of the queue.

### Question 4
By using `clock_gettime` in `CLOCK_MONOTONIC` mode, identify which implementation (lock-free or protected by a `pthread_mutex_lock`) gives the best result.

### Question 5
Now, try to free a node in the lock-free queue implementation of `dequeue`. If your code is correct, the application should crash lamentably with a segmentation fault. Try to understand why by taking a look at [the ABA problem](https://en.wikipedia.org/wiki/ABA_problem). When you think that you understand, check with your professor that your explanation is correct.

### Question 6: Optional and difficult

In order to avoid the ABA problem, we have to ensure that a node $A$ is not reallocated when a thread uses it. For that purpose, we will use hazard pointers (Maged Michael, "Hazard Pointers: Safe Memory Reclamation for Lock-Free Objects", TPDS 2004).

At a high level, when a thread reads a pointer $X$ from a location $L$ and wants to perform a CAS to change the value of $L$ from $X$ to another value, it has to ensure that $X$ cannot be reallocated between the read and the CAS. For that purpose, the thread registers $X$ in a thread-local variable called `hazard` while it uses $X$, and the algorithm has to ensure that $X$ cannot be freed if one of the hazard variables points to $X$.

With the queue, when a thread reads the pointer $X$ in `head` in `dequeue`, it writes $X$ in `hazard`. Then, it re-reads `head`, and if `head` is not equal to $X$, it restarts from the beginning. Finally, if the compare-and-swap succeeds, instead of freeing the node, the thread writes `0` in its hazard pointer and adds $X$ to a lock-free stack called `free_nodes`.

Similarly, in `enqueue`, the thread also has to ensure that `tail` is not freed during one of the operations that modify `tail`. For this reason, when the thread reads `tail`, it saves its value in its hazard pointer, re-reads `tail` in order to ensure that it was not yet potentially freed, and writes `0` in its hazard location after the CAS.

Finally, in `enqueue`, to allocate a node, a thread must first try to allocate the node from `free_nodes` before allocating a new node with `malloc`. In detail:

- The thread pops (with a lock-free algorithm) a pointer $Z$ from the `free_nodes` stack.
- If $Z$ is null (i.e., the stack is empty), the thread allocates a node with `malloc`.
- Otherwise:
  - If the thread finds the $Z$ pointer in one of the hazard variables of the other threads, it means that $Z$ is still used by another thread. In this case, it has to re-push $Z$ and use `malloc` to allocate a new node.
  - Otherwise, the node is free and no longer used; the thread can directly reuse it to enqueue a new value without calling `malloc`.

As an additional question: why can a node not appear twice in the `free_nodes` stack?

## Exercice II: The radix tree

Try to implement a lock-free version of a radix tree. You can find a description of a radix tree [here](https://en.wikipedia.org/wiki/Radix_tree). In this exercise, consider that you cannot remove elements from the radix tree.

## Exercice III: The linked list

Restart the first exercise, but by considering a linked list and without trying to free the nodes. If you still have time and were able to implement hazard pointers for the queue, you can try to use hazard pointers to handle the ABA problem for linked lists (this question is difficult).

---

## Solution
* [stack.c](stack.c)