#pragma once

/*

409. Longest Palindrome

Given a string which consists of lowercase or uppercase letters, find the length of the longest palindromes that can be built with those letters.

This is case sensitive, for example "Aa" is not considered a palindrome here.

Note:
Assume the length of given string will not exceed 1,010.

Example:

Input:
"abccccdd"

Output:
7

Explanation:
One longest palindrome that can be built is "dccaccd", whose length is 7.

Approach:

ʹ�� unorderd_map<char, int> ��¼ÿ����ĸ���ֵĴ�����
���ڳ��ִ��� k Ϊż������ĸ���� k �������ս����
���ڳ��ִ��� k Ϊ��������ĸ���� k-1 �������ս��������¼���ڶ������ĸ������������������������ȵĻ��Ĵ���

*/

#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution {
public:
	int longestPalindrome(string s)
	{
		unordered_map<char, int> char_to_cnt;
		for (auto& c : s)
			++char_to_cnt[c];

		int result = 0;
		int withExtraChar = 0;		// ��¼�Ƿ���ڶ���ĵ�����ĸ���������������ȵ����ջ�����
		for (auto it = char_to_cnt.begin(); it != char_to_cnt.end(); ++it)
		{
			if (it->second % 2 == 0)
				result += it->second;
			else
			{
				result += it->second - 1;
				withExtraChar = 1;	// ���ڶ�����ĸ�������չ����������ȵĻ�����
			}
		}
		return result + withExtraChar;
	}
};
