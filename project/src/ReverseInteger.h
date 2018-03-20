#pragma once

/*

7. Reverse Integer

Given a 32-bit signed integer, reverse digits of an integer.

Example 1:

Input: 123
Output:  321

Example 2:

Input: -123
Output: -321
Example 3:

Input: 120
Output: 21
Note:
Assume we are dealing with an environment which could only hold integers within the 32-bit signed integer range. 
For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.

Approach:
beat 0.23%
这里需要注意的是数字为32位的有符号整数，当其逆序数字超过 [INT_MIN, INT_MAX] 范围时，返回 0。
由于输入的数字一定是范围内的数字，所以其逆序数字的长度不会超过 INT_MIN 或者 INT_MAX 的长度。
且只有当长度与 INT_MIN 或者 INT_MAX 长度相同时，才有可能超出范围。

Approach v2:
用一个 long long 类型的整数 val 来存储 x 的逆序数，然后将其与 INT_MIN 和 INT_MAX 比较，若在范围之外，则返回0，否则直接返回 val。
当然，题目说了这是一个32位的系统，，，SO WHAT?


*/

#include <string>
#include <algorithm>
#include <climits>


class Solution {
public:
	int reverse(int x)
	{
		std::string int_max_str = std::to_string(INT_MAX);
		std::string int_min_str = std::to_string(INT_MIN);
		std::string s = std::to_string(x);
		if (s[0] == '-')
		{
			s.erase(s.begin());
			std::reverse(s.begin(), s.end());
			s.insert(s.begin(), '-');	// 加上符号
			// 如果s与int_min_str长度相同，则进行字符串层次的大小比较，由于都是负数，较大的字符串具有较小的数值
			if (s.size() == int_min_str.size() && s > int_min_str)		
				return 0;
			else
				return stoi(s);
		}
		else if(s[0] == '+')
		{
			s.erase(s.begin());
			std::reverse(s.begin(), s.end());
			if (s.size() == int_max_str.size() && s > int_max_str)
				return 0;
			else
				return stoi(s);
		}
		else
		{
			std::reverse(s.begin(), s.end());
			if (s.size() == int_max_str.size() && s > int_max_str)
				return 0;
			else
				return stoi(s);
		}
	}
};

class Solution_v2 {
public:
	int reverse(int x)
	{
		long long val = 0;
		while (x)
		{
			val = val * 10 + x % 10;
			x = x / 10;
		}
		return (val > INT_MAX || val < INT_MIN) ? 0 : val;
	}
};