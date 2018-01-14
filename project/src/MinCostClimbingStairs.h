#pragma once

/*

746. Min Cost Climbing Stairs

On a staircase, the i-th step has some non-negative cost cost[i] assigned (0 indexed).

Once you pay the cost, you can either climb one or two steps. 
You need to find minimum cost to reach the top of the floor, 
and you can either start from the step with index 0, or the step with index 1.

Example 1:
Input: cost = [10, 15, 20]
Output: 15
Explanation: Cheapest is start on cost[1], pay that cost and go to the top.

Example 2:
Input: cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
Output: 6
Explanation: Cheapest is start on cost[0], and only step on 1s, skipping cost[3].

Note:
1. cost will have a length in the range [2, 1000].
2. Every cost[i] will be an integer in the range [0, 999]

Approach:
DP

Target: MinCost[cost.size()]

MinCost[i], i = 1,2,3,...,cost.size().
分析题目，每次可以上行一或者两级阶梯。则
问题的递归表示：
MinCost[i] = min{MinCost[i-1] + cost[i-1], MinCost[i-2] + cost[i-2]}
具有重叠的子问题，应用 DP 解决。
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int minCostClimbingStairs(vector<int>& cost)
	{
		// MinCost[0] = 0, MinCost[1] = 0
		vector<int> MinCost(cost.size() + 1, 0);

		for (int i = 2; i <= cost.size(); ++i)
			MinCost[i] = min(MinCost[i - 2] + cost[i - 2], MinCost[i - 1] + cost[i - 1]);
		
		return MinCost[cost.size()];
	}
};
