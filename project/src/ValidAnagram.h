#pragma once

/*

242. Valid Anagram

Given two strings s and t, write a function to determine if t is an anagram of s.

For example,
s = "anagram", t = "nagaram", return true.
s = "rat", t = "car", return false.

Note:
You may assume the string contains only lowercase alphabets.

Follow up:
What if the inputs contain unicode characters? How would you adapt your solution to such case?

Approach:
use unordered_map

*/

#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
	bool isAnagram(string s, string t)
	{
		if (s.size() != t.size())
			return false;

		unordered_map<char, int> char_to_int;
		for (auto c : t)
			++char_to_int[c];

		for (auto c : s)
		{
			--char_to_int[c];
			if (char_to_int[c] == 0)
				char_to_int.erase(c);
		}

		return char_to_int.empty();
	}
};

class Solution_v2 {
public:
	bool isAnagram(string s, string t)
	{
		if (s.size() != t.size())
			return false;

		unordered_map<char, int> um_s;
		unordered_map<char, int> um_t;
		for (auto c : s)
			++um_s[c];

		for (auto c : t)
			++um_t[c];

		return um_s == um_t;
	}
};

