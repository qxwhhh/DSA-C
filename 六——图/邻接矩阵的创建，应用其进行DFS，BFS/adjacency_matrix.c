#include <stdio.h>
#include <stdlib.h>

#define MaxSize 10
typedef char DataType;
//邻接矩阵的存储结构定义
typedef struct
{
    DataType vertex[MaxSize];
    int edge[MaxSize][MaxSize];
    int vertexNum,edgeNum;        
}MGraph;

/*
创建无向图的邻接矩阵,含有n个顶点，e条边。
将顶点信息存储在一位数组vertex中，初始化邻接矩阵edge
*/
void CreateGraph(MGraph * G,DataType a[],int n,int e)
{
    G->vertexNum = n;
    G->edgeNum = e;
     
    for (int i = 0; i < n; i++)
    {
        G->vertex[i] = a[i];
        for (int j = 0; j < n; j++)
        {
            G->edge[i][j] = 0;
        }
        
    }

    for (int k = 0; k < e; k++)
    {
        int i,j;
        //输入边依附的顶点编号
        scanf("%d%d",&i,&j);
        //将其改为1，标志有边
        G->edge[i][j] = 1;
        G->edge[j][i] = 1;
    }
}

//由于它是静态存储分布，因此不需要destroy

/*深度优先遍历
    需要输入一个顶点的编号v，逐一访问（输出其Typedata中存储的数据）
    1. 访问顶点v，修改标志代表它已经被访问
    2. w = v的第一个连接点(！实际上是通过遍历来找和它连接的点！)
    3. while（w存在）
        3.1 判断w有没有被访问过,否：从w继续递归
                             是：w = v的下一个连接点
*/
//定义全局变量数组visited[MaxSize],并且初始化为0
int visited[MaxSize]={0};
void DFSTraverse(MGraph * G,int v)
{
    printf("%c ",G->vertex[v]);
    visited[v] = 1;

    for (int j = 0; j < G->vertexNum; j++)
    {
        if (G->edge[v][j] == 1 && visited[j] == 0)
        {
            DFSTraverse(G,j);
        }
        
    }
    
}

/*广度优先遍历
    1.需要输入一个顶点的编号v，逐一访问（输出其Typedata中存储的数据）
    2.定义一个数组和两个标志rear，front来表示队列
    3.将v入队
    4.逐一遍历edge二维数组，找到与v连接且没有被访问过的节点（当然此时只要与v连接都是）
        找到一个rear就+1并将找到的节点入队
        全部找到后，使v出队
    5.重复上述过程，无须递归：只需用while(front != rear)
*/
void BFTraverse(MGraph * G,int v)
{
    int i,j,Q[MaxSize];
    int front = -1;
    int rear = -1;
    printf("%c ",G->vertex[v]);
    visited[v] = 1;
    Q[++rear] = v;

    while (front != rear)
    {
        i = Q[++front];//将队头元素送出队列
        for ( j = 0; j < G->vertexNum; j++)
        {
            if (G->edge[i][j] == 1 && visited[j] == 0)
            {
                printf("%c ",G->vertex[j]);
                visited[j] = 1;
                Q[++rear] = j;
            }
            
        }
        

    }
    
}


//drive code
int main()
{
    int i;
    char ch[] = {'A','B','C','D','E'};
    MGraph MG;
    CreateGraph(&MG,ch,5,6);
    for ( i = 0; i < MaxSize; i++)
    {
        visited[i] = 0; 
    }
    printf("深度优先遍历顺序是：");
    DFSTraverse(&MG,0);
    for ( i = 0; i < MaxSize; i++)
    {
        visited[i] = 0; 
    }
    printf("广度优先遍历顺序是：");
    BFTraverse(&MG,0);
    return 0;
}
/*
example:
0
2
0
4
1
0
1
4
3
2
2
1
深度优先遍历顺序是：A B C D E 广度优先遍历顺序是：A B C E D
*/
