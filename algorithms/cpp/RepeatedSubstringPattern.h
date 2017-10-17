#pragma once

/*

459. Repeated Substring Pattern

Related Topics: String

Given a non-empty string check if it can be constructed by taking a substring of it and appending multiple copies of the substring together. 
You may assume the given string consists of lowercase English letters only and its length will not exceed 10000.

Input: "abab"

Output: True

Explanation: It's the substring "ab" twice.

Input: "aba"

Output: False

Input: "abcabcabcabc"

Output: True

Explanation: It's the substring "abc" four times. (And the substring "abcabc" twice.)

*/

#include <string>

using namespace std;

class Solution {
public:
	bool repeatedSubstringPattern(string s)
	{
		int length = s.length();
		for (int i = 1; i <= length / 2; i++)	// i Ϊ�Ӵ��ĳ��ȣ����δ� 1 ������ length/2
		{
			if(length % i != 0)		// ��� s �ĳ��Ȳ��� i ����������������
				continue;
			string si(s.begin(), s.begin() + i);	// ���� si
			int j = i;
			while (j < length && si == string(s.begin() + j, s.begin() + j + i))	// �������Ƚϣ����ȫ����ͬ���� j==length
			{
				j += i;
			}
			if (j == length)
				return true;
		}

		return false;
	}
};

