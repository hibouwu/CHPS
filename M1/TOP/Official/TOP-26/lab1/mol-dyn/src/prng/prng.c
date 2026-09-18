#include <prng/prng.h>

#include <assert.h>
#include <stdint.h>

static int64_t const MULTIPLIER = 1366;
static int64_t const ADDEND     = 150889;
static int64_t const PMOD       = 714025;
static double const FPMOD       = (double)PMOD;

static int64_t prng_last = 0;
static double prng_lo, prng_hi;

void prng_seed(double lo_bound, double hi_bound) {
  assert(lo_bound < hi_bound);
  prng_lo   = lo_bound;
  prng_hi   = hi_bound;
  prng_last = PMOD / ADDEND; // just pick something
}

double prng_random() {
  // Compute an integer random number from zero to mod
  int64_t prng_next = (MULTIPLIER * prng_last + ADDEND) % PMOD;
  prng_last         = prng_next;

  // Shift into preset range and return
  return ((double)prng_next / FPMOD) * (double)((prng_hi - prng_lo) + prng_lo);
}
