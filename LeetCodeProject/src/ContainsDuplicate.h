#pragma once

/*

217. Contains Duplicate

Given an array of integers, find if the array contains any duplicates. 
Your function should return true if any value appears at least twice in the array, 
and it should return false if every element is distinct.

*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	bool containsDuplicate(vector<int>& nums)
	{
		sort(nums.begin(), nums.end());

		auto last = unique(nums.begin(), nums.end());
		return last != nums.end();
	}
};