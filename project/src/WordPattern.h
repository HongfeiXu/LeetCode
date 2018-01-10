#pragma once

/*

290. Word Pattern

Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.

Examples:
1. pattern = "abba", str = "dog cat cat dog" should return true.
2. pattern = "abba", str = "dog cat cat fish" should return false.
3. pattern = "aaaa", str = "dog cat cat dog" should return false.
4. pattern = "abba", str = "dog dog dog dog" should return false.
Notes:
You may assume pattern contains only lowercase letters, and str contains lowercase letters separated by a single space.

Approach:
ʹ������ unordered_map ��ȷ���Ƿ�Ϊ˫���ϵ

*/

#include<string>
#include<vector>
#include<unordered_map>
#include<sstream>

using namespace std;

class Solution {
public:
	bool wordPattern(string pattern, string str)
	{
		vector<string> words;

		// ���ַ����ָ�Ϊ����
		stringstream ss(str);
		string temp;
		while (ss >> temp)
			words.push_back(temp);

		if (pattern.size() != words.size())
			return false;

		if (pattern.empty())
			return true;

		unordered_map<char, string> char_to_string;
		unordered_map<string, char> string_to_char;

		char_to_string[pattern[0]] = words[0];
		string_to_char[words[0]] = pattern[0];

		for (int i = 1; i < pattern.size(); ++i)
		{
			// �����ǰ�ַ�û��ӳ�䵽������
			if (char_to_string[pattern[i]] == "")
			{
				// ������Ҳû��ӳ�䵽�ַ��ϣ���������ӳ��
				if (string_to_char[words[i]] == 0)
				{
					char_to_string[pattern[i]] = words[i];
					string_to_char[words[i]] = pattern[i];
				}
				// ���򣬲���˫��
				else
					return false;
			}
			// ����
			else
			{
				// ����ǰ�ַ�ӳ�䵽�ĵ��ʲ��ǵ�ǰ���ʵĵ��ʣ�����˫��
				if (char_to_string[pattern[i]] != words[i])
					return false;
			}
		}
		return true;
	}
};
