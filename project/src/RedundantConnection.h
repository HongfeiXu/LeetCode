#pragma once

/*

684. Redundant Connection

In this problem, a tree is an undirected graph that is connected and has no cycles.

The given input is a graph that started as a tree with N nodes (with distinct values 1, 2, ..., N), with one additional edge added. The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.

The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] with u < v, that represents an undirected edge connecting nodes u and v.

Return an edge that can be removed so that the resulting graph is a tree of N nodes. If there are multiple answers, return the answer that occurs last in the given 2D-array. The answer edge [u, v] should be in the same format, with u < v.

Example 1:
Input: [[1,2], [1,3], [2,3]]
Output: [2,3]
Explanation: The given undirected graph will be like this:
  1
 / \
2 - 3
Example 2:
Input: [[1,2], [2,3], [3,4], [1,4], [1,5]]
Output: [1,4]
Explanation: The given undirected graph will be like this:
5 - 1 - 2
    |   |
    4 - 3
Note:
The size of the input 2D-array will be between 3 and 1000.
Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input array.

Approach my:
目标： 寻找那个唯一的环。
方法：
逐个去掉度为1的点（叶子节点），同时从邻接矩阵中删除该边（a--b, b--a），更新其他顶点的度，直到不存在度为1的顶点。（类似剥洋葱）
最后，按照 edges 的逆序，查找仍然在邻接矩阵中的边，即为所求

Approach v2(much better):
Union Find
无向图中是否有环的判断方法。https://www.geeksforgeeks.org/union-find/
这里由于只存在一个环，则按照 edges 的正序，逐个访问各个边，合并不相交顶点集合，直到这条边的两个顶点在同一个集合时，构成环，可知，该边即为所求。


*/

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
	vector<int> findRedundantConnection(vector<vector<int>>& edges)
	{
		// number of veritces
		int n = edges.size();
		// (n+1)x(n+1) 图的邻接矩阵表示，其中，第0行与第0列为无效内容。
		vector<vector<int>> adj_mat(n + 1, vector<int>(n + 1, 0));
		// 顶点的度
		vector<int> degree(n + 1, 0);

		for (auto edge : edges)
		{
			adj_mat[edge.front()][edge.back()] = 1;
			adj_mat[edge.back()][edge.front()] = 1;
			++degree[edge.front()];
			++degree[edge.back()];
		}

		// 标记节点是否已经被访问
		vector<bool> visited(n + 1, false);
		// 入队当前度为 1 的顶点，且标记为已访问
		queue<int> q;
		for (int i = 1; i <= n; ++i)
		{
			if (degree[i] == 1)
			{
				q.push(i);
				visited[i] = true;	// 将该节点标记为已访问，防止重复访问该节点
			}
		}
		while (!q.empty())
		{
			// 出队一个度为 1 的顶点
			int curr = q.front();
			q.pop();
			for (int i = 1; i <= n; ++i)
			{
				// 如果 i 未被访问，且是 curr 的邻居，递减 i 的度，如果减至 1 则入队，且标记为已访问
				if (!visited[i] && adj_mat[curr][i] == 1)
				{
					--degree[i];
					// 从 adj_mat 中删除边 curr -- i 与 i -- curr
					adj_mat[curr][i] = 0;
					adj_mat[i][curr] = 0;

					if (degree[i] == 1)
					{
						q.push(i);
						visited[i] = true;
					}
				}
			}
		}

		// adj_mat 中余下的边构成一个环，按照题目要求，从后向前搜索 edges，找到第一个在 adj_mat 中的边即为所求
		for (auto it = edges.rbegin(); it != edges.rend(); ++it)
		{
			if (adj_mat[it->front()][it->back()] == 1)
				return *it;
		}
	}
};

class Solution_v2 {
public:
	vector<int> findRedundantConnection(vector<vector<int>>& edges)
	{
		int n = edges.size();
		vector<int> parent(n + 1, -1);	// 并查集
		for (auto edge : edges)
		{
			int u = edge.front();
			int v = edge.back();
			while (parent[u] != -1)
				u = parent[u];
			while (parent[v] != -1)
				v = parent[v];
			if (u != v)
				parent[u] = v;
			else
				return edge;
		}
	}
};