// 二叉树的层序遍历

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef char elementType;



typedef struct TREENODE{
    elementType data;
    struct TREENODE* left_child;
    struct TREENODE* right_child;
}treenode;

typedef treenode* bitree;

typedef struct QUEUE{
    bitree* data;
    int front;
    int rear;
}queue;



// 树的内容 以前序遍历的方式
char str[] = "ABDH#K###E##CFI###G#J##";

// 创建一个树 前序遍历的方式

int idx = 0;
void create_binarytree(bitree *t)
{   
    
    elementType ch = str[idx++];
    // 如果已经到达字符串末尾，则设置为NULL并返回
    if (str[idx] == '\0') {
        *t = NULL;
        return;
    }
    

    if (ch == '#')
    {
        *t = NULL;
    }
    else
    {
        *t = (bitree)malloc(sizeof(treenode));
        (*t) -> data = ch;

        printf("Processing char: %c\n", ch);
        create_binarytree(&(*t)->left_child);
        create_binarytree(&(*t)->right_child);
    }

}

// 初始化队列 动态内存分配
queue* initialize_queue()
{
    queue* new = (queue*)malloc(sizeof(queue));
    new -> front = 0;
    new -> rear = 0;
    new -> data = (bitree*)malloc(sizeof(bitree)*MAXSIZE);
    return new;
}

// 入队
int add_queue(queue* q, bitree add_data)
{
    if ((q -> rear + 1)%MAXSIZE == q -> front)
    {
        printf("\n\n真满了\\n\n");
        return 0;
    }
    else
    {
        q -> data [q -> rear] = add_data;
        q -> rear = (q -> rear + 1) % MAXSIZE;
        return 1;
    }
}

// 出队
int out_queue(queue* q, bitree* out_data)
{
    if (q -> rear == q -> front)
    {
        printf("\n\n队列是空的\n\n");
        return 0;
    }
    else
    {
        *out_data = q -> data [q -> front];
        q -> front = (q -> front + 1) % MAXSIZE;
        return 1;
    }
}

// 判断队列是否是空的
int isempty(queue *q)
{
    if (q -> front == q -> rear)
    {
        printf("\n\n队列已空\n\n");
        return 1;
    }
    else
    {
        return 0;
    }
}

// 判断队列中的数量
int number_queue(queue* q)
{
    int num = (q -> rear - q -> front + MAXSIZE) % MAXSIZE;
    return num;
}

// 判断树的层数
int mainfunc(queue* q, bitree root)
{   
    if (root == NULL) {
        return 0; // 如果根节点为NULL，深度为0
    }
    
    add_queue(q, root);
    int depth = 0;
    while(!isempty(q))
    {
        int count = number_queue(q);
        while(count>0)
        {
            treenode* current;
            int res = out_queue(q,&current);
            if (res == 0) {
                printf("out_queue failed!\n");
                break; // 出队失败时跳出内层循环
            }
            count --;
            if (current -> left_child != NULL)
            {
                add_queue(q, current -> left_child);
            }
            if (current -> right_child != NULL)
            {
                add_queue(q, current -> right_child);
            }
        }
        depth ++;
    }
    return depth;
}

int main()
{
    bitree t;
    create_binarytree(&t);
    queue* q = initialize_queue();
    
    printf("\n\n%d \n",mainfunc(q,t));




    return 0;
}
