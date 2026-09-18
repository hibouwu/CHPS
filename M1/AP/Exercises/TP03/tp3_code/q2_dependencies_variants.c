#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#include "constants.h"

float loop1_scalar(size_t n, float a[n]) {

  uint64_t k = K2;

  asm(
    // Ensure n>k
    "cmp %[n], %[k];"
    "jle end;"

    "mov rax, 0;"    // Counter for index i
    "mov rbx, %[k];" // Counter for index i+k

    "start:"

    "movss xmm0, [%[a]+rbx*4];"   
    "divss xmm0, %[two];"
    "movss [%[a]+rax*4], xmm0;"

    "inc rax;"
    "inc rbx;"
    "cmp rbx, %[n];"
    "jl start;"

    "end:"
    :
    : [n]"r"(n), [a]"r"(a), [k]"r"(k), [two]"x"(2.f)
    : "rax", "rbx", "xmm0"
  );
}


float loop1_vec(size_t n, float a[n]) {

  uint64_t k = K1;

  asm(
    // Ensure n>k
    "cmp %[n], %[k];"
    "jle loop1_end;"

    "vbroadcastss %[two], %[two];" // broadcast 2.0 to all elements of %[two]

    "mov rax, 0;"          // i = 0
    "mov rdx, %[k];"        // i + k
    
    "sub %[n], %[k];"        // update upper loop bound with pre-adding
    "mov rcx, %[n];"
    "ADD %[n],0b11111100;" 

    "cmp %[n], 0;"
    "je loop1_tail_prep;"
    
    //Main vector loop
    "Start_Loop1_Vector:"
      
    "movups xmm0, [%[a]+rdx*4];"
    "divps xmm0, %[two];"
    "movups [%[a]+rax*4], xmm0;"
    
    "add rax, 4;"
    "add rdx, 4;"
    "cmp rax, %[n];"
    "jl Start_Loop1_Vector;"

    //Tail scalar loop prep
    "loop1_tail_prep:"
    "cmp rax, rcx;"
    "je loop1_end;"

    "loop1_tail_start:"

      "movss xmm0, [%[a]+rdx*4];"
      "divss xmm0, %[two];"
      "movss [%[a]+rax*4], xmm0;"

      "inc rax;"
      "inc rdx;"
      "cmp rax, rcx;"
      "jl loop1_tail_start;"

    "loop1_end:"
    : 
    : [n]"r"(n), [a]"r"(a), [k]"r"(k), [two]"x"(2.f)
    : "rax", "rbx", "rcx", "rdx", "xmm0"
  );
}


float loop2_vec(size_t n, float a[n]) {

  uint64_t k = K2;

  // WARNING This is wrong (on purpose)

  asm(
    ""
    : 
    : [n]"r"(n), [a]"r"(a), [k]"r"(k), [two]"x"(2.f)
    : "rax", "rbx", "rcx", "xmm0"
  );
}


float loop3_vec(size_t n, float a[n], int64_t k) {


  int64_t r8 = 0;
  int64_t r9 = 0;

  asm(
    ""
    :
    : [n]"r"(n), [a]"r"(a), [k]"r"(k), [two]"x"(2.f)
    : "rax", "rbx", "rcx", "r8", "r9", "xmm0"
  );
}
