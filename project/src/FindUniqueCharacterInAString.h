#pragma once

/*

387. First Unique Character in a String

Given a string, find the first non-repeating character in it and return it's index. If it doesn't exist, return -1.

Examples:

s = "leetcode"
return 0.

s = "loveleetcode",
return 2.
Note: You may assume the string contain only lowercase letters.

Approach:

��ǰ�������������ǰ��ĸ�ں���Ҳ���֣������ unordered_set �У�
����֮��ÿ����ĸ������ʱ�������ж��Ƿ��Լ������������У�����Ѿ����ڣ�����һ���Ƿ�unique�ģ�ֱ��������һ�ε���
�����ǰ���ʵ���ĸ��֮���ÿ����ĸ����ͬ����һ���ǵ�һ�� unique �ġ�
*/

#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
	int firstUniqChar(string s)
	{
		unordered_set<char> non_unique_chars;
		for (int i = 0; i < s.size(); ++i)
		{
			// �����ǰ�ַ��Լ�ȷ������ unique �ģ��������һ�ε���
			if (non_unique_chars.find(s[i]) != non_unique_chars.end())
				continue;
			int j;
			for (j = i + 1; j < s.size(); ++j)
			{
				if (s[i] == s[j])
				{
					non_unique_chars.insert(s[i]);
					break;
				}
			}
			if (j == s.size())
				return i;
		}
		return -1;
	}
};