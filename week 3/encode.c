#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char a;
    struct Node *nxt;
}node;

int purge(char *s)
{
    int i, j, v[130] = {0};
    for(i = 0; s[i]; i++)
        for(j = i + 1; s[j]; j++)
        {
            if(v[j]) continue;
            if(s[i] == s[j]) v[j] = 1;
        }
    for(i = 0, j = 0; s[i]; i++)
        if(!v[i]) s[j++] = s[i];
    s[j] = '\0';

    return j;
}

int main()
{
    int v[130] = {0};
    int i, j, n, len = 0, cnt;
    char s[10000], hr[10000] = {0}, c;
    node *p, *q, *new, *hp, *hpp;
    FILE *in, *out;
    in = fopen("in.txt","r");
    out = fopen("in_crpyt.txt","w");

    gets(s);
    n = purge(s);

    hp = (node*)malloc(sizeof(node));
    hp->nxt = hp; p = hp;
    for(i = 0; i < n; i++)
    {
        v[s[i]] = 1;
        new = (node*)malloc(sizeof(node));
        new->a = s[i]; new->nxt = hp;
        p->nxt = new; p = new;
    }

    for(i = 32; i <= 126; i++)//32 is space, 126 is ~
    {
        if(!v[i])
        {
            new = (node*)malloc(sizeof(node));
            new->a = i; new->nxt = hp;
            p->nxt = new; p = new;
        }
    }

    for(p = hp->nxt, i = 0; p != hp; p = p->nxt, i++);
    len = i;

    //copy hp LinkList
    hpp = (node*)malloc(sizeof(node));
    hpp->nxt = hpp; q = hpp;
    for(p = hp->nxt; p != hp; p = p->nxt)
    {
        new = (node*)malloc(sizeof(node));
        new->nxt = hpp; new->a = p->a;
        q->nxt = new; q = new;
    }

    n = 0; p = hpp->nxt, q = hpp;
    while(n < len - 1)
    {
        c = p->a;
        
        q->nxt = p->nxt; free(p);
        p = q->nxt;

        for(cnt = c; --cnt; q = p, p = p->nxt)
            if(p == hpp) q = p, p = p->nxt;

        if(p == hpp) q = p, p = p->nxt;
        hr[c] = p->a; n++;
    }
    hr[hpp->nxt->a] = s[0];

    while(c = fgetc(in), c != EOF) 
    {
        if(hr[c]) putc(hr[c],out);
        else putc(c,out);
    }

    return 0;
}