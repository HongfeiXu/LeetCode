#pragma once

/*

344. Reverse String

Write a function that takes a string as input and returns the string reversed.

Example:
Given s = "hello", return "olleh".

Approach:
ʹ�÷�����������ռ临�Ӷ�ΪO(n)

Approach:
�������࣬�ռ临�Ӷ�ΪO(1)

*/

#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
	string reverseString(string s)
	{
		return string(s.rbegin(), s.rend());
	}
};

class Solution_v2 {
public:
	string reverseString(string s)
	{
		int mid = s.size() / 2;
		int len = s.size();
		for (int i = 0; i < mid; ++i)
		{
			swap(s[i], s[len - 1 - i]);
		}

		return s;
	}
};