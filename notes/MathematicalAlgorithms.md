# Mathematical Algorithms

>Ref: https://www.geeksforgeeks.org/fundamentals-of-algorithms/#MathematicalAlgorithms

## Some Nice Problems

### 1. Write an Efficient Method to Check if a Number is Multiple of 3

TODO...

### 2. Write a program to print all permutations of a given string

**���ַ�����ȫ����**

Ref: https://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/

A permutation, also called an ��arrangement number�� or ��order,�� is a rearrangement of the elements of an ordered list S into a one-to-one correspondence with S itself. A string of length n has n! permutation.

Below are the permutations of string ABC.   
ABC ACB BAC BCA CBA CAB

Here is a solution that is used as a basis in **backtracking**.

![NewPermutation](https://github.com/HongfeiXu/LeetCode/blob/master/images/NewPermutation.gif?raw=true)

Note : The below solution prints duplicate permutations if there are repeating characters in input string. 

Time Complexity: O(n*n!) Note that there are n! permutations and it requires O(n) time to print a a permutation.

```c++
/*
ȫ���еĵݹ�ʵ��
ȫ���о��Ǵӵ�һ��������ÿ�����ֱ�������������ֽ�������δȥ�أ�
�����׵Ŀ���ʹ�� unordered_set �����м���ʵ��ȥ�ء�
*/
class SolutionRaw {
public:
	// ���� a[left,left+1,...,right]
	void permuteAux(string& a, int left, int right, vector<string>& result)
	{
		// �� left == right��˵�������ַ���λ���Ѿ�ȷ������Ϊһ�����н����
		if (left == right)
			result.push_back(a);
		// i �� left ��ʼ�� right ������ѡ��һ��������Ϊ a[left]��
		for (int i = left; i <= right; ++i)
		{
			swap(a[left], a[i]);
			permuteAux(a, left + 1, right, result);
			swap(a[left], a[i]);	// backtrack
		}
	}

	vector<string> permute(string a)
	{
		vector<string> result;
		permuteAux(a, 0, a.size() - 1, result);
		return result;
	}
};
```

```c++
/*
ȥ���ظ���ȫ���еķǵݹ�ʵ�֣�����STL�� next_permutation()��
Time: O(n*n!) 
����ÿ�� next_permutation ������ a.size() / 2 �˽�����
*/
class SolutionHandleDup_v3{
public:
	vector<string> permute(string a)
	{
		sort(a.begin(), a.end());
		vector<string> result;
		result.push_back(a);
		while (next_permutation(a.begin(), a.end()))
			result.push_back(a);
		return result;
	}
};
```

*��������ݿ����룺[Permutation.h](https://github.com/HongfeiXu/LeetCode/blob/master/notes/src/Permutation.h)*

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

### 2. Square root

**ţ�ٵ���������Ѱ��ƽ���� **  
Ref: https://www.zhihu.com/question/20690553����ϸ������ţ��-����ɭ������ԭ���Լ������ĳ��������   
Ref: http://www.matrix67.com/blog/archives/361   

����� a��Ҳ������� `x^2 - a = 0` �ķǸ��⡣   
�����㷨��ԭ��ܼ򵥣����ǽ����ǲ����� (x,f(x)) ���������ƽ����� `x^2 - a = 0` �ĸ���   
����aʵ���Ͼ��� `x^2-a=0` ��һ����ʵ������������ĵ����� 2x��Ҳ����˵����������һ�� (x,f(x)) ��������б���� 2x��   
��ô��x-f(x)/(2x) ����һ����x���ӽ��Ľ���ֵ������ `f(x)=x^2-a` �õ� `x-(x^2-a)/(2x)`��Ҳ���� `(x+a/x)/2`��   

����ʽΪ��

x[k+1] = (x[k] + n/x[k])/2, k >= 0, x[0] > 0

```c++
// ��������� n
double NewtonsMethod(double n)
{
	if (n == 0)
		return n;
	int k = 10;			// ���Ƶ�������
	double result = n;
	for (int i = 0; i < k; ++i)
		result = (result + n / result) / 2;
	return result;
}
```

**ţ�ٵ���������Ѱ������������ƽ����  **
Ref: https://en.wikipedia.org/wiki/Integer_square_root#Using_only_integer_division

���⣬����ţ�ٵ����������Կ��ټ������� a ������ƽ���� x����`x * x <= a,(x+1) * (x+1)>a`��   
���ô��������д����ĵ���ʽ���ô��ǣ������м���ֻ��Ҫ������ֵ���д洢������Ҫ���и��ӵĸ��������㣩��

x[k+1] = floor((x[k] + floor(n/x[k]))/2), k >= 0, x[0] > 0, x[0] ��������x[k]ҲΪ������

start at x = a, the root candidate will decrease monotonically and never get too small, till x * x <= a, x is the answer.

```c++
// leetcode 69, ���� isqrt
class Solution {
public:
    int mySqrt(int a) {
        long x = a;
        while(x * x > a)
            x = (x + a / x) / 2;
        return x;
    }
};
```