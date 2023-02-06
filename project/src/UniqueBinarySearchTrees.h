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

对于数字 1...n，可以用任何数字作为根节点，然后将在构造左子树和右子树。
对于任意节点作为根，若左子树有 a 种，右子树有 b 种，则此时可以构成 a * b 种树。将所有情况求和即得到 1...n 的UBST个数。
表示如下：
UB: Unique Binary Search Trees
UB[n] = Sum{UB[i] * UB[n-i-1]}, i=0,...,n-1
UB[0] = 1，即允许某一侧子树为空
当然如果初始 n == 0，则直接返回 0

使用动态规划法，自底向上求解出 UB[1...n]
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
			// 求i个数字（1..i）所能构造的 unique binary search trees 的数目
			for (int j = 1; j <= i; ++j)
			{
				// j 为根节点，左子树有 j-1 个节点，右子树有 i-j 个节点
				UB[i] += UB[j - 1] * UB[i - j];
			}
		}
		return UB[n];
	}
};

