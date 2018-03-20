#pragma once

/*

9. Palindrome Number

Determine whether an integer is a palindrome. Do this without extra space.

###################################################
Approach:

No extra space ? Not gonna happen...

首先，负数都不是回文数，即使是 -121 这种，也不是回文数，因为不中心对称。
对于正数或者0，我们求出其逆序数（参考 7. Reverse Integer），当然，会有额外的空间消耗，不符合题意。
而且，特别需要注意的是，逆序的数字可能会超过 INT_MAX，所以需要用 long long 来存储。

###################################################
Approach More Generic:

还是用上面的思路，但是这次我们只去反转一半的数字，而保留余下的一半，如果两半相同则是回文串。
如 1221 => 12 12
若 12321 ，则 12 123， 由于 12 = 123 / 10 所以也是回文串

注：负数一定不是回文数，个位为0且不为0的数也一定不是回文数（因为数字的最高位一定不能为0）


*/

class Solution {
public:
	bool isPalindrome(int x)
	{
		if (x < 0)
			return false;
		return x == reverse(x);
	}

	long long reverse(int x)
	{
		long long y = 0;
		while (x)
		{
			y = y * 10 + x % 10;
			x = x / 10;
		}
		return y;
	}
};

class Solution_v2 {
public:
	bool isPalindrome(int x)
	{
		// 负数一定不是回文数，个位为0且不为0的数也一定不是回文数（因为数字的最高位一定不能为0）
		if (x < 0 || x % 10 == 0 && x != 0)
			return false;

		int reverse_number = 0;
		// when the original number is less than the reversed number, it means we've processed half of the number digits.
		while (reverse_number < x)
		{
			reverse_number = reverse_number * 10 + x % 10;
			x = x / 10;
		}
		return (reverse_number == x || reverse_number / 10 == x);
	}
};