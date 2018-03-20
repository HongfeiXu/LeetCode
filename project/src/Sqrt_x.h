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

����� a��Ҳ������� `x^2 - a = 0` �ķǸ��⡣

���ǲ����� (x,f(x)) ���������ƽ����� `x^2 - a = 0` �ĸ�������ʽΪ��

x[k+1] = (x[k] + n/x[k])/2, k >= 0, x[0] > 0

���ô��������дţ�ٵ���ʽ���ô��ǣ������м���ֻ��Ҫ������ֵ���д洢������Ҫ���и��ӵĸ��������㣩��

x[k+1] = floor((x[k] + floor(n/x[k]))/2), k >= 0, x[0] > 0, x[0] ��������x[k]ҲΪ������

Approach v2[TLE]:

�� 0~a��Χ����������x��ʹ�� x * x == a || (x * x < a && (x+1)*(x+1) >a)

Approach v3:

���ֲ���
use long type variable to hold intermediate values.

Appraoch v4:

���ֲ���
use int and divide operator������˷����Ӷ������� long ��ʹ�á�but slower.

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
