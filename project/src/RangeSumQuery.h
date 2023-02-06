#pragma once

/*

303. Range Sum Query - Immutable

Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

Example:
Given nums = [-2, 0, 3, -5, 2, -1]

sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3

Note:
You may assume that the array does not change.
There are many calls to sumRange function.

Approach:
DP构造sum[0..n]，且
	sum[i] = nums[0] + nums[1] + ... + nums[i-1] = s[i-1] + nums[i-1]
	s[0] = 0
则 sumRange(i,j) = sum[j + 1] - sum[i]

*/

#include <vector>

using namespace std;

class NumArray {
private:
	vector<int> sum;		// sum[i] = num[0] + num[1] + ... + num[i-1]

public:
	NumArray(vector<int> nums)
	{
		sum.assign(nums.size() + 1, 0);
		for (int i = 1; i < sum.size(); ++i)
			sum[i] = sum[i - 1] + nums[i-1];
	}

	// sumRange(i,j) = sum[j + 1] - sum[i]
	int sumRange(int i, int j)
	{
		return sum[j + 1] - sum[i];
	}
};

/**
* Your NumArray object will be instantiated and called as such:
* NumArray obj = new NumArray(nums);
* int param_1 = obj.sumRange(i,j);
*/