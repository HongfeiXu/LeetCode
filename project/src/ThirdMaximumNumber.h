#pragma once

/*

414. Third Maximum Number

Related Topics: Array

Given a non-empty array of integers, return the third maximum number in this array. 
If it does not exist, return the maximum number. The time complexity must be in O(n).

Example 1:
Input: [3, 2, 1]

Output: 1

Explanation: The third maximum is 1.
Example 2:
Input: [1, 2]

Output: 2

Explanation: The third maximum does not exist, so the maximum (2) is returned instead.
Example 3:
Input: [2, 2, 3, 1]

Output: 1

Explanation: Note that the third maximum here means the third maximum distinct number.
Both numbers with value 2 are both considered as second maximum.


Approach:
Bubble sort pattern
at least 3 time bubbling
2 2 3 1
2 2 1 3
2 1 2 3
1 2 2 3
then from right to left, get the third distinct number is the result
if there is no such number, return the rightmost number

Approach my old way:
Iterate, compare, and mark

Approach new way: WOW
a faster way to find 3 biggest numbers.

*/

#include <vector>
#include <algorithm>
#include "HelpFunc.h"

using namespace std;

class Solution {
	void bubbling(vector<int>& nums)
	{
		if (nums.empty())
			return;
		for (int i = 0; i < static_cast<int>(nums.size()) - 1; i++)
		{
			if (nums[i] > nums[i + 1])
				swap(nums[i], nums[i + 1]);
		}
	}

public:
	int thirdMax(vector<int>& nums)
	{
		switch (nums.size())
		{
		case 1:
			return nums[0];
			break;
		case 2:
			return max(nums[0], nums[1]);
			break;
		default:
			for (int i = 0; i < 3; ++i)
			{
				bubbling(nums);
			}

			int cnt = 1;	// 从高位到低位，找到第3大的数，当cnt==3时即为该数字。
			for (int j = nums.size() - 2; j >= 0; j--)
			{
				if (nums[j] != nums[j + 1])
					cnt++;
				else
					bubbling(nums);	// 有重复的数字，则需要进行额外的冒泡
				if (cnt == 3)
					return nums[j];
			}
			return nums.back();
			break;
		}
	}

	int thirdMax_v2(vector<int>& nums)
	{
		long max = LONG_MIN;
		long second_max = LONG_MIN;
		long third_max = LONG_MIN;
		for (unsigned i = 0; i < nums.size(); i++)
		{
			if (nums[i] == max || nums[i] == second_max)	// 去除重复的数字
				continue;
			if (nums[i] > max)
			{
				third_max = second_max;
				second_max = max;
				max = nums[i];
			}
			else if (nums[i] > second_max)
			{
				third_max = second_max;
				second_max = nums[i];
			}
			else if (nums[i] > third_max)
			{
				third_max = nums[i];
			}
		}
		if (third_max != LONG_MIN)
			return third_max;
		else
			return max;
	}
};