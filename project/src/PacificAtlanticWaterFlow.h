#pragma once

/*

417. Pacific Atlantic Water Flow

Given an m x n matrix of non-negative integers representing the height of each unit cell in a continent, 
the "Pacific ocean" touches the left and top edges of the matrix and the "Atlantic ocean" touches the right and bottom edges.

Water can only flow in four directions (up, down, left, or right) from a cell to another one with height equal or lower.

Find the list of grid coordinates where water can flow to both the Pacific and Atlantic ocean.

Note:
The order of returned grid coordinates does not matter.
Both m and n are less than 150.
Example:

Given the following 5x5 matrix:

  Pacific ~   ~   ~   ~   ~ 
       ~  1   2   2   3  (5) *
       ~  3   2   3  (4) (4) *
       ~  2   4  (5)  3   1  *
       ~ (6) (7)  1   4   5  *
       ~ (5)  1   1   2   4  *
          *   *   *   *   * Atlantic

Return:

[[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]] (positions with parentheses in above matrix).

Approach MY:
2 times BFS
beat 58%
两次广度优先搜索，搜索可以从左边和上边“逆流到达”的水流，以及可以从右边和下边“逆流到达”的水流。
即，对于太平洋，左边、上边一开始就放入队列中，并标记为已访问（可到达）
对于大西洋，右边、下边也一开始就放入队列中，并标记为已访问（可到达）
思路是，广度优先搜索不一定非要从一个顶点出发，可以从多个顶点出发。

Approach v2:
DFS
beat 35%
Ref: https://leetcode.com/problems/pacific-atlantic-water-flow/discuss/90739/Python-DFS-bests-85.-Tips-for-all-DFS-in-matrix-question.

The DFS solution is straightforward. Starting from each point, and dfs its neighbor 
if the neighbor is equal or less than itself. And maintain two boolean matrix for two oceans, 
indicating an ocean can reach to that point or not. Finally go through all nodes again and 
see if it can be both reached by two oceans. The trick is if a node is already visited, 
no need to visited again. Otherwise it will reach the recursion limits.

This question is very similar to https://leetcode.com/problems/longest-increasing-path-in-a-matrix/

寻找所有从 Pacific 可以到达的水域：从 left 和 top edges 中的水域的节点出发，进行 DFS，若相邻水域的海拔高于或相同，则可以逆流而上到该处。对于可以到达的水域标记在 p_visited 二维数组中
寻找所有从 Atlantic 可以到达的水域：从 right 和 bottom edges 中的水域的节点出发，进行 DFS，若相邻水域的海拔高于或相同，则可以逆流而上到该处。对于可以到达的水域标记在 a_visited 二维数组中
那些可以同时出现在 p_visited 以及 a_visited 中的水域就是能流入两个大洋的水域。



*/

#include <vector>
#include <utility>
#include <queue>
#include <unordered_map>

using namespace std;

class Solution {
public:
	vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix)
	{
		vector<pair<int, int>> result;
		if (matrix.empty())
			return result;
		int m = matrix.size();
		int n = matrix[0].size();
		vector<vector<int>> table(m, vector<int>(n, 0));		// 记录每个水域被访问到的次数
		int dirsX[] = { -1, 1, 0, 0 };
		int dirsY[] = { 0, 0, -1, 1 };

		auto check = [=](const int x, const int y) { return x >= 0 && x < m && y >= 0 && y < n; };

		// 从 Pacific 出发
		queue<pair<int, int>> Q_Pacific;
		vector<vector<bool>> visited(m, vector<bool>(n, false));// 记录此次广搜访问到的水域
		for (int i = 0; i < m; ++i)		// 添加第一列
		{
			Q_Pacific.push({ i, 0 });
			++table[i][0];
			visited[i][0] = true;
		}
		for (int j = 1; j < n; ++j)		// 添加第一行，注 [0][0] 不要再添加了，否则重复
		{
			Q_Pacific.push({ 0, j });
			++table[0][j];
			visited[0][j] = true;
		}
		while (!Q_Pacific.empty())
		{
			auto pos = Q_Pacific.front();
			Q_Pacific.pop();
			for (int i = 0; i < 4; ++i)
			{
				int newPosX = pos.first + dirsX[i];
				int newPosY = pos.second + dirsY[i];
				// 如果新水域合法且未被访问过
				if (check(newPosX, newPosY) && !visited[newPosX][newPosY])
				{
					// 如果新水域比老水域更高，则可逆流到达
					if (matrix[pos.first][pos.second] <= matrix[newPosX][newPosY])
					{
						++table[newPosX][newPosY];
						visited[newPosX][newPosY] = true;
						// 入队当前水域
						Q_Pacific.push({ newPosX, newPosY });
					}
				}
			}
		}

		// 从 Atlantic 出发
		queue<pair<int, int>> Q_Atlantic;
		visited.assign(m, vector<bool>(n, false));		// 记录此次广搜访问到的水域
		for (int i = 0; i < m; ++i)		// 添加最后一列
		{
			Q_Atlantic.push({i, n-1 });
			++table[i][n-1];
			visited[i][n-1] = true;
		}
		for (int j = 0; j < n-1; ++j)	// 添加最后一行，注 [m-1][n-1] 不要再添加了，否则重复
		{
			Q_Atlantic.push({ m-1, j });
			++table[m-1][j];
			visited[m-1][j] = true;
		}
		while (!Q_Atlantic.empty())
		{
			auto pos = Q_Atlantic.front();
			Q_Atlantic.pop();
			for (int i = 0; i < 4; ++i)
			{
				int newPosX = pos.first + dirsX[i];
				int newPosY = pos.second + dirsY[i];
				// 如果新水域合法且未被访问过
				if (check(newPosX, newPosY) && !visited[newPosX][newPosY])
				{
					// 如果新水域比老水域更高，则可逆流到达
					if (matrix[pos.first][pos.second] <= matrix[newPosX][newPosY])
					{
						++table[newPosX][newPosY];
						visited[newPosX][newPosY] = true;
						// 入队当前水域
						Q_Atlantic.push({ newPosX, newPosY });
					}
				}
			}
		}
		// table 中值为 2 表示从 Pacific 和 Altlantic 都可以到达
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j)
				if (table[i][j] == 2)
					result.push_back({ i, j });
		return result;
	}
};

class Solution_v2 {
public:
	int M, N;
	vector<pair<int, int>> dirs = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

	vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix)
	{
		vector<pair<int, int>> result;
		if (matrix.empty())
			return result;
		M = matrix.size(), N = matrix[0].size();
		vector<vector<bool>> p_visited(M, vector<bool>(N, 0));
		vector<vector<bool>> a_visited(M, vector<bool>(N, 0));
		// "Pacific ocean" touches the left and top edges of the matrix and the "Atlantic ocean" touches the right and bottom edges
		for (int i = 0; i < M; ++i)
		{
			dfs(i, 0, matrix, p_visited);
			dfs(i, N - 1, matrix, a_visited);
		}
		for (int j = 0; j < N; ++j)
		{
			dfs(0, j, matrix, p_visited);
			dfs(M - 1, j, matrix, a_visited);
		}
		for(int i = 0; i < M; ++i)
			for (int j = 0; j < N; ++j)
			{
				if (p_visited[i][j] && a_visited[i][j])
				{
					result.push_back({ i, j });
				}
			}
		return result;
	}

	void dfs(int x, int y, vector<vector<int>>& matrix, vector<vector<bool>>& visited)
	{
		// x，y的合法性在 dfs 被调用之前确认。所以不需要再次判断
		visited[x][y] = true;	// 将当前访问节点标记为已访问
		for (auto dir : dirs)
		{
			// 邻居的位置
			int newX = x + dir.first;
			int newY = y + dir.second;
			// 对于合法的邻居、没有被访问过、并且海拔高于当前水域，继续进行深度搜索
			if (newX >= 0 && newX < M
				&& newY >= 0 && newY < N
				&& !visited[newX][newY]
				&& matrix[newX][newY] >= matrix[x][y])
			{
				dfs(newX, newY, matrix, visited);
			}
		}
	}
};