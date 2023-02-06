#pragma once

/*

13. Roman to Integer

Given a roman numeral, convert it to an integer.

Input is guaranteed to be within the range from 1 to 3999.

Approach:
将当前数字与后面的数字比较，如果比后面的数字小，则减去当前数字，如果大于等于后面数字，则加上当前数字。
对于最后一个数字，一定是加上的。
Ref:http://www.cnblogs.com/grandyang/p/4120857.html

Approach2:
将当前数字与前面的数字比较，如果小于等于前面数字，则加上当前数字，如果大于等于前面数字，则加上当前数字并减去前面数字的二倍。
对于第一个数字，先进行加上处理。
Ref:http://www.cnblogs.com/grandyang/p/4120857.html

*/

#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
	unordered_map<char, int> dict { { 'I', 1 }, { 'V', 5 }, { 'X', 10 }, { 'L', 50 }, { 'C', 100 }, { 'D', 500 }, { 'M', 1000 } };
	int romanToInt(string s)
	{
		int result = 0;
		for (int i = 0; i < s.size(); ++i)
		{
			if (i == s.size() - 1 || dict[s[i]] >= dict[s[i + 1]])
				result += dict[s[i]];
			else
				result -= dict[s[i]];
		}

		return result;
	}
};

class  Solution_v2 {
public:
	unordered_map<char, int> dict { { 'I', 1 }, { 'V', 5 }, { 'X', 10 }, { 'L', 50 }, { 'C', 100 }, { 'D', 500 }, { 'M', 1000 } };
	int romanToInt(string s)
	{
		int result = 0;
		for (int i = 0; i < s.size(); ++i)
		{
			if (i == 0 || dict[s[i]] <= dict[s[i - 1]])
				result += dict[s[i]];
			else
			{
				result += dict[s[i]];
				result -= 2 * dict[s[i - 1]];
			}
		}

		return result;
	}
};