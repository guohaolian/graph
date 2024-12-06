#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#define N 100 // 最大顶点数

int color[N] = {0};    // 各顶点颜色数组
int graph[N][N] = {0}; // 无向图的邻接矩阵
int n, m;              // n为顶点数，m为着色数
int counts = 0;        // 可行方案总数

bool check(int step)
{
    for (int i = 0; i < n; i++)
    {
        // 如果两顶点连通且着色相同，着色不合理
        if (graph[step][i] == 1 && color[step] == color[i])
        {
            return false;
        }
    }
    return true;
}

void graphColor(int step)
{
    if (step == n)
    { // 存在可行的完整着色方案，打印方案
        for (int i = 0; i < n; i++)
        {
            printf("%d ", color[i]);
        }
        printf("\n");
        counts++;
    }
    else
    {
        for (int k = 1; k <= m; k++)
        {
            color[step] = k; // step顶点尝试各种颜色着色
            if (check(step))
            { // 若该颜色着色可行，进行下一个顶点的着色
                graphColor(step + 1);
            }
            // 不可行，回溯
            color[step] = 0;
        }
    }
}

int main()
{
    /* 输入：
        5 4
        0 1 1 1 0
        1 0 1 1 1
        1 1 0 1 0
        1 1 1 0 1
        0 1 0 1 0
    */

    SetConsoleOutputCP(65001); // 解决输出中文乱码问题
    printf("请分别输入顶点数n和着色数m：\n");
    scanf("%d %d", &n, &m);
    printf("请输入邻接矩阵：\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    graphColor(0);
    if (counts != 0)
        printf("可行方案数为：%d\n", counts);
    else
        printf("No\n");

    system("pause");
    return 0;
}
