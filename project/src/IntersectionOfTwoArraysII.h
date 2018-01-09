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
ʹ������ unordered_map ���ֱ��¼ nums1��nums2 �����ּ����ִ���
������Щ��ͬ���ڵ����֣����ִ�����С�ļ�Ϊ�ཻ�Ĳ��֡�

Approach Follow up1:
What if the given array is already sorted? How would you optimize your algorithm?
�� Solution_v2����nice�ķ������۷�ʽ��

What if nums1's size is small compared to nums2's size? Which algorithm is better?
��Ȼ����ʱ Solution_v2 �����ʣ��˷����� nums2������󣬾ͻ�������С���Solution����Ҫ���������� unordered_map

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
