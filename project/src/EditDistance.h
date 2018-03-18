#pragma once

/*

72. Edit Distance

Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. 
(each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character

#################################################################
Approach[TLE]:
Divide and Conquer
string a: a[1...m], string b: b[1...n]
d[i][j] ��ʾ a[1...i] �� b[1...j] �ı༭���롣���У�
�ݹ���ɣ�
If a[i] == b[j], then d[i][j] = d[i-1][j-1]
Else, d[i][j] ȡ�����������Сֵ�������� fxy -> fab �� ED��
	1. d[i-1][j] + 1 ɾ��a[i]��fx->fab �� ED + 1
	2. d[i][j-1] + 1 ��ĩβ���� b[j]��fxyb->fab �� ED + 1 = fxy->fa �� ED + 1
	3. d[i-1][j-1]   �� a[i] �滻Ϊ b[j]��fxb->fab �� ED + 1 = fx->fa �� ED + 1
�ݹ�߽磺
d[i][0] = i��b��Ϊ�գ�����Ҫ��a[1...i]��ȫ��ɾ�����༭����Ϊi��
d[0][j] = j��a��Ϊ�գ���Ҫa�в���b[1...j]���༭����Ϊj��

#################################################################
Approach v2[AC]:
Dynamic Programming

Time: O(m*n)
Space: O(m*n) 

#################################################################
Approach v3[AC]:
Space �����Ż��� O(2*min(m,n)) Solution_v3
����֪������ d[i] ��һ��ʱ��ֻ��Ҫ֪�� d[i-1] ��һ�е�ֵ�����ֻ��Ҫ���м��ɡ�

#################################################################
Approach v4[AC]:
��һ���ģ���ʵ����ֻҪһ�оͿ����ˣ�ÿ�μ����ʱ��������Ҫ3��ֵ��
�����ϱߺ���ߵ�ֵ����ֱ�ӵõ������Ͻǵ�ֵ��Ҫ��ʱ������left_up������¼��
ÿ�θ��µ� i �е� d[j] ֮ǰ��Ҫ�ȱ��ݵ� i-1 �е� d[j] ��ֵ�� left_up �С�

Space�����Ż��� O(min(m,n)) Solution_v4


*/

#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
	int minDistance(string word1, string word2)
	{
		if (word1.size() == 0)
			return word2.size();
		if (word2.size() == 0)
			return word1.size();
		if (word1.back() == word2.back())
		{
			word1.pop_back(), word2.pop_back();
			return minDistance(word1, word2);
		}
		else
		{
			return 1 + minOfThree(
				minDistance(string(word1, 0, word1.length() - 1), word2),
				minDistance(word1, string(word2, 0, word2.length() - 1)),
				minDistance(string(word1, 0, word1.length() - 1), string(word2, 0, word2.length() - 1))
				);
		}
	}

	int minOfThree(int a, int b, int c)
	{
		return min(min(a, b), c);
	}
};

class Solution_v2 {
public:
	int minDistance(string word1, string word2)
	{
		int m = word1.size(), n = word2.size();
		vector<vector<int>> d(m + 1, vector<int>(n + 1, 0));
		for (int i = 0; i <= m; ++i)
		{
			for (int j = 0; j <= n; ++j)
			{
				if (i == 0)
					d[0][j] = j;
				else if (j == 0)
					d[i][0] = i;
				else
				{
					if (word1[i-1] == word2[j-1])
						d[i][j] = d[i - 1][j - 1];
					else
						d[i][j] = minOfThree(d[i - 1][j], d[i][j - 1], d[i - 1][j - 1]) + 1;
				}

			}
		}
		return d[m][n];
	}

	int minOfThree(int a, int b, int c)
	{
		return min(min(a, b), c);
	}
};

class Solution_v3 {
public:
	int minDistance(string word1, string word2)
	{
		// �� word1.size() >= word2.size()
		if (word1.size() < word2.size())
			swap(word1, word2);
		int m = word1.size(), n = word2.size();
		vector<vector<int>> d(2, vector<int>(n + 1, 0));
		for (int i = 0; i <= m; ++i)
		{
			for (int j = 0; j <= n; ++j)
			{
				if (i == 0)
					d[0][j] = j;
				else if (j == 0)
					d[i % 2][0] = i;
				else
				{
					if (word1[i - 1] == word2[j - 1])
						d[i % 2][j] = d[(i - 1) % 2][j - 1];
					else
						d[i % 2][j] = minOfThree(d[(i - 1) % 2][j], d[i % 2][j - 1], d[(i - 1) % 2][j - 1]) + 1;
				}

			}
		}
		return d[m % 2][n];
	}

	int minOfThree(int a, int b, int c)
	{
		return min(min(a, b), c);
	}
};

class Solution_v4 {
public:
	int minDistance(string word1, string word2)
	{
		// �� word1.size() >= word2.size()
		if (word1.size() < word2.size())
			swap(word1, word2);
		int m = word1.size(), n = word2.size();
		vector<int> d(n+1, 0);
		int left_up = 0;			// ���浱ǰ����Ԫ�����Ͻ�����Ԫ�ص�ֵ
		for (int i = 0; i <= m; ++i)
		{
			for (int j = 0; j <= n; ++j)
			{
				if (i == 0)
					d[j] = j;
				else if (j == 0)
				{
					left_up = d[j];	
					d[j] = i;
				}
				else
				{
					if (word1[i - 1] == word2[j - 1])
					{
						swap(left_up, d[j]);
					}
					else
					{
						int temp = d[j];
						d[j] = minOfThree(d[j - 1], d[j], left_up) + 1;
						left_up = temp;
					}
				}

			}
		}
		return d[n];
	}

	int minOfThree(int a, int b, int c)
	{
		return min(min(a, b), c);
	}
};