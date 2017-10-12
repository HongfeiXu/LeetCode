#pragma once

/*

561. Array Partition I

Given an array of 2n integers, your task is to group these integers into n pairs of integer, 
say (a1, b1), (a2, b2), ..., (an, bn) which makes sum of min(ai, bi) for all i from 1 to n as large as possible.

Example 1:
Input: [1,4,3,2]

Output: 4
Explanation: n is 2, and the maximum sum of pairs is 4 = min(1, 2) + min(3, 4).
Note:
n is a positive integer, which is in the range of [1, 10000].
All the integers in the array will be in the range of [-10000, 10000].

Approach:
1 7 3 6 2 5
1 2 3 5 6 7
1 + 3 + 6 = 10 is the result

use sort O(nlgn)

Approach COOL:
Bucket Sort can sort an integer array in linear time when we know the scope of all the integers.
kind of exchange time with space
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int arrayPairSum(vector<int>& nums)
	{
		int result = 0;
		sort(nums.begin(), nums.end());

		for (int i = 0; i < nums.size() / 2; i++)
		{
			result += nums[i * 2];
		}
		return result;
	}

	int arrayPairSum_Bucket(vector<int>& nums)
	{
		vector<int> bucket(20001, 0);
		for (auto i : nums) ++bucket[i + 10000];

		int sum = 0;
		int count = 0;
		int i = 0;
		while (count < nums.size())
		{
			if (bucket[i] == 0)
				i++;
			else
			{
				if (count % 2 == 0)
					sum += i - 10000;
				--bucket[i];
				++count;
			}
		}
		return sum;
	}
};