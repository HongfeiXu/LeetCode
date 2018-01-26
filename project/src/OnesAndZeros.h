#pragma once

/*

474. Ones and Zeroes

In the computer world, use restricted resource you have to generate maximum benefit is what we always want to pursue.
For now, suppose you are a dominator of m 0s and n 1s respectively. On the other hand, there is an array with strings consisting of only 0s and 1s.
Now your task is to find the maximum number of strings that you can form with given m 0s and n 1s. Each 0 and 1 can be used at most once.

Note:
The given numbers of 0s and 1s will both not exceed 100
The size of given string array won't exceed 600.

Example 1:
Input: Array = {"10", "0001", "111001", "1", "0"}, m = 5, n = 3
Output: 4

Explanation: This are totally 4 strings can be formed by the using of 5 0s and 3 1s, which are “10,”0001”,”1”,”0”
Example 2:
Input: Array = {"10", "0", "1"}, m = 1, n = 1
Output: 2

Explanation: You could form "10", but then you'd have nothing left. Better form "0" and "1".

Approach:
Time Limit Exceeded
Backtracking

Approach v2:

0-1背包问题的变形   WOWOWOW

这里商品为所有的字符串，背包的容量由两个变量决定，即0的个数和1的个数
设 mf[i, m, n] 表示前 i 个字符串装入容量最大为 m 个 0 和 n 个 1 的背包中的最大字符串数目
则对第i个字符串，有两种情况，放进背包或者不放进背包
if strs[i].zeros > m || strs[i].ones > n，则无法放进背包，mf[i, m, n] = mf[i-1, m, n]
else mf[i, m, n] = max(mf[i-1, m, n], mf[i-1, m - zeros, n- ones] + 1) 此时可以将次字符串不放入背包或者放入背包，取较大值。

mf[strs.size(), m, n] 即为所求，注：这里 strs.size() 表示有 strs.size() 个字符串，而不用 strs.size() - 1
直接用递归实现，依然是 Time Limit Exceeded

Approach v3:
DP
动态规划方法实现 Approach v2 的算法

Time: O(strs.size() * m * n)
Space: O(strs.size() * m * n)

Approach v4:
Space Optimized
Time: O(strs.size() * m * n)
Space: O(m * n)

*/

#include <string>
#include <vector>
#include <bitset>
#include <utility>
#include <algorithm>

using namespace std;

class Solution {
public:
	int findMaxForm(vector<string>& strs, int m, int n)
	{
		int result = 0;
		aux(strs, 0, m, n, 0, result);
		return result;
	}

	void aux(vector<string>& strs, int start, int m, int n, int currFormCnt, int& maxFormCnt)
	{
		if (start == strs.size())
			maxFormCnt = max(maxFormCnt, currFormCnt);
		for (int i = start; i < strs.size(); ++i)
		{
			pair<int, int> cnt_of_zeros_ones = cntOfZerosAndOnes(strs[i]);
			if (cnt_of_zeros_ones.first > m || cnt_of_zeros_ones.second > n)
			{
				maxFormCnt = max(maxFormCnt, currFormCnt);
				continue;
			}
			else
				aux(strs, i + 1, m - cnt_of_zeros_ones.first, n - cnt_of_zeros_ones.second, currFormCnt + 1, maxFormCnt);
		}
	}

	// 返回 s 中的 0 和 1 的个数
	pair<int, int> cntOfZerosAndOnes(const string& s)
	{
		pair<int, int> result(0,0);
		for (const auto c : s)
		{
			if (c == '0')
				result.first++;
			else
				result.second++;
		}
		return result;
	}
};

class Solution_v2 {
public:
	int findMaxForm(vector<string>& strs, int m, int n)
	{
		if (strs.empty())
			return 0;
		return findMaxFormAux(strs, strs.size(), m, n);
	}

	int findMaxFormAux(vector<string>& strs, int i, int m, int n)
	{
		// Base case
		if (i == 0 || (m == 0 && n == 0))
			return 0;
		pair<int, int> cnt_of_zeros_and_ones = cntOfZerosAndOnes(strs[i-1]);

		if (cnt_of_zeros_and_ones.first > m || cnt_of_zeros_and_ones.second > n)
			return findMaxFormAux(strs, i - 1, m, n);
		else
			return max(findMaxFormAux(strs, i - 1, m, n), findMaxFormAux(strs, i - 1, m - cnt_of_zeros_and_ones.first, n - cnt_of_zeros_and_ones.second) + 1);
	}

	// 返回 s 中的 0 和 1 的个数
	pair<int, int> cntOfZerosAndOnes(const string& s)
	{
		pair<int, int> result(0, 0);
		for (const auto c : s)
		{
			if (c == '0')
				result.first++;
			else
				result.second++;
		}
		return result;
	}
};

class Solution_v3 {
public:
	int findMaxForm(vector<string>& strs, int m, int n)
	{
		vector<vector<vector<int>>> mf(strs.size() + 1, vector<vector<int>>());
		for (int i = 0; i < mf.size(); ++i)
			mf[i].assign(m + 1, vector<int>(n + 1, 0));

		for (int i = 1; i <= strs.size(); ++i)
		{
			pair<int, int> cnt_of_zeros_and_ones = cntOfZerosAndOnes(strs[i - 1]);
			for (int x = 0; x <= m; ++x)
			{
				for (int y = 0; y <= n; ++y)
				{
					if (cnt_of_zeros_and_ones.first > x || cnt_of_zeros_and_ones.second > y)
						mf[i][x][y] = mf[i - 1][x][y];
					else
						mf[i][x][y] = max(mf[i - 1][x][y], mf[i - 1][x - cnt_of_zeros_and_ones.first][y - cnt_of_zeros_and_ones.second] + 1);
				}
			}
		}
		return mf[strs.size()][m][n];
	}

	// 返回 s 中的 0 和 1 的个数
	pair<int, int> cntOfZerosAndOnes(const string& s)
	{
		pair<int, int> result(0, 0);
		for (const auto c : s)
		{
			if (c == '0')
				result.first++;
			else
				result.second++;
		}
		return result;
	}
};

class Solution_v4 {
public:
	int findMaxForm(vector<string>& strs, int m, int n)
	{
		vector<vector<vector<int>>> mf(2, vector<vector<int>>());
		for (int i = 0; i < mf.size(); ++i)
			mf[i].assign(m + 1, vector<int>(n + 1, 0));

		for (int i = 1; i <= strs.size(); ++i)
		{
			pair<int, int> cnt_of_zeros_and_ones = cntOfZerosAndOnes(strs[i - 1]);
			for (int x = 0; x <= m; ++x)
			{
				for (int y = 0; y <= n; ++y)
				{
					if (cnt_of_zeros_and_ones.first > x || cnt_of_zeros_and_ones.second > y)
						mf[i % 2][x][y] = mf[(i-1+2)%2][x][y];
					else
						mf[i % 2][x][y] = max(mf[(i-1+2)%2][x][y], mf[(i-1+2)%2][x - cnt_of_zeros_and_ones.first][y - cnt_of_zeros_and_ones.second] + 1);
				}
			}
		}
		return mf[strs.size()%2][m][n];
	}

	// 返回 s 中的 0 和 1 的个数
	pair<int, int> cntOfZerosAndOnes(const string& s)
	{
		pair<int, int> result(0, 0);
		for (const auto c : s)
		{
			if (c == '0')
				result.first++;
			else
				result.second++;
		}
		return result;
	}
};