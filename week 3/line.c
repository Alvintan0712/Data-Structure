#include <stdio.h>
#include <stdlib.h>

typedef struct Line
{
    int x1, y1, x2, y2;
}line;
typedef struct List
{
    line l;
    struct List *nxt;
}list;

int main()
{
    int n, i, j, k, max = 0;
    line ll;
    list *head[100] = {NULL}, *p, *q, *new;
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        scanf("%d%d%d%d", &ll.x1, &ll.y1, &ll.x2, &ll.y2);

        new = (list*)malloc(sizeof(list));
        new->l = ll; new->nxt = NULL;

        //let all the line put in the different List first
        head[i] = (list*)malloc(sizeof(list)); 
        head[i]->nxt = new;
    }

    //combine the list
    for(i = 0; head[i]; i++)
        for(j = 0; head[j]; j++)
        {
            if(i == j) continue;

            //run to last
            for(p = head[i]->nxt; p->nxt; p = p->nxt);
            for(q = head[j]->nxt; q->nxt; q = q->nxt);

            //if last can link, link it
            if(p->l.x2 == head[j]->nxt->l.x1 && p->l.y2 == head[j]->nxt->l.y1)
            {
                p->nxt = head[j]->nxt;
                free(head[j]);
                for(k = j; k < n - 1; k++) head[k] = head[k + 1];
                n--; j--;
                continue;
            }

            //if last can link, link it
            if(q->l.x2 == head[i]->nxt->l.x1 && q->l.y2 == head[i]->nxt->l.y1)
            {
                q->nxt = head[i]->nxt;
                free(head[i]);
                for(k = i; k < n - 1; k++) head[k] = head[k + 1];
                n--;
                continue;
            }
        }

    for(i = 0, max = 0; i < n; i++)
    {
        for(j = 0, p = head[i]->nxt; p; p = p->nxt, j++);
        if(max < j) max = j, q = head[i]->nxt;
    }

    printf("%d %d %d\n", max, q->l.x1, q->l.y1);

    return 0;
}