#pragma once

/*

3. Longest Substring Without Repeating Characters

Given a string, find the length of the longest substring without repeating characters.

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. 
Note that the answer must be a substring, "pwke" is a subsequence and not a substring.

Approach:
Sliding Window ���� [begin, end)
ʹ��һ�� unordered_map<char, int> ��¼��ǰ������ÿ����ĸ���ֵĴ���

�� s[end] �� um �е�ֵΪ 0���� s[end] ��ӵ� um������ ++end
�� s[end] �� um ��ֵ��Ϊ 0����[begin, end)Ϊ��ǰһ���������ظ���ĸ�ĳ��Ӵ�������� max_len�������л��� ++begin ��ģʽ

++begin ����
�� s[begin] �� um �м�ȥ��ÿ�ζ���� s[end] ��ֵ�Ƿ��Ϊ 1������Ϊ1�����ʱ���ظ���ĸ��++end,Ȼ�󷵻�++endģʽ��

Approach v2:
�������������ƣ�ֻ��ʹ�� unordered_set ������ unordered_map����Ϊ����ֻ��Ҫ��¼����һ�ε���ĸ

Approach v3:

ʹ�� Sliding Window algorithm template ��������Ӵ��������⡣COOL�����Ref��
Ref: https://leetcode.com/problems/find-all-anagrams-in-a-string/discuss/92007/

*/

#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
	int lengthOfLongestSubstring(string s)
	{
		if (s.empty())
			return 0;

		int begin = 0, end = 0;	// [begin, end) Ϊ��ǰ����
		int max_len = 1;
		unordered_map<char, int> um;
		
		int a_switch = 1;		// �� ���� Ϊ1���� ++end��������Ϊ0���� ++begin

		while (end != s.size())
		{
			// ++end ģʽ
			if (um[s[end]] == 0)
			{
				++um[s[end]];
				++end;
			}
			else
			{
				max_len = max(max_len, end - begin);
				++um[s[end]];
				a_switch = 0;
			}

			// ++begin ģʽ
			while (a_switch == 0)
			{
				--um[s[begin]];
				//if (um[s[end]] == 1)	// ��֮ǰ�ظ�����ĸ������һ��������� ++end
				if(s[end] == s[begin])	// ��ɾ��Ԫ��Ϊ end ָ����Ǹ�Ԫ�أ������ ++end
				{
					a_switch = 1;
					++end;
				}
				++begin;
			}
		}
		// ������ַ��������� s ��ĩβ������Ҫ�ڴ��ж� max_len �� end-begin �Ĵ�С��ȡ�ϴ���Ǹ�
		max_len = max(max_len, end - begin);
		return max_len;
	}
};

class Solution_v2 {
public:
	int lengthOfLongestSubstring(string s)
	{
		if (s.empty())
			return 0;

		int begin = 0, end = 0;	// [begin, end) Ϊ��ǰ����
		int max_len = 1;
		unordered_set<char> us;	// ������ظ��� [begin,end) �е�Ԫ��

		int a_switch = 1;		// �� ���� Ϊ1���� ++end��������Ϊ0���� ++begin

		while (end != s.size())
		{
			// ++end ģʽ
			if (us.find(s[end]) == us.end())
			{
				us.insert(s[end]);
				++end;
			}
			// ���� s[end] �����������ظ��������Ҫ ++begin���Ӷ�ɾ�������е�һ���� s[end]��ȵ��ַ�
			else
			{
				max_len = max(max_len, end - begin);
				a_switch = 0;
			}

			// ++begin ģʽ
			while (a_switch == 0)
			{
				us.erase(s[begin]);
				// �� s[begin] Ϊ�� s[end] ��ȵ��ַ������ʱ���Խ� s[end] ��ӵ� us ��
				if (s[end] == s[begin])	
				{
					a_switch = 1;
					us.insert(s[end]);
					++end;
				}
				++begin;
			}
		}
		// ������ַ��������� s ��ĩβ������Ҫ�ڴ��ж� max_len �� end-begin �Ĵ�С��ȡ�ϴ���Ǹ�
		max_len = max(max_len, end - begin);
		return max_len;
	}
};

class Solution_v3 {
public:
	int lengthOfLongestSubstring(string s)
	{
		if (s.empty())
			return 0;

		unordered_map<char, int> um;
		int begin = 0, end = 0;			// [begin, end) Ϊ��ǰ����
		int max_len = 0, counter = 0;

		while (end < s.length())
		{
			char c = s[end];
			++um[c];
			if (um[c] > 1)
				++counter;
			++end;

			// �����������ظ���ĸ�����ֻ��������ĸ����ͬ�ģ���ͨ���ƶ�����ʼ��ɾ����ĸ
			while (counter > 0)
			{
				char c = s[begin];
				if (um[c] > 1)	// �ҵ��ظ���ĸ���˴�ѭ�����ٽ���ɾ��������ȥ�����ƶ�����ĩ��
					--counter;
				--um[s[begin]];
				++begin;
			}

			max_len = max(max_len, end - begin);
		}
		// ������ַ��������� s ��ĩβ������Ҫ�ڴ��ж� max_len �� end-begin �Ĵ�С��ȡ�ϴ���Ǹ�
		max_len = max(max_len, end - begin);
	
		return max_len;
	}
};
