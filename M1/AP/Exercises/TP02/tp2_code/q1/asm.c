#include <stddef.h>
#include <stdint.h>


// make clean && make && ./loop

void loop_asm(size_t n, double a[n]) {
  asm(
    "xor rax, rax;"             // rax = 0 (循环计数器 i)
    "sub %[n], 1;"              // %[n] = n - 1 (循环边界调整)
    "start1:"                   // 循环开始标签

    "mov rbx, rax;"             // rbx = rax = i
    "add rbx, 1;"               // rbx = i + 1 (下一个数组索引)
    "movsd xmm0, [%[a] + rbx*8];"  // xmm0 = a[i+1] (加载下一个元素到xmm0)
    "sqrtsd xmm1, %[two];"      // xmm1 = sqrt(2.0) (计算平方根，存入xmm1)
    "divsd xmm0, xmm1;"         // xmm0 = xmm0 / xmm1 = a[i+1] / sqrt(2.0)
    "movsd [%[a] + rax*8], xmm0;"  // a[i] = xmm0 (将结果存储到当前位置)
    "inc rax;"                  // rax = rax + 1 (i++)
    
    "cmp rbx, %[n];"            // 比较 rbx(i+1) 和 %[n](n-1)
    "jl start1;"                // 如果 i+1 < n，跳转回start1继续循环
    :
    : [n]"r"(n), [a]"r"(a), [two]"x"(2.)
    : "rax", "rbx", "xmm0", "xmm1"
  );
}


void loop_asm_opt(size_t n, double a[n]) {
  // 优化版本：将 sqrt(2.) 计算移出循环
  asm(
    "xor rax, rax;"             // rax = 0 (循环计数器 i)
    "sub %[n], 1;"              // %[n] = n - 1 (循环边界调整)
    "sqrtsd xmm0, %[two];"      // xmm0 = sqrt(2.0) - 优化：移出循环，只计算一次！
    "start2:"                   // 循环开始标签
    "mov rbx, rax;"             // rbx = rax = i
    "add rbx, 1;"               // rbx = i + 1 (下一个数组索引)
    "movsd xmm1, [%[a] + rbx*8];"  // xmm1 = a[i+1] (加载下一个元素到xmm1)
    "divsd xmm1, xmm0;"         // xmm1 = xmm1 / xmm0 = a[i+1] / sqrt(2.0)
    "movsd [%[a] + rax*8], xmm1;"  // a[i] = xmm1 (将结果存储到当前位置)
    "inc rax;"                  // rax = rax + 1 (i++)
    "cmp rbx, %[n];"            // 比较 rbx(i+1) 和 %[n](n-1)
    "jl start2;"                    // 如果 i+1 < n，跳转回start2继续循环
    :
    : [n]"r"(n), [a]"r"(a), [two]"x"(2.)
    : "rax", "rbx", "xmm0", "xmm1"
  );
}
