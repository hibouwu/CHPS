#include <stdio.h>

/*
 * Éléments de correction / 解析与纠正
 *
 * La commande echo, comme son nom l'indique, reproduit sur sa sortie standard les arguments qui lui sont passés,
 * séparés par une espace. La sortie se termine par un saut de ligne.
 * Voici une implémentation simpliste de cette commande à l'aide de la fonction de librairie printf.
 *
 * echo 命令，顾名思义，在标准输出上重现传递给它的参数，并用空格分隔。输出以换行符结束。
 * 这是使用 printf 库函数对此命令的简单实现。
 */

int main(int argc, char ** argv) {
  if(argc < 2) {
    return 0;
  }
  for(int i = 1; i < argc; i++) {
    printf("%s", argv[i]);
    if(i + 1 < argc) {
      printf(" ");
    }
  }
  printf("\n");
  return 0;
}
