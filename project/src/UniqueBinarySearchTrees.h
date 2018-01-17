#pragma once

/*

96. Unique Binary Search Trees

Given n, how many structurally unique BST's (binary search trees) that store values 1...n?

For example,
Given n = 3, there are a total of 5 unique BST's.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

Approach:

�������� 1...n���������κ�������Ϊ���ڵ㣬Ȼ���ڹ�������������������
��������ڵ���Ϊ�������������� a �֣��������� b �֣����ʱ���Թ��� a * b �����������������ͼ��õ� 1...n ��UBST������
��ʾ���£�
UB: Unique Binary Search Trees
UB[n] = Sum{UB[i] * UB[n-i-1]}, i=0,...,n-1
UB[0] = 1��������ĳһ������Ϊ��
��Ȼ�����ʼ n == 0����ֱ�ӷ��� 0

ʹ�ö�̬�滮�����Ե��������� UB[1...n]
Time: O(n^2)
Space: O(n)

*/

#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

class Solution {
public:
	int numTrees(int n)
	{
		if (n == 0)
			return 0;
		vector<int> UB(n + 1, 0);
		UB[0] = 1;
		for (int i = 1; i <= n; ++i)
		{
			// ��i�����֣�1..i�����ܹ���� unique binary search trees ����Ŀ
			for (int j = 1; j <= i; ++j)
			{
				// j Ϊ���ڵ㣬�������� j-1 ���ڵ㣬�������� i-j ���ڵ�
				UB[i] += UB[j - 1] * UB[i - j];
			}
		}
		return UB[n];
	}
};

