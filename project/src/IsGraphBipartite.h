#pragma once

/*

785. Is Graph Bipartite?

Given an undirected graph, return true if and only if it is bipartite.

Recall that a graph is bipartite if we can split it's set of nodes 
into two independent subsets A and B such that every edge in the 
graph has one node in A and another node in B.

The graph is given in the following form: graph[i] is a list of 
indexes j for which the edge between nodes i and j exists.  
Each node is an integer between 0 and graph.length - 1.  
There are no self edges or parallel edges: graph[i] does not contain i, and it doesn't contain any element twice.

Example 1:
Input: [[1,3], [0,2], [1,3], [0,2]]
Output: true
Explanation: 
The graph looks like this:
0----1
|    |
|    |
3----2
We can divide the vertices into two groups: {0, 2} and {1, 3}.

Example 2:
Input: [[1,2,3], [0,2], [0,1,3], [0,2]]
Output: false
Explanation: 
The graph looks like this:
0----1
| \  |
|  \ |
3----2
We cannot find a way to divide the set of nodes into two independent subsets.
 
Note:
graph will have length in range [1, 100].
graph[i] will contain integers in range [0, graph.length - 1].
graph[i] will not contain i or duplicate values.
The graph is undirected: if any element j is in graph[i], then i will be in graph[j].

Approach My:

�ж�һ������ͼ��û���ظ��ߣ�û���Ի�·���Ƿ�Ϊ����ͼ
BFS����ɫ�����������ɫ�ܹ������нڵ���ɫ�����ڽڵ���ɫ��ͬ������Ϊ����ͼ�������Ƕ���ͼ��

Approach v2:

Ref: https://www.geeksforgeeks.org/bipartite-graph/

˼����ͬ��ֻ�����������һ�� vector ������ÿ���ڵ����ɫ����û����ɫ����˵���ýڵ㻹û�б����ʣ�ʡȥ�� visited ���顣
�Լ�����ӵ�ʱ�򸳸��ڵ���ɫ��ÿ�γ���һ���ڵ㣬����һ�У�ÿ�γ���һ��ڵ�ʱ����Ҫ�ġ���

Better then Approach 1.
Time: O(V+E)

*/

#include <vector>
#include <queue>
#include <unordered_set>


using namespace std;

class Solution {
public:
	bool isBipartite(vector<vector<int>>& graph)
	{
		int n = graph.size();
		vector<unordered_set<int>> two_sets(2); // ������ɫ0����ɫ1��Ӧ�Ķ��㼯��
		vector<bool> visited(n, false);

		// ��ֹͼ����ͨ�������ж��㣬���û�з��ʣ������ BFS
		for (int k = 0; k < n; ++k)
		{
			if (visited[k])
				continue;
			queue<int> Q;
			Q.push(k);
			visited[k] = true;      // ���ʱ���Ϊ�ѷ���
			int cnt_of_layer = 0;   // ��¼��ǰ�Ĳ��������ݲ�������ż��ȷ����ɫ
			while (!Q.empty())
			{
				int size_of_layer = Q.size();   // ��ǰ���нڵ�ĸ���
				for (int i = 0; i < size_of_layer; ++i)
				{
					// ���ӣ�Ⱦɫ
					int u = Q.front();
					Q.pop();
					two_sets[cnt_of_layer % 2].insert(u);

					// ��ӣ�ͬʱ�ж� v �Ƿ�����ɫ����ɫ�Ƿ��� u ��ͬ
					for (auto v : graph[u])
					{
						// �� v δ�����ʣ������
						if (!visited[v])
						{
							Q.push(v);
							visited[v] = true;
						}

						// �� v �Ѿ�����ɫ���Һ� u ���õ���ɫ��ͬ�����ܽ���2��ɫ�����Ƕ���ͼ
						if (two_sets[cnt_of_layer % 2].find(v) != two_sets[cnt_of_layer % 2].end())
							return false;
					}

				}

				++cnt_of_layer;
			}
		}
		return true;
	}
};

class Solution_v2 {
public:
	bool isBipartite(vector<vector<int>>& graph)
	{
		int n = graph.size();
		// Create a color vector to store colors assigned to all vertices. -1: no color, 1: first color, 0: second color.
		vector<int> color_vec(n, -1);	

		for (int i = 0; i < n; ++i)
		{
			if (color_vec[i] == -1)
			{
				if (!isBipartiteUtil(graph, i, color_vec))
					return false;
			}
		}
		return true;
	}

	bool isBipartiteUtil(vector<vector<int>>& graph, int start, vector<int>& color_vec)
	{
		// Assign first color to source����ͬ�ڷ�һ����������ӵ�ʱ��������ɫ�������ʡȥ visited ���飩
		color_vec[start] = 1;
		queue<int> Q;
		Q.push(start);
		while (!Q.empty())
		{
			// Dequeue a vertex from queue
			int u = Q.front();
			Q.pop();

			// Find all non-colored adjacent vertices
			for (auto v : graph[u])
			{
				// v is not colored
				if (color_vec[v] == -1)
				{
					// Assign alternate color to v
					color_vec[v] = 1 - color_vec[u];
					Q.push(v);
				}
				// v is colored with same color as u
				else if (color_vec[v] == color_vec[u])
					return false;
			}
		}
		return true;
	}
};
