#pragma once

/*

520. Detect Capital

Given a word, you need to judge whether the usage of capitals in it is right or not.

We define the usage of capitals in a word to be right when one of the following cases holds:

All letters in this word are capitals, like "USA".
All letters in this word are not capitals, like "leetcode".
Only the first letter in this word is capital if it has more than one letter, like "Google".
Otherwise, we define that this word doesn't use capitals in a right way.

Example 1:
Input: "USA"
Output: True
Example 2:
Input: "FlaG"
Output: False

Approach:
分类讨论

*/

#include <string>
#include <cctype>

using namespace std;

class Solution {
public:
	bool detectCapitalUse(string word)
	{
		// 若第一个字母为大写字母
		// 则，之后的字母为全部大写或者全部小写时，单词合法
		if (isupper(static_cast<unsigned char>(word[0])))
		{
			bool all_upper = true;
			bool all_lower = true;
			for (int i = 1; i < word.size(); ++i)
			{
				if (isupper(static_cast<unsigned char>(word[i])))
					all_lower = false;
				else
					all_upper = false;

				if ((!all_lower) && (!all_upper))
					return false;
			}
			return true;
		}
		// 若第一个字母为小写字母，则，之后的字母为全部小写时，单词合法
		else
		{
			for (int i = 1; i < word.size(); ++i)
			{
				if (isupper(static_cast<unsigned char>(word[i])))
					return false;
			}
			return true;
		}
	}
};