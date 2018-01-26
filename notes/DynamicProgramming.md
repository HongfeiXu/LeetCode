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

## 动态规划算法解“LCS 问题”

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

## 动态规划解“钢条切割问题”

### 钢条切割问题

>Ref: 算法导论 第15章   
>Ref: https://www.geeksforgeeks.org/dynamic-programming-set-13-cutting-a-rod/

给定一段长度为 n 英寸的钢条和一个价格表 p_i(i=1,2,...,n)。求钢条的切割方案，使得销售收益 r_n 最大。   
注意：若长度 n 英寸的钢条的价格 p_n 足够大，最优解可能就是完全不需要切割。   

对于r_n(n>=1)，我们使用更短的钢条的最优切割收益来描述它   
r_n = max{p_n, r_1 + r_(n-1), r_2 + r_(n-2), ..., r_(n-1) + r_1}   
==>   
相似但更为简单的递归公式   
r_n = max{p_i + r_(n-i)} (i = 1,...,n)   
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

## 动态规划解“线段分割问题”

### Cutted Segments

>Ref: https://practice.geeksforgeeks.org/problems/cutted-segments/0

Given an integer N denoting the Length of a line segment. 
you need to cut the line segment in such a way that the cut length of a line segment each time is integer either x , y or z. 
and after performing all cutting operation the total number of cutted segments must be maximum.

对于长度为 n 的线段，其最优切割 S_n(n+>=1)，我们使用更短的线段的最优切割来描述它    
S_n = max{S_i + S_(n-i)}, i = x,y,z 中小于等于 n 的数字   
=>   
S_n = max{i + S_(n-i)}, i = x,y,z 中小于等于 n 的数字   
S_0 = 0   
前面的 i 长度不进行分割，只分割余下的 n - i 长度的线段，   
S_i == -1 表示该线段无法用 x,y,z 进行分割  

### Solve CutRod Problem

下面代码中有2种实现，对应了不同的需求。

1. 动态规划实现，输出最优解的值
2. 动态规划实现，并且输出最优解

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
	sort(candidate.begin(), candidate.end());	// 将候选的线段长度从小到大排序

	// bottom-up Dynamic Programming
	// 对长度为 i 的线段，计算其能被分割的最大块数。
	for (int i = 1; i <= N; ++i)
	{
		int temp = -1;
		// 用长度 x,y,z 作为左边不继续分割的线段
		for (int j = 0; j < candidate.size(); ++j)
		{
			if (i >= candidate[j])
			{
				if(S[i-candidate[j]] != -1)
					temp = max(temp, 1 + S[i - candidate[j]]);
			}
			// 当 curr < candidate[j] 时，不能进行分割，直接返回
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
	sort(candidate.begin(), candidate.end());	// 将候选的线段长度从小到大排序

	vector<int> A(N + 1, -1);					// 记录长度为 i 的钢条分割的第一段长度，用来构造分割的解
	// bottom-up Dynamic Programming
	// 对长度为 i 的线段，计算其能被分割的最大块数。
	for (int i = 1; i <= N; ++i)
	{
		int temp = -1;
		// 用长度 x,y,z 作为左边不继续分割的线段
		for (int j = 0; j < candidate.size(); ++j)
		{
			if (i >= candidate[j])
			{
				if (S[i - candidate[j]] != -1)
				{
					if (temp < 1 + S[i - candidate[j]])
					{
						temp = 1 + S[i - candidate[j]];
						A[i] = candidate[j];		// 记录被分割的位置
					}
				}
			}
			// 当 curr < candidate[j] 时，不能进行分割，直接返回
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

## 动态规划解“0-1 背包问题”

### 0-1 Knapsack Problem

一个正在抢劫商店的小偷发现了 n 个商品，第 i 个商品价值 vi 美元，重 wi 磅，vi 和 wi 都是整数。这个小偷希望拿走价值尽可能高的商品，但他的背包最多容纳 W 磅中的商品，W是一个整数。他应该拿那些商品呢？

注：与 0-1 背包问题相对的，分数背包问题，其不同在于对每个商品，允许小偷拿走商品的一部分，而不是只能做出二元选择。可以将 0-1 背包问题中的商品详细为金锭，而分数背包问题中的商品更像金砂。

Ref: CLRS Chapter 16
Ref: https://www.geeksforgeeks.org/knapsack-problem/

此问题具有最优子结构性质：如果我们将商品 j 从此方案中删除，则剩余的商品必须是不超过 W-wj 的价值最高方案。

**设 M[i, w] 为用前 i 个商品装入最大容量为 w 的背包中的最大价值，则对任意的第 i 个物品，有两种情况，放进背包或者不放。**   
If wi > w ，容量不够无法放入背包：**M[i, w] = M[i-1, w]**   
Else， 容量足够，可以不放入也可以放入，取两者较大值：**M[i, w] = Max(M[i-1, w], M[i-1, w-wi] + vi)**   
另外：**M[0, w] = 0，M[i, 0] = 0**

### Solve 0-1 Knapsack Problem

下面代码中有2种实现，对应了不同的需求。

1. 递归实现
2. 动态规划实现，输出最优解的值，Time: O(nW)

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

// n 件商品，每件商品的价格，每件商品的重量，背包的容量
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
			// 求解 M[i, w]
			if (weight[i - 1] > w)
				M[i][w] = M[i - 1][w];
			else
				M[i][w] = max(M[i - 1][w], M[i - 1][w - weight[i - 1]] + value[i - 1]);
		}
	}
	return M[n][W];
}
```

## 动态规划解 类“0-1 背包问题” Ones and Zeros

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

Explanation: This are totally 4 strings can be formed by the using of 5 0s and 3 1s, which are “10,”0001”,”1”,”0”   
Example 2:   
Input: Array = {"10", "0", "1"}, m = 1, n = 1   
Output: 2   

Explanation: You could form "10", but then you'd have nothing left. Better form "0" and "1".   

### 分析

这是 0-1背包问题的变形问题

这里商品为所有的字符串，背包的容量由两个变量决定，即0的个数和1的个数   
用 mf[i, m, n] 表示前 i 个字符串装入容量最大为 m 个 0 和 n 个 1 的背包中的最大字符串数目    
则对第i个字符串，有两种情况，放进背包或者不放进背包   
if strs[i].zeros > m || strs[i].ones > n，则无法放进背包，mf[i, m, n] = mf[i-1, m, n]   
else mf[i, m, n] = max(mf[i-1, m, n], mf[i-1, m - zeros, n- ones] + 1) 此时可以将次字符串不放入背包或者放入背包，取较大值。      

注：   
i=0,1,2,...,strs.size()，i == 0 时表示没有字符串放入背包，故mf[0,m,n] = 0   
m == 0 && n == 0 时表示，背包为空，（如果字符串中没有空字符的话。。。），则背包中字符串的数目显然也为0，故 m[i][0][0] = 0      

mf[strs.size(), m, n] 即为所求，注：这里 strs.size() 表示有 strs.size() 个字符串，而不用 strs.size() - 1   

可以进行空间复杂度优化    
因为每一次迭代i时只用到了i-1的数据，故只需要存储两行就足够完成递推   
Time: O(strs.size() * m * n)   
Space: O(m * n)   

### 解决

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

	// 返回 s 中的 0 和 1 的个数
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











