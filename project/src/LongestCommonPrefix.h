#pragma once

/*

14. Longest Common Prefix

Write a function to find the longest common prefix string amongst an array of strings.

*/


#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
	string longestCommonPrefix(vector<string>& strs)
	{
		// 边界条件
		if (strs.size() == 0)
			return string("");
		if (strs.size() == 1)
			return strs[0];


		string result;

		int min_len = INT_MAX;
		for (int i = 0; i < strs.size(); ++i)
			min_len = min(static_cast<int>(strs[i].size()), min_len);

		for (int i = 0; i < min_len; ++i)
		{
			int j = 0;
			for (j = 1; j < strs.size(); ++j)
			{
				if(strs[j][i] != strs[0][i])
					break;
			}
			if (j == strs.size())
				result.push_back(strs[0][i]);
			else
				break;
		}
		return result;
	}
};