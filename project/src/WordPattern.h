#pragma once

/*

290. Word Pattern

Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.

Examples:
1. pattern = "abba", str = "dog cat cat dog" should return true.
2. pattern = "abba", str = "dog cat cat fish" should return false.
3. pattern = "aaaa", str = "dog cat cat dog" should return false.
4. pattern = "abba", str = "dog dog dog dog" should return false.
Notes:
You may assume pattern contains only lowercase letters, and str contains lowercase letters separated by a single space.

Approach:
使用两个 unordered_map 来确定是否为双射关系

*/

#include<string>
#include<vector>
#include<unordered_map>
#include<sstream>

using namespace std;

class Solution {
public:
	bool wordPattern(string pattern, string str)
	{
		vector<string> words;

		// 将字符串分割为单词
		stringstream ss(str);
		string temp;
		while (ss >> temp)
			words.push_back(temp);

		if (pattern.size() != words.size())
			return false;

		if (pattern.empty())
			return true;

		unordered_map<char, string> char_to_string;
		unordered_map<string, char> string_to_char;

		char_to_string[pattern[0]] = words[0];
		string_to_char[words[0]] = pattern[0];

		for (int i = 1; i < pattern.size(); ++i)
		{
			// 如果当前字符没有映射到单词上
			if (char_to_string[pattern[i]] == "")
			{
				// 若单词也没有映射到字符上，则添加这对映射
				if (string_to_char[words[i]] == 0)
				{
					char_to_string[pattern[i]] = words[i];
					string_to_char[words[i]] = pattern[i];
				}
				// 否则，不是双射
				else
					return false;
			}
			// 否则，
			else
			{
				// 若当前字符映射到的单词不是当前访问的单词，则不是双射
				if (char_to_string[pattern[i]] != words[i])
					return false;
			}
		}
		return true;
	}
};
