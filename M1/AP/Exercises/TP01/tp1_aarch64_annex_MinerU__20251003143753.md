# Architectures Parallèles

# TP1 ANNEX: AARCH64 CHEATSHEET

# UVSQ - M1 CHPS

Some of you may have an ARM processor on your machine (most likely Apple Silicon). This annex document is an AArch64 version of the introductory cheatsheet.
你们中有些人的机器上可能有 ARM 处理器（最有可能是 Apple Silicon）。本附件文档是 AArch64 版本的介绍性备忘单。


# 0 Cheatsheet 备忘单

# 0.1 Registers 寄存器

The following table lists the "general purpose" registers (GPRs) of the AArch64 architecture:
随后的表格列出了 AArch64 架构的“通用寄存器”（GPR）：

<table><tr><td>64 bits</td><td>Comment</td><td>Volatile</td><td>32 bits</td></tr><tr><td>x0</td><td>Functions arguments and return</td><td>✓</td><td>w0</td></tr><tr><td>x1</td><td>Functions arguments and return</td><td>✓</td><td>w1</td></tr><tr><td>x2</td><td>Functions arguments and return</td><td>✓</td><td>w2</td></tr><tr><td>x3</td><td>Functions arguments and return</td><td>✓</td><td>w3</td></tr><tr><td>x4</td><td>Functions arguments and return</td><td>✓</td><td>w4</td></tr><tr><td>x5</td><td>Functions arguments and return</td><td>✓</td><td>w5</td></tr><tr><td>x6</td><td>Functions arguments and return</td><td>✓</td><td>w6</td></tr><tr><td>x7</td><td>Functions arguments and return</td><td>✓</td><td>w7</td></tr><tr><td>x8</td><td>Functions return for &gt; 128 bits types, otherwise scratch</td><td>~</td><td>w8</td></tr><tr><td>x9</td><td></td><td>✓</td><td>w9</td></tr><tr><td>x10</td><td></td><td>✓</td><td>w10</td></tr><tr><td>x11</td><td></td><td>✓</td><td>w11</td></tr><tr><td>x12</td><td></td><td>✓</td><td>w12</td></tr><tr><td>x13</td><td></td><td>✓</td><td>w13</td></tr><tr><td>x14</td><td></td><td>✓</td><td>w14</td></tr><tr><td>x15</td><td></td><td>✓</td><td>w15</td></tr><tr><td>x16</td><td></td><td>✓</td><td>w16</td></tr><tr><td>x17</td><td></td><td>✓</td><td>w17</td></tr><tr><td>x18</td><td></td><td>✓</td><td>w18</td></tr><tr><td>x19</td><td></td><td></td><td>w19</td></tr><tr><td>x20</td><td></td><td></td><td>w20</td></tr><tr><td>x21</td><td></td><td></td><td>w21</td></tr><tr><td>x22</td><td></td><td></td><td>w22</td></tr><tr><td>x23</td><td></td><td></td><td>w23</td></tr><tr><td>x24</td><td></td><td></td><td>w24</td></tr><tr><td>x25</td><td></td><td></td><td>w25</td></tr><tr><td>x26</td><td></td><td></td><td>w26</td></tr><tr><td>x27</td><td></td><td></td><td>w27</td></tr><tr><td>x28</td><td></td><td></td><td>w28</td></tr><tr><td>x29</td><td>Frame pointer</td><td></td><td>w29</td></tr><tr><td>x30</td><td>Functions return address (do not use)</td><td></td><td>w30</td></tr></table>

Depending on the size of the manipulated types, these registers can be accessed in 64 or 32 bits modes. The 32 bits variant corresponds to the lower part of the register:
根据操作类型的大小，可以以 64 或 32 位模式访问这些寄存器。 32 位变体对应于寄存器的低部分：

![](https://cdn-mineru.openxlab.org.cn/result/2025-10-03/00bbc5e4-6f2a-4f79-b339-77ccd2757afb/e2a79a5176535efd6637f3d7d80016ecf90da016260cdeeeb41f8e02d1c37f9a.jpg)

# 0.2 Syntax

Similarly to x86's Intel syntax, AArch 64 uses the "destination  $\leftarrow$  sources" scheme.

Example: "mov rax, #42" stores the value 42 in the rax register. Note how this instruction would not make sense in Intel AT&T syntax.

Moreover, immediate operands are preceded by a  $\#$  , and memory operands are put in brackets []

# 0.3 Instructions

The following table lists some basic instructions:

<table><tr><td>Instruction</td><td>Description</td><td>C equivalent</td></tr><tr><td>add x0, x1, x2</td><td>Integer addition</td><td>x0 = x1 + x2;</td></tr><tr><td>sub x0, x1, x2</td><td>Integer subraction</td><td>x0 = x1 - x2;</td></tr><tr><td>mul x0, x1 ,x2</td><td>Integer multiplication</td><td>x0 = x1 * x2;</td></tr><tr><td>mov x0, x1</td><td>Copy content of a register into another</td><td>x0 = x1;</td></tr><tr><td>ldr x0, [x1]</td><td>Load value from memory to a register</td><td>x0 = *x1;</td></tr><tr><td>str [x0], x1</td><td>Store value from a register into memory</td><td>*x0 = x1;</td></tr><tr><td>cmp x0, x1</td><td>Compare operands and set the flag register</td><td>x0 == x1</td></tr><tr><td>b.eq addr</td><td>Read the flag register and jump if equal</td><td></td></tr><tr><td>b.ne</td><td>Read the flag register and jump if non-equal</td><td></td></tr><tr><td>b addr</td><td>Jump unconditionally</td><td></td></tr></table>

A more complete list of AArch64 instructions can be found at https://developer.arm.com/documentation/ddi0602/2025-09/Base-Instructions.

Instruction operands can be of the following types:

<table><tr><td>Operand type</td><td>Examples</td><td>C equivalent</td></tr><tr><td rowspan="2">Immediate</td><td>mov x0, #42</td><td>x0 = #42;</td></tr><tr><td>mul x0, x0, #2</td><td>x0 *= 2;</td></tr><tr><td rowspan="2">Register</td><td>mov x0, x1</td><td>x0 = x1;</td></tr><tr><td>add x0, x1, x1</td><td>x0 += x1 + x1;</td></tr><tr><td rowspan="2">Memory</td><td>str [x0], x1</td><td>*x0 = x1;</td></tr><tr><td>mov x0, [x1, #16]</td><td>x0 = *(x1+16);</td></tr></table>

Finally, the address operand of the break instructions corresponds to the address of the instruction to jump to. In practice, it is easier to define labels in the following way:

```txt
b.eq mylabel [. . .] mylabel: mov . . .
```

If the flag register is set to equal, execution will jump to the mov instruction below mylabel.