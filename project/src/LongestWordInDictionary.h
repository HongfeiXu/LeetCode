#pragma once

/*

720. Longest Word in Dictionary

Given a list of strings words representing an English Dictionary, 
find the longest word in words that can be built one character at a time by other words in words. 
If there is more than one possible answer, return the longest word with the smallest lexicographical order.

If there is no answer, return the empty string.

Example 1:
Input:
words = ["w","wo","wor","worl", "world"]
Output: "world"
Explanation:
The word "world" can be built one character at a time by "w", "wo", "wor", and "worl".
Example 2:
Input:
words = ["a", "banana", "app", "appl", "ap", "apply", "apple"]
Output: "apple"
Explanation:
Both "apply" and "apple" can be built from other words in the dictionary. However, "apple" is lexicographically smaller than "apply".

Note:

All the strings in the input will only contain lowercase letters.
The length of words will be in the range [1, 1000].
The length of words[i] will be in the range [1, 30].

Approach:

使用 unordered_set 记录那些以及确定可以每次添加一个字母构成的单词
先对 words 排序，然后对于长度为 1 的单词，直接放入 unordered_set 中，
对于长度为 n 的单词，若其前 n-1 个字符构成的子串在 unordered_set 中，则该单词也放入 unordered_set 中。

*/

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Solution {
public:

	string longestWord(vector<string>& words)
	{
		// 按照单词的长度对 words 进行从小到大排序
		sort(words.begin(), words.end());
		
		unordered_set<string> built;		// 记录那些以及确定可以每次添加一个字母构成的单词
		for (int i = 0; i < words.size(); ++i)
		{
			if (words[i].size() == 1)		// 对于长度为 1 的单词，直接放入 unordered_set 中
				built.insert(words[i]);
			else if(words[i].empty())		
				continue;
			else							// 对于长度为 n 的单词，若其前 n-1 个字符构成的子串在 unordered_set 中，则该单词也放入 unordered_set 中
			{
				string temp = words[i].substr(0, words[i].size() - 1);
				if (built.find(temp) != built.end())
					built.insert(words[i]);
			}
		}

		string result = "";
		for (auto it = built.begin(); it != built.end(); ++it)
		{
			if (it->size() > result.size())
				result = *it;
			else if (it->size() == result.size())
				result = min(result, *it);
		}
		return result;
	}
};
