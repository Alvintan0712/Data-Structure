#include <stdio.h>

int top = -1, stk[100];
void pop()
{
    if(top == -1) printf("error ");
    else printf("%d ", stk[top--]);    
}
void push(int n)
{
    if(top == 99) printf("error ");
    else stk[++top] = n;
}

int main()
{
    int n, k;
    while(scanf("%d", &k), k != -1)
    {
        switch(k)
        {
            case 0: pop(); break;
            case 1: scanf("%d", &n); push(n); break;
            default: break;
        }
    }

    return 0;
}