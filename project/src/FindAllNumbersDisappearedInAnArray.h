#pragma once

/*

448. Find All Numbers Disappeared in an Array

Related Topics: Array

Given an array of integers where 1 ¡Ü a[i] ¡Ü n (n = size of array), some elements appear twice and others appear once.
Find all the elements of [1, n] inclusive that do not appear in this array.
Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.

Example:

Input:
[4,3,2,7,8,2,3,1]

Output:
[5,6]

Approach:
use Index Sort method to count number appear time
The time is O(n)
But I use some extra space, like vector<int> temp

Approach(WOW, so Trickey):

use  negative sign to mark
The time is O(n)
use just one int extra space.

*/

#include <vector>

using namespace std;

class Solution {
public:
	vector<int> findDisappearedNumbers(vector<int>& nums)
	{
		vector<int> temp(nums.size() + 1, 0);
		for (int i = 0; i < nums.size(); i++)
		{
			temp[nums[i]]++;
		}

		vector<int> result;
		for (int i = 1; i < temp.size(); i++)
		{
			if (temp[i] == 0)
				result.push_back(i);
		}

		return result;
	}

	vector<int> findDisappearedNumbers_v2(vector<int>& nums)
	{
		int temp;
		for (unsigned i = 0; i < nums.size(); i++)
		{
			temp = abs(nums[i]) - 1;
			// use negative sign to mark temp + 1 is exist
			if (nums[temp] > 0)
				nums[temp] *= -1;
		}

		vector<int> result;
		for (unsigned i = 0; i < nums.size(); i++)
		{
			if (nums[i] > 0)
			{
				result.push_back(i + 1);
			}
		}
		return result;
	}
};