#include<stdio.h>
#include<stdlib.h>

#define MaxSize 10
//define adjacency list = edgeNode + vertexNode array
typedef char DataType;
typedef struct EdgeNode
{
    int adjvex;
    struct EdgeNode* next; 
}EdgeNode;
typedef struct 
{
    DataType vertex;
    EdgeNode *first;
}VertexNode;
typedef struct 
{
    VertexNode adjlist[MaxSize];
    int vertexNum,edgeNum;
}ALGraph;



