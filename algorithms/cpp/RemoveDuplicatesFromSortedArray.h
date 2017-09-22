#pragma once

/*

26. Remove Duplicates from Sorted Array

Related Topics: Array

Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.
Do not allocate extra space for another array, you must do this in place with constant memory.
For example,
Given input array nums = [1,1,2],

Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively. It doesn't matter what you leave beyond the new length.

Approach:
use STL alogrithm: unique
kind of cheating

Approach v2:
iterate, set target, jump, move..

Approach v3:
simple code, easy to read, and effective

*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int removeDuplicates(vector<int>& nums)
	{
		auto end_unique = unique(nums.begin(), nums.end());
		return end_unique - nums.begin();
	}

	int removeDuplicates_v2(vector<int>& nums)
	{
		int removeNumsCnt = 0;
		int target = -1;
		for (unsigned i = 1; i < nums.size(); i++)
		{
			if (nums[i] == nums[i - 1])
			{
				// find the first target index
				if(target < 0)
					target = i;
				// count the duplicated number and jump to the next different number
				while (i < nums.size() && nums[i] == nums[i - 1])
				{
					removeNumsCnt++;
					i++;
				}
			}
			// move number to target index
			if (target > 0 && i < nums.size())
			{
				nums[target] = nums[i];
				target++;
			}
		}
		return nums.size() - removeNumsCnt;
	}

	int removeDuplicates_v3(vector<int>& nums)
	{
		if (nums.size() < 2)
			return nums.size();

		// start from nums[1]
		int target = 1;
		for (int i = 1; i < nums.size(); i++)
		{
			if (nums[i] != nums[i - 1])
			{
				nums[target] = nums[i];
				target++;
			}
		}
		return target;
	}
};