#include <stddef.h>
#include <stdint.h>
#include <stdio.h>


void gather_asm_fixedsize(double a[4], int64_t id[4], double b[4]) {
  int64_t mask;
  int64_t *maskptr = &mask;

  asm(
    "xor rax, rax;"
    "not rax;"
    "mov [%[mask]], rax;"
    "vpbroadcastq ymm2, [%[mask]];" // Broadcast mask

    "vmovdqu ymm0, [%[id]];"        // Load indices as packed integers
    "vgatherqpd ymm1, [%[b]+ymm0*8], ymm2;" // Gather loads
    "vmovdqu [%[a]], ymm1;"         // Store result
    :     
    : [a]"r"(a), [id]"r"(id), [b]"r"(b), [mask]"r"(maskptr)
    : "rax", "ymm0", "ymm1", "ymm2"
  );
}


void gather_asm_scalar(int64_t n, double a[n], int64_t id[n], double b[n]) {
  int64_t mask;
  int64_t *maskptr = &mask;

  asm(
    "xor rax, rax;"
    
    "startscalar:"

    "mov rbx, [%[id]+rax*8];"
    "movsd xmm0, [%[b]+rbx*8];"
    "movsd [%[a]+rax*8], xmm0;"

    "inc rax;"
    "cmp rax, %[n];"
    "jl startscalar;"
    :     
    : [n]"r"(n), [a]"r"(a), [id]"r"(id), [b]"r"(b), [mask]"r"(maskptr)
    : "rax", "rbx", "xmm0"
  );
}

void gather_asm(int64_t n, double a[n], int64_t id[n], double b[n]) {
  int64_t mask;
  int64_t *maskptr = &mask;
  asm(
    "xor rax, rax;"
    "not rax;"
    "vpbroadcastq ymm2, [%[mask]];" // Broadcast mask

    // Vectorized loop upper bound
    "mov r8, %[n];"
    "sar r8, 2;" // r8 = n / 4
    "sal r8, 2;" // r8 = (n / 4) * 4

    "cmp r8, 0;"
    "je prestart_tail;"

    "xor rax, rax;"
    "start:"
    "vmovdqu ymm1, [%[id]+rax*8];"        // Load indices as packed integers
    "vgatherqpd ymm0, [%[b]+ymm1*8], ymm2;" // Gather loads from b using indices ids of ymm0
    "vpbroadcastq ymm2, [%[mask]];" // Re-broadcast mask
    "vmovupd [%[a]+rax*8], ymm0;"        // Store result
    "add rax, 4;"
    "cmp rax, r8;"
    "jl start;"
    // End of main vectorized loop

    //Enter tail loop
    "prestart_tail:"
    "cmp r8, %[n];"
    "je endgather;"

    // Start tail loop
    "start_tail:"

    "mov rbx, [%[id]+rax*8];"
    "movsd xmm0, [%[b]+rbx*8];"
    "movsd [%[a]+rax*8], xmm0;"
    
    "inc rax;"
    "cmp rax, %[n];"
    "jl start_tail;"
    // End tail loop

    "endgather:"
    :
    : [n]"r"(n), [a]"r"(a), [id]"r"(id), [b]"r"(b), [mask]"r"(maskptr)
    : "rax", "rbx", "r8", "ymm0", "ymm1", "ymm2"
  );
}
