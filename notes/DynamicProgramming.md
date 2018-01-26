# Dynamic Programming

## ʲô�Ƕ�̬�滮

>Ref: http://blog.csdn.net/v_JULY_v/article/details/6110269

��̬�滮һ��Ҳֻ��Ӧ�����������ӽṹ�����⡣�����ӽṹ����˼�Ǿֲ����Ž��ܾ���ȫ�����Ž�(����Щ�������Ҫ�󲢲�����ȫ���㣬����ʱ��Ҫ����һ���Ľ���)���򵥵�˵�������ܹ��ֽ�����������������̬�滮�㷨������4�����裺
1. �������Ž�Ľṹ
2. �ݹ鶨�����Ž��ֵ
3. ���Ե����ϵķ�ʽ�������Ž��ֵ   //��3�����ɶ�̬�滮��Ļ�����
4. �ɼ�����Ľ������һ�����Ž⡣   //�˲����ֻҪ��������Ž��ֵʱ����ʡ�ԡ�

���������ʺϲ��ö�̬�滮���������Ż����������Ҫ�أ������ӽṹ���ʣ����������ص����ʡ�

- �����ӽṹ

�����������Ž���������������Ľ�Ҳ�����ŵģ����ǾͳƸ�������������ӽṹ���ʣ����������Ż�ԭ������˼���ǣ�����������ܶ�������⣬����Щ������Ľ�Ҳ�����ŵġ�

- �ص�������

�������ص�������ָ���õݹ��㷨�Զ����¶�����������ʱ��ÿ�β����������Ⲣ�����������⣬��Щ������ᱻ�ظ������Ρ���̬�滮�㷨����������������������ص����ʣ���ÿһ��������ֻ����һ�Σ�Ȼ���������������һ������У����ٴ���Ҫ�����Ѿ��������������ʱ��ֻ���ڱ���м򵥵ز鿴һ�½�����Ӷ���ýϸߵ�Ч�ʡ�

## ��̬�滮�㷨�⡰LCS ���⡱

>Ref: https://www.geeksforgeeks.org/longest-common-subsequence/

### LCS Problem Statement
Given two sequences, find the length of longest subsequence present in both of them. 
A subsequence is a sequence that appears in the same relative order, but not necessarily contiguous. 

For example, ��abc��, ��abg��, ��bdf��, ��aeg��, ����acefg��, .. etc are subsequences of ��abcdefg��. 
So a string of length n has 2^n different possible subsequences.

Let us see how this problem possesses both important properties of a Dynamic Programming (DP) Problem.

**1. Optimal Substructure**

**Input :** X[0..m-1], Y[0..n-1] 

Let L(X[0..m-1], Y[0..n-1]) be the length of LCS of X and Y   
**If** X[m-1]==Y[n-1] then   
L(X[0..m-1], Y[0..n-1]) = L(X[0..m-2], Y[0..n-2]) + 1   
**Else**   
L(X[0..m-1], Y[0..n-1]) = max(L(X[0..m-2], Y[0..n-1]), L(X[0..m-1], Y[0..n-2]))   
So the LCS problem has optimal substructure property as the main problem can be solved using solutions to subproblems.

**2. Overlapping Subproblems**

Following "Solution" is simple recursive implementation of the LCS problem. The implementation simply follows the recursive structure mentioned above.

### Solve LCS Problem 

�����������6��ʵ�֣���Ӧ�˲�ͬ������

1. Naive recursive implementation
2. Dynamic Programming C/C++ implementation of LCS problem
3. Space Optimized Dynamic Programming C/C++ implementation of LCS problem
4. Printing Longest Common Subsequence
5. Printing Longest Common Subsequence with an auxiliary Table

![LCS_TABLE](https://github.com/HongfeiXu/LeetCode/blob/master/images/LCS_table.png?raw=true)

��ͼ��ʾ��L[0..m, 0..n] �������Լ� B[1..m, 1..n] ������

```c++
#pragma once

#include <string>
#include <algorithm>
#include <vector>

using namespace std;

/* 1. A Naive recursive implementation of LCS problem */
class Solution {
public:
	/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
	int LCS(const string& X, const string& Y, int m, int n)
	{
		if(m == 0 || n == 0)
			return 0;
		if (X[m] == Y[n])
			return 1 + LCS(X, Y, m - 1, n - 1);
		else
			return max(LCS(X, Y, m - 1, n), LCS(X, Y, m, n - 1));
	}
};
/*
Time complexity of the above naive recursive approach is O(2^n) in worst case 
and worst case happens when all characters of X and Y mismatch i.e., length of LCS is 0.
*/


/* 2. Dynamic Programming C/C++ implementation of LCS problem */
class Solution_DP {
public:
	/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
	int LCS(const string& X, const string& Y, int m, int n)
	{
		// L[i, j] ��ʾ X[0..i-1] �� Y[0..j-1] �� LCS �ĳ���
		vector<vector<int>> L(m + 1);
		for (int i = 0; i < m + 1; ++i)
			L[i].assign(n + 1, 0);

		// Following steps build L[m+1][n+1] in bottom up fashion.
		for (int i = 0; i < m + 1; ++i)
		{
			for (int j = 0; j < n + 1; ++j)
			{
				if (i == 0 || j == 0)
					L[i][j] = 0;
				else if (X[i - 1] == Y[j - 1])	// ������񣬷������������±�Ϊ���� i-1 ������ i
					L[i][j] = L[i - 1][j - 1] + 1;
				else
					L[i][j] = max(L[i - 1][j], L[i][j - 1]);
			}
		}

		return L[m][n];
	}
};
/*
Time Complexity of the above implementation is O(mn) which is much better than the worst case time complexity of Naive Recursive implementation.
Auxiliary Space: O(mn)
*/


/* 3. Space Optimized Dynamic Programming C/C++ implementation of LCS problem */
/*
One important observation in above simple implementation is, in each iteration of outer loop we only, 
need values from all columns of previous row. So there is no need of storing all rows in our DP matrix, 
we can just store two rows at a time and use them, in that way used space will reduce from L[m+1][n+1] to L[2][n+1].
*/
class Solution_DP_v2 {
public:
	/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
	int LCS(const string& X, const string& Y, int m, int n)
	{
		// L[i, j] ��ʾ X[0..i-1] �� Y[0..j-1] �� LCS �ĳ���
		vector<vector<int>> L(m + 1);
		for (int i = 0; i < m + 1; ++i)
			L[i].assign(n + 1, 0);

		// Following steps build L[m+1][n+1] in bottom up fashion.
		for (int i = 0; i < m + 1; ++i)
		{
			for (int j = 0; j < n + 1; ++j)
			{
				if (i == 0 || j == 0)
					L[i % 2][j] = 0;
				else if (X[i - 1] == Y[j - 1])	// ������񣬷������������±�Ϊ���� i-1 ������ i
					L[i % 2][j] = L[(i - 1) % 2][j - 1] + 1;
				else
					L[i % 2][j] = max(L[(i - 1) % 2][j], L[i % 2][j - 1]);
			}
		}

		return L[m % 2][n];
	}
};
/*
Time Complexity : O(m*n)
Auxiliary Space : O(n)
*/


/* 4. Printing Longest Common Subsequence */
/*
���� L[0..m, 0..n] ����Ϣ�������½ǣ�����������������
*/
class Solution_DP_print {
public:
	void LCS(const string& X, const string& Y, int m, int n)
	{
		// L[i, j] ��ʾ X[0..i-1] �� Y[0..j-1] �� LCS �ĳ���
		vector<vector<int>> L(m + 1);
		for (int i = 0; i < m + 1; ++i)
			L[i].assign(n + 1, 0);

		// Following steps build L[m+1][n+1] in bottom up fashion.
		for (int i = 0; i < m + 1; ++i)
		{
			for (int j = 0; j < n + 1; ++j)
			{
				if (i == 0 || j == 0)
					L[i][j] = 0;
				else if (X[i - 1] == Y[j - 1])
					L[i][j] = L[i - 1][j - 1] + 1;
				else
					L[i][j] = max(L[i - 1][j], L[i][j - 1]);
			}
		}
		
		// Following code is used to print LCS
		string lcs;
		// Start from the right-most-bottom-most corner and
		// one by one store characters in lcs[]
		int i = m, j = n;
		while (i > 0 && j > 0)
		{
			if (X[i - 1] == Y[j - 1])
			{
				lcs.push_back(X[i - 1]);
				--i;
				--j;
			}
			else if (L[i - 1][j] > L[i] [j - 1])
				--i;
			else
				--j;
		}
		reverse(lcs.begin(), lcs.end());
		cout << "LCS of " << X << " and " << Y << " is " << lcs << endl;

		/*
		Time Complexity of above print LCS is O(m+n)����Ϊÿ��ѭ�� i �� j ������һ������� 1
		*/
	}
};


/* 5. Printing Longest Common Subsequence */
/*
ʹ����һ������B[1..m, 1..n]�����������Ž⡣
B[i, j]ָ��ı����Ӧ���� L[i, j] ʱ��ѡ�������������Ž⡣
*/
class Solution_DP_print_v2 {
public:
	void LCS(const string& X, const string& Y, int m, int n)
	{
		// L[i, j] ��ʾ X[0..i-1] �� Y[0..j-1] �� LCS �ĳ���
		vector<vector<int>> L(m + 1);
		vector<vector<char>> B(m + 1);
		for (int i = 0; i < m + 1; ++i)
		{
			L[i].assign(n + 1, 0);
			B[i].assign(n + 1, ' ');
		}

		for (int i = 0; i < m + 1; ++i)
		{
			for (int j = 0; j < n + 1; ++j)
			{
				if (i == 0 || j == 0)
					L[i][j] = 0;
				else if (X[i - 1] == Y[j - 1])
				{
					L[i][j] = L[i - 1][j - 1] + 1;
					B[i][j] = '\\';
				}
				else if (L[i - 1][j] >= L[i][j - 1])
				{
					L[i][j] = L[i - 1][j];
					B[i][j] = '|';
				}
				else
				{
					L[i][j] = L[i][j - 1];
					B[i][j] = '-';
				}
			}
		}
		
		// Following code is used to print LCS
		string lcs;
		// ���ñ� B ���ٹ���� X Y �� LCS
		cout << "LCS of " << X << " and " << Y << " is ";
		PrintLcs(B, X, m, n);
		cout << endl;
		/*
		Time Complexity of above print LCS is O(m+n)����Ϊÿ��ѭ�� i �� j ������һ������� 1
		*/
	}

	void PrintLcs(const vector<vector<char>>& B, const string& X, int X_len, int Y_len)
	{
		if (X_len == 0 || Y_len == 0)
			return;
		if (B[X_len][Y_len] == '\\')
		{
			PrintLcs(B, X, X_len - 1, Y_len - 1);
			cout << X[X_len - 1];
		}
		else if (B[X_len][Y_len] == '|')
			PrintLcs(B, X, X_len - 1, Y_len);
		else
			PrintLcs(B, X, X_len, Y_len - 1);
	}
};

```

## ��̬�滮�⡰�����и����⡱

### �����и�����

>Ref: �㷨���� ��15��   
>Ref: https://www.geeksforgeeks.org/dynamic-programming-set-13-cutting-a-rod/

����һ�γ���Ϊ n Ӣ��ĸ�����һ���۸�� p_i(i=1,2,...,n)����������и����ʹ���������� r_n ���   
ע�⣺������ n Ӣ��ĸ����ļ۸� p_n �㹻�����Ž���ܾ�����ȫ����Ҫ�и   

����r_n(n>=1)������ʹ�ø��̵ĸ����������и�������������   
r_n = max{p_n, r_1 + r_(n-1), r_2 + r_(n-2), ..., r_(n-1) + r_1}   
==>   
���Ƶ���Ϊ�򵥵ĵݹ鹫ʽ   
r_n = max{p_i + r_(n-i)} (i = 1,...,n)   
r_0 = 0   
����и��³���Ϊ i ��һ�Σ�ֻ���ұ�ʣ�µĳ��Ƚ����и�ݹ���⣩������ߵ�һ�����ٷָ

![LCS_TABLE](https://github.com/HongfeiXu/LeetCode/blob/master/images/CutRod.png?raw=true)

### Solve CutRod Problem 

�����������6��ʵ�֣���Ӧ�˲�ͬ������

1. �ݹ�ʵ��
2. ��̬�滮ʵ�֣�������Ž��ֵ
3. ��̬�滮ʵ�֣�����������Ž�

```c++
#pragma once

#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

// 1. �ݹ�ʵ��
// Time: O(2^n)
int CutRod(vector<int> price, int length)
{
	if (length == 0)
		return 0;
	int q = INT_MIN;
	for (int i = 1; i <= length; ++i)
		q = max(q, price[i] + CutRod(price, length - i));
	return q;
}

// 2. ��̬�滮ʵ��(bottom-up)
// Time: O(n^2)
int CutRod_DP(vector<int> price, int length)
{
	vector<int> r(length + 1, 0);	// r[1,...,length] ��¼����Ϊ i �ĸ����ܻ�õ�������棬r[0] = 0

	for (int i = 1; i <= length; ++i)
	{
		int q = INT_MIN;
		for (int j = 1; j <= i; ++j)
			q = max(price[j] + r[i - j], q);
		r[i] = q;
	}
	return r[length];
}

// 3. ��̬�滮ʵ��(bottom-up)���������Ž�
// Time: O(n^2)
void CutRod_DP_print(vector<int> price, int length)
{
	vector<int> r(length + 1, 0);	// r[1,...,length] ��¼����Ϊ i �ĸ����ܻ�õ�������棬r[0] = 0
	vector<int> s(length + 1, 0);	// s[1,...,length] ��¼����Ϊ i �ĸ����ĵ�һ�γ���

	// �Գ���Ϊ i �ĸ����������õ�������棬�Լ����ڵĵ�һ���и��
	for (int i = 1; i <= length; ++i)
	{
		int q = INT_MIN;
		int len;
		for (int j = 1; j <= i; ++j)
		{
			if (price[j] + r[i - j] > q)
			{
				q = price[j] + r[i - j];
				len = j;
			}
		}
		r[i] = q;
		s[i] = len;
	}

	// ����и�Ľ������ÿһ�θ����ĳ���
	while (length > 0)
	{
		cout << s[length] << endl;	// ����Ϊ length �ĸ����и����߲��ٷָ����һ��
		length -= s[length];		// ��ʣ�³��ȵĸ�����������
	}
}

```

## ��̬�滮�⡰�߶ηָ����⡱

### Cutted Segments

>Ref: https://practice.geeksforgeeks.org/problems/cutted-segments/0

Given an integer N denoting the Length of a line segment. 
you need to cut the line segment in such a way that the cut length of a line segment each time is integer either x , y or z. 
and after performing all cutting operation the total number of cutted segments must be maximum.

���ڳ���Ϊ n ���߶Σ��������и� S_n(n+>=1)������ʹ�ø��̵��߶ε������и���������    
S_n = max{S_i + S_(n-i)}, i = x,y,z ��С�ڵ��� n ������   
=>   
S_n = max{i + S_(n-i)}, i = x,y,z ��С�ڵ��� n ������   
S_0 = 0   
ǰ��� i ���Ȳ����зָֻ�ָ����µ� n - i ���ȵ��߶Σ�   
S_i == -1 ��ʾ���߶��޷��� x,y,z ���зָ�  

### Solve CutRod Problem

�����������2��ʵ�֣���Ӧ�˲�ͬ������

1. ��̬�滮ʵ�֣�������Ž��ֵ
2. ��̬�滮ʵ�֣�����������Ž�

```c++
#pragma once

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void CuttedSegments(int N, int x, int y, int z)
{
	vector<int> S(N + 1, 0);
	vector<int> candidate { x,y,z };
	sort(candidate.begin(), candidate.end());	// ����ѡ���߶γ��ȴ�С��������

	// bottom-up Dynamic Programming
	// �Գ���Ϊ i ���߶Σ��������ܱ��ָ����������
	for (int i = 1; i <= N; ++i)
	{
		int temp = -1;
		// �ó��� x,y,z ��Ϊ��߲������ָ���߶�
		for (int j = 0; j < candidate.size(); ++j)
		{
			if (i >= candidate[j])
			{
				if(S[i-candidate[j]] != -1)
					temp = max(temp, 1 + S[i - candidate[j]]);
			}
			// �� curr < candidate[j] ʱ�����ܽ��зָֱ�ӷ���
			else
				break;
		}
		S[i] = temp;
	}
	cout << "Cutted Segments of " << N << " : " << S[N] << endl;
}

void CuttedSegments_Print(int N, int x, int y, int z)
{
	vector<int> S(N + 1, 0);
	vector<int> candidate { x,y,z };
	sort(candidate.begin(), candidate.end());	// ����ѡ���߶γ��ȴ�С��������

	vector<int> A(N + 1, -1);					// ��¼����Ϊ i �ĸ����ָ�ĵ�һ�γ��ȣ���������ָ�Ľ�
	// bottom-up Dynamic Programming
	// �Գ���Ϊ i ���߶Σ��������ܱ��ָ����������
	for (int i = 1; i <= N; ++i)
	{
		int temp = -1;
		// �ó��� x,y,z ��Ϊ��߲������ָ���߶�
		for (int j = 0; j < candidate.size(); ++j)
		{
			if (i >= candidate[j])
			{
				if (S[i - candidate[j]] != -1)
				{
					if (temp < 1 + S[i - candidate[j]])
					{
						temp = 1 + S[i - candidate[j]];
						A[i] = candidate[j];		// ��¼���ָ��λ��
					}
				}
			}
			// �� curr < candidate[j] ʱ�����ܽ��зָֱ�ӷ���
			else
				break;
		}
		S[i] = temp;
	}
	
	if (S[N] != -1)
	{
		cout << "Cutted Segments of " << N << " : ";
		while (N != 0)
		{
			cout << A[N] << " ";
			N = N - A[N];
		}
		cout << endl;
	}
	else
	{
		cout << "Segment of " << N << " can't be cutted by " << x << ", " << y << " and " << z << endl;
	}
}

```

## ��̬�滮�⡰0-1 �������⡱

### 0-1 Knapsack Problem

һ�����������̵��С͵������ n ����Ʒ���� i ����Ʒ��ֵ vi ��Ԫ���� wi ����vi �� wi �������������С͵ϣ�����߼�ֵ�����ܸߵ���Ʒ�������ı���������� W ���е���Ʒ��W��һ����������Ӧ������Щ��Ʒ�أ�

ע���� 0-1 ����������Եģ������������⣬�䲻ͬ���ڶ�ÿ����Ʒ������С͵������Ʒ��һ���֣�������ֻ��������Ԫѡ�񡣿��Խ� 0-1 ���������е���Ʒ��ϸΪ�𶧣����������������е���Ʒ�����ɰ��

Ref: CLRS Chapter 16
Ref: https://www.geeksforgeeks.org/knapsack-problem/

��������������ӽṹ���ʣ�������ǽ���Ʒ j �Ӵ˷�����ɾ������ʣ�����Ʒ�����ǲ����� W-wj �ļ�ֵ��߷�����

**�� M[i, w] Ϊ��ǰ i ����Ʒװ���������Ϊ w �ı����е�����ֵ���������ĵ� i ����Ʒ��������������Ž��������߲��š�**   
If wi > w �����������޷����뱳����**M[i, w] = M[i-1, w]**   
Else�� �����㹻�����Բ�����Ҳ���Է��룬ȡ���߽ϴ�ֵ��**M[i, w] = Max(M[i-1, w], M[i-1, w-wi] + vi)**   
���⣺**M[0, w] = 0��M[i, 0] = 0**

### Solve 0-1 Knapsack Problem

�����������2��ʵ�֣���Ӧ�˲�ͬ������

1. �ݹ�ʵ��
2. ��̬�滮ʵ�֣�������Ž��ֵ��Time: O(nW)

```c++
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int ZeroOneKnapsack_Recursive(int n, const vector<int>& value, const vector<int>& weight, int W)
{
	// Base Case
	if (n == 0 || W == 0)
		return 0;

	// If weight of the nth item is more than Knapsack capacity W, then
	// this item cannot be included in the optimal solution
	if (weight[n - 1] > W)
		return ZeroOneKnapsack_Recursive(n - 1, value, weight, W);

	// Return the maximum of two cases: 
	// (1) nth item included 
	// (2) not included
	else
		return max(ZeroOneKnapsack_Recursive(n - 1, value, weight, W),
				   ZeroOneKnapsack_Recursive(n - 1, value, weight, W - weight[n - 1]) + value[n - 1]);
}

// n ����Ʒ��ÿ����Ʒ�ļ۸�ÿ����Ʒ������������������
int ZeroOneKnapsack_DP(int n, const vector<int>& value, const vector<int>& weight, int W)
{
	// M[0~n, 0~W]
	// M[0~n, 0] = 0, M[0, 0~W] = 0
	vector<vector<int>> M(n + 1, vector<int>(W + 1, 0));

	// bottom-up
	for (int i = 1; i <= n; ++i)
	{
		for (int w = 1; w <= W; ++w)
		{
			// ��� M[i, w]
			if (weight[i - 1] > w)
				M[i][w] = M[i - 1][w];
			else
				M[i][w] = max(M[i - 1][w], M[i - 1][w - weight[i - 1]] + value[i - 1]);
		}
	}
	return M[n][W];
}
```

## ��̬�滮�� �ࡰ0-1 �������⡱ Ones and Zeros

### Ones and Zeros

> https://leetcode.com/problems/ones-and-zeroes/

474. Ones and Zeroes

In the computer world, use restricted resource you have to generate maximum benefit is what we always want to pursue.   
For now, suppose you are a dominator of m 0s and n 1s respectively. On the other hand, there is an array with strings consisting of only 0s and 1s.   
Now your task is to find the maximum number of strings that you can form with given m 0s and n 1s. Each 0 and 1 can be used at most once.   

Note:   
The given numbers of 0s and 1s will both not exceed 100   
The size of given string array won't exceed 600.   

Example 1:   
Input: Array = {"10", "0001", "111001", "1", "0"}, m = 5, n = 3   
Output: 4   

Explanation: This are totally 4 strings can be formed by the using of 5 0s and 3 1s, which are ��10,��0001��,��1��,��0��   
Example 2:   
Input: Array = {"10", "0", "1"}, m = 1, n = 1   
Output: 2   

Explanation: You could form "10", but then you'd have nothing left. Better form "0" and "1".   

### ����

���� 0-1��������ı�������

������ƷΪ���е��ַ���������������������������������0�ĸ�����1�ĸ���   
�� mf[i, m, n] ��ʾǰ i ���ַ���װ���������Ϊ m �� 0 �� n �� 1 �ı����е�����ַ�����Ŀ    
��Ե�i���ַ�����������������Ž��������߲��Ž�����   
if strs[i].zeros > m || strs[i].ones > n�����޷��Ž�������mf[i, m, n] = mf[i-1, m, n]   
else mf[i, m, n] = max(mf[i-1, m, n], mf[i-1, m - zeros, n- ones] + 1) ��ʱ���Խ����ַ��������뱳�����߷��뱳����ȡ�ϴ�ֵ��      

ע��   
i=0,1,2,...,strs.size()��i == 0 ʱ��ʾû���ַ������뱳������mf[0,m,n] = 0   
m == 0 && n == 0 ʱ��ʾ������Ϊ�գ�������ַ�����û�п��ַ��Ļ������������򱳰����ַ�������Ŀ��ȻҲΪ0���� m[i][0][0] = 0      

mf[strs.size(), m, n] ��Ϊ����ע������ strs.size() ��ʾ�� strs.size() ���ַ����������� strs.size() - 1   

���Խ��пռ临�Ӷ��Ż�    
��Ϊÿһ�ε���iʱֻ�õ���i-1�����ݣ���ֻ��Ҫ�洢���о��㹻��ɵ���   
Time: O(strs.size() * m * n)   
Space: O(m * n)   

### ���

```c++
class Solution {
public:
	int findMaxForm(vector<string>& strs, int m, int n)
	{
		vector<vector<vector<int>>> mf(2, vector<vector<int>>());
		for (int i = 0; i < mf.size(); ++i)
			mf[i].assign(m + 1, vector<int>(n + 1, 0));

		for (int i = 1; i <= strs.size(); ++i)
		{
			pair<int, int> cnt_of_zeros_and_ones = cntOfZerosAndOnes(strs[i - 1]);
			for (int x = 0; x <= m; ++x)
			{
				for (int y = 0; y <= n; ++y)
				{
					if (cnt_of_zeros_and_ones.first > x || cnt_of_zeros_and_ones.second > y)
						mf[i % 2][x][y] = mf[(i-1+2)%2][x][y];
					else
						mf[i % 2][x][y] = max(mf[(i-1+2)%2][x][y], mf[(i-1+2)%2][x - cnt_of_zeros_and_ones.first][y - cnt_of_zeros_and_ones.second] + 1);
				}
			}
		}
		return mf[strs.size()%2][m][n];
	}

	// ���� s �е� 0 �� 1 �ĸ���
	pair<int, int> cntOfZerosAndOnes(const string& s)
	{
		pair<int, int> result(0, 0);
		for (const auto c : s)
		{
			if (c == '0')
				result.first++;
			else
				result.second++;
		}
		return result;
	}
};
```











