#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10000
#define INF (-((1 << 31) + 1))

typedef struct Edge edge;
typedef struct Ver ver;
struct Edge
{
    int index, line;
    edge *nxt;
};
struct Ver
{
    char name[100];
    int index, flag;
    edge *nxt;
};
int top, num;
int dist[N], path[N];
ver *v[N], *stk[N], *new;
edge *l[N];

void insert(ver *a, ver *b, int line)
{
    edge *p, *new;

    //create edge
    new = (edge*)malloc(sizeof(edge));
    new->index = b->index; new->nxt = NULL; new->line = line;

    //attach edge
    if(a->nxt == NULL) a->nxt = new;
    else
    {
        for(p = a->nxt; p->nxt; p = p->nxt);
        p->nxt = new;
    }
    
    //create edge
    new = (edge*)malloc(sizeof(edge));
    new->index = a->index; new->nxt = NULL; new->line = line;

    //attach edge
    if(b->nxt == NULL) b->nxt = new;
    else
    {
        for(p = b->nxt; p->nxt; p = p->nxt);
        p->nxt = new;
    }
}

void dijkstra(int start, int end)
{
    unsigned int front = 0, rear = 0, cnt = 0, parent;
    ver *queue[N];
    edge *p;

    queue[rear++ % N] = v[start]; cnt++;
    dist[start] = 0; path[start] = -1;

    while(cnt > 0)
    {
        //dequeue vertex
        parent = queue[front % N]->index;
        p = queue[front++ % N]->nxt; cnt--;

        while(p && parent != end)
        {
            //enqueue all the adjvex
            if(dist[p->index] == INF)
            {
                queue[rear++ % N] = v[p->index];
                cnt++;
            }

            //if have shorter distance just exchange it
            if(dist[p->index] > dist[parent] + 1) 
            {
                dist[p->index] = dist[parent] + 1;
                path[p->index] = parent;
                l[p->index] = p;
            }

            p = p->nxt;
        }
    }
}

int main()
{
    FILE *in;
    in = fopen("bgstations.txt","r");

    int n, m, line, flag;
    int i, j, k, index_start, index_end;
    char name[100], start[100], end[100];
    ver *t;

    fscanf(in,"%d", &n);
    for(i = 0; i < n; i++)
    {
        fscanf(in,"%d%d", &line, &m);
        for(j = 0; j < m; j++)
        {
            fscanf(in,"%s%d", name, &flag);
            if(flag)
            {
                for(k = 0; k < top; k++)
                    if(strcmp(name,stk[k]->name) == 0)
                    {
                        if(j) insert(stk[k],t,line);
                        t = stk[k];
                        flag = 0;
                        break;
                    }

                //create vertex
                if(flag)
                {
                    new = (ver*)malloc(sizeof(ver));
                    strcpy(new->name,name); new->index = num;
                    new->flag = flag; new->nxt = NULL;

                    v[num++] = new; stk[top++] = new;
                }
                else continue;
            }
            else
            {
                //create vertex
                new = (ver*)malloc(sizeof(ver));
                strcpy(new->name,name); new->index = num;
                new->flag = flag; new->nxt = NULL;

                v[num++] = new;
            }
            if(j) insert(v[num - 1],t,line);
            t = v[num - 1];
        }
    }

    scanf("%s%s", start, end);
    for(i = 0; i < num; i++)
    {
        if(strcmp(start,v[i]->name) == 0) index_start = i;
        if(strcmp(end,v[i]->name) == 0) index_end = i;
    }

    for(i = 0; i < num; i++) dist[i] = INF;
    dijkstra(index_start,index_end);

    int stack[N] = {0}, ttop = -1, cnt = 1;
    edge *stkk[N];
    while(path[index_end] != -1)
    {
        stack[++ttop] = index_end;
        stkk[ttop] = l[index_end];
        index_end = path[index_end];
    }

    printf("%s", v[index_start]->name);
    while(ttop)
    {
        if(stkk[ttop]->line == stkk[ttop - 1]->line) cnt++;
        else printf("-%d(%d)-%s", stkk[ttop]->line, cnt, v[stkk[ttop]->index]->name), cnt = 1;
        ttop--;
    }
    printf("-%d(%d)-%s", stkk[ttop]->line, cnt, v[stkk[ttop]->index]->name);

    fclose(in);

    return 0;
}