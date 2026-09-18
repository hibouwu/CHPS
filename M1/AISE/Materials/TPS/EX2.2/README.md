# 练习 2 (Exercice 2)

## 题目描述

> Écrivez un programme qui lance un processus fils et lui envoie un signal toutes les 3 secondes.
> 编写一个程序，启动一个子进程，并每 3 秒向其发送一个信号。
>
> Le processus fils devra capturer ce signal, incrémenter un compteur et afficher sa valeur sur sa sortie standard.
> 子进程必须捕获该信号，增加计数器，并将其值显示在标准输出上。
>
> Enfin, en cas d'interruption (réception du signal SIGINT) du processus parent, le processus fils sera également interrompu par le signal SIGINT.
> 最后，如果父进程被中断（接收到 SIGINT 信号），子进程也将通过 SIGINT 信号被中断。

来源: [felsoci.sk/aise/practice.html](https://felsoci.sk/aise/practice.html#sigalrm)

## 解析与纠正 (Éléments de correction)

除了主函数 `main` 之外，通过程序还包含另外三个作为信号处理程序的函数：

1. `increment`，它递增一个全局计数器（参见变量 counter）并显示其当前值；
2. `poke`，它向子进程（其标识符位于全局变量 child 中）发送一个信号（这里我们选择了 `SIGUSR1`），并设置一个 3 秒的计时器；
3. `interrupt`，它向子进程发送 `SIGINT` 信号，并使用 `exit` 函数中断当前进程的执行。

在 `main` 中，程序使用系统原语 `fork` 创建一个子进程，并在全局变量 `child` 中检索后者的标识符。

为了每 3 秒向子进程发送一次 `SIGUSR1` 信号，父进程使用最初从主函数触发的计时器（参见对例程 `alarm` 的调用）。3 秒后，父进程接收到 `SIGALRM` 信号，我们预先将例程 `poke` 与该信号关联。后者向子进程发送 `SIGUSR1` 信号，并通过第二次调用 `alarm` 重新设置 3 秒的计时器，该调用将在另外 3 秒后发出 `SIGALRM` 信号并触发对 `poke` 的新调用。此循环持续进行，直到父进程接收到 `SIGINT` 信号，该信号将传输给子进程以在其中断自身之前中断子进程。为此，我们还重新定义了父进程中与 `SIGINT` 信号关联的操作，现在由例程 `interrupt` 管理。最后，父进程通过调用 `wait` 等待子进程的终止。

子进程的作用是保持待机状态，对父进程发送的 `SIGUSR1` 信号做出反应，从而触发对 `increment` 函数的调用。

`wait` 是一个系统原语，一旦调用进程接收到诸如 `SIGALRM` 之类的信号，其执行就会在子进程终止之前中断。为了避免这种情况，我们在 `a_poke` 结构中添加了 `SA_RESTART` 标志（详见 `man sigaction`）。因此，如果 `wait` 调用的执行被接收到的 `SIGALRM` 信号中断，它将自动恢复。不要犹豫，尝试在没有此标志的情况下编译和运行程序，以了解其重要性！

## 代码详解

该程序展示了父子进程间的信号通信和定时器使用。

1. **进程创建**:
    使用 `fork()` 创建子进程。
    - **子进程**: 进入无限循环 `while(1) { sleep(10); }`，等待信号。注册 `SIGUSR1` 处理函数 `increment`。
    - **父进程**: 设置定时器并等待子进程。

2. **定时器 (`alarm`)**:
    父进程使用 `alarm(3)` 设置 3 秒定时器。
    当定时器到期时，发送 `SIGALRM` 信号。父进程捕获该信号并调用 `poke` 函数。
    `poke` 函数向子进程发送 `SIGUSR1`，并再次调用 `alarm(3)` 重置定时器。

3. **信号转发**:
    父进程捕获 `SIGINT` (Ctrl+C)。
    处理函数 `interrupt` 会先向子进程发送 `SIGINT` (`kill(child, SIGINT)`)，然后退出。

4. **`SA_RESTART`**:
    父进程在 `wait(NULL)` 时可能会被 `SIGALRM` 中断。为了让 `wait` 在信号处理后自动重启而不是返回错误（EINTR），我们在 `poke` 的 `sigaction` 中设置了 `SA_RESTART` 标志。
