#include <stdio.h>
#define N 100

typedef struct Stu
{
    int id, n;
    char name[N];
}stu;

int main()
{
    FILE *in, *out;
    in = fopen("in.txt","r");
    out = fopen("out.txt","w");

    int n, m = 0, q, nn;
    int i, j, top = 0;
    int v[N + 1] = {0};
    stu t1[N + 1], *t2[N + 1], *rpt[N + 1];
    scanf("%d", &n);

    for(i = 1; i <= n; i++) 
    {
        fscanf(in,"%d%s%d", &t1[i].id, t1[i].name, &t1[i].n);
        if(m < t1[i].n) m = t1[i].n;
    }

    for(i = 1; i <= n; i++) t2[i] = &t1[i];

    for(i = 1; i <= n - 1; i++)
        for(j = 1; j <= n - i; j++)
            if(t2[j]->n > t2[j + 1]->n)
            {
                stu *t = t2[j];
                t2[j] = t2[j + 1];
                t2[j + 1] = t;
            }

    for(i = 1; i <= n; i++) v[t2[i]->n]++;

    q = n < m? n : m;
    nn = n;
    for(i = 1; i <= nn; i++)
    {
        if(i > 1 && t2[i]->n == t2[i - 1]->n)
        {
            rpt[top++] = t2[i];
            v[t2[i]->n]--;
            for(j = i, nn--; j <= nn; j++) t2[j] = t2[j + 1];
        }
        if(v[i] == 0 && i <= q)
        {
            stu *t = t2[nn];

            for(j = nn; j > i; j--) t2[j] = t2[j - 1];

            v[t->n]--;
            t->n = i;
            v[t->n]++;

            t2[i] = t;
        }
    }
    for(i = 0; i < top; i++)
    {
        rpt[i]->n = ++nn;
        t2[nn] = rpt[top];
    }
    for(i = 1; i <= n; i++) fprintf(out,"%d %s %d\n", t1[i].id, t1[i].name, t1[i].n);
    fclose(in); fclose(out);

    return 0;
}