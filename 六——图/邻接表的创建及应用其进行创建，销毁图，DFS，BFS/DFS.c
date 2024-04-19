int visited[MaxSize]={0};
void DFSTraverse(ALGraph * G,int v)
{
    EdgeNode * p = NULL;
    int j;
    printf("%c ",G->adjlist[v].vertex);
    visited[v] = 1;
    
    //工作指针p指向节点v的边表
    p = G->adjlist[v].first;

    while (p != NULL)
    {
        j = p->adjvex;
        if (visited[j] == 0)
        {
            DFSTraverse(G,j);
        }
        p = p->next;
    }//依次搜索顶点v的邻接点j，每搜到一个就判断是否访问过，
     //若访问过就下一个，若未访问过就进入对其DFSTtaverse
     //直到这个顶点的所有邻接点都被访问过
     //有点类似强连通分量了
}
