#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack
{
    int op, n, pos;
    char s[1000];
}stack;
stack stk[1000];
int top = -1;

void insert(char *s, char *t, int pos)
{
    char buf[1024] = {0};
    strcpy(buf,t);
    strcat(buf,s + pos);
    strcpy(s + pos,buf);
}
void delete(char *s, char *t, int pos, int n)
{
    int end;
    if(pos + n >= strlen(s)) n = strlen(s) - pos;
    strncpy(t,s + pos,n);
    end = strlen(s) - n;

    memmove(s + pos,s + pos + n,strlen(s + pos + n));
    s[end] = '\0';
}
void push(int op, int pos, char *t)
{
    stack new;
    new.op = op;
    new.pos = pos;
    new.n = strlen(t);
    strcpy(new.s,t);

    stk[++top] = new;
}
stack pop()
{
    return stk[top--];
}

int main()
{
    int op, n, pos;
    char s[1000], t[1000];
    stack p;
    gets(s);
    scanf("%d", &n);
    while(n--)
    {
        memset(t,0,sizeof(t));
        scanf("%d%d %s", &op, &pos, t);
        push(op,pos,t);
    }
    while(scanf("%d", &op), op != -1)
    {
        memset(t,0,sizeof(t));
        if(op == 1)
        {
            scanf("%d %s", &pos, t);
            insert(s,t,pos);
            push(op,pos,t);
        }
        else if(op == 2)
        {
            scanf("%d%d", &pos, &n);
            delete(s,t,pos,n);
            push(op,pos,t);
        }
        else if(op == 3)
        {
            if(top == -1) continue;
            p = pop();
            if(p.op == 1) delete(s,t,p.pos,p.n);
            else if(p.op == 2) insert(s,p.s,p.pos);
        }
    }
    puts(s);

    return 0;
}