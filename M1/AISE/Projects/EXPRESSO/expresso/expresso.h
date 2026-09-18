#ifndef __EXPRESSO_H
#define __EXPRESSO_H

#include <stdlib.h>

/**
 * @brief Scheduling strategies for task distribution.
 */
typedef enum {
  /** Dynamic scheduling. */
  SCHEDULE_DYNAMIC,
  /** Static scheduling. */
  SCHEDULE_STATIC,
  /** Balanced scheduling. */
  SCHEDULE_BALANCED
} schedule_t;

/**
 * @brief Initialize the Expresso runtime.
 * @return 0 on success, non-zero on failure.
 */
int expresso_initialize();

/**
 * @brief Get the number of worker threads.
 * @return Worker thread count.
 */
size_t expresso_worker_count();

/**
 * @brief Get the current scheduling strategy.
 * @return Current schedule strategy.
 */
schedule_t expresso_schedule_get();

/**
 * @brief Set the scheduling strategy.
 * @param strategy Scheduling strategy to apply.
 */
void expresso_schedule_set(schedule_t);

/**
 * @brief Enqueue a task for execution.
 * @param fn Task function pointer.
 * @param arg Task argument passed to @p fn.
 * @return 0 on success, non-zero on failure.
 */
int expresso_task(void (*) (void *), void *);

/**
 * @brief Enqueue a weighted task for execution.
 * @param fn Task function pointer.
 * @param arg Task argument passed to @p fn.
 * @param weight Relative task weight for scheduling.
 * @return 0 on success, non-zero on failure.
 */
int expresso_weighted_task(void (*) (void *), void *, unsigned int);

/**
 * @brief Wait for all queued tasks to complete.
 * @return 0 on success, non-zero on failure.
 */
int expresso_wait();

/**
 * @brief Print runtime statistics.
 */
void expresso_stats();

/**
 * @brief Get wall-clock time since runtime start.
 * @return Elapsed wall time in seconds.
 */
double expresso_wall_time();

/**
 * @brief Finalize the Expresso runtime.
 * @return 0 on success, non-zero on failure.
 */
int expresso_finalize();

#endif
