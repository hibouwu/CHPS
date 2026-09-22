#include <sys/types.h>

#define NB_CELLS 65536

struct cell {
  uintptr_t value;
  size_t    counter;
};

struct memory {
  struct cell* cells[NB_CELLS];
  size_t       clock;
};

