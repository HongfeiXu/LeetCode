#pragma once

/*

8. String to Integer (atoi)

Implement atoi to convert a string to an integer.

Hint: Carefully consider all possible input cases. If you want a challenge, please do not see below and ask yourself what are the possible input cases.

Notes: It is intended for this problem to be specified vaguely (ie, no given input specs). You are responsible to gather all the input requirements up front.

*/

#include <string>

using namespace std;

class Solution {
public:
	int myAtoi(string str)
	{
		int num = 0;
		int sign = 1;
		int offset = 0;

		// 跳过空格
		while (offset < str.size() && str[offset] == ' ')
			++offset;
		if (str[offset] == '+')
			++offset;
		else if (str[offset] == '-')
		{
			++offset;
			sign = -1;
		}

		// 访问连续的数字字符
		int a = INT_MAX / 10;
		int b = INT_MAX % 10;
		for (int i = offset; i < str.size(); ++i)
		{
			// 遇到非数字，退出循环
			if (str[i] < '0' || str[i] > '9')
				break;

			int digit = str[i] - '0';
			if (num > a || (num == a && digit > b))
			{
				// 超过范围 INT_MAX
				if (sign == 1)
					return INT_MAX;
				// 达到或超过范围 INT_MIN
				else
					return INT_MIN;
			}
			num *= 10;
			num += digit;
		}
		return sign * num;
	}
};
