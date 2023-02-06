#pragma once

/*

53. Maximum Subarray

Find the contiguous subarray within an array (containing at least one number) which has the largest sum.

For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
the contiguous subarray [4,-1,2,1] has the largest sum = 6.

Approach:
Idea is very simple. Basically, keep adding each integer to the sequence until the sum drops below 0.
If sum is negative, then should reset the sequence.

Approach: DP
Reference: https://discuss.leetcode.com/topic/6413/dp-solution-some-thoughts
very clear explanation

This is a optimization problem, which can be usually solved by DP.
So when it comes to DP, the first thing for us to figure out is the format of the sub problem.
The format of the sub problem can be helpful when we are trying to come up with recursive iteration.
......
So I change the format of the sub problem into something like: 
maxSubArray(int A[], int i), which means the maxSubArray for A[0:i ] which must has A[i] as the end element.
now the connect between the sub problem & the original one becomes clearer:

maxSubArray(A, i) = (maxSubArray(A, i - 1) > 0 ? maxSubArray(A, i - 1) : 0) + A[i];

Approach v3:

Kadane Algorithm
见 LargestSubContiguousSubarray.md

*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int maxSubArray(vector<int>& nums)
	{
		int maxSum = INT_MIN;
		int currSum = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			currSum += nums[i];
			maxSum = max(maxSum, currSum);
			currSum = max(currSum, 0);
		}
		return maxSum;
	}

	int maxSubArray_DP(vector<int>& nums)
	{
		vector<int> dp(nums.size());	// dp[i] means the maximum subarray ending with dp[i]
		dp[0] = nums[0];
		int maxSum = dp[0];

		for (int i = 1; i < nums.size(); i++)
		{
			dp[i] = (dp[i - 1] > 0 ? dp[i - 1] : 0) + nums[i];
			maxSum = max(maxSum, dp[i]);
		}
		return maxSum;
	}

	int maxSubArray_v3(vector<int>& nums)
	{
		int maxSum = nums[0];
		int currSum = nums[0];
		for (int i = 1; i < nums.size(); i++)
		{
			currSum = max(currSum + nums[i], nums[i]);
			maxSum = max(maxSum, currSum);
		}
		return maxSum;
	}
};