#pragma once

/*

219. Contains Duplicate II

Given an array of integers and an integer k, 
find out whether there are two distinct indices i and j in the array 
such that nums[i] = nums[j] and the absolute difference between i and j is at most k.

Approach My:
a new class to save num and it's index in the vector
then stable sort it
then iterate through it to find

*/

#include <vector>
#include <algorithm>

using namespace std;

class Data {
public:
	int num;
	int index;
};

bool operator< (const Data &lhs, const Data &rhs)
{
	return lhs.num < rhs.num;
}

class Solution {
public:
	bool containsNearbyDuplicate(vector<int>& nums, int k)
	{
		vector<Data> datas;
		for (int i = 0; i < nums.size(); i++)
		{
			datas.push_back({ nums[i], i });
		}
		stable_sort(datas.begin(), datas.end());	// The order of equal elements is guaranteed to be preserved.
		
		for (int i = 0; i < static_cast<int>(datas.size()) - 1; i++)
		{
			if (datas[i].num == datas[i + 1].num && datas[i + 1].index - datas[i].index <= k)
				return true;
		}
		return false;
	}
};