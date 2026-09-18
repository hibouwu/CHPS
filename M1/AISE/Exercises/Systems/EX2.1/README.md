# 练习 1 (Exercice 1)

## 题目描述

> Écrivez un programme qui affiche la taille du terminal courant et qui supporte le redimensionnement de la fenêtre, affichant alors dynamiquement la nouvelle taille.
> 编写一个程序，显示当前终端的大小，并支持窗口大小调整，动态显示新的大小。
> Le programme suivant vous montre comment lire la taille du terminal courant.
> 下面的程序向您展示了如何读取当前终端的大小。
>
> ```c
> #include <sys/ioctl.h>
> #include <stdio.h>
>
> int main(void) {
>   struct winsize w;
>   ioctl(0, TIOCGWINSZ, &w);
>   printf("Lignes : %d\n", w.ws_row);
>   printf("Colonnes : %d\n", w.ws_col);
>   return 0;
> }
> ```
>
> En voici un exemple de sortie standard :
> 标准输出示例如下：
>
> ```txt
> Lignes : 18848 
> Colonnes : 22290
> ```

来源: [felsoci.sk/aise/practice.html](https://felsoci.sk/aise/practice.html#winch)

## 代码详解

该程序主要演示了如何处理 Unix 信号 `SIGWINCH` (Window Change)。

1. **获取终端大小**:
    使用 `ioctl(0, TIOCGWINSZ, &w)` 系统调用。其中 `0` 是标准输入的伪文件描述符，`TIOCGWINSZ` 是获取窗口大小的请求码，结果存入 `struct winsize` 结构体。

2. **信号处理**:
    - `sigaction` 用于注册信号处理函数。
    - `SIGWINCH` 是当终端窗口大小改变时发送给前台进程组的信号。
    - 我们在 `main` 函数中注册了 `report_size` 函数来处理 `SIGWINCH`。

3. **主循环**:
    `while(1) {}` 保持程序运行，等待信号触发。
