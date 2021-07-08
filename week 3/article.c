#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define N 10000

typedef struct Node
{
    int cnt;
    char str[N];
    struct Node *nxt;
}node;

int main()
{
    FILE *in;
    in = fopen("article.txt","r");

    char get[N], s[N];
    int n, len, i;
    node *v = (node*)malloc(sizeof(node)), *p, *q, *new;
    v->nxt = NULL;

    while(fgets(get,N,in) != NULL)
    {        
        //take off the others symbol
        for(i = 0, len = 0; get[i]; i++)
        {
            if(isalpha(get[i])) get[len++] = tolower(get[i]);
            else get[len++] = ' ';
        }
        get[len] = '\0';

        for(n = 0; get[n]; n++) 
        {
            memset(s,'\0',N);
            for(i = 0; isalpha(get[n]); n++) s[i++] = get[n];
            s[i] = '\0';
            if(s[0] == '\0') continue;
    
            //if List is empty
            if(v->nxt == NULL)
            {
                new = (node*)malloc(sizeof(node));
                strcpy(new->str,s); new->cnt = 1;
                new->nxt = NULL;
                v->nxt = new;
            }

            //if List not empty
            else
            {
                for(p = v->nxt, q = v; p; q = p, p = p->nxt)
                {
                    if(strcmp(s,p->str) > 0) continue;

                    else if(strcmp(s,p->str) == 0)
                    {
                        (p->cnt)++;
                        break;
                    }

                    else if(strcmp(s,p->str) < 0)
                    {
                        new = (node*)malloc(sizeof(node));
                        strcpy(new->str,s); new->cnt = 1;
                        new->nxt = q->nxt;
                        q->nxt = new;
                        break;
                    }
                }            
                if(p == NULL)
                {
                    new = (node*)malloc(sizeof(node));
                    strcpy(new->str,s); new->cnt = 1;
                    new->nxt = NULL;
                    q->nxt = new;
                }
            }
        }
    }
    for(p = v->nxt; p; p = p->nxt) printf("%s %d\n", p->str, p->cnt);
}