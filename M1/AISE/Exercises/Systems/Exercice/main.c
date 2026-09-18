// 题干是：编写一个程序，能够读/写如下结构体：
// struct {
//     char nom[256];
//     int age;
// };
// 程序要用你自己的名字和年龄创建这样一个结构体，写入到一个文件中，然后再用同一个程序把它读出来并打印（可以用 printf）。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#define FILENAME "person.dat"
struct Person {
    char nom[256];
    int age;
};

int main(int argc, char **argv) {
    struct Person p1;
    if (argc == 1) {
        strncpy(p1.nom, "Jianye Shi", sizeof(p1.nom) - 1);
        p1.nom[sizeof(p1.nom) - 1] = '\0';
        p1.age = 24;
    } else if (argc == 2 && strcmp(argv[1], "--ecrire") == 0) {
        printf("Ecriture du fichier %s avec les données par le format <nom> <age>:\n", FILENAME);
        scanf("%255s %d", p1.nom, &p1.age);
        int fd = open(FILENAME, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
        if (fd == -1) {
            perror("open for write");
            return 1;
        }
        if (write(fd, &p1, sizeof(p1)) != sizeof(p1)) {
            perror("write");
            close(fd);
            return 1;
        }
        close(fd);
    } else if (argc == 2 && strcmp(argv[1], "--lire") == 0) {
    } else {
        fprintf(stderr, "Usage: %s --[ecrire|lire]\n", argv[0]);
        return 1;
    }
    // lecture fichier
    int fd = open(FILENAME, O_RDONLY);
    if (fd == -1) {
        perror("open for read");
        return 1;
    }
    if (read(fd, &p1, sizeof(p1)) != sizeof(p1)) {
        perror("read");
        close(fd);
        return 1;
    }
    close(fd);

    // affichage
    printf("Je suis %s et j'ai %d ans.\n", p1.nom, p1.age);

    return 0;
}