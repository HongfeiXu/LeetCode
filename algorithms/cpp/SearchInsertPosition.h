#pragma once

/*

35. Search Insert Position

Given a sorted array and a target value, return the index if the target is found. 
If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

Here are few examples.
[1,3,5,6], 5 ¡ú 2
[1,3,5,6], 2 ¡ú 1
[1,3,5,6], 7 ¡ú 4
[1,3,5,6], 0 ¡ú 0

Approach:
binary search

*/

#include <vector>

using namespace std;

class Solution {
public:
	int searchInsert(vector<int>& nums, int target)
	{
		int low = 0;
		int high = nums.size() - 1;
		int mid = 0;
		while (low <= high)
		{
			mid = (low + high) / 2;
			if (nums[mid] == target)
				return mid;
			else if (nums[mid] < target)
				low = mid + 1;
			else
				high = mid - 1;
		}

		return low;
	}
};