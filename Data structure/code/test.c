#include <stdio.h>

void swap1(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void swap2(int a, int b)
{
    
}

int main()
{
    int m = 10;
    int n = 5;
    swap1(&m, &n);

    printf("m=%d, n=%d", m, n);

    return 0;
}