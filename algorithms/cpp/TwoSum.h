#pragma once

/*

1. Two Sum

Related Topics:  Array, Hash Table

Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].

Approach 1:
iterate nums, set nums[i] -> firstNum,
Lookup target-firstNum in the nums[i-1,...,nums.size()-1]
use vector and find()

Approach 2:
use unordered_map to speed up the find process
the unordered_map is built along with the main loop.

*/

#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target)
	{
		vector<int> result;

		for (unsigned i = 0; i < nums.size(); i++)
		{
			// this step is time consuming, consider use a map to speed up
			auto numsIter = find(nums.begin() + i + 1, nums.end(), target - nums[i]);
			if (numsIter != nums.end())
			{
				result.push_back(i);
				result.push_back(numsIter - nums.begin());
				return result;
			}
		}
		return result;
	}

	// use map to speed up
	vector<int> twoSum_v2(vector<int> &nums, int target)
	{
		unordered_map<int, int> num2Index;
		vector<int> result;

		for (unsigned i = 0; i < nums.size(); i++)
		{
			auto secondNumIter = num2Index.find(target - nums[i]);
			if (secondNumIter != num2Index.end())
			{
				result.push_back((*secondNumIter).second);
				result.push_back(i);
				break;
			}
			num2Index[nums[i]] = i;
		}
		return result;
	}
};
