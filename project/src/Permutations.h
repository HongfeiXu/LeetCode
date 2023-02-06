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

注意到：如果输入数字为从小到大，则输出的排列也是按照字典序排列的
另外：题目提示输入的时不同数字，所以这里面的判断其实时多余的，但，没有坏处嘛

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
		// 前 nums.size() - 1 个数字确定，整个排列就定下来了
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

	// 若 nums[j] 在 nums[i,...,j-1] 中没有出现，则需要交换，否则不应该交换，避免出现重复排列
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