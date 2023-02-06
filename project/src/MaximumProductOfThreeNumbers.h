#pragma once

/*

628. Maximum Product of Three Numbers

Given an integer array, find three numbers whose product is maximum and output the maximum product.
Example 1:
Input: [1,2,3]
Output: 6
Example 2:
Input: [1,2,3,4]
Output: 24
Note:
The length of the given array will be in range [3,104] and all elements are in the range [-1000, 1000].
Multiplication of any three numbers in the input won't exceed the range of 32-bit signed integer.

Approach My way:
classified discussion, nlg(n) time

Approach New way:
要找最大的三个数的乘积，经过一定的分析，可以知道，我们只需要知道最大的三个数和最小的两个数，即可算得结果。
因为这里有负数的存在。
所以 My way 中的排序是费事不讨好的。
like 414. Third Maximum Number

*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int maximumProduct(vector<int>& nums)
	{
		if (nums.size() == 3)
			return nums[0] * nums[1] * nums[2];

		int nums_size = static_cast<int>(nums.size());
		
		sort(nums.begin(), nums.end());
		if (nums.front() >= 0)
			return nums[nums_size - 1] * nums[nums_size - 2] * nums[nums_size - 3];
		else if (nums.back() <= 0)
			return nums[0] * nums[1] * nums[2];
		else
		{
			int temp1 = nums[0] * nums[1] * nums[nums_size - 1];
			int temp2 = nums[nums_size - 1] * nums[nums_size - 2] * nums[nums_size - 3];

			return max(temp1, temp2);
		}
	}

	int maximumProduct_v2(vector<int>& nums)
	{
		int min1 = INT_MAX, min2 = INT_MAX;
		int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN;

		for (size_t i = 0; i < nums.size(); i++)
		{
			if (nums[i] < min1)
			{
				min2 = min1;
				min1 = nums[i];
			}
			else if (nums[i] < min2)
			{
				min2 = nums[i];
			}

			if (nums[i] > max1)
			{
				max3 = max2;
				max2 = max1;
				max1 = nums[i];
			}
			else if (nums[i] > max2)
			{
				max3 = max2;
				max2 = nums[i];
			}
			else if (nums[i] > max3)
			{
				max3 = nums[i];
			}
		}

		return max(min1 * min2 * max1, max1 * max2 * max3);
	}
};