#include <stdio.h>
#include <string.h>

struct book
{
    char name[100], num[100];
}ppl[100], t;

void sswap(char **a, char **b)
{
    char *t = *a;
    *a = *b;
    *b = t;
}

int main()
{
    int n, i, j, k, v[100] = {0};
    scanf("%d", &n);
    for(i = 0; i < n; i++) scanf("%s%s", ppl[i].name, ppl[i].num);

    for(i = 0; i < n; i++)
        for(j = i + 1; j < n; j++)
            if(strcmp(ppl[i].num,ppl[j].num) == 0) v[j] = 1;

    for(i = 0, j = 0; i < n; i++)
        if(!v[i]) ppl[j++] = ppl[i];
    n = j;

    for(i = 0; i < n - 1; i++)
        for(j = 0; j < n - i - 1; j++)
            if(strcmp(ppl[j].name,ppl[j + 1].name) > 0)
                t = ppl[j],
                ppl[j] = ppl[j + 1],
                ppl[j + 1] = t;

    for(i = 0, j = 0, k = 0; i < n; i++)
    {
        if(strcmp(ppl[i].name,ppl[i + 1].name) == 0)
        {
            if(j) printf("%s_%d %s\n", ppl[i].name, j++, ppl[i].num);
            else printf("%s %s\n", ppl[i].name, ppl[i].num), j++, k = 1;
        }
        else 
        {
            if(k) printf("%s_%d %s\n", ppl[i].name, j++, ppl[i].num), k = 0, j = 0;
            else printf("%s %s\n", ppl[i].name, ppl[i].num);
        }
    }    

    return 0;
}