#pragma once

/*

674. Longest Continuous Increasing Subsequence

Related Topics: Array

Given an unsorted array of integers, find the length of longest continuous increasing subsequence.

Input: [1,3,5,4,7]
Output: 3
Explanation: The longest continuous increasing subsequence is [1,3,5], its length is 3.
Even though [1,3,5,7] is also an increasing subsequence, it's not a continuous one where 5 and 7 are separated by 4.

*/

#include <vector>

using namespace std;

class Solution {
public:
	int findLengthOfLCIS(vector<int>& nums)
	{
		if (nums.empty())
			return 0;

		int result = 1;			// 记录结果
		int temp_result = 1;	// 记录当前正在访问的连续递增数字的长度

		for (unsigned i = 0; i < nums.size() - 1; i++)
		{
			if (nums[i] < nums[i + 1])
			{
				temp_result++;
				if (temp_result > result)
					result = temp_result;
			}
			else
			{
				temp_result = 1;
			}
		}

		return result;
	}
};