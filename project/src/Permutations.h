#pragma once

/*

46. Permutations

Given a collection of distinct integers, return all possible permutations.

Example

Input: [1,2,3]
Output:
[
	[1,2,3],
	[1,3,2],
	[2,1,3],
	[2,3,1],
	[3,1,2],
	[3,2,1]
]

Approach:

Backtracking

ע�⵽�������������Ϊ��С���������������Ҳ�ǰ����ֵ������е�
���⣺��Ŀ��ʾ�����ʱ��ͬ���֣�������������ж���ʵʱ����ģ�����û�л�����

*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
	vector<vector<int>> permute(vector<int>& nums)
	{
		vector<vector<int>> result;
		if (nums.empty())
			return result;
		permuteAux(nums, 0, result);
		return result;
	}

	void permuteAux(vector<int>& nums, int i, vector<vector<int>>& result)
	{
		// ǰ nums.size() - 1 ������ȷ�����������оͶ�������
		if (i == nums.size() - 1)
		{
			result.push_back(nums);
			return;
		}
		for (int j = i; j < nums.size(); ++j)
		{
			if (shouldSwap(nums, i, j))
			{
				swap(nums[i], nums[j]);
				permuteAux(nums, i+1, result);
				swap(nums[i], nums[j]);
			}
		}
	}

	// �� nums[j] �� nums[i,...,j-1] ��û�г��֣�����Ҫ����������Ӧ�ý�������������ظ�����
	bool shouldSwap(vector<int>& nums, int i, int j)
	{
		for (int k = i; k < j; ++k)
		{
			if (nums[k] == nums[j])
				return false;
		}
		return true;
	}
};

// use std::next_permutation
// should sort first
class Solution2 {
public:
	vector<vector<int>> permute(vector<int>& nums)
	{
		vector<vector<int>> result;
		if (nums.empty())
			return result;
		sort(nums.begin(), nums.end());
		result.push_back(nums);
		while (next_permutation(nums.begin(), nums.end()))
		{
			result.push_back(nums);
		}
		return result;
	}
};

void test()
{
	Solution2 solu;
	vector<int> input{ 3,4,8,7 };
	sort(input.begin(), input.end());
	vector<vector<int>> result = solu.permute(input);
	cout << "There are " << result.size() << " permutations." << endl;
	for (int i = 0; i < result.size(); ++i)
	{
		for (int j = 0; j < result[i].size(); ++j)
			cout << result[i][j] << " ";
		cout << endl;
	}
}

void driver()
{
	test();
}