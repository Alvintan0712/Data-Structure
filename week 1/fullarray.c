#include <stdio.h>

int n;
int val[15], vis[15];

void Calc(int index)
{
	int i;
	if(index >= n)
	{
		for(i = 0; i < n; i++) printf("%d ", val[i]);
		puts("");
		return;
	}
	for(i = 0; i < n; i++)
	{
		if(!vis[i])
		{
			val[index] = i + 1;
			vis[i] = 1;
			Calc(index + 1);
			vis[i] = 0;
		}
	}
}

int main()
{
	scanf("%d", &n);
	Calc(0);

	return 0;
}