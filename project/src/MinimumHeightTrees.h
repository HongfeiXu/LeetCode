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

��ÿ������ u Ϊ��ʼ�㣬��Դ���·���������ֵ��Ϊ�� u Ϊ���������ĸ߶� Hu��
ѡ�������С Hu ����Щ���㡣

########################################################################
Approach #2 

����з�
һ��һ�����ȥҶ�ڵ㣬��ȥһ��ڵ��ͬʱ��������ЩҶ�ӽڵ�ĸ��ڵ㣬
���ʣ��һ�����������ڵ��������Ҫ�����С�߶ȵĸ��ڵ㡣��ע��������С�߶ȵĸ��ڵ�����ֻ��������

########################################################################
Approach #3������ Approach #2

Ref: http://www.cnblogs.com/grandyang/p/5000291.html

����з�
��϶��У�Ѱ��һ���Ϊ1�Ľڵ㣬��ΪҶ�ӽڵ㣬����һ�� k ���ڵ㣬���丸�ڵ���ɾ����ЩҶ�ӽڵ㣬�����ڵ�Ķ�Ҳ��Ϊ1���򽫸��ڵ�����С����Ҹ��� n = n-k��
ֱ�� n <= 2 ʱ���˳�ѭ����

���ַ�����BFS����ֻ�������Ǵ�k��Ҷ�ӽڵ�������������ڵ��������BFS���ǴӸ��ڵ������Ҷ�ӽڵ������

������ 207. Course Schedule

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

		// ���� u Ϊ��ʼ�㣬��Դ���·�����������·�������ֵ
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

		// n >= 2 ʱ
		vector<unordered_set<int>> adj(n);
		for (auto edge : edges)
		{
			adj[edge.first].insert(edge.second);
			adj[edge.second].insert(edge.first);
		}
		// ��ŵ�ǰ����ȥ��Ҷ��
		vector<int> leaves;
		// ������ȥ��Ҷ�ӱ��Ϊ true
		vector<bool> erased(n, false);
		int count = 0;			// ��¼�Լ���ȥ��Ҷ�ӽڵ�ĸ���
		while (count + 2 < n)	// ���ʣ��1������2���ڵ�ʱ�������������
		{
			// Ѱ��Ҷ�ӽڵ㲢��ȥ
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

	// Ѱ��Ҷ�ӽڵ㲢��ȥ
	void findAndEraseLeaves(vector<unordered_set<int>>& nodes, vector<int>& leaves, vector<bool>& erased)
	{
		vector<pair<int, int>> leaves_edge;	// �洢Ҷ�ڵ��Լ��丸�ڵ�
		// Ѱ��һ��Ҷ�ӽڵ�
		for (int i = 0; i < nodes.size(); ++i)
		{
			if (!erased[i] && nodes[i].size() == 1)
				leaves_edge.push_back({ i, *(nodes[i].begin()) });
		}
		// ����Ҷ�ӽڵ�ĸ��ڵ㣬���ҽ�Ҷ�ӽڵ���Ϊ��ɾ��
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
			// һ��һ�����
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