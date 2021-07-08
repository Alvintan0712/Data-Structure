#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define N 10000
int index(char s[], char t[])
{
    while(tolower(*s) == tolower(*t)) s++, t++;
    if(*t) return 0;
    return 1;
}
int main()
{
    FILE *in, *out;
    char *s, s1[N], s2[N];
    s = (char*)malloc(N);
    scanf("%s%s", s1, s2);
    in  = fopen("filein.txt","r");
    out = fopen("fileout.txt","w");
    while(fgets(s,N,in) != NULL)
    {
        while(*s)
        {
            if(tolower(*s) != tolower(*s1)) putc(*s,out), s++;
            else if(tolower(*s) == tolower(*s1))
            {
                if(index(s,s1)) fprintf(out,"%s",s2), s += strlen(s1);
                else putc(*s,out), s++;
            }
        }
    }
    fclose(in); fclose(out);

    return 0;
}