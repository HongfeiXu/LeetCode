#pragma once

/*

345. Reverse Vowels of a String

Write a function that takes a string as input and reverse only the vowels of a string.

Example 1:
Given s = "hello", return "holle".

Example 2:
Given s = "leetcode", return "leotcede".

Note:
The vowels does not include the letter "y".

Approach:
两边夹

*/

#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
	string reverseVowels(string s)
	{
		int i = 0;
		int j = s.size() - 1;
		while (i < j)
		{
			while (!isVowel(s[i]))
				++i;
			while (!isVowel(s[j]))
				--j;
			if (i < j)
				swap(s[i], s[j]);
			++i;
			--j;
		}

		return s;
	}

	bool isVowel(char c)
	{
		c = tolower(c);
		return (c == 'a' || c == 'o' || c == 'e' || c == 'i' || c == 'u');
	}
};
