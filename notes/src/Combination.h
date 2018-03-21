#pragma once

/*
Date: 2018.3.20
����һ���ַ�����������ַ������ַ���������ϡ��ٸ����ӣ��������abc�����������a��b��c��ab��ac��bc��abc��

Ref: http://blog.csdn.net/hackbuteer1/article/details/7462447
*/

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

/*
�����ַ�����ÿһ���ַ�����ÿ�������ֻ�����������Ҫô���ڣ�Ҫô�����ڡ�
�����ַ���ʼ���ݹ�õ��������ַ�����ϣ����������ַ�����ϡ�
���յõ�����Ϊ1,2,3,...,s.size()�����
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

	// a Ϊ������ַ���
	// i ��ʾ��ǰҪѡ����ַ� a[i]��Ҫô���뵱ǰ��ϣ�Ҫô������
	// curr ��ʾ��ǰ���
	// result �����������
	void combineAux(const string& a, int i, string& curr,  vector<string>& result)
	{
		if (i == a.size())
		{
			// ���������
			if (curr.empty())
				return;
			result.push_back(curr);
			return;
		}

		// �� a[i] ���뵱ǰ���
		curr.push_back(a[i]);
		combineAux(a, i + 1, curr, result);
		curr.pop_back();	// backtrack
		// ���� a[i] ���뵱ǰ���
		combineAux(a, i + 1, curr, result);
	}
};

/*
�����������ڳ���Ϊn���ַ�������m���ַ�����ϡ������ȴ�ͷɨ���ַ����ĵ�һ���ַ���
��Ե�һ���ַ�������������ѡ��
��һ�ǰ�����ַ��ŵ������ȥ��������������Ҫ��ʣ�µ�n-1���ַ���ѡȡm-1���ַ���
�ڶ��ǲ�������ַ��ŵ������ȥ��������������Ҫ��ʣ�µ�n-1���ַ���ѡ��m���ַ���

��str�г���Ϊ1,2,3,...,str.size()����ϣ���ֻ��Ҫ���� combineAux ���벻ͬ�ĳ�����Ϊ�������ɡ�
*/
class Solution_v2 {
public:
	vector<string> combine(string str)
	{
		vector<string> result;
		// ���εõ���Ϊ 1,2,...,str.size() �����
		for (int i = 1; i <= str.size(); ++i)
		{
			string curr = "";
			combineAux(str, 0, i, curr, result);
		}
		return result;
	}

	/*
	���ַ��� str���Ӵ� str[i,i+1,...,str.size() - 1] ��ѡ��Ϊ m ���ַ����
	str: �����ַ���
	i: ��ǰ���ʵ���λ��
	curr: ��ǰ���
	result: ���

	str.size() - i  Ϊ���µ��ַ�����
	*/
	void combineAux(const string& str, int i, int m, string& curr, vector<string>& result)
	{
		// ѡȡ���
		if (m == 0)
		{
			result.push_back(curr);
			return;
		}

		// �ַ���������ϵ�δ��� m ��ѡȡ
		//if (i == str.size())
		//{
		//	return;
		//}

		// �����µ��ַ�ȫ��ѡ��Ҳ�����Դﵽ����Ҫ�� m����ֱ�ӷ��أ���֦��
		if (str.size() - i < m)
			return;

		// ѡ�� str[i]���������µ��ַ� str[i+1,...,str.size()-1] ��ѡ�� m-1 ���ַ�
		curr.push_back(str[i]);
		combineAux(str, i + 1, m - 1, curr, result);
		curr.pop_back();
		// ��ѡ�� str[i]���������µ��ַ� str[i+1,...,str.size()-1] ��ѡ�� m ���ַ�
		combineAux(str, i + 1, m, curr, result);
	}
};
