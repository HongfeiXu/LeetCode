#pragma once

/*

À©³ä£ºMini Swap Array

Assume we have an integer array row of length N, which contains integers from 0 up to N-1 but in random order. 
You are free to choose any two numbers and swap them. What is the minimum number of swaps needed 
so that we have i == row[i] for 0 <= i < N (or equivalently, to sort this integer array)?

Approach:
Ref: https://leetcode.com/problems/couples-holding-hands/discuss/113362/JavaC++-O(N)-solution-using-cyclic-swapping

row: 2, 3, 1, 0, 5, 4
idx: 0, 1, 2, 3, 4, 5

Here we employ the notation i --> j to indicate that we expect the element at index i to appear at index j at the end of the swapping process.

find index groups: 
1. 0->2->1->3->0
2. 5->4->5

resolve groups:

In practice, we can always choose a pivot index and continuously swap it with its expected index 
until the pivot index is the same as its expected index, meaning the entire group is resolved 
and all placement requirements within the group are satisfied.

*/

#include <vector>

using namespace std;

class Solution {
public:
	int miniSwapArray(vector<int> row)
	{
		int result = 0;
		for (int i = 0; i < row.size(); ++i)
		{
			if (row[i] != i)
			{
				swap(i, row[i]);
				++result;
			}
		}
		return result;
	}
};