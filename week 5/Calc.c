#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node
{
    int num, flag;
    char op;
    struct Node *l, *r;
}node;
int top;
node *root = NULL;
node *stk[1000];

void buildtree();
void print(node *root)
{
    if(!root) return;
    print(root->l);
    print(root->r);
    if(root->flag) printf("%d ", root->num);
    else printf("%c ", root->op);
}
int calc(node *root)
{
    int a, b;
    if(!root) return 0;
    if(root->flag) return root->num;
    a = calc(root->l);
    b = calc(root->r);
    if(root->op == '+') root->num = a + b, root->flag = 1;
    if(root->op == '-') root->num = a - b, root->flag = 1;
    if(root->op == '*') root->num = a * b, root->flag = 1;
    if(root->op == '/') root->num = a / b, root->flag = 1;
    return root->num;
}

int main()
{
    buildtree();
    if(root->flag) printf("%d ", root->num);
    else printf("%c ", root->op);
    if(root->l->flag) printf("%d ", root->l->num);
    else printf("%c ", root->l->op);
    if(root->r->flag) printf("%d ", root->r->num);
    else printf("%c ", root->r->op);
    puts("");

    printf("%d\n", calc(root));

    return 0;
}

int isop(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

void insertNode(node *new)
{
    node *a, *b;

    if(new->flag) stk[top++] = new;
    else
    {
        b = stk[--top];
        a = stk[--top];
        new->l = a; new->r = b;
        stk[top++] = new;
    }
}

void buildtree()
{
    int i, n, ttop = -1;
    char s[1000], t[1000], c;
    node *new;
    gets(s);

    for(i = 0; s[i] && s[i] != '='; i++)
    {
        if(isdigit(s[i]))
        {
            n = atoi(s + i);
            new = (node*)malloc(sizeof(node));
            new->num = n; new->flag = 1;
            new->l = new->r = NULL;

            insertNode(new);

            while(isdigit(s[i + 1])) i++;
        }

        else if(isop(s[i]))
        {
            if(ttop == -1) t[++ttop] = s[i];
            else
            {
                if(s[i] == '+' || s[i] == '-')
                {
                    while(ttop >= 0 && t[ttop] != '(')
                    {
                        new = (node*)malloc(sizeof(node));
                        new->op = t[ttop--]; new->flag = 0;
                        new->l = new->r = NULL;

                        c = new->op;
                        insertNode(new);

                        if(c == '+' || c == '-') break;
                    }
                }
                else
                {
                    if(t[ttop] == '*' || t[ttop] == '/')
                    {
                        new = (node*)malloc(sizeof(node));
                        new->op = t[ttop--]; new->flag = 0;
                        new->l = new->r = NULL;

                        insertNode(new);
                    }
                }
                t[++ttop] = s[i];
            }
        }
        else if(s[i] == '(') t[++ttop] = s[i];
        else if(s[i] == ')')
        {
            while(isop(t[ttop]))
            {
                new = (node*)malloc(sizeof(node));
                new->op = t[ttop--]; new->flag = 0;
                new->l = new->r = NULL;

                insertNode(new);
            }
            ttop--;
        }
    }
    while(ttop >= 0)
    {
        new = (node*)malloc(sizeof(node));
        new->op = t[ttop--]; new->flag = 0;
        new->l = new->r = NULL;

        insertNode(new);        
    }
    root = stk[0];
}