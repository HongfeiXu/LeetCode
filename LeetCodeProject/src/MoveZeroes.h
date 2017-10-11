#pragma once


/*

283. Move Zeroes

Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

For example, given nums = [0, 1, 0, 3, 12], after calling your function, nums should be [1, 3, 12, 0, 0].

Note:
You must do this in-place without making a copy of the array.
Minimize the total number of operations.

*/

#include <vector>

using namespace std;

class Solution {
public:
	void moveZeroes(vector<int>& nums)
	{
		int target = 0;
		int i = 0;

		while (i < nums.size())
		{
			if (nums[i] != 0)
			{
				nums[target] = nums[i];
				target++;
			}
			++i;
		}

		for (int j = target; j < nums.size(); j++)
			nums[j] = 0;
	}
};