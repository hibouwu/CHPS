# TP – Transactional Memory

In this lab, we will implement a small runtime for a software transactional memory.

## Question 1

As usual, write a `main` function that creates $N$ threads, where $N$ is a parameter of the application. The `main` function has to wait for the termination of the threads before exiting.

## Question 2

We will consider the memory as an array of cells, where each cell contains both a value (an integer) and a counter. For this reason, you have to define the corresponding structures from `mem.h`.

We consider that the variable `x` is the variable at index 0 in the array of cells. In each thread, use this structure to increment the `x` variable `1024*1024` times using an atomic instruction. Check, at the end of the application, that `x` has a consistent value (`1024*1024` times the number of threads).

Don't forget to write an initialization function that allocates the cells and gives them an initial value (0 for the value and 0 for the counter).

## Question 3

Measure, using `clock_gettime` in `CLOCK_MONOTONIC` mode, the average time taken by the threads to execute the loop.

## Question 4

Now, add an argument to your application which will specify the algorithm used to protect the `x` variable. For this first version, the argument should be equal to `atomic`. If the protection algorithm is not equal to `atomic`, your application should terminate with an error.

## Question 5

Add a second version of the loop where you protect the `x` variable with a `pthread_mutex_lock`. Check that the application is slower.

## Question 6

Now, we will implement a third version that relies on a software transactional memory. You will have to use this API:

* `void startTX()`: starts a transaction.
* `uintptr_t read(int n)`: reads the value of the cell at index `n`. The `read` function can detect an abort. If this is the case, `read` has to return a reserved value (`MAX_INT` for example).
* `void write(int n, uintptr_t value)`: writes the value of the cell at index `n`.
* `bool commitTX()`: commits the transaction if possible, and aborts it otherwise. The function has to return `false` in case of an abort.

For the moment, just add the functions with empty code blocks. In order to test the transactional memory version, you can use this code:

```c
for(size_t i = 0; i < 1024 * 1024; i++) {
restart:
    startTX();
    int value = read(0); // read x
    if(value == MAX_INT)
        goto restart;
    write(0, value + 1); // write x + 1
    if(!commitTX())      // try to commit
        goto restart;    // in case of abort, restart
}
```

## Question 7

Complete the functions in order to implement the algorithm given during the [lecture](../cours/04-stm.pdf). For that purpose, you will have to define a thread-local structure to store the state of a transaction (`_Thread_local`).

At this step, don't try to free an old cell during a commit (recall that, in order to record a new value during a commit, you have to allocate a new cell with a new value and a new counter, and atomically change the pointer to the cell).

## Question 8 (Optional)

You can now try to recycle the memory of old cells during a commit. Technically, when a thread uses a cell (for example, when a thread reads a cell during a read operation), you cannot free it during a commit.

In order to know when you can free a cell, you can reuse the hazard pointer pattern presented in the previous lab.

---

## Solution
* [main.c](main.c)
