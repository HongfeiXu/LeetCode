#pragma once

/*

665. Non-decreasing Array

Given an array with n integers, your task is to check if it could become non-decreasing by modifying at most 1 element.

We define an array is non-decreasing if array[i] <= array[i + 1] holds for every i (1 <= i < n).

Example 1:
Input: [4,2,3]
Output: True
Explanation: You could modify the first
4
to
1
to get a non-decreasing array.
Example 2:
Input: [4,2,1]
Output: False
Explanation: You can't get a non-decreasing array by modify at most one element.
Note: The n belongs to [1, 10,000].

Approach:

This problem is like a greedy problem. When you find nums[i-1] > nums[i] for some i, 
you will prefer to change nums[i-1]'s value, since a larger nums[i] will give you more risks 
that you get inversion errors after position i. But, if you also find nums[i-2] > nums[i], 
then you have to change nums[i]'s value instead, or else you need to change both of nums[i-2]'s and nums[i-1]'s values.

6 2 ... -> 2 2 ...
3 6 2 ... -> 3 6 6 ...
3 6 5 ... -> 3 5 5 ... 或者 3 3 5 ...
After modify one element, if the array is sorted, return true. Otherwise, return false.

*/

#include <vector>

using namespace std;

class Solution {
public:
	bool checkPossibility(vector<int>& nums)
	{
		bool modified = false;
		for (int i = 1; i < static_cast<int> (nums.size()); i++)
		{
			if (nums[i] < nums[i - 1])
			{
				if (modified++)		// if the array already has been modified, return false.
					return false;
				if (i - 2 < 0 || nums[i - 2] <= nums[i])	// note: nums[i-2] < nums[i] is not correct. i.e. 3 6 3 4
					nums[i - 1] = nums[i];
				else
					nums[i] = nums[i - 1];
			}
		}
		return true;
	}
};