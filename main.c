#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//�����жϲ˵�����ʾ��ʽ
int flag;

//���������ö�������洢
struct tree
{
    char data;
    struct tree* lchild;
    struct tree* rchild;
};

//�������
struct queue
{
    struct tree* data;
    struct queue* next;
};

//����ջ
struct stack
{
    struct tree* data;
    struct stack* next;
    int Flag;
};

//������
typedef struct tree* Tree;
typedef struct queue* Queue;
typedef struct stack* Stack;

Tree MakeTree(char data);//����һ������������data����ֵ��
Tree CreateTree();//����һ������ͨ������MakeTree()ʵ��
Queue MakeQueue();//����һ���ն���
void EnQueue(Tree p, Queue Q);//����
void DeQueue(Queue Q);//����
Queue Next(Queue p);//���������һ�����
int IsQueueEmpty(Queue Q);//�����Ƿ�Ϊ��
Tree FrontQueue(Queue Q);//���ض���Ԫ��
Stack MakeStack();//����һ����ջ
void PushStack(Tree T, Stack S);//ѹջ
void PopStack(Stack S);//��ջ
Tree TopStack(Stack S);//����ջ��Ԫ��
void ReverseStack(Stack S);//��ջ�ߵ�
int IsStackEmpty(Stack S);//�ж�ջ�Ƿ�Ϊ��
void ShowMenu();//��ʾ�˵�
void PreOrder(Tree T);//�������
void InOrder(Tree T);//�������
void PostOrder(Tree T);//�������
void LeverOrder(Tree T);//�������
void IsCompleteTree(Tree T);//�ж��Ƿ�Ϊ��ȫ������
int FindNode(Stack S, char data, Tree T);//Ѱ�ҽ��
void FindCommonAncestor(Tree T);//Ѱ�������Ĺ�������
void ShowTree(Tree T);//��ʾ������
int IsLineFeed(int n);//�ж��Ƿ���
int TreeHeight(Tree T);//���ض������ĸ߶�

int main()
{
    int a;
    Tree T = NULL;
    while (1)
    {
        ShowMenu();
        while (scanf("%d", &a) != 1 || (flag == 0 && (a != 1 && a != 0)) || (flag == 1 && !(a >= 0 && a <= 7)))
        {
            printf("����������������룡\n");
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
    printf("## 1������������          ##\n");
    if (flag == 1)
    {
        printf("## 2���������������      ##\n");
        printf("## 3���������������      ##\n");
        printf("## 4���������������      ##\n");
        printf("## 5���������������      ##\n");
        printf("## 6���ж��Ƿ�Ϊ��ȫ������##\n");
        printf("## 7���ж��Ƿ��й�������  ##\n");
    }
    printf("## 0���˳�����            ##\n");
    printf("############################\n");
}

Stack MakeStack()
{
    Stack S = malloc(sizeof(struct stack));//��ͷ�ڵ�
    S->next = NULL;
    return S;
}

void PushStack(Tree T, Stack S)
{
    Stack temp = malloc(sizeof(struct stack));
    temp->data = T;
    temp->next = S->next;//����ͷ�巨
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
    Stack temp = MakeStack();//ͨ��ʹ����ʱջ��ʵ��ջ�ķ�ת
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
    Queue Q = malloc(sizeof(struct queue));//��ͷ�ڵ�
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
    printf("ʹ�ò��������������\n");
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
        if (temp != '#')//����#��ʾ������
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
    flag = 1;//ʹ�˵���ʾ�����仯
    return T;
}

/*
//��������ĵݹ��㷨
void PreOrder(Tree T){
    if(T){
        printf("%c ",T->data);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}
*/


//��������ķǵݹ��㷨
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
//��������ĵݹ��㷨
void InOrder(Tree T){
    if(T){
        InOrder(T->lchild);
        printf("%c ",T->data);
        InOrder(T->rchild);
    }
}
*/

//��������ķǵݹ��㷨
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
//��������ĵݹ��㷨
void PostOrder(Tree T){
    if(T){
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        printf("%c ",T->data);
    }
}
*/

//��������ķǵݹ��㷨
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
            S->next->Flag = 2;//�������б��
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
    while (!IsQueueEmpty(Q))//ʹ�ò���������ҵ���һ�������ӻ��Һ��ӵĽ��
    {
        Tree temp = FrontQueue(Q);
        if (temp->lchild == NULL && temp->rchild != NULL)
        {
            break;//�������ӣ����Һ��ӣ������һ��������ȫ������
        }
        DeQueue(Q);
        if (temp->lchild == NULL || temp->rchild == NULL)
        {
            break;
        }
        EnQueue(temp->lchild, Q);
        EnQueue(temp->rchild, Q);
    }
    while (!IsQueueEmpty(Q))//����ջ��ʣ��Ľ��
    {
        Tree temp = FrontQueue(Q);
        if (temp->lchild != NULL || temp->rchild != NULL)
        {
            break;//������Ҷ�ӽ�㣬ֱ���˳�
        }
        DeQueue(Q);
    }
    if (IsQueueEmpty(Q))//���ջΪ��
        printf("��������ȫ������\n");
    else
        printf("����������ȫ������\n");
}

//ͨ����������ҵ����������������ȣ�������ջ��
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
    printf("������������������ֵ:\n");
    scanf("%c", &data1);
    scanf("%c", &data2);
    Stack S1 = MakeStack();
    Stack S2 = MakeStack();
    Stack S = MakeStack();
    if (!FindNode(S1, data1, T))
    {
        printf("δ�ҵ����\n");
        goto END;
    }
    if (!FindNode(S2, data2, T))
    {
        printf("δ�ҵ����\n");
        goto END;
    }
    ReverseStack(S1);
    ReverseStack(S2);//��ջ�ߵ�
    //����ջ�Ĺ����Ӽ��������������ջ��
    while (!IsStackEmpty(S1) && !IsStackEmpty(S2) && TopStack(S1) == TopStack(S2))
    {
        PushStack(TopStack(S1), S);
        PopStack(S1);
        PopStack(S2);
    }
    printf("�����Ĺ�������Ϊ��\n");//��ӡ��������
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
    printf("������Ϊ��\n");
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
        printf("����Ϊ����\n");
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
                EnQueue(EmptyTree, Q);//��Ϊ����ʹ�ս�����
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
            return 1;//���n����2�ĵȱ����еĺ�����
        if (sum > n)
            return 0;
        sum = sum + pow(2, i);
    }
}

int TreeHeight(Tree T)//ͨ���ݹ�ķ�ʽ�õ����ĸ߶�
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
