#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*
 * Éléments de correction / 解析与纠正
 *
 * Pour réaliser ce programme, nous avons recours à 2 gestionnaires de signaux :
 * 1. h_child (côté fils) qui réagit aux signaux SIGCONT, SIGPIPE et SIGUSR1.
 * 2. h_parent (côté parent) qui réagit au signal SIGINT.
 *
 * 为了实现这个程序，我们使用了两个信号处理程序：
 * 1. h_child，在子进程方面，对 SIGCONT、SIGPIPE 和 SIGUSR1 信号做出反应。
 * 2. h_parent，在父进程方面，对 SIGINT 信号做出反应。
 *
 * Notre programme commence par la création d'un processus fils. Ce dernier met en place la gestion des signaux SIGCONT, SIGPIPE et SIGUSR1
 * à l'aide de la routine h_child. Ensuite, il entre dans une boucle d'attente conditionnée par la variable run.
 *
 * 我们的程序首先创建一个子进程，该子进程使用 h_child 例程设置 SIGCONT、SIGPIPE 和 SIGUSR1 信号的处理，
 * 然后进入一个等待循环，该循环的退出取决于变量 run。
 *
 * Le processus parent met en place la gestion du signal SIGINT à l'aide de la routine h_parent.
 * Ensuite, il entre dans la phase d'émission des signaux SIGCONT et SIGPIPE à destination de son fils, phase qui dure environ 30 secondes (voir la boucle for).
 * Le processus fils réagit en comptabilisant les occurrences de signaux SIGCONT et SIGPIPE.
 *
 * 父进程使用 h_parent 例程设置 SIGINT 信号的处理，然后进入向子进程发送 SIGCONT 和 SIGPIPE 信号的阶段，
 * 该阶段持续约 30 秒（参见 for 循环）。子进程通过计算 SIGCONT 和 SIGPIPE 信号的出现次数来做出反应。
 *
 * Une fois la phase d'émission terminée, le processus parent envoie le signal SIGUSR1 à son fils.
 * Ce dernier y réagit en affichant le décompte des signaux SIGCONT et SIGPIPE reçu, et ensuite en mettant la variable run à 0.
 * Ainsi, le processus fils sort de sa boucle d'attente et se termine normalement. Le processus parent peut maintenant se terminer à son tour.
 *
 * 在信号发送阶段结束后，父进程向子进程发送 SIGUSR1 信号，子进程对此做出反应，显示收到的 SIGCONT 和 SIGPIPE 信号的计数，
 * 然后将变量 run 设为 0。因此，子进程退出其等待循环并正常终止。父进程现在也可以轮流终止。
 *
 * Si le processus parent reçoit le signal SIGINT avant la fin de la phase d'émission, il le transmet à son fils pour l'interrompre avant de l'être lui-même.
 *
 * 如果父进程在信号发送阶段结束之前接收到 SIGINT 信号，它将其传输给子进程以在其中断自身之前中断子进程。
 *
 * Il n'est pas nécessaire de mettre en place une gestion spécifique du signal SIGINT côté fils.
 * En effet, l'action par défaut à la réception de ce signal par un processus est de s'interrompre.
 *
 * 即不需要在子进程方面建立对 SIGINT 信号的特定处理。事实上，进程接收到此信号时的默认操作是中断自身。
 */

int sigcont = 0, sigpipe = 0;
int run = 1;
pid_t child;

void h_child(int signal) {
    switch(signal) {
        case SIGCONT:
            sigcont++;
            break;
        case SIGPIPE:
            sigpipe++;
            break;
        case SIGUSR1:
            printf( "Signaux reçus : %d fois SIGCONT et %d fois SIGPIPE.\n", sigcont, sigpipe );
            run = 0;
        default:
            break;
    }
}

void h_parent(int signal) {
    kill(child, SIGINT);
    exit(EXIT_SUCCESS);
}

int main(int argc, char ** argv) {
    srand(time(NULL));
    child = fork();

    if(child == 0) {
        struct sigaction action = {
            .sa_handler = &h_child,
            .sa_flags = 0
        };
        sigemptyset(&action.sa_mask);
        sigaction(SIGCONT, &action, NULL);
        sigaction(SIGPIPE, &action, NULL);
        sigaction(SIGUSR1, &action, NULL);

        while(run) {
        }
    } else {
        struct sigaction action = {
            .sa_handler = &h_parent,
            .sa_flags = 0
        };
        sigemptyset(&action.sa_mask);
        sigaction(SIGINT, &action, NULL);

        for(int i = 0; i < 30; i++) {
            printf("Envoi du signal %d sur 30...\r", i + 1);
            fflush(stdout);
            kill(child, (rand() % 2) ? SIGCONT : SIGPIPE);
            sleep(1);
        }

        kill(child, SIGUSR1);
        wait(NULL);
    }
    return 0;
}