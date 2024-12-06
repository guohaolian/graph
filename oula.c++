#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // 包含Windows API头文件

#define maxn 500
int a[maxn][maxn] = {0}, n;

void input(void);   // 输入邻接矩阵
int Is_Even(void);  // 判断是否每个点度数都为偶数
int Warshall(void); // 判断是否连通

int main()
{
    /*
    0 1 0 0 0 1
    1 0 1 0 0 0
    0 1 0 1 0 0
    0 0 1 0 1 0
    0 0 0 1 0 1
    1 0 0 0 1 0
     */
    SetConsoleOutputCP(65001); // 解决输出中文乱码问题
    input();
    if (Is_Even() && Warshall())
        printf("Yes\n");
    else
        printf("No\n");
    system("pause");
    return 0;
}

void input(void)
{
    int i, j;
    printf("请输入顶点个数：");
    scanf("%d", &n);
    printf("请输入图的邻接矩阵：\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
}
int Is_Even(void)
{
    int count, i, j;
    for (i = 0; i < n; i++)
    {
        count = 0;
        for (j = 0; j < n; j++)
        {
            count += a[i][j];
        }
        if (count % 2)
            return 0;
    }
    return 1;
}

int Warshall(void)
{
    int i, j, k;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            if (a[j][i] == 1)
            {
                for (k = 0; k < n; k++)
                    a[j][k] = a[j][k] + a[i][k] - a[j][k] * a[i][k];
            }
        }
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (a[i][j] == 0)
                return 0;
    return 1;
}
