/*

树的基本知识
结点: 树中的一个独立单元
结点的度: 结点拥有的子树数称为结点的度
树的度: 树内各结点度的最大值
叶子: 度为0的结点或终端结点
非终端结点: 度不为0度结点
双亲和孩子: 结点的子树的根称为该结点度孩子,相应地,该结点称为孩子的双亲
层次: 结点的层次从根开始定义,根为第一层,根的孩子为第二层,以此类推

       1
      / \
     2   3
    / \   \
   4   5   6
  /
 7

 根节点(Root): 1
 叶子节点(Leaf nodes): 7, 5, 6
 内部节点(Internal nodes): 1, 2, 3, 4
 父节点(Parent nodes):
    1 是 2 和 3 的父节点
    2 是 4 和 5 的父节点
    3 是 6 的父节点
    4 是 7 的父节点
 子节点(Child nodes):
    2 和 3 是 1 的子节点
    4 和 5 是 2 的子节点
    6 是 3 的子节点
    7 是 4 的子节点
 兄弟节点(Sibling nodes):
    2 和 3 是兄弟节点
    4 和 5 是兄弟节点
 节点的度(Degree of nodes):
    1 的度为 2
    2 的度为 2
    3 的度为 1
    4 的度为 1
    5 的度为 0
    6 的度为 0
    7 的度为 0
 树的度(Degree of tree): 2
 层次(Level):
    第1层: 1
    第2层: 2, 3
    第3层: 4, 5, 6
    第4层: 7
 深度/高度(Depth/Height): 4

完全二叉树特点: 没有左子树,不能有右子树;上一层没有铺满,不能有下一层
这个解释更好些: 若二叉树的深度为 h，除第 h 层外，其它各层的结点数都达到最大个数，第 h 层所有的叶子结点都连续集中在最左边，这就是完全二叉树。
*/
// 顺序结构除了满二叉树和完全二叉树外比较浪费空间

// 二叉树的存储结构 链式结构

#include <stdio.h>
#include <stdlib.h>

typedef char elementType;

typedef struct TREENODE{
    elementType data;
    struct TREENODE* left_child;
    struct TREENODE* right_child;
}treenode;

typedef treenode* bitree; // binary_tree缩写为bitree,声明一个bitree变量相当于声明了一个treenode指针


char str[] = "ABDH#K###E##CFI###G#J##"; // 按照前序遍历设计的
/*
                A
        B               C
    D       E       F      G
H                 I           J
   K
*/
int idx = 0;

// 以前序遍历的思路创建一棵树 有点复杂,建议认真搞懂
void createtree(bitree *t)
{
    elementType ch; // 创建了一个char类型的变量
    ch = str[idx++]; // 读取str[]中的字符
    if (ch == '#')
    {
        *t = NULL; // 此时*t对应的是某个结点的子节点(left或right)
    }
    else
    {
        *t = (bitree)malloc(sizeof(treenode)); // 创建一个结点并给其分配一块内存
        (*t) -> data = ch; // 该结点存储的内容为读取的内容
        createtree(&(*t)->left_child); // 去创建该结点的左结点
        createtree(&(*t)->right_child); // 去创建该结点的右结点
    }
}

// 非递归遍历就是自己写一个栈自己进栈出栈即可

// 前序遍历 递归思路
void preorder(bitree t) // t存的是二叉树的根
{
    if (t == NULL)
    {
        return;
    }
    else
    {
        printf("%c ",t -> data);

        // 先左后右(没有强制要求)
        // 会先把二叉树的左边全部遍历完,这就叫做前序遍历
        preorder(t -> left_child);
        preorder(t -> right_child);
    }
}

/*
        A
      /   \
     B     C
    / \   / \
   D   E F   G
  /
 H

前序遍历: 先访问根节点，再访问左子树，最后访问右子树 A → B → D → H → E → C → F → G
中序遍历: 先访问左子树，再访问根节点，最后访问右子树 H → D → B → E → A → F → C → G
后序遍历: 先访问左子树，再访问右子树，最后访问根节点 H → D → E → B → F → G → C → A

什么序就是根在哪里,做一定在右前

*/


// 中序遍历 递归思路
void inorder(bitree t)
{
    if (t == NULL)
    {
        return;
    }
    else
    {
        inorder(t -> left_child);
        printf("%c ",t -> data);
        inorder(t -> right_child);
    }
}

// 后序遍历 递归思路
void postorder(bitree t)
{
    if (t == NULL)
    {
        return;
    }
    else
    {
        postorder(t -> left_child);
        postorder(t -> right_child);
        printf("%c ",t -> data);
    }
}

int main()
{
    bitree t;
    createtree(&t);
    preorder(t);
    printf("\n");
    inorder(t);
    printf("\n");
    postorder(t);
    printf("\n");
}

/*

a.前序遍历 b.中序遍历 c.后序遍历

已知a,b或b,c都可以唯一确定一棵二叉树
已知a,c不能确定一棵二叉树



*/


