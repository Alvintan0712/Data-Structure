#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 53327
#define M 100000
#define CNT 10000
#define BUCKET_SIZE 12000
#define LEN 50
#define ALPHABET_SIZE 26

typedef struct Node
{
    int cnt1, cnt2, flag;
    char s[LEN];
    struct Node *nxt;
}node;

node Space[N*26];
node *Article[ALPHABET_SIZE][N], *Array1[M], *Array2[M];
node *Bucket1[CNT][BUCKET_SIZE], *Bucket2[CNT][BUCKET_SIZE];
int top1[M], top2[M], MAX, num, n1, n2;
int visit1[CNT], heap1[CNT], visit2[CNT], heap2[CNT];

void article();
void Stop();
void Dictionary();
void Solve();

int main()
{
    scanf("%d", &MAX);
    article();
    Stop();
    Dictionary();
    Solve();
 
    return 0;
}

unsigned int hash(char *s)
{
    register unsigned int seed = 131, val = 0, i = 0;
    register char *t = s;

    while (*t) val = (val << 7) + (val << 1) + val + *t++;
    return val % N;
}

node* CreateNode(char *s, int flag)
{
    register node *new;

    new = &Space[num++];
    strcpy(new->s,s);
    new->cnt1 = new-> cnt2 = new->flag = 0;
    new->nxt = NULL;

    if(flag == 1) new->cnt1++;
    else new->cnt2++;

    return new;
}

void Article_Insert(char *s, int flag)
{
    register unsigned int n, a;
    register node *p, *q;

    n = hash(s);
    a = *s - 'a';

    q = p = Article[a][n];
    if(p)
    {
        while(p)
        {
            if(strcmp(s,p->s) == 0)
            {
                if(flag == 1) p->cnt1++;
                else p->cnt2++;
                return;
            }
            q = p;
            p = p->nxt;
        }
        q->nxt = CreateNode(s,flag);
    }
    else Article[a][n] = CreateNode(s,flag);
}

void article()
{
    FILE *in;
    in = fopen("article1.txt","rb");

    char t[LEN] = {0};
    register int i, len = 0;
    register long int length;
    register char *s, *tt = t;

    fseek(in,0L,SEEK_END);
    length = ftell(in);
    fseek(in,0L,SEEK_SET);
    s = (char*)malloc(sizeof(char)*length + 1);
    fread(s,1,length,in);

    for(i = 0, len = 0; i < length; ++i)
    {
        if(isalpha(s[i])) tt[len++] = tolower(s[i]);
        if(!isalpha(s[i + 1]) && len > 0)
        {
            tt[len] = '\0';
            Article_Insert(t,1);
            len = 0;
            ++i;
        }
    }

    fclose(in);

    in = fopen("article2.txt","rb");

    fseek(in,0L,SEEK_END);
    length = ftell(in);
    fseek(in,0L,SEEK_SET);
    s = (char*)realloc(s,sizeof(char)*length + 1);
    fread(s,1,length,in);

    for(i = 0, len = 0; i < length; ++i)
    {
        if(isalpha(s[i])) tt[len++] = tolower(s[i]);
        if(!isalpha(s[i + 1]) && len > 0)
        {
            tt[len] = '\0';
            Article_Insert(t,2);
            len = 0;
            ++i;
        }
    }

    free(s);
    fclose(in);
}

void mark(char *t)
{
    register int n, a;
    register node *p;

    a = *t - 'a';
    n = hash(t);
    
    p = Article[a][n];
    while(p)
    {
        if(strcmp(t,p->s) == 0)
        {
            p->cnt1 = p->cnt2 = 0;
            break;
        }
        p = p->nxt;
    }    
}

void Stop()
{
    FILE *in;
    in = fopen("stopwords.txt","rb");

    char t[LEN];
    register char *s, *tt = t;
    register long int length;
    register int i, len;

    fseek(in,0L,SEEK_END);
    length = ftell(in);
    fseek(in,0L,SEEK_SET);

    s = (char*)malloc(sizeof(char)*length + 1);
    fread(s,1,length,in);

    for(i = 0, len = 0; i < length; ++i)
    {
        if(isalpha(s[i])) tt[len++] = s[i];
        if(!isalpha(s[i + 1]) && len > 0)
        {
            tt[len] = '\0';
            mark(t);
            len = 0;
            ++i;
        }
    }

    free(s);
    fclose(in);
}

void swap(int *a, int *b)
{
    *a = *a^*b;
    *b = *a^*b;
    *a = *a^*b;
}
void heapify()
{
    register int i, j, p, *t = &n1, *tt = heap1;

    p = (*t - 1) >> 1;
    do
    {
        i = (p << 1) + 1;
        j = p;

        while(tt[j] < tt[i] || ((i < *t - 1) && tt[j] < tt[i + 1]))
        {
            if(i < *t - 1 && tt[i] < tt[i + 1]) i++;
            swap(&tt[i],&tt[j]);
            j = i;

            if((j << 1) + 1 < *t - 1) i = (j << 1) + 1;
            else break;
        }
    }while(p--);

    t = &n2; tt = heap2;
    p = (*t - 1) >> 1;
    do
    {
        i = (p << 1) + 1;
        j = p;

        while(tt[j] < tt[i] || ((i < *t - 1) && tt[j] < tt[i + 1]))
        {
            if(i < *t - 1 && tt[i] < tt[i + 1]) i++;
            swap(&tt[i],&tt[j]);
            j = i;

            if((j << 1) + 1 < *t - 1) i = (j << 1) + 1;
            else break;
        }
    }while(p--);
}

int deleteheap(int heap[], int *n)
{
    register int i = 0, j, *t = n, *tt = heap;
    register int cur, last;

    cur = tt[0]; last = tt[--(*t)];
    while((i << 1) + 1 < *t)
    {
        j = (i << 1) + 1;
        if(j != *t - 1 && tt[j] < tt[j + 1]) j++;
        if(last < tt[j]) tt[i] = tt[j];
        else break;
        i = j;
    }
    tt[i] = last;

    return cur;
}

void Insert_Bucket(char *t)
{
    register node *p;
    register int a, n;
    register int *p1 = visit1, *p2 = visit2, *p3 = heap1, *p4 = heap2, *p5 = &n1, *p6 = &n2;

    a = *t - 'a';
    n = hash(t);

    p = Article[a][n];
    while(p)
    {
        if((p->cnt1 || p->cnt2) && strcmp(t,p->s) == 0)
        {
            if(!p1[p->cnt1]) p1[p->cnt1] = 1, p3[(*p5)++] = p->cnt1;
            if(!p2[p->cnt2]) p2[p->cnt2] = 1, p4[(*p6)++] = p->cnt2;

            Bucket1[p->cnt1][top1[p->cnt1]++] = p;
            Bucket2[p->cnt2][top2[p->cnt2]++] = p;

            break;
        }
        p = p->nxt;
    }
}

void Dictionary()
{
    FILE *in;
    in = fopen("dictionary.txt","rb");

    char t[LEN];
    register char *s, *tt = t;
    register long int length;
    register int i, len;

    fseek(in,0L,SEEK_END);
    length = ftell(in);
    fseek(in,0L,SEEK_SET);
    s = (char*)malloc(sizeof(char)*length + 1);
    fread(s,1,length,in);

    for(i = 0, len = 0; i < length; ++i)
    {
        if(isalpha(s[i])) tt[len++] = s[i];
        if(!isalpha(s[i + 1]) && len > 0)
        {
            tt[len] = '\0';
            Insert_Bucket(t);
            len = 0;
            ++i;
        }
    }
    heapify();

    free(s);
    fclose(in);
}

char s[100*M], buff[M];
void Solve()
{
    FILE *fp;
    fp = fopen("results.txt","wb");

    register int i, j, cnt, max = MAX;
    register int freq1 = 0, ffreq1 = 0, freq2 = 0, ffreq2 = 0;
    register int ttop1 = 0, ttop2 = 0;
    register double pro1, pro2, sim;

    cnt = 0;
    do
    {
        i = deleteheap(heap1,&n1);
        for(j = 0; j < top1[i] && cnt < max; ++j)
        {
            Bucket1[i][j]->flag++;
            cnt++;

            ffreq1 += Bucket1[i][j]->cnt1;
            Array1[ttop1++] = Bucket1[i][j];
        }
    }while(cnt < max && n1);

    cnt = 0;
    do
    {
        i = deleteheap(heap2,&n2);
        for(j = 0; j < top2[i] && cnt < max; ++j)
        {
            Bucket2[i][j]->flag++;
            cnt++;

            if(Bucket2[i][j]->flag == 2)
            {
                freq1 += Bucket2[i][j]->cnt1;
                freq2 += Bucket2[i][j]->cnt2;
            }

            ffreq2 += Bucket2[i][j]->cnt2;
            Array2[ttop2++] = Bucket2[i][j];
        }
    }while(cnt < max && n2);

    pro1 = (double)freq1/ffreq1;
    pro2 = (double)freq2/ffreq2;

    if(pro1 < pro2) sim = pro1 / pro2;
    else sim = pro2 / pro1;

    printf("%.5lf\n", sim);

    sprintf(s,"%.5lf\n\n", sim);
    for(i = 0; i < ttop1; i++) 
    {
        sprintf(buff, "%s %d\n", Array1[i]->s, Array1[i]->cnt1);
        strcat(s,buff);
    }
    strcat(s,"\n");
    for(i = 0; i < ttop2; i++) 
    {
        sprintf(buff, "%s %d\n", Array2[i]->s, Array2[i]->cnt2);
        strcat(s,buff);
    }
    fwrite(s,strlen(s),1,fp);
}
