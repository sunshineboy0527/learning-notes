#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct node{
    ElemType data;
    struct node *next;
}Node;

//单链表初始化
Node* initList()
{
    Node *head = (Node *)malloc(sizeof(Node));
    head->data = 0;
    head->next = NULL;
    return head;
}

//单链表头插法
int insertHead (Node* L, ElemType e)
{
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = e;
    p->next = L->next;
    L->next = p;
    return 1;
}

//单链表遍历
void listNode(Node* L)
{
    Node *p = L->next;
    while(p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf(("\n"));
}

//单链表获取尾节点
Node* get_tail(Node *L)
{
    Node *p = L;
    while(p->next != NULL)
    {
        p = p->next;
    }
    return p;
}

//单链表尾插法
Node* insertTail(Node *tail, ElemType e)
{
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = e;
    tail->next = p;
    p->next = NULL;
    return p;
}

//单链表在指定位置插入数据
int insertNode(Node *L, int pos, ElemType e)
{
    Node *p = L;
    int i = 0;
    //获取要插入位置前一个节点
    while(i < pos-1)
    {
        p = p->next;
        i++;
        if(p == NULL)
        {
            printf("插入位置有误！");
            return 0;
        }
    }

    //开始进行插入操作
    Node *q = (Node *)malloc(sizeof(Node));
    q->data = e;
    q->next = p->next;
    p->next = q;
    return 1;
}

//单链表删除指定位置数据
int deleteNode(Node *L, int pos)
{
    Node *p = L;
    int i = 0;
    //获取要删除节点的前驱节点
    while(i < pos-1)
    {
        p = p->next;
        i++;
        if(p == NULL)
        {
            return 0;
        }
    }

    if(p->next == NULL)
    {
        printf("要删除的位置有误\n");
        return 0;
    }

    //开始进行删除操作
    Node *q = p->next;
    p->next = q->next;
    free(q);
    return 1;
}

//获取单链表长度
int listLength(Node* L)
{
    Node *p = L;
    int len = 0;
    //从头结点开始遍历，直到尾节点
    while (p != NULL)
    {
        p = p->next;
        len++;
    }
    return len;
}

//释放单链表
void freeList(Node* L)
{
    Node *p = L->next;
    Node *q;
    //循环一次释放节点
    while (p != NULL)
    {
        q = p->next;
        free(p);
        p = q;
    }
    L->next = NULL;
}

int main()
{
    Node *list1 = initList();
    Node *list2 = initList();
    //头插法测试
    insertHead(list1, 10);
    insertHead(list1, 20);
    insertHead(list1, 30);

    listNode(list1);

    //尾插法测试
    Node *tail = get_tail(list2);

    tail = insertTail(tail, 10);
    tail = insertTail(tail, 20);
    tail = insertTail(tail, 30);

    listNode(list2);

    //插入测试
    insertNode(list2, 2, 99);
    listNode(list2);

    //删除测试
    deleteNode(list2, 2);
    listNode(list2);

    //测试获取长度
    printf("该链表长度为:%d \n", listLength(list2));

    freeList(list2);
    printf("释放链表后，该链表长度为:%d \n", listLength(list2));

    return 0;
}