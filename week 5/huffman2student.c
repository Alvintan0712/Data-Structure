//文件压缩-Huffman实现
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode {                      //Huffman树结构
    char c;     
    int weight;                     //树节点权重，叶节点为字符和它的出现次数
    struct tnode *left,*right;
} ; 
int Ccount[128] = {0};              //存放每个字符的出现次数，如Ccount[i]表示ASCII值为i的字符出现次数 
struct tnode *Root = NULL;          //Huffman树的根节点
char HCode[128][MAXSIZE] = {{0}};   //字符的Huffman编码，如HCode['a']为字符a的Huffman编码（字符串形式） 
int Step = 0;                       //实验步骤 
FILE *Src, *Obj;
    
void statCount();                   //步骤1：统计文件中字符频率
void createHTree();                 //步骤2：创建一个Huffman树，根节点为Root 
void makeHCode();                   //步骤3：根据Huffman树生成Huffman编码
void atoHZIP();                     //步骤4：根据Huffman编码将指定ASCII码文本文件转换成Huffman码文件

void print1();                      //输出步骤1的结果
void print2(struct tnode *p);       //输出步骤2的结果 
void print3();                      //输出步骤3的结果
void print4();                      //输出步骤4的结果

int main()
{
    if((Src = fopen("input.txt","r")) == NULL) 
    {
        fprintf(stderr, "%s open failed!\n", "input.txt");
        return 1;
    }
    if((Obj = fopen("output.txt","w")) == NULL) 
    {
        fprintf(stderr, "%s open failed!\n", "output.txt");
        return 1;
    }
    scanf("%d", &Step);                     //输入当前实验步骤 
        
    statCount();                            //实验步骤1：统计文件中字符出现次数（频率）
    (Step == 1) ? print1(): 1;              //输出实验步骤1结果 
    createHTree();                          //实验步骤2：依据字符频率生成相应的Huffman树
    (Step == 2) ? print2(Root): 2;          //输出实验步骤2结果 
    makeHCode(Root);                        //实验步骤3：依据Root为树的根的Huffman树生成相应Huffman编码
    (Step == 3) ? print3(): 3;              //输出实验步骤3结果
    (Step >= 4) ? atoHZIP(),print4(): 4;    //实验步骤4：据Huffman编码生成压缩文件，并输出实验步骤4结果 

    fclose(Src);
    fclose(Obj);

    return 0;
} 

//【实验步骤1】开始 

void statCount()
{
    char c;
    while(c = fgetc(Src), c != EOF && c != '\n') Ccount[c]++;
    Ccount[0] = 1;
    rewind(Src);
}

//【实验步骤1】结束

//【实验步骤2】开始

void createHTree()
{
    struct tnode *new, *a[1000], *t;
    int i, j, top = 0;

    for(i = 0; i < 128; i++)
        if(Ccount[i] > 0)
        {
            new = (struct tnode*)malloc(sizeof(struct tnode));
            new->c = i; new->weight = Ccount[i];
            new->left = new->right = NULL;
            a[top++] = new;
        }

    for(i = 0; i < top - 1; i++)
        for(j = 0; j < top - i - 1; j++)
        {
            if(a[j]->weight < a[j + 1]->weight) t = a[j], a[j] = a[j + 1], a[j + 1] = t;
            else if(a[j]->weight == a[j + 1]->weight && a[j]->c < a[j + 1]->c) t = a[j], a[j] = a[j + 1], a[j + 1] = t;            
        }

    while(top > 1)
    {
        new = (struct tnode*)malloc(sizeof(struct tnode));
        new->left = a[--top]; 
        new->right = a[--top];
        new->weight = new->left->weight + new->right->weight;

        for(i = 0; i < top && a[i]->weight > new->weight; i++);
        j = i;
        for(i = top; i > j; i--) a[i] = a[i - 1];
        top++;
        a[j] = new;
    }
    Root = a[0];
}

//【实验步骤2】结束

//【实验步骤3】开始
char H[1000];
void visit(struct tnode *p, char code, int depth)
{
    if(depth >= 0) H[depth] = code;
    if(p->left == NULL && p->right == NULL) H[depth + 1] = '\0', strcpy(HCode[p->c],H);
    else
    {
        visit(p->left,'0',depth + 1);
        visit(p->right,'1',depth + 1);
    }
}
void makeHCode()
{
    visit(Root,'0',-1);
}
//【实验步骤3】结束

//【实验步骤4】开始

void atoHZIP()
{
    int i, cnt = 0;
    char c, hc = 0, *s;

    while(c = fgetc(Src), c != EOF && c != '\n') 
    {
        s = HCode[c];
        while(*s)
        {
            hc = (hc << 1) | (*s - '0');
            cnt++;
            if(cnt == 8)
            {
                fputc(hc,Obj);
                printf("%x", (unsigned char)hc);
                cnt = 0;
            }
            s++;
        }
    }
    s = HCode[0];
    while(*s)
    {
        hc = (hc << 1) | (*s - '0');
        cnt++;
        if(cnt == 8)
        {
            fputc(hc,Obj);
            printf("%x", (unsigned char)hc);
            cnt = 0;
        }
        s++;
    }
    while(cnt < 8)
    {
        hc <<= 1;
        cnt++;
    }
}

//【实验步骤4】结束

void print1()
{
    int i;
    printf("NUL:1\n");
    for(i = 1; i < 128; i++)
        if(Ccount[i] > 0)
            printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode *p)
{
    if(p != NULL)
    {
        if((p->left == NULL) && (p->right == NULL)) 
            switch(p->c)
            {
                case 0:    printf("NUL ");      break;
                case ' ':  printf("SP ");       break;
                case '\t': printf("TAB ");      break;
                case '\n': printf("CR ");       break;
                default:   printf("%c ",p->c);  break;
            }
        print2(p->left);
        print2(p->right);
    }
}

void print3()
{
    int i;
    
    for(i = 0; i < 128; i++)
    {
        if(HCode[i][0] != 0)
        {
            switch(i)
            {
                case 0:    printf("NUL:");  break;
                case ' ':  printf("SP:");   break;
                case '\t': printf("TAB:");  break;
                case '\n': printf("CR:");   break;
                default:   printf("%c:",i); break;
            }
            printf("%s\n", HCode[i]);
        }
    }
} 

void print4()
{
    long int in_size, out_size;
    
    fseek(Src,0,SEEK_END);
    fseek(Obj,0,SEEK_END);
    in_size = ftell(Src);
    out_size = ftell(Obj);
    
    printf("\n原文件大小：%ldB\n", in_size);
    printf("压缩后文件大小：%ldB\n", out_size);
    printf("压缩率：%.2f%%\n",(float)(in_size-out_size)*100/in_size);
}