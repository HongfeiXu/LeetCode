#pragma once

/*

���ַ�����ȫ����

Date: 2018.3.20

Write a program to get all permutations of a given string

Ref: https://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/
Ref: https://www.geeksforgeeks.org/permutations-of-a-given-string-using-stl/
Ref: http://blog.csdn.net/hackbuteer1/article/details/7462447

Below are the permutations of string ABC.
ABC ACB BAC BCA CBA CAB

�����ʵ���У�ǰ����δ����ȥ�أ������ĸ���������ȥ���ظ���ȫ���С�

*/

#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

/*
ȫ���еĵݹ�ʵ��
ȫ���о��Ǵӵ�һ��������ÿ�����ֱ�������������ֽ�������δȥ�أ�
*/
class SolutionRaw {
public:
	// ���� a[left,left+1,...,right]
	void permuteAux(string& a, int left, int right, vector<string>& result)
	{
		// �� left == right��˵�������ַ���λ���Ѿ�ȷ������Ϊһ�����н����
		if (left == right)
			result.push_back(a);
		// i �� left ��ʼ�� right ������ѡ��һ��������Ϊ a[left]��
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
		permuteAux(a, 0, a.size() - 1, result);
		return result;
	}
};


/*
ȫ���еĵݹ�ʵ��(���� STL std::rotate())
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
		string out = "";
		permuteAux(a, out, result);
		return result;
	}
};


/*
ȥ���ظ���ȫ���еĵݹ�ʵ�֣�����SolutionRaw��
��ȫ������ȥ���ظ��Ĺ���ȥ�ص�ȫ���о��Ǵӵ�һ��������ÿ�����ֱ�����������ظ����ֵ����ֽ�����
��������������룺
*/
class SolutionHandleDup_v1 {
public:
	// �� [left, right) �����в����ǻ������ a[right] ��ͬ���ַ��������ˣ����ܽ��� swap���Դ��������ظ������С�
	bool canSwap(string& a, int left, int right)
	{
		for (int i = left; i < right; ++i)
		{
			if (a[i] == a[right])
				return false;
		}
		return true;
	}

	// ���� a[left,left+1,...,right]
	void permuteAux(string& a, int left, int right, vector<string>& result)
	{
		// �� left == right��˵�������ַ���λ���Ѿ�ȷ������Ϊһ�����н����
		if (left == right)
			result.push_back(a);
		// i �� left ��ʼ�� right ������ѡ��һ��������Ϊ a[left]��
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
		permuteAux(a, 0, a.size() - 1, result);
		return result;
	}
};


/*
ȥ��ȫ���еĵݹ�ʵ��(���� unordered_set ȥ��)
*/
class SolutionHandleDup_v2 {
public:
	// ���� a[left,left+1,...,right]
	void permuteAux(string& a, int left, int right, unordered_set<string>& result)
	{
		// �� left == right��˵�������ַ���λ���Ѿ�ȷ������Ϊһ�����н����
		if (left == right)
			result.insert(a);
		// i �� left ��ʼ�� right ������ѡ��һ��������Ϊ a[left]��
		for (int i = left; i <= right; ++i)
		{
			swap(a[left], a[i]);
			permuteAux(a, left + 1, right, result);
			swap(a[left], a[i]);	// backtrack
		}
	}

	vector<string> permute(string a)
	{
		// use unordered_set to remove the duplicates
		unordered_set<string> result;
		permuteAux(a, 0, a.size() - 1, result);

		vector<string> ret;
		copy(result.begin(), result.end(), back_inserter(ret));
		return ret;
	}
};


/*
ȥ���ظ���ȫ���еķǵݹ�ʵ�֣�����STL�� next_permutation()��
Time: O(n*n!) 
����ÿ�� next_permutation ������ a.size() / 2 �˽�����
*/
class SolutionHandleDup_v3{
public:
	vector<string> permute(string a)
	{
		sort(a.begin(), a.end());
		vector<string> result;
		result.push_back(a);
		while (next_permutation(a.begin(), a.end()))
			result.push_back(a);
		return result;
	}
};

/*
ȥ���ظ���ȫ���еķǵݹ�ʵ�֣��Լ�д nextPermutation()��
Ref: http://en.cppreference.com/w/cpp/algorithm/next_permutation
Ref: http://blog.csdn.net/hackbuteer1/article/details/7462447
Ref: ��STLԴ��������
Time: O(n*n!)
*/
class SolutionHandleDup_v4 {
public:
	vector<string> permute(string a)
	{
		sort(a.begin(), a.end());
		vector<string> result;
		result.push_back(a);
		while (nextPermutation(a.begin(), a.end()))
			result.push_back(a);
		return result;
	}
	/*
	�ο�STL next_permutation() ��д��
	nextPermutation ��ȡ�� [first, last) ����ʾ���е���һ��������ϡ�
	���û����һ��������ϣ��򷵻� false�����򷵻� true��
	*/
	bool nextPermutation(string::iterator first, string::iterator last)
	{
		// ���ַ���Ϊ�գ���û����һ�����У����� false
		if (first == last)
			return false;
		auto i = last;
		// ���ַ�����ֻ��һ���ַ�����û����һ�����У����� false
		if (first == --i)
			return false;
		while (true)
		{
			auto i1 = i;
			// �Ӻ���ǰѰ���滻������ǰһ��Ԫ��iС�ں�һ��Ԫ��i1��i��ΪҪ�滻������
			if (*(--i) < *i1)
			{
				// �Ӻ���ǰѰ�ҵ�һ���� *i ������� *i2
				auto i2 = last;
				while (!(*i < *--i2))
					;

				// ������һ������
				iter_swap(i, i2);	// �滻 *i, *i2
				reverse(i1, last);	// �滻�� i �����ȫ����ת
				return true;
			}
			// i����ǰ���ˣ�û���ҵ��滻������ǰ�ַ���Ϊ������У��ߵ��õ���С���У������� false��
			if (i == first)
			{
				reverse(first, last);
				return false;
			}
		}
	}
};
