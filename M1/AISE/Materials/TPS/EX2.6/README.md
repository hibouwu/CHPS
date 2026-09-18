# 练习 6 (Exercice 6)

## 题目描述

> Reprenez le programme de l'exercice précédent et ajoutez un traitement spécial dans le cas où la commande est terminée par le caractère &.
> 基于上一个练习的程序，添加对以 `&` 字符结尾的命令的特殊处理。

来源: [felsoci.sk/aise/practice.html](https://felsoci.sk/aise/practice.html#shell-detach)

## 解析与纠正 (Éléments de correction)

我们修改了初始实现（参见 [EX2.5](../EX2.5/README.md)）如下。

在 `while` 循环的步骤 3 和 4 之间，我们添加了对命令行末尾是否存在 `&` 字符的检测（参见变量 `detach`）。

如果 `&` 字符确实出现在用户输入的命令行的末尾，我们必须将其考虑在内，但我们不能将其保留，因为 `wordexp` 函数将 `&` 视为非法字符。

然后，我们要对 `while` 循环的步骤 7 进行条件化。程序仅当 `&` 字符**不**存在于相应命令行的末尾时，才等待当前命令的终止。

最后，我们添加了最后一个步骤，该步骤仅在通过 `exit` 命令退出 shell 时触发，包括等待所有作为后台任务启动的命令的终止。

为了能够执行这最后一步，我们必须计算这些命令的数量。实际上，调用系统原语 `wait` 只允许等待单个子进程。因此，必须为每个对应于后台任务的子进程调用 `wait`。

## 代码详解

本练习在基本的 Shell 实现（练习 5）上增加了后台任务支持：

1. **检测 `&`**:
    - 使用 `strchr(line, '&')` 查找命令行中是否有 `&`。
    - 判断 `&` 是否位于命令末尾（或后面仅跟空格/结束符），若是则标记为 `detach`。
    - 将 `&` 替换为 `\0`，以免 `wordexp` 解析出错。

2. **后台执行**:
    - 如果 `detach` 为真，父进程**不调用** `wait(NULL)`，而是让子进程在后台运行，并增加 `background` 计数器。
    - 如果 `detach` 为假，父进程像往常一样调用 `wait(NULL)` 等待子进程结束。

3. **退出处理**:
    - 当用户输入 `exit` 时，程序会在退出前通过循环 `for(int i = 0; i < background; i++) wait(NULL);` 等待所有后台任务结束，避免产生僵尸进程。
