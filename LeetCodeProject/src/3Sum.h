#pragma once

/*

15. 3Sum

Related Topics: Array

Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note: The solution set must not contain duplicate triplets.

For example, given array S = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]

Approach 1: Use Backtracking(Time Limit Exceeded)
when we get a solution, we need to know whether it is duplicated,
it takes a lot time to iterate and compare...

Approach 2: Accepted
The idea is to sort an input array and then run through all indices of a possible first element of a triplet.
For each possible first element, we make a standard bi-direction 2Sum sweep of the remaining part of the array.
Also we want to skip equal elements to avoid duplicates in the answer without making a set or smth like that.
Reference:https://discuss.leetcode.com/topic/8125/concise-o-n-2-java-solution

*/

#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
private:
	void threeSumAux(vector<int>& nums, 
					 vector<vector<int>>& solutionSet, 
					 vector<int>& currSolution,
					 int beginIndex, 
					 int& sumOf3)
	{
		if (currSolution.size() == 3)
		{
			if (sumOf3 == 0)
			{
				// remove the duplicated answer, time consuming!!!
				for (int i = 0; i < solutionSet.size(); i++)
				{
					if (solutionSet[i] == currSolution)
						return;
				}
				solutionSet.push_back(currSolution);
			}
			return;
		}

		for (int i = beginIndex; i < static_cast<int>(nums.size()); i++)
		{
			currSolution.push_back(nums[i]);
			sumOf3 += nums[i];
			threeSumAux(nums, solutionSet, currSolution, i + 1, sumOf3);
			sumOf3 -= nums[i];
			currSolution.pop_back();
		}
	}

public:
	vector<vector<int>> threeSum(vector<int>& nums)
	{
		vector<vector<int>> solutionSet;
		vector<int> currSolution;
		int sumOf3 = 0;

		// sort first, to avoid sort in the threeSumAux, save time
		sort(nums.begin(), nums.end());
		threeSumAux(nums, solutionSet, currSolution, 0, sumOf3);
		
		return solutionSet;
	}


	vector<vector<int>> threeSum_v2(vector<int>& nums)
	{
		vector<vector<int>> solutionSet;

		sort(nums.begin(), nums.end());
		for (int i = 0; i < static_cast<int>(nums.size()) - 2; i++)	// note: this static_cast is important, or when the nums is empty, error happens
		{
			if (i == 0 || (i > 0 && nums[i] != nums[i - 1]))
			{
				int low = i + 1;
				int high = nums.size() - 1;
				int twoSum = 0 - nums[i];
				while (low < high)
				{
					if (nums[low] + nums[high] == twoSum)
					{
						solutionSet.push_back(vector<int>{nums[i], nums[low], nums[high]});
						// avoid duplicates
						while (low < high && nums[low] == nums[low + 1])
							low++;
						while (low < high && nums[high] == nums[high - 1])
							high--;
						low++;
						high--;
					}
					else if (nums[low] + nums[high] < twoSum)
					{
						low++;
					}
					else
					{
						high--;
					}
				}
			}
		}
		return solutionSet;
	}
};
