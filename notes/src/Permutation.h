#pragma once

/*

求字符串的全排列

Date: 2018.3.20

Write a program to get all permutations of a given string

Ref: https://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/
Ref: https://www.geeksforgeeks.org/permutations-of-a-given-string-using-stl/
Ref: http://blog.csdn.net/hackbuteer1/article/details/7462447

Below are the permutations of string ABC.
ABC ACB BAC BCA CBA CAB

下面的实现中，前两个未考虑去重，后面四个均考虑了去除重复的全排列。

*/

#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <iterator>

using namespace std;

/*
全排列的递归实现
全排列就是从第一个数字起每个数分别与它后面的数字交换。（未去重）
*/
class SolutionRaw {
public:
	// 排列 a[left,left+1,...,right]
	void permuteAux(string& a, int left, int right, vector<string>& result)
	{
		// 若 left == right，说明所有字符的位置已经确定，则为一个排列结果。
		if (left == right)
			result.push_back(a);
		// i 从 left 开始到 right 结束，选择一个数字作为 a[left]。
		for (int i = left; i <= right; ++i)
		{
			swap(a[left], a[i]);
			permuteAux(a, left + 1, right, result);
			swap(a[left], a[i]);	// backtrack
		}
	}

	vector<string> permute(string a)
	{
		vector<string> result;
		if (a.empty())
			return result;
		permuteAux(a, 0, a.size() - 1, result);
		return result;
	}
};


/*
全排列的递归实现(借助 STL std::rotate())
*/
class SolutionRotate {
public:
	void permuteAux(string str, string out, vector<string>& result)
	{
		// When size of str becomes 0, out has a
		// permutation (length of out is n)
		if (str.size() == 0)
		{
			result.push_back(out);
			return;
		}
		for (int i = 0; i < str.size(); ++i)
		{
			// Remove first character from str and
			// add it to out
			permuteAux(str.substr(1), out + str[0], result);
			// Rotate string in a way second character
			// moves to the beginning.
			rotate(str.begin(), str.begin() + 1, str.end());
		}
	}

	vector<string> permute(string a)
	{
		vector<string> result;
		if (a.empty())
			return result;
		string out = "";
		permuteAux(a, out, result);
		return result;
	}
};


/*
去掉重复的全排列的递归实现（基于SolutionRaw）
在全排列中去掉重复的规则：去重的全排列就是从第一个数字起每个数分别与它后面非重复出现的数字交换。
下面给出完整代码：
*/
class SolutionHandleDup_v1 {
public:
	// 在 [left, right) 区间中查找是或否有与 a[right] 相同的字符，若有了，则不能进行 swap，以此来避免重复的排列。
	bool canSwap(string& a, int left, int right)
	{
		for (int i = left; i < right; ++i)
		{
			if (a[i] == a[right])
				return false;
		}
		return true;
	}

	// 排列 a[left,left+1,...,right]
	void permuteAux(string& a, int left, int right, vector<string>& result)
	{
		// 若 left == right，说明所有字符的位置已经确定，则为一个排列结果。
		if (left == right)
			result.push_back(a);
		// i 从 left 开始到 right 结束，选择一个数字作为 a[left]。
		for (int i = left; i <= right; ++i)
		{
			if (canSwap(a, left, i))
			{
				swap(a[left], a[i]);
				permuteAux(a, left + 1, right, result);
				swap(a[left], a[i]);	// backtrack
			}
		}
	}

	vector<string> permute(string a)
	{
		vector<string> result;
		if (a.empty())
			return result;
		permuteAux(a, 0, a.size() - 1, result);
		return result;
	}
};


/*
去重全排列的递归实现(借助 unordered_set 去重)
*/
class SolutionHandleDup_v2 {
public:
	// 排列 a[left,left+1,...,right]
	void permuteAux(string& a, int left, int right, unordered_set<string>& result)
	{
		// 若 left == right，说明所有字符的位置已经确定，则为一个排列结果。
		if (left == right)
			result.insert(a);
		// i 从 left 开始到 right 结束，选择一个数字作为 a[left]。
		for (int i = left; i <= right; ++i)
		{
			swap(a[left], a[i]);
			permuteAux(a, left + 1, right, result);
			swap(a[left], a[i]);	// backtrack
		}
	}

	vector<string> permute(string a)
	{
		vector<string> ret;
		if (a.empty())
			return ret;

		// use unordered_set to remove the duplicates
		unordered_set<string> result;
		permuteAux(a, 0, a.size() - 1, result);
		copy(result.begin(), result.end(), back_inserter(ret));
		return ret;
	}
};


/*
去掉重复的全排列的非递归实现（借助STL中 next_permutation()）
Time: O(n*n!) 
这里每次 next_permutation 最多进行 a.size() / 2 此交换。
*/
class SolutionHandleDup_v3{
public:
	vector<string> permute(string a)
	{
		vector<string> result;
		if (a.empty())
			return result;

		sort(a.begin(), a.end());
		result.push_back(a);
		while (next_permutation(a.begin(), a.end()))
			result.push_back(a);
		return result;
	}
};

/*
去掉重复的全排列的非递归实现（自己写 nextPermutation()）
Ref: http://en.cppreference.com/w/cpp/algorithm/next_permutation
Ref: http://blog.csdn.net/hackbuteer1/article/details/7462447
Ref: 《STL源码剖析》
Time: O(n*n!)
*/
class SolutionHandleDup_v4 {
public:
	vector<string> permute(string a)
	{
		vector<string> result;
		if (a.empty())
			return result;
		sort(a.begin(), a.end());
		result.push_back(a);
		while (nextPermutation(a.begin(), a.end()))
			result.push_back(a);
		return result;
	}
	/*
	参考STL next_permutation() 的写法
	nextPermutation 会取得 [first, last) 所标示序列的下一个排列组合。
	如果没有下一个排列组合，则返回 false；否则返回 true。
	*/
	bool nextPermutation(string::iterator first, string::iterator last)
	{
		// 若字符串为空，则没有下一个排列，返回 false
		if (first == last)
			return false;
		auto i = last;
		// 若字符串中只有一个字符，则没有下一个排列，返回 false
		if (first == --i)
			return false;
		while (true)
		{
			auto i1 = i;
			// 从后向前寻找替换数，即前一个元素i小于后一个元素i1，i即为要替换的数字
			if (*(--i) < *i1)
			{
				// 从后向前寻找第一个比 *i 大的数字 *i2
				auto i2 = last;
				while (!(*i < *--i2))
					;

				// 构造下一个排列
				iter_swap(i, i2);	// 替换 *i, *i2
				reverse(i1, last);	// 替换点 i 后的数全部反转
				return true;
			}
			// i到最前面了，没有找到替换数，当前字符串为最大排列，颠倒得到最小排列，并返回 false。
			if (i == first)
			{
				reverse(first, last);
				return false;
			}
		}
	}
};
