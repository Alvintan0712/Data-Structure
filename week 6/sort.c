#include <stdio.h>
#include <string.h>
#define N 100

int cnt;
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
void Insert_Sort(int a[], int n)
{
    int i, j, min, min_index;
    for(i = 0; i < n - 1; i++)
    {
        for(j = i + 1, min = a[i]; j < n; j++)
            if(cnt++, min > a[j])
            {
                min = a[j];
                min_index = j;
            }

        swap(&a[i],&a[min_index]);
    }
}
void Bubble_Sort(int a[], int n)
{
    int i, j, k, flag = 1;
    for(i = 0; i < n - 1 && flag; i++)
    {
        for(j = 0, k = 1; j < n - i - 1; j++)
            if(a[j] > a[j + 1])
            {
                k = 0;
                swap(&a[j],&a[j + 1]);
            }
        if(flag) cnt += n - i - 1;
        if(k) flag = 0;
    }
}
void adjust(int a[], int i, int n)
{
    int j, temp;
    temp = a[i];
    j = 2*i + 1;

    while(j < n)
    {
        if(j < n - 1 && a[j] < a[j + 1]) j++;
        if(cnt++, temp >= a[j]) break;
        a[(j - 1)/2] = a[j];
        j = 2*j + 1;
    }

    a[(j - 1)/2] = temp;
}
void Heap_Sort(int a[], int n)
{
    int i, temp;

    for(i = (n - 1)/2; i >= 0; i--) adjust(a,i,n);
    for(i = n - 1; i > 0; i--)
    {
        temp = a[i];
        a[i] = a[0];
        a[0] = temp;
        adjust(a,0,i);
    }
}
void Merge(int a[], int t[], int left, int leftend, int rightend)
{
    int i = left, j = leftend + 1, q = left;
    while(i <= leftend && j <= rightend)
    {
        if(cnt++, a[i] <= a[j]) t[q++] = a[i++];
        else t[q++] = a[j++];
    }
    while(i <= leftend)  t[q++] = a[i++];
    while(j <= rightend) t[q++] = a[j++];
    for(i = left; i <= rightend; i++) a[i] = t[i];
}
void Split(int a[], int t[], int start, int end)
{
    int mid;
    if(start < end)
    {
        mid = (start + end) >> 1;
        Split(a,t,start,mid);
        Split(a,t,mid + 1,end);
        Merge(a,t,start,mid,end);
    }
}
void Merge_Sort(int a[], int start, int end)
{
    int t[N], i;
    Split(a,t,start,end);
}
void Quick_Sort(int a[], int start, int end)
{
    int i, last;
    if(start < end)
    {
        last = start; 
        for(i = start + 1; i <= end; i++)
            if(cnt++, a[i] < a[start])
                swap(&a[++last],&a[i]); 

        swap(&a[start],&a[last]);
        Quick_Sort(a,start,last - 1);
        Quick_Sort(a,last + 1,end);
    }
}

int main()
{
    int a[N], n, k, i;
    scanf("%d%d", &n, &k);

    for(i = 0; i < n; i++) scanf("%d", &a[i]);

    switch(k)
    {
        case 1: Insert_Sort(a,n); break;
        case 2: Bubble_Sort(a,n); break;
        case 3: Heap_Sort(a,n); break;
        case 4: Merge_Sort(a,0,n - 1); break;
        case 5: Quick_Sort(a,0,n - 1); break;
    }
    for(i = 0; i < n; i++) printf("%d ", a[i]); puts("");
    printf("%d\n", cnt);

    return 0;
}