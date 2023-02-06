#pragma once

/*

557. Reverse Words in a String III

Given a string, you need to reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.

Example 1:
Input: "Let's take LeetCode contest"
Output: "s'teL ekat edoCteeL tsetnoc"
Note: In the string, each word is separated by single space and there will not be any extra space in the string.


Approach:
使用 stringstream 进行单词分割

Approach2:
扩展：
stringstream 不能直接使用逗号来分割一句话，可结合 getline 函数进行解析


*/

#include <string>
#include <sstream>

using namespace std;

class Solution {
public:
	string reverseWords(string s)
	{
		stringstream buf1;
		buf1 << s;
		
		string result;
		string temp;
		while (buf1 >> temp)
		{
			result.append(string(temp.rbegin(), temp.rend()));
			result.push_back(' ');
		}
		result.pop_back();		// 弹出最后一个空格

		return result;
	}
};


// 扩展内容：利用 stringstream + getline 实现以逗号为分割符时语句的解析
// 	cout << solution.reverseWords("hello,world,I,am,HongFei") << endl;

class Solution_v2 {
public:
	string reverseWords(string s)
	{
		stringstream buf1;
		buf1 << s;

		string result;
		string temp;
		while (getline(buf1, temp, ','))
		{
			result.append(string(temp.rbegin(), temp.rend()));
			result.push_back(' ');
		}
		result.pop_back();		// 弹出最后一个空格

		return result;
	}
};
