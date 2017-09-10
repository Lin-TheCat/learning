
// sudoku.cpp: 定义控制台应用程序的入口点。

#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;

int map[9][9];
int arr[9] = { 1,2,3,4,5,6,7,8,9 };
int first;
bool m;

//对数独赋初值
void set()
{
	//定义每个数独局面的二维数组map为全0，除map[0][0]=first外
	for (int i = 0; i < 9; ++i)
		for (int j = 0; j < 9; ++j)
			map[i][j] = 0;
	map[0][0] = first;
}

//求得一个完整数独则输出到文件
/*void fileoutput()
{
for (int i = 0; i < 9; ++i)
{
for (int j = 0; j < 9; ++j)
fout << setw(2) << map[i][j];
fout << endl;
}
fout << endl;
}*/

//求得一个完整数独则输出
void fileoutput()
{
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			char c = map[i][j] + '0';	//将数字转为字符输出 
			putchar(c);
			putchar(' ');
		}
		puts("");
	}
	puts("");
}

//判断准备填入的数值是否符合要求
bool judge(int k, int t)
{
	int row, col;
	row = k / 9;	//取行值
	col = k % 9;	//取列值

	for (int j = 0; j < 9; ++j)	//对同行异列进行判断
		if (map[row][j] == t)
			return false;
	for (int i = 0; i < 9; ++i)	//对同列异行进行判断
		if (map[i][col] == t)
			return false;

	int a, b;
	a = row / 3 * 3;	//确定所在3*3九宫格的首位map[a][b]
	b = col / 3 * 3;

	for (int i = a; i < a + 3; ++i)	//对所在3*3九宫格进行判断
		for (int j = b; j < b + 3; ++j)
			if (map[i][j] == t)
				return false;

	return true;
}

//根据判断情况确定是否填入
void insert(int k)
{
	int row, col;
	row = k / 9;
	col = k % 9;
	if (k == 81)
	{
		m = true;
		return;
	}
	if (map[row][col] != 0)
		insert(k + 1);
	else
	{
		if (k % 18 == 0)
			random_shuffle(&(arr[0]), &(arr[9])); //随机打乱数组arr[]

		for (int i = 0; i<9; ++i)
		{
			if (judge(k, arr[i]))	//允许插入
			{
				map[row][col] = arr[i];
				insert(k + 1);
				if (m)
					return;
				map[row][col] = 0;
			}
		}
	}
}

//检查字符串是否为非零整数
bool check(string str)
{
	int len = str.size();
	int n = 0;

	if (str[0] == 48)
	{
		cout << "Error! Please input a non-zero integer!" << endl;
		return false;
	}
	else
	{
		for (int i = 0; i < len; ++i)
		{
			if (str[i] < 48 || str[i]>57)	//非数字的字符
			{
				cout << "Error! Please input a integer!" << endl;
				return false;
			}
		}
	}
	return true;
}

int main(int argc, char *argv[])
{
	first = (2 + 0) % 9 + 1;	//学号后两位为20，所以 first=3
	string p;

	if (argc == 1 || argc > 3)
	{
		cout << "Error! Please input the correct order!" << endl;
		return 0;
	}
	else
		p = argv[1];

	if (p == "-c")
	{
		if (argv[2] == NULL)
		{
			cout << "Error! Please input a integer!" << endl;
			return 0;
		}
		else
		{
			int num;
			stringstream stream;
			if (check(argv[2]))
			{
				stream << argv[2];	//字符串转为数值
				stream >> num;
				stream.clear();

				freopen("./sudoku.txt", "w", stdout);	//重定向生成文件sudoku.txt
				random_shuffle(&(arr[0]), &(arr[9])); //随机打乱一次数组arr[]

				while (num--)
				{
					set();
					m = false;
					insert(1);	//首位为默认数值first，从第二位开始寻找可插入值
					fileoutput();
				}
			}
		}
	}
	else
	{
		cout << "Error! Please input the correct order! " << endl;
		return 0;
	}
	return 0;
}

