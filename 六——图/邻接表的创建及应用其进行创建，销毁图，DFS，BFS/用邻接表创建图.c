//adjacency list = edgeNode + vertexNode array

//建立一个含有n个顶点，e条边的图
void CreatGraph(ALGraph * G,DataType a[],int n,int e)
{
    int i,j,k;
    EdgeNode * s = NULL;
    G->vertexNum = n;
    G->edgeNum = e;
    for ( i = 0; i < n; i++)
    {
        G->adjlist[i].vertex = a[i];//存储顶点char
        G->adjlist[i].first = NULL;//初始化边表的头指针
    }
    for ( k = 0; k < e; k++)
    {
        scanf("%d%d",&i,&j);//输入边所依附的顶点信息
        s = (EdgeNode*)malloc(sizeof(EdgeNode));
        s->adjvex = j;
        //！！!将s插入到第i个边表的表头！！！
        s->next = G->adjlist[i].first;
        G->adjlist[i].first = s;
    }
    
}
/*
    输入顶点的info数组，顶点个数，边的个数  （maybe return G）
    1.存储图的顶点个数和边的个数
    2.将顶点信息存储在顶点表中，并初始化各自的头指针
    3.依次（想要什么顺序就按什么顺序输入？）输入边的信息并将其存储在边表中
        3.1输入边所依附的两个顶点的信息
        3.2生成边表节点s，其邻接点编号为j
        3.3将节点s插入到第i个边表的表头
*/
