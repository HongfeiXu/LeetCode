#pragma once

/*

119. Pascal's Triangle II

Related Topics: Array

Given an index k, return the kth row of the Pascal's triangle.

For example, given k = 3,
Return [1,3,3,1].

Note:
Could you optimize your algorithm to use only O(k) extra space?

Approach:
Use another vector to save the previous row.

Approach better:
rowIndex = 3: 1 3 3 1
rowIndex = 4: 1 3 3 1 1 -> 1 3 3 4 1 -> 1 3 6 4 1 -> 1 4 6 4 1

*/

#include <vector>

using namespace std;

class Solution {
public:
	vector<int> getRow(int rowIndex)
	{
		vector<int> prevRow { 1 };

		for (int i = 0; i <= rowIndex; i++)
		{
			vector<int> currRow(i + 1, 0);
			currRow.front() = 1;
			currRow.back() = 1;

			for (int j = 1; j < i; j++)
			{
				currRow[j] = prevRow[j - 1] + prevRow[j];
			}
			prevRow = currRow;
		}

		return prevRow;
	}

	vector<int> getRow_v2(int rowIndex)
	{
		vector<int> row;
		for (int i = 0; i <= rowIndex; i++)
		{
			row.push_back(1);
			for (int j = i - 1; j > 0; j--)
			{
				row[j] = row[j] + row[j - 1];
			}
		}
		return row;
	}
};