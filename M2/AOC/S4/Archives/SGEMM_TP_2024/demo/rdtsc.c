#include <stdint.h>

#ifdef __i386
uint64_t rdtsc() {
   uint64_t x;
   __asm__ volatile ("rdtsc" : "=A" (x));
   return x;
}
#elif defined __amd64
uint64_t rdtsc() {
   uint64_t a, d;
   __asm__ volatile ("rdtsc" : "=a" (a), "=d" (d));
   return (d<<32) | a;
}
#endif
