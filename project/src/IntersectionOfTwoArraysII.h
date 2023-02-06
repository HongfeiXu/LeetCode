#pragma once

/*

350. Intersection of Two Arrays II

Given two arrays, write a function to compute their intersection.

Example:
Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2, 2].

Note:
Each element in the result should appear as many times as it shows in both arrays.
The result can be in any order.
Follow up:
What if the given array is already sorted? How would you optimize your algorithm?
What if nums1's size is small compared to nums2's size? Which algorithm is better?
What if elements of nums2 are stored on disk, and the memory is limited such that you cannot load all elements into the memory at once?


Approach:
使用两个 unordered_map 来分别记录 nums1、nums2 中数字及出现次数
对于那些共同存在的数字，出现次数较小的即为相交的部分。

Approach Follow up1:
What if the given array is already sorted? How would you optimize your algorithm?
见 Solution_v2。很nice的分类讨论方式。

What if nums1's size is small compared to nums2's size? Which algorithm is better?
显然，此时 Solution_v2 更合适，此方法中 nums2访问完后，就会结束运行。而Solution则需要构建完整的 unordered_map

What if elements of nums2 are stored on disk, and the memory is limited such that you cannot load all elements into the memory at once?

*/

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
	vector<int> intersect(vector<int>& nums1, vector<int>& nums2)
	{
		unordered_map<int, int> um_nums1;
		unordered_map<int, int> um_nums2;

		for (auto &item : nums1)
			++um_nums1[item];
		for (auto &item : nums2)
			++um_nums2[item];

		vector<int> result;
		for (auto &item : um_nums1)
		{
			if (um_nums2.find(item.first) != um_nums2.end())
			{
				int cnt = min(um_nums2[item.first], item.second);
				for (int i = 0; i < cnt; ++i)
					result.push_back(item.first);
			}
		}

		return result;
	}
};


class Solution_v2 {
public:
	vector<int> intersect(vector<int>& nums1, vector<int>& nums2)
	{
		vector<int> result;

		sort(nums1.begin(), nums1.end());
		sort(nums2.begin(), nums2.end());

		for (int i = 0, j = 0; i < nums1.size() && j < nums2.size();)
		{
			if (nums1[i] < nums2[j])
				++i;
			else if (nums1[i] > nums2[j])
				++j;
			else
			{
				result.push_back(nums1[i]);
				++i;
				++j;
			}
		}

		return result;
	}
};
