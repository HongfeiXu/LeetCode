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

˼�룺

���� equations �� values ������Ȩ����ͼ G���� u->v ��ȨֵΪ u/v��������ָ������ value ��Ϊ���������� u/v ������ v/u �ض����ڣ�
�� v->u ��ȨֵΪ v/u��

���� queries �е� x/y��
��� x �� y ������һ������ͼ�г��֣��򷵻� -1.0
���򣬲��� x �� y ��·������DFS�������룩
	��·������ x->a->b->y �� x/y = x/a * a/b * b/y
	��·�������ڣ��� x/y = -1.0

Approach v2:

���������ƣ��������ﲻ��ʾ�����·�������ǽ��еݹ���ʽ�� dfs��
���յݹ�ʽ from/to = from/neighbor.first * neighbor.first/to�������ǰ neighbor �����ڵ��� to ��·�����򿼲���һ�� neighbor��
���ȫ�� neighbor ��������ϣ��޷�����  to����˵�� from �޷����� to������0.

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
			// �� x ���� y ����һ��������
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

			// x, y ����
			if (g[query.first].find(query.second) != g[query.first].end())
			{
				result.push_back(g[query.first][query.second]);
				continue;
			}
			
			// Ѱ�� x �� y ��·�������ܲ����ڣ�
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

	// ʹ���������������ʽ���ҵ� x �� y ��·�� path�������������Ϊ��
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
			// ���ҵ�Ŀ��ڵ㣬���˳�ѭ������ջ�׵�ջ����Ϊ x �� y ��һ��
			if(curr_node == y)
				break;
			bool found = false;	// curr_node �Ƿ���û�б����ʵ��ھ�
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
			// curr_node �������ھӽڵ㶼�����ʹ�����û�з��� y �ڵ㣬�� curr_node һ�����ٴ� x �� y �� path ��
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

	// �ݹ���� from/to����������ڣ����� 0��from �� to ����ͼ�У�from == to ������ֱ�� handle��
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
				// �� neighbor.first / to
				double temp = dfs(neighbor.first, to, visited, g);
				// ��temp != 0��˵������·�����ʣ�from/to = from/neighbor.first * neighbor.first/to��ֱ�ӷ���
				if (temp != 0)
					return temp * g[from][neighbor.first];
			}
		}
		// ����� from ������ to���򣬷��� 0
		return 0;
	}
};
