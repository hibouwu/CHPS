#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


bool opposite_signs(int64_t a, int64_t b) {
  return (a>=0 && b<0) || (a<0 && b>=0);
}

bool opposite_signs_asm(int64_t a, int64_t b) {
  bool r;

  asm(
    "cmp %1, 0;"
    "jge aplus;"
    
    // aminus:
    "cmp %2, 0;" 
    "jge tr;" // b>=0? true
    "jmp fa;" // else, false
    
    "aplus:"
    "cmp %2, 0;"
    "jl tr;"  // b<0? true
    "jmp fa;" // else, false

    "tr:" // true case: set r to 1
    "mov %0, 1;"
    "jmp end;"
    
    "fa:" // false case: set r to 0
    "mov %0, 0;"
    
    "end:"
    : "=r" (r)
    : "r" (a), "r" (b)
    :
  );

  return r;
}

bool opposite_signs_branchless_asm(int64_t a, int64_t b) {
  asm(
    "xor %0, %1;"
    "shr %0, 63;"
    : "+r" (a)
    : "r" (b)
    :
  );

  return (bool) a;
}

int main(void) {
  int64_t a = 4; int64_t b = -2; int64_t c = 0;

  printf("a=%i\n", a);
  printf("b=%i\n", b);
  printf("c=%i\n\n", c);

  bool ab = opposite_signs(a, b);
  bool bc = opposite_signs(b, c);
  bool ac = opposite_signs(a, c);

  printf("ab=%d\n", ab);
  printf("bc=%d\n", bc);
  printf("ac=%d\n\n", ac);

  ab = opposite_signs_asm(a, b);
  bc = opposite_signs_asm(b, c);
  ac = opposite_signs_asm(a, c);

  printf("asm ab=%d\n", ab);
  printf("asm bc=%d\n", bc);
  printf("asm ac=%d\n\n", ac);

  ab = opposite_signs_branchless_asm(a, b);
  bc = opposite_signs_branchless_asm(b, c);
  ac = opposite_signs_branchless_asm(a, c);

  printf("branchless ab=%d\n", ab);
  printf("branchless bc=%d\n", bc);
  printf("branchless ac=%d\n", ac);

  return 0;
}