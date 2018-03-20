#pragma once

/*

9. Palindrome Number

Determine whether an integer is a palindrome. Do this without extra space.

###################################################
Approach:

No extra space ? Not gonna happen...

���ȣ����������ǻ���������ʹ�� -121 ���֣�Ҳ���ǻ���������Ϊ�����ĶԳơ�
������������0��������������������ο� 7. Reverse Integer������Ȼ�����ж���Ŀռ����ģ����������⡣
���ң��ر���Ҫע����ǣ���������ֿ��ܻᳬ�� INT_MAX��������Ҫ�� long long ���洢��

###################################################
Approach More Generic:

�����������˼·�������������ֻȥ��תһ������֣����������µ�һ�룬���������ͬ���ǻ��Ĵ���
�� 1221 => 12 12
�� 12321 ���� 12 123�� ���� 12 = 123 / 10 ����Ҳ�ǻ��Ĵ�

ע������һ�����ǻ���������λΪ0�Ҳ�Ϊ0����Ҳһ�����ǻ���������Ϊ���ֵ����λһ������Ϊ0��


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
		// ����һ�����ǻ���������λΪ0�Ҳ�Ϊ0����Ҳһ�����ǻ���������Ϊ���ֵ����λһ������Ϊ0��
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