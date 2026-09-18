/**
 * @file no-tasks.c
 * @brief Does nothing.
 *
 * This is a test program for the ExPResSO library.
 *
 * This program does not expect any argument.
 */

#include "expresso.h"

/**
 * @fn int main(void)
 * @brief Main function.
 */
int main(void) {
  // Test without any task.
  expresso_initialize();
  expresso_wait();
  expresso_stats();
  expresso_finalize();
  return 0;
}
