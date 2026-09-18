#include <stddef.h>
#include <stdio.h>


float dotprod_nd_asm_notail(size_t n, float a[n], float b[n]) {
  float r = 0.;

  asm(
    "cmp %1, 0;"
    "je end_notail;"

    "xor rax, rax;"
    "start_notail:"
      "movups xmm0, [%2+rax*4];"
      "movups xmm1, [%3+rax*4];"
      "mulps xmm0, xmm1;"
      "haddps xmm0, xmm0;"
      "haddps xmm0, xmm0;"
      "addss %0, xmm0;"

      "add rax, 4;"
      "cmp rax, %1;"
      "jl start_notail;"

    "end_notail:"
    : "+x" (r) // Outputs
    : "r" (n), "r" (a), "r" (b) // Inputs
    : "rax", "rbx", "xmm0", "xmm1" // Clobber
  );
  return r;
}

float dotprod_nd_asm(size_t n, float a[n], float b[n]) {
  float r = 0.;

  asm(
    "cmp %1, 0;"
    "je end;"

    "mov rbx, %1;"       // save upper bound for tail loop
    "sar %1, 2;"         // vector iterations = n / 4
    "sal %1, 2;"         // convert back to count of processed elems
    "xor rax, rax;"

    "cmp %1, 0;"
    "je prestart_tail;"

    "start:"
      "movups xmm0, [%2+rax*4];"
      "movups xmm1, [%3+rax*4];"
      "mulps xmm0, xmm1;"
      "haddps xmm0, xmm0;"
      "haddps xmm0, xmm0;"
      "addss %0, xmm0;"
      "add rax, 4;"
      "cmp rax, %1;"
      "jl start;"

    "prestart_tail:"
    "cmp rbx, %1;"
    "je end;"

    "start_tail:"
      "movss xmm0, [%2+rax*4];"
      "movss xmm1, [%3+rax*4];"
      "mulss xmm0, xmm1;"
      "addss %0, xmm0;"
      "inc rax;"
      "cmp rax, rbx;"
      "jl start_tail;"

    "end:"
    : "+x" (r) // Outputs
    : "r" (n), "r" (a), "r" (b) // Inputs
    : "rax", "rbx", "xmm0", "xmm1" // Clobber
  );
  
  return r;
}
