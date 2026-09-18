# Architectures Parallèles 并行体系结构

# TP3: x86_64 assembly - SIMD with SSE and AVX (part 1) TP3：x86_64汇编——使用SSE和AVX的SIMD（第一部分）

# 0 Cheatsheet 速查表

# 0.1 SIMD SIMD简介

SIMD 就是通过把多个数据元素打包到向量寄存器，让单条指令对这些元素并行执行同一种操作，从而提升数据并行任务的吞吐。

The SSE and AVX instruction set extensions introduce SIMD (Single-Instruction, Multiple-Data) compute capabilities for both integer and FP operands. As their name implies, SIMD instructions are able to process multiple scalar operands at once, as shown in the figure below. We talk about vector registers, containing packed integer or packed floating-point values. XMM registers are 128-bits wide, which allows storing two double precision or four single precision elements:
SSE和AVX指令集扩展为整数和浮点操作数引入了SIMD（单指令多数据）计算能力，如其名所示，SIMD指令可以像下图所示那样一次处理多个标量操作数。我们称之为向量寄存器，内部存放打包的整数或浮点数。XMM寄存器宽128位，可容纳两个双精度或四个单精度元素：

![](<images/image1.jpg>)

SIMP instructions usually operate element-by-element as illustrated below:
SIMD指令通常按照下列示意逐个元素进行操作：

![](<images/image2.png>)

At the hardware level, vector processors can process all pairs of elements (f11/f21, f12/f22, ...) in parallel, significantly speeding up the computation. Note that some instructions that we will use in the lab do not operate element-by-element like the above example (vbroadcastss, haddps, ...).
在硬件层面，向量处理器可以并行处理所有元素对（f11/f21、f12/f22等），显著提升计算速度。注意本实验中会用到的一些指令（如vbroadcastss、haddps等）并不会像上面的示例那样逐元素操作。

# 0.2 Instructions 指令

<table><tr><td>Instruction</td><td>Description</td><td>C equivalent</td></tr><tr><td>addpd x1, x2</td><td>Double-precision packed FP add<br>双精度打包浮点加法</td><td>x11 += x21; x12 += x22;</td></tr><tr><td>addps x1, x2</td><td>Single-precision packed FP add<br>单精度打包浮点加法</td><td>x11 += x21; . . .; x14 += x24;</td></tr><tr><td>subpd x1, x2</td><td>Double-precision packed FP sub<br>双精度打包浮点减法</td><td>x11 -= x21; x12 -= x22;</td></tr><tr><td>mulpd x1, x2</td><td>Double-precision packed FP mul<br>双精度打包浮点乘法</td><td>x11 *= x21; x12 *= x22;</td></tr><tr><td>divpd x1, x2</td><td>Double-precision packed FP div<br>双精度打包浮点除法</td><td>x11 /= x21; x12 /= x22;</td></tr><tr><td>movupd x, m</td><td>Double-precision unaligned load<br>双精度非对齐加载</td><td>x11 = *m; x12 = *(m+1);</td></tr><tr><td>movapd x, m</td><td>Double-precision aligned load<br>双精度对齐加载</td><td>x11 = *m; x12 = *(m+1);</td></tr><tr><td>movupd m, x</td><td>Double-precision unaligned store<br>双精度非对齐存储</td><td>*m = x11; *(m+1) = x12;</td></tr><tr><td>movups x, m</td><td>Single-precision unaligned load<br>单精度非对齐加载</td><td>x11 = *m; . . .; x14 = *(m+3);</td></tr><tr><td>vbandcastsd x1, x2</td><td>Copy the lower double-precision element of x2 in all elements of x1<br>将x2的低位双精度元素广播到x1全部元素</td><td>x11 = x21; x12 = x21;</td></tr><tr><td>vbandcastss x1, x2</td><td>Copy the lower single-precision element of x2 in all elements of x1<br>将x2的低位单精度元素广播到x1全部元素</td><td>x11 = x21; . . .; x14 = x21;</td></tr><tr><td>haddps x1, x2</td><td>Horizontal add (add pairs of elements) into elements of x1<br>水平加法（元素成对相加后写回x1）</td><td>x11=x11+x12; x12=x13+x14; x13=x21+x22; x14=x23+x24;</td></tr></table>

Note: You will notice that mov[a|u]p[s|d] instructions have two variants for aligned and unaligned memory operands. A memory access is considered aligned if the accessed address is a multiple of the type's size. Aligned accesses are considered better because they give the guarantee that we do not overlap cache lines. However, on modern hardware, the performance penalty of performing unaligned accesses is usually negligible. For the sake of simplicity, you can always perform unaligned accesses in this lab (that is using the movup[s|d] instructions).
注意：mov[a|u]p[s|d]指令针对对齐与非对齐内存操作数各有一个变体。当访问地址是类型大小的整数倍时，该内存访问被视为对齐。对齐访问通常更好，因为它们能够保证不会跨越缓存行。然而在现代硬件上，执行非对齐访问的性能损失通常可以忽略。为简化起见，本实验中你可以始终使用非对齐访问（即movup[s|d]指令）。

# 1 Introductory example and tail loops
介绍示例与尾循环

Consider the following scalar dot product code vectorized in inline ASM:
下面是一段用内联汇编编写的标量点积代码：

```c
float dotprod_id_asm(size_t n, float a[n], float b[n]) {  
float r = 0.f;  
asm()  
"cmp %1, 0;"  
"je end;"  
"xor rax, rax;"  
"start:"  
"movss xmm0, [%2+rax*4]"  
"movss xmm1, [%3+rax*4]"  
"mulss xmm0, xmm1;"  
"addss %0, xmm0;"  
"inc rax;"  
"cmp rax, %1;"  
"jl start;"  
"end:"  
: "+"r" (r) // Outputs  
: "r" (n), "r" (a), "r" (b) // Inputs  
: "rax", "xmm0", "xmm1" // Clobber  
);  
return r;
```

# 1.1
第一问

For now, let us focus on the case  $n \% 4 == 0$ . Vectorize this code by replacing the scalar movss, mulss and addss by their vector counterpart.
目前先聚焦 $n \% 4 == 0$ 的情形，将标量的movss、mulss和addss指令替换成对应的向量版本，对上述代码完成向量化。

# 1.2
第二问

What problem would occur when  $n$  is not a multiple of the vector size? Fix the issue by introducing a "tail loop" to treat remaining elements.
当 $n$ 不是向量长度的倍数时会出现什么问题？通过添加“尾循环”来处理剩余元素并修复这一问题。

# 2 Loop carried dependencies
循环相关依赖

Consider the following C loop:
请看下面这段C循环：

```c
include<stdio.h>   
defineK5   
void loop1(size_t n,float a[n]) { if(n<=K) return;   
for(size_t i=0;i<n-K;++i）{ a[i]=a[i+K]/2.;   
}   
10
```

We assume  $K > 0$  for now. 这里先假设 K > 0$。

# 2.1
问题2.1

Are there any loop-carried dependency preventing us from naively vectorizing the loop? Write a vectorized version of this code in ASM or inline ASM (a scalar ASM version is also given to help you).
是否存在阻止我们直接向量化的循环相关依赖？请用ASM或内联ASM写出该代码的向量化版本（可参考给出的标量ASM版本）。

# 2.2
问题2.2

Consider the following variant of the previous code:
考虑上面代码的如下变体：

```txt
1 #define K 5   
2   
3 void loop2(size_t n, float a[n]) { if(n <= K) return;   
5   
6 for(size_t i = K; i<n; ++i) { a[i] = a[i-K] / 2.;   
7 }   
8   
9 }
```

We assume  $\mathrm{K} > 0$ .
同样假设 $\mathrm{K} > 0$。

Are there any loop-carried dependency preventing us from naively vectorizing the loop? Write a vectorized version of this code in ASM or inline ASM, by assuming that we are in a case where naive vectorization is possible.
是否存在阻碍直接向量化的循环依赖？假设这里可以直接向量化，请写出该代码的ASM或内联ASM向量版本。

# 2.3
问题2.3

Consider the following generalization of the two previous codes:
观察下面对前面两个代码的泛化：

```c
1 void loop3(size_t n, float a[n], int64_t k) {
2 if (n <= k) return;
3
4 size_t lower = k >= 0 ? 0 : k;
5 size_t upper = k >= 0 ? n-k : n;
6
7 for (size_t i = lower; i < upper; ++i) {
8 a[i] = a[i+k] / 2.;
9 }
10 }
```

Note how  $\mathbf{k}$  is not a constant known at compile-time anymore. Indeed, it will create loop-carried dependencies that must be resolved at run-time.
注意此处的 $\mathbf{k}$ 不再是编译期常量，因此会产生需在运行期解决的循环依赖。

In the general case presented above, what are the conditions on  $\mathbf{k}$  and the vector size that allow trivial vectorization of the code?
在上述一般情况下，$\mathbf{k}$ 与向量长度需要满足哪些条件才能进行直接向量化？

Write a code in ASM or inline ASM that checks those conditions at runtime. If they are met, execute the vectorized version of the loop. If not, execute a scalar version as a fallback solution.
请编写ASM或内联ASM代码，在运行时检查这些条件；若满足则执行向量化循环，否则回退到标量实现。

Note: The technique you are asked to implement above is called loop versioning. It is commonly used by compilers, especially in the case of pointers that may overlap. This allows them to perform alias-analysis at run-time if they can not ensure that vectorization is always possible at compile-time.
注：上述技术称为循环版本化。编译器常在指针可能重叠时使用它，如果编译期无法保证总能向量化，就在运行时做别名分析并选择相应版本。
