#pragma once

/*

204. Count Primes

Description:

Count the number of prime numbers less than a non-negative number, n.

Credits:
Special thanks to @mithmatt for adding this problem and creating all test cases.

Approach:
直接法，判断、计数
O(n^1.5)


Approach:
埃拉托斯特尼筛法
给出要筛数值的范围n，找出 sqrt {n} 以内的素数 p_1,p_2, ... ,p_k。
先用2去筛，即把2留下，把2的倍数剔除掉；再用下一个素数，也就是3筛，把3留下，把3的倍数剔除掉；接下去用下一个素数5筛，把5留下，把5的倍数剔除掉；不断重复下去......。
注：这里不需要再判断2、3、5、...等是素数
复杂度是O(n log log n)。

*/

#include <unordered_set>
#include <iostream>
#include <numeric>

using namespace std;

class Solution {
public:
	int countPrimes(int n)
	{
		int result = 0;

		for (int i = 0; i < n; ++i)
		{
			if (isPrime(i))
				++result;
		}
		return result;
	}

	bool isPrime(int n)
	{

		if (n <= 1)
			return false;

		// Loop's ending condition is i * i <= num instead of i <= sqrt(num)
		// to avoid repeatedly calling an expensive function sqrt().
		for (int i = 2; i * i <= n; ++i)
		{
			if (n % i == 0)
				return false;
		}
		return true;
	}
};

class Solution_v2 {
public:
	int countPrimes(int n)
	{
		if (n == 0)
			return 0;

		vector<int>is_prime_table(n, 1);

		is_prime_table[0] = 0;		// 0 不在考虑之列
		is_prime_table[1] = 0;		// 1 为非素数
		for (int i = 2; i * i < n; ++i)
		{
			if (!is_prime_table[i])
				continue;
			for (int j = i * i; j < n; j += i)
				is_prime_table[j] = 0;
		}

		return accumulate(is_prime_table.begin(), is_prime_table.end(), 0);
	}
};