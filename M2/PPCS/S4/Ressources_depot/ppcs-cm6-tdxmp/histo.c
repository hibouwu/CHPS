#include "Matrix.xmptype.h"
#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for usleep
#include <xmp.h>

#pragma xmp nodes p(1)
#pragma xmp template t[ : ]
#pragma xmp distribute t(block) onto p

float *data_in;
#pragma xmp align data_in[i] with t(i)
#pragma xmp shadow data_in[*]

int *data_out;

void calcule_histo(float *data, int rows) {
#pragma xmp loop on t(i)
  for (int i = 0; i < rows; i++) {
    int j = (int)data[i];
    if ((j >= 0) && (j < 20)) {
      data_out[j]++;
    }
  }
}

int main(int argc, char **argv) {
  xmp_init_mpi(&argc, &argv);

  FILE *file = fopen("input.txt", "r");
  if (file == NULL) {
    fprintf(stderr, "Erreur : impossible d'ouvrir le fichier d'entree\n");
    return 1;
  }
  // Lecture du nombre d'observations
  int rows;
  fscanf(file, "%d", &rows);
  fprintf(stderr, "rows %d\n", rows);
#pragma xmp template_fix t[rows]
  data_in = xmp_malloc(xmp_desc_of(data_in), rows);

  data_out = (int *)malloc(20 * sizeof(int));
  if (data_in == NULL) {
    fprintf(stderr, "Erreur : impossible d'allouer la memoire pour le vecteur "
                    "de donnees\n");
    return 1;
  }

  // Lecture des données du fichier
  for (int i = 0; i < rows; i++) {
    float a;
    fscanf(file, "%f,", &a);
    data_in[i] = a;
  }
  fclose(file);

  char *processor_name = malloc(256 * sizeof(char));
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);
  fprintf(stderr, "\ndebut traitement \nProcesseur %d - Nom : %s \n",
          xmpc_node_num(), processor_name);

  MPI_Barrier(MPI_COMM_WORLD);
  // Calcul de l'histogramme
  calcule_histo(data_in, rows);

  MPI_Barrier(MPI_COMM_WORLD);

  usleep(100);

  // Écriture de l'histogramme
  // Ouverture du fichier de sortie
  char buffer[100];
  sprintf(buffer, "output.txt.%i", xmpc_node_num());
  FILE *output_file = fopen(buffer, "w");
  if (output_file == NULL) {
    printf("Erreur : impossible d'ouvrir le fichier de sortie\n");
    return 1;
  }
  for (int i = 0; i < 20; i++) {
    fprintf(output_file, "%u ", i);
  }
  fprintf(output_file, "\n");
  for (int i = 0; i < 20; i++) {
    fprintf(output_file, "%u ", data_out[i]);
  }
  fprintf(output_file, "\n");
  fclose(output_file);

  MPI_Barrier(MPI_COMM_WORLD);
  usleep(100);
  // Libération de la mémoire

  free(data_in);
  free(data_out);
  fprintf(stderr, "\nfin traitement \nProcesseur %d - Nom : %s \n",
          xmpc_node_num(), processor_name);
  free(processor_name);
  xmp_finalize_mpi();

  return 0;
}
