#ifndef _NVMM_H_
#define _NVMM_H_

// note: compile with the option -march=native

#include <stdbool.h>

#if defined(__CLWB__)
//#pragma message "Using clwb as pwb implementation"
static void pwb(void *p) { asm volatile("clwb (%0)\n\t" : : "r"(p) : "memory"); }
static void pfence()     { asm volatile("sfence" ::: "memory"); }
static void psync()      { asm volatile("sfence" ::: "memory"); }
#elif defined(__CLFLUSHOPT__)
//#pragma message "Using clflushopt as pwb implementation"
static void pwb(void *p) { asm volatile("clflushopt (%0)\n\t" : : "r"(p) : "memory"); }
static void pfence()     { asm volatile("sfence" ::: "memory"); }
static void psync()      { asm volatile("sfence" ::: "memory"); }
#else
//#pragma message "Using default clflush as pwb implementation, try to compile with -march=native"
static void pwb(void *p) { asm volatile("clflush (%0)\n\t" : : "r"(p) : "memory"); }
static void pfence()     { asm volatile("" ::: "memory"); }
static void psync()      { asm volatile("" ::: "memory"); }
#endif

//
// Intel-specific optimization for Intel processors
//
// An Intel processor executes speculativly the instructions. When we spinloop on a boolean, it means that the processor
// will execute many load in advance, and suppose that the load returns false (we are in the spinloop while the condition is false).
//
// When the condition becomes true, the processor has to abort the execution of the speculative loads, which significantly slows
// down the execution of the load when the condition becomes true, and thus hampers reactivity when the condition becomes true.
static bool asm_pause() { asm volatile("pause"); return true; }

#if defined(__HAS_NVMM__)

// If we actually have a NVMM, use the standard flags that allows Linux to directly mmap the PMEM in the virtual address space.
// These flags only work for a DAX file system
#define MMAP_NVMM_FLAGS  (MAP_SHARED_VALIDATE | MAP_SYNC)

#else

// If we don't have a NVMM, we simulate a NVMM by just using a volatile memory region.
// In this case, we have to mmap it with this flag since a volatile memory region is not a DAX file system.
#define MMAP_NVMM_FLAGS  MAP_SHARED

#endif

#endif
