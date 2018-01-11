#pragma once

/*

159 Longest Substring with At Most Two Distinct Characters

Given a string S, find the length of the longest substring T that contains at most two distinct characters.
For example,
Given S = "eceba",
T is "ece" which its length is 3.

Approach:

Sliding Window���ڵ�ǰ�����м�¼ÿ����ĸ���ֵĸ���
ͨ�������Ҷ˵��������󴰿ڣ��������в�ͬ��ĸ��������2������¼��ʱ�Ĵ��ڴ�С������Ҫ��С���ڡ�
ͨ��������˵�������С���ڣ�ֱ�������в�ͬ��ĸ������2����

�� 340 Longest Substring with At Most K Distinct Characters ���ơ�

ע��δ����վ�� submit ��֤����Ϊ���ǻ�Ա������

*/

#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
	int lengthOfLongestSubstringTwoDistinct(string s)
	{
		int begin = 0, end = 0;
		int counter = 0;		// ��¼��ǰ�������ж��ٸ���ͬ����ĸ
		
		int max_len = INT_MIN;
		int curr_len;

		unordered_map<char, int> um;	// ��¼��ǰ��������ĸ���ֵĸ������� value Ϊ0����ʾ��ǰ�����в����ڸ�����

		while (end < s.size())
		{
			++um[s[end]];
			if (um[s[end]] == 1)
				++counter;

			curr_len = end - begin;
			max_len = max(max_len, curr_len);

			++end;

			while (counter > 2)
			{
				--um[s[begin]];
				if (um[s[begin]] == 0)
					--counter;
				++begin;
			}
		}

		max_len = max(max_len, curr_len);
		return max_len;
	}
};
