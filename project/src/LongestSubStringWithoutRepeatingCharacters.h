#pragma once

/*

3. Longest Substring Without Repeating Characters

Given a string, find the length of the longest substring without repeating characters.

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. 
Note that the answer must be a substring, "pwke" is a subsequence and not a substring.

Approach:
Sliding Window 方法 [begin, end)
使用一个 unordered_map<char, int> 记录当前窗口中每个字母出现的次数

若 s[end] 在 um 中的值为 0，则将 s[end] 添加到 um，继续 ++end
若 s[end] 在 um 中值不为 0，则[begin, end)为当前一个不存在重复字母的长子串，则更新 max_len，并且切换到 ++begin 的模式

++begin 部分
将 s[begin] 从 um 中减去，每次都检测 s[end] 的值是否变为 1，若变为1，则此时无重复字母，++end,然后返回++end模式。

Approach v2:
方法与上面类似，只是使用 unordered_set 而不是 unordered_map，因为我们只需要记录存在一次的字母

Approach v3:

使用 Sliding Window algorithm template 解决这类子串搜索问题。COOL。详见Ref。
Ref: https://leetcode.com/problems/find-all-anagrams-in-a-string/discuss/92007/

*/

#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
	int lengthOfLongestSubstring(string s)
	{
		if (s.empty())
			return 0;

		int begin = 0, end = 0;	// [begin, end) 为当前窗口
		int max_len = 1;
		unordered_map<char, int> um;
		
		int a_switch = 1;		// 若 开关 为1，则 ++end，若开关为0，则 ++begin

		while (end != s.size())
		{
			// ++end 模式
			if (um[s[end]] == 0)
			{
				++um[s[end]];
				++end;
			}
			else
			{
				max_len = max(max_len, end - begin);
				++um[s[end]];
				a_switch = 0;
			}

			// ++begin 模式
			while (a_switch == 0)
			{
				--um[s[begin]];
				//if (um[s[end]] == 1)	// 若之前重复的字母被弹出一个，则继续 ++end
				if(s[end] == s[begin])	// 若删除元素为 end 指向的那个元素，则继续 ++end
				{
					a_switch = 1;
					++end;
				}
				++begin;
			}
		}
		// 若最长的字符串出现在 s 的末尾，则需要在此判断 max_len 与 end-begin 的大小，取较大的那个
		max_len = max(max_len, end - begin);
		return max_len;
	}
};

class Solution_v2 {
public:
	int lengthOfLongestSubstring(string s)
	{
		if (s.empty())
			return 0;

		int begin = 0, end = 0;	// [begin, end) 为当前窗口
		int max_len = 1;
		unordered_set<char> us;	// 存放无重复的 [begin,end) 中的元素

		int a_switch = 1;		// 若 开关 为1，则 ++end，若开关为0，则 ++begin

		while (end != s.size())
		{
			// ++end 模式
			if (us.find(s[end]) == us.end())
			{
				us.insert(s[end]);
				++end;
			}
			// 若将 s[end] 放入则会出现重复，因此需要 ++begin，从而删除掉其中的一个与 s[end]相等的字符
			else
			{
				max_len = max(max_len, end - begin);
				a_switch = 0;
			}

			// ++begin 模式
			while (a_switch == 0)
			{
				us.erase(s[begin]);
				// 若 s[begin] 为与 s[end] 相等的字符，则此时可以将 s[end] 添加到 us 中
				if (s[end] == s[begin])	
				{
					a_switch = 1;
					us.insert(s[end]);
					++end;
				}
				++begin;
			}
		}
		// 若最长的字符串出现在 s 的末尾，则需要在此判断 max_len 与 end-begin 的大小，取较大的那个
		max_len = max(max_len, end - begin);
		return max_len;
	}
};

class Solution_v3 {
public:
	int lengthOfLongestSubstring(string s)
	{
		if (s.empty())
			return 0;

		unordered_map<char, int> um;
		int begin = 0, end = 0;			// [begin, end) 为当前窗口
		int max_len = 0, counter = 0;

		while (end < s.length())
		{
			char c = s[end];
			++um[c];
			if (um[c] > 1)
				++counter;
			++end;

			// 若窗口中有重复字母（最多只有两个字母是相同的），通过移动窗口始端删除字母
			while (counter > 0)
			{
				char c = s[begin];
				if (um[c] > 1)	// 找到重复字母，此次循环后不再接着删除，而是去接着移动窗口末端
					--counter;
				--um[s[begin]];
				++begin;
			}

			max_len = max(max_len, end - begin);
		}
		// 若最长的字符串出现在 s 的末尾，则需要在此判断 max_len 与 end-begin 的大小，取较大的那个
		max_len = max(max_len, end - begin);
	
		return max_len;
	}
};
