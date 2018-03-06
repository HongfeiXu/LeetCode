#pragma once

/*

332. Reconstruct Itinerary

Given a list of airline tickets represented by pairs of departure and arrival airports [from, to], 
reconstruct the itinerary in order. All of the tickets belong to a man who departs from JFK. 
Thus, the itinerary must begin with JFK.

Note:
1. If there are multiple valid itineraries, you should return the itinerary that has the 
smallest lexical order when read as a single string. For example, the itinerary 
["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].

2. All airports are represented by three capital letters (IATA code).

3. You may assume all tickets form at least one valid itinerary.

Example 1:
tickets = [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
Return ["JFK", "MUC", "LHR", "SFO", "SJC"].
Example 2:
tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Return ["JFK","ATL","JFK","SFO","ATL","SFO"].
Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"]. But it is larger in lexical order.

Approach:

这里需要访问完所有的边。（用光所有的机票）
Ref(DFS, recursive): https://leetcode.com/problems/reconstruct-itinerary/discuss/78768/Short-Ruby-Python-Java-C++
Solution v1
Ref(DFS, iterative): https://leetcode.com/problems/reconstruct-itinerary/discuss/78832/Short-C++-DFS-iterative-44ms-solution-with-explanation.-No-recursive-calls-no-backtracking.
Solution v2

Just Eulerian path. Greedy DFS, building the route backwards when retreating.

*/

#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
#include <set>
#include <stack>

using namespace std;

class Solution {
public:
	vector<string> findItinerary(vector<pair<string, string>> tickets)
	{
		vector<string> result;
		if (tickets.empty())
			return result;

		// 用 multiset 保存可以到达的机场，则自动按照字典序升序排列
		unordered_map<string, multiset<string>> um;		
		for (auto & ticket : tickets)
			um[ticket.first].insert(ticket.second);

		dfs(string("JFK"), result, um);

		// 逆序返回
		return vector<string>(result.rbegin(), result.rend());
	}

	void dfs(const string& curr_pos, vector<string>& result, unordered_map<string, multiset<string>>& um)
	{
		while (!um[curr_pos].empty())
		{
			string next_pos = *um[curr_pos].begin();
			um[curr_pos].erase(um[curr_pos].begin());
			dfs(next_pos, result, um);
		}
		// 所有出边被访问完，才轮到当前节点
		result.push_back(curr_pos);
	}
};

class Solution_v2 {
public:
	vector<string> findItinerary(vector<pair<string, string>> tickets)
	{
		// We are always appending the deepest node to the itinerary,
		vector<string> result;
		if (tickets.empty())
			return result;
		
		unordered_map<string, multiset<string>> um;
		for (auto & ticket : tickets)
			um[ticket.first].insert(ticket.second);

		stack<string> dfs;
		dfs.push("JFK");
		while (!dfs.empty())
		{
			string top_airport = dfs.top();
			// 如果还有出边
			if (!um[top_airport].empty())
			{
				// 选择字典序最小的出边，加入dfs，下一次循环将会访问该新加入的点（DFS）
				dfs.push(*um[top_airport].begin());
				// 并从出边中删除这一条
				um[top_airport].erase(um[top_airport].begin());
			}
			// 如果没有出边
			else
			{
				// 将节点加入 result
				result.push_back(top_airport);
				// 将该节点从 dfs 中弹出
				dfs.pop();
			}
		}
		return vector<string>(result.rbegin(), result.rend());
	}
};