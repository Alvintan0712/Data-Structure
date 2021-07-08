#include <stdio.h>
#include <ctype.h>
#define MAX 60000

char s[MAX] = {0};
int n[MAX] = {0};
int main() 
{
	int i, j, len, sum;
	char op[MAX];
	gets(s);
	for(len = 0, i = 0, j = 0; s[i]; i++)
	{
		if(isdigit(s[i])) n[len] = n[len]*10 + s[i] - '0';
		else if(isspace(s[i])) continue;
		else op[len++] = s[i];
	}
	for(i = 0; i < len; i++)
	{
		int t;
		if(op[i] == '*' || op[i] == '/') 
		{
			t = n[i]; j = i - 1;
			while(op[i] == '*' || op[i] == '/') 
			{
				if(op[i] == '*') t *= n[++i];
				else if(op[i] == '/') t /= n[++i];
			}
			if(j < 0) sum = t;
			else if(op[j] == '+') sum += t;
			else if(op[j] == '-') sum -= t;
		}
		else if(op[i] == '+' || op[i] == '-')
		{
			if(i == 0) sum = n[i];
			else if(op[i - 1] == '+') sum += n[i];
			else sum -= n[i];
		}
		else
		{
			if(op[i - 1] == '+') sum += n[i];
			else if(op[i - 1] == '-') sum -= n[i];
			else sum = n[0];
		}
	}
	printf("%d\n", sum);

	return 0;
}