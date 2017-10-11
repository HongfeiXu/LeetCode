#pragma once

/*

268. Missing Number

Related Topics: Array, Math, Bit Manipulation

Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.

For example,
Given nums = [0, 1, 3] return 2.

Note:
Your algorithm should run in linear runtime complexity. Could you implement it using only constant extra space complexity

Approach My:
Time O(n)
Space O(n)

Approach COOL

Bit Manipulation
XOR (all numbers in nums array and 0, 1, ..., n)
Each number in [0, 1, ... n] have two occurrences except the missing number. 
So the result is the missing number. The same idea as the solution to "single number".

Time O(n)
Space O(1)

*/

#include <vector>

using namespace std;

class Solution {
public:
	int missingNumber(vector<int>& nums)
	{
		vector<int> times(nums.size() + 1);

		for (size_t i = 0; i < nums.size(); i++)
		{
			times[nums[i]]++;
		}
		auto it = find(times.begin(), times.end(), 0);
		return it - times.begin();
	}

	int missingNumber_v2(vector<int>& nums)
	{
		int result = nums.size();
		for (size_t i = 0; i < nums.size(); i++)
		{
			result ^= nums[i];
			result ^= i;
		}

		return result;
	}
};