#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(char *a, char *b)
{
	if(strlen(a) > strlen(b)) return 1;
	else if(strlen(a) < strlen(b)) return -1;
	else
	{
		if(strcmp(a,b) > 0) return 1;
		else if(strcmp(a,b) < 0) return -1;
		else return 0;
	}
}

int main()
{
	char A[1000], B[1000];
	int a[1000] = {0}, b[1000] = {0}, ans[1000] = {0};
	int i, j, la, lb;
	gets(A); gets(B);
	la = strlen(A); lb = strlen(B);
	for(i = 0, j = la - 1; i < la; i++, j--) a[j] = A[i] - '0';
	for(i = 0, j = lb - 1; i < lb; i++, j--) b[j] = B[i] - '0';

	if(cmp(A,B) > 0)
	{
		for(i = 0; i < la; i++)
		{
			ans[i] += a[i] - b[i];
			if(ans[i] < 0) ans[i + 1]--, ans[i] += 10;
			while(i == la - 1 && ans[i] == 0) la--, i--;
		}
		while(la--) printf("%d", ans[la]);
	}
	else if(cmp(A,B) < 0)
	{
		for(i = 0; i < lb; i++)
		{
			ans[i] += b[i] - a[i];
			if(ans[i] < 0) ans[i + 1]--, ans[i] += 10;
			while(i == lb - 1 && ans[i] == 0) lb--, i--;
		}
		printf("-");
		while(lb--) printf("%d", ans[lb]);
	}
	else printf("0\n");

	return 0;
}