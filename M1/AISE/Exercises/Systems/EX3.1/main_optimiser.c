#include <stdio.h>
#include <string.h>

/*
 * Éléments de correction / 解析与纠正
 *
 * Version Optimisée (Optimal Version)
 *
 * Pour éviter de stocker des caractères nuls superflus (\0), on pourrait adapter le format du fichier
 * en y incluant par exemple une information sur la taille réelle du nom.
 * 为了避免存储多余的空字符（\0），我们可以调整文件格式，例如，在其中包含有关名称实际长度的信息。
 *
 * Dans cette version, nous écrivons d'abord la taille de la chaîne de caractères (incluant le caractère nul de fin),
 * puis nous écrivons uniquement les octets utiles de la chaîne.
 * 在此版本中，我们首先写入字符串的大小（包括结尾的空字符），然后只写入字符串的有用字节。
 *
 */

typedef struct {
    char name[256];
    int age;
} Me;

int main(int argc, char ** argv) {
    Me me;
    size_t length;
    if(argc < 2) {
        FILE * output = fopen("me", "w");
        length = 14; // "Marek Felsoci" + '\0'
        // Nous écrivons la taille de la chaîne / 我们写入字符串的大小
        fwrite(&length, 1, sizeof(size_t), output);
        strcpy(me.name, "Marek Felsoci");
        me.age = 29;
        // Nous écrivons uniquement les 'length' octets de la chaîne / 我们只写入字符串的 'length' 个字节
        fwrite(me.name, 1, length, output);
        fwrite(&me.age, sizeof(int), 1, output);
        fclose(output);
    } else {
        FILE * input = fopen(argv[1], "r");
        // Nous lisons la taille de la chaîne / 我们读取字符串的大小
        fread(&length, 1, sizeof(size_t), input);
        // Nous lisons uniquement les 'length' octets de la chaîne / 我们只读取字符串的 'length' 个字节
        fread(me.name, 1, length, input);
        fread(&me.age, sizeof(int), 1, input);
        fclose(input);
        printf("Je m'appelle %s et j'ai %d ans.\n", me.name, me.age);
    }
    return 0;
}

/*
 * Résultats / 结果
 *
 * Avec cette version optimisée, nous pouvons constater que le bloc de caractères nuls \0 superflus a disparu.
 * En contrepartie, le début du fichier contient 8 octets supplémentaires pour coder la taille du nom.
 * Cependant, ce surcoût de 8 octets nous permet d'économiser le stockage de dizaines d'octets inutiles (les zéros).
 *
 * 使用此优化版本，我们可以看到多余的空字符块消失了。
 * 另一方面，文件的开头现在多了 8 个字节用于编码名称的长度。
 * 但是，这 8 个字节的额外开销使我们能够避免存储数十个不必要的字节（零）。
 * 
 * Après la lecture du fichier me à l'aide de notre programme, nous pouvons confirmer que le changement du format n'a en rien affecté l'objectif du programme.
 * 通过使用我们的程序读取 me 文件后，我们可以确认格式变更并未影响程序的目标。
Je m'appelle Marek Felsoci et j'ai 29 ans.
 */
