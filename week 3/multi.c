#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int a, n;
    struct Node *nxt;
}node;

int main()
{
    node *ha, *hb, *ans, *p, *q, *r, *s, *new;
    int co, pow;
    char c;

    ha = (node*)malloc(sizeof(node));
    ha->nxt = NULL; p = ha;
    do
    {
        scanf("%d%d", &co, &pow); c = getchar();
        new = (node*)malloc(sizeof(node));
        new->a = co; new->n = pow;
        p->nxt = new; new->nxt = NULL;
        p = new;
    }while(c != '\n');

    hb = (node*)malloc(sizeof(node));
    hb->nxt = NULL; p = hb;
    do
    {
        scanf("%d%d", &co, &pow); c = getchar();
        new = (node*)malloc(sizeof(node));
        new->a = co; new->n = pow;
        p->nxt = new; new->nxt = NULL;
        p = new;
    }while(c != '\n');

    ans = (node*)malloc(sizeof(node)); ans->nxt = NULL;
    r = ans;
    for(p = ha->nxt; p; p = p->nxt)
    {
        for(q = hb->nxt; q; q = q->nxt)
        {
            new = (node*)malloc(sizeof(node));
            new->a = (p->a)*(q->a); new->n = p->n + q->n;

            if(ans->nxt == NULL)
            {
                new->nxt = NULL;
                ans->nxt = new;
            }

            else
            {
                for(r = ans->nxt, s = ans; r; s = r, r = r->nxt)
                {
                    if(new->n < r->n) continue;

                    else if(r->n == new->n)
                    {
                        r->a += new->a;
                        free(new);
                        break;
                    }

                    else if(new->n > r->n)
                    {
                        new->nxt = s->nxt;
                        s->nxt = new;
                        break;
                    }
                }
                if(r == NULL)
                {
                    s->nxt = new;
                    new->nxt = NULL;
                }
            }
        }
    }

    for(p = ans->nxt; p; p = p->nxt) printf("%d %d ", p->a, p->n);

    return 0;
}