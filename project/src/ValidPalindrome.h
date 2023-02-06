#pragma once

/*

125. Valid Palindrome

Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

For example,
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.

Note:
Have you consider that the string might be empty? This is a good question to ask during an interview.
For the purpose of this problem, we define empty string as valid palindrome.

Approach:
make the string pure alphanumeric, then copy to another string in reverse order,
compare them, equal <-> valid

*/

#include <iostream>
#include <string>
#include <cctype>
#include <iterator>

using namespace std;

class Solution {
public:
	bool isPalindrome(string s)
	{
		string pureAlphanumeric;
		for (size_t i = 0; i < s.size(); ++i)
		{
			if (isalnum(s[i]))
			{
				// 如果是字母，存为对应的小写字母
				if (isalpha(s[i]))
					pureAlphanumeric.push_back(tolower(s[i]));
				// 如果是数字，直接保存
				else
					pureAlphanumeric.push_back(s[i]);
			}
		}

		int len = pureAlphanumeric.size();
		int halfLen = len / 2;
		for (int i = 0; i < halfLen; ++i)
		{
			if (pureAlphanumeric[i] != pureAlphanumeric[len - 1 - i])
				return false;
		}
		return true;
	}
};