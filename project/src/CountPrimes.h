#pragma once

/*

204. Count Primes

Description:

Count the number of prime numbers less than a non-negative number, n.

Credits:
Special thanks to @mithmatt for adding this problem and creating all test cases.

Approach:
ֱ�ӷ����жϡ�����
O(n^1.5)


Approach:
������˹����ɸ��
����Ҫɸ��ֵ�ķ�Χn���ҳ� sqrt {n} ���ڵ����� p_1,p_2, ... ,p_k��
����2ȥɸ������2���£���2�ı����޳�����������һ��������Ҳ����3ɸ����3���£���3�ı����޳���������ȥ����һ������5ɸ����5���£���5�ı����޳����������ظ���ȥ......��
ע�����ﲻ��Ҫ���ж�2��3��5��...��������
���Ӷ���O(n log log n)��

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

		is_prime_table[0] = 0;		// 0 ���ڿ���֮��
		is_prime_table[1] = 0;		// 1 Ϊ������
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