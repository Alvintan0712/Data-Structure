#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 1245721
#define M 100000
#define CNT 10000
#define BUCKET_SIZE 10000
#define LEN 50

char article[N][LEN], str[100*M];
int nxt[N], visit[N], cnt1[N], cnt2[N];
int Bucket1[CNT][BUCKET_SIZE], Bucket2[CNT][BUCKET_SIZE];
int a1[M], a2[M], top1[M], top2[M];

int main()
{
    int MAX;
    scanf("%d", &MAX);

    FILE *fp;

    register char *s;
    register long int length;
    register unsigned int i, j, len, key, n, nxt_n = N >> 1;
    char t[LEN], buff[1024] = {0};

    s = (char*)malloc(sizeof(char)*10000010);

    //read article1.txt
    fp = fopen("article1.txt","rb");

    fseek(fp,0L,SEEK_END);
    length = ftell(fp);
    fseek(fp,0L,SEEK_SET);
    fread(s,1,length,fp);

    i = 0;
    while(i < length)
    {
        while(i < length && !isalpha(s[i])) ++i;
        len = 0;
        while(i < length && isalpha(s[i])) t[len++] = tolower(s[i++]);
        t[len] = '\0';
        if(!len) 
        {
            ++i;
            continue;
        }

        key = 0; j = 0;
        while(j < len) key = (key << 7) + (key << 1) + key + t[j++];
        n = key % (N >> 1);

        if(!article[n][0]) strcpy(article[n],t), cnt1[n]++;
        else
        {
            while(article[n][0])
            {
                if(strcmp(t,article[n]) == 0)
                {
                    cnt1[n]++;//若是相同字符串
                    break;
                }
                else if(nxt[n]) n = nxt[n];//若后面还有数据
                else//若后面没有数据
                {
                    nxt[n] = nxt_n++;//申请新空间
                    strcpy(article[nxt[n]],t);//存储数据
                    cnt1[nxt[n]]++;//频数为1
                    break;
                }
            }
        }
        
        ++i;
    }

    fclose(fp);

    //read article2.txt
    fp = fopen("article2.txt","rb");

    fseek(fp,0L,SEEK_END);
    length = ftell(fp);
    fseek(fp,0L,SEEK_SET);
    fread(s,1,length,fp);

    i = 0;
    while(i < length)
    {
        while(i < length && !isalpha(s[i])) ++i;
        len = 0;
        while(i < length && isalpha(s[i])) t[len++] = tolower(s[i++]);
        t[len] = '\0';
        if(!len) 
        {
            ++i;
            continue;
        }

        key = 0; j = 0;
        while(j < len) key = (key << 7) + (key << 1) + key + t[j++];
        n = key % (N >> 1);

        if(!article[n][0]) strcpy(article[n],t), cnt2[n]++;
        else
        {
            while(article[n][0])
            {
                if(strcmp(t,article[n]) == 0)
                {
                    cnt2[n]++;//若是相同字符串
                    break;
                }
                else if(nxt[n]) n = nxt[n];//若后面还有数据
                else//若后面没有数据
                {
                    nxt[n] = nxt_n++;//申请新空间
                    strcpy(article[nxt[n]],t);//存储数据
                    cnt2[nxt[n]]++;//频数为1
                    break;
                }
            }
        }
        
        ++i;
    }

    fclose(fp);

    //read stopwords.txt
    fp = fopen("stopwords.txt","rb");

    fseek(fp,0L,SEEK_END);
    length = ftell(fp);
    fseek(fp,0L,SEEK_SET);
    fread(s,1,length,fp);

    i = 0;
    while(i < length)
    {
        while(i < length && !isalpha(s[i])) ++i;
        len = 0;
        while(i < length && isalpha(s[i])) t[len++] = tolower(s[i++]);
        t[len] = '\0';
        if(!len) 
        {
            ++i;
            continue;
        }

        key = 0; j = 0;
        while(j < len) key = (key << 7) + (key << 1) + key + t[j++];
        n = key % (N >> 1);

        while(article[n][0])
        {
            if(strcmp(t,article[n]) == 0) 
            {
                cnt1[n] = cnt2[n] = 0;
                break;
            }
            else if(nxt[n]) n = nxt[n];
            else break;
        }
        
        ++i;
    }

    fclose(fp);

    //read dictionary.txt
    fp = fopen("dictionary.txt","rb");

    fseek(fp,0L,SEEK_END);
    length = ftell(fp);
    fseek(fp,0L,SEEK_SET);
    fread(s,1,length,fp);

    i = 0;
    while(i < length)
    {
        while(i < length && !isalpha(s[i])) ++i;
        len = 0;
        while(i < length && isalpha(s[i])) t[len++] = tolower(s[i++]);
        t[len] = '\0';
        if(!len) 
        {
            ++i;
            continue;
        }

        key = 0; j = 0;
        while(j < len) key = (key << 7) + (key << 1) + key + t[j++];
        n = key % (N >> 1);

        while(article[n][0])
        {
            if(strcmp(t,article[n]) == 0) 
            {
                if(cnt1[n]) Bucket1[cnt1[n]][top1[cnt1[n]]++] = n;
                if(cnt2[n]) Bucket2[cnt2[n]][top2[cnt2[n]]++] = n;
                break;
            }
            else if(nxt[n]) n = nxt[n];
            else break;
        }
        
        ++i;
    }

    fclose(fp);

    //write in results.txt and solve it
    fp = fopen("results.txt","wb");

    register int ttop1 = 0, ttop2 = 0, freq1 = 0, freq2 = 0, ffreq1 = 0, ffreq2 = 0;
    double pro1, pro2, sim;

    for(i = CNT; ttop1 < MAX && i > 0; i--)
        for(j = 0; ttop1 < MAX && j < top1[i]; j++)
        {
            a1[ttop1] = Bucket1[i][j];
            freq1 += cnt1[a1[ttop1]];
            visit[a1[ttop1]] = 1;
            ++ttop1;
        }

    for(i = CNT; ttop2 < MAX && i > 0; i--)
        for(j = 0; ttop2 < MAX && j < top2[i]; j++)
        {
            a2[ttop2] = Bucket2[i][j];
            freq2 += cnt2[a2[ttop2]];
            if(visit[a2[ttop2]]) ffreq1 += cnt1[a2[ttop2]], ffreq2 += cnt2[a2[ttop2]];
            ++ttop2;
        }

    pro1 = (double)ffreq1/freq1;
    pro2 = (double)ffreq2/freq2;

    if(pro1 < pro2) sim = pro1 / pro2;
    else sim = pro2 / pro1;

    printf("%.5lf\n", sim);
    sprintf(str,"%.5lf\n\n", sim);
    for(i = 0; i < ttop1; i++) 
    {
        sprintf(buff, "%s %d\n", article[a1[i]], cnt1[a1[i]]);
        strcat(str,buff);
    }
    strcat(str,"\n");
    for(i = 0; i < ttop2; i++) 
    {
        sprintf(buff, "%s %d\n", article[a2[i]], cnt2[a2[i]]);
        strcat(str,buff);
    }
    fwrite(str,strlen(str),1,fp);
    fclose(fp);

    return 0;
}