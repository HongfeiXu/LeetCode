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

判断一个无向图（没有重复边，没有自回路）是否为二部图
BFS，着色，如果两个颜色能够将所有节点着色（相邻节点颜色不同），则为二部图，否则不是二部图。

Approach v2:

Ref: https://www.geeksforgeeks.org/bipartite-graph/

思想相同，只是这里关于用一个 vector 来保存每个节点的颜色，若没有颜色，则说明该节点还没有被访问，省去了 visited 数组。
以及在入队的时候赋给节点颜色，每次出队一个节点，（法一中，每次出队一层节点时不必要的。）

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
		vector<unordered_set<int>> two_sets(2); // 保存颜色0和颜色1对应的顶点集合
		vector<bool> visited(n, false);

		// 防止图不连通，对所有顶点，如果没有访问，则进行 BFS
		for (int k = 0; k < n; ++k)
		{
			if (visited[k])
				continue;
			queue<int> Q;
			Q.push(k);
			visited[k] = true;      // 入队时标记为已访问
			int cnt_of_layer = 0;   // 记录当前的层数，根据层数的奇偶性确定颜色
			while (!Q.empty())
			{
				int size_of_layer = Q.size();   // 当前层中节点的个数
				for (int i = 0; i < size_of_layer; ++i)
				{
					// 出队，染色
					int u = Q.front();
					Q.pop();
					two_sets[cnt_of_layer % 2].insert(u);

					// 入队，同时判断 v 是否有颜色，颜色是否与 u 相同
					for (auto v : graph[u])
					{
						// 若 v 未被访问，则入队
						if (!visited[v])
						{
							Q.push(v);
							visited[v] = true;
						}

						// 若 v 已经有颜色，且和 u 设置的颜色相同，则不能进行2着色，不是二部图
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
		// Assign first color to source（不同于法一，这里在入队的时候设置颜色，则可以省去 visited 数组）
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
