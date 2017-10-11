#pragma once

/*

643. Maximum Average Subarray I

Given an array consisting of n integers, find the contiguous subarray of given length k that has the maximum average value. 
And you need to output the maximum average value.

Example 1:
Input: [1,12,-5,-6,50,3], k = 4
Output: 12.75
Explanation: Maximum average is (12-5-6+50)/4 = 51/4 = 12.75
Note:
1 <= k <= n <= 30,000.
Elements of the given array will be in the range [-10,000, 10,000].

Approach: a very Silly way, direct way, BUT Time Limit Exceeded!

Approach: simple sliding-window solution

*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	double findMaxAverage(vector<int>& nums, int k)
	{
		double maxAverage = 0;

		for (int i = 0; i <= static_cast<int> (nums.size()) - k; i++)
		{
			double currAverage = 0;
			for (int j = i; j < i + k; j++)
			{
				currAverage += nums[j];
			}
			if (i == 0)
				maxAverage = currAverage;
			maxAverage = max(maxAverage, currAverage);
		}

		return maxAverage / k;
	}

	double findMaxAverage_v2(vector<int>& nums, int k)
	{
		double currSum = 0;
		double maxSum = INT_MIN;
		for (int i = 0; i < static_cast<int>(nums.size()); i++)
		{
			if (i < k)
				currSum += nums[i];
			else
			{
				maxSum = max(maxSum, currSum);
				currSum += nums[i] - nums[i - k];
			}
		}
		maxSum = max(maxSum, currSum);
		return maxSum / k;
	}
};