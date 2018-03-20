#pragma once

/*

����һ���ַ�����������ַ������ַ���������ϡ��ٸ����ӣ��������abc�����������a��b��c��ab��ac��bc��abc��

Date: 2018.3.20

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

��s�г���Ϊ1,2,3,...,s.size()����ϣ���ֻ��Ҫ���� combineAux ���벻ͬ�ĳ�����Ϊ�������ɡ�
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
		// ���s�Ѿ�Ϊ�գ�˵��û���ַ��ɹ�ѡ�񣬶���ʱm��Ϊ0��˵����δ��ѡ���㹻���ַ�������
		if (s.empty())
			return;
		// ������ַ��ŵ������ȥ��������������Ҫ��ʣ�µ�s.size()-1���ַ���ѡȡm-1���ַ�
		curr.push_back(s[0]);
		combineAux(s.substr(1), m - 1, curr, result);
		curr.pop_back();
		// ��������ַ��ŵ������ȥ��������������Ҫ��ʣ�µ�s.size() - 1���ַ���ѡ��m���ַ�
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
