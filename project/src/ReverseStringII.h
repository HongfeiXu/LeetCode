#pragma once

/*

541. Reverse String II

Given a string and an integer k, you need to reverse the first k characters for every 2k characters counting from the start of the string. 
If there are less than k characters left, reverse all of them. If there are less than 2k but greater than or equal to k characters, 
then reverse the first k characters and left the other as original.

Example:
Input: s = "abcdefg", k = 2
Output: "bacdfeg"
Restrictions:
The string consists of lower English letters only.
Length of the given string and k will in the range [1, 10000]

*/

#include <string>

using namespace std;

class Solution {
public:
	string reverseStr(string s, int k)
	{
		int len = s.size();
		for (int i = 0; i < len; i += 2*k)
		{
			reverseAux(s, i, k);
		}
		return s;
	}

	void reverseAux(string& s, int i, int k)
	{
		// 字符串s，从i开始至少有k个字符，反转这k个字符
		if (i + k <= s.size())
		{
			int last = i + k;		// 子串的最后一个元素的尾后位置
			int mid = (i + last) / 2;
			for (int j = 0; j < mid - i; ++j)
				swap(s[i + j], s[last - 1 - j]);
		}
		else	// 字符串s，从i开始，还有不到k个字符
		{
			int last = s.size();
			int mid = (i + last) / 2;
			for (int j = 0; j < mid - i; ++j)
				swap(s[i + j], s[last- 1 - j]);
		}
	}
};
