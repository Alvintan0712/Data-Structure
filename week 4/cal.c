#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define N 100

typedef struct Stack
{
    int num, flag;
    char op;
}stack;

int top = -1, ttop = -1;
int val[N];
char var[N];
stack stk[N];

int isop(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}
void printStack()
{
    for(int i = 0; i <= top; i++) 
    {
        if(stk[i].flag) printf("%d ", stk[i].num);
        else printf("%c ", stk[i].op);
    }
    puts("");
}

int main()
{
    int n, k, i, a, b, num;
    char s[N] = {0}, c;

    gets(s);
    for(n = 0, k = -1; s[n]; n++, k++)
    {
        if(isdigit(s[n])) //数字处理
        {
            num = atoi(&s[n]);

            //若是第一个数字, 则将符号合并
            if(!k && ttop >= 0)
            {
                c = var[ttop--];
                if(c == '-') num *= -1;
            }

            //输出在stk stack
            stk[++top].num = num;
            stk[top].flag = 1;

            //略过其他数字
            while(isdigit(s[n + 1])) n++;
        }
        else if(isop(s[n])) //运算符处理
        {
            if(s[n] == '+' || s[n] == '-')
            {
                while(ttop >= 0 && var[ttop] != '(')
                {
                    stk[++top].op = var[ttop--];
                    stk[top].flag = 0;
                    if(stk[top].op == '+' || stk[top].op == '-') break;
                }
            }
            else
            {
                if(ttop >= 0)
                {
                    //若是* /, 就pop一次
                    if(var[ttop] == '*' || var[ttop] == '/' || var[ttop] == '%')
                    {
                        stk[++top].op = var[ttop--];
                        stk[top].flag = 0;
                    }
                }
            }

            var[++ttop] = s[n]; //输入在var stack
        }
        else if(s[n] == '(') //左括号处理
        {
            k = -2;// 重置起点
            var[++ttop] = s[n];//输入进var stack
        }
        else if(s[n] == ')') //右括号处理
        {
            while(1)
            {
                if(ttop >= 0) c = var[ttop--];
                if(c == '(') break;

                //输出到stk stack
                stk[++top].op = c;
                stk[top].flag = 0;
            }
        }
        else if(s[n] == '=') break;
        else 
        {
            k--;
            continue;
        }
    }
    while(ttop >= 0)
    {
        c = var[ttop--];
        stk[++top].op = c;
        stk[top].flag = 0;
    }

    ttop = -1;//回收利用在val stack

    for(i = 0; i <= top; i++)
    {
        if(stk[i].flag) val[++ttop] = stk[i].num;
        else
        {
            b = val[ttop--];
            a = val[ttop--];
            c = stk[i].op;
            if(c == '+') val[++ttop] = a + b;
            else if(c == '-') val[++ttop] = a - b;
            else if(c == '*') val[++ttop] = a * b;
            else if(c == '/') val[++ttop] = a / b;
            else if(c == '%') val[++ttop] = a % b;
        }
    }
    printf("%d\n", val[ttop]);

    return 0;
}