#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int num;
    struct Node *nxt;
}node;

void create(node *head, int n)
{
    int i;
    node *new, *p = head;
    for(i = 1; i <= n; i++) 
    {
        new = (node*)malloc(sizeof(node));
        new->num = i; new->nxt = head; 
        p->nxt = new; p = new;
    }
}
void del(node *head, int n, int m, int q)
{
    int i;
    node *p, *r;
    for(p = head->nxt, r = head; --q; p = p->nxt);
    while(n > 1)
    {
        for(i = 1; i < m; i++) 
        {
            if(p->nxt == head) r = p, p = p->nxt;
            r = p, p = p->nxt;
        }
        r->nxt = p->nxt; free(p); p = r->nxt;
        if(p == head) p = p->nxt;
        n--;
    }
}

int main()
{
    int n, m, q;
    node *head;
    head = (node*)malloc(sizeof(node)); head->nxt = head;

    scanf("%d%d%d", &n, &m, &q);
    create(head,n);
    del(head,n,m,q);

    printf("%d\n", head->nxt->num);

    return 0;
}