#pragma once

/*

415. Add Strings

Given two non-negative integers num1 and num2 represented as string, return the sum of num1 and num2.

Note:

The length of both num1 and num2 is < 5100.
Both num1 and num2 contains only digits 0-9.
Both num1 and num2 does not contain any leading zero.
You must not use any built-in BigInteger library or convert the inputs to integer directly.

Approach:

从低位到高位（与string下标相反），依次计算每一位的相加结果，进位为0或1，用临时变量保存。初始时，进位为0.

*/

#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
	string addStrings(string num1, string num2)
	{
		string result;

		// 为了方便后面的处理
		// 将 num1 与 num2 变为相同位数的数字
		if (num1.size() > num2.size())
			swap(num1, num2);
		size_t gap = num2.size() - num1.size();	// 使用 gap 是因为 num2.size() - num1.size() 在循环中会改变
		for (size_t i = 0; i < gap; ++i)
			num1.insert(num1.begin(), '0');

		size_t len = num1.size();

		int carry = 0;							// 保存进位，最低位进行相加运算时，进位一定为0
		for (int i = 0; i < len; ++i)
		{
			int oneDigitSum = num1[len - 1 - i] - '0' + num2[len - 1 - i] - '0' + carry;
			if (oneDigitSum > 9)
			{
				char temp = (oneDigitSum % 10) + '0';
				result.insert(result.begin(), temp);		// 将当前数位和的结果保存到 result，通过头插法插入
				carry = 1;		// 向高位进位1
			}
			else
			{
				char temp = oneDigitSum + '0';
				result.insert(result.begin(), temp);
				carry = 0;		// 向高位进位0
			}
		}
		if (carry != 0)
			result.insert(result.begin(), '1');

		return result;
	}
};