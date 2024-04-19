#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct EdgeNode {
    int adjvex; // 邻接点的索引
    struct EdgeNode *next; // 指向下一个边表节点的指针
} EdgeNode;

typedef struct ALGraph {
    int vertexNum; // 图的顶点数
    int edgeNum; // 图的边数
    EdgeNode *adjlist[100]; // 邻接表数组
} ALGraph;

// 假设DataType是int类型，根据实际情况可能需要修改
typedef int DataType;

void CreatGraph(ALGraph *G, DataType a[], int n, int e) {
    int i, j, k;
    EdgeNode *s = NULL;
    if (!G) return; // 检查传入的指针是否为NULL

    G->vertexNum = n;
    G->edgeNum = e;
    for (i = 0; i < n; i++) {
        G->adjlist[i].vertex = a[i]; // 存储顶点信息
        G->adjlist[i].first = NULL; // 初始化边表的头指针
    }

    for (k = 0; k < e; k++) {
        if (scanf("%d%d", &i, &j) != 2) { // 检查scanf是否成功读取了两个值
            printf("Invalid input!\n");
            return;
        }
        // 如果顶点编号从1开始，需要减1
        i--; j--;

        if (i < 0 || i >= n || j < 0 || j >= n) {
            printf("Vertex index out of bounds!\n");
            continue;
        }

        s = (EdgeNode *)malloc(sizeof(EdgeNode));
        if (!s) { // 检查内存是否成功分配
            printf("Memory allocation failed!\n");
            return;
        }
        s->adjvex = j;
        s->next = G->adjlist[i].first; // 插入到第i个边表的表头
        G->adjlist[i].first = s;
    }
}

// 注意：这个函数没有返回类型，因为ALGraph结构体是按引用传递的（指针）
