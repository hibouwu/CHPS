# Architectures Parallèles

# TP1: x86_64 ASSEMBLY - BASICS

# UVSQ - M1 CHPS

The goal of this first lab is to get you familiar with the basics of x86_64 assembly. You will be provided with an archive containing code to complete for each question.
这个第一个实验的目标是让您熟悉x86_64汇编的基础知识。您将获得一个包含每个问题要完成的代码的档案。

# 0 Cheatsheet 备忘单

# 0.1 Registers 寄存器

The following table lists the "general purpose" registers (GPRs) of the x86_64 architecture, as well as some special registers:
随后的表格列出了x86_64架构的“通用寄存器”（GPR）以及一些特殊寄存器：

<table><tr><td>64 bits</td><td>Comment</td><td>Volatile</td><td>32 bits</td><td>16 bits</td><td>8 bits</td></tr><tr><td>rax</td><td>Functions&#x27; return values (by convention)</td><td>✓</td><td>eax</td><td>ax</td><td>al</td></tr><tr><td>rbx</td><td></td><td></td><td>ebx</td><td>bx</td><td>bl</td></tr><tr><td>rcx</td><td></td><td>✓</td><td>ecx</td><td>cx</td><td>cl</td></tr><tr><td>rdx</td><td></td><td>✓</td><td>edx</td><td>dx</td><td>dl</td></tr><tr><td>rsi</td><td></td><td>✓</td><td>esi</td><td>si</td><td>sil</td></tr><tr><td>rdi</td><td></td><td>✓</td><td>edi</td><td>di</td><td>dil</td></tr><tr><td>rbp</td><td>Base pointer (base of the stack)</td><td></td><td>ebp</td><td>bp</td><td>bpl</td></tr><tr><td>rsp</td><td>Stack pointer (top of the stack)</td><td></td><td>esp</td><td>sp</td><td>spl</td></tr><tr><td>r8</td><td></td><td>✓</td><td>r8d</td><td>r8w</td><td>r8b</td></tr><tr><td>r9</td><td></td><td>✓</td><td>r9d</td><td>r9w</td><td>r9b</td></tr><tr><td>r10</td><td></td><td>✓</td><td>r10d</td><td>r10w</td><td>r10b</td></tr><tr><td>r11</td><td></td><td>✓</td><td>r11d</td><td>r11w</td><td>r11b</td></tr><tr><td>r12</td><td></td><td></td><td>r12d</td><td>r12w</td><td>r12b</td></tr><tr><td>r13</td><td></td><td></td><td>r13d</td><td>r13w</td><td>r13b</td></tr><tr><td>r14</td><td></td><td></td><td>r14d</td><td>r14w</td><td>r14b</td></tr><tr><td>r15</td><td></td><td></td><td>r15d</td><td>r15w</td><td>r15b</td></tr><tr><td>rip</td><td>Address of the next instruction to be executed</td><td rowspan="2">N/A N/A</td><td rowspan="2"></td><td rowspan="2"></td><td rowspan="2"></td></tr><tr><td>rflags</td><td>Contains flags set by some instructions</td></tr></table>

Depending on the size of the manipulated types, these registers can be accessed in 64, 32, 16 or 8 bits modes. These variants correspond to the lower parts of the register:
依赖于操作类型的大小，可以以 64、32、16 或 8 位模式访问这些寄存器。这些变体对应于寄存器的低部分：

![](https://cdn-mineru.openxlab.org.cn/result/2025-10-03/25872df7-ebff-4cbd-8ab4-601ec3990560/2a50151adc8cc61285b55fbd242aaca82e25b32457db43bc03a6f850d235a76b.jpg)

Besides having specific functions for some of them (see the "Comment" column), GPRs can, by convention, be of two different types:
此外，除了它们的一些特定功能（见“评论”栏），GPR 按惯例可以分为两种不同的类型：

- caller-saving: also called volatile, these registers are used to save temporary values that do not need saving between function calls.
  调用者保存：也称为易失性，这些寄存器用于保存函数调用之间不需要保留的临时值。

- callee-saved: also called non-volatile, these registers are used to save values that must be preserved over function calls. A function that uses them needs to backup and restore their original values.
  被调用者保存：也称为非易失性，这些寄存器用于保存必须在函数调用中保留的值。使用它们的函数需要备份并恢复其原始值。

# 0.2 Syntaxes 语法

For historical reasons, there are two syntaxes in x86 assembly: AT&T and Intel. Here are the differences between them:
由于历史原因，x86 汇编中有两种语法：AT&T 和 Intel。以下是它们之间的区别：

## Parameters order 参数顺序

AT&T uses the "sources  $\rightarrow$  destination" scheme.
AT&T 使用“源 $\rightarrow$ 目标”方案。

Example: "movq $42, %rax" stores the value 42 in the rax register.
示例：“movq $42, %rax”将值 42 存储在 rax 寄存器中。

Intel uses the "destination  $\leftarrow$  sources" scheme.
Intel 使用“目标 $\leftarrow$ 源”方案。

Example: "mov rax, 42" stores the value 42 in the rax register. Note how this instruction would not make sense in AT&T syntax.
示例：“mov rax, 42”将值 42 存储在 rax 寄存器中。请注意，这条指令在 AT&T 语法中没有意义。

## Instruction suffixes 指令后缀

AT&T uses suffixes on instruction mnemonics, depending on the size of operands (q for quadwords (64 bits), l for long (32 bits), w for words (16 bits), b for byte (8 bits)).
AT&T 在指令助记符上使用后缀，具体取决于操作数的大小（q 表示四字（64 位），l 表示长（32 位），w 表示字（16 位），b 表示字节（8 位））。

Example: "movl $42, %eax" stores the value 42 in the 32-bits wide eax register (as opposed to the previous example using the 64-bits version of the register).
示例：“movl $42, %eax”将值 42 存储在 32 位宽的 eax 寄存器中（与前一个使用寄存器 64 位版本的示例相反）。

Intel does not use suffixes on mnemonics.
Intel 在助记符上不使用后缀。

## Operands prefixes 操作数前缀

In AT&T syntax, immediates values are prefixed with a "\$" and registers are prefixed with a "%".
AT&T 语法中，立即数值以前缀 “$”，寄存器以前缀 “%” 表示。

In Intel syntax, there are no prefixes on instruction operands.
Intel 语法中，指令操作数没有前缀。

## Addresses computation 地址计算

AT&T uses the following syntax: movq (%rbx, %rcx, 8), %rax
AT&T 使用以下语法：movq (%rbx, %rcx, 8), %rax

Intel uses the following syntax: mov rax, [rbx+rcx*8]
Intel 使用以下语法：mov rax, [rbx + rcx * 8]

(see the next section for more details on address computation in memory operands)
（有关内存操作数中地址计算的更多详细信息，请参见下一节）

By convention, this document uses the Intel syntax.
按惯例，本文档使用 Intel 语法。

# 0.3 Instructions 指令

The following table lists some basic instructions:
下表列出了一些基本指令：

<table><tr><td>Instruction</td><td>Description</td><td>C equivalent</td></tr><tr><td>add rax, rbx</td><td>Integer addition 整数加法</td><td>rax += rbx;</td></tr><tr><td>sub rax, rbx</td><td>Integer subtraction 整数减法</td><td>rax -= rbx;</td></tr><tr><td>imul rax, rbx</td><td>Integer multiplication 整数乘法</td><td>rax *= rbx;</td></tr><tr><td>mov rax, rbx</td><td>Copy content of a register into another 拷贝一个寄存器的内容到另一个寄存器</td><td>rax = rbx;</td></tr><tr><td>mov rax, [rbx]</td><td>Load value from memory to a register 从内存加载值到寄存器</td><td>rax = *rbx;</td></tr><tr><td>mov [rax], rbx</td><td>Store value from a register into memory 将寄存器中的值存储到内存</td><td>*rax = rbx;</td></tr><tr><td>cmp rax, rbx</td><td>Compare operands and set the flag register 比较操作数并设置标志寄存器</td><td>rax == rbx</td></tr><tr><td>je addr</td><td>Read the flag register and jump if equal 读取标志寄存器并在相等时跳转</td><td></td></tr><tr><td>jne addr</td><td>Read the flag register and jump if non-equal 读取标志寄存器并在不相等时跳转</td><td></td></tr><tr><td>jmp addr</td><td>Jump unconditionally 无条件跳转</td><td></td></tr><tr><td>push rax</td><td>Push an element on top of the stack 将元素压入栈顶</td><td></td></tr><tr><td>pop</td><td>Pop the element on top of the stack 弹出栈顶元素</td><td></td></tr><tr><td>call f</td><td>Call a function 调用函数</td><td>f(...);</td></tr><tr><td>ret</td><td>Return from a function 从函数返回</td><td>return ...;</td></tr></table>

A more complete list of x86 instructions can be found at https://www.felixcloutier.com/x86/.
更完整的 x86 指令列表可以在 https://www.felixcloutier.com/x86/ 找到。

Instruction operands can be of the following types:
指令操作数可以是以下类型：

<table><tr><td>Operand type</td><td>Examples</td><td>C equivalent</td></tr><tr><td rowspan="2">Immediate 立即数</td><td>mov rax, 42</td><td>rax = 42;</td></tr><tr><td>imul r8, 2</td><td>r8 *= 2;</td></tr><tr><td rowspan="2">Register 寄存器</td><td>mov rax, rbx</td><td>rax = rbx;</td></tr><tr><td>add r9, r10</td><td>r9 += r10;</td></tr><tr><td rowspan="2">Memory 内存</td><td>mov [rbx], r12</td><td>*rbx = r12;</td></tr><tr><td>mov rax, [r11+16]</td><td>rax = *(r11+16);</td></tr></table>

Moreover, memory operands can be addressed in multiple ways (non exhaustive list, addresses are computed in bytes):
此外，内存操作数可以通过多种方式寻址（非详尽列表，地址以字节为单位计算）：

<table><tr><td>Addressing form</td><td>Example</td></tr><tr><td>Base register</td><td>mov rax, [rbx]</td></tr><tr><td>Base register + displacement</td><td>mov rax, [rbx+8]</td></tr><tr><td>Base register + Index register</td><td>mov rax, [rbx+r8]</td></tr><tr><td>Base register + Index register * scaling factor</td><td>mov rax, [rbx+r8*8]</td></tr></table>

Finally, the address operand of the jump instructions corresponds to the address of the instruction to jump to. In practice, it is easier to define labels in the following way:
最后，跳转指令的地址操作数对应于要跳转到的指令的地址。实际上，更容易以以下方式定义标签：

```txt
je mylabel 
[. . .] 
mylabel: 
mov . . . , . .
```

If the rflags register is set to equal, execution will jump to the mov instruction below mylabel.
如果 rflags 寄存器设置为相等，执行将跳转到 mylabel 下方的 mov 指令。

# 0.4 A practical guide to writing assembly 一个实用的汇编编写指南

# 0.4.1 Inline ASM 内联汇编

One of the simplest ways to write assembly is to use inline ASM, which is an extension supported by most modern compilers. It allows writing assembly snippets directly from a high level language (such as C).
编写汇编的一种最简单的方法是使用内联 ASM，这是大多数现代编译器支持的扩展。它允许直接从高级语言（如 C）编写汇编代码片段。

When writing inline ASM, up to four sections can be specified (or left empty if not needed):
编写内联 ASM 时，可以指定最多四个部分（如果不需要，可以留空）：

- the ASM template section, containing the assembly code to generate in a string. This is the only mandatory section.
  ASM 模板部分，包含要生成的汇编代码字符串。这是唯一的强制性部分。
- the outputs section, indicating in which C variables the result(s) should be stored.
  输出部分，指示结果应存储在哪些 C 变量中。
- the inputs section, indicating which C variable should be passed to the ASM snippet.
  输入部分，指示哪些 C 变量应传递给 ASM 代码段。
- the clobber sections, to preserve values of registers that are modified by the ASM snippet, and that are use neither as input or output.
  破坏部分，用于保存 ASM 代码段修改的寄存器值，这些寄存器既不作为输入也不作为输出。

These sections are separated by a ":".
这些部分由“:”分隔。

Inputs and outputs can have multiple "constraints":
输入和输出可以有多个“约束”：

- "r" indicates that the operand is neither an input or an output and will be affected to any GPR.
  “r” 表示操作数既不是输入也不是输出，并且会被分配到任意 GPR。
- "=" indicates that the operand is only an output and will be affected to any GPR.
  “=” 表示操作数只是输出，并且会被分配到任意 GPR。
- "+" indicates that the operand is both an output and an input, and will be affected to any GPR.
  “+” 表示操作数既是输出又是输入，并且会被分配到任意 GPR。

## Example in C 示例（C 语言）

```c
int a = 1; int b = 2;  
asm( 
    "add %0, %1; " 
    : "+r" (a)  // Output section (%0 = a). Notice how a is also an input, 
                // but is listed in the output section. 
    : "r" (b)   // Input section (%1 = b) : 
                // Clobber section (empty) 
); 
// From there, a == 3
```

Operands can also be given names. This is especially useful when the ASM listings become complex.
操作数也可以命名。当 ASM 列表变得复杂时，这尤其有用。

## Example in C 示例（C 语言）

```c
int a = 1;  
asm( 
    "mov r8, 2;"  
    "add %[foo], r8;"  
    : [foo]"+r" (a) // Output section (%[foo] = a)  
    :               // Input section (empty)  
    : "r8"          // Clobber section  
    );  
    // From there, a ==3  
    // Also the original value of r8 is preserved,  
    // preventing later issues in the code.
```

By default, the GCC compiler will use AT&T syntax. Intel syntax can be used by adding the -masm=intel flag.
默认情况下，GCC 编译器将使用 AT&T 语法。通过添加 -masm=intel 标志可以使用 Intel 语法。

# 0.4.2 Compiling ASM files 编译 ASM 文件

It is also possible to compile files entirely written in assembly using GCC:
也可以使用 GCC 编译完全用汇编编写的文件：

gcc [-masm=intel] -c foo.s

... where foo.S is the file containing the assembly source. Once again, AT&T syntax is the default. However, this is often more complex than writing inline assembly, because this requires handling the calling convention. This is why we are going to use inline ASM in these labs.
...其中 foo.S 是包含汇编源代码的文件。再次强调，AT&T 语法是默认的。然而，这通常比编写内联汇编更复杂，因为这需要处理调用约定。这就是为什么我们将在这些实验中使用内联 ASM 的原因。

# 0.4.3 Reading compiler generated assembly 阅读编译器生成的汇编

If you are stuck on a question for instance, it can be helpful to have a look at the assembly generated by the compiler:
如果您在某个问题上遇到困难，查看编译器生成的汇编代码可能会有所帮助：

gcc [-masm=intel] -S foo.c -o foo.s

It is also possible to disassemble a binary using the objdump command and the -d flag:
也可以使用 objdump 命令和 -d 标志反汇编二进制文件：

objdump -d foo

If the binary was built with debug info, it is possible to match the assembly with source lines and get an output that is easier to read with the -S flag:
如果二进制文件是使用调试信息构建的，则可以使用 -S 标志将汇编与源代码行匹配，并获得更易于阅读的输出：

gcc -g -o foo foo.c

objdump -d [-M intel] -S foo

# 1 Dot product 点乘

# 1.1 2 dimensions dot product 2 维点乘

The following code computes the dot product between two vectors  $a = (a_x, a_y)$  and  $b = (b_x, b_y)$ , represented by four signed integer values:
下列代码计算两个向量 $a = (a_x, a_y)$ 和 $b = (b_x, b_y)$ 之间的点积，由四个有符号整数值表示：

```c
#include<stdio.h> 
int64_t dotprod_2d(int64_t ax, int64_t ay, int64_t bx, int64_t by){
    return ax*bx + ay*by;   
}
```

Write an equivalent function in ASM or inline ASM.
写一个等效的 ASM 或内联 ASM 函数。

```c
#include<stdio.h> 
int64_t dotprod_2d(int64_t ax, int64_t ay, int64_t bx, int64_t by){
    int64_t result;
    asm(
        "imul %[bx], %[ax];"
        "imul %[by], %[ay];"
        "add %[ay], %[ax];"
        : [result]"=r"(result)
        : [ax]"r"(ax), [ay]"r"(ay), [bx]"r"(bx), [by]"r"(by)
    );
    return result;
}
```

# 1.2 Generalization to  $n$  dimensions 推广到 $n$ 维

The following code computes the dot product between two vectors  $a = (a_{1},\dots,a_{n})$  and  $b = (b_{1},\dots,b_{n})$  of size  $n$ , represented by two arrays of signed integers:
下列代码计算大小为 $n$ 的两个向量 $a = (a_{1},\dots,a_{n})$ 与 $b = (b_{1},\dots,b_{n})$ 的点积，这两个向量由两个有符号整数数组表示：

```c
int64_t dotprod_nd(size_t n, int64_t a[n], int64_t b[n]) {
    int64_t sum = 0;
    for (size_t i = 0; i < n; ++i) {  
        sum += a[i] * b[i];  
    }
    return sum;
}
```

Write an equivalent function in ASM or inline ASM.
写一个等效的 ASM 或内联 ASM 函数。

Tip: In assembly, loops are implemented using a conditional jump instruction to a label placed at the top of the loop body.
提示：在汇编中，循环通过条件跳转指令跳回到循环体顶部的标签来实现。

# 2 Detecting opposite integer signedness 检测整数符号是否相反

# 2.1 Naive approach 朴素方法

The following code returns true if a and b have opposite signs, and false otherwise:
下面的代码在 a 和 b 符号相反时返回 true，否则返回 false：

```c
#include<stdbool.h>   
bool opposite_signs(int64_t a, int64_t b) { 
    if((a>=0 && b<0) || (a<0 && b>=0)) { 
        return true; 
    } else { 
        return false; 
    }
}
```

Write an equivalent function in ASM or inline ASM.
写一个等效的 ASM 或内联 ASM 函数。

# 2.2 [Bonus] Branchless approach 【加分】无分支方法

Using ONLY bitwise operators, write an equivalent and branchless function in ASM or inline ASM. This will require instructions that are not given in this document.
只使用按位运算符，在 ASM 或内联 ASM 中编写一个等效且无分支的函数。这将需要使用本文档未涵盖的指令。

# 3 Searching for the minimum of an array 寻找数组最小值

The following code finds and returns the minimum value of an array of signed integers of size  $n$ :
下面的代码会找到并返回大小为 $n$ 的有符号整数数组的最小值：

```c
int64_t array_min(size_t n, int64_t array[n]) { 
    if(n == 0) return 0; 
    int64_t min = array[0]; 
    for(size_t i=1; i<n; ++i) { 
        if(array[i] < min) min = array[i]; 
    } return min; 
}
```

Write an equivalent function in ASM or inline ASM.
写一个等效的 ASM 或内联 ASM 函数。

# 4 Fibonacci sequence 斐波那契数列

The Fibonacci sequence is defined as :
斐波那契数列定义如下：

$$
\left\{ \begin{array}{l} f _ {0} = 1 \\ f _ {1} = 1 \\ f _ {i} = f _ {i - 1} + f _ {i - 2} \quad \text {if  } i \geq 2 \end{array} \right.
$$

The following code computes the  $n$ -th element of the Fibonacci sequence using the iterative method:
下面的代码使用迭代方法计算斐波那契数列的第 $n$ 项：

```c
uint64_t fibonacci(uint64_t n) {
    if(n <= 1)
        return 1;
    uint64_t curr; uint64_t prev1 = 1; uint64_t prev2 = 1;
    for (uint64_t i = 1; i < n; ++i) {
        curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return curr;
}
```

Write an equivalent function in ASM or inline ASM.
写一个等效的 ASM 或内联 ASM 函数。
