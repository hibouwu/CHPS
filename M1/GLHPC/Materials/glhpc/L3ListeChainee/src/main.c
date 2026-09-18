/* Liste chaînée de n = 5 nœuds
   由 n = 5 个节点构成的链表
         .---------.    .---------.           .--------------.
         | val = 4 |    | val = 3 |           | val = 0      |
 head -> | next  --|--> | next  --|--> ... -> | next =  NULL |
         '---------'    '---------'           '--------------'
 */

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

// 单链表节点，存储整数值和指向下一个节点的指针
struct Node
{
    int val;
    struct Node *next;
};

// 构建包含 n 个节点的链表，头插法生成递减序列
struct Node *init_list(int n)
{
    struct Node *head = NULL;
    for (int i = 0; i < n; ++i) {
        struct Node *p = malloc(sizeof *p);
        assert(p != NULL);
        p->val = i;
        p->next = head;
        head = p;
    } 
    return head;
}

// 依次释放整条链表的节点内存
void delete_list(struct Node *head)
{
    while (head)
    {
        struct Node *next = head->next;
        free(head);
        head = next;
    }
}

// 删除指定下标的节点，返回新的表头指针
struct Node *delete_node(struct Node *head, int index)
{
    if (head == NULL) return NULL;

    if (index == 0)
    {
        struct Node *next = head->next;   // 保留头结点的后继，避免失联
        free(head);                       // 释放原头结点
        return next;                      // 返回新的头结点
    }

    struct Node *prev = head;            // prev 最终指向被删节点的前驱
    struct Node *curr = head->next;      // curr 用于遍历到目标节点
    int i = 1;
    while (curr && i < index)
    {
        prev = curr;                     // 向前推进前驱
        curr = curr->next;               // 向前推进当前节点
        ++i;                             // 更新当前索引
    }

    if (curr)
    {
        prev->next = curr->next;         // 前驱指向当前节点的下一个节点
        free(curr);                      // 释放当前节点
    }

    return head;
}

// 打印链表内容，便于验证结构
void print_list(struct Node *head)
{
    struct Node *p = head;
    while (p)
    {
        printf("%d -> ", p->val);
        p = p->next;
    }
    printf("NULL\n");
}


int main()
{
    int n = 5;

    struct Node *head = init_list(n);        // 构建链表：4 -> 3 -> 2 -> 1 -> 0
    head = delete_node(head, 2);             // 删除索引 2 的节点（值为 2）
    print_list(head);                        // 输出当前链表结构
    delete_list(head);                       // 释放所有节点，避免内存泄漏
    return 0;
}
