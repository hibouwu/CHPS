#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

/*
 * Éléments de correction / 解析与纠正
 *
 * Le rôle de la commande kill est d'envoyer un signal à un processus.
 * Son premier argument est obligatoire et signifie l'identifiant du processus récepteur (PID).
 * Le second argument est optionnel et signifie le code du signal à envoyer (par défaut SIGHUP).
 * Voici une implémentation simpliste de cette commande à l'aide de la fonction de librairie kill.
 *
 * kill 命令的作用是向进程发送信号。它的第一个参数是强制性的，表示接收进程的标识符 (PID)。
 * 第二个参数是可选的，表示要发送的信号代码（默认为 SIGHUP）。
 * 这是使用 kill 库函数对此命令的简单实现。
 */

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
