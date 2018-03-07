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
Ŀ�꣺ Ѱ���Ǹ�Ψһ�Ļ���
������
���ȥ����Ϊ1�ĵ㣨Ҷ�ӽڵ㣩��ͬʱ���ڽӾ�����ɾ���ñߣ�a--b, b--a����������������Ķȣ�ֱ�������ڶ�Ϊ1�Ķ��㡣�����ư���У�
��󣬰��� edges �����򣬲�����Ȼ���ڽӾ����еıߣ���Ϊ����

Approach v2(much better):
Union Find
����ͼ���Ƿ��л����жϷ�����https://www.geeksforgeeks.org/union-find/
��������ֻ����һ���������� edges ������������ʸ����ߣ��ϲ����ཻ���㼯�ϣ�ֱ�������ߵ�����������ͬһ������ʱ�����ɻ�����֪���ñ߼�Ϊ����


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
		// (n+1)x(n+1) ͼ���ڽӾ����ʾ�����У���0�����0��Ϊ��Ч���ݡ�
		vector<vector<int>> adj_mat(n + 1, vector<int>(n + 1, 0));
		// ����Ķ�
		vector<int> degree(n + 1, 0);

		for (auto edge : edges)
		{
			adj_mat[edge.front()][edge.back()] = 1;
			adj_mat[edge.back()][edge.front()] = 1;
			++degree[edge.front()];
			++degree[edge.back()];
		}

		// ��ǽڵ��Ƿ��Ѿ�������
		vector<bool> visited(n + 1, false);
		// ��ӵ�ǰ��Ϊ 1 �Ķ��㣬�ұ��Ϊ�ѷ���
		queue<int> q;
		for (int i = 1; i <= n; ++i)
		{
			if (degree[i] == 1)
			{
				q.push(i);
				visited[i] = true;	// ���ýڵ���Ϊ�ѷ��ʣ���ֹ�ظ����ʸýڵ�
			}
		}
		while (!q.empty())
		{
			// ����һ����Ϊ 1 �Ķ���
			int curr = q.front();
			q.pop();
			for (int i = 1; i <= n; ++i)
			{
				// ��� i δ�����ʣ����� curr ���ھӣ��ݼ� i �Ķȣ�������� 1 ����ӣ��ұ��Ϊ�ѷ���
				if (!visited[i] && adj_mat[curr][i] == 1)
				{
					--degree[i];
					// �� adj_mat ��ɾ���� curr -- i �� i -- curr
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

		// adj_mat �����µı߹���һ������������ĿҪ�󣬴Ӻ���ǰ���� edges���ҵ���һ���� adj_mat �еı߼�Ϊ����
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
		vector<int> parent(n + 1, -1);	// ���鼯
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