#pragma once

/*

650. 2 Keys Keyboard

Initially on a notepad only one character 'A' is present. You can perform two operations on this notepad for each step:

Copy All: You can copy all the characters present on the notepad (partial copy is not allowed).
Paste: You can paste the characters which are copied last time.
Given a number n. You have to get exactly n 'A' on the notepad by performing the minimum number of steps permitted. 
Output the minimum number of steps to get n 'A'.

Example 1:
Input: 3
Output: 3
Explanation:
Intitally, we have one character 'A'.
In step 1, we use Copy All operation.
In step 2, we use Paste operation to get 'AA'.
In step 3, we use Paste operation to get 'AAA'.

Note:
The n will be in the range [1, 1000].

Approach:

分析
n = 1, MinStep = 0
n = 2, MinStep = 1, Operating: CP
n = 3, MinStep = 3, Operating: CPP
n = 4, MinStep = 4, Operating: CPPP\CPCP
n = 5, MinStep = 5, Operating: CPPPP
n = 6, MinStep = 5, Operating: CPPCP\CPCPP
...

由于这里的 COPY 必须是完全拷贝，所以，用来拷贝构造出结果的子段的长度必须为 n 的因子。
比如这里的 n = 6，先构造出 AAA，然后在进行 CP 操作，得到 AAAAAA，或者先构造出 AA 然后在进行 CPP 操作的到 AAAAAA。
所以，这里我们找出 n 的所有因子 i 作为模块的长度，则 n 被分割为 n/i 个模块，对每个因子，递归计算需要的操作数，并将操作数加上模块分数得到最终的操作数，取最小的那个。
归纳得到公式如下：
若 n == 1
	MinStep[1] = 0
若 n 具有除了1和其本身的其他因子
	MinStep[n] = min{MinStep[k] + n/k}, k 为 n 的因子（非1和其本身）
若 n 没有除了1和其本身的其他因子
	MinSte[n] = n

直接使用递归实现之
Time:?
Space:O(1)


Approach_v2:
DP
为啥比上面的递归还要慢很多

Approach_v3:

Ref: https://discuss.leetcode.com/topic/97623/loop-best-case-log-n-no-dp-no-extra-space-no-recursion-with-explanation

We look for a divisor d so that we can make d copies of (n / d) to get n
The process of making d copies takes d steps (1 step of Copy All and d - 1 steps of Paste)
We keep reducing the problem to a smaller one in a loop.
The best cases occur when n is decreasing fast, and method is almost O(log(n))
For example, when n = 1024 then n will be divided by 2 for only 10 iterations, which is much faster than O(n) DP method.
The worst cases occur when n is some multiple of large prime, e.g. n = 997 but such cases are rare.

看起来这个方法是贪心法，但没有正确性的证明。
不过直观上，将目标 n 个字母，尽可能分成少的部分，每个部分尽可能的大，好像是会减少操作的次数。

*/

#include <algorithm>

using namespace std;

class Solution {
public:
	int minSteps(int n)
	{
		if (n == 1)
			return 0;
		int res = n;	// 对于 n 个 A，若 n 没有除了1和本身的因子，则需要进行 n 次操作得到。
		for (int i = n - 1; i > 1; --i)
		{
			if (n % i == 0)
				res = min(res, minSteps(i) + n/i);
		}
		return res;
	}
};

class Solution_v2 {
public:
	int minSteps(int n)
	{
		if (n == 1)
			return 0;

		vector<int> MinSteps(n + 1);
		MinSteps[1] = 0;
		for (int i = 2; i < n + 1; ++i)
		{
			MinSteps[i] = i;
			for (int j = 2; j < i; ++j)
			{
				if (i % j == 0)
					MinSteps[i] = min(MinSteps[i], MinSteps[j] + i / j);
			}
		}
		return MinSteps[n];
	}
};

class Solution_v3 {
public:
	int minSteps(int n)
	{
		int res = 0;
		// 将目标的 n 个 A 分成尽可能少的份数 d，然后对每一份 n/d 再继续这种分割，若没有除了1和自身之外的因子，则需要 n 次操作。
		for (int d = 2; d <= n; ++d)
		{
			while (n % d == 0)
			{
				res += d;
				n /= d;
			}
		}
		return res;
	}
};
