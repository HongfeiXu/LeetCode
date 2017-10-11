#pragma once

/*

39. Combination Sum

Related Topics: Array, Backtracking

Approach Backtracking: Just like 22. Generate Parentheses

to avoid duplicated combinations,
we use a variable called "begin" to control the start of the for-loop

note that, there is another way to avoid duplicated combinations,
sort this currCombine, and check if there is already a currCombine in combines.
but this way is much slower.

*/

#include <vector>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
private:
	void combinationSumAux(vector<vector<int>> &combines, vector<int> &currCombine, int target, vector<int> &candidates, int begin)
	{
		if (target == 0)
		{
			combines.push_back(currCombine);
			return;
		}
		// candidates {1,2,3,7} target 7
		// if we pick 1, next time we can pick 1,2,3,7
		// if we pick 2, next time we can pick 2,3,7
		// in this way, we can avoid things like pick 2 and then go back pick 1 which would lead to duplicated combinations
		// like 1,2,2,2 and 2,1,2,2 are the same combination
		// we use begin to prune the solution space tree
		for (int i = begin; i < candidates.size(); i++)
		{
			if (candidates[i] <= target)
			{
				currCombine.push_back(candidates[i]);
				combinationSumAux(combines, currCombine, target - candidates[i], candidates, i);
				currCombine.pop_back();
			}
		}
	}

public:
	vector<vector<int>> combinationSum(vector<int>& candidates, int target)
	{
		sort(candidates.begin(), candidates.end());

		vector<vector<int>> result;
		vector<int> currCombine;

		combinationSumAux(result, currCombine, target, candidates, 0);

		return result;
	}
};
