#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//用来判断菜单的显示方式
int flag;

//定义树，用二叉链表存储
struct tree
{
    char data;
    struct tree* lchild;
    struct tree* rchild;
};

//定义队列
struct queue
{
    struct tree* data;
    struct queue* next;
};

//定义栈
struct stack
{
    struct tree* data;
    struct stack* next;
    int Flag;
};

//重命名
typedef struct tree* Tree;
typedef struct queue* Queue;
typedef struct stack* Stack;

Tree MakeTree(char data);//创建一棵子树，并将data存入值域
Tree CreateTree();//创建一棵树，通过调用MakeTree()实现
Queue MakeQueue();//创建一个空队列
void EnQueue(Tree p, Queue Q);//进队
void DeQueue(Queue Q);//出队
Queue Next(Queue p);//队列里的下一个结点
int IsQueueEmpty(Queue Q);//队列是否为空
Tree FrontQueue(Queue Q);//返回队首元素
Stack MakeStack();//创建一个空栈
void PushStack(Tree T, Stack S);//压栈
void PopStack(Stack S);//弹栈
Tree TopStack(Stack S);//返回栈顶元素
void ReverseStack(Stack S);//将栈颠倒
int IsStackEmpty(Stack S);//判断栈是否为空
void ShowMenu();//显示菜单
void PreOrder(Tree T);//先序遍历
void InOrder(Tree T);//中序遍历
void PostOrder(Tree T);//后序遍历
void LeverOrder(Tree T);//层序遍历
void IsCompleteTree(Tree T);//判断是否为完全二叉树
int FindNode(Stack S, char data, Tree T);//寻找结点
void FindCommonAncestor(Tree T);//寻找两结点的公共祖先
void ShowTree(Tree T);//显示二叉树
int IsLineFeed(int n);//判断是否换行
int TreeHeight(Tree T);//返回二叉树的高度

int main()
{
    int a;
    Tree T = NULL;
    while (1)
    {
        ShowMenu();
        while (scanf("%d", &a) != 1 || (flag == 0 && (a != 1 && a != 0)) || (flag == 1 && !(a >= 0 && a <= 7)))
        {
            printf("输入错误，请重新输入！\n");
            fflush(stdin);
        }
        switch (a)
        {
        case 1:
            T = CreateTree();
            ShowTree(T);
            system("pause");
            system("cls");
            break;
        case 2:
            ShowTree(T);
            PreOrder(T);
            printf("\n");
            system("pause");
            system("cls");
            break;
        case 3:
            ShowTree(T);
            InOrder(T);
            printf("\n");
            system("pause");
            system("cls");
            break;
        case 4:
            ShowTree(T);
            PostOrder(T);
            printf("\n");
            system("pause");
            system("cls");
            break;
        case 5:
            ShowTree(T);
            LeverOrder(T);
            printf("\n");
            system("pause");
            system("cls");
            break;
        case 6:
            ShowTree(T);
            IsCompleteTree(T);
            system("pause");
            system("cls");
            break;
        case 7:
            ShowTree(T);
            FindCommonAncestor(T);
            system("pause");
            system("cls");
            break;
        case 0:
            system("pause");
            system("cls");
            return 0;
        }
    }
    return 0;
}

void ShowMenu()
{
    printf("############################\n");
    printf("## 1、创建二叉树          ##\n");
    if (flag == 1)
    {
        printf("## 2、先序遍历二叉树      ##\n");
        printf("## 3、中序遍历二叉树      ##\n");
        printf("## 4、后序遍历二叉树      ##\n");
        printf("## 5、层序遍历二叉树      ##\n");
        printf("## 6、判断是否为完全二叉树##\n");
        printf("## 7、判断是否有公共祖先  ##\n");
    }
    printf("## 0、退出程序            ##\n");
    printf("############################\n");
}

Stack MakeStack()
{
    Stack S = malloc(sizeof(struct stack));//有头节点
    S->next = NULL;
    return S;
}

void PushStack(Tree T, Stack S)
{
    Stack temp = malloc(sizeof(struct stack));
    temp->data = T;
    temp->next = S->next;//采用头插法
    S->next = temp;
}

void PopStack(Stack S)
{
    Stack temp = S->next;
    S->next = temp->next;
    free(temp);
}

Tree TopStack(Stack S)
{
    return S->next->data;
}

void ReverseStack(Stack S)
{
    Stack temp = MakeStack();//通过使用临时栈来实现栈的翻转
    while (!IsStackEmpty(S))
    {
        PushStack(TopStack(S), temp);
        PopStack(S);
    }
    S->next = temp->next;
}

int IsStackEmpty(Stack S)
{
    if (S->next == NULL)
        return 1;
    return 0;
}

Queue MakeQueue()
{
    Queue Q = malloc(sizeof(struct queue));//有头节点
    Q->next = NULL;
    return Q;
}

void EnQueue(Tree p, Queue Q)
{
    Queue temp = malloc(sizeof(struct queue));
    temp->data = p;
    temp->next = Q->next;
    Q->next = temp;
}

void DeQueue(Queue Q)
{
    if (Q->next != NULL)
    {
        Queue temp = Q;
        Queue pre = Q;
        while (temp->next != NULL)
        {
            pre = temp;
            temp = Next(temp);
        }
        pre->next = NULL;
        free(temp);
    }
}

Queue Next(Queue p)
{
    return p->next;
}

int IsQueueEmpty(Queue Q)
{
    if (Q->next == NULL)
        return 1;
    return 0;
}

Tree MakeTree(char data)
{
    Tree T = malloc(sizeof(struct tree));
    T->data = data;
    T->lchild = NULL;
    T->rchild = NULL;
    return T;
}

Tree FrontQueue(Queue Q)
{
    Queue temp = Q;
    while (temp->next != NULL)
    {
        temp = Next(temp);
    }
    return temp->data;
}

Tree CreateTree()
{
    fflush(stdin);
    Queue Q = MakeQueue();
    char temp;
    printf("使用层序遍历创建树：\n");
    scanf("%c", &temp);
    Tree T = NULL;
    if (temp != '#')
    {
        T = MakeTree(temp);
        EnQueue(T, Q);
    }
    while (!IsQueueEmpty(Q))
    {
        Tree p = FrontQueue(Q);
        DeQueue(Q);
        scanf("%c", &temp);
        if (temp != '#')//输入#表示无子树
        {
            p->lchild = MakeTree(temp);
            EnQueue(p->lchild, Q);
        }
        scanf("%c", &temp);
        if (temp != '#')
        {
            p->rchild = MakeTree(temp);
            EnQueue(p->rchild, Q);
        }
    }
    flag = 1;//使菜单显示发生变化
    return T;
}

/*
//先序遍历的递归算法
void PreOrder(Tree T){
    if(T){
        printf("%c ",T->data);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}
*/


//先序遍历的非递归算法
void PreOrder(Tree T)
{
    Stack S = MakeStack();
    Tree root = T;
    while (root != NULL || !IsStackEmpty(S))
    {
        while (root != NULL)
        {
            PushStack(root, S);
            printf("%c ", root->data);
            root = root->lchild;
        }
        if (!IsStackEmpty(S))
        {
            root = TopStack(S);
            PopStack(S);
            root = root->rchild;
        }
    }
}

/*
//中序遍历的递归算法
void InOrder(Tree T){
    if(T){
        InOrder(T->lchild);
        printf("%c ",T->data);
        InOrder(T->rchild);
    }
}
*/

//中序遍历的非递归算法
void InOrder(Tree T)
{
    Stack S = MakeStack();
    Tree root = T;
    while (root != NULL || !IsStackEmpty(S))
    {
        while (root != NULL)
        {
            PushStack(root, S);
            root = root->lchild;
        }
        if (!IsStackEmpty(S))
        {
            root = TopStack(S);
            PopStack(S);
            printf("%c ", root->data);
            root = root->rchild;
        }
    }
}

/*
//后序遍历的递归算法
void PostOrder(Tree T){
    if(T){
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        printf("%c ",T->data);
    }
}
*/

//后序遍历的非递归算法
void PostOrder(Tree T)
{
    Stack S = MakeStack();
    Tree root = T;
    while (root != NULL || !IsStackEmpty(S))
    {
        while (root != NULL)
        {
            PushStack(root, S);
            S->next->Flag = 1;
            root = root->lchild;
        }
        while (!IsStackEmpty(S) && S->next->Flag == 2)
        {
            printf("%c ", TopStack(S)->data);
            PopStack(S);
        }
        if (!IsStackEmpty(S))
        {
            root = TopStack(S);
            S->next->Flag = 2;//将结点进行标记
            root = root->rchild;
        }
    }
}

void LeverOrder(Tree T)
{
    Queue Q = MakeQueue();
    if (T != NULL)
        EnQueue(T, Q);
    while (!IsQueueEmpty(Q))
    {
        Tree temp = FrontQueue(Q);
        DeQueue(Q);
        printf("%c ", temp->data);
        if (temp->lchild != NULL)
            EnQueue(temp->lchild, Q);
        if (temp->rchild != NULL)
            EnQueue(temp->rchild, Q);
    }
}

void IsCompleteTree(Tree T)
{
    Queue Q = MakeQueue();
    if (T != NULL)
        EnQueue(T, Q);
    while (!IsQueueEmpty(Q))//使用层序遍历，找到第一个无左孩子或右孩子的结点
    {
        Tree temp = FrontQueue(Q);
        if (temp->lchild == NULL && temp->rchild != NULL)
        {
            break;//若无左孩子，有右孩子，则该树一定不是完全二叉树
        }
        DeQueue(Q);
        if (temp->lchild == NULL || temp->rchild == NULL)
        {
            break;
        }
        EnQueue(temp->lchild, Q);
        EnQueue(temp->rchild, Q);
    }
    while (!IsQueueEmpty(Q))//遍历栈中剩余的结点
    {
        Tree temp = FrontQueue(Q);
        if (temp->lchild != NULL || temp->rchild != NULL)
        {
            break;//若不是叶子结点，直接退出
        }
        DeQueue(Q);
    }
    if (IsQueueEmpty(Q))//如果栈为空
        printf("该树是完全二叉树\n");
    else
        printf("该树不是完全二叉树\n");
}

//通过后序遍历找到单个结点的所有祖先，并存入栈中
int FindNode(Stack S, char data, Tree T)
{
    Tree root = T;
    while (root != NULL || !IsStackEmpty(S))
    {
        while (root != NULL)
        {
            PushStack(root, S);
            S->next->Flag = 1;
            root = root->lchild;
        }
        while (!IsStackEmpty(S) && S->next->Flag == 2)
        {
            if (TopStack(S)->data == data)
            {
                return 1;
            }
            PopStack(S);
        }
        if (!IsStackEmpty(S))
        {
            root = TopStack(S)->rchild;
            S->next->Flag = 2;
        }
    }
    return 0;
}

void FindCommonAncestor(Tree T)
{
    fflush(stdin);
    char data1, data2;
    printf("请输入树内两个结点的值:\n");
    scanf("%c", &data1);
    scanf("%c", &data2);
    Stack S1 = MakeStack();
    Stack S2 = MakeStack();
    Stack S = MakeStack();
    if (!FindNode(S1, data1, T))
    {
        printf("未找到结点\n");
        goto END;
    }
    if (!FindNode(S2, data2, T))
    {
        printf("未找到结点\n");
        goto END;
    }
    ReverseStack(S1);
    ReverseStack(S2);//将栈颠倒
    //求两栈的公共子集，并将其存入新栈中
    while (!IsStackEmpty(S1) && !IsStackEmpty(S2) && TopStack(S1) == TopStack(S2))
    {
        PushStack(TopStack(S1), S);
        PopStack(S1);
        PopStack(S2);
    }
    printf("两结点的公共祖先为：\n");//打印公共祖先
END:
    while (!IsStackEmpty(S))
    {
        printf("%c ", TopStack(S)->data);
        PopStack(S);
    }
    printf("\n");
}

void ShowTree(Tree T)
{
    printf("二叉树为：\n");
    int n = 0;
    int count = 0;
    int level = TreeHeight(T);
    for (int i = 1; i <= level; i++)
    {
        count += pow(2, i - 1);
    }
    Tree EmptyTree = MakeTree('#');
    Queue Q = MakeQueue();
    if (T == NULL)
    {
        printf("该树为空树\n");
    }
    else
    {
        EnQueue(T, Q);
    }
    while (!IsQueueEmpty(Q))
    {
        Tree temp = FrontQueue(Q);
        DeQueue(Q);
        n++;
        if (n <= count)
        {
            printf("%c ", temp->data);
            if (IsLineFeed(n))
                printf("\n");
            if (temp->lchild != NULL)
            {
                EnQueue(temp->lchild, Q);
            }
            else
            {
                EnQueue(EmptyTree, Q);//若为空则使空结点进队
            }
            if (temp->rchild != NULL)
            {
                EnQueue(temp->rchild, Q);
            }
            else
            {
                EnQueue(EmptyTree, Q);
            }
        }
    }
}

int IsLineFeed(int n)
{
    int sum = 1;
    for (int i = 1;; i++)
    {
        if (n == sum)
            return 1;//如果n等于2的等比数列的和则换行
        if (sum > n)
            return 0;
        sum = sum + pow(2, i);
    }
}

int TreeHeight(Tree T)//通过递归的方式得到树的高度
{
    if (T != NULL)
    {
        int n = TreeHeight(T->lchild) + 1;
        int m = TreeHeight(T->rchild) + 1;
        return n > m ? n : m;
    }
    else
        return 0;
}
