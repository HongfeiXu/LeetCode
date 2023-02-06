#pragma once

/*

521. Longest Uncommon Subsequence I

Given a group of two strings, you need to find the longest uncommon subsequence of this group of two strings. 
The longest uncommon subsequence is defined as the longest subsequence of one of these strings and this 
subsequence should not be any subsequence of the other strings.

A subsequence is a sequence that can be derived from one sequence by deleting some characters without 
changing the order of the remaining elements. Trivially, any string is a subsequence of itself and 
an empty string is a subsequence of any string.

The input will be two strings, and the output needs to be the length of the longest uncommon subsequence. 
If the longest uncommon subsequence doesn't exist, return -1.

Example 1:
Input: "aba", "cdc"
Output: 3
Explanation: The longest uncommon subsequence is "aba" (or "cdc"),
because "aba" is a subsequence of "aba",
but not a subsequence of any other strings in the group of two strings.
Note:

Both strings' lengths will not exceed 100.
Only letters from a ~ z will appear in input strings.

Approach:
这是一道智力题。。。
关键在于弄清楚“子序列”、“最长不同子序列”的含义。

分情况讨论
如果 a b 长度不同，则较长的那个是结果。
若 a b 长度相同，则如果 a==b，则不存在不同子序列
若 a != b 则任意a或b均为最长不同子序列

*/

#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
	int findLUSlength(string a, string b)
	{
		if (a.size() != b.size())
			return max(a.size(), b.size());

		else
		{
			if (a == b)
				return -1;
			else
				return a.size();
		}
	}
};