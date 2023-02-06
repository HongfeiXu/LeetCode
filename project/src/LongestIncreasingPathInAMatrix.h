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

结合了DP的深度优先搜索，并使用辅助表格记录已经被访问过的节点信息（从该结点起始的最长的递增路径长度）


一个节点的最长递增路径长度 = max{ 可到达的（递增）相邻节点的最长递增路径长度 } + 1

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
		vector<vector<int>> table(M, vector<int>(N, 0));			// 从当前节点出发，最长的递增路径长度，若路径长度为0表示当前节点未被访问
																	//vector<vector<bool>> visited(M, vector<bool>(N, false));	// 当前节点是否已经被访问

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

	// 深度优先搜索，求从 x，y 位置出发的最长递增路径长度
	int dfs(int x, int y, vector<vector<int>>& matrix, vector<vector<int>>& table)
	{
		if (table[x][y] != 0)		// 如果当前节点以及被访问过，则直接返回
			return table[x][y];
		int longest = 0;
		for (auto dir : dirs)		// 当前节点未被访问，深度遍历四个方向
		{
			int newX = x + dir.first;
			int newY = y + dir.second;
			if (!check(newX, newY))
				continue;
			int curr = 0;
			if (matrix[x][y] < matrix[newX][newY])	// 若新位置的节点大于原来的节点，则更新 curr
				curr = dfs(newX, newY, matrix, table);
			longest = max(longest, curr);
		}
		table[x][y] = longest + 1;	// 更新 table[x][y]
		return table[x][y];
	}
};