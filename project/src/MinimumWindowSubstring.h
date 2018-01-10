#pragma once

/*

76. Minimum Window Substring

Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"
Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the empty string "".

If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S.

Approach:

使用 Sliding Window 算法， 类似于 438. Find All Anagrams in a String

Ref: Ref: https://leetcode.com/problems/find-all-anagrams-in-a-string/discuss/92007/

*/

#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
	string minWindow(string s, string t)
	{
		string result;

		if (t.size() > s.size())
			return result;
		
		unordered_map<char, int> stillneed;
		for (auto c : t)
			++stillneed[c];

		int begin = 0, end = 0;
		int counter = stillneed.size();

		int len = INT_MAX;		// 保存满足条件的窗口的最小长度

		// loop at the begining of the source string
		while (end < s.size())
		{
			if (stillneed.find(s[end]) != stillneed.end())
			{
				--stillneed[s[end]];
				if (stillneed[s[end]] == 0)
					--counter;
			}
			++end;

			// increase begin pointer to make it invalid/valid again
			while (counter == 0)
			{
				if (end - begin < len)
				{
					len = end - begin;
					result = s.substr(begin, len);
				}
				
				if (stillneed.find(s[begin]) != stillneed.end())
				{
					++stillneed[s[begin]];
					if (stillneed[s[begin]] > 0)
						++counter;
				}
				++begin;
			}
		}

		return result;
	}
};