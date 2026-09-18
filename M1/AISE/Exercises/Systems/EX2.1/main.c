#define _GNU_SOURCE
#include <stdio.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>

/*
 * Éléments de correction / 解析与纠正
 *
 * L'un des paramètres d'un terminal est sa taille exprimée en nombre de lignes et de colonnes.
 * Par exemple, si un terminal a 20 lignes et 80 colonnes, la fenêtre, dans le cas d'un pseudo-terminal--PTY,
 * ou l'écran, dans le cas d'un terminal réel ou virtuel--TTY, ne pourra afficher plus que 80 caractères par ligne
 * et 1600 caractères au total à la fois.
 *
 * 终端的参数之一是其尺寸，以行数和列数表示。例如，如果一个终端有 20 行和 80 列，
 * 那么在伪终端 (PTY) 的情况下，窗口（或在真实/虚拟终端 TTY 的情况下的屏幕）
 * 每次最多只能显示 80 个字符每行，总共 1600 个字符。
 *
 * Pour les applications qui évoluent dans le cadre d'un terminal et fonctionnent en mode textuel,
 * telle que nano, vim, htop et ainsi de suite, la taille du terminal est un paramètre crucial pour produire
 * un affichage correct et lisible. Alors lorsque la taille de la fenêtre ou de l'écran du terminal change,
 * ces applications doivent pouvoir adapter leur affichage, y compris en cours d'exécution.
 * Ainsi, à chaque changement de la taille de la fenêtre ou de l'écran d'un terminal, ce dernier envoie
 * un signal SIGWINCH (numéro 28) à tous les processus attachés. À la réception de ce signal,
 * les processus ont la possibilité de déclancher une action, telle que la mise à jour de leur affichage.
 * C'est également l'objectif de cet exercice.
 *
 * 对于在终端环境中运行且采用文本模式的应用程序（如 nano, vim, htop 等），终端尺寸是产生正确且可读显示的关键参数。
 * 当终端窗口或屏幕尺寸发生变化时，这些应用程序必须能够调整其显示，包括在运行过程中。
 * 因此，每当终端窗口或屏幕尺寸发生变化时，终端都会向所有关联进程发送一个 SIGWINCH 信号（编号 28）。
 * 收到该信号后，进程可触发相应操作，例如更新显示内容。这也是本练习的目标所在。
 *
 * À l'exception d'une attente active dans une boucle while infinie (ou une pause), notre programme ne fait rien de spécial.
 * En effet, ce qui nous intéresse est la gestion du singal SIGWINCH. Le programme comporte la fonction report_size qui,
 * lorsqu'elle est appelée, récupère la taille courante du terminal et l'affiche sur la sortie standard.
 * C'est cette fonction que nous voulons appeler à chaque réception du signal SIGWINCH.
 * Pour ce faire, nous avons fait de la fonction report_size le gestionnaire du signal SIGWINCH à l'aide de la routine sigaction.
 *
 * 除了在无限循环中进行主动等待外，我们的程序并无特殊操作。实际上，我们要关注的是 SIGWINCH 信号的管理。
 * 程序包含函数 report_size，当被调用时，该函数会获取终端的当前尺寸并将其显示在标准输出上。
 * 我们希望在每次接收到 SIGWINCH 信号时调用该函数。为此，我们通过 sigaction 例程将 report_size 函数设为 SIGWINCH 信号的管理器。
 */


void report_size(int signal) {
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  printf("Taille actuelle : %d x %d\n", w.ws_row, w.ws_col);
}

int main(int argc, char **argv) {
  struct sigaction action = {
    .sa_handler = &report_size, // 指定信号处理函数
    .sa_flags = 0, // 默认标志
  };
  sigemptyset(&action.sa_mask); // 清空信号掩码
  sigaction(SIGWINCH, &action, NULL); // 注册信号处理函数

  while (1) { }
  return 0;
}