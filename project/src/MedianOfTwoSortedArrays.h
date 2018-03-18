#pragma once

/*

4. Median of Two Sorted Arrays

There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

Example 1:
nums1 = [1, 3]
nums2 = [2]

The median is 2.0

Example 2:
nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5

Approach:

未结合二分查找
Time Complexity: O(min(m))
Space Complexity: O(1)

Approach_v2:
Ref: https://leetcode.com/problems/median-of-two-sorted-arrays/solution/
Ref: https://leetcode.com/problems/median-of-two-sorted-arrays/discuss/2481/Share-my-O(log(min(mn))-solution-with-explanation

Time Complexity: O(log(min(m, n)))
Space Complexity: O(1)

*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
	{
		// make nums1.size() <= nums2.size()
		if (nums1.size() > nums2.size())
			swap(nums1, nums2);
		int m = nums1.size(), n = nums2.size();
		int half_len = (m + n) / 2;
		int max_left = 0, min_right = 0;
		for (int i = 0; i <= m; ++i)
		{
			int j = half_len - i;
			if ((i == 0 || j == n || nums1[i - 1] <= nums2[j]) &&
				(j == 0 || i == m || nums2[j - 1] <= nums1[i]))
			{
				max_left = max(i > 0 ? nums1[i - 1] : INT_MIN, j > 0 ? nums2[j - 1] : INT_MIN);
				min_right = min(i < m ? nums1[i] : INT_MAX, j < n ? nums2[j] : INT_MAX);
				if ((m + n) % 2 == 0)
					return 0.5 * (max_left + min_right);
				else
					return static_cast<double>(min_right);
			}
		}
		return 0.0;
	}
};

class Solution_v2 {
public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
	{
		// make nums1.size() <= nums2.size()
		if (nums1.size() > nums2.size())
			swap(nums1, nums2);
		int m = nums1.size(), n = nums2.size();
		int half_len = (m + n) / 2;
		int max_left = 0, min_right = 0;
		int i_min = 0, i_max = m;
		while (i_min <= i_max)
		{
			int i = (i_min + i_max) / 2;
			int j = half_len - i;
			// i is perfect
			if ((i == 0 || j == n || nums1[i - 1] <= nums2[j]) &&
				(j == 0 || i == m || nums2[j - 1] <= nums1[i]))
			{
				max_left = max(i > 0 ? nums1[i - 1] : INT_MIN, j > 0 ? nums2[j - 1] : INT_MIN);
				min_right = min(i < m ? nums1[i] : INT_MAX, j < n ? nums2[j] : INT_MAX);
				if ((m + n) % 2 == 0)
					return 0.5 * (max_left + min_right);
				else
					return static_cast<double>(min_right);
			}
			// i is too big
			else if (i > 0 && nums1[i - 1] > nums2[j])
				--i_max;
			// i is too small
			else if (i < m && nums2[j - 1] > nums1[i])
				++i_min;
		}
		return 0.0;
	}
};
