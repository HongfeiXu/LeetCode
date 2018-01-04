#pragma once

/*

58. Length of Last Word

Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.

If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space characters only.

Example:

Input: "Hello World"
Output: 5

Approach:

注意边界情况，比如s为空时

跳过末尾的空格，然后记录最后一个单词的个数

*/

#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
	int lengthOfLastWord(string s)
	{
		if (s.empty())
			return 0;

		int len = s.size();
		int i = len -1;
		while (s[i] == ' ' && i >= 0)	// 如果最后一个字符为空格，则从后向前跳过空格
		{
			--i;
		}
		if (i == -1)					// 若全部都是空格，则返回0
			return 0;
		int j = i - 1;
		while (j >= 0 && s[j] != ' ')	// 从 i 开始，从后往前跳过字母
			--j;

		return i - j;
	}
};