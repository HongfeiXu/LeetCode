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

����
n = 1, MinStep = 0
n = 2, MinStep = 1, Operating: CP
n = 3, MinStep = 3, Operating: CPP
n = 4, MinStep = 4, Operating: CPPP\CPCP
n = 5, MinStep = 5, Operating: CPPPP
n = 6, MinStep = 5, Operating: CPPCP\CPCPP
...

��������� COPY ��������ȫ���������ԣ��������������������Ӷεĳ��ȱ���Ϊ n �����ӡ�
��������� n = 6���ȹ���� AAA��Ȼ���ڽ��� CP �������õ� AAAAAA�������ȹ���� AA Ȼ���ڽ��� CPP �����ĵ� AAAAAA��
���ԣ����������ҳ� n ���������� i ��Ϊģ��ĳ��ȣ��� n ���ָ�Ϊ n/i ��ģ�飬��ÿ�����ӣ��ݹ������Ҫ�Ĳ���������������������ģ������õ����յĲ�������ȡ��С���Ǹ���
���ɵõ���ʽ���£�
�� n == 1
	MinStep[1] = 0
�� n ���г���1���䱾�����������
	MinStep[n] = min{MinStep[k] + n/k}, k Ϊ n �����ӣ���1���䱾��
�� n û�г���1���䱾�����������
	MinSte[n] = n

ֱ��ʹ�õݹ�ʵ��֮
Time:?
Space:O(1)


Approach_v2:
DP
Ϊɶ������ĵݹ黹Ҫ���ܶ�

Approach_v3:

Ref: https://discuss.leetcode.com/topic/97623/loop-best-case-log-n-no-dp-no-extra-space-no-recursion-with-explanation

We look for a divisor d so that we can make d copies of (n / d) to get n
The process of making d copies takes d steps (1 step of Copy All and d - 1 steps of Paste)
We keep reducing the problem to a smaller one in a loop.
The best cases occur when n is decreasing fast, and method is almost O(log(n))
For example, when n = 1024 then n will be divided by 2 for only 10 iterations, which is much faster than O(n) DP method.
The worst cases occur when n is some multiple of large prime, e.g. n = 997 but such cases are rare.

���������������̰�ķ�����û����ȷ�Ե�֤����
����ֱ���ϣ���Ŀ�� n ����ĸ�������ֳܷ��ٵĲ��֣�ÿ�����־����ܵĴ󣬺����ǻ���ٲ����Ĵ�����

*/

#include <algorithm>

using namespace std;

class Solution {
public:
	int minSteps(int n)
	{
		if (n == 1)
			return 0;
		int res = n;	// ���� n �� A���� n û�г���1�ͱ�������ӣ�����Ҫ���� n �β����õ���
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
		// ��Ŀ��� n �� A �ֳɾ������ٵķ��� d��Ȼ���ÿһ�� n/d �ټ������ַָ��û�г���1������֮������ӣ�����Ҫ n �β�����
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
