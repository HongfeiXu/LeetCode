#pragma once

/*

581. Shortest Unsorted Continuous Subarray

Given an integer array, you need to find one continuous subarray that if you only sort this subarray in ascending order, 
then the whole array will be sorted in ascending order, too.

You need to find the shortest such subarray and output its length.

Example 1:
Input: [2, 6, 4, 8, 10, 9, 15]
Output: 5
Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.
Note:
Then length of the input array is in range [1, 10,000].
The input array may contain duplicates, so ascending order here means <=.

Approach My:

找规律，两头挤，对于中间的那一段，确定最小值、最大值，在两边可能有在（最小值，最大值）范围内的数字，需要扩大重新sort的范围。
略慢的速度

Approach Better:
TODO

*/

#include <vector>

using namespace std;

class Solution {
public:
	int findUnsortedSubarray(vector<int>& nums)
	{
		// find the not sorted segment
		int start = 0;
		int end = static_cast<int>(nums.size()) - 1;

		while (start + 1 < nums.size() && nums[start] <= nums[start+1])
			start++;
		while (end - 1 >= 0 && nums[end] >= nums[end-1])
			end--;
		if (end <= start)
			return 0;
		
		// get min and max
		int min = INT_MAX;
		int max = INT_MIN;
		for (int i = start; i <= end; i++)
		{
			if (nums[i] < min)
				min = nums[i];
			if (nums[i] > max)
				max = nums[i];
		}

		// update start and end(expand to get Unsorted Continuous Subarray)
		for (int i = 0; i < start; i++)
		{
			if (nums[i] > min)
			{
				start = i;
				break;
			}
		}
		for (int i = nums.size() - 1; i > end; i--)
		{
			if (nums[i] < max)
			{
				end = i;
				break;
			}
		}

		return end - start + 1;
	}
};