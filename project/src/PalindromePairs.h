#pragma once

/*

336. Palindrome Pairs

Given a list of unique words, find all pairs of distinct indices (i, j) in the given list, so that the concatenation of the two words, 
i.e. words[i] + words[j] is a palindrome.

Example 1:
Given words = ["bat", "tab", "cat"]
Return [[0, 1], [1, 0]]
The palindromes are ["battab", "tabbat"]
Example 2:
Given words = ["abcd", "dcba", "lls", "s", "sssll"]
Return [[0, 1], [1, 0], [3, 2], [2, 4]]
The palindromes are ["dcbaabcd", "abcddcba", "slls", "llssssll"]

Approach:
Time Limit Exceeded...

Approach 2:
word->left|right
left|right|newword if left = reverse(newword) && right is Palindrome then left|right|newword si a Palindrome

关键思想：
1.用单词的逆构造hash表
2. 分割单词为 left，right，分别查表

*/

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
	vector<vector<int>> palindromePairs(vector<string>& words)
	{
		vector<vector<int>> result;

		for (int i = 0; i < words.size(); ++i)
		{
			for (int j = 0; j < words.size(); ++j)
			{
				if(i == j)
					continue;

				string s = words[i] + words[j];
				if (isPalindrome(s))
				{
					vector<int> temp = { i, j };
					result.push_back(temp);
				}
			}
		}
		return result;
	}

	bool isPalindrome(const string& s)
	{
		int i = 0;
		int j = static_cast<int>(s.size()) - 1;
		while (i < j)
		{
			if (s[i++] != s[j--])
				return false;
		}

		return true;
	}
};

class Solution_v2 {
public:
	vector<vector<int>> palindromePairs(vector<string>& words)
	{
		vector<vector<int>> result;
		
		// 1. 构造一个 hash表， key 是所有单词的逆转，value 是单词的下标
		unordered_map<string, int> um;
		for (int i = 0; i < words.size(); ++i)
		{
			string temp(words[i].rbegin(), words[i].rend());
			um[temp] = i;
		}

		// 2. 对每个单词，分割为 left 和 right，
		// 在 hash 表中搜索left，若存在,判断 right 是否为回文字，如果是，则 left|right|searched 构成一个回文字
		// 在 hash 表中搜索right，若存在，判断left是否为会文字，如果是，则 searched|left|right 构成一个回文字
		for (int i = 0; i < words.size(); ++i)
		{
			// edge case: if empty string "" exists, find all palindromes to become pairs ("", self)
			if (words[i].size() == 0)
			{
				for (int j = 0; j < words.size(); ++j)
				{
					if (i == j)
						continue;
					if (isPalindrome(words[j]))	// 1) if self is palindrome, here ans covers concatenate("", self)
					{
						result.push_back({ i, j });
					}
				}
			}
			else
			{
				string left, right;
				for (int k = 0; k < words[i].size(); ++k)
				{
					left = string(words[i].begin(), words[i].begin() + k);
					right = string(words[i].begin() + k, words[i].end());
					if (um.find(left) != um.end() && isPalindrome(right) && um[left] != i)
						result.push_back({ i,um[left] });	// 2) when k = 0, left = "", right = self, so here covers concatenate(self, "")
					if (um.find(right) != um.end() && isPalindrome(left) && um[right] != i)
						result.push_back({ um[right], i });
				}
			}
		}

		return result;
	}

	bool isPalindrome(const string& s)
	{
		int i = 0;
		int j = static_cast<int>(s.size()) - 1;
		while (i < j)
		{
			if (s[i++] != s[j--])
				return false;
		}

		return true;
	}
};