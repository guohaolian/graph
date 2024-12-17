#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <windows.h> // 包含Windows API头文件

#define INF INT_MAX
#define MAX_VERTICES 10 // 假设图中最多有10个节点

// 定义图的结构，图采用邻接矩阵表示
typedef struct
{
    int matrix[MAX_VERTICES][MAX_VERTICES]; // 存储图的邻接矩阵
    int num_vertices;                       // 节点数
} Graph;

// 初始化图，设置所有边的权重为INF（表示不存在边），对角线设置为0
void init_graph(Graph *graph, int num_vertices)
{
    graph->num_vertices = num_vertices;
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < num_vertices; j++)
        {
            if (i == j)
            {
                graph->matrix[i][j] = 0;
            }
            else
            {
                graph->matrix[i][j] = INF;
            }
        }
    }
}

// 添加有向边，weight表示边的权重
void add_edge(Graph *graph, int u, int v, int weight)
{
    graph->matrix[u][v] = weight;
}

// Dijkstra算法，返回从源节点start到各个节点的最短距离
void dijkstra(Graph *graph, int start)
{
    int dist[MAX_VERTICES];          // 存储最短距离
    int visited[MAX_VERTICES] = {0}; // 标记节点是否已经访问
    int num_vertices = graph->num_vertices;

    // 初始化dist数组，源点的距离为0，其他节点的距离为INF
    for (int i = 0; i < num_vertices; i++)
    {
        dist[i] = INF;
    }
    dist[start] = 0;

    // Dijkstra算法的主体
    for (int count = 0; count < num_vertices - 1; count++)
    {
        // 选择一个距离源点最近且未被访问的节点
        int min_dist = INF;
        int u = -1;
        for (int i = 0; i < num_vertices; i++)
        {
            if (!visited[i] && dist[i] < min_dist)
            {
                min_dist = dist[i];
                u = i;
            }
        }

        // 标记该节点为已访问
        visited[u] = 1;

        // 更新相邻节点的最短距离
        for (int v = 0; v < num_vertices; v++)
        {
            if (!visited[v] && graph->matrix[u][v] != INF)
            {
                if (dist[u] + graph->matrix[u][v] < dist[v])
                {
                    dist[v] = dist[u] + graph->matrix[u][v];
                }
            }
        }
    }

    // 输出最短路径结果
    printf("Shortest distances from vertex %d:\n", start);
    for (int i = 0; i < num_vertices; i++)
    {
        if (dist[i] == INF)
        {
            printf("Vertex %d is unreachable\n", i);
        }
        else
        {
            printf("Distance to vertex %d: %d\n", i, dist[i]);
        }
    }
}

int main()
{
    SetConsoleOutputCP(65001); // 解决输出中文乱码问题
    Graph graph;
    int num_vertices = 5; // 假设图有5个节点

    init_graph(&graph, num_vertices);

    // 添加边：图的顶点是从0开始编号
    add_edge(&graph, 0, 1, 10);
    add_edge(&graph, 0, 4, 5);
    add_edge(&graph, 1, 2, 1);
    add_edge(&graph, 2, 3, 4);
    add_edge(&graph, 3, 2, 6);
    add_edge(&graph, 4, 1, 3);
    add_edge(&graph, 4, 2, 9);
    add_edge(&graph, 4, 3, 2);

    // 执行Dijkstra算法，源节点为0
    dijkstra(&graph, 0);

    system("pause");
    return 0;
}