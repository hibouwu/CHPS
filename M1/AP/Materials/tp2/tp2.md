# Architectures Parallèles

# TP2: x86_64 assembly -

# Floating-point arithmetic with SSE
使用SSE的浮点数算术

UVSQ - M1 CHPS

# 0 Cheatsheet
速查表

# 0.1 Registers
寄存器

Floating-point (FP) operations are typically performed using the XMM registers (xmm0 to xmm15), which have been introduced by SSE (Streaming SIMD Extension). The following figure lists the general purpose, special and XMM registers that we have seen so far:

浮点运算通常使用XMM寄存器（xmm0到xmm15）来执行，这些寄存器由SSE（流式SIMD扩展）引入。下图列出了我们到目前为止看到的通用寄存器、特殊寄存器和XMM寄存器：

Special registers

特殊寄存器


<table><tr><td>rip </td></tr><tr><td>rflags</td></tr></table>


General purpose registers

通用寄存器

<table><tr><td>rax*</td></tr><tr><td>rbx</td></tr><tr><td>rcx*</td></tr><tr><td>rdx*</td></tr><tr><td>rsi*</td></tr><tr><td>rdi*</td></tr><tr><td>rbp</td></tr><tr><td>rsp</td></tr><tr><td>r8*</td></tr><tr><td>r9*</td></tr><tr><td>r10*</td></tr><tr><td>r11*</td></tr><tr><td>r12</td></tr><tr><td>r13</td></tr><tr><td>r14</td></tr><tr><td>r15</td></tr></table>

XMM registers

XMM寄存器

<table><tr><td>xmm0*</td></tr><tr><td>xmm1*</td></tr><tr><td>xmm2*</td></tr><tr><td>xmm3*</td></tr><tr><td>xmm4*</td></tr><tr><td>xmm5*</td></tr><tr><td>xmm6*</td></tr><tr><td>xmm7*</td></tr><tr><td>xmm8*</td></tr><tr><td>xmm9*</td></tr><tr><td>xmm10*</td></tr><tr><td>xmm11*</td></tr><tr><td>xmm12*</td></tr><tr><td>xmm13*</td></tr><tr><td>xmm14*</td></tr><tr><td>xmm15*</td></tr></table>

*: scratch register

：暂存寄存器

Note that XMM registers are 128-bit wide. However, we will only use their full length later, after introducing SIMD instructions.

注意XMM寄存器是128位宽的。然而，我们将在介绍SIMD指令后才使用它们的完整长度。

# 0.2 Instructions

指令

<table><tr><td>Instruction</td><td>Description</td><td>C equivalent</td></tr><tr><td>adds x1, x2</td><td>Double-precision FP addition</td><td>x1 += x2;</td></tr><tr><td>addss x1, x2</td><td>Single-precision FP addition</td><td>x1 += x2;</td></tr><tr><td>subs[d|s] x1, x2</td><td>FP subtraction</td><td>x1 -= x2;</td></tr><tr><td>muls[d|s] x1, x2</td><td>FP multiplication</td><td>x1 *= x2;</td></tr><tr><td>divs[d|s] x1, x2</td><td>FP addition</td><td>x1 /= *x2;</td></tr><tr><td>sqrtx[s] x1, x2</td><td>Square root</td><td>x1 /= *x2;</td></tr><tr><td>movers[d|s] x, m[64|32]</td><td>Load value from memory to an XMM register</td><td>x = *m32;</td></tr><tr><td>movers[d|s] m[64|32], x</td><td>Store value from an XMM register to memory</td><td>*m64 = x;</td></tr><tr><td>cvtsi2s[d|s] x, r[64|32]</td><td>Cast a signed integer value to an FP value</td><td>x = (double)r64;</td></tr><tr><td>cvtts[d|s]2si r[64|32], x</td><td>Cast an FP value to a signed integer value</td><td>r32 = (int)x</td></tr></table>

Similarly to the smaller versions of GPRs, scalar instructions that manipulate XMM registers target their lower parts.

与GPR的较小版本类似，操作XMM寄存器的标量指令针对它们的低位部分。

Remark: As opposed to integer values, it is not possible to use immediate floating-point values as operands.

备注：与整数值不同，不能使用立即浮点值作为操作数。

# 0.3 Using the XMM registers from inline assembly

从内联汇编使用XMM寄存器

In GCC inline assembly, XMM registers can be accessed using the "x" operand constraint.

在GCC内联汇编中，可以使用"x"操作数约束来访问XMM寄存器。

Example in C:

```txt
double a = 41.;  
asm()  
"addsd %0, %1"  
: "+" (a)  
: "x" (1.)  
:  
7);
```

# 1 Simple 1D loops

简单的一维循环

1.1

```c
void loop(size_t n, double a[n]) {
    for(size_t i=0; i<n-1; ++i) {
        a[i] = a[i+1] / sqrt(2.);
    }
}
```

Write an equivalent function in ASM or inline ASM.

用ASM或内联ASM编写等效函数。

$\rightarrow$  Notice the loop-carried dependence in this code. In the next lab, we will study how to exploit data-level parallelism on similar loops using SIMD (Single-Instruction, Multiple-Data) instructions.

注意这段代码中的循环依赖关系。在下一个实验中，我们将学习如何使用SIMD（单指令多数据）指令在类似的循环中利用数据级并行性。

1.2

Which instruction can be moved out of the loop as an optimization? Using the code in the provided archive, observe the speedup yielded by this change.

哪条指令可以作为优化移出循环？使用提供的代码包，观察这种改变带来的加速效果。

# 2 Reciprocal square root

倒数平方根

The goal of this exercise is to study and compare the different methods that have been used historically to optimize the computation of the reciprocal square root  $\frac{1}{\sqrt{x}}$ . This study will deal with both performance and numerical accuracy aspects. Nowadays, the most simple way to perform it is to use a hardware implementation in form of a dedicated instruction. However, doing so was not possible before such instructions were introduced (SSE was introduced in 1999, for instance).

这个练习的目标是学习和比较历史上用于优化倒数平方根 $\frac{1}{\sqrt{x}}$ 计算的不同方法。这项研究将涉及性能和数值精度两个方面。如今，执行此操作最简单的方法是使用专用指令形式的硬件实现。然而，在引入此类指令之前（例如SSE于1999年引入），这样做是不可能的。

In this exercise, you are given a set of scripts and drivers, which you are to complete with the different algorithm versions. Performance and accuracy measurements are handled by the driver. For more details, have a look at the attached README file.

在这个练习中，给您提供了一套脚本和驱动程序，您需要用不同的算法版本来完成它们。性能和精度测量由驱动程序处理。更多详细信息，请查看附带的README文件。

Note: Before SSE was introduced, FP computations on x86 architectures were often performed using x87 instructions. Even though the methods we are going to study have been made obsolete by SSE, we are still going to use it, as x87 is now mostly deprecated.

注意：在引入SSE之前，x86架构上的浮点计算通常使用x87指令执行。尽管我们将要学习的方法已被SSE所淘汰，但我们仍将使用它，因为x87现在大多已被弃用。

# 2.1 "Naive" approach

"朴素"方法

While x87 did not have an instruction for the reciprocal square root, it did have one for the square root. The "naive method" to compute the reciprocal square root would thus be to first compute the square root, and then its inverse:

虽然x87没有倒数平方根指令，但它确实有平方根指令。因此，计算倒数平方根的"朴素方法"是先计算平方根，然后计算其倒数：

```javascript
float naive(float y) { return 1. / sqrt(x); }
```

Complete the naive function using inline ASM. Make sure to use the sqrtss and divss instructions. Launch the driver to observe the performance and accuracy results.

使用内联ASM完成朴素函数。确保使用sqrtss和divss指令。启动驱动程序以观察性能和精度结果。

$\rightarrow$  Both the square root and division instructions are known for having important latencies, which can make this method inefficient in certain contexts.

平方根和除法指令都因具有重要的延迟而闻名，这可能使该方法在某些情况下效率低下。

# 2.2 Newton-Raphson method

A very general method for approximating roots of real-valued functions is the Newton-Raphson method (or simply Newton method). It states that if  $x_0$  is a satisfying initial guess for a root of  $f(x)$  (that is  $f(x_0) \approx 0$ ), then:

一个非常通用的逼近实值函数根的方法是牛顿-拉弗森方法（或简称牛顿方法）。它指出，如果 $x_0$ 是 $f(x)$ 的根的一个令人满意的初始猜测（即 $f(x_0) \approx 0$），那么：

$$
x _ {1} = x 0 - \frac {f (x _ {0})}{f ^ {\prime} (x _ {0})}
$$

is a better approximation. This method can be applied multiple times and will converge to the exact solution.
是一个更好的近似值。该方法可以多次应用，并将收敛到精确解。

In the case of the reciprocal square root, we can write  $y = \frac{1}{\sqrt{x}}$  such that  $f(y) = \frac{1}{y^2} - x = 0$  is the function on which the Newton method should be applied. This yields, for all  $i$ , that  $f'(y) = -\frac{2}{y^3}$  and thus:
在倒数平方根的情况下，我们可以写成 $y = \frac{1}{\sqrt{x}}$，使得 $f(y) = \frac{1}{y^2} - x = 0$ 是牛顿方法应应用的函数。这为所有 $i$ 带来了 $f'(y) = -\frac{2}{y^3}$，因此：

$$
y _ {i + 1} = \frac {y _ {i} \left(3 - x y _ {i} ^ {2}\right)}{2}
$$

The following code computes an iteration of the Newton-Raphson method, given an  $x$  and an initial guess  $y$ :
随后的代码计算了牛顿-拉弗森方法的一次迭代，给定一个 $x$ 和一个初始猜测 $y$：

```txt
float newton(float x, float y) {
const float threequarters = 1.5f;
x2 = x * 0.5f;
return y * (threequarters - (x2 * y * y));
}
```

Complete the Newton function using inline ASM. You are free to add a second or third iteration of the Newton method. Launch the driver to observe the performance and accuracy results. It will use  $y = 1$ , which is a good approximation when  $x \approx 1$ . How does the accuracy evolve as  $x$  first approaches and then strays away from 1? How do performances compare with the naive approach?
使用内联ASM完成Newton函数。您可以自由添加牛顿方法的第二次或第三次迭代。启动驱动程序以观察性能和精度结果。它将使用 $y = 1$，当 $x \approx 1$ 时，这是一个很好的近似值。当 $x$ 首先接近然后远离1时，精度如何变化？性能与朴素方法相比如何？

# 2.3 Fast inverse square root
快速倒数平方根

Before the introduction of hardware implementations, the fast inverse square root algorithm was the fastest way to compute reciprocal square roots. It also uses one or two iterations of the Newton-Raphson method, but is more known for its clever way of computing a first guess. Here is the C code for it:
在引入硬件实现之前，快速倒数平方根算法是计算倒数平方根的最快方法。它也使用了一到两次牛顿-拉弗森方法的迭代，但更为人所知的是它计算第一个猜测的巧妙方法。以下是它的C代码：

```lisp
float fast(float x) {  
const float threehalfs = 1.5f;  
float x2 = x * 0.5f;  
float y = x;  
long i = *(long *) &y;  
i = 0x5f3759df - (i >> 1); // ???  
y = *(float *) &i;  
y = y * (threehalfs - (x2 * y * y));  
// y = y * (threehalfs - (x2 * y * y));  
return y;  
}
```

Line 6 should be the most surprising one. The idea of this algorithm is to manipulate the floating-point input with bitwise operators, as if it was an integer (line 5). Without going into too much details, 0x5f3759df is a magic number which was chosen because it happened to give the best overall approximation when converting the value back to a float. One way of finding such constant is through a trial-and-error process (ie. testing many possible values and choosing the best one).<sup>1</sup>
第6行应该是最令人惊讶的一行。该算法的思想是使用按位运算符操作浮点输入，就像它是一个整数一样（第5行）。不深入细节，0x5f3759df是一个神奇的数字，因为在将值转换回浮点数时，它恰好给出了最佳的整体近似值。找到这样的常数的一种方法是通过反复试验的过程（即测试许多可能的值并选择最佳值）。<sup>1</sup>

Complete the fast function using inline ASM. You are free to add a second or third iteration of the Newton method. Launch the driver to observe the performance and accuracy results. Conclude on the validity of the initial guess provided by this method.
使用内联ASM完成快速函数。您可以自由添加牛顿方法的第二次或第三次迭代。启动驱动程序以观察性能和精度结果。总结该方法提供的初始猜测的有效性。