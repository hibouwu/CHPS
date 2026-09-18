#include <stdio.h>
#include <wordexp.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define PROMPT "$ "

/*
 * Éléments de correction / 解析与纠正
 *
 * Nous avons modifié l'implémentation initiale (voir Exercice 5) comme suit.
 * Entre les étapes 3 et 4 de la boucle while, nous avons ajouté la détection de l'éventuelle présence du caractère & en fin de ligne de commande (voir variable detach).
 *
 * 我们修改了初始实现（参见 [EX2.5](../EX2.5/README.md)）如下。
 * 在 while 循环的步骤 3 和 4 之间，我们添加了对命令行末尾是否存在 & 字符的检测（参见变量 detach）。
 *
 * Si le caractère & est effectivement présent en fin de ligne de commande saisie par l'utilisateur, nous devons le prendre en compte mais nous ne pouvons pas le conserver,
 * car la fonction wordexp considère & comme un caractère illégal.
 *
 * 如果 & 字符确实出现在用户输入的命令行的末尾，我们必须将其考虑在内，但我们不能将其保留，因为 wordexp 函数将 & 视为非法字符。
 *
 * Ensuite, nous avons conditionné l'étape 7 de la boucle while. Le programme n'attend la terminaison de la commande courante
 * que si le caractère & n'était PAS présent en fin de ligne de commande correspondante.
 *
 * 然后，我们要对 while 循环的步骤 7 进行条件化。程序仅当 & 字符**不**存在于相应命令行的末尾时，才等待当前命令的终止。
 *
 * Finalement, nous avons ajouté une dernière étape qui ne se déclenche qu'à la sortie du shell via la commande exit
 * et qui consiste à attendre la terminaison de l'ensemble des commandes lancées en tâche de fond.
 *
 * 最后，我们添加了最后一个步骤，该步骤仅在通过 exit 命令退出 shell 时触发，包括等待所有作为后台任务启动的命令的终止。
 *
 * Pour pouvoir réaliser cette dernière étape, nous avons dû comptabiliser le nombre de ces commandes.
 * En effet, l'appel à la primitive système wait ne permet d'attendre qu'un seul processus fils.
 * Il est donc impératif d'appeler wait pour chaque processus fils correspondant à une tâche de fond.
 * 
 * 为了能够执行这最后一步，我们必须计算这些命令的数量。实际上，调用系统原语 wait 只允许等待单个子进程。
 * 因此，必须为每个对应于后台任务的子进程调用 wait。
 */

int main(void) {
  int terminate = 0;
  char * line = NULL;
  wordexp_t expansion;
  int first = 1, background = 0;

  while(!terminate) {
    printf("%s", PROMPT);
    fflush(stdout);

    size_t length;
    if(getline(&line, &length, stdin) < 0) {
      perror("lecture de la ligne de commande");
      terminate = -1;
      continue;
    }

    length = strlen(line) - 1;
    line[length] = '\0';

    char * ampersand = strchr(line, '&');
    int detach = ampersand && ((ampersand + 1)[0] == ' ' || (ampersand + 1)[0] == '\0');

    if(detach) {
      (* ampersand) = '\0';
    }

    int r;
    if((r = wordexp(line, &expansion, first ? 0 : WRDE_REUSE))) {
      errno = EINVAL;
      perror("expansion de la ligne de commande");
      terminate = -1;
      continue;
    } else {
      first = 0;
      if(strncmp(expansion.we_wordv[0], "exit", 4) == 0) {
        terminate = 1;
        continue;
      }

      pid_t executor = fork();
      if(executor == 0) {
        if(execvp(expansion.we_wordv[0], expansion.we_wordv) < 0) {
          perror("exécution de la ligne de commande");
          terminate = -1;
          return 1;
        }
      } else if(detach) {
        background++;
      } else {
        wait(NULL);
      }
    }
  }

  free(line);
  wordfree(&expansion);

  for(int i = 0; i < background; i++) {
    wait(NULL);
  }

  if(terminate > 0) {
    printf("Bye\n");
    return 0;
  }

  return 1;
}
