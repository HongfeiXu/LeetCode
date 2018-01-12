#pragma once

/*

594. Longest Harmonious Subsequence

We define a harmonious array is an array where the difference between its maximum value and its minimum value is exactly 1.

Now, given an integer array, you need to find the length of its longest harmonious subsequence among all its possible subsequences.

Example 1:
Input: [1,3,2,2,5,2,3,7]
Output: 5
Explanation: The longest harmonious subsequence is [3,2,2,2,3].

Approach:

use map<int, vector<int>> 与 vector<pair<int, vector<int>>>

Approach_v2:

简化了第一种方法，因为这里不许要最终输出子序列，没必要保存用来确定子序列信息的数字。

*/

#include <vector>
#include <map>
#include <utility>
#include <iterator>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
	int findLHS(vector<int>& nums)
	{
		// (K, V) = (number, number positions)
		map<int, vector<int>> num2pos;
		for (int i = 0; i < nums.size(); ++i)
			num2pos[nums[i]].push_back(i);

		vector<pair<int, vector<int>>> num2pos_vec;
		copy(num2pos.begin(), num2pos.end(), back_inserter(num2pos_vec));

		pair<int, int> LHS({ -1,-1 });
		pair<int, int> currHS;

		for (int i = 0; i < num2pos_vec.size() - 1; ++i)
		{
			if (num2pos_vec[i + 1].first - num2pos_vec[i].first == 1)
			{
				currHS.first = num2pos_vec[i].first;
				currHS.second = num2pos_vec[i + 1].first;

				if (LHS.first == -1)		// LHS 还没有有效内容，直接用 currHS 赋值
				{
					LHS = currHS;
				}
				else
				{
					if (num2pos[currHS.first].size() + num2pos[currHS.second].size() > num2pos[LHS.first].size() + num2pos[LHS.second].size())
						LHS = currHS;
				}
			}
		}
		return num2pos[LHS.first].size() + num2pos[LHS.second].size();
	}
};

class Solution_v2 {
public:
	int findLHS(vector<int>& nums)
	{
		map<int, int> num2appeartimes;
		for (auto n : nums)
			++num2appeartimes[n];

		vector<pair<int, int>> num2pos_vec;
		copy(num2appeartimes.begin(), num2appeartimes.end(), back_inserter(num2pos_vec));

		int LHS = 0;
		int currHS;

		for (int i = 0; i < static_cast<int>(num2pos_vec.size()) - 1; ++i)
		{
			int currNumber = num2pos_vec[i].first;
			int nextNumber = num2pos_vec[i + 1].first;
			if (nextNumber - currNumber == 1)
			{
				currHS = num2appeartimes[currNumber] + num2appeartimes[nextNumber];
				LHS = max(LHS, currHS);
			}
		}
		return LHS;
	}
};