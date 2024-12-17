#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // 用于设置控制台输出编码

#define MAX_VERTICES 10 // 假设图中最多有10个节点

// 定义图的结构，图采用邻接矩阵表示
typedef struct
{
    int matrix[MAX_VERTICES][MAX_VERTICES]; // 存储图的邻接矩阵
    int num_vertices;                       // 节点数
} Graph;

// 初始化图，设置所有边的权重为0（表示不存在边）
void init_graph(Graph *graph, int num_vertices)
{
    graph->num_vertices = num_vertices;
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < num_vertices; j++)
        {
            graph->matrix[i][j] = 0;
        }
    }
}

// 添加无向边
void add_edge(Graph *graph, int u, int v)
{
    graph->matrix[u][v] = 1; // 无向边，设置两个方向
    graph->matrix[v][u] = 1;
}

// 深度优先搜索（DFS）
void dfs(Graph *graph, int start, int visited[])
{
    visited[start] = 1;
    printf("%d ", start);

    for (int v = 0; v < graph->num_vertices; v++)
    {
        if (graph->matrix[start][v] == 1 && !visited[v])
        {
            dfs(graph, v, visited);
        }
    }
}

// 判断图是否连通
int is_connected(Graph *graph)
{
    int visited[MAX_VERTICES] = {0};

    // 从第一个节点开始DFS
    dfs(graph, 0, visited);

    // 检查是否所有节点都被访问过
    for (int i = 0; i < graph->num_vertices; i++)
    {
        if (visited[i] == 0)
        {
            return 0; // 如果有节点没有被访问过，说明图不连通
        }
    }

    return 1; // 图连通
}

int main()
{
    SetConsoleOutputCP(65001); // 解决输出中文乱码问题
    Graph graph;
    int num_vertices = 6; // 假设图有6个节点

    init_graph(&graph, num_vertices);

    // 添加无向边
    add_edge(&graph, 0, 1);
    add_edge(&graph, 0, 2);
    add_edge(&graph, 1, 3);
    add_edge(&graph, 2, 3);
    add_edge(&graph, 3, 4);
    add_edge(&graph, 4, 5);

    // 显式定义一个访问标记数组
    int visited[MAX_VERTICES] = {0};

    printf("DFS Traversal: ");
    dfs(&graph, 0, visited); // 传递访问标记数组
    printf("\n");

    if (is_connected(&graph))
    {
        printf("The graph is connected.\n");
    }
    else
    {
        printf("The graph is not connected.\n");
    }
    system("pause");

    return 0;
}