#pragma once

/*

169. Majority Element

Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.

You may assume that the array is non-empty and the majority element always exist in the array.

Approach My:
Use map<int, int> to map nums[i] to it's appear time
count and find
O(n) time and O(n) space


Approach WOW:
the majority element appears more than  ⌊ n/2 ⌋ times
O(n) time and O(1) space

*/

#include <vector>
#include <map>

using namespace std;

class Solution {
public:
	int majorityElement(vector<int>& nums)
	{
		map<int, int> m;	// map nums[i] to it's appear time

		for (size_t i = 0; i < nums.size(); i++)
			m[nums[i]] = 0;
		for (size_t i = 0; i < nums.size(); i++)
		{
			m[nums[i]]++;
		}

		for (auto it = m.begin(); it != m.end(); it++)
		{
			if ((*it).second > static_cast<int>(nums.size()) / 2)
				return (*it).first;
		}

		return 0;
	}

	int majorityElement_v2(vector<int>& nums)
	{
		int curr = 0;
		int cnt = 1;
		for (int i = 1; i < static_cast<int>(nums.size()); i++)
		{
			if (nums[i] == nums[curr])
				cnt++;
			else
			{
				cnt--;
				if (cnt == 0)
				{
					curr = i;
					cnt = 1;
				}
			}
		}
		return nums[curr];
	}
};