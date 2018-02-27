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
���ι�������������������Դ���ߺ��ϱߡ����������ˮ�����Լ����Դ��ұߺ��±ߡ����������ˮ����
��������̫ƽ����ߡ��ϱ�һ��ʼ�ͷ�������У������Ϊ�ѷ��ʣ��ɵ��
���ڴ������ұߡ��±�Ҳһ��ʼ�ͷ�������У������Ϊ�ѷ��ʣ��ɵ��
˼·�ǣ��������������һ����Ҫ��һ��������������ԴӶ�����������

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

Ѱ�����д� Pacific ���Ե����ˮ�򣺴� left �� top edges �е�ˮ��Ľڵ���������� DFS��������ˮ��ĺ��θ��ڻ���ͬ��������������ϵ��ô������ڿ��Ե����ˮ������ p_visited ��ά������
Ѱ�����д� Atlantic ���Ե����ˮ�򣺴� right �� bottom edges �е�ˮ��Ľڵ���������� DFS��������ˮ��ĺ��θ��ڻ���ͬ��������������ϵ��ô������ڿ��Ե����ˮ������ a_visited ��ά������
��Щ����ͬʱ������ p_visited �Լ� a_visited �е�ˮ��������������������ˮ��



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
		vector<vector<int>> table(m, vector<int>(n, 0));		// ��¼ÿ��ˮ�򱻷��ʵ��Ĵ���
		int dirsX[] = { -1, 1, 0, 0 };
		int dirsY[] = { 0, 0, -1, 1 };

		auto check = [=](const int x, const int y) { return x >= 0 && x < m && y >= 0 && y < n; };

		// �� Pacific ����
		queue<pair<int, int>> Q_Pacific;
		vector<vector<bool>> visited(m, vector<bool>(n, false));// ��¼�˴ι��ѷ��ʵ���ˮ��
		for (int i = 0; i < m; ++i)		// ��ӵ�һ��
		{
			Q_Pacific.push({ i, 0 });
			++table[i][0];
			visited[i][0] = true;
		}
		for (int j = 1; j < n; ++j)		// ��ӵ�һ�У�ע [0][0] ��Ҫ������ˣ������ظ�
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
				// �����ˮ��Ϸ���δ�����ʹ�
				if (check(newPosX, newPosY) && !visited[newPosX][newPosY])
				{
					// �����ˮ�����ˮ����ߣ������������
					if (matrix[pos.first][pos.second] <= matrix[newPosX][newPosY])
					{
						++table[newPosX][newPosY];
						visited[newPosX][newPosY] = true;
						// ��ӵ�ǰˮ��
						Q_Pacific.push({ newPosX, newPosY });
					}
				}
			}
		}

		// �� Atlantic ����
		queue<pair<int, int>> Q_Atlantic;
		visited.assign(m, vector<bool>(n, false));		// ��¼�˴ι��ѷ��ʵ���ˮ��
		for (int i = 0; i < m; ++i)		// ������һ��
		{
			Q_Atlantic.push({i, n-1 });
			++table[i][n-1];
			visited[i][n-1] = true;
		}
		for (int j = 0; j < n-1; ++j)	// ������һ�У�ע [m-1][n-1] ��Ҫ������ˣ������ظ�
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
				// �����ˮ��Ϸ���δ�����ʹ�
				if (check(newPosX, newPosY) && !visited[newPosX][newPosY])
				{
					// �����ˮ�����ˮ����ߣ������������
					if (matrix[pos.first][pos.second] <= matrix[newPosX][newPosY])
					{
						++table[newPosX][newPosY];
						visited[newPosX][newPosY] = true;
						// ��ӵ�ǰˮ��
						Q_Atlantic.push({ newPosX, newPosY });
					}
				}
			}
		}
		// table ��ֵΪ 2 ��ʾ�� Pacific �� Altlantic �����Ե���
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
		// x��y�ĺϷ����� dfs ������֮ǰȷ�ϡ����Բ���Ҫ�ٴ��ж�
		visited[x][y] = true;	// ����ǰ���ʽڵ���Ϊ�ѷ���
		for (auto dir : dirs)
		{
			// �ھӵ�λ��
			int newX = x + dir.first;
			int newY = y + dir.second;
			// ���ںϷ����ھӡ�û�б����ʹ������Һ��θ��ڵ�ǰˮ�򣬼��������������
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