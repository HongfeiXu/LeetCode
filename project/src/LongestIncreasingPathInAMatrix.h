#pragma once

/*

329. Longest Increasing Path in a Matrix

Given an integer matrix, find the length of the longest increasing path.

From each cell, you can either move to four directions: left, right, up or down. 
You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).

Example 1:

nums = [
  [9,9,4],
  [6,6,8],
  [2,1,1]
]
Return 4
The longest increasing path is [1, 2, 6, 9].

Example 2:

nums = [
  [3,4,5],
  [3,2,6],
  [2,2,1]
]
Return 4
The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.

Approach MY:

beat 71.61 %

�����DP�����������������ʹ�ø�������¼�Ѿ������ʹ��Ľڵ���Ϣ���Ӹý����ʼ����ĵ���·�����ȣ�


һ���ڵ�������·������ = max{ �ɵ���ģ����������ڽڵ�������·������ } + 1

*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	vector<pair<int, int>> dirs = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

	int M, N;

	int longestIncreasingPath(vector<vector<int>>& matrix)
	{
		if (matrix.empty())
			return 0;
		M = matrix.size();
		N = matrix[0].size();
		vector<vector<int>> table(M, vector<int>(N, 0));			// �ӵ�ǰ�ڵ��������ĵ���·�����ȣ���·������Ϊ0��ʾ��ǰ�ڵ�δ������
																	//vector<vector<bool>> visited(M, vector<bool>(N, false));	// ��ǰ�ڵ��Ƿ��Ѿ�������

		int result = 0;
		for (int i = 0; i < M; ++i)
			for (int j = 0; j < N; ++j)
				result = max(result, dfs(i, j, matrix, table));
		return result;
	}

	bool check(int x, int y)
	{
		return(x >= 0 && x < M && y >= 0 && y < N);
	}

	// ���������������� x��y λ�ó����������·������
	int dfs(int x, int y, vector<vector<int>>& matrix, vector<vector<int>>& table)
	{
		if (table[x][y] != 0)		// �����ǰ�ڵ��Լ������ʹ�����ֱ�ӷ���
			return table[x][y];
		int longest = 0;
		for (auto dir : dirs)		// ��ǰ�ڵ�δ�����ʣ���ȱ����ĸ�����
		{
			int newX = x + dir.first;
			int newY = y + dir.second;
			if (!check(newX, newY))
				continue;
			int curr = 0;
			if (matrix[x][y] < matrix[newX][newY])	// ����λ�õĽڵ����ԭ���Ľڵ㣬����� curr
				curr = dfs(newX, newY, matrix, table);
			longest = max(longest, curr);
		}
		table[x][y] = longest + 1;	// ���� table[x][y]
		return table[x][y];
	}
};