# Dynamic Programming

## 什么是动态规划

>Ref: http://blog.csdn.net/v_JULY_v/article/details/6110269

动态规划一般也只能应用于有最优子结构的问题。最优子结构的意思是局部最优解能决定全局最优解(对有些问题这个要求并不能完全满足，故有时需要引入一定的近似)。简单地说，问题能够分解成子问题来解决。动态规划算法分以下4个步骤：
1. 描述最优解的结构
2. 递归定义最优解的值
3. 按自底向上的方式计算最优解的值   //此3步构成动态规划解的基础。
4. 由计算出的结果构造一个最优解。   //此步如果只要求计算最优解的值时，可省略。

咱们讨论适合采用动态规划方法的最优化问题的俩个要素：最优子结构性质，和子问题重叠性质。

- 最优子结构

如果问题的最优解所包含的子问题的解也是最优的，我们就称该问题具有最优子结构性质（即满足最优化原理）。意思就是，总问题包含很多个子问题，而这些子问题的解也是最优的。

- 重叠子问题

子问题重叠性质是指在用递归算法自顶向下对问题进行求解时，每次产生的子问题并不总是新问题，有些子问题会被重复计算多次。动态规划算法正是利用了这种子问题的重叠性质，对每一个子问题只计算一次，然后将其计算结果保存在一个表格中，当再次需要计算已经计算过的子问题时，只是在表格中简单地查看一下结果，从而获得较高的效率。

## 动态规划算法解 LCS 问题

>Ref: https://www.geeksforgeeks.org/longest-common-subsequence/

### LCS Problem Statement
Given two sequences, find the length of longest subsequence present in both of them. 
A subsequence is a sequence that appears in the same relative order, but not necessarily contiguous. 

For example, “abc”, “abg”, “bdf”, “aeg”, ‘”acefg”, .. etc are subsequences of “abcdefg”. 
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

下面代码中有6种实现，对应了不同的需求。

1. Naive recursive implementation
2. Dynamic Programming C/C++ implementation of LCS problem
3. Space Optimized Dynamic Programming C/C++ implementation of LCS problem
4. Printing Longest Common Subsequence
5. Printing Longest Common Subsequence with an auxiliary Table

![LCS_TABLE](https://github.com/HongfeiXu/LeetCode/blob/master/images/LCS_table.png?raw=true)

上图表示了L[0..m, 0..n] 的内容以及 B[1..m, 1..n] 的内容

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
		// L[i, j] 表示 X[0..i-1] 与 Y[0..j-1] 的 LCS 的长度
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
				else if (X[i - 1] == Y[j - 1])	// 画出表格，方便理解这里的下标为何是 i-1 而不是 i
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
		// L[i, j] 表示 X[0..i-1] 与 Y[0..j-1] 的 LCS 的长度
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
				else if (X[i - 1] == Y[j - 1])	// 画出表格，方便理解这里的下标为何是 i-1 而不是 i
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
利用 L[0..m, 0..n] 的信息从最右下角，构造出最长公共子序列
*/
class Solution_DP_print {
public:
	void LCS(const string& X, const string& Y, int m, int n)
	{
		// L[i, j] 表示 X[0..i-1] 与 Y[0..j-1] 的 LCS 的长度
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
		Time Complexity of above print LCS is O(m+n)，因为每次循环 i 和 j 至少有一个会减少 1
		*/
	}
};


/* 5. Printing Longest Common Subsequence */
/*
使用另一个数组B[1..m, 1..n]帮助构造最优解。
B[i, j]指向的表项对应计算 L[i, j] 时所选择的子问题的最优解。
*/
class Solution_DP_print_v2 {
public:
	void LCS(const string& X, const string& Y, int m, int n)
	{
		// L[i, j] 表示 X[0..i-1] 与 Y[0..j-1] 的 LCS 的长度
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
		// 利用表 B 快速构造出 X Y 的 LCS
		cout << "LCS of " << X << " and " << Y << " is ";
		PrintLcs(B, X, m, n);
		cout << endl;
		/*
		Time Complexity of above print LCS is O(m+n)，因为每次循环 i 和 j 至少有一个会减少 1
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

## 动态规划解钢条切割问题

### 钢条切割问题

>Ref: 算法导论 第15章

给定一段长度为 n 英寸的钢条和一个价格表 p_i(i=1,2,...,n)。求钢条的切割方案，使得销售收益 r_n 最大。   
注意：若长度 n 英寸的钢条的价格 p_n 足够大，最优解可能就是完全不需要切割。   

对于r_n(n>=1)，我们使用更短的钢条的最优切割收益来描述它   
r_n = max{p_n, r_1 + r_(n-1), r_2 + r_(n-2), ..., r_(n-1) + r_1}   
==>   
相似但更为简单的递归公式   
r_n = max{p_i, r_(n-i)} (i = 1,...,n)   
r_0 = 0   
左边切割下长度为 i 的一段，只对右边剩下的长度进行切割（递归求解），对左边的一段则不再分割。

![LCS_TABLE](https://github.com/HongfeiXu/LeetCode/blob/master/images/CutRod.png?raw=true)

### Solve CutRod Problem 

下面代码中有6种实现，对应了不同的需求。

1. 递归实现
2. 动态规划实现，输出最优解的值
3. 动态规划实现，并且输出最优解

```c++
#pragma once

#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

// 1. 递归实现
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

// 2. 动态规划实现(bottom-up)
// Time: O(n^2)
int CutRod_DP(vector<int> price, int length)
{
	vector<int> r(length + 1, 0);	// r[1,...,length] 记录长度为 i 的钢条能获得的最大收益，r[0] = 0

	for (int i = 1; i <= length; ++i)
	{
		int q = INT_MIN;
		for (int j = 1; j <= i; ++j)
			q = max(price[j] + r[i - j], q);
		r[i] = q;
	}
	return r[length];
}

// 3. 动态规划实现(bottom-up)，构造最优解
// Time: O(n^2)
void CutRod_DP_print(vector<int> price, int length)
{
	vector<int> r(length + 1, 0);	// r[1,...,length] 记录长度为 i 的钢条能获得的最大收益，r[0] = 0
	vector<int> s(length + 1, 0);	// s[1,...,length] 记录长度为 i 的钢条的第一段长度

	// 对长度为 i 的钢条，计算获得的最大收益，以及对于的第一段切割长度
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

	// 输出切割的结果，即每一段钢条的长度
	while (length > 0)
	{
		cout << s[length] << endl;	// 长度为 length 的钢条切割掉左边不再分割的那一段
		length -= s[length];		// 对剩下长度的钢条继续迭代
	}
}

```
