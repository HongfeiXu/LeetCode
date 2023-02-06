#pragma once

/*

516. Longest Palindromic Subsequence

Given a string s, find the longest palindromic subsequence's length in s. You may assume that the maximum length of s is 1000.

Example 1:
Input:

"bbbab"
Output:
4
One possible longest palindromic subsequence is "bbbb".

Example 2:
Input:

"cbbd"
Output:
2
One possible longest palindromic subsequence is "bb".

#############################################################
Approach:

这一题要求的是最长回文子序列，不同于 5. Longest Palindromic Substring 要求的最长回文串。
很显然的是可以想到用原串 s0,s1,...,s_n-1 与其逆序串 s_n-1,...,s0 求 longest common subsequence 的 dp 算法，这里实现的时候顺带优化了空间复杂度。
时间复杂度为 O(n^2)。
空间复杂度为 O(2*n)。

#############################################################
Approach v2:
直接DP

dp[i][j] 为 s[i],s[i+1],...,s[j] 的最长回文子序列的长度，则

				dp[i+1][j-1] + 2				(s[i] == s[j])
dp[i][j] =
				max{dp[i+1][j], dp[i][j-1]}		(s[i] != s[j])

且：
dp[i][i] = 1
dp[i][i+1] = 2 若 s[i] == s[i+1]，否则 = 1

*/

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

class Solution {
public:
	int longestPalindromeSubseq(string s)
	{
		string rs(s.rbegin(), s.rend());
		return longestCommonSubsequence(s, rs);
	}

	int longestCommonSubsequence(const string& str_a, const string& str_b)
	{
		int m = str_a.size(), n = str_b.size();
		vector<vector<int>> dp(2, vector<int>(n + 1, 0));
		for (int i = 1; i <= m; ++i)
		{
			for (int j = 1; j <= n; ++j)
			{
				if (str_a[i - 1] == str_b[j - 1])
					dp[i % 2][j] = dp[(i - 1) % 2][j - 1] + 1;
				else
					dp[i % 2][j] = max(dp[(i - 1) % 2][j], dp[i % 2][j - 1]);
			}
		}
		return dp[m % 2][n];
	}
};

class Solution_v2 {
public:
	int longestPalindromeSubseq(string s)
	{
		int s_len = s.size();
		vector<vector<int>> dp(s_len, vector<int>(s_len, 0));
		for (int i = 0; i < s_len; ++i)
			dp[i][i] = 1;
		for (int i = 0; i < s_len - 1; ++i)
			dp[i][i + 1] = s[i] == s[i + 1] ? 2 : 1;
		for (int sub_len = 3; sub_len <= s_len; ++sub_len)
		{
			for (int i = 0; i < s_len - sub_len + 1; ++i)
			{
				if (s[i] == s[i + sub_len - 1])
					dp[i][i + sub_len - 1] = dp[i + 1][i + sub_len - 2] + 2;
				else
					dp[i][i + sub_len - 1] = max(dp[i + 1][i + sub_len - 1], dp[i][i + sub_len - 2]);
			}
		}
		return dp[0][s_len - 1];
	}
};