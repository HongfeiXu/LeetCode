#pragma once

/*

16. 3Sum Closest

Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. 
Return the sum of the three integers. You may assume that each input would have exactly one solution.

For example, given array S = {-1 2 1 -4}, and target = 1.
The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).

Approach:
Idea is similar to 3Sum

*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int threeSumClosest(vector<int>& nums, int target)
	{
		int result = 0;
		int tempResult;
		
		// we sort the nums
		sort(nums.begin(), nums.end());
		result = nums[0] + nums[1] + nums[2];

		for (int i = 0; i < static_cast<int>(nums.size()) - 2; i++)
		{
			if (i == 0 || (i > 0 && nums[i] != nums[i - 1]))
			{
				int low = i + 1;
				int high = nums.size() - 1;
				while (low < high)
				{
					tempResult = nums[i] + nums[low] + nums[high];
					if (tempResult == target)
						return tempResult;
					if (abs(tempResult - target) < abs(result - target))
						result = tempResult;
					if (tempResult < target)
						low++;
					else if (tempResult > target)
						high--;
				}
			}
		}

		return result;
	}
};
