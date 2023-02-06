#pragma once

/*

645. Set Mismatch

The set S originally contains numbers from 1 to n. But unfortunately, due to the data error, 
one of the numbers in the set got duplicated to another number in the set, 
which results in repetition of one number and loss of another number.

Given an array nums representing the data status of this set after the error. 
Your task is to firstly find the number occurs twice and then find the number that is missing. 
Return them in the form of an array.

Example 1:
Input: nums = [1,2,2,4]
Output: [2,3]
Note:
The given array size will in the range [2, 10000].
The given array's numbers won't have any order.

Approach:

构造一个 unordered_map
key: nums[i]
value: nums[i] 出现的次数

*/

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
	vector<int> findErrorNums(vector<int>& nums)
	{
		vector<int> result;
		unordered_map<int, int> num_to_cnt;
		for (size_t i = 0; i < nums.size(); ++i)
			++num_to_cnt[nums[i]];

		for (int i = 1; i <= nums.size(); ++i)
		{
			if (num_to_cnt[i] == 2)
				result.push_back(i);
		}
		for (int i = 1; i <= nums.size(); ++i)
		{
			if (num_to_cnt[i] == 0)
				result.push_back(i);
		}

		return result;
	}
};