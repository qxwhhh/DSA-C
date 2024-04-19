//第一次手敲销毁数据，定义两个指针来 free 图中的EdgeNode还是十分巧妙的
//感觉应该是要根据创建来写销毁代码的，因为在上述创建中也只申请了EdgeNode，所以此处对应销毁
void DestroyGraph(ALGraph * G)
{
    EdgeNode * p = NULL;
    EdgeNode * q = NULL;
    for (int i = 0; i < G->vertexNum; i++)
    {
        p = q = G->adjlist[i].first;
        while (p!=NULL)
        {
            p = p->next;
            free(q);
            q = p;
        }   
    }
}
