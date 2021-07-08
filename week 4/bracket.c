#include <stdio.h>

struct stack
{
    char c;
    int l;
}stk1[1000], tar, t;
int top1 = -1, top2 = -1;
char stk2[1000];

int isbrac(char c)
{
    return c == '(' || c == ')' || c == '{' || c == '}';
}

int main()
{
    FILE *in;
    int line, i, k = 1, q = 1, r = 1;
    char s[1000];
    in = fopen("example.c","r");

    for(line = 1; fgets(s,1000,in); line++)
    {
        for(i = 0; s[i] != '\n' && s[i]; i++)
        {
            if(s[i + 1] && s[i] == '/' && s[i + 1] == '/') break;
            else if(s[i + 1] && s[i] == '/' && s[i + 1] == '*') k = 0;
            else if(s[i + 1] && s[i] == '*' && s[i + 1] == '/') k = 1;
            if(k && r && s[i] == '\"' && (i == 0 || s[i - 1] != '\\')) q = q? 0 : 1;
            if(k && q && s[i] == '\'' && (i == 0 || s[i - 1] != '\\')) r = r? 0 : 1;

            if(k && q && r && isbrac(s[i]))
            {
                stk2[++top2] = s[i];

                if(s[i] == '(')
                {
                    stk1[++top1].c = s[i];
                    stk1[top1].l = line;
                }
                else if(s[i] == '{')
                {
                    if(stk1[top1].c == '(')
                    {
                        printf("without maching '(' at line %d\n", line);
                        return 0;
                    }
                    else
                    {
                        stk1[++top1].c = s[i];
                        stk1[top1].l = line;
                    }
                }
                else if(s[i] == ')')
                {
                    if(stk1[top1].c == '(') top1--;
                    else 
                    {
                        printf("without maching ')' at line %d\n", line);
                        return 0;
                    }
                }
                else if(s[i] == '}')
                {
                    if(stk1[top1].c == '{') top1--;
                    else 
                    {
                        printf("without maching '}' at line %d\n", line);
                        return 0;
                    }
                }
            }
        }
    }
    if(top1 == -1)
        for(i = 0; i <= top2; i++) 
            printf("%c", stk2[i]);
    else
        printf("without maching '%c' at line %d\n", stk1[top1].c, stk1[top1].l);

    return 0;
}