#pragma once

/*

69. Sqrt(x)

Implement int sqrt(int x).

Compute and return the square root of x.

x is guaranteed to be a non-negative integer.


Example 1:

Input: 4
Output: 2

Example 2:

Input: 8
Output: 2
Explanation: The square root of 8 is 2.82842..., and since we want to return an integer, the decimal part will be truncated.

Approach:

Newton's method

求根号 a，也就是求解 `x^2 - a = 0` 的非负解。

我们不断用 (x,f(x)) 的切线来逼近方程 `x^2 - a = 0` 的根。迭代式为：

x[k+1] = (x[k] + n/x[k])/2, k >= 0, x[0] > 0

运用带余除法改写牛顿迭代式（好处是，这里中间结果只需要用整型值进行存储，不需要进行复杂的浮点数计算）：

x[k+1] = floor((x[k] + floor(n/x[k]))/2), k >= 0, x[0] > 0, x[0] 是整数（x[k]也为整数）

Approach v2[TLE]:

在 0~a范围内搜索数字x，使得 x * x == a || (x * x < a && (x+1)*(x+1) >a)

Approach v3:

二分查找
use long type variable to hold intermediate values.

Appraoch v4:

二分查找
use int and divide operator，避免乘法，从而避免了 long 的使用。but slower.

*/

#include <iostream>

using namespace std;


class Solution {
public:
	int mySqrt(int a)
	{
		// start at x = a, the root candidate will decrease monotonically and never get too small, till x * x <= a, break out the loop.
		long x = a;
		while (x * x > a)
			x = (x + a / x) / 2;
		return x;
	}
};

class Solution_v2 {
public:
	int mySqrt(int a)
	{
		long left = 0, right = a, mid = 0;
		while (left <= right)
		{
			mid = left + (right - left) / 2;
			if (mid * mid == a || (mid * mid < a && (mid + 1) * (mid + 1) > a))
				break;
			else if (mid * mid > a)
				right = mid - 1;
			else
				left = mid + 1;
		}
		return mid;
	}
};

class Solution_v3 {
public:
	int mySqrt(int a)
	{
		if (a == 0)
			return 0;
		int left = 1, right = a, mid = 0;
		while (left <= right)
		{
			mid = left + (right - left) / 2;
			if (mid > a / mid)
				right = mid - 1;
			else
			{
				if (mid + 1 > a / (mid + 1))
					break;
				else
					left = mid + 1;
			}
		}
		return mid;
	}
};
