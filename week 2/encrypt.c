#include <stdio.h>
#include <ctype.h>
#define N 10000

void purge (char a[])
{
    int i, j;
    int v[N] = {0};
    for (i = 0; a[i]; i++)
    {
        if(v[i] == 1) continue;
        for (j = i + 1; j < a[j]; j++)
            if (a[j] == a[i]) v[j] = 1;
    }
    for(i = 0, j = 0; a[i]; i++)
        if (!v[i]) a[j++] = a[i];
    a[j] = '\0';
}

char pass(char c, char a[])
{
    if(islower(c)) return a[c - 'a'];
    else return c;
}

int main()
{
    FILE *in, *out;
    int i, j;
    char s[N], a[26], p[50], v[50] = {0};

    scanf("%s", p);
    purge(p);

    for(i = 0; i < 26 && p[i]; i++) a[i] = p[i], v[p[i] - 'a'] = 1;
    for(i, j = 'z'; i < 26; j--)
        if(!v[j - 'a']) 
            a[i] = j, i++;

    in = fopen("encrypt.txt","r");
    out = fopen("output.txt","w");

    while(fgets(s,N,in) != NULL)
        for(i = 0; s[i]; i++) 
            putc(pass(s[i],a),out);

    fclose(in), fclose(out);

    return 0;
}