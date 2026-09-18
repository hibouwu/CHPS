#include <stdio.h>
#include <stdlib.h>

#include "constants.h"

float loop1_scalar(size_t n, float a[n]);
float loop1_vec(size_t n, float a[n]);
float loop2_vec(size_t n, float a[n]);
float loop3_vec(size_t n, float a[n], int64_t k);

void loop1(size_t n, float a[n]) {
  if(n <= K1) return;

  for(size_t i=0; i<n-K1; ++i) {
    a[i] = a[i+K1] / 2.;
  }
}

void loop2(size_t n, float a[n]) {
  if(n <= K2) return;

  for(size_t i=K2; i<n; ++i) {
  a[i] = a[i-K2] / 2.;
  }
}

void loop3(size_t n, float a[n], int64_t k) {
  if(n <= abs(k)) return;

  size_t lower = k>=0 ? 0 : -k;
  size_t upper = k>=0 ? n-k : n;

  for(size_t i=lower; i<upper; ++i) {
    a[i] = a[i+k] / 2.;
  }
}


int main(void) {

  /* 1 */

  size_t l = 14;
  float a1_ref[l]; float a1_scalar[l]; float a1_vec[l];


  // Init a1
  for(size_t i=0; i<l; i++) {
    a1_ref[i] = (float) (i+1);
    a1_scalar[i] = (float) (i+1);
    a1_vec[i] = (float) (i+1);
  }

  loop1(l, a1_ref);
  loop1_scalar(l, a1_scalar);
  loop1_vec(l, a1_vec);
  
  for(size_t i=0; i<6; ++i) {
    printf("a1_ref[%d]=%lf  a1_scalar[%d]=%lf a1_vec[%d]=%lf\n", i, a1_ref[i], i, a1_scalar[i], i, a1_vec[i]);
  }
  printf("...\n");
  // Also check the last elements for tail loop
  for(size_t i=l-6; i<l; ++i) {
    printf("a1_ref[%d]=%lf  a1_scalar[%d]=%lf a1_vec[%d]=%lf\n", i, a1_ref[i], i, a1_scalar[i], i, a1_vec[i]);
  }
  printf("\n");


  /* 2 */
  
  size_t m = 14;
  float a2_ref[m]; float a2_vec[m];

  // Init a2
  for(size_t i=0; i<l; i++) {
    a2_ref[i] = (float) (i+1);
    a2_vec[i] = (float) (i+1);
  }

  loop2(m, a2_ref);
  loop2_vec(m, a2_vec);
  
  for(size_t i=0; i<6; ++i) {
    printf("a2_ref[%d]=%lf a2_vec[%d]=%lf\n", i, a2_ref[i], i, a2_vec[i]);
  }
  printf("...\n");
  // Also check the last elements for tail loop
  for(size_t i=m-6; i<m; ++i) {
    printf("a2_ref[%d]=%lf a2_vec[%d]=%lf\n", i, a2_ref[i], i, a2_vec[i]);
  }
  printf("\n");


  /* 3 */
  
  size_t n = 20;
  float a3_ref[n]; float a3_vec[n];

  // Init a2
  for(size_t i=0; i<n; i++) {
    a3_ref[i] = (float) (i+1);
    a3_vec[i] = (float) (i+1);
  }

  loop3(n, a3_ref, K3);
  loop3_vec(n, a3_vec, K3);

  for(size_t i=0; i<6; ++i) {
    printf("a3_ref[%d]=%lf a3_vec[%d]=%lf\n", i, a3_ref[i], i, a3_vec[i]);

  }
  printf("...\n");
  // Also check the last elements for tail loop
  for(size_t i=n-6; i<n; ++i) {
    printf("a3_ref[%d]=%lf a3_vec[%d]=%lf\n", i, a3_ref[i], i, a3_vec[i]);
  }
  printf("\n");

  return 0;
}
