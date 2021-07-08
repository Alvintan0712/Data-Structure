#include <stdio.h>
#define N 1000

int a[N][N], visit[N];
int n, m;
void DFS(int vex, int a[][N])
{
    int i;
    if(!visit[vex]) printf("%d ", vex), visit[vex] = 1;
    for(i = 0; i < n; i++)
        if(!visit[i] && a[vex][i])
            DFS(i,a);
}

int queue[N], front, rear;
void BFS(int vex, int a[][N])
{
    int i;
    if(visit[vex]) printf("%d ", vex), visit[vex] = 0;

    for(i = 0; i < n; i++)
        if(visit[i] && a[vex][i])
            queue[rear++] = i;

    while(front < rear) BFS(queue[front++],a);
}

int main()
{
    int i, j, v, w;
    scanf("%d%d", &n, &m);

    while(m--) 
    {
        scanf("%d%d", &v, &w);
        a[w][v] = a[v][w] = 1;
    }

    DFS(0,a); puts("");
    BFS(0,a); puts("");

    scanf("%d", &m);
    for(i = 0; i < n; i++) a[m][i] = a[i][m] = 0;

    DFS(0,a); puts("");
    BFS(0,a); puts("");

    return 0;
}