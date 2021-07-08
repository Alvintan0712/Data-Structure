#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define N 100

typedef struct Stack
{
    int num, flag;
    char op;
}stack;
typedef struct tree
{
    stack stk;
    struct tree *l, *r;
}node;

int top = -1, ttop = -1;
int val[N];
char var[N];
stack stk[N];

int isop(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}
int print(node *root)
{
    int a, b, n;
    char c;
    if(root->stk.flag) 
    {
        n = root->stk.num;
        free(root);
        return n;
    }
    if(root->l) a = print(root->l);
    if(root->r) b = print(root->r);
    c = root->stk.op;

    if(c == '+') n = a + b;
    else if(c == '-') n = a - b;
    else if(c == '*') n = a * b;
    else if(c == '/') n = a / b;
    else if(c == '%') n = a % b;

    return n;
}

int main()
{
    int n, k, i, a, b, num;
    char s[N] = {0}, c;
    node *root[N];

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
            while(isdigit(s[n + 1]) && s[n]) n++;
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
            //sini ada bug
            if(isop(var[ttop]) && ttop >= 0)
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
                else if(s[n] == '*' || s[n] == '/' || s[n] == '%')
                {
                    c = var[ttop];
                    if((c == '*' || c == '/' || c == '%') && ttop >= 0)//top为* /才pop
                    {
                        c = var[ttop--];
                        stk[++top].op = c;
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

    //build tree
    ttop = -1;
    node *p, *q, *new;
    for(i = 0; i <= top; i++)
    {
        new = (node*)malloc(sizeof(node));
        new->stk = stk[i];
        new->l = NULL; new->r = NULL;
        if(stk[i].flag) root[++ttop] = new;
        else
        {
            q = root[ttop--];
            p = root[ttop--];
            new->l = p; new->r = q;

            root[++ttop] = new;
        }
    }
    p = root[0];

    // calculate it
    if(p->stk.flag) printf("%d ", p->stk.num);
    else printf("%c ", p->stk.op);
    if(p->l)
        if(p->l->stk.flag) printf("%d ", p->l->stk.num);
        else printf("%c ", p->l->stk.op);
    if(p->r)
        if(p->r->stk.flag) printf("%d ", p->r->stk.num);
        else printf("%c ", p->r->stk.op);
    puts("");

    printf("%d\n", print(p));

    return 0;
}