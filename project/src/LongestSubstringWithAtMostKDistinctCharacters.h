#pragma once

/*

340 Longest Substring with At Most K Distinct Characters

Given a string, find the length of the longest substring T that contains at most k distinct characters.

For example, Given s = "eceba" and k = 2,

T is "ece" which its length is 3.

Approach:

Sliding Window���ڵ�ǰ�����м�¼ÿ����ĸ���ֵĸ���
ͨ�������Ҷ˵��������󴰿ڣ��������в�ͬ��ĸ��������k������¼��ʱ�Ĵ��ڴ�С������Ҫ��С���ڡ�
ͨ��������˵�������С���ڣ�ֱ�������в�ͬ��ĸ������k����

�� 159 Longest Substring with At Most Two Distinct Characters ���ơ�

ע��δ����վ�� submit ��֤����Ϊ���ǻ�Ա������

*/

#include <string>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
	int lengthOfSubstringKDistance(string s, int k)
	{
		int begin = 0, end = 0;
		int counter = 0;			// ��¼��ǰ�������ж��ٸ���ͬ����ĸ
		
		int max_len = INT_MIN;
		int curr_len;

		unordered_map<char, int> um;	// ��¼��ǰ������ÿ����ĸ���ֵĸ������� value Ϊ0����ʾ��ǰ�����в����ڸ�����

		while (end < s.size())
		{
			++um[s[end]];
			if (um[s[end]] == 1)
				++counter;
			curr_len = end - begin;
			max_len = max(curr_len, max_len);

			++end;

			while (counter > k)
			{
				--um[s[begin]];
				if (um[s[begin]] == 0)
					--counter;
				++begin;
			}
		}

		curr_len = end - begin;
		max_len = max(curr_len, max_len);
		return max_len;
	}
};
