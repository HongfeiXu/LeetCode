#pragma once

/*

399. Evaluate Division

Equations are given in the format A / B = k, where A and B are variables represented as strings, 
and k is a real number (floating point number). Given some queries, return the answers. 
If the answer does not exist, return -1.0.

Example:
Given a / b = 2.0, b / c = 3.0.
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? .
return [6.0, 0.5, -1.0, 1.0, -1.0 ].

The input is: vector<pair<string, string>> equations, vector<double>& values, 
vector<pair<string, string>> queries , where equations.size() == values.size(), 
and the values are positive. This represents the equations. Return vector<double>.

According to the example above:

equations = [ ["a", "b"], ["b", "c"] ],
values = [2.0, 3.0],
queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ].
The input is always valid. You may assume that evaluating the queries 
will result in no division by zero and there is no contradiction.

Approach:

思想：

根据 equations 和 values 建立带权有向图 G，边 u->v 的权值为 u/v，（题中指出所有 value 均为正数，所以 u/v 存在则 v/u 必定存在）
则 v->u 的权值为 v/u。

对于 queries 中的 x/y，
如果 x 与 y 中任意一个不再图中出现，则返回 -1.0
否则，查找 x 到 y 的路径，（DFS，见代码）
	若路径存在 x->a->b->y 则， x/y = x/a * a/b * b/y
	若路径不存在，则 x/y = -1.0

Approach v2:

与上面类似，不过这里不显示的求出路径，而是进行递归形式的 dfs，
按照递归式 from/to = from/neighbor.first * neighbor.first/to，如果当前 neighbor 不存在到达 to 的路径，则考察下一个 neighbor，
如果全部 neighbor 都考察完毕，无法到达  to，则说明 from 无法到达 to，返回0.

*/

#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
	vector<double> calcEquation(vector<pair<string, string>> equations, 
								vector<double>& values, 
								vector<pair<string, string>> queries)
	{
		vector<double> result;

		unordered_map<string, unordered_map<string, double>> g;
		for (int i = 0; i < equations.size(); ++i)
		{
			g[equations[i].first].insert({ equations[i].second, values[i] });
			g[equations[i].second].insert({ equations[i].first, 1.0 / values[i] });
		}

		for (auto query : queries)
		{
			// 若 x 或者 y 中有一个不存在
			if (g.find(query.first) == g.end() || g.find(query.second) == g.end())
			{
				result.push_back(-1);
				continue;
			}

			// x == y
			if (query.first == query.second)
			{
				result.push_back(1.0);
				continue;
			}

			// x, y 相邻
			if (g[query.first].find(query.second) != g[query.first].end())
			{
				result.push_back(g[query.first][query.second]);
				continue;
			}
			
			// 寻找 x 到 y 的路径（可能不存在）
			vector<string> path = dfs(query.first, query.second, g);
			if (!path.empty())
			{
				double curr_result = 1.0;
				for (int i = 0; i < path.size() - 1; ++i)
					curr_result *= g[path[i]][path[i + 1]];
				result.push_back(curr_result);
			}
			else
				result.push_back(-1.0);
		}
		return result;
	}

	// 使用深度优先搜索方式，找到 x 到 y 的路径 path，如果不存在则为空
	vector<string> dfs(string x, string y, unordered_map<string, unordered_map<string, double>>& g)
	{
		vector<string> path;
		unordered_set<string> visited;
		stack<string> dfs;
		dfs.push(x);
		visited.insert(x);
		while (!dfs.empty())
		{
			string curr_node = dfs.top();
			// 若找到目标节点，则退出循环，从栈底到栈顶即为 x 到 y 的一条
			if(curr_node == y)
				break;
			bool found = false;	// curr_node 是否还有没有被访问的邻居
			for (auto neighbor : g[curr_node])
			{
				if (visited.find(neighbor.first) == visited.end())
				{
					dfs.push(neighbor.first);
					visited.insert(neighbor.first);
					found = true;
					break;
				}
			}
			// curr_node 的所有邻居节点都被访问过，且没有发现 y 节点，则 curr_node 一定不再从 x 到 y 的 path 上
			if (!found)
				dfs.pop();
		}
		if (!dfs.empty())
		{
			while (!dfs.empty())
			{
				path.push_back(dfs.top());
				dfs.pop();
			}
			reverse(path.begin(), path.end());
		}

		return path;
	}
};

class Solution_v2 {
public:
	vector<double> calcEquation(vector<pair<string, string>> equations, 
								vector<double>& values, 
								vector<pair<string, string>> queries)
	{
		unordered_map<string, unordered_map<string, double>> g;
		for (int i = 0; i < equations.size(); ++i)
		{
			g[equations[i].first].insert({ equations[i].second, values[i] });
			g[equations[i].second].insert({ equations[i].first, 1.0 / values[i] });

		}
		
		vector<double> result;
		for (int i = 0; i < queries.size(); ++i)
		{
			unordered_set<string> visited;
			double tmp = dfs(queries[i].first, queries[i].second, visited, g);
			if (tmp != 0)
				result.push_back(tmp);
			else
				result.push_back(-1);
		}
		return result;
	}

	// 递归求解 from/to，如果不存在，返回 0（from 或 to 不在图中，from == to 都可以直接 handle）
	// from/to = from/neighbor.first * neighbor.first/to
	double dfs(string from, string to, 
			   unordered_set<string>& visited, 
			   unordered_map<string, unordered_map<string, double>>& g)
	{
		if (g[from].find(to) != g[from].end())
			return g[from][to];

		visited.insert(from);
		for (auto neighbor : g[from])
		{
			if (visited.find(neighbor.first) == visited.end())
			{
				// 求 neighbor.first / to
				double temp = dfs(neighbor.first, to, visited, g);
				// 若temp != 0，说明存在路径，故，from/to = from/neighbor.first * neighbor.first/to，直接返回
				if (temp != 0)
					return temp * g[from][neighbor.first];
			}
		}
		// 如果从 from 到不了 to，则，返回 0
		return 0;
	}
};
