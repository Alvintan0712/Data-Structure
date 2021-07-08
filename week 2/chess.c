#include <stdio.h>
int jud1(int a[][19], int i, int j)
{
    int cnt, data, x, y;
    x = j, y = i; data = a[i][j];
    for(cnt = 1; cnt < 5 && (data == a[i][j + 1]); j++) cnt++;
    if(cnt >= 4 && !(a[y][x - 1] && a[y][x + 4])) return data;
    else return 0;
}
int jud2(int a[][19], int i, int j)
{
    int cnt, data, x, y;
    x = j, y = i; data = a[i][j];
    for(cnt = 1; cnt < 5 && (data == a[i + 1][j]); i++) cnt++;
    if(cnt >= 4 && !(a[y - 1][x] && a[y + 4][x])) return data;
    else return 0;
}
int jud3(int a[][19], int i, int j)
{
    int cnt, data, x, y;
    x = j, y = i; data = a[i][j];
    for(cnt = 1; cnt < 5 && (data == a[i + 1][j + 1]); i++, j++) cnt++;
    if(cnt >= 4 && !(a[y - 1][x - 1] && a[y + 4][x + 4])) return data;
    else return 0;
}
int jud4(int a[][19], int i, int j)
{
    int cnt, data, x, y;
    x = j, y = i; data = a[i][j];
    for(cnt = 1; cnt < 5 && (data == a[i + 1][j - 1]); i++, j--) cnt++;
    if(cnt >= 4 && !(a[y - 1][x + 1] && a[y + 4][x - 4])) return data;
    else return 0;
}
int main()
{
    int a[19][19];
    int i, j, min_x = 19, max_x = 0, min_y = 19, max_y = 0;
    for(i = 0; i < 19; i++)
        for(j = 0; j < 19; j++)
        {
            scanf("%d", &a[i][j]);
            if(a[i][j])
            {
                if(min_x > j) min_x = j;
                if(min_y > i) min_y = i;
                if(max_x < j) max_x = j;
                if(max_y < i) max_y = i;
            }
        }
    for(i = min_y; i <= max_y; i++)
        for(j = min_x; j <= max_x; j++)
            if(jud1(a,i,j) || jud2(a,i,j) || jud3(a,i,j) || jud4(a,i,j)) 
            {
                if(jud1(a,i,j)) return printf("%d:%d,%d\n", jud1(a,i,j), i + 1, j + 1), 0;
                if(jud2(a,i,j)) return printf("%d:%d,%d\n", jud2(a,i,j), i + 1, j + 1), 0;
                if(jud3(a,i,j)) return printf("%d:%d,%d\n", jud3(a,i,j), i + 1, j + 1), 0;
                if(jud4(a,i,j)) return printf("%d:%d,%d\n", jud4(a,i,j), i + 1, j + 1), 0;
            }
    printf("No\n");
    return 0;
}