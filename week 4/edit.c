#include <stdio.h>
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
    char t1[1000] = {0}, t2[1000] = {0};
    strncpy(t1,s,pos); t1[pos] = '\0';
    strcpy(t2,s + pos);
    sprintf(s,"%s%s%s",t1,t,t2);
}
void delete(char *s, char *t, int pos, int n)
{
    char t1[1000] = {0}, t2[1000] = {0};
    if(pos + n >= strlen(s)) n = strlen(s) - pos;
    strncpy(t1,s,pos);
    t1[pos] = '\0';
    strncpy(t,s + pos,n);
    t[n] = '\0';
    strcpy(t2, s + pos + n);
    sprintf(s,"%s%s",t1,t2);
}
void del(char *s, int pos, int n)
{
    char t1[1000] = {0}, t2[1000] = {0};
    if(pos + n >= strlen(s)) n = strlen(s) - pos;
    strncpy(t1,s,pos);
    t1[pos] = '\0';
    strcpy(t2, s + pos + n);
    sprintf(s,"%s%s",t1,t2);
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
            if(p.op == 1) del(s,p.pos,p.n);
            else if(p.op == 2) insert(s,p.s,p.pos);
        }
    }
    puts(s);

    return 0;
}