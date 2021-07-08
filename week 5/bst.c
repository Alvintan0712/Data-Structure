#include <stdio.h>
#include <stdlib.h>

typedef struct tree
{
    int data;
    struct tree *l, *r;
}node;

void insert(int data, node **root)
{
    node *new;
    if(*root)
    {
        if(data >= (*root)->data) insert(data,&(*root)->r);
        else insert(data,&(*root)->l);
    }
    else
    {
        new = (node*)malloc(sizeof(node));
        new->l = NULL; new->r = NULL;
        new->data = data;

        *root = new;
    }
}
void print(node *root, int depth)
{
    if(root)
    {
        print(root->l,depth + 1);
        if(root->l == NULL && root->r == NULL) printf("%d %d\n", root->data, depth);
        print(root->r,depth + 1);        
    }
}

int main()
{
    int n, data;
    node *root = NULL;

    scanf("%d", &n);
    while(n--) 
    {
        scanf("%d", &data);
        insert(data,&root);
    }
    print(root,1);

    return 0;
}