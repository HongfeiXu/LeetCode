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
LIS[i] ��ʾ�� nums[i] Ϊ���һ��Ԫ�ص�����������еĳ���
��LIS[k] = max{LIS[i] + 1}������ nums[i] < nums[k]��i = 0...k-1

##############################################
Approach_v2:
sort => unique => LCS
Time: O(n^2), Slower

##############################################
Approach_v3:
COOL
Time: O(n log n)
�����B[0..n-1] �洢��Ӧ����Ϊ i + 1 �� LIS ����Сĩβ��
�������ĩβ�����ǾͿ���һ��һ������ĩβ������ݻ����м��滻���ݡ�
����ʹ�� ���ֲ��� �ӿ��ٶȣ�ÿһ�β��� O(log n)
�����ܵ�ʱ�临�Ӷ�Ϊ O(n log n)
Example:
nums[0~9] = {2,1,5,3,6,4,8,9,7}
B[0~9] = {2,}
1 < 2�����루�ҵ�����λ�ã��滻����λ�õ�����
B[0~9] = {1,}
5 > 1��׷�ӵ� B ��
B[0~9] = {1,5,}
3 < 5�����루�ҵ�����λ�ã��滻����λ�õ�����
B[0~9] = {1,3,}
6 > 3��׷�ӵ� B ��
B[0~9] = {1,3,6,}
4 < 6�����루�ҵ�����λ�ã��滻����λ�õ�����
B[0~9] = {1,3,4,}
8 > 4��׷��
B[0~9] = {1,3,4,8,}
9 > 8��׷��
B[0~9] = {1,3,4,8,9,}
7 < 9������
B[0~9] = {1,3,4,7,9,}

���տɵ� LIS ����Ϊ 5

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
		vector<int> LIS(nums.size(), 1);	// ��ʼֵ��Ϊ1����Ϊ�� nums[i] Ϊ���һ��Ԫ�ص�����������г�������Ϊ1
		int lis = 1;	// nums ������������еĳ���
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
		// ȥ�أ���Ϊ����Ҫ����ǵ���������
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

	// �����������в���Ŀ�����ֵĲ���λ��
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

