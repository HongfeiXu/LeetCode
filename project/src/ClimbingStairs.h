#pragma once

/*

70. Climbing Stairs

You are climbing a stair case. It takes n steps to reach to the top.
Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
Note: Given n will be a positive integer.

Example 1:

Input: 2
Output:  2
Explanation:  There are two ways to climb to the top.

1. 1 step + 1 step
2. 2 steps
Example 2:

Input: 3
Output:  3
Explanation:  There are three ways to climb to the top.

1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step

Approach:

C[n] = C[n-1] + C[n-2]
到达第n个台阶的方法数 = 到达第n-2个台阶的方法书 + 到达第n-1个台阶的方法数
C[0] = 1
C[1] = 1

*/

#include <vector>

using namespace std;

class Solution {
public:
	int climbStairs(int n)
	{
		if (n == 1)
			return 1;
		vector<int> C(n + 1, 0);
		C[0] = 1;
		C[1] = 1;
		for (int i = 2; i <= n; ++i)
			C[i] = C[i - 1] + C[i - 2];

		return C[n];
	}
};

class Solution_v2 {
public:
	int climbStairs(int n)
	{
		if (n == 1)
			return 1;
		int pre = 0;
		int prepre = 1;
		int curr = 0;
		for (int i = 2; i <= n; ++i)
		{
			curr = pre + prepre;
			pre = prepre;
			prepre = curr;
		}

		return curr;
	}
};
