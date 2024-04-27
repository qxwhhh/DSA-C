typedef struct
{
  int source;    //the node with a shortest distance between U
  edgetype dist; //the shortest distance between U
  int flag;      //whether the Node is in U
} primNode;

void Prim(Graph *g)
{
  primNode *PrimList;
  int i,j;
  int cnt;       //record node in U
  int min;       //choose the node with the shortest distance now
  int source,dist;

  prim = (primNode*)malloc(sizeof(PrimNode)*g->verts);
                 //verts are the real numbers of the Graph's vert
  for(i = 0;i<g->verts;i++)
  {
    primList[i].source = -1;
    primList[i].dist = MAXNUM;
                 //means the max distance
    primList[i].flag = 0;
  }

  //from the i=0 vert
  min = 0;
  cnt = 1;
  primList[0].dist = 0;
  primList[0].flag = 1;

  while(cnt<g->verts)
  {
    //judge whether to refresh the shortest distance between 2 verts 
    //by the edges from min vert
    for(j = 0;j<g->verts;j++)
    {
      if(g->edgeMatrix[min][j]==0)
        continue;
      if(primList[j].flag = 1)
        continue;
      if(g->edgeMatrix[min][j]<primList[j].dist)
      {
        primList[j].dist = g->edgeMatrix[min][j];
        primList[j].source = min;
      }
    }

    // find the node with the shortest distance in U
    min = -1;
    dist = MAXNUM;
    for(i = 0;i<g->verts;i++)
    {
      if(primList[i].flag == 0 && primList[i].dist < dist)
      {
        min = i;
        dist = primList[i].dist;
      }
    }

    // add the node to U
    primList[min].flag = 1;
    cnt++;
  }

  // print the minimum spanning tree
  for(i = 1;i<g->verts;i++)
  {
    printf("Edge (%d, %d) with weight %d\n", primList[i].source, i, primList[i].dist);
  }

  free(primList);
}







/*
Here's a brief explanation of the algorithm:
以下是该算法的简要说明：

Initialize an array primList to store the shortest distance and source node for each vertex.
初始化一个数组 primList 来存储每个顶点的最短距离和源节点。
Set the distance of the starting vertex (0) to 0 and mark it as visited.
将起始顶点 (0) 的距离设置为 0 并将其标记为已访问。
While there are still vertices to visit, find the vertex with the shortest distance in U (the set of visited vertices) and mark it as visited.
当仍有顶点要访问时，在 U （已访问顶点集合）中找到距离最短的顶点并将其标记为已访问。
Update the shortest distances of the vertices adjacent to the newly visited vertex.
更新与新访问的顶点相邻的顶点的最短距离。
Repeat steps 3-4 until all vertices have been visited.
重复步骤3-4，直到访问完所有顶点。
Print the minimum spanning tree by traversing the primList array.
通过遍历 primList 数组来打印最小生成树。
Note that this implementation assumes that the graph is represented as an adjacency matrix g->edgeMatrix, where g->edgeMatrix[i][j] represents the weight of the edge between vertices i and j. If the graph is represented as an adjacency list, the implementation would need to be modified accordingly.
请注意，此实现假设图表示为邻接矩阵 g->edgeMatrix ，其中 g->edgeMatrix[i][j] 表示顶点 i 和 j
*/
