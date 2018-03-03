#pragma once

/*

207. Course Schedule

There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?

For example:

2, [[1,0]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0. So it is possible.

2, [[1,0],[0,1]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.

Note:
The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
You may assume that there are no duplicate edges in the input prerequisites.

######################################################
Approach:

只要没有循环依赖的课程，则一定可以完成所有课程。
判断有向图（考虑一般情况，即：非连通图）是否有环。
DFS + recursive_stack

######################################################
Approach v2:

DFS + color
更直观

######################################################
Approach v3:

BFS
Ref: http://www.cnblogs.com/grandyang/p/4484571.html

从入度的角度考虑，一层层删除入度为0的节点，删除当前层入度为0的节点时也要更新其孩子节点。
若最终还有节点的入度不为0，则说明有环，否则无环。

主要处理两部分内容：1. 各节点的入度，2. 各节点的孩子节点


*/

#include <vector>
#include <utility>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution {
public:
	bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites)
	{
		if (numCourses <= 1)
			return true;
		// construct adjacency matrix
		auto graph = makeGraph(numCourses, prerequisites);

		vector<bool> visited(numCourses, false);			// 记录以及被访问的节点
		vector<bool> recursive_stack(numCourses, false);	// 记录当前深度搜索栈中的节点
		bool is_cyclic = false;

		// Call the recursive helper function to detect cycle in different
		// DFS trees
		for (int i = 0; i < numCourses; ++i)
		{
			if (isCyclic(i, graph, visited, recursive_stack))
			{
				is_cyclic = true;
				break;
			}
		}
		return !is_cyclic;		// 有环则无法完成所有课程，无环则可以完成所有课程
	}

	// 使用 unordered_set 存储邻接矩阵的信息
	vector<unordered_set<int>> makeGraph(int numCourses, vector<pair<int, int>>& prerequisites)
	{
		vector<unordered_set<int>> graph(numCourses);
		for (auto pre : prerequisites)
			graph[pre.second].insert(pre.first);
		return graph;
	}

	bool isCyclic(int v, vector<unordered_set<int>>& graph, vector<bool>& visited, vector<bool>& recursive_stack)
	{
		if (!visited[v])
		{
			visited[v] = true;
			recursive_stack[v] = true;
			for (auto neighbor : graph[v])
			{
				if (!visited[neighbor] && isCyclic(neighbor, graph, visited, recursive_stack))
					return true;
				else if (recursive_stack[neighbor])
					return true;
			}
			recursive_stack[v] = false;
		}
		return false;
	}
};

class Solution_v2 {
public:
	enum color { WHITE, GREY, BLACK };

	bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites)
	{
		vector<unordered_set<int>> graph(numCourses);
		for (auto edge : prerequisites)
			graph[edge.second].insert(edge.first);

		vector<color> colors(numCourses, WHITE);
		for (int i = 0; i < numCourses; ++i)
		{
			if (colors[i] == WHITE)
			{
				// 若存在回路，则无法完成
				if (isCyclic(i, graph, colors))
					return false;
			}
		}
		return true;
	}

	bool isCyclic(int u, vector<unordered_set<int>>& graph, vector<color>& colors)
	{
		colors[u] = GREY;
		for (auto v : graph[u])
		{
			if (colors[v] == WHITE && isCyclic(v, graph, colors))
				return true;
			else if (colors[v] == GREY)
				return true;
		}
		colors[u] = BLACK;
		return false;
	}
};

class Solution_v3 {
public:
	bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites)
	{
		vector<vector<int>> adj(numCourses);		// 使用 vector 更保险，
		vector<int> in(numCourses, 0);
		for (const auto& edge : prerequisites)
		{
			adj[edge.second].push_back(edge.first);
			++in[edge.first];
		}

		queue<int> q;
		for (int i = 0; i < numCourses; ++i)
		{
			if (in[i] == 0)
				q.push(i);
		}
		while (!q.empty())
		{
			--numCourses;
			int u = q.front();
			q.pop();
			// 更新 u 的孩子节点 v 的入度
			for (auto v : adj[u])
			{
				--in[v];
				// 若 v 的入度减至 0，则入队。
				if (in[v] == 0)
					q.push(v);
			}
		}
		return numCourses == 0;
	}
};