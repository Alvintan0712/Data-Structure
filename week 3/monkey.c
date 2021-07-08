#include <stdio.h>

int king(int n, int m)
{
    if(n == 1) return 0;
    return (king(n - 1,m) + m) % n;
}

int main()
{
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    printf("%d\n", (king(n,m) + q) % n);

    return 0;
}