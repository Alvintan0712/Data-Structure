#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define Max 100000

int main()
{
	int i, j;
	char a, b;
	char *s = (char*)malloc(sizeof(char)*Max);
	scanf("%s", s);
	for(i = 0; i < strlen(s); i++)
	{
		if(s[i] == '-')
		{
			a = s[i - 1]; b = s[i + 1];
			if((isupper(a) && isupper(b)) || (islower(a) && islower(b)) || (isdigit(a) && isdigit(b)))
				for(a++; a < b; a++) putchar(a);
			else putchar(s[i]);
		}
		else putchar(s[i]);
	}

	return 0;
}