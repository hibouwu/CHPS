/**
 * @file list.c
 * @brief Processes a linked list.
 *
 * This is a benchmark program for the ExPResSO library. It has a reference
 * sequential and a room for a parallel implementation using ExPResSO.
 *
 * This program accepts exactly one optional argument, i.e., the length of the
 * list to process (number of nodes in the linked list).
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "expresso.h"

/**
 * @var struct list
 * @brief Structure to modelize a linked list of integers.
 */
struct list {
  int value;
  struct list * next;
};

/**
 * @fn struct list * list_new(int value)
 * @brief Creates new linked list node initialized with @a value.
 * @returns Poiner to the newly allocated and initialized linked list node.
 */
struct list * list_new(int value) {
  struct list * new = malloc(sizeof(struct list));
  new->value = value; new->next = NULL;
  return new;
}

/**
 * @fn void list_free(struct list * list)
 * @brief Destructs the entire linked @a list.
 */
void list_free(struct list * list) {
  struct list * next;
  while (list != NULL) {
    next = list->next;
    free(list);
    list = next;
  }
}

/**
 * @fn struct list * list_init(int nb_nodes)
 * @brief Creates new linked list of @a nb_nodes nodes.
 * @returns Poiner to the newly allocated and initialized linked list.
 */
struct list * list_init(int nb_nodes) {
  struct list * list, * current;
  if(nb_nodes > 0) {
    list = current = list_new(1);
    for(int i = 1; i < nb_nodes; i++) {
      current->next = list_new(i+1);
      current = current->next;
    }
  }
  return list;
}

/**
 * @fn void list_print(struct list * list)
 * @brief Prints the nodes of the linked @a list.
 */
void list_print(struct list * list) {
  int i = 1;
  while(list != NULL) {
    printf("Node %2d: value = %d\n", i, list->value);
    list = list->next;
    i++;
  }
}

/**
 * @fn void list_process_node(struct list * node)
 * @brief Processes a linked list @a node.
 *
 * The processing amounts to sleeping for the number of seconds corresponding to
 * the node's value and to incrementing the node's value by one.
 */
void list_process_node(struct list * node) {
  if(node != NULL) {
    sleep(node->value);
    node->value++;
  }
}

/**
 * @fn int list_check(struct list * list1, struct list * list2)
 * @brief Checks the equality of two linked lists.
 *
 * Verifies whether @a list1 and @a list2 are the same.
 *
 * @returns 0 if @a list1 is the same as @a list2
 * @returns 1 otherwise
 */
int list_check(struct list * list1, struct list * list2) {
  while(list1 != NULL) {
    if(list1->value != list2->value)
      return 1;
    list1 = list1->next;
    list2 = list2->next;
  }
  if(list2)
    return 1;
  return 0;
}

/**
 * @fn int main(int argc, char ** argv)
 * @arg argc Number of command-line arguments (including the executable name).
 * @arg argv Values of command-line arguments (including the executable name).
 * @brief Main function.
 */
int main(int argc, char ** argv) {
  int size = 5;
  if(argc > 1) {
    size = atoi(argv[1]);
  }

  // Initialization with arbitrary values.
  struct list * reference = list_init(size);
  struct list * expresso = list_init(size);
  struct list * list;
  double time_reference = 0.0, time_expresso = 0.0;

  // Show lists before computation.
  printf("Reference list:\n");
  list_print(reference);
  printf(" ExPResSO list:\n");
  list_print(expresso);

  // Reference sequential implementation.
  time_reference = expresso_wall_time();
  list = reference;
  while(list != NULL) {
    list_process_node(list);
    list = list->next;
  }
  time_reference = expresso_wall_time() - time_reference;

  // Parallel implementation using ExPResSO.
  expresso_initialize();
  time_expresso = expresso_wall_time();

  list = expresso;
  while(list != NULL) {
    expresso_weighted_task((void (*)(void *))list_process_node, list, (unsigned int)list->value);
    list = list->next;
  }
  expresso_wait();

  time_expresso = expresso_wall_time() - time_expresso;
  
  expresso_stats();
  expresso_finalize();
  /******* fin *******/

  // Show lists after computation.
  printf("Processed reference list:\n");
  list_print(reference);
  printf("ExPResSO reference list:\n");
  list_print(expresso);

  // Results check.
  if(list_check(reference, expresso)) {
    fprintf(stderr, "Bad results :-(\n");
    list_free(reference);
    list_free(expresso);
    return 1;
  }

  printf("Reference computation time: %g s\n", time_reference);
  printf(" ExPResSO computation time: %g s\n", time_expresso);

  printf("Good results :-)\n");
  list_free(reference);
  list_free(expresso);
  
  return 0;
}
