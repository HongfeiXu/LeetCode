#pragma once

/*

72. Edit Distance

Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. 
(each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character

#################################################################
Approach[TLE]:
Divide and Conquer
string a: a[1...m], string b: b[1...n]
d[i][j] 表示 a[1...i] 到 b[1...j] 的编辑距离。则有：
递归规律：
If a[i] == b[j], then d[i][j] = d[i-1][j-1]
Else, d[i][j] 取下面三项的最小值（例：求 fxy -> fab 的 ED）
	1. d[i-1][j] + 1 删除a[i]：fx->fab 的 ED + 1
	2. d[i][j-1] + 1 在末尾插入 b[j]：fxyb->fab 的 ED + 1 = fxy->fa 的 ED + 1
	3. d[i-1][j-1]   将 a[i] 替换为 b[j]：fxb->fab 的 ED + 1 = fx->fa 的 ED + 1
递归边界：
d[i][0] = i，b串为空，则需要将a[1...i]串全部删除，编辑距离为i；
d[0][j] = j，a串为空，需要a中插入b[1...j]，编辑距离为j。

#################################################################
Approach v2[AC]:
Dynamic Programming

Time: O(m*n)
Space: O(m*n) 

#################################################################
Approach v3[AC]:
Space 可以优化到 O(2*min(m,n)) Solution_v3
我们知道计算 d[i] 这一行时，只需要知道 d[i-1] 这一行的值。因此只需要两行即可。

#################################################################
Approach v4[AC]:
进一步的，其实我们只要一行就可以了，每次计算的时候我们需要3个值，
其中上边和左边的值可以直接得到，左上角的值需要临时变量（left_up）来记录。
每次更新第 i 行的 d[j] 之前需要先备份第 i-1 行的 d[j] 的值到 left_up 中。

Space可以优化到 O(min(m,n)) Solution_v4


*/

#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
	int minDistance(string word1, string word2)
	{
		if (word1.size() == 0)
			return word2.size();
		if (word2.size() == 0)
			return word1.size();
		if (word1.back() == word2.back())
		{
			word1.pop_back(), word2.pop_back();
			return minDistance(word1, word2);
		}
		else
		{
			return 1 + minOfThree(
				minDistance(string(word1, 0, word1.length() - 1), word2),
				minDistance(word1, string(word2, 0, word2.length() - 1)),
				minDistance(string(word1, 0, word1.length() - 1), string(word2, 0, word2.length() - 1))
				);
		}
	}

	int minOfThree(int a, int b, int c)
	{
		return min(min(a, b), c);
	}
};

class Solution_v2 {
public:
	int minDistance(string word1, string word2)
	{
		int m = word1.size(), n = word2.size();
		vector<vector<int>> d(m + 1, vector<int>(n + 1, 0));
		for (int i = 0; i <= m; ++i)
		{
			for (int j = 0; j <= n; ++j)
			{
				if (i == 0)
					d[0][j] = j;
				else if (j == 0)
					d[i][0] = i;
				else
				{
					if (word1[i-1] == word2[j-1])
						d[i][j] = d[i - 1][j - 1];
					else
						d[i][j] = minOfThree(d[i - 1][j], d[i][j - 1], d[i - 1][j - 1]) + 1;
				}

			}
		}
		return d[m][n];
	}

	int minOfThree(int a, int b, int c)
	{
		return min(min(a, b), c);
	}
};

class Solution_v3 {
public:
	int minDistance(string word1, string word2)
	{
		// 让 word1.size() >= word2.size()
		if (word1.size() < word2.size())
			swap(word1, word2);
		int m = word1.size(), n = word2.size();
		vector<vector<int>> d(2, vector<int>(n + 1, 0));
		for (int i = 0; i <= m; ++i)
		{
			for (int j = 0; j <= n; ++j)
			{
				if (i == 0)
					d[0][j] = j;
				else if (j == 0)
					d[i % 2][0] = i;
				else
				{
					if (word1[i - 1] == word2[j - 1])
						d[i % 2][j] = d[(i - 1) % 2][j - 1];
					else
						d[i % 2][j] = minOfThree(d[(i - 1) % 2][j], d[i % 2][j - 1], d[(i - 1) % 2][j - 1]) + 1;
				}

			}
		}
		return d[m % 2][n];
	}

	int minOfThree(int a, int b, int c)
	{
		return min(min(a, b), c);
	}
};

class Solution_v4 {
public:
	int minDistance(string word1, string word2)
	{
		// 让 word1.size() >= word2.size()
		if (word1.size() < word2.size())
			swap(word1, word2);
		int m = word1.size(), n = word2.size();
		vector<int> d(n+1, 0);
		int left_up = 0;			// 保存当前表中元素左上角相邻元素的值
		for (int i = 0; i <= m; ++i)
		{
			for (int j = 0; j <= n; ++j)
			{
				if (i == 0)
					d[j] = j;
				else if (j == 0)
				{
					left_up = d[j];	
					d[j] = i;
				}
				else
				{
					if (word1[i - 1] == word2[j - 1])
					{
						swap(left_up, d[j]);
					}
					else
					{
						int temp = d[j];
						d[j] = minOfThree(d[j - 1], d[j], left_up) + 1;
						left_up = temp;
					}
				}

			}
		}
		return d[n];
	}

	int minOfThree(int a, int b, int c)
	{
		return min(min(a, b), c);
	}
};