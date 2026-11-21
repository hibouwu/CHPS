# Processus, threads et synchronisation · 进程、线程与同步

[目录](README.md) · [教师英文讲义（18 页）](../../GitLab/cours/01-threads.pdf) · [本讲实验](../../GitLab/threads/Readme.md)

## Processus et rôle du système · 进程与操作系统

[原讲义第 1–2 页](../../GitLab/cours/01-threads.pdf#page=1)

**FR** Un processus est une instance d'un programme en cours d'exécution. Deux instances d'un même programme ont chacune leur espace d'adressage. Le système gère leur création et leur terminaison, les ordonnance sur les processeurs et fournit des mécanismes de communication comme les signaux, les tubes et les sockets. Par défaut, l'isolation des espaces d'adressage empêche un processus d'accéder directement à la mémoire privée d'un autre.

**中文** 进程是程序运行时的一个实例。同一个程序运行两次，两个进程各有自己的地址空间。操作系统负责创建、结束和调度进程，也通过信号、管道、套接字等提供通信机制。默认的地址空间隔离使一个进程不能直接访问另一个进程的私有内存。

## Cadre d'appel et état d'un thread · 调用帧与线程执行状态

[原讲义第 3–5 页](../../GitLab/cours/01-threads.pdf#page=3)

**FR** Dans le modèle du cours, l'appel de `add(1, 2)` place un cadre au-dessus de celui de `main`. Il contient les paramètres `x` et `y`, la variable locale `z` et les informations nécessaires pour reprendre l'appelant. Au retour, le cadre de `add` disparaît et l'exécution reprend dans `main`. La pile et la prochaine instruction permettent de suivre la continuation d'un thread.

**中文** 在课件模型中，调用 `add(1, 2)` 会在 `main` 的帧上方建立一个调用帧，记录参数 `x` 和 `y`、局部变量 `z`，以及返回调用者所需的信息。函数返回后，`add` 的帧退出，执行回到 `main`。线程的栈和下一条指令描述了它要从哪里继续执行。

## Mémoire partagée et identité · 共享地址空间与线程标识

[原讲义第 6–7 页](../../GitLab/cours/01-threads.pdf#page=6)

**FR** Dans un processus, les threads partagent le code, les données globales et le tas. Chacun possède sa propre pile et son propre état d'exécution. Le processus commence avec un thread et peut en créer d'autres que le système pourra exécuter simultanément sur plusieurs cœurs. `pthread_t` est le type d'un identifiant POSIX, et `pthread_self()` renvoie celui du thread appelant.

**中文** 同一进程中的线程共享代码、全局数据和堆，各自有独立的栈与执行状态。一个进程从单线程开始，之后可创建更多线程，操作系统可以让它们在多个核心上同时运行。`pthread_t` 是 POSIX 线程标识的类型，`pthread_self()` 返回调用线程自己的标识。

## Création, terminaison et récupération · 创建、退出与回收

[原讲义第 8–11 页](../../GitLab/cours/01-threads.pdf#page=8)

**FR** `pthread_create` place l'identifiant dans `*tid` et lance `start_routine(arg)`. Le thread se termine en revenant de cette fonction ou en appelant `pthread_exit(retval)`. `pthread_join(tid, &retval)` attend sa fin, récupère sa valeur de retour et permet la récupération des ressources d'un thread joignable. Pour un thread détaché, les ressources sont libérées à sa terminaison et on ne peut pas faire de `join`. Le retour de `main` ou un appel à `exit` met fin au processus et à ses threads.

**中文** `pthread_create` 把线程标识写入 `*tid`，并启动 `start_routine(arg)`。入口函数返回或调用 `pthread_exit(retval)` 都会结束当前线程。`pthread_join(tid, &retval)` 等待一个可连接线程结束、取得返回值，并让系统回收相应资源。分离线程结束后自动释放资源，无法再 `join`。`main` 返回或任意线程调用 `exit` 会结束整个进程及其线程。

```c
pthread_t tid;
/* f has type void *f(void *arg). */
if (pthread_create(&tid, NULL, f, arg) == 0) {
    void *result;
    pthread_join(tid, &result);
}
```

## Mise à jour perdue et section critique · 丢失更新与临界区

[原讲义第 12–15 页](../../GitLab/cours/01-threads.pdf#page=12)

**FR** Le solde vaut initialement 1000. Le débit lit 1000 et s'interrompt. Le crédit lit à son tour 1000 et publie 1100. Le débit reprend avec sa copie locale et écrit 999. Le résultat séquentiel attendu est 1099. Cet entrelacement illustre une mise à jour perdue. En C, des accès concurrents conflictuels à un entier ordinaire sans synchronisation constituent une course de données. Un même mutex doit protéger toute la séquence lecture–calcul–écriture de chaque opération.

**中文** 余额初始为 1000。扣款先读到 1000，随后暂停。存款线程也读到 1000，写回 1100。扣款线程恢复，用自己的旧副本计算并写回 999，而串行执行的正确结果是 1099。这组交错说明了一次更新怎样被覆盖。在 C 中，不经同步地并发冲突访问普通整数还构成数据竞争。两边都要用同一把互斥锁保护完整的读—算—写过程。

## Variable de condition et moniteur · 条件变量与管程

[原讲义第 16–18 页](../../GitLab/cours/01-threads.pdf#page=16)

**FR** Le prédicat partagé est ici `msg != NULL`. Tant qu'il est faux, `pthread_cond_wait(&c, &m)` libère le mutex `m` en s'endormant puis le reprend avant de retourner. Le producteur modifie `msg` sous ce mutex et signale `c`. `pthread_cond_signal` réveille au moins un des threads qui attendent, s'il y en a. `pthread_cond_broadcast` les réveille tous. Un réveil invite à relire le prédicat sous verrou, d'où la boucle `while`.

**中文** 共享条件是 `msg != NULL`。条件不满足时，`pthread_cond_wait(&c, &m)` 在进入等待时释放互斥锁 `m`，并在返回之前重新取得它。生产者持锁修改 `msg`，再通知条件变量 `c`。有等待者时，`pthread_cond_signal` 唤醒至少一位，`pthread_cond_broadcast` 唤醒所有等待者。线程醒来后必须持锁重查条件，所以这里用 `while`。

```c
pthread_mutex_lock(&m);
while (msg == NULL)
    pthread_cond_wait(&c, &m);
/* Read or consume msg while holding m. */
pthread_mutex_unlock(&m);
```

## Vérification rapide · 自检

- **FR** Pourquoi attendre dans une boucle avec deux consommateurs ? Le premier qui reprend le mutex peut consommer l'élément avant le second. **中文** 两个消费者时为什么要循环？先抢回锁的线程可能已经取走了元素。
- **FR** Que protège le mutex du solde ? La lecture, le calcul et l'écriture forment ensemble la section critique. **中文** 余额的锁保护什么？读、算、写共同组成的临界区。
