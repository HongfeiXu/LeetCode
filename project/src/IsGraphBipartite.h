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



Approach:
Ref: https://www.geeksforgeeks.org/bipartite-graph/

�ж�һ������ͼ��û���ظ��ߣ�û���Ի�·���Ƿ�Ϊ����ͼ
��ɫ���⣬���������ɫ�ܹ������нڵ���ɫ�����ڽڵ���ɫ��ͬ������Ϊ����ͼ�������Ƕ���ͼ��

BFS
����������ʼ����u��
���uû����ɫ������һ����ɫ��ɫ��ӡ�
����u��Ȼ�����u�������ھӽڵ�v�����vû����ɫ��������һ����ɫ��ɫ���������С����v��ɫ����u��ɫ��ͬ���򷵻�false��

�������ͼ�����Ƿ���ͨ�ģ�������Ҫ�������е�ǰû�б���ɫ�Ľڵ㡣

Better then Approach 1.
Time: O(V+E)

Approach 2:

DFS
�������ⶥ��u��
���uû�б���ɫ����ɫ֮��Ȼ��ݹ������һ����ɫ��ɫ��u���е��ھӽڵ㣬��������нڵ��Ѿ�����ɫ��������ɫ��u����ɫ�Ƿ���ͬ�������ͬ�򷵻� false��


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

class Solution_v2 {
public:
	bool isBipartite(vector<vector<int>>& graph)
	{
		int n = graph.size();
		vector<int> color_vec(n, -1);
		for (int i = 0; i < n; ++i)
		{
			if (color_vec[i] == -1 && !validColor(graph, i, color_vec, 0))
				return false;
		}
		return true;
	}

	// use color to color vertex u
	bool validColor(vector<vector<int>>& graph, int u, vector<int>& color_vec, int color)
	{
		// u is colored
		// ��� u ���е���ɫ��Ҫ��������ɫ��ͬ���򷵻� true
		if (color_vec[u] != -1)
			return color_vec[u] == color;
		// u is not colored
		color_vec[u] = color;
		for (auto v : graph[u])
		{
			// use another color to color all u's adjacent nodes
			if (!validColor(graph, v, color_vec, 1 - color))
				return false;
		}
		return true;
	}
};