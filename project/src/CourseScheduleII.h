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

�������棺
���������Ƿ���ڣ�����ͼ�Ƿ�Ϊ�޻�ͼ����
�����ڱ���������С�

���������ж�����ͼ�Ƿ�Ϊ�޻�ͼ���㷨���� DFS��
��������Ҳ���� DFS������ͬʱ���� DFS ʵ�����������棬��ɨ����жϡ�
��������л�����ֱ�ӷ��ؿ����У����򣬲��ϸ����������С�

����ͨ����¼DFS�ݹ���ʵĽڵ�ջ recur_stack ���ж��Ƿ���ڻ�·��

Approach v2:

BFS�������� 207. Course Schedule Approach v3��������ȡ�
ɾ�����Ϊ0�Ľڵ㣬ɾ����ǰ�����Ϊ0�Ľڵ�ʱҲҪ�����亢�ӽڵ㡣�ң����ճ���˳�򱣴�ڵ㣬�õ��������С�
�����ջ��нڵ����Ȳ�Ϊ0����˵���л��������޻���

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

		// ���򷵻�
		return vector<int>(result.rbegin(), result.rend());
	}

	// ���� true ��ʾ�л���false ��ʾ�޻�
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
		// ʹ�� vector<vector<int>> �� vector<unordered_set<int>> �����գ�������� [0,1],[0,1] �����ظ��ıߣ�
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
		// ������нڵ���Ⱦ���Ϊ0��˵�����԰������еĿγ�
		if (result.size() == numCourses)
			return result;
		// ���ڿγ�δ�����ţ����ڻ���
		else
			return { };
	}
};
