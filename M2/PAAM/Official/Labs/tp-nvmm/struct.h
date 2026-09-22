#ifndef _STRUCT_H_
#define _STRUCT_H_

#include <stdbool.h>
#include <sys/types.h>

#define NB_ENTRIES (64*1024)
#define CACHE_LINE 64

struct operation {
  union {                // first cache line
    // the cache line can either be accessed through these fields...
    struct {
      _Atomic bool committed; // _Atomic because committed is accessed in parallel by both the main an cleanup threads
      int          fd;        // the cleanup thread has to write the n bytes of buf at the offset off of the file fd
      size_t       n;
      off_t        off;
    };
    // ...or by using the variable first_cache_line
    char           first_cache_line[CACHE_LINE];
  };
  union {                // second cache line
    // the cache line either can accessed as a buffer (the content of the written buffer)...
    char           buf[CACHE_LINE];
    // ...or by using the variable second_cache_line
    char           second_cache_line[CACHE_LINE];
  };
};  // note: we suppose that we call my_pwrite with buffers of at most 64 bytes

// the content stored in persistent memory (nvmm = non-volatile main memory == persistent memory)
struct nvmm {
  struct operation operation[NB_ENTRIES]; // a circular buffer of pending operations
  size_t           tail;                  // the cleanup thread applies the operations from tail
  // if nvmm->operations[nvmm->tail]->committed == false, it means that we don't have any operation to apply
};

extern struct nvmm*   nvmm; // pointer to NVMM
extern _Atomic size_t head; // where we add the entries in the log
                            // _Atomic because several threads may call my_pwrite in parallel

#endif
