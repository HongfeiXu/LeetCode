#pragma once

/*

438. Find All Anagrams in a String

Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

Strings consists of lowercase English letters only and the length of both strings s and p will not be larger than 20,100.

The order of output does not matter.

Example 1:

Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
Example 2:

Input:
s: "abab" p: "ab"

Output:
[0, 1, 2]

Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".

Approach:
Time Limit Exceeded
对p建立一个 unordered_map， (K, V) = (Character, Frequence of the Characters)
然后遍历s，对每个位置，取一个长为 p.size() 的子串，建立 unordered_map，看两个 unordered_map 是否相同

Approach_v2:

使用 Sliding Window algorithm template 解决这类子串搜索问题。COOL。详见Ref。

对 p 建立一个 unordered_map，命名为 stillneed，表示在当前的窗口中，需要各个字符的数目。
窗口用 begin，end 表示。
用 counter 记录当前窗口内的字符在个数上是否满足了要求，可以多于 p 中要求的各个字符数。

Ref: https://leetcode.com/problems/find-all-anagrams-in-a-string/discuss/92007/


*/

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
	vector<int> findAnagrams(string s, string p)
	{
		unordered_map<char, int> char_to_int;
		for (int i = 0; i < p.size(); ++i)
			++char_to_int[p[i]];

		vector<int> result;

		if (p.size() > s.size() || p.size() == 0)
			return result;

		for (int i = 0; i < s.size() - p.size() + 1; ++i)
		{
			unordered_map<char, int> temp;
			for (int j = 0; j < p.size(); ++j)
				++temp[s[i + j]];
			if (temp == char_to_int)
				result.push_back(i);
		}

		return result;
	}
};

class Solution_v2 {
public:
	vector<int> findAnagrams(string s, string p)
	{
		vector<int> result;

		if (p.size() > s.size())
			return result;

		unordered_map<char, int> stillneed;
		for (auto c : p)
			++stillneed[c];

		int begin = 0, end = 0;
		// maintain a counter to check whether match the target string.
		int counter = stillneed.size(); 

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

			//increase begin pointer to make it invalid/valid again
			while (counter == 0)
			{
				if (end - begin == p.size())
					result.push_back(begin);
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