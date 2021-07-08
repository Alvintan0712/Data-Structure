#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int n, t;
    struct Node *nxt;
}node;
int ppl = 0, n = 1, cnt = 3;

void insert(node *head, int num)
{
    node *new, *p;
    for(p = head; p->nxt; p = p->nxt);
    while(num--)
    {
        new = (node*)malloc(sizeof(node));
        new->n = n++; new->t = 0;
        new->nxt = NULL;

        p->nxt = new;
        p = new;
        ppl++;
    }
}
void delete(node *head, int cnt)
{
    node *p = head->nxt;

    while(cnt-- && ppl)
    {
        head->nxt = p->nxt;
        printf("%d : %d\n", p->n, p->t);
        free(p);
        p = head->nxt;
        ppl--;
    }
    for(p = head->nxt; p; p = p->nxt) (p->t)++;
}

int main()
{
    int T, num;
    node *head;
    head = (node*)malloc(sizeof(node));
    head->nxt = NULL; 

    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &num);
        insert(head,num);
        if(cnt == 3) while(ppl >= 7*cnt && cnt < 5) cnt++;
        else if(cnt == 4)
        {
            if(ppl >= 7*cnt) cnt++;
            else if(ppl < 7*cnt) cnt--;
        }
        else if(ppl < 7*cnt && cnt == 5) cnt--;
        delete(head,cnt);
    }
    while(head->nxt) 
    {
        if(ppl < 7*cnt && cnt > 3) cnt--;
        delete(head,cnt);
    }

    return 0;
}