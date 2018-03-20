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
������Ҫע���������Ϊ32λ���з��������������������ֳ��� [INT_MIN, INT_MAX] ��Χʱ������ 0��
�������������һ���Ƿ�Χ�ڵ����֣��������������ֵĳ��Ȳ��ᳬ�� INT_MIN ���� INT_MAX �ĳ��ȡ�
��ֻ�е������� INT_MIN ���� INT_MAX ������ͬʱ�����п��ܳ�����Χ��

Approach v2:
��һ�� long long ���͵����� val ���洢 x ����������Ȼ������ INT_MIN �� INT_MAX �Ƚϣ����ڷ�Χ֮�⣬�򷵻�0������ֱ�ӷ��� val��
��Ȼ����Ŀ˵������һ��32λ��ϵͳ������SO WHAT?


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
			s.insert(s.begin(), '-');	// ���Ϸ���
			// ���s��int_min_str������ͬ��������ַ�����εĴ�С�Ƚϣ����ڶ��Ǹ������ϴ���ַ������н�С����ֵ
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