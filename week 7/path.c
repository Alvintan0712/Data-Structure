#include <stdio.h>
#include <stdlib.h>
#define N 1000

typedef struct Ver ver;
typedef struct Node node;
struct Ver
{
    int data, flag;
    node *nxt;
};
struct Node
{
    int weight;
    ver *head;
    node *nxt;
};

ver *head[N];
node* CreateNode(int data, int weight)
{
    node *new = (node*)malloc(sizeof(node));
    new->head = head[data]; new->nxt = NULL; new->weight = weight;
    return new;
}
ver* CreateHead(int vex)
{
    head[vex] = (ver*)malloc(sizeof(ver));
    head[vex]->data = vex; head[vex]->nxt = NULL; head[vex]->flag = 0;
    return head[vex];
}

void insert(int weight, int vex, int data)
{
    node *new, *p;

    new = CreateNode(data,weight);

    if(!head[vex]->nxt) head[vex]->nxt = new;

    else if(!head[vex]->nxt->nxt)
    {
        if(weight < head[vex]->nxt->weight) 
        {
            new->nxt = head[vex]->nxt;
            head[vex]->nxt = new;
        }
        else head[vex]->nxt->nxt = new;
    }

    else
    {
        for(p = head[vex]->nxt; p->nxt; p = p->nxt)
        {
            if(weight < p->nxt->weight)
                break;
        }
        new->nxt = p->nxt;
        p->nxt = new;
    }
}

int top, end;
int a[N];
void DFS(int vex)
{
    int i;
    node *p;
    if(vex == end)
    {
        for(i = 0; i < top; i++) printf("%d ", a[i]); 
        puts("");
        return;
    }

    for(p = head[vex]->nxt; p; p = p->nxt)
    {
        if(!p->head->flag)
        {
            p->head->flag = 1;
            a[top++] = p->weight;
            DFS(p->head->data);
            p->head->flag = 0;
            top--;
        }
    }
}

int main()
{
    int n, m, v, w, num;
    int i;
    node *p;

    scanf("%d%d", &n, &m); end = n - 1;
    for(i = 0; i < n; i++) head[i] = CreateHead(i);
    for(i = 0; i < m; i++)
    {
        scanf("%d%d%d", &num, &v, &w);
        insert(num,v,w);
        insert(num,w,v);
    }

    head[0]->flag = 1;
    DFS(0); puts("");

    return 0;
}
