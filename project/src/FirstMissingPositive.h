#pragma once

/*

41. First Missing Positive

Given an unsorted integer array, find the first missing positive integer.

For example,
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.

Your algorithm should run in O(n) time and uses constant space.

Approach:

Ref: https://leetcode.com/problems/first-missing-positive/discuss/17071/My-short-c++-solution-O(1)-space-and-O(n)-time

Put each number in its right place.

For example:

When we find 5, then swap it with A[4].

At last, the first place where its number is not right, return the place + 1.

*/

#include <vector>

using namespace std;

class Solution {
public:
	int firstMissingPositive(vector<int>& nums)
	{
		int n = nums.size();
		for (int i = 0; i < n; ++i)
		{
			while (nums[i] > 0 && nums[i] <= n && nums[i] != nums[nums[i]-1])
				swap(nums[i], nums[nums[i] - 1]);
		}
		for (int i = 0; i < n; ++i)
		{
			if (nums[i] != i + 1)
				return i + 1;
		}
		return n + 1;
	}
};
