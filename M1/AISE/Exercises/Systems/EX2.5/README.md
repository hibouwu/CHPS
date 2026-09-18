# 练习 5 (Exercice 5)

## 题目描述

> Écrivez un programme qui :
> 编写一个程序，该程序：
>
> 1. attend une ligne (une commande) sur l'entrée standard (vous pouvez utiliser la fonction de librairie getline);
>    在标准输入上等待一行（一个命令）（您可以使用库函数 getline）；
>
> 2. la décompose en mots séparés par des espaces;
>    将其分解为用空格分隔的单词；
>
> 3. recherche le premier mot dans le PATH;
>    在 PATH 中搜索第一个单词；
>
> 4. exécute cette commande par le biais de la primitive système execv (ou une de ses variantes);
>    通过系统原语 execv（或其变体之一）执行该命令；
>
> 5. revient au point 1.
>    返回第 1 点。
>
> Félicitations, vous avez écrit un shell !
> 恭喜，你写了一个 shell！

来源: [felsoci.sk/aise/practice.html](https://felsoci.sk/aise/practice.html#shell)

## 解析与纠正 (Éléments de correction)

祝贺你，你已经写了一个 Shell！

我们对 Shell 的实现归结为一个 `while` 循环，只有当用户输入 `exit` 命令时程序才会退出。在这个循环的每一轮中，程序：

1. 显示命令提示符（参见宏 `PROMPT`）；
2. 等待直到用户在标准输入上输入一行命令行，程序使用 `getline` 函数将其检索到字符串 `line` 中；
3. 通过将位于 `line` 最后位置的换行符 `\n` 替换为字符串结束符 `\0` 来去除它；
4. 调用 `wordexp` 函数（参见 `man wordexp`）以在将组成命令行的单词放入单独的字符串（参见表 `expansion.we_wordv`）之前，评估对环境变量的任何引用和嵌套命令的结果；
5. 如果第一个单词是 `exit`，则退出 `while` 循环；
6. 利用系统原语 `fork` 启动一个子进程来执行用户输入的命令；
7. 利用系统原语 `wait` 等待此命令的终止。

使用 `wordexp` 函数还有其他替代方法。例如，可以使用 `strtok` 函数将字符串分割成单个单词（参见 `man strtok`）。但是，`wordexp` 函数还允许我们评估用户输入的命令行中可能存在的对环境变量和嵌套命令结果的引用。

## 代码详解

本练习是一个简单的 Shell 实现。

1. **用户输入读取**:
    使用 `getline` 读取用户输入的整行命令。

2. **命令解析与扩展**:
    使用 `wordexp` 函数。
    - 它可以将字符串分割成参数列表（类似 shell 的分割）。
    - 它还可以扩展环境变量（如 `$HOME`）和通配符。
    - 结果存储在 `wordexp_t` 结构体中，`we_wordv` 成员即为参数数组 (argv)。

3. **内建命令**:
    检查第一个参数是否为 `exit`。如果是，则退出循环。

4. **命令执行**:
    - `fork()` 创建子进程。
    - **子进程**: 调用 `execvp(argv[0], argv)` 执行命令。`execvp` 会自动在 `PATH` 环境变量指定的目录中查找可执行文件。
    - **父进程**: 调用 `wait(NULL)` 等待子进程结束。

5. **资源清理**:
    使用 `free` 释放 `getline` 分配的内存，使用 `wordfree` 释放 `wordexp` 分配的内存。
