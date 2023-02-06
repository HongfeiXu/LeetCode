#pragma once

/*

349. Intersection of Two Arrays

Given two arrays, write a function to compute their intersection.

Example:
Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2].

Note:
Each element in the result must be unique.
The result can be in any order.

Approach:

先排序，然后一同遍历

Approach_v2:

因为这里只保存一个重复字母，所以使用 unordered_set 来保存每个单词中的字母的一个副本


*/

#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Solution {
public:
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
	{
		sort(nums1.begin(), nums1.end());
		sort(nums2.begin(), nums2.end());
		vector<int> result;
		for (int i = 0, j = 0; i < nums1.size() && j < nums2.size();)
		{
			if (nums1[i] < nums2[j])
				++i;
			else if (nums1[i] > nums2[j])
				++j;
			else
			{
				result.push_back(nums1[i]);
				int k = i + 1;
				while (k < nums1.size() && nums1[i] == nums1[k])
					++k;
				i = k;
				k = j + 1;
				while (k < nums2.size() && nums2[j] == nums2[k])
					++k;
				j = k;
			}
		}
		return result;
	}
};

class Solution_v2 {
public:
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
	{
		vector<int> result;

		unordered_set<int> nums1_set;
		unordered_set<int> nums2_set;

		for (int i = 0; i < nums1.size(); ++i)
			nums1_set.insert(nums1[i]);
		for (int i = 0; i < nums2.size(); ++i)
			nums2_set.insert(nums2[i]);

		for (auto it = nums1_set.begin(); it != nums1_set.end(); ++it)
		{
			if (nums2_set.find(*it) != nums2_set.end())
				result.push_back(*it);
		}

		return result;
	}
};