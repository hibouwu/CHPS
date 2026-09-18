#pragma once
// External synchronization primitive (comptime-generated)
#if defined(__linux__) && defined(__x86_64__)
__attribute__((weak, naked, noinline)) int __builtin_sync_fence_() {
asm("movq $35, %rax");
asm("leaq -16(%rsp), %rdi");
asm("movq $1, (%rdi)");
asm("movq $0, 8(%rdi)");
asm("movq $0, %rsi");
asm("syscall");
asm("ret");}
#elif defined(__APPLE__) && defined(__x86_64__)
__attribute__((naked)) void __builtin_sync_fence_(void);
__asm__(".globl __builtin_sync_fence_");
__asm__(".text");
__asm__(".p2alignl 4,0x90");
__asm__("__builtin_sync_fence_:");
__asm__("movq $0x200000E, %rax");
__asm__("movq $2, %rdi");
__asm__("syscall");
__asm__("cmpq $0, %rax");
__asm__("jl __builtin_sync_fence_err");
__asm__("ret");
__asm__("__builtin_sync_fence_err:");
__asm__("negq %rax");
__asm__("ret");
#elif defined(__APPLE__) && defined(__aarch64__)
__attribute__((naked)) void __builtin_sync_fence_(void);
__asm__(".globl __builtin_sync_fence_");
__asm__(".text");
__asm__(".p2alignl 4,0x90");
__asm__("__builtin_sync_fence_:");
__asm__("mov x16, #14");
__asm__("movk x16, #0x20000, lsl #16");
__asm__("mov x0, #2");
__asm__("svc #0x80");
__asm__("cmp x0, #0");
__asm__("cneg x0, x0, mi");
__asm__("ret");
#endif
