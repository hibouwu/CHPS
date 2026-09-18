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
 * Félicitations, vous avez écrit un Shell !
 * Notre implémentation d'un Shell se résume à une boucle while dont le programme ne sort que si l'utilisateur saisit la commande exit.
 *
 * 祝贺你，你已经写了一个 Shell！
 * 我们对 Shell 的实现归结为一个 while 循环，只有当用户输入 exit 命令时程序才会退出。
 *
 * À chaque tour de cette boucle le programme :
 * 1. affiche un invite de commande (voir macro PROMPT) ;
 * 2. attend que l'utilisateur saisisse une ligne de commande sur l'entrée standard que le programme récupère dans la chaîne de caractères line à l'aide de la fonction getline ;
 * 3. retire le retour à la ligne \n situé en dernière position de line en le remplaçant par le caractère de fin de chaîne \0;
 * 4. fait appel à la fonction wordexp (voir man wordexp) pour évaluer le résultat d'éventuelles références à des variables d'environnement...
 * 5. si le premier mot correspond à exit, on sort de la boucle while ;
 * 6. lance un processus fils à l'aide de la primitive système fork pour exécuter la commande saisie par l'utilisateur ;
 * 7. attend la terminaison de cette commande à l'aide de la primitive système wait.
 *
 * 在这个循环的每一轮中，程序：
 * 1. 显示命令提示符（参见宏 PROMPT）；
 * 2. 等待直到用户在标准输入上输入一行命令行，程序使用 getline 函数将其检索到字符串 line 中；
 * 3. 通过将位于 line 最后位置的换行符 \n 替换为字符串结束符 \0 来去除它；
 * 4. 调用 wordexp 函数以评估对环境变量的任何引用...
 * 5. 如果第一个单词是 exit，则退出 while 循环；
 * 6. 利用系统原语 fork 启动一个子进程来执行用户输入的命令；
 * 7. 利用系统原语 wait 等待此命令的终止。
 *
/*
 * Il existe d'autres alternatives à l'utilisation de la fonction wordexp.
 * Par exemple, il est possible de découper une chaîne de caractères en mots individuels à l'aide de la fonction strtok (voir man strtok).
 * Cependant, la fonction wordexp nous permet aussi d'évaluer les références aux variables d'environnement et aux résultats de commandes imbriquées
 * éventuellement présentes dans la ligne de commande saisie par l'utilisateur.
 * Par exemple, si l'utilisateur saisit la commande :
 * echo "Je m'appelle $(whoami) et je me trouve dans le répertoire $PWD."
 * la fonction wordexp retournera dans expansion.we_wordv un tableau contenant les mots suivants :
 * Je m'appelle marek et je me trouve dans le répertoire /home/marek/src/gitlab.com/aise.
 *
 * 除了使用 wordexp 函数外，还有其他替代方案。例如，可以使用 strtok 函数将字符串分割为单个单词（参见 man strtok）。
 * 然而，wordexp 功能还允许我们评估用户输入命令中可能存在的环境变量引用和嵌套命令结果。
 * 例如，如果用户输入命令
 * echo "Je m'appelle $(whoami) et je me trouve dans le répertoire $PWD."
 * 函数 wordexp 将在 expansion.we_wordv 中返回一个包含以下单词的数组：
 * Je m'appelle marek et je me trouve dans le répertoire /home/marek/src/gitlab.com/aise.
 */
 */

int main(void) {
  int terminate = 0;
  char * line = NULL;
  wordexp_t expansion;
  int first = 1;

  while(!terminate) {
    printf("%s", PROMPT);
    fflush(stdout);

    size_t length;
    if(getline(&line, &length, stdin) < 0) {
      perror("lecture de la ligne de commande");
      terminate = -1;
      continue;
    }
    line[strlen(line) - 1] = '\0';

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
          continue;
        }
      } else {
        wait(NULL);
      }
    }
  }

  free(line);
  wordfree(&expansion);

  if(terminate > 0) {
    printf("Bye\n");
    return 0;
  }

  return 1;
}
