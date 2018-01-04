#pragma once

/*

28. Implement strStr()

Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

Example 1:

Input: haystack = "hello", needle = "ll"
Output: 2
Example 2:

Input: haystack = "aaaaa", needle = "bba"
Output: -1

Approach:

Brute force.

*/

#include <string>

using namespace std;

class Solution {
public:
	int strStr(string haystack, string needle)
	{
		int len_haystack = haystack.size();
		int len_needle = needle.size();
		
		if (len_haystack < len_needle)
			return -1;

		for (int i = 0; i < len_haystack - len_needle + 1; ++i)
		{
			string temp(haystack, i, len_needle);
			if (temp == needle)
				return i;
		}
		return -1;
	}
};