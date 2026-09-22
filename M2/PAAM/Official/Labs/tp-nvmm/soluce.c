#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdatomic.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include "nvmm.h"
#include "struct.h"

struct nvmm*   nvmm;
_Atomic size_t head;
_Atomic size_t vtail;
_Atomic bool   stop;

size_t random_crash;

double gettime() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec*1e0 + ts.tv_nsec*1e-9;
}

void* get_nvmm(const char* path, size_t size) {
  int fd = open(path, O_RDWR | O_CREAT, 0644);
  assert(fd != -1);
  
  ftruncate(fd, size);
  
  char* res = mmap(NULL, sizeof(*nvmm), PROT_READ | PROT_WRITE, MMAP_NVMM_FLAGS, fd, 0);
  assert(res != MAP_FAILED);

  return res;
}

void* cleanup_thread(void* arg) {
  size_t tail = nvmm->tail;
  size_t cur_jobs = 0;    // current number of jobs since the last sync
  size_t max_jobs_per_sync = NB_ENTRIES / 2; // at most NB_ENTRIES / 2 jobs between two syncs
  size_t total_jobs = 0;  // statistics
  size_t total_syncs = 0; // statistics
  
  while(true) {
    struct operation* cur = &nvmm->operation[tail];

    if(atomic_load(&cur->committed) && cur_jobs < max_jobs_per_sync) {
      // the cleanup thread has to apply an operation
      if(random_crash) {
        if(!(rand() % random_crash)) {
          printf("---- random crashed (%zu) after %zu syncs, %zu + %zu propagated operations, have a nice day!----\n",
                 random_crash, total_syncs, total_jobs, cur_jobs);
          exit(0);
        }
      }
    
      //printf("proceed %zu\n", tail);
      pwrite(cur->fd, cur->buf, cur->n, cur->off);
      fsync(cur->fd);
      cur->committed = false;
      pwb(&cur->first_cache_line);
      pfence();
      
      tail = (tail + 1) % NB_ENTRIES;

      cur_jobs ++;             // a sync is required
    } else if(cur_jobs) {
      //printf("--- sync ---\n");
      total_jobs += cur_jobs;  // statistics
      total_syncs ++;          // statistics
      cur_jobs = 0;            // sync is no longer required
      
      nvmm->tail = tail;       // advance tail, the max_jobs_per_sync operation are applied
      pwb(&nvmm->tail);        
      psync();                 // ensures that the tail is actually written to PMEM

      atomic_store(&vtail, tail); // and then makes the tail visible to the other threads
    } else if(atomic_load(&stop)) {
      printf("[cleanup] Stats: %zu jobs and %zu syncs\n", total_jobs, total_syncs);
      return NULL;
    } else
      asm_pause();
  }
}

int my_pwrite(int fd, const void* buf, size_t n, off_t off) {
  size_t index;
  size_t next_index;

  // check whether the operation buffer is full
  // here we use vtail because, if we use tail instead, we could have this execution:
  //   - cleanup thread propagate operations
  //   - advance nvmm->tail, but pwb/psync are not yet executed
  //   - this thread adds a new operation op_last since the thread observes that tail lets a room between head and tail
  //   - crash while nvmm->tail not yet propagated to PMEM
  //   - at recover, we will apply op_last since nvmm->operation[nvmm->tail] contains op_last
  //     this is an error! op_last should be applied after all the other pending operations, not before
  //     the problem is that at recovery, the runtime "think" that the operations that was at the location of op_last is not yet applied
  do {
    index = atomic_load(&head);
    next_index = (index + 1) % NB_ENTRIES;
  } while((atomic_load(&vtail) == next_index || !atomic_compare_exchange_strong(&head, &index, next_index)) && asm_pause());

  struct operation* cur = &nvmm->operation[index];

  memcpy(cur->buf, buf, n < CACHE_LINE ? n : CACHE_LINE);
  pwb(cur->second_cache_line);
  
  cur->fd = fd;
  cur->n = n;
  cur->off = off;

  pwb(&cur->first_cache_line); // write back fd, n and off
  pfence();                    // ensures fd, n and off reaches NVMM before committed

  atomic_store(&cur->committed, true);
  
  pwb(&cur->first_cache_line); // write back committed
  pfence();                    // ensures that after a call to my_pwrite, buf is persisted
  
  return 0;
}

void recovery(int fd) {
  size_t total_jobs = 0;
  
  for(size_t i=0; i<NB_ENTRIES; i++) {
    struct operation* op = &nvmm->operation[(nvmm->tail + i) % NB_ENTRIES];

    if(op->committed) {
      total_jobs ++;
      pwrite(fd, op->buf, op->n, op->off);
    }
  }

  if(total_jobs) {
    printf("[recovery]: Found %zu old jobs\n", total_jobs);
    fsync(fd);
    
    for(size_t i=0; i<NB_ENTRIES; i++) {
      nvmm->operation[i].committed = false;
      pwb(nvmm->operation[i].first_cache_line);
      pfence(); // ensure that in case of crash, we remove the oldest pwrite before the newer ones
    }
  }

  nvmm->tail = 0;
  pwb(&nvmm->tail);
  pfence();
}


int main(int argc, char** argv) {
  if(argc != 2) {
    fprintf(stderr, "%s N\n", argv[0]);
    fprintf(stderr, "   - if N = 0 => never crash\n");
    fprintf(stderr, "   - otherwise, crash with a probability of 1/N in the cleanup thread\n");
    exit(1);
  }

  random_crash = atoi(argv[1]);
  srand(time(NULL));
  
  nvmm = get_nvmm("nvmm.dat", sizeof(*nvmm));

  int fd = open("out.dat", O_RDWR | O_CREAT | O_TRUNC, 0644);
  assert(fd != -1);

  recovery(fd);
    
  pthread_t tid;
  pthread_create(&tid, NULL, cleanup_thread, NULL);

  size_t nb_ops = 65536;
  double start = gettime();
  
  for(size_t i=0; i<nb_ops; i++) {
    char buf[] = "hello";
    size_t length = strlen(buf);
    my_pwrite(fd, buf, length, (i*length) % (1024 * 5));
  }

  double end = gettime();

  atomic_store(&stop, true);
  void* retval;
  pthread_join(tid, &retval);

  printf("[main]: %f microseconds per operation\n", (end - start)*1e6 / nb_ops);

  return 0;
}
