#include <stdio.h>
#include <stdlib.h>
#define N 1000

typedef struct Node
{
    int data, flag;
    struct Node *head, *nxt;
}node;

node* CreateNode(node *head, int data)
{
    node *new;
    new = (node*)malloc(sizeof(node));
    new->nxt = NULL; new->head = head; new->data = data; new->flag = 0;

    return new;
}

void insert(node *H[], int vex, int data)
{
    node *new, *p;
    new = CreateNode(H[data],data);

    for(p = H[vex]; p->nxt; p = p->nxt)
        if(data < p->nxt->data)
            break;

     new->nxt = p->nxt;
     p->nxt = new;
}

void DFS(node *head)
{
    node *p;
    if(!head->flag) printf("%d ", head->data), head->flag = 1;

    for(p = head->nxt; p; p = p->nxt)
        if(!p->head->flag)
            DFS(p->head);
}

node *queue[N];
int front, rear;
void BFS(node *head)
{
    node *p;
    if(head->flag) printf("%d ", head->data); head->flag = 0;

    for(p = head->nxt; p; p = p->nxt)
        if(p->head->flag)
            queue[rear++] = p->head;

    while(front < rear) BFS(queue[front++]);
}

int main()
{
    node *H[N] = {NULL}, *p;
    int n, m, i, v, w;
    scanf("%d%d", &n, &m);
    for(i = 0; i < n; i++) H[i] = CreateNode(NULL,i);

    while(m--) scanf("%d%d", &v, &w), insert(H,v,w), insert(H,w,v);

    DFS(H[0]); puts("");
    BFS(H[0]); puts("");

    scanf("%d", &m);
    H[m]->flag = !H[m]->flag;

    DFS(H[0]); puts("");
    H[m]->flag = !H[m]->flag;
    BFS(H[0]); puts("");    

    return 0;
}