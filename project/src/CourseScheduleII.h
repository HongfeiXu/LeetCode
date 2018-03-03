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

Approach v2:

BFS，类似于 207. Course Schedule Approach v3。考虑入度。
删除入度为0的节点，删除当前层入度为0的节点时也要更新其孩子节点。且，按照出队顺序保存节点，得到拓扑序列。
若最终还有节点的入度不为0，则说明有环，否则无环。

*/

#include <vector>
#include <unordered_set>
#include <queue>

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

class Solution_v2 {
public:
	vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites)
	{
		vector<int> result;
		// 使用 vector<vector<int>> 比 vector<unordered_set<int>> 更保险（比如存在 [0,1],[0,1] 这种重复的边）
		vector<vector<int>> adj(numCourses);		
		vector<int> in(numCourses, 0);
		for (auto edge : prerequisites)
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
			int u = q.front();
			q.pop();
			result.push_back(u);
			for (auto v : adj[u])
			{
				--in[v];
				if (in[v] == 0)
					q.push(v);
			}
		}
		// 如果所有节点入度均变为0，说明可以安排所有的课程
		if (result.size() == numCourses)
			return result;
		// 存在课程未被安排（存在环）
		else
			return { };
	}
};
