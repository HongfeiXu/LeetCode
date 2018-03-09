#pragma once

/*

685. Redundant Connection II

In this problem, a rooted tree is a directed graph such that, 
there is exactly one node (the root) for which all other nodes are descendants of this node, 
plus every node has exactly one parent, except for the root node which has no parents.

The given input is a directed graph that started as a rooted tree with N nodes 
(with distinct values 1, 2, ..., N), with one additional directed edge added. 
The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.

The resulting graph is given as a 2D-array of edges. Each element of edges is 
a pair [u, v] that represents a directed edge connecting nodes u and v, where u is a parent of child v.

Return an edge that can be removed so that the resulting graph is a rooted tree of N nodes. 
If there are multiple answers, return the answer that occurs last in the given 2D-array.

Example 1:
Input: [[1,2], [1,3], [2,3]]
Output: [2,3]
Explanation: The given directed graph will be like this:
  1
 / \
v   v
2-->3
Example 2:
Input: [[1,2], [2,3], [3,4], [4,1], [1,5]]
Output: [4,1]
Explanation: The given directed graph will be like this:
5 <- 1 -> 2
     ^    |
     |    v
     4 <- 3
Note:
The size of the input 2D-array will be between 3 and 1000.
Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input array.

Approach:

DFS
�����ֿ��������

https://discuss.leetcode.com/assets/uploads/files/1507232873325-screen-shot-2017-10-05-at-2.25.34-pm-resized.png

1. ��ǰͼ���޻�����һ����һ���������� parent��
2. ��ǰͼ���л�������һ������������ parent��
3. ��ǰͼ���л��������ж��㶼ֻ��һ�� parent��

������һ������ v ������ parent���������� parent �� root �Ƿ���ͬ��
	1. ����ͬ����˵���޻���ɾ������һ�� parent->v ���ɣ���ĿҪ�󣬰��� edges ������ѡ��
	2. ����ͬ����˵�����ڻ�����ʱ���ϵ�ĳ���ڵ�����������ڵ㣨һ�����ڵ��ڻ��ϣ�һ�����ڻ��ϣ���������Ҫɾ���Ǹ����ϵĸ��ڵ㡣
	��ɾ����һ�� parent->v������ɾ����� parent->v��
�����ж��㶼ֻ��һ�� parent���������ڵ� u �����������丸�ڵ㷽�����ϱ�����һ����õ����� Example 2: 5,1,4,3,2,1��
�� 1,4,3,2 һ���ǻ��ϵ����нڵ��ˡ�������� edges �в�������������� 1,4,3,2 �еĵ�һ���ߣ���Ϊ����

*/

#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "HelpFunc.h"

using namespace std;

class Solution {
public:
	int n;	// �ڵ����
	vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges)
	{
		n = edges.size();
		vector<vector<int>> parent(n + 1);
		for (auto & edge : edges)
			parent[edge.back()].push_back(edge.front());

		// ���Ҿ����������ڵ�Ķ���
		int v = 0;	
		for (int i = 1; i <= n; ++i)
		{
			if (parent[i].size() == 2)
				v = i;
		}
		//////////////////////////////////////////////////////////////////////////
		// ������ھ����������ڵ�Ľڵ�
		if (v != 0)
		{
			vector<int> two_parents = parent[v];	// �������ڵ�
			vector<int> two_roots(two_parents);		// �������ڵ㷽������ֱ�����ڵ�
			for (int i = 0; i < 2; ++i)
			{
				while (parent[two_roots[i]].size() == 1) // ������ two_parents[i] ������ڻ������ص��ڵ� v ��ֹͣ
					two_roots[i] = parent[two_roots[i]][0];
			}

			// case 1. ���������ڵ�ĸ��ڵ���ͬ��˵��ͼ�޻���ɾ�� edges �����ں�����Ǹ��߼��ɡ������� parent[v] ���Ǹ��ڵ�ָ�� v �ı�
			if (two_roots[0] == two_roots[1])
				return { two_parents[1], v };
			// case 2. ����������ڵ�ĸ��ڵ㲻ͬ��˵���л���ɾ���Ǹ��ڻ��еĸ��ڵ㵽v�ı�
			else
			{
				if (two_roots[0] == v)
					return { two_parents[0], v };
				else
					return { two_parents[1], v };
			}
		}

		//////////////////////////////////////////////////////////////////////////
		// case 3. ��������ھ����������ڵ�Ľڵ㣬��һ�����ڻ�
		// �������нڵ�ֻ��һ�����ڵ㣬����Դ�����ڵ�������� parent �������Ϸ��ʣ�
		// ֱ���ظ����ʵ�ĳ���ڵ㣬������ظ��ڵ������еĽڵ㼴Ϊ�������нڵ㡣
		vector<int> loop;
		unordered_set<int> visited;
		int u = 1;
		// ѭ��������u�����Ǹ��ظ��Ľڵ�
		while (visited.find(u) == visited.end())
		{
			visited.insert(u);
			loop.push_back(u);
			u = parent[u].front();
		}
		unordered_set<int> vertex_in_loop;		// ���еĽڵ�
		auto start_iter = find(loop.begin(), loop.end(), u);
		for (auto it = start_iter; it != loop.end(); ++it)
			vertex_in_loop.insert(*it);
		//�� edges �����������������ڻ��еıߣ���Ϊ����
		for (auto it = edges.rbegin(); it != edges.rend(); ++it)
		{
			if (vertex_in_loop.find(it->front()) != vertex_in_loop.end()
				&& vertex_in_loop.find(it->back()) != vertex_in_loop.end())
				return *it;
		}
	}
};