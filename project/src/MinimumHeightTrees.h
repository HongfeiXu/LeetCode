#pragma once

/*

310. Minimum Height Trees

For a undirected graph with tree characteristics, we can choose any node as the root. 
The result graph is then a rooted tree. Among all possible rooted trees, 
those with minimum height are called minimum height trees (MHTs). 
Given such a graph, write a function to find all the MHTs and return a list of their root labels.

Format
The graph contains n nodes which are labeled from 0 to n - 1. 
You will be given the number n and a list of undirected edges (each edge is a pair of labels).

You can assume that no duplicate edges will appear in edges. 
Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.

Example 1:

Given n = 4, edges = [[1, 0], [1, 2], [1, 3]]

        0
        |
        1
       / \
      2   3
return [1]

Example 2:

Given n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]

     0  1  2
      \ | /
        3
        |
        4
        |
        5
return [3, 4]

########################################################################
Approach #1 Dijsktra[Time Limit Exceeded]:

以每个顶点 u 为起始点，求单源最短路径，则，最大值即为以 u 为树根的树的高度 Hu。
选择具有最小 Hu 的那些顶点。

########################################################################
Approach #2 

剥洋葱法
一层一层的褪去叶节点，退去一层节点的同时，更新这些叶子节点的父节点，
最后剩下一个或者两个节点就是我们要求的最小高度的根节点。（注：具有最小高度的根节点至多只有两个）

########################################################################
Approach #3，优于 Approach #2

Ref: http://www.cnblogs.com/grandyang/p/5000291.html

剥洋葱法
结合队列，寻找一层度为1的节点，即为叶子节点，对这一层 k 个节点，在其父节点中删除这些叶子节点，若父节点的度也变为1，则将父节点入队列。并且更新 n = n-k。
直到 n <= 2 时，退出循环。

这种方法与BFS很像，只是这里是从k个叶子节点出发，逐层向根节点遍历。而BFS则是从根节点出发向叶子节点遍历。

类似于 207. Course Schedule

*/

#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <queue>
#include <numeric>
#include <unordered_set>

using namespace std;

class Solution {
public:
	vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges)
	{
		vector<int> result;
		if (n == 0)
			return result;

		vector<vector<int>> adj_mat(n, vector<int>(n, INT_MAX));
		for (const auto &edge : edges)
		{
			adj_mat[edge.first][edge.second] = 1;
			adj_mat[edge.second][edge.first] = 1;
		}

		// 顶点 u 为起始点，求单源最短路径，保存最短路径的最大值
		vector<int> u_height(n);

		for (int u = 0; u < n; ++u)
		{
			vector<bool> spt_set(n, false);
			vector<int> dist(n, INT_MAX);
			sptSolver(u, spt_set, dist, adj_mat);
			int height = dist[0];
			for (int i = 1; i < n; ++i)
				height = max(height, dist[i]);
			u_height[u] = height;
		}
		
		int min_height = u_height[0];
		result.push_back(0);
		for (int i = 1; i < n; ++i)
		{
			if (u_height[i] < min_height)
			{
				result.clear();
				result.push_back(i);
				min_height = u_height[i];
			}
			else if (u_height[i] == min_height)
			{
				result.push_back(i);
			}
		}
		return result;
	}

	void sptSolver(int start, vector<bool>& spt_set, vector<int>& dist, vector<vector<int>>& adj_mat)
	{
		dist[start] = 0;
		int n = spt_set.size();

		for (int cnt = 0; cnt < n - 1; ++cnt)
		{
			int u = minDistVertex(spt_set, dist);
			spt_set[u] = true;
			for (int v = 0; v < n; ++v)
			{
				if (spt_set[v] == false && adj_mat[u][v] == 1 && dist[u] + adj_mat[u][v] < dist[v])
					dist[v] = dist[u] + adj_mat[u][v];
			}
		}
	}

	int minDistVertex(vector<bool>& spt_set, vector<int>& dist)
	{
		int min_dist = INT_MAX;
		int min_dist_vertex;
		for (int i = 0; i < spt_set.size(); ++i)
		{
			if (spt_set[i] == false && dist[i] <= min_dist)
			{
				min_dist = dist[i];
				min_dist_vertex = i;
			}
		}
		return min_dist_vertex;
	}
};

class Solution_v2 {
public:
	vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges)
	{
		vector<int> result;
		if (n == 0)
			return result;
		else if (n == 1)
		{
			result.push_back(0);
			return result;
		}

		// n >= 2 时
		vector<unordered_set<int>> adj(n);
		for (auto edge : edges)
		{
			adj[edge.first].insert(edge.second);
			adj[edge.second].insert(edge.first);
		}
		// 存放当前待剥去的叶子
		vector<int> leaves;
		// 将被剥去的叶子标记为 true
		vector<bool> erased(n, false);
		int count = 0;			// 记录以及剥去的叶子节点的个数
		while (count + 2 < n)	// 最后剩下1个或者2个节点时，不继续剥洋葱
		{
			// 寻找叶子节点并剥去
			findAndEraseLeaves(adj, leaves, erased);
			count += leaves.size();
		}
		for (int i = 0; i < n; ++i)
		{
			if (!erased[i])
				result.push_back(i);
		}
		return result;
	}

	// 寻找叶子节点并剥去
	void findAndEraseLeaves(vector<unordered_set<int>>& nodes, vector<int>& leaves, vector<bool>& erased)
	{
		vector<pair<int, int>> leaves_edge;	// 存储叶节点以及其父节点
		// 寻找一层叶子节点
		for (int i = 0; i < nodes.size(); ++i)
		{
			if (!erased[i] && nodes[i].size() == 1)
				leaves_edge.push_back({ i, *(nodes[i].begin()) });
		}
		// 更新叶子节点的父节点，并且将叶子节点标记为已删除
		for (int i = 0; i < leaves_edge.size(); ++i)
		{
			nodes[leaves_edge[i].second].erase(leaves_edge[i].first);
			erased[leaves_edge[i].first] = true;
		}

		leaves.clear();
		for (int i = 0; i < leaves_edge.size(); ++i)
			leaves.push_back(leaves_edge[i].first);
	}
};

class Solution_v2_2 {
public:
	vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges)
	{
		if (n == 1)
			return { 0 };
		vector<unordered_set<int>> adj(n);
		for (auto edge : edges)
		{
			adj[edge.first].insert(edge.second);
			adj[edge.second].insert(edge.first);
		}
		queue<int> q;
		for (int i = 0; i < adj.size(); ++i)
		{
			if (adj[i].size() == 1)
				q.push(i);
		}
		while (n > 2)
		{
			// 一层一层剥除
			int size = q.size();
			n -= size;
			for (int i = 0; i < size; ++i)
			{
				int leaf = q.front();
				q.pop();
				for (auto parent : adj[leaf])
				{
					adj[parent].erase(leaf);
					if (adj[parent].size() == 1)
						q.push(parent);
				}
			}
		}

		vector<int> result;
		while (!q.empty())
		{
			result.push_back(q.front());
			q.pop();
		}
		return result;
	}
};