#include <stdio.h>
#include <stdint.h>


uint64_t fibonacci(uint64_t n) {
  if(n<=1) {
    return 1;
  }

  uint64_t curr; uint64_t prev1=1; uint64_t prev2=1;
  for(uint64_t i=1; i<n; ++i) {
    curr = prev1 + prev2;
    prev2 = prev1;
    prev1 = curr;
  }

  return curr;
}

uint64_t fibonacci_asm(uint64_t n) {
  uint64_t r;

  asm(
    "cmp %1, 1;"
    "jg prestart;"
    "mov %0, 1;"
    "jmp end;"
    
    "prestart:"
    "mov r8, 1;" // r8 <=> prev1
    "mov r9, 1;" // r9 <=> prev2
    "mov rax, 1;"
    
    "start:"
    "mov %0, r8;" // curr = prev1
    "add %0, r9;" // curr += prev2 (== prev1 + prev2)
    "mov r9, r8;" // prev2 = prev1
    "mov r8, %0;" // prev1 = curr
    
    "inc rax;"
    "cmp rax, %1;"
    "jl start;"
    
    "end:"
    "mov rax, %1;"
    : "+r" (r)
    : "r" (n)
    : "rax", "r8", "r9"
  );

  return r;
}


int64_t main(void) {
  for(int i=0; i<6; ++i) {
    printf("fibo_iter(%d)=%u\n", i, fibonacci(i));
  }

  for(int i=0; i<6; ++i) {
    printf("fibo_iter_asm(%d)=%u\n", i, fibonacci_asm(i));
  }
  printf("\n");
  
  return 0;
}