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
��������

*/

#include <string>
#include <cctype>

using namespace std;

class Solution {
public:
	bool detectCapitalUse(string word)
	{
		// ����һ����ĸΪ��д��ĸ
		// ��֮�����ĸΪȫ����д����ȫ��Сдʱ�����ʺϷ�
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
		// ����һ����ĸΪСд��ĸ����֮�����ĸΪȫ��Сдʱ�����ʺϷ�
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