#include<stdio.h>
#include<string.h>
#define N 100000

char s[N], in[N], flt[N];
int main()
{
	int len_i, len_f, i, n;
	scanf("%s", s);
	for(i = 0, len_i = 0; s[i] != '.'; i++)	in[len_i++] = s[i];
	for(i++, len_f = 0; s[i]; i++)	flt[len_f++] = s[i];
	//若是0.001
	if(len_i == 1 && in[0] == '0')
	{
		for(n = 0, i = 0; flt[i] == '0'; i++, n--);
		if(flt[i + 1] == 0) printf("%se%d\n", &flt[i], n - 1);
		else printf("%c.%se%d\n", flt[i], &flt[i + 1], n - 1);
	}
	//若不是0.001
	else printf("%c.%s%se%d\n", in[0], &in[1], flt,len_i - 1);

	return 0;
}