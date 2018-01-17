#pragma once

/*

91. Decode Ways

A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given an encoded message containing digits, determine the total number of ways to decode it.

For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

The number of ways decoding "12" is 2.

###########################################
Approach:
DP
�۲죺

"123" => "12" + (3) => "12" + C
		 "1" + (23) => A + W
"12" => "1" + (2) => AB
	 => (12) => L
�� "123" => {ABC, LC, AW} NumOfDec("123") = 2 + 1���� NumOfDec[3] = 3

����
���ڴ�������ַ��� d[0...n-1]��

If n == 0
	Return 0
If d[0] == '0'
	Return 0

NumOfDec[0] = 1
NumOfDec[1] = 1

If d[n-2]d[n-1] <= "26"
	NumOfDec[n] = NumOfDec[n-1] + NumOfDec[n-2]
Else If d[n-2]d[n-1] > "26"
	NumOfDec[n] = NumOfDec[n-1]

corner case: ��"0"�����
If d[n-2]d[n-1] = "00"
	Return 0
If d[n-1] = "0"			// ��ʱ�޷����� d[n-1]����ֻ�ܿ� d[n-2]d[n-1] �ܷ����
	NumOfDec[n] = NumOfDec[n-2]
Else If d[n-2] == "0"	// ��ʱ�޷����� d[n-2]d[n-1]����ֻ�ܿ� d[n-1] �ܷ����
	NumOfDec[n] = NumOfDec[n-1]

����ʹ��DP����������⣬�߼��е㸴�ӡ�����

###########################################
Approach_v2:
DP
�ܽ����� Approach �ķ��������Եó�

d[i-2]d[i-1] ���Խ���������� "09" < d[i-2]d[i-1] <= "26"
d[i-1] ���Խ���������� d[i-1] != '0'

�����У�
�� d[i-2]d[i-1] ���Խ��룬��
	NumOfDec[i] += NumOfDec[i-2]
�� d[i-1] ���Խ��룬��
	NumOfDec[i] += NumOfDec[i-1]
������ NumOfDec[i] == 0���� d[i-2]d[i-1] �� d[i-1] ���޷����룬
	���ַ����޷����룬ֱ�ӷ���0

###########################################
Approach_v3:

����������㵱ǰ NumOfDec[i] ֻҪ�õ� NumOfDec[i-2]��NumOfDec[i-1]�����Կ��Լ��ٿռ��ʹ�á�

*/

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	int numDecodings(string s)
	{
		if (s.empty())
			return 0;
		if (s[0] == '0')
			return 0;

		vector<int> NumOfDec(s.size() + 1, 0);
		NumOfDec[0] = 1;	// ��ʵ�����壬���ڸ�������ļ��㣬ʡȥһ���жϹ��̣�������� i == 2 �� last2char <= "26" ʱ��NumOfDec[2] = NumOfDec[0] + NumOfDec[1] = 2
		NumOfDec[1] = 1;
		for (int i = 2; i <= s.size(); ++i)
		{
			string last2char = s.substr(i - 2, 2);
			if (last2char <= "26")
			{
				if (last2char == "00")	// ���� "00" Ϊ�Ӵ�ʱ���޷�����
					return 0;
				if (last2char[1] == '0')
					NumOfDec[i] = NumOfDec[i - 2];
				else if (last2char[0] == '0')
					NumOfDec[i] = NumOfDec[i - 1];
				else
					NumOfDec[i] = NumOfDec[i - 1] + NumOfDec[i - 2];
			}
			else
			{
				if (last2char[1] == '0')	// ���� "30" �� "40" ���� > 26 �����Ϊ'0'���Ӵ�ʱ���޷�����
					return 0;
				else
					NumOfDec[i] = NumOfDec[i - 1];
			}
		}

		return NumOfDec[s.size()];
	}
};

class Solution_v2 {
public:
	int numDecodings(string s)
	{
		if (s.empty() || s[0] == '0')
			return 0;
		vector<int> dp(s.size() + 1, 0);
		dp[0] = dp[1] = 1;
		for (int i = 2; i < s.size() + 1; ++i)
		{
			string temp = { s[i - 2], s[i - 1] };
			if (temp <= "26" && temp > "09")
				dp[i] += dp[i - 2];
			if (temp[1] != '0')
				dp[i] += dp[i - 1];
			if (dp[i] == 0)
				return 0;
		}
		return dp.back();
	}
};

class Solution_v3 {
public:
	int numDecodings(string s)
	{
		if (s.empty() || s[0] == '0')
			return 0;
		vector<int> dp(2, 0);		// ��ʡ�ռ�
		dp[0] = dp[1] = 1;
		for (int i = 2; i < s.size() + 1; ++i)
		{
			string temp = { s[i - 2], s[i - 1] };
			int curr_res = 0;
			if (temp <= "26" && temp > "09")
				curr_res += dp[(i - 2) % 2];
			if (temp[1] != '0')
				curr_res += dp[(i - 1) % 2];
			if (dp[i % 2] == 0)
				return 0;
			dp[i % 2] = curr_res;
		}
		return dp[s.size() % 2];
	}
};
