#pragma once

/*

88. Merge Sorted Array

Related Topics: Array

Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

Note:
You may assume that nums1 has enough space (size that is greater or equal to m + n) 
to hold additional elements from nums2. The number of elements initialized in nums1 and nums2 are m and n respectively.

Approach:
intuition, but use extral space O(m+n)

Approach no extral space:
use swap, to make nums1 have m smallest numbers, and nums2 has n biggerse numbers
both of them are sorted


Approach WOW:

no swap, just assign
from right to left, each time select the bigger number and put it to the end(from right to left)

Reference https://discuss.leetcode.com/topic/16946/4ms-c-solution-with-single-loop
This code relies on the simple observation that once all of the numbers from nums2 have been merged into nums1, 
the rest of the numbers in nums1 that were not moved are already in the correct place.



2 4 6 _ _
1 3
=>
2 4 6 _ 6
1 3
=>
2 4 6 4 6
1 3
=>
2 4 3 4 6
1 3
=>
2 2 3 4 6
1 3
=>
1 2 3 4 6
1 3

*/

#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

class Solution {
public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
	{
		vector<int> mergeResult;

		int i = 0, j = 0;
		for (i = 0, j = 0; i < m && j < n; )
		{
			if (nums1[i] <= nums2[j])
			{
				mergeResult.push_back(nums1[i]);
				i++;
			}
			else
			{
				mergeResult.push_back(nums2[j]);
				j++;
			}
		}
		if (i < m)
			copy(nums1.begin() + i, nums1.begin() + m, back_inserter(mergeResult));
		if (j < n)
			copy(nums2.begin() + j, nums2.begin() + n, back_inserter(mergeResult));
		nums1.assign(mergeResult.begin(), mergeResult.end());
	}

	void merge_v2(vector<int>& nums1, int m, vector<int>& nums2, int n)
	{
		if (n == 0)
			return;

		for (int i = 0; i < m; )
		{
			if (nums2[0] >= nums1[i])
				i++;
			else
			{
				// too many swaps, slow
				swap(nums2[0], nums1[i]);
				for (int j = 0; j < n - 1 && nums2[j] > nums2[j + 1]; j++)
				{
					swap(nums2[j], nums2[j + 1]);
				}
				i++;
			}
		}
		// copy nums2 to nums1
		for (int i = m; i < m + n; i++)
		{
			nums1[i] = nums2[i-m];
		}
	}

	void merge_v3(vector<int>& nums1, int m, vector<int>& nums2, int n)
	{
		// from right to left, compare and update nums1
		int i = m - 1;
		int j = n - 1;
		int target = m + n - 1;
		while (j >= 0)
		{
			// put the bigger one from right to left
			if (i >= 0 && nums1[i] > nums2[j])
			{
				nums1[target] = nums1[i];
				i--;
				target--;
			}
			else
			{
				nums1[target] = nums2[j];
				j--;
				target--;
			}
		}
	}
};