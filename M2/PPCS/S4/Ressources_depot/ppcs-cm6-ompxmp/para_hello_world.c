// programme élémentaire pour GLCS-CM6-OMPXMP
// OpenMP et XMP
#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <xmp.h>
#pragma xmp nodes p(*)
int main(int argc, char **argv) {
  xmp_init_mpi(&argc, &argv);
#pragma omp parallel
  fprintf(stderr, "Hello from process: %d on node %d \n", omp_get_thread_num(),
          xmpc_node_num());

  xmp_finalize_mpi();

  return 0;
}