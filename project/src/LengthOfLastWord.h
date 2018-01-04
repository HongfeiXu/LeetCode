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

ע��߽����������sΪ��ʱ

����ĩβ�Ŀո�Ȼ���¼���һ�����ʵĸ���

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
		while (s[i] == ' ' && i >= 0)	// ������һ���ַ�Ϊ�ո���Ӻ���ǰ�����ո�
		{
			--i;
		}
		if (i == -1)					// ��ȫ�����ǿո��򷵻�0
			return 0;
		int j = i - 1;
		while (j >= 0 && s[j] != ' ')	// �� i ��ʼ���Ӻ���ǰ������ĸ
			--j;

		return i - j;
	}
};