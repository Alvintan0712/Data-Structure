#include <stdio.h>
#include <stdlib.h>
#define max(a,b) ((a)>(b))? (a):(b)

typedef struct tree
{
    int num, depth, cnt, n;
    struct tree *l, *m, *r;
}node;
int v[101], m = 1, max_root, max_depth, top = -1;
node *stack[100];

node* createNode(int num, int depth)
{
    node *new;

    new = (node*)malloc(sizeof(node));
    new->l = NULL; new->m = NULL; new->r = NULL;
    new->num = num; new->depth = depth; new->cnt = 0;

    return new;
}
void insert(node **root, int r, int a, int b, int c, int depth)
{
    if(!v[r])
    {
        *root = createNode(r,depth); v[r] = 1;
        if(a) (*root)->l = createNode(a,depth + 1), v[a] = 1, (*root)->cnt++;
        if(b) (*root)->m = createNode(b,depth + 1), v[b] = 1, (*root)->cnt++;
        if(c) (*root)->r = createNode(c,depth + 1), v[c] = 1, (*root)->cnt++;
        if(max_root < (*root)->cnt) max_root = (*root)->cnt;

        return;
    }

    if(*root == NULL) return;
    else if(r == (*root)->num)
    {
        if(a) (*root)->l = createNode(a,depth + 1), v[a] = 1, (*root)->cnt++;
        if(b) (*root)->m = createNode(b,depth + 1), v[b] = 1, (*root)->cnt++;
        if(c) (*root)->r = createNode(c,depth + 1), v[c] = 1, (*root)->cnt++;
        if(max_root < (*root)->cnt) max_root = (*root)->cnt;
    }
    else
    {
        insert(&(*root)->l,r,a,b,c,depth + 1);
        insert(&(*root)->m,r,a,b,c,depth + 1);
        insert(&(*root)->r,r,a,b,c,depth + 1);
    }
}
void travel(node *root)
{
    if(root == NULL) return;
    if(root->cnt == max_root)
    {
        if(max_depth < root->depth) 
        {
            max_depth = root->depth;
            while(top >= 0) top--;
        }
        if(root->depth == max_depth) stack[++top] = root;
    }
    root->n = m++;
    travel(root->l);
    travel(root->m);
    travel(root->r);
}

int main()
{
    int n, i;
    int r, a, b, c;
    node *root = NULL;
    scanf("%d", &n);
    while(n--)
    {
        scanf("%d%d%d%d", &r, &a, &b, &c);
        insert(&root,r,a,b,c,1);
    }
    travel(root);
    for(i = 0; i <= top; i++) printf("%d %d\n", stack[i]->num, stack[i]->n);

    return 0;
}