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
��ɢ����
����һ����Ϊ m ���ַ����� s0,s1,s2,...,s_m-1
�� 2*m-1��λ�ÿ�����Ϊ��ɢ���ģ�ȷ��������ɢ���ĵ���Ļ��Ĵ���
��ɢ���ģ� s0,s1,s2,...,s_m-1 �Լ� s0��s1���м�,s1��s2���м�,...,s_m-2��s_m-1 ���м䣬���� 2*m-1��λ�á�

Time: O(n^2)
Space: O(1)

********************************************************************
Approach v2[AC]:
Ref: https://leetcode.com/problems/longest-palindromic-substring/solution/
Ӧ�� Longest Common Substring��������Ӵ���

����һ����Ϊ m ���ַ�����s0,s1,s2,...,s_m-1
������Ϊ m' = s_m-1,...,s2,s1,s0
���������ַ����Ĺ����Ӵ��������Ҫ��� m �Ļ����Ӵ���

ע�� abcdc - cdcba  -> cdc��������Ӵ���Ҳ��������Ӵ�
     bcdacb - bcadcb -> bc��������Ӵ���������������Ӵ�
�����Ҫ���ҵ���ÿһ�������Ӵ������жϣ����Ƿ�Ϊ���Ĵ���
���ﲻ��Ҫ����ȥ�ж� bc �Ƿ�Ϊ���Ĵ���ֻ��Ҫ��bc��ԭ���г��ֵ���ʼλ��pos_a�Լ��������г��ֵĽ�����β��λ��pos_b�����pos_a+pos_b==m���ǻ����Ӵ���
���磺
aaab - baaa
��dp[3][4] = 3
pos_a = 3 - dp[3][4] = 0, pos_b = 4, pos_a + pos_b == 4
���� aaa Ϊ���Ĵ�

abcdba - abdcba
��dp[2][2] = 2
pos_a = 2 - dp[2][2] = 0, pos_b = 2, pos_a + pos_b = 2 != 6
���� ab ���ǻ��Ĵ�


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

DP���������ı����������ǹ۲���Щ�ظ��Ĳ������ظ������⣩���������� abcba������Ѿ������ bcb �ǻ��Ĵ��������� a==a���� abcba Ҳ�ǻ��Ĵ���
���Ƕ���
P(i,j) = true, ��ʾ s[i],s[i+1],...,s[j] Ϊ���Ĵ������У�

	P(i,j) = (P(i+1,j-1) && s[i] == s[j])
	P(i,i) = true
	P(i,i+1) = (s[i] == s[i+1])

���ȵõ����г���Ϊ1��2�Ļ��Ĵ���Ȼ��Ѱ�ҳ���Ϊ3�Ļ��Ĵ���������ȥ��ֱ������Ϊstr_len��

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
		// �� s[i] Ϊ��ɢ���ģ����ҷ�ɢ
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
		// ��s[i] �� s[i+1] ���м�λ��Ϊ��ɢ���ģ����ҷ�ɢ
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
				// �����ǰ������׺���ȴ��� result��
				// check if the substring��s indices are the same as the reversed substring��s original indices.
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
		// dp[i][j] Ϊ X[0..i-1] �� Y[0..j-1] ���������׺����
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
		// s[i],s[i+1],...,s[j] ���� candidate
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