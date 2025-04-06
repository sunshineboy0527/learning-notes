#include <stdio.h>

/*
    顺序表样例代码
*/

#define MAXSIZE 100
typedef int ElemType;

typedef struct{
    ElemType data[MAXSIZE];
    int length;
} SeqList;

//初始化链表
void initList(SeqList *L)
{
    L->length = 0;
}

//尾插法添加元素
int appendElem(SeqList *L, ElemType e)
{
    if (L->length >= MAXSIZE)
    {
        printf("顺序表已满!\n");
        return 0;
    }

    L->data[L->length] = e;
    L->length++;
}

//遍历
void listElem(SeqList *L)
{
    for (int i = 0; i < L->length; i++)
    {
        printf("%d ", L->data[i]);
    }
    printf("\n");
}

//插入元素
int insertElem(SeqList *L, int pos, ElemType e)
{
    if(L->length >= MAXSIZE)
    {
        printf("线性表已满\n");
        return 0;
    }

    if(pos < 1 || pos > L->length)
    {
        printf("插入位置错误！\n");
        return 0;
    }

    if(pos >= 1 && pos <= L->length)
    {
        for (int i = L->length - 1; i >= pos - 1; i--)
        {
            L->data[i + 1] = L->data[i];
        }
        L->data[pos - 1] = e;
        L->length++;
    }
    return 1;
}

//删除元素
int deleteElem(SeqList *L, int pos, ElemType *e)
{
    if(L->length == 0)
    {
        printf("空表\n");
        return 0;
    }

    if(pos < 1 || pos > L->length)
    {
        printf("删除数据位置有误！\n");
        return 0;
    }

    *e = L->data[pos-1]; //记录被删除的元素值
    if (pos < L->length)
    {
        for (int i = pos; i < L->length; i++)
        {
            L->data[i-1] = L->data[i];
        }
    }

    L->length--;
    return 1;
}

//查找元素首次出现的位置
int findElem(SeqList *L, ElemType e)
{
    if(L->length == 0)
    {
        printf("空列表\n");
        return 0;
    }

    for (int i = 0; i < L->length; i++)
    {
        if(L->data[i] == e)
        {
            return i + 1;
        }
    }

    return 0;
}

int main()
{
    SeqList list; //声明一个线性表
    initList(&list); //初始化
    printf("初始化成功，目前长度占用%d\n", list.length);
    printf("目前占用内存%zu字节\n", sizeof(list.data));
    //添加元素
    appendElem(&list, 2);
    appendElem(&list, 6);
    appendElem(&list, 1);
    appendElem(&list, 9);
    appendElem(&list, 3);
    listElem(&list);

    insertElem(&list, 2, 99);
    listElem(&list);

    ElemType delData;
    deleteElem(&list, 2, &delData);
    listElem(&list);
    printf("被删除的数据为：%d\n", delData);

    printf("查找9元素在顺序表中首次出现的位置是%d\n", findElem(&list, 9));

    return 0;
}