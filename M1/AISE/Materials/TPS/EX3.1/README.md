# 练习 1 (Exercice 1)

## 题目描述

> Écrivez un programme capable d'écrire une structure de données telle que `struct { char nom[256]; int age; }` dans un fichier, puis de la relire et d'afficher son contenu sur la sortie standard selon le modèle suivant.
> 编写一个程序，能够将数据结构 `struct { char nom[256]; int age; }` 写入文件，然后重新读取并按照以下格式显示其内容。
>
> `Je m'appelle Marek Felsoci et j'ai 29 ans.`
> `我叫 Marek Felsoci，今年 29 岁。`

来源: [felsoci.sk/aise/practice.html](https://felsoci.sk/aise/practice.html#files)

## 解析与纠正 (Éléments de correction)

我们从定义一个名为 `Me` 的新数据类型开始程序，该类型对应于题目中提出的结构。

程序的核心由两种运行模式组成：

1. 如果程序无参数运行，我们用关于我们的信息填充一个 `Me` 结构，然后将其元素写入当前目录中名为 `me` 的只写文件中。
2. 如果程序使用至少一个命令行参数运行，我们将第一个参数视为包含 `Me` 结构元素的文件位置。然后我们以只读方式打开该文件，并从其内容填充 `Me` 结构。最后，我们按照题目中提出的模型显示该结构的元素。

```c
/* Version Basique (Basic Version) */
#include <stdio.h>
#include <string.h>
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
```

为了避免存储多余的空字符（`\0`），我们可以调整文件格式，例如，在其中包含有关名称实际长度的信息。以下是此调整的实现（**改进版**）。

```c
/* Version Optimisée (Optimal Version) */
#include <stdio.h>
#include <string.h>
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
        fwrite(&length, 1, sizeof(size_t), output);
        strcpy(me.name, "Marek Felsoci");
        me.age = 29;
        fwrite(me.name, 1, length, output);
        fwrite(&me.age, sizeof(int), 1, output);
        fclose(output);
    } else {
        FILE * input = fopen(argv[1], "r");
        fread(&length, 1, sizeof(size_t), input);
        fread(me.name, 1, length, input);
        fread(&me.age, sizeof(int), 1, input);
        fclose(input);
        printf("Je m'appelle %s et j'ai %d ans.\n", me.name, me.age);
    }
    return 0;
}
```

我们可以看到，多余的空字符块消失了。另一方面，文件的开头现在多了 8 个字节用于编码名称的长度。但是，通过增加 8 个字节，我们能够避免存储数十个字节。

## 代码详解

本练习展示了如何使用 `fwrite` 和 `fread` 进行二进制文件 I/O。

1. **结构体定义**:
    定义 `Me` 结构体，包含固定大小的字符数组 `name` (256字节) 和整数 `age`。

2. **写入模式**:
    如果程序无参数运行 (`argc < 2`)：
    - 初始化结构体数据。
    - 使用 `fopen(..., "w")` 打开文件 "me"。
    - `fwrite` 写入 `name` 和 `age`。
        - **注意**: 即使名字很短，也会写入完整的 256 字节（包含大量 `\0`）。这是为了简化读取时的定位，但也造成了空间浪费。

3. **读取模式**:
    如果程序带参数运行 (`argc >= 2`)：
    - 使用 `fopen(argv[1], "r")` 打开指定文件。
    - `fread` 读取 256 字节到 `name`，读取一个 `int` 到 `age`。
    - 打印格式化字符串。

4. **改进版 (Opt)**:
    课程还提及了一种改进版，先写入名字长度 `length`，再写入名字内容，从而节省空间。本练习主要实现基础版。
