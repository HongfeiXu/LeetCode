#pragma once

/*

337. Course Schedule II

There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.

There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.

For example:

2, [[1,0]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1]

4, [[1,0],[2,0],[3,1],[3,2]]
There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. 
Both courses 1 and 2 should be taken after you finished course 0. So one correct course order is [0,1,2,3]. 
Another correct ordering is[0,2,1,3].

Approach:

Topological Sorting and Detect Cycle in a Directed Graph

两个方面：
拓扑排序是否存在（有向图是否为无环图），
若存在保存这个序列。

这里由于判断有向图是否为无环图的算法基于 DFS，
拓扑排序也基于 DFS，可以同时基于 DFS 实现这两个方面，边扫描边判断。
如果发现有环，则直接返回空序列，否则，不断更新拓扑序列。

这里通过记录DFS递归访问的节点栈 recur_stack 来判断是否存在环路。

*/

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
	vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites)
	{
		vector<int> result;
		vector<unordered_set<int>> graph(numCourses);
		for (auto edge : prerequisites)
			graph[edge.second].insert(edge.first);
		vector<bool> visited(numCourses, false);
		vector<bool> recur_stack(numCourses, false);
		for (int i = 0; i < numCourses; ++i)
		{
			if (!visited[i])
			{
				if (topologicalSort(i, graph, visited, recur_stack, result))
					return vector<int>(result.begin(), result.begin());
			}
		}

		// 逆序返回
		return vector<int>(result.rbegin(), result.rend());
	}

	// 返回 true 表示有环，false 表示无环
	bool topologicalSort(int u, vector<unordered_set<int>>& graph, vector<bool>& visited, vector<bool>& recur_stack, vector<int>& result)
	{
		visited[u] = true;
		recur_stack[u] = true;
		for (auto v : graph[u])
		{
			if (!visited[v] && topologicalSort(v, graph, visited, recur_stack, result))
			{
				return true;
			}
			else if (recur_stack[v])
			{
				return true;
			}
		}
		recur_stack[u] = false;
		result.push_back(u);

		return false;
	}
};
