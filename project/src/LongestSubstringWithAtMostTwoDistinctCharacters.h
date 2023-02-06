#pragma once

/*

159 Longest Substring with At Most Two Distinct Characters

Given a string S, find the length of the longest substring T that contains at most two distinct characters.
For example,
Given S = "eceba",
T is "ece" which its length is 3.

Approach:

Sliding Window，在当前窗口中记录每个字母出现的个数
通过窗口右端递增，增大窗口，若窗口中不同字母个数超过2个，记录此时的窗口大小，并需要缩小窗口。
通过窗口左端递增，缩小窗口，直到窗口中不同字母数降到2个。

与 340 Longest Substring with At Most K Distinct Characters 类似。

注：未在网站上 submit 验证，因为不是会员。。。

*/

#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
	int lengthOfLongestSubstringTwoDistinct(string s)
	{
		int begin = 0, end = 0;
		int counter = 0;		// 记录当前窗口中有多少个不同的字母
		
		int max_len = INT_MIN;
		int curr_len;

		unordered_map<char, int> um;	// 记录当前窗口中字母出现的个数，若 value 为0，表示当前窗口中不存在该数字

		while (end < s.size())
		{
			++um[s[end]];
			if (um[s[end]] == 1)
				++counter;

			curr_len = end - begin;
			max_len = max(max_len, curr_len);

			++end;

			while (counter > 2)
			{
				--um[s[begin]];
				if (um[s[begin]] == 0)
					--counter;
				++begin;
			}
		}

		max_len = max(max_len, curr_len);
		return max_len;
	}
};
