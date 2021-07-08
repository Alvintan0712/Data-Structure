#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Stack
{
    int num, flag;
    char op;
}arr;
int top = -1, max = -1;
char stk[1000];
int stkk[1000];
arr ep[1000];

int isop(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}
void insert(int num, char op, int flag)
{
    ep[++max].flag = flag;
    if(flag) ep[max].num = num;
    else ep[max].op = op;
}
void push(char op)
{
    stk[++top] = op;
}
char pop()
{
    return stk[top--];
}
void ppush(int num)
{
    stkk[++top] = num;
}
int ppop()
{
    return stkk[top--];
}
void getexp();

int main()
{
    int i, a, b;
    char c;

    getexp();

    top = -1;
    for(i = 0; i <= max; i++)
    {
        if(ep[i].flag) ppush(ep[i].num);
        else
        {
            c = ep[i].op;
            b = ppop();
            a = ppop();
            if(c == '+') ppush(a + b);
            if(c == '-') ppush(a - b);
            if(c == '*') ppush(a * b);
            if(c == '/') ppush(a / b);
            if(c == '%') ppush(a % b);
        }
    }
    printf("%d\n", ppop());

    return 0;
}

void getexp()
{
    int n, i;
    char c, cc;
    char s[1000];
    gets(s);

    for(i = 0; s[i] && s[i] != '='; i++)
    {
        if(isdigit(s[i]))
        {
            n = atoi(s + i);
            insert(n,0,1);
            while(isdigit(s[i + 1]) && s[i + 1]) i++;
        }

        else if(isop(s[i])) 
        {
            c = s[i];

            if(top >= 0) cc = stk[top];

            if(c == '+' || c == '-')
            {
                while(top >= 0 && cc != '(')
                {
                    cc = pop();
                    if(cc == '(') //出bug地点
                    {
                        push(cc);
                        break;
                    }
                    insert(0,cc,0);
                    if(cc == '+' || cc == '-') break;
                }
            }

            else
            {
                if(top >= 0)
                    if(cc == '*' || cc == '/' || cc == '%') 
                    {
                        cc = pop();
                        insert(0,cc,0);
                    }                    
            }

            push(c);
        }

        else if(s[i] == '(') push(s[i]);

        else if(s[i] == ')')
            while(cc = pop(), cc != '(')
                insert(0,cc,0);

    }
    while(top >= 0) cc = pop(), insert(0,cc,0);
}