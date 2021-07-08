#include <stdio.h>
#define N 1000

typedef struct Line
{
	int v1, v2, id, w;
}line;

void swap(line *a, line *b)
{
	line t = *a;
	*a = *b;
	*b = t;
}
void sort(line a[], int n, int flag)
{
	int i, j;
	for(i = 0; i < n - 1; i++)
		for(j = 0; j < n - i - 1; j++)
		{
			if(flag && a[j].w > a[j + 1].w) swap(&a[j],&a[j + 1]);
			else if(!flag && a[j].id > a[j + 1].id) swap(&a[j],&a[j + 1]);			
		}
}
int parent[N], top;
line b[N];
int find(int x)
{
	while(parent[x] != -1) x = parent[x];
	return x;
}
void attach(line data)
{
	int x, y;
	x = find(data.v1);
	y = find(data.v2);
	if(x != y) parent[x] = y, b[top++] = data;
}

line a[N];
int main()
{
	int n, m, i, sum = 0;
	scanf("%d%d", &n, &m);
	for(i = 0; i < n; i++) parent[i] = -1;
	for(i = 0; i < m; i++) scanf("%d%d%d%d", &a[i].id, &a[i].v1, &a[i].v2, &a[i].w);
	sort(a,m,1);
	for(i = 0; i < m && top < n - 1; i++) attach(a[i]);
	sort(b,top,0);
	for(i = 0; i < top; i++) sum += b[i].w;
	printf("%d\n", sum);
	for(i = 0; i < top; i++) printf("%d ", b[i].id);

	return 0;
}