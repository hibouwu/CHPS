# 练习 4 (Exercice 4)

## 题目描述

> Implémentez (sans rentrer dans la complexité des arguments) un programme qui effectue la même opération que la commande echo et un programme qui effectue la même opération que la commande kill.
> 实现一个程序（无需涉及复杂的参数），执行与 echo 命令相同的操作，以及一个执行与 kill 命令相同操作的程序。
>
> Prenez également le temps de comprendre le rôle de ce programme et d'expérimenter ses arguments.
> 同时花时间理解该程序的作用并对其参数进行实验。

来源: [felsoci.sk/aise/practice.html](https://felsoci.sk/aise/practice.html#args)

## 解析与纠正 (Éléments de correction)

`echo` 命令，顾名思义，在标准输出上重现传递给它的参数，并用空格分隔。输出以换行符结束。这是使用 `printf` 库函数对此命令的简单实现。

```c
/* Implementation of echo */
#include <stdio.h>
int main(int argc, char ** argv) {
    if(argc < 2) {
        return 0;
    }
    for(int i = 1; i < argc; i++) {
        printf("%s", argv[i]);
        if(i + 1 < argc) {
            printf(" ");
        }
    }
    printf("\n");
    return 0;
}
```

`kill` 命令的作用是向进程发送信号。它的第一个参数是强制性的，表示接收进程的标识符 (PID)。第二个参数是可选的，表示要发送的信号代码（默认为 `SIGHUP`）。这是使用 `kill` 库函数对此命令的简单实现。

```c
/* Implementation of kill */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
int main(int argc, char ** argv) {
    if(argc < 2) {
        errno = EINVAL;
        perror("aucun identifiant de processus n'a été spécifié");
        return 1;
    }
    pid_t target = atoi(argv[1]);
    int signal = argc > 2 ? atoi(argv[2]) : SIGHUP;
    if(kill(target, signal) < 0) {
        perror("envoi de signal");
        return 1;
    }
    printf("signal %d envoyé au processus %d\n", signal, target);
    return 0;
}
```

## 代码详解

本练习要求实现 `echo` 和 `kill` 的简化版本。

1. **Echo 实现**:
    - 遍历 `argv` 数组（从索引 1 开始）。
    - 打印每个参数，并在参数之间打印空格。
    - 最后打印换行符。

2. **Kill 实现**:
    - 接收 PID 作为第一个参数 (`argv[1]`)。
    - 可选地接收信号编号作为第二个参数 (`argv[2]`)，默认为 `SIGHUP`。
    - 使用 `kill(target, signal)` 系统调用发送信号。
    - 处理错误情况（如参数不足、发送失败）。
