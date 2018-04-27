#pragma once

/*

300. Longest Increasing Subsequence

Given an unsorted array of integers, find the length of longest increasing subsequence.

For example,
Given [10, 9, 2, 5, 3, 7, 101, 18],
The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. Note that there may be more than one LIS combination, it is only necessary for you to return the length.

Your algorithm should run in O(n2) complexity.

Follow up: Could you improve it to O(n log n) time complexity?

##############################################
Approach:
DP
Time: O(n^2)

Input: nums[0...n-1]

Def: LIS[0...n-1]
LIS[i] 表示以 nums[i] 为最后一个元素的最长递增子序列的长度
则，LIS[k] = max{LIS[i] + 1}，其中 nums[i] < nums[k]，i = 0...k-1

##############################################
Approach_v2:
sort => unique => LCS
Time: O(n^2), Slower

##############################################
Approach_v3:
COOL
Time: O(n log n)
构造出B[0..n-1] 存储对应长度为 i + 1 的 LIS 的最小末尾。
有了这个末尾，我们就可以一个一个的在末尾添加数据或在中间替换数据。
可以使用 二分查找 加快速度，每一次插入 O(log n)
最终总的时间复杂度为 O(n log n)
Example:
nums[0~9] = {2,1,5,3,6,4,8,9,7}
B[0~9] = {2,}
1 < 2，插入（找到插入位置，替换掉该位置的数）
B[0~9] = {1,}
5 > 1，追加到 B 中
B[0~9] = {1,5,}
3 < 5，插入（找到插入位置，替换掉该位置的数）
B[0~9] = {1,3,}
6 > 3，追加到 B 中
B[0~9] = {1,3,6,}
4 < 6，插入（找到插入位置，替换掉该位置的数）
B[0~9] = {1,3,4,}
8 > 4，追加
B[0~9] = {1,3,4,8,}
9 > 8，追加
B[0~9] = {1,3,4,8,9,}
7 < 9，插入
B[0~9] = {1,3,4,7,9,}

最终可得 LIS 长度为 5

*/

#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;

class Solution {
public:
	int lengthOfLIS(vector<int>& nums)
	{
		if (nums.empty())
			return 0;
		vector<int> LIS(nums.size(), 1);	// 初始值设为1，因为以 nums[i] 为最后一个元素的最长递增子序列长度至少为1
		int lis = 1;	// nums 的最长递增子序列的长度
		for (int i = 1; i < nums.size(); ++i)
		{
			for (int j = 0; j < i; ++j)
			{
				if (nums[j] < nums[i])
					LIS[i] = max(LIS[i], LIS[j] + 1);
			}
			cout << "LIS[" << i << "] = " << LIS[i] << endl;
			lis = max(lis, LIS[i]);
		}
		return lis;
	}
};

class Solution_v2 {
public:
	int lengthOfLIS(vector<int>& nums)
	{
		if (nums.empty())
			return 0;
		vector<int> nums_sorted(nums);
		sort(nums_sorted.begin(), nums_sorted.end());
		// 去重，因为我们要求的是递增子序列
		auto end_unique = unique(nums_sorted.begin(), nums_sorted.end());
		nums_sorted.erase(end_unique, nums_sorted.end());

		return LCS(nums, nums_sorted);
	}

	int LCS(vector<int>& lhs, vector<int>& rhs)
	{
		vector<vector<int>> T(2, vector<int>());
		for (int i = 0; i < 2; ++i)
			T[i].assign(rhs.size() + 1, 0);

		for (int i = 0; i < lhs.size() + 1; ++i)
		{
			for (int j = 0; j < rhs.size() + 1; ++j)
			{
				if (i == 0 || j == 0)
				{
					T[i % 2][j] = 0;
				}
				else
				{
					if (lhs[i - 1] == rhs[j - 1])
						T[i % 2][j] = T[(i - 1) % 2][j - 1] + 1;
					else
						T[i % 2][j] = max(T[(i - 1) % 2][j], T[i % 2][j - 1]);
				}
			}
		}
		return T[lhs.size() % 2][rhs.size()];
	}
};

class Solution_v3 {
public:
	int lengthOfLIS(vector<int>& nums)
	{
		if (nums.empty())
			return 0;
		vector<int> B;
		B.push_back(nums[0]);
		for (int i = 1; i < nums.size(); ++i)
		{
			if (nums[i] > B.back())
				B.push_back(nums[i]);
			else
			{
				int pos = FindInsertPos(B, nums[i]);
				B[pos] = nums[i];
			}
		}

		return B.size();
	}

	// 在升序序列中查找目标数字的插入位置
	int FindInsertPos(const vector<int>& nums, int target)
	{
		int low = 0;
		int high = nums.size() - 1;
		while (low <= high)
		{
			int mid = (low + high) / 2;
			if (nums[mid] > target)
				high = mid - 1;
			else if (nums[mid] < target)
				low = mid + 1;
			else
				return mid;
		}
		return low;
	}
};

