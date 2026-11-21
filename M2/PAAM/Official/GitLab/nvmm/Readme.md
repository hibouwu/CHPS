# Non volatile main memory

This exercise has the goal of implementing a write cache in non-volatile memory in order to boost I/O performance. The code that you will implement is incomplete because it cannot handle reads. You can find the full algorithm in the "[NVCache: A Plug-and-Play NVMM-based I/O Booster for Legacy Systems](https://pages.saclay.inria.fr/gael.thomas/research/biblio/2021/dulong-dsn-nvcache.pdf)" paper published by Rémi Dulong et al. at DSN'21.

At a high level, we will implement the `int my_pwrite(int fd, const void* buf, size_t n, off_t off)` function. This function behaves like the classical `pwrite` function: it writes `n` bytes from `buf` to the file `fd` at offset `off`. However, instead of writing the buffer directly to the file `fd`, `my_pwrite` will add the write operation to a log stored in NVMM. Asynchronously, a thread—called the cleanup thread—will take operations from the log and use the standard `pwrite` function to propagate them to the disk.

## Question 1

Since you probably don't have NVMM hardware, we will simulate NVMM by mapping a persistent file in memory. Write an application that creates a 128-megabyte file named `nvmm.dat`, maps this file into memory, and increments its first byte. Check that the first byte is actually incremented each time you run your application by executing `hexdump -C nvmm.dat`.

> **Remarque :** Don't forget to check the return codes of the `open`, `ftruncate`, and `mmap` functions.

> **Remarque :** Since you are using a regular file rather than actual NVMM, simply replace the `MAP_SHARED_VALIDATE | MAP_SYNC` flags with `MAP_SHARED`.

## Question 2

In order to use NVMM instructions (`pwb`, `pfence`, and `psync`), you first need to compile with the `-march=native` option in GCC.
Then, download and include the following file: [nvmm.h](nvmm.h).

## Question 3

Add a `my_pwrite` function. For now, `my_pwrite` simply needs to call the standard `pwrite` function. In the `main` function, add code that writes "hello" 1024 times at offsets 0, 5, etc., in the file `out.dat`, and check that your application behaves correctly by inspecting `out.dat` with `hexdump -C out.dat`.

## Question 4

At this step, we define the main structures and variables. For this purpose, download and include this file: [struct.h](struct.h).

The `struct operation` describes a write operation. Specifically, a `struct operation` spans two cache lines (the first one defined with a union, the second being the `buf` field). In the first cache line, we store the metadata associated with the write:

* `commit` is true if the entry contains a write operation,
* `fd`, `n`, and `off` describe the operation.

In the second cache line, we store the buffer to be written.

The NVMM consists of a log (`struct nvmm`). In this log, we find:

* An array of operations (`operation`),
* A tail index (`tail`), which indicates where the least recently added operation is located.

Finally, in volatile memory, you have:

* A pointer to the NVMM (`nvmm`),
* A volatile head index (`head`) where new operations are added.

## Question 5

Now that we have the main structures and variables, we can implement our booster. In `my_pwrite`, you need to add new operations at `head`. If `head + 1` equals `tail`, it means the log is full. In this case, `my_pwrite` must wait.

In addition to the `my_pwrite` function, you must also implement the cleanup thread. This thread inspects the `commit` flag of the operation at `tail`. When the commit flag becomes true, the cleanup thread must call the standard `pwrite` function to propagate the write to disk. Then, the cleanup thread calls `fsync` to ensure the data is actually written to disk. Finally, once `fsync` returns, the entry in the log is no longer needed. The cleanup thread can thus increment `tail` and flush it to NVMM.

> **Remarque :** You should treat the log as a circular buffer.

## Question 6

Using `clock_gettime` in `CLOCK_MONOTONIC` mode, compare the performance of:

* A simple call to `pwrite`,
* A call to `pwrite` followed by a call to `fsync` to ensure durability,
* A call to `my_pwrite`.

## Question 7

Now, we want to handle crashes. In case of a crash, when your application recovers, it must apply the latest writes from the log. Specifically, the recovery procedure must inspect all operations starting at `tail` and apply all committed operations. To keep things simple, since the old file descriptor is invalid after a crash, you may assume that `fd` always corresponds to the file `out.dat`.

## Question 8: Batching

If the log contains multiple entries, calling `fsync` for every single write in the cleanup thread is inefficient. Modify your code to call `fsync` only once when propagating multiple entries.

## Question 9: Optional

Because of batching, our application contains a minor bug. Imagine that the log is full—that is, `head + 1` is equal to `tail`. If the cleanup thread consumes two entries, it will add 2 to `tail`. At this point, the main thread can create two new entries: `e1` and `e2`. Unfortunately, a crash might occur while the two new entries are being written to NVMM, but before the updated `tail` index is persisted.

During recovery, the cleanup thread would consider `e2` to be the oldest write (`e1` is at `head`, which is just before `tail`, while `e2` is at `tail`). If `e2` and another entry `e0` in the log target the same offset, `e0` would overwrite `e2`'s write, which is incorrect: `e2` is the most recent write and should overwrite `e0`.

To fix this issue, you should use two `tail` variables:

* A `persistent_tail` stored in NVMM, used by the cleanup thread and during recovery.
* A `volatile_tail` stored in volatile memory, incremented only after the update to `persistent_tail` in the cleanup thread has actually been flushed to NVMM (e.g., using `pwb`/`pfence`).

If the main thread waits whenever `head + 1` equals `volatile_tail`, we ensure that the main thread can only start adding entries `e1` and `e2` once the persistent tail is consistent (pointing past `e2`), thus fixing the bug.

---

## Solution

* [Makefile](Makefile)
* [soluce.c](soluce.c)
