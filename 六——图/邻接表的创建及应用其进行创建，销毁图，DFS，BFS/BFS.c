//现在打算根据前天写的邻接矩阵BFS写个邻接表的BFS，希望可以写出来
//肯定可以写出来，因为我会先看一遍书上的代码(after 5 mins ,that is a dream)
//写完自己的代码后再抄一遍书上的代码，又发现了一个自己所未熟悉的地方
//边表节点（EdgeNode）里的adjvex存放的是邻接点的v，因此可以直接用
  //但是我在刚开始时用了p->next->adjvex，这样做就会直接跳过了v的第一个邻接表，
void BFTraverse_1(ALGraph * G,int v)
{
    int Q[MaxSize];
    int front = 0;
    int rear = -1;
    EdgeNode * p;

    Q[front] = v;
    p = G->adjlist[v].first;
    printf("%c ",G->adjlist[v].vertex);
    visited[v] = 1;
    while (front != rear)
    {
        front++;//将队头元素送出队列
        while (p->next != NULL)
        {
            if (visited[p->next->adjvex] == 0)
            {
                Q[++rear] = p->next->adjvex;
                visited[p->next->adjvex] = 1;
            }
            p = p->next;
        }
        
    }
    
}

//book code
void BFTraverse(ALGraph * G,int v)
{
    int Q[MaxSize];
    int front = 0;
    int rear = -1;
    EdgeNode * p = NULL;
    int j;

    while (front != rear)
    {
        v = Q[++front];
        p = G->adjlist[v].first;
        while (p != NULL)
        {
            j = p->adjvex;
            if (visited[j] == 0)
            {
                printf("%c ",G->adjlist[j].vertex);
                visited[j] = 1;
                Q[++rear] = j;
            }
            p = p->next;
        }   
    }
}
