#include <stdio.h>

#define MAXSIZE 100
typedef int ElemType;

typedef struct{
    ElemType data[MAXSIZE];
    int top; //栈顶指针(作为数组下标)
}Stack;

//顺序结构初始化
void initStack(Stack *s)
{
    s->top = -1;
}

//是否为空
int isEmpty(Stack *s)
{
    if(s->top == -1)
    {
        printf("栈为空！\n");
        return 1;
    }
    else
    {
        return 0;
    }
}

//进栈
int push(Stack *s, ElemType e)
{
    if(s->top >= MAXSIZE - 1)
    {
        printf("栈满了！\n");
        return 0;
    }
    s->top++;
    s->data[s->top] = e;
    return 1;
}

//出栈
int pop(Stack *s, ElemType *e)
{
    if(s->top == -1)
    {
        printf("栈是空的！\n");
        return 0;
    }
    *e = s->data[s->top];
    s->top--;
    return 1;
}

//获取栈顶元素
int getTop(Stack *s, ElemType *e)
{
    if(s->top == -1)
    {
        printf("栈是空的！\n");
        return 0;
    }
    *e = s->data[s->top];
    return 1;
}

int main()
{
    Stack s;

    ElemType e; //存储栈顶/删除的值

    //初始化栈
    initStack(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    pop(&s, &e);
    printf("出栈元素为：%d\n", e);
    getTop(&s, &e);
    printf("当前栈顶元素为：%d\n", e);

    return 0;
}