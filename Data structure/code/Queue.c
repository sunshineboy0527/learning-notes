#include <stdio.h>

#define MAXSIZE 100

typedef int ElemType;

typedef struct
{
    ElemType data[MAXSIZE];
    int front;
    int rear;
} Queue;

//初始化
void initQueue(Queue *Q)
{
    Q->front = 0;
    Q->rear = 0;
}

//判断队列是否为空
int isEmpty(Queue *Q)
{
    if(Q->front == Q->rear)
    {
        printf("队列为空！\n");
        return 1;
    }
    else
    {
        return 0;
    }
}

//判断队列rear是否到头，队列是否已满
int queueFull(Queue *Q)
{
    if(Q->front > 0)
    {
        int gap = Q->front;
        for(int i = Q->front; i <= Q->rear; i++)
        {
            Q->data[i-gap] = Q->data[i];
        }
        Q->front = 0;
        Q->rear = Q->rear - gap;
        return 1;
    }
    else
    {
        printf("队列真的满了!\n");
        return 0;
    }
}

//队列入队操作
int equeue(Queue *Q, ElemType e)
{
    if(Q->rear >= MAXSIZE)
    {
        if(!queueFull(Q))
        {
            return 0;
        }
    }
    Q->data[Q->rear] = e;
    Q->rear++;
    return 1;
}

//出队列
ElemType dequeue(Queue *Q)
{
    if(Q->front == Q->rear)
    {
        printf("队列为空！\n");
        return 1;
    }
    ElemType e = Q->data[Q->front];
    Q->front++;
    return e; //返回出队的元素
}

//获取对头元素
int getHead(Queue *Q, ElemType *e)
{
    if(Q->front == Q->rear)
    {
        printf("队列为空！\n");
        return 0;
    }
    *e = Q->data[Q->front];
    return 1;
}

int main()
{
    Queue q;
    initQueue(&q);

    equeue(&q, 10);
    equeue(&q, 20);
    equeue(&q, 30);
    equeue(&q, 40);
    equeue(&q, 50);

    printf("出队元素为：%d\n", dequeue(&q));
    printf("出队元素为：%d\n", dequeue(&q));

    ElemType e;
    getHead(&q, &e);
    printf("队头元素为：%d\n", e);

    return 0;
}