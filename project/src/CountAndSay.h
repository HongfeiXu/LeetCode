#pragma once

/*

The count-and-say sequence is the sequence of integers with the first five terms as following:

1.     1
2.     11
3.     21
4.     1211
5.     111221
1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.
Given an integer n, generate the nth term of the count-and-say sequence.

Note: Each term of the sequence of integers will be represented as a string.

Example 1:

Input: 1
Output: "1"
Example 2:

Input: 4
Output: "1211"

Approach:
��ʼnΪ 1 ʱ�����Ϊ"1"
��n>1�����е�������2��n������n����
	ÿ�ε������൱�ڼ�¼ÿ�������������ֵĴ�����֮�󹹳ɽ������
����n-1�˵����õ����

*/

#include <string>

using namespace std;

class Solution {
public:
	string countAndSay(int n)
	{
		string result("1");

		if (n == 1)
			return result;

		for (int i = 2; i <= n; ++i)
		{
			string tempResult;
			for (int j = 0; j < result.size(); )
			{
				int count = 1;
				// ��һ������ʽ����Ҫ
				while ((j + count < result.size()) && (result[j] == result[j + count]))
					++count;

				tempResult.push_back(count + '0');
				tempResult.push_back(result[j]);

				j += count;
			}
			result = tempResult;
		}
		return result;
	}
};