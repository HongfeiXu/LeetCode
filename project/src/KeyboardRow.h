#pragma once

/*

500. Keyboard Row

Given a List of words, return the words that can be typed using letters of alphabet on only one row's of American keyboard like the image below.

https://leetcode.com/static/images/problemset/keyboard.png

Example 1:
Input: ["Hello", "Alaska", "Dad", "Peace"]
Output: ["Alaska", "Dad"]
Note:
You may use one character in the keyboard more than once.
You may assume the input string will only contain letters of alphabet.

*/

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
	vector<string> findWords(vector<string>& words)
	{
		vector<string> lines = { "qwertyuiopQWERTYUIOP", "asdfghjklASDFGHJKL", "zxcvbnmZXCVBNM" };

		unordered_map<char, int> char_to_line;
		for (int i = 0; i < lines.size(); ++i)
		{
			for (char c : lines[i])
				char_to_line[c] = i;
		}

		vector<string> result;
		for (int i = 0; i < words.size(); ++i)
		{
			if (isOneRowWord(words[i], char_to_line))
				result.push_back(words[i]);
		}

		return result;
	}

	bool isOneRowWord(const string& s, unordered_map<char, int>& char_to_line)
	{
		if (s.size() < 2)
			return true;

		int row_id = char_to_line[s[0]];
		for (int i = 1; i < s.size(); ++i)
		{
			if (row_id != char_to_line[s[i]])
				return false;
		}
		return true;
	}
};