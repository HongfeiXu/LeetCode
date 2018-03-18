# Mathematical Algorithms

>Ref: https://www.geeksforgeeks.org/fundamentals-of-algorithms/#MathematicalAlgorithms

## Some Nice Problems

### 1. Write an Efficient Method to Check if a Number is Multiple of 3

TODO...

### 2. Write a program to print all permutations of a given string

TODO...

## Some Small Useful Scripts

### 1. Reverse a integer number

>Ref: https://leetcode.com/problems/reverse-integer/description/

```c++
/*

Given a 32-bit signed integer, reverse digits of an integer.
Assume we are dealing with an environment which could only hold integers within the 32-bit signed integer range. 
For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.
*/
class Solution {
public:
	int reverse(int x)
	{
		long long val = 0;
		while (x)
		{
			val = val * 10 + x % 10;
			x = x / 10;
		}
		return (val > INT_MAX || val < INT_MIN) ? 0 : val;
	}
};
```