#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define N 53327
#define M 100000
#define CNT 10000
#define BUCKET_SIZE 10000
#define LEN 50
#define ALPHABET_SIZE 26
#define min(x,y) ((x)<(y))?(x):(y)
#define max(x,y) ((x)>(y))?(x):(y)

typedef struct Node
{
    int cnt, flag;
    char s[LEN];
    struct Node *nxt;
}node;

node *Article1[ALPHABET_SIZE][N], *Article2[ALPHABET_SIZE][N];
node *Bucket1[CNT][BUCKET_SIZE], *Bucket2[CNT][BUCKET_SIZE];
node Array1[M], Array2[M];
int MAX1, MAX2, top1[M], top2[M], MAX, ttop1, ttop2;
int freq1, ffreq1, freq2, ffreq2;
double pro1, pro2, sim;

unsigned int hash(char *s);
void article1();
void article2();
void Stop();
void Insert_Bucket();
void printBucket(node *Bucket[][BUCKET_SIZE], node Array[], int *ttop, int top[], int max);
void Count();
void Print();

int main()
{
    clock_t start, end;
    double total;
    scanf("%d", &MAX);

    start = clock();
    article1();
    article2();
    Stop();
    Insert_Bucket();
    printBucket(Bucket1,Array1,&ttop1,top1,MAX1);
    printBucket(Bucket2,Array2,&ttop2,top2,MAX2);
    Count();
    Print();
    end = clock();
    total = (double)(end - start)/CLOCKS_PER_SEC;
    printf("time:%lf\n", total);

    return 0;
}
unsigned int hash(char *s)
{
    register unsigned int seed = 131, val = 0, i = 0;
    while (*s && i < LEN) val = val * seed + (*s++), i++;
    return val % N;
}

node* CreateNode(char *s)
{
    register node *new;
    new = (node*)malloc(sizeof(node));
    strcpy(new->s,s);
    new->cnt = 1; new->flag = 0;
    new->nxt = NULL;

    return new;
}

void Article_Insert(node *head[][N], char *s)
{
    register unsigned int n, a;
    register node *p, *q;

    n = hash(s);
    a = *s - 'a';

    q = p = head[a][n];
    if(p)
    {
        while(p)
        {
            if(strcmp(s,p->s) == 0) 
            {
                p->cnt++;
                return;
            }
            q = p;
            p = p->nxt;
        }
        q->nxt = CreateNode(s);
    }
    else head[a][n] = CreateNode(s);
}

char s[M];
void article1()
{
    FILE *in;
    in = fopen("article1.txt","r");

    register int i, len = 0;
    char t[LEN] = {0};

    while(~fscanf(in,"%s",s))
    {
        for(i = 0, len = 0; s[i]; i++)
        {
            if(isalpha(s[i])) t[len++] = tolower(s[i]);
            if(!isalpha(s[i + 1]) && len > 0)
            {
                t[len] = '\0';
                Article_Insert(Article1,t);
                len = 0;
            }
        }
    }

    fclose(in);
}

void article2()
{
    FILE *in;
    in = fopen("article2.txt","r");

    register int i, len = 0;
    char t[LEN] = {0};

    while(~fscanf(in,"%s",s))
    {
        for(i = 0, len = 0; s[i]; i++)
        {
            if(isalpha(s[i])) t[len++] = tolower(s[i]);
            if(!isalpha(s[i + 1]) && len > 0)
            {
                t[len] = '\0';
                Article_Insert(Article2,t);
                len = 0;
            }
        }
    }

    fclose(in);
}

void Stop()
{
    FILE *in;
    in = fopen("stopwords.txt","r");

    register int n, a;
    char t[LEN];
    register node *p, *q;

    while(~fscanf(in,"%s",t))
    {
        a = *t - 'a';
        n = hash(t);

        p = Article1[a][n];
        while(p)
        {
            if(strcmp(t,p->s) == 0)
            {
                p->cnt = 0;
                break;
            }
            p = p->nxt;
        }

        q = Article2[a][n];
        while(q)
        {
            if(strcmp(t,q->s) == 0)
            {
                q->cnt = 0;
                break;
            }
            q = q->nxt;
        }
    }

    fclose(in);
}

void Insert_Bucket()
{
    FILE *in;
    in = fopen("dictionary.txt","r");

    register int n, a;
    char t[LEN];
    register node *p, *q;

    while(~fscanf(in,"%s",t))
    {
        a = *t - 'a';
        n = hash(t);

        p = Article1[a][n];
        q = Article2[a][n];
        while(p)
        {
            if(p->cnt && strcmp(t,p->s) == 0)
            {
                if(MAX1 < p->cnt) MAX1 = p->cnt;
                Bucket1[p->cnt][top1[p->cnt]++] = p;
                break;
            }
            p = p->nxt;
        }
        while(q)
        {
            if(q->cnt && strcmp(t,q->s) == 0)
            {
                if(MAX2 < q->cnt) MAX2 = q->cnt;
                Bucket2[q->cnt][top2[q->cnt]++] = q;
            }
            q = q->nxt;
        }
    }

    fclose(in);
}

void printBucket(node *Bucket[][BUCKET_SIZE], node Array[], int *ttop, int top[], int max)
{
    register int i, j, cnt;
    for(i = max, cnt = 0; i > 0 && cnt < MAX; i--)
        for(j = 0; j < top[i] && cnt < MAX; j++)
            if(Bucket[i][j])
            {
                Bucket[i][j]->flag = 1;
                Array[(*ttop)++] = *Bucket[i][j];
                cnt++;
            }
}

void Count()
{
    register int n, a, i = 0, j = 0;
    node *p;

    while(i < ttop1 || j < ttop2)
    {
        if(i < ttop1)
        {
            n = hash(Array1[i].s);
            a = Array1[i].s[0] - 'a';

            p = Article2[a][n];
            while(p)
            {
                if(strcmp(p->s,Array1[i].s) == 0) 
                    if(p->flag)
                    {
                        freq1 += Array1[i].cnt;
                        break;
                    }
                p = p->nxt;
            }
            ffreq1 += Array1[i].cnt;
        }

        if(j < ttop2)
        {
            n = hash(Array2[j].s);
            a = Array2[j].s[0] - 'a';

            p = Article1[a][n];
            while(p)
            {
                if(strcmp(p->s,Array2[j].s) == 0)
                    if(p->flag)
                    {
                        freq2 += Array2[j].cnt;
                        break;
                    }
                p = p->nxt;
            }
            ffreq2 += Array2[j].cnt;
        }

        i++; j++;
    }
    pro1 = (double)freq1/ffreq1;
    pro2 = (double)freq2/ffreq2;

    sim = ((min(pro1,pro2))/(max(pro1,pro2)));
    printf("%.5lf\n", sim);
}

void Print()
{
    FILE *out;
    out = fopen("results.txt","w");

    fprintf(out,"%.5lf\n\n", sim);
    for(register int i = 0; i < ttop1; i++) fprintf(out, "%s %d\n", Array1[i].s, Array1[i].cnt); fprintf(out,"\n");
    for(register int i = 0; i < ttop2; i++) fprintf(out, "%s %d\n", Array2[i].s, Array2[i].cnt);

    fclose(out);
}