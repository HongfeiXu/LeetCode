#pragma once

/*

43. Multiply Strings

Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2.

Note:

The length of both num1 and num2 is < 110.
Both num1 and num2 contains only digits 0-9.
Both num1 and num2 does not contain any leading zero.
You must not use any built-in BigInteger library or convert the inputs to integer directly.

Approach:
直接的方法
假设 num1.size() < num2.size()
则，对 num1 的每一位进行迭代，每一个迭代过程中，用 num2 与之相乘，得到乘积，在乘积后面添加若干个0，为相乘结果
保存 num1.size（）个相乘结果，调用 AddString() 过程计算最终结果

应该有更好的方式

*/

#include <iostream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

class Solution {
public:
	string multiply(string num1, string num2)
	{
		if (num1.size() > num2.size())
			swap(num1, num2);

		string result = "0";
		for (int i = 0; i < num1.size(); ++i)
		{
			string tempResult = multiply(num2, num1[num1.size() - 1 - i]);
			for (int j = 0; j < i; ++j)
				tempResult.push_back('0');
			result = addStrings(result, tempResult);
		}
		return result;
	}

	string multiply(string num1, char c)
	{
		string result;

		if (c == '0')
			return string("0");
		else if (c == '1')
			return num1;

		int carry = 0;		// 记录进位，初值为0
		for (int i = 0; i < num1.size(); ++i)
		{
			int oneDigitMulti = (num1[num1.size() - 1 - i] - '0') * (c - '0') + carry;
			if (oneDigitMulti > 9)
			{
				char temp = (oneDigitMulti % 10) + '0';
				result.insert(result.begin(), temp);
				carry = oneDigitMulti / 10;
			}
			else
			{
				char temp = oneDigitMulti + '0';
				result.insert(result.begin(), temp);
				carry = 0;
			}
		}
		if (carry != 0)
			result.insert(result.begin(), carry + '0');

		return result;
	}

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