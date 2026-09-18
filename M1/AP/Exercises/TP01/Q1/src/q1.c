#include <stdio.h>
#include <stdint.h>


int64_t dotprod_2d(int64_t ax, int64_t ay, int64_t bx, int64_t by) {
  return ax*bx + ay*by;
}

int64_t dotprod_nd(size_t n, int64_t a[n], int64_t b[n]) {
  int64_t r = 0;
  for(size_t i=0; i<n; ++i) {
    r += a[i] * b[i];
  }

  return r;
}


// TODO

int64_t dotprod_2d_asm(int64_t ax, int64_t ay, int64_t bx, int64_t by) {
  asm(
    "imul %0, %2;"
    "imul %1, %3;"
    "add %0, %1;"
    : "+r" (ax)
    : "r" (ay), "r" (bx), "r" (by)
    :
  );

  return ax;
}

int64_t dotprod_nd_asm(size_t n, int64_t a[n], int64_t b[n]) {
  int64_t r = 0;
  asm(
    "xor rax, rax;"
    "cmp rax, %1;"
    "je end;"

    "start:"

    "mov r8, [%2+rax*8];"
    "mov r9, [%3+rax*8];"
    "imul r8, r9;"
    "add %0, r8;"

    "inc rax;"
    "cmp rax, %1;"
    "jl start;"

    "end:"
    : "+r" (r)
    : "r" (n), "r" (a), "r" (b)
    : "rax", "r8", "r9"
  );

  return r;
}


int64_t main(void) {

  int64_t ax = 4; int64_t ay = 2;
  int64_t bx = 2; int64_t by = -3;

  int64_t ref = dotprod_2d(ax, ay, bx, by);
  int64_t asmref = dotprod_2d_asm(ax, ay, bx, by);
  printf("2D ref=%d\n", ref);
  printf("2D asm=%d\n", asmref);

  int64_t a[4] = {1, 2, 3, -1};
  int64_t b[4] = {-1, 2, 2, -1};

  ref = dotprod_nd(4, a, b);
  asmref = dotprod_nd_asm(4, a, b);
  printf("nD ref=%d\n", ref);
  printf("nD asm=%d\n", asmref);

  return 0;
}