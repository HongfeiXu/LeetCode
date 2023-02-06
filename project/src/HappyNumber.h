#pragma once

/*

202. Happy Number

Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: Starting with any positive integer, 
replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), 
or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.

Example: 19 is a happy number

12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1

*/

#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
	bool isHappy(int n)
	{
		unordered_set<int> already_judged;
		while (n != 1)
		{
			if (already_judged.find(n) != already_judged.end())
				return false;

			already_judged.insert(n);
			n = nextNumber(n);
		}
		return true;
	}

	int nextNumber(int n)
	{
		vector<int> digits;
		num2ToDigit(n, digits);
		n = 0;
		for (auto d : digits)
			n += d * d;
		return n;
	}

	// 正整数拆分为数位
	void num2ToDigit(int n, vector<int>& digits)
	{
		if (n / 10 != 0)
			num2ToDigit(n / 10, digits);
		digits.push_back(n % 10);
	}
};
