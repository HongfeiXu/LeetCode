#pragma once

/*

20. Valid Parentheses

Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.

Approach:

Use stack

*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	bool isValid(string s)
	{
		vector<char> stack;

		if (s.size() == 0)
			return true;

		vector<char> leftBrackets { '(', '{', '[' };

		for (unsigned i = 0; i < s.size(); i++)
		{
			switch (s[i])
			{
			case '(':
			case '{':
			case '[':
				stack.push_back(s[i]);
				break;
			case ')':
				if (stack.empty() || stack.back() != '(')
					return false;
				else
					stack.pop_back();
				break;
			case '}':
				if (stack.empty() || stack.back() != '{')
					return false;
				else
					stack.pop_back();
				break;
			case ']':
				if (stack.empty() || stack.back() != '[')
					return false;
				else
					stack.pop_back();
				break;
			}
		}

		if (stack.empty())
			return true;
		else
			return false;
	}

	bool isValid_v2(string s)
	{
		vector<char> stack;

		if (s.size() == 0)
			return true;

		for (unsigned i = 0; i < s.size(); i++)
		{
			switch (s[i])
			{
			case '(':
				stack.push_back(')');
				break;
			case '{':
				stack.push_back('}');
				break;;
			case '[':
				stack.push_back(']');
				break;
			case ')':
			case '}':
			case ']':
				if (stack.empty() || stack.back() != s[i])
					return false;
				stack.pop_back();
				break;
			}
		}
		return stack.empty();
	}
};
