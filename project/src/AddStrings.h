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

�ӵ�λ����λ����string�±��෴�������μ���ÿһλ����ӽ������λΪ0��1������ʱ�������档��ʼʱ����λΪ0.

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