#include <stdio.h>
#include <stdlib.h>

// TODO
float dotprod_nd_asm_notail(size_t n, float a[n], float b[n]);
float dotprod_nd_asm(size_t n, float a[n], float b[n]);


float dotprod_nd(size_t n, float a[n], float b[n]) {
  float sum = 0;
  for(size_t i=0; i<n; ++i) {
    sum += a[i] * b[i];
  }

  return sum;
}

float dotprod_nd_asm_scalar(size_t n, float a[n], float b[n]) {
  float r = 0.f;
  asm(
    "cmp %1, 0;"
    "je end_scalar;"

    "xor rax, rax;"

    "start_scalar:"
  
    "movss xmm0, [%2+rax*4];"
    "movss xmm1, [%3+rax*4];"
    "mulss xmm0, xmm1;"
    "addss %0, xmm0;"

    "inc rax;"
    "cmp rax, %1;"
    "jl start_scalar;"

    "end_scalar:"
    : "+x" (r) // Outputs
    : "r" (n), "r" (a), "r" (b) // Inputs
    : "rax", "xmm0", "xmm1" // Clobber
  );
  
  return r;
}



int main(void) {

  size_t n = 8;
  float a[n]; float b[n];
  float r_ref;
  float r_scalar;
  float r_nd_asm_notail;
  float r_nd_asm;

  // Init a
  for(size_t i=0; i<n; i++) {
    a[i] = (float) (i+1);
    b[i] = (float) (i+2);
  }

  r_ref = dotprod_nd(n, a, b);
  r_scalar = dotprod_nd_asm_scalar(n, a, b);
  r_nd_asm_notail = dotprod_nd_asm_notail(n, a, b);
  r_nd_asm = dotprod_nd_asm(n, a, b);
  printf("r_ref=%lf  r_scalar=%lf\n", r_ref, r_scalar);
  printf("r_nd_asm_notail=%lf  r_nd_asm=%lf\n\n", r_nd_asm_notail, r_nd_asm);

  // Test with multiple sizes
  for (size_t i=0; i<50; i++) {
    n = i;
    float a[n]; float b[n];
    // Init a
    for(size_t i=0; i<n; i++) {
      a[i] = (float) (i+1);
      b[i] = (float) (i+2);
    }
    printf("Iteration %lu with n=%lu   ", i, n);
    r_ref = dotprod_nd(n, a, b);
    r_nd_asm_notail = dotprod_nd_asm_notail(n, a, b);
    if (r_ref != r_nd_asm_notail) {
      printf("ERROR: Error in dotprod_nd_asm_notail: r_ref=%lf r_nd_asm_notail=%lf\n", i, r_ref, r_nd_asm_notail);
    }else{
      printf("PAASSED : dotprod_nd_asm_notail passed: r_ref=%lf r_nd_asm_notail=%lf\n", i, r_ref, r_nd_asm_notail);
    }
  }
  return 0;
}
