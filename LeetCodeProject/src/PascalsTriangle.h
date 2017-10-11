#pragma once

/*

118. Pascal's Triangle

Given numRows, generate the first numRows of Pascal's triangle.

For example, given numRows = 5,
Return

[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]

Approach:

Just find the rule of this number

*/

#include <vector>

using namespace std;

class Solution {
public:
	vector<vector<int>> generate(int numRows)
	{
		vector<vector<int>> result;
		
		for (int i = 0; i < numRows; i++)
		{
			vector<int> temp;
			temp.assign(i + 1, 0);
			temp.front() = 1;
			temp.back() = 1;

			for (int j = 1; j < i; j++)
			{
				temp[j] = result[i - 1][j - 1] + result[i - 1][j];
			}

			result.push_back(temp);
		}

		return result;
	}
};