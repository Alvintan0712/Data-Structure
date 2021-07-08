#include <stdio.h>
#include <string.h>

typedef struct book
{
    char book[55], au[25], shd[35], date[15];
}lib;
lib a[1000];

int insert(int n)
{
    lib t = a[n];
    int i, j;

    for(i = 0; i < n; i++)
        if(strcmp(t.book,a[i].book) <= 0)
        {
            if(strcmp(t.book,a[i].book) == 0) return 0;
            else
            {
                for(j = n; j > i; j--) a[j] = a[j - 1];
                a[i] = t;
                return 1;                
            }
        }
    return 1;
}
void check(char *s, int n)
{
    int i;
    for(i = 0; i < n; i++)
        if(strstr(a[i].book,s)) printf("%-50s%-20s%-30s%-10s\n", a[i].book, a[i].au, a[i].shd, a[i].date);
}
int delete(char *s, int n)
{
    int i, j, v[100] = {0};
    for(i = 0; i < n; i++)
        if(strstr(a[i].book,s)) v[i] = 1;
    for(i = 0, j = 0; i < n; i++)
        if(!v[i]) a[j++] = a[i];
    return j;
}

int main()
{
    FILE *in, *out;
    int i, j, n, x;
    char s[100];
    lib t;
    in = fopen("books.txt","r");
    out = fopen("ordered.txt","w");
    for(n = 0; fscanf(in,"%s%s%s%s", a[n].book, a[n].au, a[n].shd, a[n].date) == 4; n++);

    for(i = 0; i < n - 1; i++)
        for(j = 0; j < n - i - 1; j++)
        {
            if(strcmp(a[j].book,a[j + 1].book) > 0)
            {
                t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }

    do
    {
        scanf("%d", &x);
        switch(x)
        {
            case 1:
            scanf("%s%s%s%s", a[n].book, a[n].au, a[n].shd, a[n].date);
            n += insert(n);
            break;
            case 2:
            scanf("%s", s);
            check(s,n);
            break;
            case 3:
            scanf("%s", s);
            n = delete(s,n);
            break;
            default: break;
        }
    }while(x);
    for(i = 0; i < n; i++) fprintf(out,"%-50s%-20s%-30s%-10s\n", a[i].book, a[i].au, a[i].shd, a[i].date);

    fclose(in); fclose(out);

    return 0;
}