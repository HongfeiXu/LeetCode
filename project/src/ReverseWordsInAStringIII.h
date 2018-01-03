#pragma once

/*

557. Reverse Words in a String III

Given a string, you need to reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.

Example 1:
Input: "Let's take LeetCode contest"
Output: "s'teL ekat edoCteeL tsetnoc"
Note: In the string, each word is separated by single space and there will not be any extra space in the string.


Approach:
ʹ�� stringstream ���е��ʷָ�

Approach2:
��չ��
stringstream ����ֱ��ʹ�ö������ָ�һ�仰���ɽ�� getline �������н���


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
		result.pop_back();		// �������һ���ո�

		return result;
	}
};


// ��չ���ݣ����� stringstream + getline ʵ���Զ���Ϊ�ָ��ʱ���Ľ���
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
		result.pop_back();		// �������һ���ո�

		return result;
	}
};
