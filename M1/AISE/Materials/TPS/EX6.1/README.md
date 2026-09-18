# 练习 1 (Exercice 1)

## 题目描述

> Pour la réalisation de cet exercice, n'hésitez pas à vous inspirer de l'exemple du cours (calcul de la suite de Fibonacci).
> 在完成此练习时，请随时参考课程示例（斐波那契数列计算）。
>
> Le but de cet exercice est de réaliser :
>
> 1. une bibliothèque de chiffrement de texte nommé cesar,
> 2. un programme nommé ave-cesar utilisant cette bibliothèque pour chiffrer et déchiffrer des fichiers texte.
>
> 本练习的目的是实现：
>
> 1. 一个名为 cesar 的文本加密库，
> 2. 一个名为 ave-cesar 的程序，使用该库对文本文件进行加密和解密。
>
> La bibliothèque utilisera la méthode de chiffrement de [César](https://fr.wikipedia.org/wiki/Chiffrement_par_d%C3%A9calage), également appelée la méthode de chiffrement par décalage. Avec l'interface de programmation suivante :
> 该库将使用 [凯撒密码](https://zh.wikipedia.org/wiki/%E5%87%B1%E6%92%92%E5%AF%86%E7%A2%BC) 加密方法，也称为移位加密方法。使用以下编程接口：
>
> ```c
> int cesar_encrypt(const char * input, char * output, int l, int k);
> int cesar_decrypt(const char * input, char * output, int l, int k);
> ```
>
> la bibliothèque permettra de chiffrer et de déchiffrer une chaîne de caractères input en une chaîne de caractères output avec la clé de chiffrement k. l indique la capacité de input et de output.
> 该库将允许使用加密密钥 k 将字符串 input 加密和解密为字符串 output。 l 指示 input 和 output 的容量。

### 程序 ave-cesar

> Ce programme prendra 4 arguments en ligne de commande :
> 该程序将接受 4 个命令行参数：
>
> 1. opération (c pour chiffrement ou d pour déchiffrement), (操作：c 表示加密，d 表示解密)
> 2. chemin vers le fichier d'entrée, (输入文件路径)
> 3. chemin vers le fichier de sortie, (输出文件路径)
> 4. clé de chiffrement. (加密密钥)
>
> Exemple / 示例:
> `./ave-cesar c clear.txt encrypted.txt 2`

来源: [felsoci.sk/aise/practice.html](https://felsoci.sk/aise/practice.html#cesar)

## 解析与纠正 (Éléments de correction)

为了符合题目要求的目录结构和功能，我们需要创建以下文件：

Structure / 结构:

```txt
.
|-- cesar
|   |-- cesar.h
|   |-- cesar.c
|   |__ Makefile
|-- ave-cesar
|   |-- ave-cesar.c
|   |__ Makefile
|__ README.md
```

### 1. Bibliothèque Cesar (`cesar/cesar.c`)

凯撒密码的核心是简单的移位。需要注意的是处理字符集（通常是 ASCII 可打印字符）和取模运算。这里我们做一个简化的假设，或者处理所有字符。

```c
/* cesar/cesar.h */
#ifndef CESAR_H
#define CESAR_H

int cesar_encrypt(const char * input, char * output, int l, int k);
int cesar_decrypt(const char * input, char * output, int l, int k);

#endif

/* cesar/cesar.c */
#include "cesar.h"
#include <stdio.h>

int cesar_encrypt(const char * input, char * output, int l, int k) {
    int i;
    for (i = 0; i < l && input[i] != '\0'; i++) {
        output[i] = (char)(input[i] + k); // Simplification: décalage simple
    }
    output[i] = '\0';
    return 0;
}

int cesar_decrypt(const char * input, char * output, int l, int k) {
    return cesar_encrypt(input, output, l, -k); // Déchiffrement = Chiffrement avec clé inverse
}
```

### 2. Programme Ave-Cesar (`ave-cesar/ave-cesar.c`)

程序需要处理文件 I/O 和参数解析。

```c
/* ave-cesar/ave-cesar.c */
#include <stdio.h>
#include <stdlib.h>
#include "cesar.h" // Nécessite d'inclure les headers de la lib

#define BUF_SIZE 1024

int main(int argc, char ** argv) {
    if (argc < 5) {
        fprintf(stderr, "Usage: %s <mode: c/d> <input> <output> <key>\n", argv[0]);
        return 1;
    }

    char mode = argv[1][0];
    char * input_path = argv[2];
    char * output_path = argv[3];
    int key = atoi(argv[4]);

    FILE * fin = fopen(input_path, "r");
    if (!fin) { perror("fopen input"); return 1; }
    
    FILE * fout = fopen(output_path, "w");
    if (!fout) { perror("fopen output"); fclose(fin); return 1; }

    char buffer_in[BUF_SIZE];
    char buffer_out[BUF_SIZE];

    // Lecture ligne par ligne ou par bloc (ici simplifié avec fgets)
    while (fgets(buffer_in, BUF_SIZE, fin)) {
        if (mode == 'c') {
            cesar_encrypt(buffer_in, buffer_out, BUF_SIZE, key);
        } else if (mode == 'd') {
            cesar_decrypt(buffer_in, buffer_out, BUF_SIZE, key);
        }
        fputs(buffer_out, fout);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
```

注意：这只是一个基本实现的框架，实际完善时需要考虑 `Makefile` 的编写（静态库链接）以及更严谨的错误处理。
