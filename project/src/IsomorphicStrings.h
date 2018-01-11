#pragma once

/*

205. Isomorphic Strings

Given two strings s and t, determine if they are isomorphic.

Two strings are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character but a character may map to itself.

For example,
Given "egg", "add", return true.

Given "foo", "bar", return false.

Given "paper", "title", return true.

Note:
You may assume both s and t have the same length.

Approach false:

unordered_map �ǹ������������д�Ψһ�ؼ��Ĺؼ�-ֵ pair �������������Ԫ���Ƴ�ӵ��ƽ������ʱ�临�Ӷȡ�
Ԫ�����ڲ������κ��ض�˳�����򣬶�����֯��Ͱ�С�Ԫ�طŽ��ĸ�Ͱ��ȫ��������ؼ��Ĺ�ϣ��������Ե���Ԫ�صĿ��ٷ��ʣ���Ϊһ�������ϣ������׼ȷָ��Ԫ�����Ž���Ͱ��

*/

#include <string>
#include <unordered_map>

using namespace std;

class Solution_false {
public:
	bool isIsomorphic(string s, string t)
	{
		unordered_map<char, string> um_s;
		unordered_map<char, string> um_t;

		for (int i = 0; i < s.size(); ++i)
			um_s[s[i]].push_back(i + '0');
		for (int i = 0; i < t.size(); ++i)
			um_t[t[i]].push_back(i + '0');

		for (auto it_s = um_s.begin(), it_t = um_t.begin(); it_s != um_s.end(); ++it_s, ++it_t)
		{
			// ������÷�����Ϊ unordered_map �����κ��ض�˳������
			if (it_s->second != it_t->second)
				return false;
		}
		return true;
	}
};

class Solution {
public:
	bool isIsomorphic(string s, string t)
	{
		unordered_map<char, string> um_s;
		unordered_map<char, string> um_t;

		for (int i = 0; i < s.size(); ++i)
			um_s[s[i]].push_back(i + '0');
		for (int i = 0; i < t.size(); ++i)
			um_t[t[i]].push_back(i + '0');

		for (int i = 0; i < s.size(); ++i)
		{
			if (um_s[s[i]] != um_t[t[i]])
				return false;
		}
		return true;
	}
};