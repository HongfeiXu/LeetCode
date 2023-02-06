#pragma once

/*
Date: 2018.3.20
输入一个字符串，输出该字符串中字符的所有组合。举个例子，如果输入abc，它的组合有a、b、c、ab、ac、bc、abc。

Ref: http://blog.csdn.net/hackbuteer1/article/details/7462447
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

求str中长度为1,2,3,...,str.size()的组合，则，只需要调用 combineAux 传入不同的长度作为参数即可。
*/
class Solution_v2 {
public:
	vector<string> combine(string str)
	{
		vector<string> result;
		// 依次得到长为 1,2,...,str.size() 的组合
		for (int i = 1; i <= str.size(); ++i)
		{
			string curr = "";
			combineAux(str, 0, i, curr, result);
		}
		return result;
	}

	/*
	在字符串 str的子串 str[i,i+1,...,str.size() - 1] 中选择长为 m 的字符组合
	str: 输入字符串
	i: 当前访问到的位置
	curr: 当前组合
	result: 结果

	str.size() - i  为余下的字符长度
	*/
	void combineAux(const string& str, int i, int m, string& curr, vector<string>& result)
	{
		// 选取完成
		if (m == 0)
		{
			result.push_back(curr);
			return;
		}

		// 字符串遍历完毕但未完成 m 次选取
		//if (i == str.size())
		//{
		//	return;
		//}

		// 若余下的字符全部选择也不足以达到还需要的 m，则直接返回（剪枝）
		if (str.size() - i < m)
			return;

		// 选择 str[i]，则在余下的字符 str[i+1,...,str.size()-1] 中选择 m-1 个字符
		curr.push_back(str[i]);
		combineAux(str, i + 1, m - 1, curr, result);
		curr.pop_back();
		// 不选择 str[i]，则在余下的字符 str[i+1,...,str.size()-1] 中选择 m 个字符
		combineAux(str, i + 1, m, curr, result);
	}
};
