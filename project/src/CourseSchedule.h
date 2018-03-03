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

ֻҪû��ѭ�������Ŀγ̣���һ������������пγ̡�
�ж�����ͼ������һ���������������ͨͼ���Ƿ��л���
DFS + recursive_stack

######################################################
Approach v2:

DFS + color
��ֱ��

######################################################
Approach v3:

BFS
Ref: http://www.cnblogs.com/grandyang/p/4484571.html

����ȵĽǶȿ��ǣ�һ���ɾ�����Ϊ0�Ľڵ㣬ɾ����ǰ�����Ϊ0�Ľڵ�ʱҲҪ�����亢�ӽڵ㡣
�����ջ��нڵ����Ȳ�Ϊ0����˵���л��������޻���

��Ҫ�������������ݣ�1. ���ڵ����ȣ�2. ���ڵ�ĺ��ӽڵ�


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

		vector<bool> visited(numCourses, false);			// ��¼�Լ������ʵĽڵ�
		vector<bool> recursive_stack(numCourses, false);	// ��¼��ǰ�������ջ�еĽڵ�
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
		return !is_cyclic;		// �л����޷�������пγ̣��޻������������пγ�
	}

	// ʹ�� unordered_set �洢�ڽӾ������Ϣ
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
				// �����ڻ�·�����޷����
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
		vector<vector<int>> adj(numCourses);		// ʹ�� vector �����գ�
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
			// ���� u �ĺ��ӽڵ� v �����
			for (auto v : adj[u])
			{
				--in[v];
				// �� v ����ȼ��� 0������ӡ�
				if (in[v] == 0)
					q.push(v);
			}
		}
		return numCourses == 0;
	}
};