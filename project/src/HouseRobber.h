#pragma once

/*

198. House Robber

You are a professional robber planning to rob houses along a street. 
Each house has a certain amount of money stashed, the only constraint 
stopping you from robbing each of them is that adjacent houses have 
security system connected and it will automatically contact the police 
if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, 
determine the maximum amount of money you can rob tonight without alerting the police.

Approach:

DP
Rob[i] (i = 0,...,num.size()-1) 表示从第0家抢劫到第i家（第i家必须抢），在不惊动警察所能得到的最大收益
为了获得最大收益，当抢劫第i家时，必须抢劫第 i-2 和 i-3 中的一家，故：
Rob[i] = max(Rob[i-2], Rob[i-3]) + num[i]
if i < 0, Rob[i] = 0
O(N) time, O(N) space

Approach_v2:

DP
For every house k, there are two options: either to rob it (include this house: i) or not rob it (exclude this house: e).

Include this house:
i = num[k] + e (money of this house + money robbed excluding the previous house)

Exclude this house:
e = max(i, e) (max of money robbed including the previous house or money robbed excluding the previous house)
(note that i and e of the previous step, that’s why we use tmp here to store the previous i when calculating e, to make O(1) space)

*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int rob(vector<int>& nums)
	{
		vector<int> Rob(nums.size(), 0);

		for (int i = 0; i < nums.size(); ++i)
		{
			if (i < 2)
				Rob[i] = nums[i];
			else if (i == 2)
				Rob[i] = Rob[i - 2] + nums[i];
			else
				Rob[i] = max(Rob[i - 2], Rob[i - 3]) + nums[i];
		}

		// 没有人家
		if (Rob.size() == 0)
			return 0;
		// 只有1家
		else if (Rob.size() == 1)
			return Rob[0];
		// 有n(n>1)家时，返回 Rob[n-1] 与 Rob[n-2] 中的较大者
		else
			return max(Rob[Rob.size() - 1], Rob[Rob.size() - 2]);
	}
};

class Solution_v2 {
public:
	int rob(vector<int>& nums)
	{
		int i = 0;
		int e = 0;
		for (int k = 0; k < nums.size(); ++k)
		{
			int temp = i;
			i = e + nums[k];
			e = max(e, temp);
		}

		return max(i, e);
	}
};