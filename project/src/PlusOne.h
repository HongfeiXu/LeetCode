#pragma once

/*

66. Plus One

Given a non-negative integer represented as a non-empty array of digits, plus one to the integer.

You may assume the integer do not contain any leading zero, except the number 0 itself.

The digits are stored such that the most significant digit is at the head of the list.

Approach:
Pretty easy, just notice that digit == 9 is the special case


*/

#include <vector>

using namespace std;

class Solution {
public:
	vector<int> plusOne(vector<int> &digits)
	{
		for (int i = static_cast<int>(digits.size()) - 1; i >= 0; i--)
		{
			if (digits[i] < 9)
			{
				digits[i]++;
				return digits;
			}
			else
			{
				digits[i] = 0;
			}
		}
		digits.insert(digits.begin(), 1);
		return digits;
	}
};