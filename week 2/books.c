#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct book
{
    char book[55], au[25], shd[35], date[15];
}lib;
typedef struct Node
{
    lib a;
    struct Node *nxt;
}node;

void swap(node *p, node *q)
{
    lib t = q->a;
    q->a = p->a;
    p->a = t;
}
int insert(node *head)
{
    lib t;
    node *p, *q, *new;
    scanf("%s%s%s%s", t.book, t.au, t.shd, t.date);
    for(p = head->nxt, q = head; p; q = p, p = p->nxt)
        if(strcmp(t.book,p->a.book) <= 0)
        {
            if(strcmp(t.book,p->a.book) == 0) return 0;
            else
            {
                new = (node*)malloc(sizeof(node));
                new->a = t; new->nxt = q->nxt; q->nxt = new;
                return 1;
            }
        }
    new = (node*)malloc(sizeof(node));
    new->a = t; new->nxt = q->nxt; q->nxt = new;
    return 1;
}
void check(char *s, node *head)
{
    node *p;
    for(p = head->nxt; p; p = p->nxt)
        if(strstr(p->a.book,s)) printf("%-50s%-20s%-30s%-10s\n", p->a.book, p->a.au, p->a.shd, p->a.date);
}
int delete(char *s, node *head)
{
    int n = 0;
    node *p = head->nxt, *q;
    if(p->nxt)
    {
        for(q = head, p = q->nxt; p;)
            if(strstr(p->a.book,s))
            {
                q->nxt = p->nxt;
                free(p);
                n++; p = p->nxt;
            }
            else q = p, p = p->nxt;
    }
    else if(p)
    {
        if(strstr(p->a.book,s)) 
        {
            free(p);
            head->nxt == NULL;
            n = 1;
        }
    }
    return n;
}

int main()
{
    FILE *in, *out;
    int i, j, n, x, k;
    char s[55];
    node *head = (node*)malloc(sizeof(node)); head->nxt = NULL;
    node *p = head, *q;

    in = fopen("books.txt","r"); out = fopen("ordered.txt","w");
    for(n = 0;; n++)
    {
        node *new = (node*)malloc(sizeof(node));
        k = fscanf(in,"%s%s%s%s", new->a.book, new->a.au, new->a.shd, new->a.date);
        if(k == EOF) break;
        p->nxt = new; new->nxt = NULL; p = new;
    }
    for(i = 0; i < n - 1; i++)
        for(j = 0, q = head->nxt, p = q->nxt; j < n - i - 1; j++, q = p, p = p->nxt)
            if(strcmp(q->a.book,p->a.book) > 0) swap(p,q);
    do
    {
        scanf("%d", &x);
        switch(x)
        {
            case 1:
            n += insert(head);
            break;
            case 2:
            scanf("%s", s);
            check(s,head);
            break;
            case 3:
            scanf("%s", s);
            n -= delete(s,head);
            break;
            default: break;
        }
    }while(x);
    for(p = head->nxt; p; p = p->nxt) fprintf(out,"%-50s%-20s%-30s%-10s\n", p->a.book, p->a.au, p->a.shd, p->a.date);
    fclose(in), fclose(out);

    return 0;
}