#pragma once

/*

13. Roman to Integer

Given a roman numeral, convert it to an integer.

Input is guaranteed to be within the range from 1 to 3999.

Approach:
����ǰ�������������ֱȽϣ�����Ⱥ��������С�����ȥ��ǰ���֣�������ڵ��ں������֣�����ϵ�ǰ���֡�
�������һ�����֣�һ���Ǽ��ϵġ�
Ref:http://www.cnblogs.com/grandyang/p/4120857.html

Approach2:
����ǰ������ǰ������ֱȽϣ����С�ڵ���ǰ�����֣�����ϵ�ǰ���֣�������ڵ���ǰ�����֣�����ϵ�ǰ���ֲ���ȥǰ�����ֵĶ�����
���ڵ�һ�����֣��Ƚ��м��ϴ���
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