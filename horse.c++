#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>	 // 包含标准库头文件
#include <windows.h> // 包含Windows API头文件

#define ROW 8
#define COL 8

bool only = true;		   // only为true表示只输出一种结果，反之多种
bool f = false;			   // 判断是否已经找到答案
int map[ROW + 5][COL + 5]; // 棋盘
int vis[ROW + 5][COL + 5]; // 标记该位置是否已经落子

int dir[8][2] = {{-1, 2}, {-1, -2}, {1, -2}, {1, 2}, {-2, 1}, {2, -1}, {-2, -1}, {2, 1}};

bool in(int x, int y) // 在棋盘里，且该位置没棋子
{
	return x >= 0 && x < ROW && y >= 0 && y < COL && !vis[x][y];
}
// 需要注意的是，这里的in函数里面整合了 !vis[x][y]

void printMap() // 打印棋盘
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			printf("%4d", map[i][j]);
		}
		printf("\n\n");
	}
	printf("\n\n");
}

void printArray(int *num, int size, const char *str) // 打印数组，用于调试
{
	printf("%5s:", str);
	for (int i = 0; i < size; i++)
	{
		printf("%4d", num[i]);
	}
	printf("\n\n");
}

// next数组的初始化值都是0
void getNext(int x, int y, int *next) // 获得后续点位数量的数组
{
	for (int i = 0; i < 8; i++)
	{
		int tx = x + dir[i][0];
		int ty = y + dir[i][1];
		if (in(tx, ty))
		{
			for (int j = 0; j < 8; j++)
			{
				int ttx = tx + dir[j][0];
				int tty = ty + dir[j][1];
				if (in(ttx, tty))
				{
					next[i]++; // 统计每个移动方向后续点位个数
				}
			}
		}
	}
}

// 获得next数组从小到大的，但是值是次序
// 比如：next[8] = {3,2,5,1,1,0,1,0};
// 那么seq数组就是 {5,7,3,4,6,1,0,2}
// 第一个是5，是因为next[5] = 0,第二个是7，是因为next[7] = 0;以此类推
void getSeq(int *next, int *seq)
{
	int n[8];
	for (int i = 0; i < 8; i++)
		n[i] = next[i];
	// 防止原本的next数组被排序，复制个next数组来排序就可

	// 冒泡排序，不过捆绑了Seq数组，当然，这里也可以用结构体实现
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7 - i; j++)
		{
			if (n[j] > n[j + 1])
			{
				int t = n[j];
				n[j] = n[j + 1];
				n[j + 1] = t;
				// n数组交换时，让seq数组进行同样的交换
				t = seq[j];
				seq[j] = seq[j + 1];
				seq[j + 1] = t;
			}
		}
	}
}

void dfs(int x, int y, int step)
{
	if (f && only)
	{
		return;
	}

	map[x][y] = step;

	if (step == 64)
	{
		// 输出
		printMap();
		f = true;
		return;
	}

	vis[x][y] = 1; // 标记

	// 这里进行深度优先搜索，采取贪心策略进行减枝优化
	int next[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	getNext(x, y, next);
	int seq[8] = {0, 1, 2, 3, 4, 5, 6, 7};
	getSeq(next, seq);

	// 原本dfs是随机的找的，现在，通过贪心得到了一个seq数组，就是搜索顺序的数组

	// 开始搜索
	for (int i = 0; i < 8; i++)
	{
		int tx = x + dir[seq[i]][0];
		int ty = y + dir[seq[i]][1];
		if (in(tx, ty))
			dfs(tx, ty, step + 1);
	}

	// 回溯
	vis[x][y] = 0;
	map[x][y] = 0;
}

void run()
{
	int x, y;
	printf("请输入起始坐标：");
	scanf("%d,%d", &x, &y);
	if (!in(x, y))
	{
		printf("\n\n坐标输入错误！！！\n\n");
		return;
	}
	printf("\n");
	dfs(x, y, 1);
}

int main()
{
	SetConsoleOutputCP(65001); // 解决输出中文乱码问题
	run();
	system("pause");
	return 0;
}
