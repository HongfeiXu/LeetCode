#pragma once

/*

467. Unique Substrings in Wraparound String

Consider the string s to be the infinite wraparound string of "abcdefghijklmnopqrstuvwxyz", 
so s will look like this: "...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd....".

Now we have another string p. Your job is to find out how many unique non-empty substrings of p are present in s. 
In particular, your input is the string p and you need to output the number of different non-empty substrings of p in the string s.

Note: p consists of only lowercase English letters and the size of p might be over 10000.

Example 1:
Input: "a"
Output: 1

Explanation: Only the substring "a" of string "a" is in the string s.
Example 2:
Input: "cac"
Output: 2
Explanation: There are two substrings "a", "c" of string "cac" in the string s.
Example 3:
Input: "zab"
Output: 6
Explanation: There are six substrings "z", "a", "b", "za", "ab", "zab" of string "zab" in the string s.

#######################################
Approach:
Ref: http://www.cnblogs.com/grandyang/p/6143071.html

Time: O(n)
Space: O(1)

对字符串 abcd，以 d 结尾的子串有 abcd，bcd，cd，d，我们发现 bcd 或 cd 这些以 d 结尾的字符串的子字符串都在 abcd 中，
得出：以某个字符结尾的最大字符串包含其他以该字符结束的字符串的所有子字符串。
因此，我们需要找出以每个字符（a~z）为结束字符的最长连续字符串就行了。用数组 cnt 记录下来其长度，最终全部相加即为结果。

#######################################
Approach_v2:
Same as the approach above
只是考虑以每个字符为开始字符的最长连续字符串，需要逆序遍历字符串。

*/

#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
public:
	int findSubstringInWraproundString(string p)
	{
		if (p.size() < 2)
			return p.size();

		vector<int> cnt(26, 0);

		int succesive_cnt = 1;	// 记录以当前访问的元素结尾的最长连续子串的长度
		cnt[p[0] - 'a'] = 1;

		for (int i = 1; i < p.size(); ++i)
		{
			// 若 p[i-1]、p[i] 连续，则增加 successive_cnt
			if (isSuccessive(p[i - 1], p[i]))
				++succesive_cnt;
			// 若 p[i-1]、p[i] 不连续，则重设 successive_cnt 为 1
			else
				succesive_cnt = 1;
			// 更新 cnt[p[i]]
			cnt[p[i] - 'a'] = max(cnt[p[i] - 'a'], succesive_cnt);

		}

		return accumulate(cnt.begin(), cnt.end(), 0);
	}

	bool isSuccessive(char a, char b)
	{
		if ((b + 26 - a) % 26 == 1)
			return true;
		else
			return false;
	}
};

class Solution_v2 {
public:
	int findSubstringInWraproundString(string p)
	{
		if (p.size() < 2)
			return p.size();

		vector<int> cnt(26, 0);
		vector<int> dp(p.size(), 0);
		dp[p.size() - 1] = 1;
		cnt[p.back() - 'a'] = 1;
		for (int i = p.size() - 2; i >= 0; --i)
		{
			if (isSuccessive(p[i], p[i + 1]))
				dp[i] = dp[i + 1] + 1;
			else
				dp[i] = 1;
			cnt[p[i] - 'a'] = max(cnt[p[i] - 'a'], dp[i]);
		}

		return accumulate(cnt.begin(), cnt.end(), 0);
	}

	bool isSuccessive(char a, char b)
	{
		if ((b + 26 - a) % 26 == 1)
			return true;
		else
			return false;
	}
};