#pragma once

/*

485. Max Consecutive Ones

Related Topics: Array

Given a binary array, find the maximum number of consecutive 1s in this array.

Example 1:
Input: [1,1,0,1,1,1]
Output: 3
Explanation: The first two digits or the last three digits are consecutive 1s.
The maximum number of consecutive 1s is 3.

Note:
The input array will only contain 0 and 1.
The length of input array is a positive integer and will not exceed 10,000

Approach:
Iterate, compare, count

*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int findMaxConsecutiveOnes(vector<int>& nums)
	{
		int maxConsecutive = 0;
		int currentConsecutive = 0;

		for (int i = 0; i < nums.size(); i++)
		{
			if(nums[i] == 1)	// count 1
			{
				currentConsecutive++;
			}
			else
			{
				maxConsecutive = max(maxConsecutive, currentConsecutive);
				currentConsecutive = 0;
			}
		}
		// consider 10111, without this line of code, the result is 1
		maxConsecutive = max(maxConsecutive, currentConsecutive);


		return maxConsecutive;
	}
};