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
ֱ�ӵķ���
���� num1.size() < num2.size()
�򣬶� num1 ��ÿһλ���е�����ÿһ�����������У��� num2 ��֮��ˣ��õ��˻����ڳ˻�����������ɸ�0��Ϊ��˽��
���� num1.size��������˽�������� AddString() ���̼������ս��

Ӧ���и��õķ�ʽ

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

		int carry = 0;		// ��¼��λ����ֵΪ0
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

		// Ϊ�˷������Ĵ���
		// �� num1 �� num2 ��Ϊ��ͬλ��������
		if (num1.size() > num2.size())
			swap(num1, num2);
		size_t gap = num2.size() - num1.size();	// ʹ�� gap ����Ϊ num2.size() - num1.size() ��ѭ���л�ı�
		for (size_t i = 0; i < gap; ++i)
			num1.insert(num1.begin(), '0');

		size_t len = num1.size();

		int carry = 0;							// �����λ�����λ�����������ʱ����λһ��Ϊ0
		for (int i = 0; i < len; ++i)
		{
			int oneDigitSum = num1[len - 1 - i] - '0' + num2[len - 1 - i] - '0' + carry;
			if (oneDigitSum > 9)
			{
				char temp = (oneDigitSum % 10) + '0';
				result.insert(result.begin(), temp);		// ����ǰ��λ�͵Ľ�����浽 result��ͨ��ͷ�巨����
				carry = 1;		// ���λ��λ1
			}
			else
			{
				char temp = oneDigitSum + '0';
				result.insert(result.begin(), temp);
				carry = 0;		// ���λ��λ0
			}
		}
		if (carry != 0)
			result.insert(result.begin(), '1');

		return result;
	}
};