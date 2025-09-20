// 线索二叉树
// 这是第2遍写,还是有很多不熟,但是加油!
// 中序遍历线索化

// 注意图中用的是中序遍历

#include <stdio.h>
#include <stdlib.h>



typedef char elementType;

typedef struct THREADNODE{
    elementType data;
    struct THREADNODE* left_child;
    struct THREADNODE* right_child;
    int left_tag;
    int right_tag;
}threadnode;

typedef  threadnode* threadtree;

// 以前序遍历顺序写出二叉树的内容
char str[] = "ABDH##I##EJ###CF##G##";

// 前驱结点的指针,指向上一个操作的结点 全局变量
threadtree prev;

// 用于记录读取二叉树内容字符串str的位置 全局变量
int idx = 0;

// 创建树 以前序顺序创建
void create_threadtree(threadtree* t) // threadtree t只能更改结点内容,但是更改不了t的指向(不能更改t指向下一个或其他结点,所以需要用指针(二级指针))
{   
    // *t 不是结点,而是指向结点的指针
    elementType ch = str[idx++];
    if ( ch == '#')
    {
        *t = NULL;
    }
    else
    {   
        // 由于是前序遍历顺序创建,因此先处理根节点
        // 创建该结点
        *t = (threadtree)malloc(sizeof(threadnode));
        (*t) -> data = ch;

        // 处理左结点
        create_threadtree(&(*t)->left_child);
        if ((*t)->left_child!=NULL)
        {
            (*t) -> left_tag = 0;
        }

        // 处理右结点
        create_threadtree(&(*t)->right_child);
        if ((*t)->right_child!=NULL)
        {
            (*t) -> right_tag = 0;
        }

        // 该函数出栈
    }
}

// 线索化内部函数 给叶子结点建立线索
void threading(threadtree t)
{
    if (t!=NULL)
    {
        threading(t -> left_child);

        // 处理根节点
        if (t -> left_child == NULL) // 左边负责建立前驱线索
        {
            t -> left_tag = 1;
            t -> left_child = prev;
        }
        if (prev -> right_child == NULL) // 前驱结点建立后继线索到该结点
        {
            prev -> right_tag = 1;
            prev -> right_child = t;
        }

        prev = t; // 更新前驱结点

        threading(t -> right_child); // IMPORTANT 自己写总是忘
    }


}

// 线索化二叉树
void inorderthreading(threadtree* head, threadtree t)
{   
    // head此时是一个指向结点的指针的指针,*head即为指向结点的指针
    // 此时*head相当于threadnode**head
    *head = (threadtree)malloc(sizeof(threadnode));
    (*head) -> left_tag = 0;
    (*head) -> right_tag = 1;

    if (t==NULL) // 如果树是空的,头结点的左孩子也指向自己本身
    {
        (*head) -> left_child = (*head);
    }
    else
    {
        (*head) -> left_child = t;

        prev = (*head);
        threading(t);

        // 执行完threading(t)后,此时prev就变成了中序遍历的最后一个结点
        (*head) -> right_child = prev;
        prev -> right_tag = 1;
        prev -> right_child = (*head);
    }
}

// 花了1个小时,总算写完了创建二叉树和线索化,接下来写遍历!

// 线索化遍历 中序遍历为顺序
void thread_traverse(threadtree t) // 此处传入的t应为head,也就是头指针
{
    threadtree current; // 声明一个遍历时用的指针,该指针表示指向当前结点的指针;
    current = t -> left_child; // current此时是指向第一个结点A的指针

    while (current != t) // 循环遍历到最后一个结点时current当前会回到头结点,此时代表循环了一圈了,就不用再遍历了,结束循环
    {
        while (current -> left_tag == 0) // 先尽量往左走,走到最左边
        {
            current = current -> left_child;
        }
        printf("%c ",current -> data);

        while (current -> right_tag == 1 && current -> right_child != t)
        {
            current = current -> right_child;
            printf("%c ",current -> data);
        }
        current = current -> right_child;
    }
    printf("\n");
}





// 主函数
int main()
{
    threadtree tree; // 建立的是指向结点的指针
    threadtree head; // 头指针 head是一个指向结点的指针

    // 创建二叉树
    create_threadtree(&tree);

    // 线索化二叉树
    inorderthreading(&head,tree);

    // 遍历二叉树
    thread_traverse(head);

    return 0;
}