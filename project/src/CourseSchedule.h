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

Approach:

只要没有循环依赖的课程，则一定可以完成所有课程。
判断有向图（考虑一般情况，即：非连通图）是否有环。

*/

#include <vector>
#include <utility>
#include <unordered_set>

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
			graph[pre.first].insert(pre.second);
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