#pragma once

/*

67. Add Binary

Given two binary strings, return their sum (also a binary string).

For example,
a = "11"
b = "1"
Return "100".

Approach:
������ת��Ϊ10���ƣ�������ӣ�Ȼ�󽫽��ת��Ϊ2����
���֣������ֺܶ�λʱ��������������

Approach:
�����ڴ�����ӣ�ʹ��һ������¼��λ�����

*/

#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
	string addBinary(string a, string b)
	{
		int a_ = stoi(a, NULL, 2);
		int b_ = stoi(b, NULL, 2);
		int c = a_ + b_;

		string result;
		Decimal2Binary(c, result);

		return result;
	}

	void Decimal2Binary(int num, string& result)
	{
		int mod = num % 2;
		num = num / 2;
		if (num != 0)
		{
			Decimal2Binary(num, result);
		}
		result.push_back(mod + '0');
	}
};

class Solution_v2 {
public:
	string addBinary(string a, string b)
	{
		// ��֤aΪ�϶̵��ַ���
		if (a.size() > b.size())
			swap(a, b);

		int len = a.size();

		int len_a = a.size();
		int len_b = b.size();

		string result;		// ��¼�����push_back��ͷ����죬����������ʱ��������������ţ�����ʹ�÷�����������췵��ֵ
		int carry_digit = 0;// ��¼��λֵ����ʼΪ0
		for (int i = 0; i < len; ++i)
		{
			if (a[len_a - 1 - i] == '0' && b[len_b - 1 - i] == '0')
			{
				result.push_back('0' + carry_digit);
				carry_digit = 0;
			}
			else if (a[len_a - 1 - i] == '1' && b[len_b - 1 - i] == '1')
			{
				result.push_back('0' + carry_digit);
				carry_digit = 1;
			}
			else
			{
				if (carry_digit == 0)
				{
					result.push_back('1');
					carry_digit = 0;
				}
				else
				{
					result.push_back('0');
					carry_digit = 1;
				}
			}
		}
		for (int i = len; i < len_b; ++i)
		{
			if (b[len_b - 1- i] == '0')
			{
				result.push_back('0' + carry_digit);
				carry_digit = 0;
			}
			else if (b[len_b - 1 - i] == '1')
			{
				if (carry_digit == 0)
				{
					result.push_back('1');
					carry_digit = 0;
				}
				else
				{
					result.push_back('0');
					carry_digit = 1;
				}
			}
		}
		if (carry_digit == 1)
			result.push_back('1');

		return string(result.rbegin(), result.rend());
	}
};