#include <math.h>
#include <stdint.h>
#include <stddef.h>
// make clean && make && ./driver

void naive(size_t n, float x[n], float y[n], uint64_t repets) {
  const float one = 1.f;

  __asm__ volatile (
    "xor rax, rax;"

    "repets_naive:"
    "xor rbx, rbx;"
    
    "n_naive:"
    "movss xmm0, [%[x] + rbx*4];"   // Load x[i] in xmm0
    /**************************/
    
    "sqrtss xmm0, xmm0;"            // xmm0 = sqrt(x[i])
    "movss xmm1, %[one];"           // xmm1 = 1.0f
    "divss xmm1, xmm0;"             // xmm1 = 1.0f / sqrt(x[i])
    
    /**************************/
    "movss [%[y] + rbx*4], xmm1;"   // Store result in y[i]

    "inc rbx;"
    "cmp rbx, %[n];"
    "jl n_naive;"

    "inc rax;"
    "cmp rax, %[repets];"
    "jl repets_naive;"
    : 
    : [repets]"r" (repets), [n]"r" (n), [x] "r" (x), [y] "r" (y), [one]"m" (one)
    : "rax", "rbx", "xmm0", "xmm1"
  );
}


void newton(size_t n, float x[n], float guess, float y[n], uint64_t repets) {
  __asm__ volatile (
    "xor rax, rax;"

    "repets_newton:"
    "xor rbx, rbx;"
    
    "n_newton:"
    "movss xmm0, [%2 + rbx*4];" // Load x[i] in xmm0

    /**************************/
    // Newton-Raphson iteration: y = y * (1.5 - 0.5 * x * y * y)


    /**************************/
    "movss [%4 + rbx*4], xmm0;" // Store xmm0 in y[i]

    "inc rbx;"
    "cmp rbx, %1;"
    "jl n_newton;"

    "inc rax;"
    "cmp rax, %0;"
    "jl repets_newton;"
    : 
    : "r" (repets), "r" (n), "r" (x), "x"(guess), "r" (y), [oneDotFive]"x" (1.5f), [dotFive] "x" (.5f)
    : "rax", "rbx", "xmm0"
  );
}


void fast(size_t n, float x[n], float y[n], uint64_t repets) {
  __asm__ volatile (
    "xor rax, rax;"

    "repets_fast:"
    "xor rbx, rbx;"
    
    "n_fast:"
    "movss xmm0, [%2 + rbx*4];" // Load x[i] in xmm0
    "mov r8d, [%2 + rbx*4];" // Load x[i] in r8d as an integer

    // Your code here

    "movss [%3 + rbx*4], xmm0;" // Store xmm0 in y[i]

    "inc rbx;"
    "cmp rbx, %1;"
    "jl n_fast;"

    "inc rax;"
    "cmp rax, %0;"
    "jl repets_fast;"
    : 
    : "r" (repets), "r" (n), "r" (x), "r" (y), "x" (1.5f), "x" (.5f)
    : "rax", "rbx", "r8", "r9", "xmm0"
  );
}
