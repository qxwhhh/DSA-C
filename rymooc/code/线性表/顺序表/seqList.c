//设计出1个相对完整的程序的 “五步操作法”
//分析参数、空间检查、核心操作、对其他属性的影响、正确返回。

//不知道为什么，vscode中这个代码居然实现不了😅😅😅😅😅😅

//即线性表的顺序存储结构
//对应于逻辑结构的存储结构的一种实现方式

#include<stdio.h>
#include<stdlib.h>
#define INITSIZE 100

typedef int elemType;
typedef struct
{
    elemType *elem;//！顺序表存储数组，存放实际的数组元素
    int len;
    int maxSize;
}seqList;

//1.初始化顺序表，需要申请动态数组，并将0号位置空出用作“哨兵”，并将结构题中各个元素赋值
void initialize(seqList *L);

//2.3.
int isEmpty(seqList *L){return(L->len==0);}
int isFull(seqList *L){return(L->len==L->maxSize);}


//4.返回获得表的长度
int length(seqList *L){return L->len;}

//5.返回获得第i个元素的值
elemType get(seqList * L,int i);

//6.返回值等于e的元素的编号，无则返回0
int find(seqList *L,elemType e);

/*  7.在第i个位置上插入新的元素（值为e）
    并使原来的第i个元素及后面的所有元素都向后移动一个位置   
    插入成功返回1，否则为0  
    否则情况包括插入位置不在数组范围内，如数组最大值之外或小于0 */
int insert(seqList *L,int i, elemType e);

/*  8.删除第i个元素，若i小于0或大于数组最后一个元素对应编号，返回0
    删除成功时将被删除元素的值放入（*e）中 ，返回1  */
int Remove(seqList *L,int i,elemType* e);

//9.
void clear(seqList *L){free(L->elem);}

//已知两个正整数集合，求其交集
/*将两个集合分别存放至两个顺序表中
  用第三个顺序表来存放公共部分
  (通过find function逐一遍历对比)找到相同元素*/
int main()
{
    seqList list1,list2,list3;
    int i,j,x;
    int len1,len2,len3;

    initialize(&list1);
    initialize(&list2);
    initialize(&list3);

    //输入第一个整数集合中的元素，输入0结束
    i = 1;
    printf("输入第一个整数集合中的元素，输入0结束:");
    scanf("%d",&x);
    while (x!=0)
    {
        if (insert(&list1,i,x)==0)
        {
            exit(1);
        }
        i++;
        scanf("%d",&x);
    }
    //输入第二个整数集合中的元素，输入0结束
    i = 1;
    printf("输入第二个整数集合中的元素，输入0结束:");
    scanf("%d",&x);
    while (x!=0)
    {
        if (insert(&list2,i,x)==0)
        {
            exit(1);
        }
        i++;
        scanf("%d",&x);
    }

    //求交集，保存至list3
    len1 = length(&list1);
    len2 = length(&list2);
    j = 1;
    for ( i = 0; i <= len1; i++)
    {
        x = get(&list1,i);
        if (find(&list2,x)!=0)
        {
            insert(&list3,j,x);
            j++;
        }
        
    }
    
    //显示list3中的元素
    printf("两个集合的交集元素为：");
    len3 = length(&list3);
    for ( i = 1; i <= len3; i++)
    {
        x = get(&list3,i);
        printf("%d ",x);
    }
    printf("\n");
    
    clear(&list1);
    clear(&list2);
    clear(&list3);

    return 0;
}

void initialize(seqList *L)
{
    L->elem = (elemType*)malloc(sizeof(elemType)*INITSIZE);
    if (!L->elem)
    {
        exit(-1);
    }
    L->maxSize = INITSIZE - 1;
    L->len = 0;
}

elemType get(seqList * L,int i)
{
    if ((i<1)||(i>L->len))
    {
        exit(-1);
    }
    return L->elem[i];
}

int find(seqList *L,elemType e)
{
    int i;
    L->elem[0] = e;
    for (i=L->len;i>=0;i--)
    {
        if (L->elem[i]==e)
        {
            break;
        }
    }
    return i;
}

int insert(seqList *L,int i, elemType e)
{
    if ((i<1)||(i>L->len+1)||L->len==L->maxSize-1)
    {
        return 0;
    }
    for (int k = L->len+1; k > i; k--)
    {
        L->elem[k] = L->elem[k-1];
    }
    L->elem[i] = e;
    L->len++;
    return 1;
}

int Remove(seqList *L,int i,elemType *e)
{
    if ((i<1)||(i>L->len))
    {
        return 0;
    }
    *e = L->elem[i];

    for (int k = i; k < L->len; k++)
    {
        L->elem[k] = L->elem[k+1];
    }
    //(L->len)--;❌
    L->len--;
    /*原因见L->len.md*/
    return 1;
}
