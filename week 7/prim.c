#include <stdio.h>
#define N 100
#define INF -((1 << 31) + 1)

typedef struct Edge
{
    int id, w;
}edge;

void prim(edge a[][N], edge line[], int n)
{
    int top = 0, ttop = 0, min = INF, min_i, min_j;
    int visit[n], v[n];
    int i, j;

    for(i = 0; i < n; i++) visit[i] = -1, v[i] = 0;

    visit[0] = 0; v[0] = 1, top++;

    while(1)
    {
        min = INF;
        for(i = 0; i < top; i++)
        {
            for(j = 0; j < n; j++)
                if(!v[j] && min > a[visit[i]][j].w)
                {
                    min = a[visit[i]][j].w;
                    min_i = visit[i];
                    min_j = j;
                }
        }

        if(min < INF)
        {
            visit[top++] = min_j; v[min_j] = 1;
            line[ttop++] = a[min_i][min_j];
        }
        else break;

        if(ttop == n - 1) break;
    }

}

edge a[N][N], line[N], tmp;
int main()
{
    int n, m, id, v1, v2, w;
    int i, j, sum = 0;
    scanf("%d%d", &n, &m);

    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            a[i][j].id = -1, a[i][j].w = INF;

    for(i = 0; i < m; i++) 
    {
        scanf("%d%d%d%d", &id, &v1, &v2, &w);
        tmp.id = id; tmp.w = w;
        a[v1][v2] = a[v2][v1] = tmp;
    }

    prim(a,line,n);
    for(i = 0; i < n - 1; i++) sum += line[i].w;
    for(i = 0; i < n - 2; i++)
        for(j = 0; j < n - i - 2; j++)
            if(line[j].id > line[j + 1].id)
            {
                tmp = line[j];
                line[j] = line[j + 1];
                line[j + 1] = tmp;
            }
    printf("%d\n", sum);
    for(i = 0; i < n - 1; i++) printf("%d ", line[i].id);

    return 0;
}