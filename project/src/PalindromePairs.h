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

�ؼ�˼�룺
1.�õ��ʵ��湹��hash��
2. �ָ��Ϊ left��right���ֱ���

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
		
		// 1. ����һ�� hash�� key �����е��ʵ���ת��value �ǵ��ʵ��±�
		unordered_map<string, int> um;
		for (int i = 0; i < words.size(); ++i)
		{
			string temp(words[i].rbegin(), words[i].rend());
			um[temp] = i;
		}

		// 2. ��ÿ�����ʣ��ָ�Ϊ left �� right��
		// �� hash ��������left��������,�ж� right �Ƿ�Ϊ�����֣�����ǣ��� left|right|searched ����һ��������
		// �� hash ��������right�������ڣ��ж�left�Ƿ�Ϊ�����֣�����ǣ��� searched|left|right ����һ��������
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