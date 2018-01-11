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

unordered_map 是关联容器，含有带唯一关键的关键-值 pair 。搜索、插入和元素移除拥有平均常数时间复杂度。
元素在内部不以任何特定顺序排序，而是组织进桶中。元素放进哪个桶完全依赖于其关键的哈希。这允许对单独元素的快速访问，因为一旦计算哈希，则它准确指代元素所放进的桶。

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
			// 错误的用法，因为 unordered_map 不以任何特定顺序排序
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