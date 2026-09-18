# 练习 3 (Exercice 3)

## 题目描述

> Écrivez un programme qui lance un processus fils.
> 编写一个程序，启动一个子进程。
>
> Le parent enverra aléatoirement soit SIGCONT soit SIGPIPE à son fils qui devra compter le nombre de signaux reçu pour chaque type.
> 父进程将随机发送 SIGCONT 或 SIGPIPE 给其子进程，子进程必须统计收到的每种信号的数量。
>
> Le parent opérera pendant 30 secondes avant de s'interrompre.
> 父进程将运行 30 秒，然后中断。
>
> Enfin, quand le parent aura fini la phase d'émission, il terminera son fils qui affichera le compte des deux signaux (SIGCONT et SIGPIPE) avant de se terminer.
> 最后，当父进程完成发送阶段后，它将终止子进程，子进程在终止前将显示两个信号（SIGCONT 和 SIGPIPE）的计数。
>
> Enfin, si le parent est interrompu avant la fin des 30 secondes, il terminera son fils de manière prématurée.
> 最后，如果父进程在 30 秒结束前被中断，它将提前终止其子进程。

来源: [felsoci.sk/aise/practice.html](https://felsoci.sk/aise/practice.html#count)

## 解析与纠正 (Éléments de correction)

为了实现这个程序，我们使用了两个信号处理程序：

1. `h_child`，在子进程方面，对 `SIGCONT`、`SIGPIPE` 和 `SIGUSR1` 信号做出反应。
2. `h_parent`，在父进程方面，对 `SIGINT` 信号做出反应。

我们的程序首先创建一个子进程，该子进程使用 `h_child` 例程设置 `SIGCONT`、`SIGPIPE` 和 `SIGUSR1` 信号的处理，然后进入一个等待循环，该循环的退出取决于变量 `run`。

父进程使用 `h_parent` 例程设置 `SIGINT` 信号的处理，然后进入向子进程发送 `SIGCONT` 和 `SIGPIPE` 信号的阶段，该阶段持续约 30 秒（参见 `for` 循环）。子进程通过计算 `SIGCONT` 和 `SIGPIPE` 信号的出现次数来做出反应。

在信号发送阶段结束后，父进程向子进程发送 `SIGUSR1` 信号，子进程对此做出反应，显示收到的 `SIGCONT` 和 `SIGPIPE` 信号的计数，然后将变量 `run` 设为 0。因此，子进程退出其等待循环并正常终止。父进程现在也可以轮流终止。

如果父进程在信号发送阶段结束之前接收到 `SIGINT` 信号，它将其传输给子进程以在其中断自身之前中断子进程。

即不需要在子进程方面建立对 `SIGINT` 信号的特定处理。事实上，进程接收到此信号时的默认操作是中断自身。

## 代码详解

该程序练习了在具有多个信号类型的场景下的信号处理。

1. **子进程逻辑**:
    - 使用 `h_child` 函数处理 `SIGCONT` (计数)、`SIGPIPE` (计数) 和 `SIGUSR1` (打印结果并退出循环)。
    - `while(run)` 循环等待，直到收到 `SIGUSR1` 将 `run` 置为 0。

2. **父进程逻辑**:
    - 使用 `h_parent` 处理 `SIGINT`。
    - 使用 `for` 循环运行 30 次，每次暂停 1 秒 (`sleep(1)`)，模拟 30 秒运行时间。
    - 在循环中随机发送 `SIGCONT` 或 `SIGPIPE` 给子进程。
    - 循环结束后，发送 `SIGUSR1` 通知子进程结束，并调用 `wait(NULL)` 等待子进程退出。

该程序练习了在具有多个信号类型的场景下的信号处理。

1. **子进程逻辑**:
    - 注册 `SIGCONT` (继续), `SIGPIPE` (管道破裂), `SIGUSR1` (自定义) 的处理函数 `handler_sigrecu`。
    - 定义全局计数器 `counter_CONT` 和 `counter_PIPE`。
    - 收到 `SIGCONT`/`SIGPIPE` 时递增对应计数器。
    - `while(1)` 循环等待。

2. **父进程逻辑**:
    - 注册 `SIGALRM` 处理函数 `handler_sigAlrm`，用于周期性发送信号。
    - 使用 `alarm(30)` 设置总运行时间？
        - **注意**: 现有的本地代码实现似乎略有不同。本地代码使用 `alarm(1)` 在 `handler_sigAlrm` 中循环触发，而主循环等待 `run` 变量。根据题目，父进程应该只运行 30 秒。
        - *本地代码分析*: `main` 中 `alarm(30)`，然后 `while(!run)`。这似乎意味着 `SIGALRM` 30秒后触发一次？不，题目要求"发送...30秒"。
        - 让我们仔细看本地代码：

            ```c
            void handler_sigAlrm(int signal) {
                (void)signal;
                envoyer_sigContPipe(); // 发送随机信号
                alarm(1); // 1秒后再次触发？？这会覆盖 main 中的 alarm(30) 吗？
            }
            // ... main ...
            alarm(30); // 这里设置了30秒
            // ...
            sigaction(SIGALRM, &a_alrm, NULL);
            while (!run) { sleep(1); }
            ```

            **代码逻辑可能有误**: 如果 `handler_sigAlrm` 是 `SIGALRM` 的处理器，且 `main` 设了 `alarm(30)`，那么程序会等待 30 秒，然后触发 **一次** `handler_sigAlrm`，发送 **一个** 信号，然后设 `alarm(1)`...
            题目说 "Le parent enverra ... pendant 30 secondes" (父进程在30秒内发送)。通常意味着循环发送。
            **网站参考代码** 使用 `for(int i = 0; i < 30; i++) { ... sleep(1); }` 循环。本地代码似乎试图用 `alarm` 实现，但逻辑混淆了总时长和间隔。
            **修正**: 我将在随后的步骤中修正 `EX2.3/main.c` 以匹配正确的逻辑。目前先按照现有代码写解释，或者指出需要修复。

3. **退出同步**:
    - 父进程结束发送后，应通过 `kill(child, SIGUSR1)` 通知子进程（网站代码逻辑）。
    - 本地代码使用 `kill(child, SIGTERM)`。这会导致子进程直接退出，可能来不及打印计数（除非注册了 SIGTERM）。
    - 子进程代码里没有处理 `SIGTERM`。
    - **结论**: 本地代码 `EX2.3/main.c` 需要由于逻辑错误进行修复。

**计划更新**: 我将在下一个步骤修复 `EX2.3/main.c`。
