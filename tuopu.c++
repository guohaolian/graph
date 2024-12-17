#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // 包含Windows API头文件

#define MAX_VERTICES 10 // 假设图中最多有10个节点

// 定义图的结构，图采用邻接矩阵表示
typedef struct
{
    int matrix[MAX_VERTICES][MAX_VERTICES]; // 存储图的邻接矩阵
    int num_vertices;                       // 节点数
} Graph;

// 初始化图，设置所有边的权重为0（表示不存在边），对角线设置为0
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

// 添加有向边，weight表示边的权重
void add_edge(Graph *graph, int u, int v)
{
    graph->matrix[u][v] = 1; // 只有边的存在，不考虑权重
}

// Kahn算法：通过入度数组进行拓扑排序
void topological_sort(Graph *graph)
{
    int num_vertices = graph->num_vertices;
    int in_degree[MAX_VERTICES] = {0}; // 入度数组，记录每个节点的入度
    int queue[MAX_VERTICES], front = 0, rear = 0;
    int result[MAX_VERTICES];
    int result_index = 0;

    // 计算每个节点的入度
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < num_vertices; j++)
        {
            if (graph->matrix[j][i] == 1)
            {
                in_degree[i]++;
            }
        }
    }

    // 将所有入度为0的节点加入队列
    for (int i = 0; i < num_vertices; i++)
    {
        if (in_degree[i] == 0)
        {
            queue[rear++] = i;
        }
    }

    // 执行拓扑排序
    while (front < rear)
    {
        int u = queue[front++];
        result[result_index++] = u;

        // 遍历所有邻接节点，减少入度
        for (int v = 0; v < num_vertices; v++)
        {
            if (graph->matrix[u][v] == 1)
            { // 如果有边 u -> v
                in_degree[v]--;
                if (in_degree[v] == 0)
                {
                    queue[rear++] = v; // 入度为0的节点加入队列
                }
            }
        }
    }

    // 检查是否存在环
    if (result_index != num_vertices)
    {
        printf("The graph contains a cycle, topological sorting is not possible.\n");
        return;
    }

    // 输出拓扑排序结果
    printf("Topological Sort: ");
    for (int i = 0; i < num_vertices; i++)
    {
        printf("%d ", result[i]);
    }
    printf("\n");
}

int main()
{
    SetConsoleOutputCP(65001); // 解决输出中文乱码问题
    Graph graph;
    int num_vertices = 6; // 假设图有6个节点

    init_graph(&graph, num_vertices);

    // 添加有向边
    add_edge(&graph, 0, 1);
    add_edge(&graph, 0, 2);
    add_edge(&graph, 1, 3);
    add_edge(&graph, 2, 3);
    add_edge(&graph, 3, 4);
    add_edge(&graph, 4, 5);

    // 执行拓扑排序
    topological_sort(&graph);
    system("pause");

    return 0;
}