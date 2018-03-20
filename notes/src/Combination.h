#pragma once

/*

输入一个字符串，输出该字符串中字符的所有组合。举个例子，如果输入abc，它的组合有a、b、c、ab、ac、bc、abc。

Date: 2018.3.20

*/

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

/*
对于字符串中每一个字符，在每个组合中只有两种情况，要么存在，要么不存在。
从首字符开始，递归得到包括该字符的组合，不包括该字符的组合。
最终得到长度为1,2,3,...,s.size()的组合
*/
class Solution {
public:
	vector<string> combine(string s)
	{
		vector<string> result;
		string curr = "";
		combineAux(s, 0, curr, result);
		return result;
	}

	// a 为输入的字符串
	// i 表示当前要选择的字符 a[i]，要么放入当前组合，要么不放入
	// curr 表示当前组合
	// result 保存所有组合
	void combineAux(const string& a, int i, string& curr,  vector<string>& result)
	{
		if (i == a.size())
		{
			// 跳过空组合
			if (curr.empty())
				return;
			result.push_back(curr);
			return;
		}

		// 将 a[i] 放入当前组合
		curr.push_back(a[i]);
		combineAux(a, i + 1, curr, result);
		curr.pop_back();	// backtrack
		// 不把 a[i] 放入当前组合
		combineAux(a, i + 1, curr, result);
	}
};

/*
假设我们想在长度为n的字符串中求m个字符的组合。我们先从头扫描字符串的第一个字符。
针对第一个字符，我们有两种选择：
第一是把这个字符放到组合中去，接下来我们需要在剩下的n-1个字符中选取m-1个字符；
第二是不把这个字符放到组合中去，接下来我们需要在剩下的n-1个字符中选择m个字符。

求s中长度为1,2,3,...,s.size()的组合，则，只需要调用 combineAux 传入不同的长度作为参数即可。
*/
class Solution_v2 {
public:
	void combineAux(string s, int m, string& curr, vector<string>& result)
	{
		if (m == 0)
		{
			result.push_back(curr);
			return;
		}
		// 如果s已经为空，说明没有字符可供选择，而此时m不为0，说明还未能选够足够的字符，返回
		if (s.empty())
			return;
		// 把这个字符放到组合中去，接下来我们需要在剩下的s.size()-1个字符中选取m-1个字符
		curr.push_back(s[0]);
		combineAux(s.substr(1), m - 1, curr, result);
		curr.pop_back();
		// 不把这个字符放到组合中去，接下来我们需要在剩下的s.size() - 1个字符中选择m个字符
		combineAux(s.substr(1), m, curr, result);
	}

	vector<string> combine(string s)
	{
		vector<string> result;
		string curr = "";
		for(int i = 1; i <= s.size(); ++i)
			combineAux(s, i, curr, result);
		return result;
	}
};
