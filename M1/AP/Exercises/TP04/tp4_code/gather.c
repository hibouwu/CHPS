#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#define N 15

void gather_asm_fixedsize(double a[4], int64_t id[4], double b[4]);
void gather_asm(int64_t n, double a[n], int64_t id[n], double b[n]);
void gather_asm_scalar(int64_t n, double a[n], int64_t id[n], double b[n]);

void gather(int64_t n, double a[n], int64_t id[n], double b[n]) {
  if(n == 0) return;
  for(size_t i=0; i<n; ++i) {
    a[i] = b[id[i]];
  }
}


void init_arrays(double a[N], double a_ref[N], double a_scalar[N], int64_t id[N], double b[N]) {
  for(size_t i=0; i<N; ++i) {
    a[i] = -1.;
    a_ref[i] = -1.;
    a_scalar[i] = -1.;
    id[i] = N - i - 1;
    b[i] = (float) i;
  }
}


int main(void) {

  double a_fixedsize[4] = {-1., -1., -1., -1.};
  int64_t id_fixedsize[4] = {3, 2, 1, 0};
  double b_fixedsize[4] = {0., 1., 2., 3.};

  
  gather_asm_fixedsize(a_fixedsize, id_fixedsize, b_fixedsize);
  printf(
    "a_fixedsize = %lf %lf %lf %lf\n", 
    a_fixedsize[0], a_fixedsize[1], a_fixedsize[2], a_fixedsize[3]
  );
 
  double a[N]; double a_ref[N]; double a_scalar[N]; int64_t id[N]; double b[N];
  init_arrays(a, a_ref, a_scalar, id, b);

  gather(N, a_ref, id, b);
  gather_asm_scalar(N, a_scalar, id, b);
  gather_asm(N, a, id, b);
  for(size_t i=0; i<N; i++) {printf("id[%lu]=%lu\n", i, id[i]);}

  for(size_t i=0; i<N; ++i) {
    printf("a_ref[%d]=%lf  a_scalar[%d]=%lf  a[%d]=%lf\n", i, a_ref[i], i, a_scalar[i], i, a[i]);
  }

  return 0;
}
