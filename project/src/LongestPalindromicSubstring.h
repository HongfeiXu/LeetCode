#pragma once

/*

5. Longest Palindromic Substring

Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example:

Input: "babad"

Output: "bab"

Note: "aba" is also a valid answer.


Example:

Input: "cbbd"

Output: "bb"

********************************************************************
Approach[AC]:

Middle Out
Expand Around Center
发散法。
对于一个长为 m 的字符串， s0,s1,s2,...,s_m-1
有 2*m-1个位置可以作为发散中心，确定各个发散中心的最长的回文串。
发散中心： s0,s1,s2,...,s_m-1 以及 s0与s1的中间,s1与s2的中间,...,s_m-2与s_m-1 的中间，共计 2*m-1个位置。

Time: O(n^2)
Space: O(1)

********************************************************************
Approach v2[AC]:
Ref: https://leetcode.com/problems/longest-palindromic-substring/solution/
应用 Longest Common Substring（最长公共子串）

对于一个长为 m 的字符串，s0,s1,s2,...,s_m-1
其逆序为 m' = s_m-1,...,s2,s1,s0
则这两个字符串的公共子串则可能是要求的 m 的回文子串。

注： abcdc - cdcba  -> cdc是最长公共子串，也是最长回文子串
     bcdacb - bcadcb -> bc是最长公共子串，但不是最长回文子串
因此需要对找到的每一个公共子串进行判断，看是否为回文串。
这里不需要真正去判断 bc 是否为回文串，只需要看bc在原串中出现的起始位置pos_a以及在逆序串中出现的结束（尾后）位置pos_b，如果pos_a+pos_b==m则是回文子串。
例如：
aaab - baaa
有dp[3][4] = 3
pos_a = 3 - dp[3][4] = 0, pos_b = 4, pos_a + pos_b == 4
所以 aaa 为回文串

abcdba - abdcba
有dp[2][2] = 2
pos_a = 2 - dp[2][2] = 0, pos_b = 2, pos_a + pos_b = 2 != 6
所以 ab 不是回文串


Time: O(n^2)
Space: O(n^2)

********************************************************************
Approach v3[TLE]:

Brute Force

The obvious brute force solution is to pick all possible starting and ending positions for a substring, and verify if it is a palindrome.

Time: O(n^3)
Space: O(1)

********************************************************************
Approach v4:

DP，结合上面的暴力法，我们观察哪些重复的操作（重复子问题），对于例子 abcba，如果已经计算出 bcb 是回文串，则由于 a==a，故 abcba 也是回文串。
我们定义
P(i,j) = true, 表示 s[i],s[i+1],...,s[j] 为回文串，则有：

	P(i,j) = (P(i+1,j-1) && s[i] == s[j])
	P(i,i) = true
	P(i,i+1) = (s[i] == s[i+1])

首先得到所有长度为1和2的回文串，然后寻找长度为3的回文串，依次下去，直到长度为str_len。

Time: O(n^2)
Space: O(n^2)
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

class Solution {
public:
	string longestPalindrome(string s)
	{
		string result = "";
		int N = s.size();
		// 以 s[i] 为发散中心，左右发散
		for (int i = 0; i < N; ++i)
		{
			int left = i, right = i;
			while (left >= 0 && right < N && s[left] == s[right])
			{
				--left;
				++right;
			}
			int len = right - left - 1;
			if (len > result.size())
				result.assign(s, left + 1, len);
		}
		// 以s[i] 和 s[i+1] 的中间位置为发散中心，左右发散
		for (int i = 0; i < N - 1; ++i)
		{
			int left = i, right = i + 1;
			while (left >= 0 && right < N && s[left] == s[right])
			{
				--left;
				++right;
			}
			int len = right - left - 1;
			if (len > result.size())
				result.assign(s, left + 1, len);
		}
		return result;
	}
};

class Solution_v2 {
public:
	string longestPalindrome(string s)
	{
		string t(s.rbegin(), s.rend());
		vector<vector<int>> dp;
		lcs(s, t, dp);
		
		unsigned len = s.size();
		string result = "";
		for (unsigned i = 1; i <= len; ++i)
		{
			for (unsigned j = 1; j <= len; ++j)
			{
				// 如果当前公共后缀长度大于 result，
				// check if the substring’s indices are the same as the reversed substring’s original indices.
				if (dp[i][j] > result.size() && i - dp[i][j] + j == len)
				{
					result.assign(s.begin() + i - dp[i][j], s.begin() + i);
				}
			}
		}
		return result;
	}

	void lcs(const string& X, const string& Y, vector<vector<int>>& dp)
	{
		unsigned m = X.size(), n = Y.size();
		// dp[i][j] 为 X[0..i-1] 与 Y[0..j-1] 的最长公共后缀长度
		dp.assign(m + 1, vector<int>(n + 1, 0));
		
		for (unsigned i = 1; i <= m; ++i)
		{
			for (unsigned j = 1; j <= n; ++j)
			{
				if (X[i - 1] == Y[j - 1])
					dp[i][j] = dp[i - 1][j - 1] + 1;
				else
					dp[i][j] = 0;
			}
		}
		return;
	}
};

class Solution_v3 {
public:
	string longestPalindrome(string s)
	{
		string result = "";
		// s[i],s[i+1],...,s[j] 构造 candidate
		for (int i = 0; i < s.size(); ++i)
		{
			// prune
			for (int j = i + result.size(); j < s.size(); ++j)
			{
				string candidate(s.begin() + i, s.begin() + j + 1);
				if (isPalindrome(candidate) && candidate.size() > result.size())
					result = candidate;
			}
		}
		return result;
	}

	bool isPalindrome(const string& s)
	{
		if (s.empty())
			return true;
		auto left = s.begin();
		auto right = s.end() - 1;
		while (left < right && *left == *right)
		{
			++left;
			--right;
		}
		if (left < right)
			return false;
		else
			return true;
	}
};

class Solution_v4 {
public:
	string longestPalindrome(string s)
	{
		int str_len = s.size();
		vector<vector<bool>> dp(str_len, vector<bool>(str_len, false));
		// one letter palindromes
		for (int i = 0; i < str_len; ++i)
			dp[i][i] = true;
		// two letter palindromes
		for (int i = 0; i < str_len - 1; ++i)
		{
			if (s[i] == s[i + 1])
				dp[i][i + 1] = true;
		}
		// find 3,4,...,str_len letters palindromes
		for (int substr_len = 3; substr_len <= str_len; ++substr_len)
		{
			for (int i = 0; i <= str_len - substr_len; ++i)
				dp[i][i + substr_len - 1] = dp[i + 1][i + substr_len - 2] && s[i] == s[i + substr_len - 1];
		}
		
		string result = "";
		for (int i = 0; i < str_len; ++i)
		{
			for (int j = i; j < str_len; ++j)
			{
				if (dp[i][j] && (j - i + 1) > result.size())
					result.assign(s, i, j - i + 1);
			}
		}
		return result;
	}
};