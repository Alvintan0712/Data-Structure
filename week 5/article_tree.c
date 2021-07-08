#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node
{
    int num;
    char *word;
    struct Node *l, *r;
}node;

void insert(node **root, char *s)
{
    node *new;
    if(*root)
    {
        if(strcmp(s,(*root)->word) > 0) insert(&(*root)->r,s);
        else if(strcmp(s,(*root)->word) < 0) insert(&(*root)->l,s);
        else (*root)->num++;
    }
    else
    {
        new = (node*)malloc(sizeof(node));
        new->word = (char*)malloc(sizeof(char)*strlen(s));

        new->l = NULL; new->r = NULL;
        strcpy(new->word,s); new->num = 1;

        *root = new;
    }
}
void print(node *root)
{
    if(root)
    {
        print(root->l);
        printf("%s %d\n", root->word, root->num);
        print(root->r);        
    }
}

int main()
{
    int i, j, len;
    char s[1000] = {0}, t[1000] = {0};
    node *p, *root = NULL;
    FILE *in;
    in = fopen("article.txt","r");
    while(fgets(s,1000,in))
    {
        for(i = 0, len = 0; s[i]; i++)
        {
            if(isalpha(s[i])) s[len++] = tolower(s[i]);
            else s[len++] = ' ';
        }
        s[len] = '\0';

        for(i = 0; s[i]; i++) 
        {
            memset(t,'\0',i);
            for(j = 0; isalpha(s[i]); i++) t[j++] = s[i];
            t[j] = '\0';
            if(t[0] == '\0') continue;

            insert(&root,t);
        }
    }
    for(p = root, i = 0; p && i < 3; i++, p = p->r) printf("%s ", p->word); puts("");
    print(root);
    fclose(in);

    return 0;
}