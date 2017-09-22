#pragma once

/*

189. Rotate Array

Related Topics: Array

Rotate an array of n elements to the right by k steps.
For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated to [5,6,7,1,2,3,4].

Approach 1:
use a list, pop_back and push_front

Approach 2:
k = 3, rotate array [1,2,3,4,5,6,7]
<==>
rotate 1,2,3,4 => 4,3,2,1
rotate 5,6,7 => 7,6,5
=> 4,3,2,1,7,6,5
rotate
=> 5,6,7,1,2,3,4

*/

#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class Solution {
public:
	void rotate(vector<int>& nums, int k)
	{
		list<int> q(nums.begin(), nums.end());
		for (int i = 0; i < k; i++)
		{
			int temp = q.back();
			q.pop_back();
			q.push_front(temp);
		}

		nums.assign(q.begin(), q.end());
	}

	// mirror the nums elem from nums[start] to nums[end-1]
	void mirror(vector<int>& nums, int start, int end)
	{
		int middle = (start + end) / 2;
		for (int i = start; i < middle; i++)
		{
			swap(nums[i], nums[--end]);
		}
	}

	void rotate_v2(vector<int>& nums, int k)
	{
		int numsSize = nums.size();
		k = k % numsSize;
		int leftSwap = numsSize - k;
		int rightSwap = k;

		mirror(nums, 0, leftSwap);
		mirror(nums, leftSwap, numsSize);
		mirror(nums, 0, numsSize);
	}
};