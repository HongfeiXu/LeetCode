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
		// �ַ���s����i��ʼ������k���ַ�����ת��k���ַ�
		if (i + k <= s.size())
		{
			int last = i + k;		// �Ӵ������һ��Ԫ�ص�β��λ��
			int mid = (i + last) / 2;
			for (int j = 0; j < mid - i; ++j)
				swap(s[i + j], s[last - 1 - j]);
		}
		else	// �ַ���s����i��ʼ�����в���k���ַ�
		{
			int last = s.size();
			int mid = (i + last) / 2;
			for (int j = 0; j < mid - i; ++j)
				swap(s[i + j], s[last- 1 - j]);
		}
	}
};
