#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char c;
    int weight;
    struct Node *l, *r;
}node;

void getalpha(int count[]);
void buildHtree(node **root, int count[]);
void travese(node *root, int depth, char hcode[][20]);
void print(char hcode[][20]);

int main()
{
    int count[128] = {1,0};
    char hcode[128][20] = {{0}};
    node *root = NULL;

    getalpha(count);
    buildHtree(&root,count);
    travese(root,0,hcode);
    print(hcode);

    return 0;
}

void getalpha(int count[])
{
    FILE *in;
    in = fopen("input.txt","r");

    char c;

    while(c = fgetc(in), c != EOF && c != '\n') count[c]++;
    fclose(in);
}

void buildHtree(node **root, int count[])
{
    node *stk[128], *p, *q, *new;
    int i, j, k, top = 0;

    for(i = 0; i < 128; i++)
        if(count[i])
        {
            for(j = 0; j < top; j++)
                if(count[i] < stk[j]->weight) continue;
                else if(count[i] == stk[j]->weight && i < stk[j]->c) continue;
                else break;

            k = j;
            for(j = ++top; j > k; j--) stk[j] = stk[j - 1];

            new = (node*)malloc(sizeof(node));
            new->weight = count[i];
            new->c = i;
            new->l = new->r = NULL;

            stk[k] = new;
        }

    while(top > 1)
    {
        p = stk[--top]; q = stk[--top];

        new = (node*)malloc(sizeof(node));
        new->weight = p->weight + q->weight;
        new->l = p; new->r = q; new->c = 0;

        for(i = 0; i < top && new->weight < stk[i]->weight; i++);
        k = i;
        for(i = top++; i > k; i--) stk[i] = stk[i - 1];

        stk[k] = new;
    }
    *root = stk[0];
}

char t[20];
void travese(node *root, int depth, char hcode[][20])
{
    if(!root) return;
    if(root->l == NULL && root->r == NULL)
    {
        t[depth] = '\0';
        strcpy(hcode[root->c],t);
        return;
    }
    t[depth] = '0'; travese(root->l,depth + 1,hcode);
    t[depth] = '1'; travese(root->r,depth + 1,hcode);
}

void print(char hcode[][20])
{
    FILE *in, *out;
    in = fopen("input.txt","r");
    out = fopen("output.txt","w");

    int i = 0;
    char c, hc = 0, *p;

    while(c = fgetc(in), c != '\n' && c != EOF)
        for(p = hcode[c]; *p; p++)
        {
            hc = (hc << 1) | (*p - '0');
            i++;
            if(i == 8) 
            {
                printf("%x", (unsigned char)hc);
                fprintf(out, "%c", hc);
                i = 0, hc = 0;
            }
        }
    for(p = hcode[0]; *p; p++)
    {
        hc = (hc << 1) | (*p - '0');
        i++;
        if(i == 8) 
        {
            printf("%x", (unsigned char)hc);
            fprintf(out, "%c", hc);
            i = 0, hc = 0;
        }
    }
    if(i)
    {
        while(i < 8) hc = (hc << 1), i++;
        fprintf(out,"%c", hc);
        printf("%x", (unsigned char)hc);
    }

    fclose(in); fclose(out);
}