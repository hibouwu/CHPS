#define _GNU_SOURCE
/*
gcc -Wall -O2 main.c -o main
*/
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

/*
 * Éléments de correction / 解析与纠正
 *
 * Outre la fonction principale main, le programme comporte trois autres fonctions qui servent de gestionnaires de signaux :
 * 1. increment, qui incrémente un compteur global (voir la variable counter) et affiche sa valeur courante ;
 * 2. poke, qui envoie un signal (ici nous avons opté pour SIGUSR1) au processus fils (dont l'identifiant se trouve dans la variable globale child) et arme une minuterie à 3 secondes ;
 * 3. interrupt, qui envoie le signal SIGINT au processus fils et interrompt l'exécution du processus courant à l'aide de la fonction exit.
 *
 * 除了主函数 main 之外，程序还包含另外三个作为信号处理程序的函数：
 * 1. increment，它递增一个全局计数器（参见变量 counter）并显示其当前值；
 * 2. poke，它向子进程（其标识符位于全局变量 child 中）发送一个信号（这里我们选择了 SIGUSR1），并设置一个 3 秒的计时器；
 * 3. interrupt，它向子进程发送 SIGINT 信号，并使用 exit 函数中断当前进程的执行。
 *
 * Dans main, le programme crée un processus fils à l'aide de la primitive système fork et récupère l'identifiant de ce dernier dans la variable globale child.
 * 在 main 中，程序使用系统原语 fork 创建一个子进程，并在全局变量 child 中检索后者的标识符。
 *
 * Pour envoyer le signal SIGUSR1 au processus fils toutes les 3 secondes, le processus parent utilise une minuterie déclenchée initialement depuis la fonction principale.
 * Au bout de 3 secondes, le processus parent reçoit le signal SIGALRM auquel nous avons associé au préalable la routine poke.
 * Celle-ci envoie le signal SIGUSR1 au processus fils et réarme la minuterie à 3 secondes via un deuxième appel à alarm...
 * Ce cycle perdure jusqu'à la réception du signal SIGINT par le processus parent qui le transmet au processus fils pour l'interrompre avant de l'être lui-même.
 *
 * 为了每 3 秒向子进程发送一次 SIGUSR1 信号，父进程使用最初从主函数触发的计时器（参见对例程 alarm 的调用）。
 * 3 秒后，父进程接收到 SIGALRM 信号，我们预先将例程 poke 与该信号关联。
 * 后者向子进程发送 SIGUSR1 信号，并通过第二次调用 alarm 重新设置 3 秒的计时器...
 * 此循环持续进行，直到父进程接收到 SIGINT 信号，该信号将传输给子进程以在其中断自身之前中断子进程。
 *
 * wait est une primitive système dont l'exécution est interrompue avant la terminaison du processus fils dès que le processus appelant reçoit un signal tel que SIGALRM.
 * Pour éviter cela, nous avons ajouté le drapeau SA_RESTART (voir man sigaction) à la structure a_poke.
 * Ainsi, si l'exécution de l'appel à wait est interrompue par la réception du signal SIGALRM, elle reprendra automatiquement.
 *
 * wait 是一个系统原语，一旦调用进程接收到诸如 SIGALRM 之类的信号，其执行就会在子进程终止之前中断。
 * 为了避免这种情况，我们在 a_poke 结构中添加了 SA_RESTART 标志（详见 man sigaction）。
 * 因此，如果 wait 调用的执行被接收到的 SIGALRM 信号中断，它将自动恢复。
 */

int counter = 0;
pid_t child;

void increment(int signal) {
  counter++;
  printf("Compteur du processus fils : %d\n", counter);
}

void poke(int signal) {
  kill(child, SIGUSR1);
  alarm(3);
}

void interrupt(int signal) {
  printf("Interruption du processus fils.\n");
  kill(child, SIGINT);
  printf("Interruption du processus parent.\n");
  exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
  child = fork();
  if (child == 0) {
    printf("Démarrage du processus fils.\n");
    struct sigaction a_increment = {
      .sa_handler = increment,
      .sa_flags = 0
    };
    sigemptyset(&a_increment.sa_mask);
    sigaction(SIGUSR1, &a_increment, NULL);
    while (1) { sleep(10); }
  } else {
    struct sigaction a_poke = {
      .sa_handler = poke,
      .sa_flags = SA_RESTART
    };
    sigemptyset(&a_poke.sa_mask);

    struct sigaction a_interrupt = {
      .sa_handler = interrupt,
      .sa_flags = 0
    };
    sigemptyset(&a_interrupt.sa_mask);

    sigaction(SIGINT, &a_interrupt, NULL);
    sigaction(SIGALRM, &a_poke, NULL);
    alarm(3);
    wait(NULL);
  }
  return 0;
}