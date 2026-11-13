#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define NB_METAS 31

extern uint64_t rdtsc ();

extern void kernel (int n, float a[n][n], float b[n][n], float c[n][n]);

static void init_array (int n, float a[n][n]) {
   int i, j;

   for (i=0; i<n; i++)
      for (j=0; j<n; j++)
         a[i][j] = (float) rand() / RAND_MAX;
}

static void print_array (int n, const float a[n][n]) {
   int i, j;

   for (i=0; i<n; i++)
      for (j=0; j<n; j++)
         printf ("%f\n", a[i][j]);
}

static int cmp_uint64 (const void *a, const void *b) {
   const uint64_t va = *((uint64_t *) a);
   const uint64_t vb = *((uint64_t *) b);

   if (va > vb) return 1;
   if (va < vb) return -1;
   return 0;
}

int main (int argc, char *argv[]) {
   /* check command line arguments */
   if (argc != 4) {
      fprintf (stderr, "Usage: %s <size> <nb warmup repets> <nb measure repets>\n", argv[0]);
      abort();
   }

   int i, m;

   /* get command line arguments */
   int size = atoi (argv[1]); /* matrix size */
   int repw = atoi (argv[2]); /* repetition number */
   int repm = atoi (argv[3]); /* repetition number */

   uint64_t t [NB_METAS];

   for (m=0; m<NB_METAS; m++) {
      /* allocate arrays */
      float (*a)[size] = malloc (size * size * sizeof a[0][0]);
      float (*b)[size] = malloc (size * size * sizeof b[0][0]);
      float (*c)[size] = malloc (size * size * sizeof c[0][0]);

      /* init arrays */
      srand(0);
      init_array (size, a);
      init_array (size, b);

      /* warmup (repw repetitions in first meta, 1 repet in next metas) */
      if (m == 0) {
         for (i=0; i<repw; i++)
            kernel (size, a, b, c);
      } else {
         kernel (size, a, b, c);
      }

      /* measure repm repetitions */
      uint64_t t1 = rdtsc();
      for (i=0; i<repm; i++)
         kernel (size, a, b, c);
      uint64_t t2 = rdtsc();

      /* print performance */
      printf ("%.2f cycles/innerprod-iter\n",
              (t2 - t1) / ((float) size * size * size * repm));

      t[m] = t2 - t1;

      /* print output */
      //if (m == 0) print_array (n, c);

      /* free arrays */
      free (a);
      free (b);
      free (c);
   }

   // Print minimum, median and (med-min)/min
   qsort (t, NB_METAS, sizeof t[0], cmp_uint64);
   printf ("MIN: %.2f cycles/innerprod-iter\n",
           t[0] / ((float) size * size * size * repm));
   printf ("MED: %.2f cycles/innerprod-iter\n",
           t[NB_METAS/2] / ((float) size * size * size * repm));
   printf ("MED-MIN/MIN: %.2f\n", (t[NB_METAS/2] - t[0]) / (float) t[0]);

   return EXIT_SUCCESS;
}
