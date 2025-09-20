// 线索二叉树
// 中序遍历线索化

/*
第一遍写下来晕菜了
希望下一遍能好一些 >_<
*/

#include <stdio.h>
#include <stdlib.h>

typedef char elementType;

typedef struct THREADNODE{
    elementType data;
    struct THREADNODE* left_child;
    struct THREADNODE* right_child;
    int left_tag; // 为0时指向左孩子,为1时指向该结点的前驱
    int right_tag; // 为0时指向有孩子,为1时指向该结点的后继
}threadnode;

typedef threadnode* threadtree;

// 用于构建二叉树的字符串（前序遍历序列,#表示空节点）
char str[] = "ABDH##I##EJ###CF##G##";
int idx = 0;

// 前驱节点指针,用于线索化过程中记录上一个访问的节点
threadtree prev;

// 中序遍历线索化
// 1.头结点的left_child指向二叉树的根
// 2.头结点的right_child指向遍历的最后一个结点
// 3.第一个结点(遍历中的第一个结点,不是最高的根结点)的left_child指向头结点
// 4.最后一个结点的right_child指向头结点

// 创建二叉树 以前序顺序创建
void create_threadtree(threadtree* t)
{
    elementType ch;
    ch = str[idx++];
    if (ch == '#')
    {
        *t = NULL;
    }
    else
    {   
        *t = (threadtree)malloc(sizeof(threadnode));
        (*t) -> data = ch;

        // 递归创建左子树
        create_threadtree(&(*t)->left_child);
        /*
        在create_threadtree(&(*t)->left_child);这句话中,传入的是指向左孩子指针的地址,
        也就是指针的指针,然后在叶子末端,读取到的是#,就会把指向左孩子的指针设置为指向null,
        此时叶子末端指向左孩子的指针不再指向下一个结点,而是直接指向null
        下面再跟判断,若指向左孩子的指针不再指向下一个结点而是指向null的话
        说明该结点为叶子结点,以后就可以被线索化,把自己左标签设置为0
        右边是一样的处理方式
        总算搞懂了😭
        */
        if ((*t)->left_child!=NULL) // 如果被填入了字符,说明是个正经孩子而不是线索,更新标识信息
        {
            (*t)->left_tag = 0;
        }

        // 递归创建右子树
        create_threadtree(&(*t)->right_child);
        if ((*t)->right_child!=NULL) // 如果被填入了字符,说明是个正经孩子而不是线索,更新标识信息
        {
            (*t)->right_tag = 0;
        }

    }
}

// 给每一个结点加线索 中序顺序线索化
// 为每个节点添加线索,建立前驱和后继关系
void threading(threadtree t)
{
    if (t!=NULL) // 只要树不是空的
    {
        threading(t -> left_child); // 先一直往左边走,遍历思想

        // 处理当前结点(根节点)
        if (t -> left_child == NULL) // 让该结点的前驱线索指向前一个结点 建立前驱线索
        {
            t -> left_tag = 1;
            t -> left_child = prev;
        }
        if (prev -> right_child == NULL) // 让前一个结点的后继线索指向该结点 建立后继线索
        {
            prev -> right_tag = 1;
            prev -> right_child = t;
        }
        prev = t; // 处理完成后更新前驱结点
        threading(t -> right_child); // 中序遍历右子树 线索化右子树
        /*
        为什么最后要加一个threading(t -> right_child);?
        比如现在t是H,先执行threading(t -> left_child);,发现左孩子是空的,于是直接返回H
        然后开始线索化H,线索化完后,执行threading(t -> right_child);,左边已经处理完了,看看右边
        H的右边什么也没有,H出栈,返回D,先尝试线索化D,发现D没办法线索化
        此时再执行threading(t -> right_child);,就到了I.这样I就可以线索化了
        */
    }
}

// 线索化 中序顺序线索化
// head: 线索二叉树的头节点
// t: 原始二叉树的根节点
void inorderthreading(threadtree* head, threadtree t)
{   
    // 创建头节点
    *head = (threadtree)malloc(sizeof(threadnode));
    (*head) -> left_tag = 0;
    (*head) -> right_tag = 1;
    (*head) -> right_child = (*head); // 刚开始不知道顺序,先让头结点的右孩子指向自己本身

    if (t == NULL) // 如果树是空的,头结点的左孩子也指向自己本身
    {
        (*head) -> left_child = (*head);
    }
    else
    {
        (*head) -> left_child = t; // 1.头结点的left_child指向二叉树的根
        prev = (*head); // prev用于记录在线索化途中上一个访问的结点
        threading(t); // 对于每一个结点加线索

        // 4.最后一个结点的right_child指向头结点
        prev -> right_child = *head;
        prev -> right_tag = 1;

        (*head) -> right_child = prev; // 2.头结点的right_child指向遍历的最后一个结点

    }

}

// 基于线索遍历 中序遍历
void inorder(threadtree t) // 此处传入的t应为head,也就是头指针
{
    threadtree current;
    current = t -> left_child; // 因为头结点的left_child指向二叉树的根

    while (current!=t) // 循环遍历到最后一个结点时current当前会回到头结点,此时代表循环了一圈了,就不用再遍历了,结束循环
    {
        while(current -> left_tag == 0) // 若左孩子是正经孩子则进入循环,直到current当前结点为叶子结点
        {
            current = current -> left_child;
        }

        printf("%c ",current -> data);

        while(current -> right_tag == 1 && current -> right_child != t)
        {
            current = current -> right_child; // 此时right_child不是正经孩子,是线索.要依据线索找下一个
            printf("%c ",current -> data);
        }
        current = current -> right_child;
    }
    printf("\n");
}


int main()
{   

    // 声明头结点(但未初始化)
    threadtree head;
    threadtree t;
    // 先创建二叉树
    create_threadtree(&t);
    // 线索化二叉树
    inorderthreading(&head,t);

    // 基于线索遍历
    inorder(head);

    return 0;
}




