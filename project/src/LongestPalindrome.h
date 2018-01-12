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

使用 unorderd_map<char, int> 记录每个字母出现的次数，
对于出现次数 k 为偶数的字母，将 k 加入最终结果，
对于出现次数 k 为奇数的字母，将 k-1 加入最终结果，并记录存在多余的字母，可以用来在最后构造奇数长度的回文串。

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
		int withExtraChar = 0;		// 记录是否存在多余的单个字母用来构造奇数长度的最终回文数
		for (auto it = char_to_cnt.begin(); it != char_to_cnt.end(); ++it)
		{
			if (it->second % 2 == 0)
				result += it->second;
			else
			{
				result += it->second - 1;
				withExtraChar = 1;	// 存在多余字母用来最终构造奇数长度的回文数
			}
		}
		return result + withExtraChar;
	}
};
