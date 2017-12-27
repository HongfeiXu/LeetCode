#pragma once

/*

680. Valid Palindrome II

Given a non-empty string s, you may delete at most one character. Judge whether you can make it a palindrome.

Example 1:
Input: "aba"
Output: True
Example 2:
Input: "abca"
Output: True
Explanation: You could delete the character 'c'.

Note:
The string will only contain lowercase characters a-z. The maximum length of the string is 50000.

Approach:
��ͷ�У����������ȵ���ĸ�������������ɾ�������ĸ����ɾ���ұ���ĸ������һ�����Ϊ�����֣��򷵻� true�����򷵻� false
��δ�������ȵ���ĸ���򷵻� true

*/

#include <string>

using namespace std;

class Solution {
public:
	bool validPalindrome(string s)
	{
		if (s.empty())
			return true;
		
		size_t i = 0;
		size_t j = s.size() - 1;

		while (i < j)
		{
			if (s[i] == s[j])
			{
				++i;
				--j;
			}
			else
			{
				string temp;
				// ɾ�� s[i]
				temp.assign(s.begin() + i + 1, s.begin() + j + 1);
				if (aux(temp))
					return true;
				// ɾ�� s[j]
				temp.assign(s.begin() + i, s.begin() + j);
				if (aux(temp))
					return true;
				return false;
			}
			
		}
		return true;
	}

	bool aux(string s)
	{
		size_t len = s.size();
		size_t halfLen = len / 2;
		for (int i = 0; i < halfLen; ++i)
		{
			if (s[i] != s[len - 1 - i])
				return false;
		}
		return true;
	}
};