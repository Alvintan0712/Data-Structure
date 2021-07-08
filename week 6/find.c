#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10000
#define NHASH  3001
#define MULT  37

typedef struct Node
{
    char *s;
    struct Node *nxt;
}node;
int n, an, nn[26];
node *Htable[NHASH];

unsigned int hash(char *str)
{
    unsigned int h = 0;
    char *p;

    for(p = str; *p; p++) h = MULT*h + *p;

    return h % NHASH;
}
void Insert(char *str)
{
    unsigned int code;
    char *s;
    node *p, *new;

    s = (char*)malloc(sizeof(char)*strlen(str) + 1);
    strcpy(s,str);

    new = (node*)malloc(sizeof(node));
    new->nxt = NULL; new->s = s;

    code = hash(str);
    if(!Htable[code]) Htable[code] = new;
    else
    {
        for(p = Htable[code]; p->nxt; p = p->nxt);
        p->nxt = new;
    }
}
void Linear_Search(char *t, char *s[])
{
    int i;
    for(i = 0; i < n && strcmp(t,s[i]) >= 0; i++)
        if(strcmp(t,s[i]) == 0)
        {
            printf("1 %d\n", i + 1);
            return;
        }
    printf("0 %d\n", i + 1);
}
void Binary_Search(char *t, char *s[])
{
    int low = 0, high = n - 1, mid, cnt = 0;
    while(low <= high)
    {
        mid = (low + high) / 2; cnt++;
        if(strcmp(t,s[mid]) > 0) low = mid + 1;
        else if(strcmp(t,s[mid]) < 0) high = mid - 1;
        else
        {
            printf("1 %d\n", cnt);
            return;
        }
    }
    printf("0 %d\n", cnt);
}
void Index_Search(char *t, char *ss[][N])
{
    int low = 0, high, mid, cnt = 0;

    an = *t - 'a';
    high = nn[an] - 1;

    while(low <= high)
    {
        mid = (low + high) / 2; cnt++;
        if(strcmp(t,ss[an][mid]) > 0) low = mid + 1;
        else if(strcmp(t,ss[an][mid]) < 0) high = mid - 1;
        else
        {
            printf("1 %d\n", cnt);
            return;
        }
    }
    printf("0 %d\n", cnt);
}
void Hash_Search(char *t)
{
    unsigned int code, cnt = 0;
    node *p;

    code = hash(t);

    for(p = Htable[code]; p; p = p->nxt, cnt++)
        if(strcmp(t,p->s) == 0)
        {
            cnt++;
            printf("1 %d\n", cnt);
            return;
        }
    printf("0 %d\n", cnt);
}

int main()
{
    FILE *in;
    in = fopen("dictionary3000.txt","r");

    int k;
    char *s[N], *ss[26][N], t[1000];
    while(~fscanf(in,"%s", t))
    {
        //构造顺序表
        s[n] = (char*)malloc(sizeof(char)*strlen(t) + 1);
        strcpy(s[n++],t);

        //构造索引表
        an = t[0] - 'a';
        ss[an][nn[an]] = (char*)malloc(sizeof(char)*strlen(t) + 1);
        strcpy(ss[an][nn[an]++],t);

        //构造哈希表
        Insert(t);
    }
    scanf("%s%d", t, &k);
    switch(k)
    {
        case 1: Linear_Search(t,s); break;
        case 2: Binary_Search(t,s); break;
        case 3: Index_Search(t,ss); break;
        case 4: Hash_Search(t); break;
    }

    fclose(in);

    return 0;
}