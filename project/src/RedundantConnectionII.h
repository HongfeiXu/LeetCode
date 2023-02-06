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
有三种可能情况：

https://discuss.leetcode.com/assets/uploads/files/1507232873325-screen-shot-2017-10-05-at-2.25.34-pm-resized.png

1. 当前图中无环，则一定有一个顶点两个 parent。
2. 当前图中有环，且有一个顶点有两个 parent。
3. 当前图中有环，且所有顶点都只有一个 parent。

若存在一个顶点 v 有两个 parent，看这两个 parent 的 root 是否相同，
	1. 若相同，则说明无环，删除任意一个 parent->v 均可（题目要求，按照 edges 的逆序，选择）
	2. 若不同，则说明存在环，这时环上的某个节点具有两个父节点（一个父节点在环上，一个不在环上），我们需要删除那个环上的父节点。
	故删除另一个 parent->v，否则，删除这个 parent->v。
若所有顶点都只有一个 parent，则从任意节点 u 出发，沿着其父节点方向向上遍历，一定会得到类似 Example 2: 5,1,4,3,2,1，
则 1,4,3,2 一定是环上的所有节点了。按逆序从 edges 中查找两个顶点均在 1,4,3,2 中的第一条边，即为所求。

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
	int n;	// 节点个数
	vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges)
	{
		n = edges.size();
		vector<vector<int>> parent(n + 1);
		for (auto & edge : edges)
			parent[edge.back()].push_back(edge.front());

		// 查找具有两个父节点的顶点
		int v = 0;	
		for (int i = 1; i <= n; ++i)
		{
			if (parent[i].size() == 2)
				v = i;
		}
		//////////////////////////////////////////////////////////////////////////
		// 如果存在具有两个父节点的节点
		if (v != 0)
		{
			vector<int> two_parents = parent[v];	// 两个父节点
			vector<int> two_roots(two_parents);		// 两个父节点方向向上直到根节点
			for (int i = 0; i < 2; ++i)
			{
				while (parent[two_roots[i]].size() == 1) // 若沿着 two_parents[i] 方向存在环，则会回到节点 v 处停止
					two_roots[i] = parent[two_roots[i]][0];
			}

			// case 1. 若两个父节点的根节点相同，说明图无环，删除 edges 中排在后面的那个边即可。即后入 parent[v] 的那个节点指向 v 的边
			if (two_roots[0] == two_roots[1])
				return { two_parents[1], v };
			// case 2. 如果两个父节点的根节点不同，说明有环，删除那个在环中的父节点到v的边
			else
			{
				if (two_roots[0] == v)
					return { two_parents[0], v };
				else
					return { two_parents[1], v };
			}
		}

		//////////////////////////////////////////////////////////////////////////
		// case 3. 如果不存在具有两个父节点的节点，则一定存在环
		// 由于所有节点只有一个父节点，则可以从任意节点出发，按 parent 方向向上访问，
		// 直到重复访问到某个节点，则这个重复节点中所夹的节点即为环中所有节点。
		vector<int> loop;
		unordered_set<int> visited;
		int u = 1;
		// 循环结束后u保存那个重复的节点
		while (visited.find(u) == visited.end())
		{
			visited.insert(u);
			loop.push_back(u);
			u = parent[u].front();
		}
		unordered_set<int> vertex_in_loop;		// 环中的节点
		auto start_iter = find(loop.begin(), loop.end(), u);
		for (auto it = start_iter; it != loop.end(); ++it)
			vertex_in_loop.insert(*it);
		//按 edges 逆序查找两个顶点均在环中的边，即为所求
		for (auto it = edges.rbegin(); it != edges.rend(); ++it)
		{
			if (vertex_in_loop.find(it->front()) != vertex_in_loop.end()
				&& vertex_in_loop.find(it->back()) != vertex_in_loop.end())
				return *it;
		}
	}
};