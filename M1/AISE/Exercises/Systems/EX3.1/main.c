#include <stdio.h>
#include <string.h>

/*
 * Éléments de correction / 解析与纠正
 *
 * Nous commençons notre programme par la définition d'un nouveau type de donnée appelé Me qui correspond à la structure proposée dans le sujet.
 *
 * 我们从定义一个名为 Me 的新数据类型开始程序，该类型对应于题目中提出的结构。
 *
 * Le noyau du programme se compose de deux modes de fonctionnement :
 * 1. Si le programme est lancé sans arguments, nous remplissons une structure Me avec des informations nous concernant
 *    et ensuite nous écrivons ses éléments dans un fichier nommé me dans le répertoire courant en mode écriture seule.
 * 2. Si le programme est lancé avec au moins un argument de ligne de commande, nous considérons le premier argument comme
 *    l'emplacement du fichier contenant les éléments d'une structure Me. Nous ouvrons alors ce fichier en lecture seule
 *    et nous remplissons la structure Me depuis son contenu. Enfin nous affichons les éléments de cette structure.
 *
 * 程序的核心由两种运行模式组成：
 * 1. 如果程序无参数运行，我们用关于我们的信息填充一个 Me 结构，然后将其元素写入当前目录中名为 me 的只写文件中。
 * 2. 如果程序使用至少一个命令行参数运行，我们将第一个参数视为包含 Me 结构元素的文件位置。
 *    然后我们以只读方式打开该文件，并从其内容填充 Me 结构。最后，我们按照题目中提出的模型显示该结构的元素。
 *
 * Note sur la version optimisée / 关于优化版本的说明:
 * Pour éviter de stocker des caractères nuls superflus (\0), on pourrait adapter le format du fichier 
 * en y incluant par exemple une information sur la taille réelle du nom.
 * (Voir le README pour le code de la version optimisée).
 *
 * 为了避免存储多余的空字符（\0），我们可以调整文件格式，例如，在其中包含有关名称实际长度的信息。
 * （请参阅 README 获取优化版本的代码）。
 */

typedef struct {
  char name[256];
  int age;
} Me;

int main(int argc, char ** argv) {
  Me me;
  memset(me.name, '\0', 256);
  if(argc < 2) {
    FILE * output = fopen("me", "w");
    strcpy(me.name, "Marek Felsoci");
    me.age = 29;
    fwrite(me.name, 1, 256, output);
    fwrite(&me.age, sizeof(int), 1, output);
    fclose(output);
  } else {
    FILE * input = fopen(argv[1], "r");
    fread(me.name, 1, 256, input);
    fread(&me.age, sizeof(int), 1, input);
    fclose(input);
    printf("Je m'appelle %s et j'ai %d ans.\n", me.name, me.age);
  }
  return 0;
}

/*
 * Compilé sous le nom struct et exécuté sans argument, le programme ci-dessous n'affiche rien sur sa sortie standard, mais il produit un fichier me.
 *编译为 struct 并无参数执行时，下面的程序不会在标准输出显示任何内容，但会生成一个 me 文件。
 *
 * Le contenu brut du fichier me est le suivant.
 * 文件 me 的原始内容如下。
 +--------+-------------------------+-------------------------+--------+--------+
|00000000| 4d 61 72 65 6b 20 46 65 | 6c 73 6f 63 69 00 00 00 |Marek Fe|lsoci000|
|00000010| 00 00 00 00 00 00 00 00 | 00 00 00 00 00 00 00 00 |00000000|00000000|
|00000020| 00 00 00 00 00 00 00 00 | 00 00 00 00 00 00 00 00 |00000000|00000000|
|00000030| 00 00 00 00 00 00 00 00 | 00 00 00 00 00 00 00 00 |00000000|00000000|
|00000040| 00 00 00 00 00 00 00 00 | 00 00 00 00 00 00 00 00 |00000000|00000000|
|00000050| 00 00 00 00 00 00 00 00 | 00 00 00 00 00 00 00 00 |00000000|00000000|
|00000060| 00 00 00 00 00 00 00 00 | 00 00 00 00 00 00 00 00 |00000000|00000000|
|00000070| 00 00 00 00 00 00 00 00 | 00 00 00 00 00 00 00 00 |00000000|00000000|
|00000080| 00 00 00 00 00 00 00 00 | 00 00 00 00 00 00 00 00 |00000000|00000000|
|00000090| 00 00 00 00 00 00 00 00 | 00 00 00 00 00 00 00 00 |00000000|00000000|
|000000a0| 00 00 00 00 00 00 00 00 | 00 00 00 00 00 00 00 00 |00000000|00000000|
|000000b0| 00 00 00 00 00 00 00 00 | 00 00 00 00 00 00 00 00 |00000000|00000000|
|000000c0| 00 00 00 00 00 00 00 00 | 00 00 00 00 00 00 00 00 |00000000|00000000|
|000000d0| 00 00 00 00 00 00 00 00 | 00 00 00 00 00 00 00 00 |00000000|00000000|
|000000e0| 00 00 00 00 00 00 00 00 | 00 00 00 00 00 00 00 00 |00000000|00000000|
|000000f0| 00 00 00 00 00 00 00 00 | 00 00 00 00 00 00 00 00 |00000000|00000000|
|00000100| 1d 00 00 00             |                         |•000    |        |
+--------+-------------------------+-------------------------+--------+--------+ 

 * Enfin, nous pouvons relire ce fichier avec le même programme en lui passant le chemin vers ce fichier en argument, c'est-à-dire ./struct me.
 * 最后，我们可以使用相同的程序重新读取该文件，只需将该文件的路径作为参数传递给程序，即 ./struct me 。

Je m'appelle Marek Felsoci et j'ai 29 ans.

 * Sur la base du contenu brut du fichier me, nous pouvons constater que ce dernier contient un grand bloc de caractères nuls \0 entre l'octet correspondant à la dernière lettre du nom et le premier octet de la valeur entière représentant l'âge. En effet, lorsque notre programme sauvegarde le contenu d'une structure Me dans le fichier, il sauvegarde les 256 caractères de la chaîne name indépendemment de la longueur réelle du nom.
 * 根据文件 me 的原始内容，我们发现该文件在名称最后一个字母对应的字节与表示年龄的整数值第一个字节之间包含一大段空字符 \0 。 事实上，当我们的程序将结构内容 Me 保存到文件中时，它会将字符串 name 的 256 个字符全部保存，而不考虑名称的实际长度。
 * 
 */