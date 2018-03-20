# Mathematical Algorithms

>Ref: https://www.geeksforgeeks.org/fundamentals-of-algorithms/#MathematicalAlgorithms

## Some Nice Problems

### 1. Write an Efficient Method to Check if a Number is Multiple of 3

TODO...

### 2. Write a program to print all permutations of a given string

**求字符串的全排列**

Ref: https://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/

A permutation, also called an “arrangement number” or “order,” is a rearrangement of the elements of an ordered list S into a one-to-one correspondence with S itself. A string of length n has n! permutation.

Below are the permutations of string ABC.   
ABC ACB BAC BCA CBA CAB

Here is a solution that is used as a basis in **backtracking**.

![NewPermutation](https://github.com/HongfeiXu/LeetCode/blob/master/images/NewPermutation.gif?raw=true)

Note : The below solution prints duplicate permutations if there are repeating characters in input string. 

Time Complexity: O(n*n!) Note that there are n! permutations and it requires O(n) time to print a a permutation.

```c++
/*
全排列的递归实现
全排列就是从第一个数字起每个数分别与它后面的数字交换。（未去重）
很容易的可以使用 unordered_set 保存中间结果实现去重。
*/
class SolutionRaw {
public:
	// 排列 a[left,left+1,...,right]
	void permuteAux(string& a, int left, int right, vector<string>& result)
	{
		// 若 left == right，说明所有字符的位置已经确定，则为一个排列结果。
		if (left == right)
			result.push_back(a);
		// i 从 left 开始到 right 结束，选择一个数字作为 a[left]。
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
去掉重复的全排列的非递归实现（借助STL中 next_permutation()）
Time: O(n*n!) 
这里每次 next_permutation 最多进行 a.size() / 2 此交换。
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

*更多的内容看代码：[Permutation.h](https://github.com/HongfeiXu/LeetCode/blob/master/notes/src/Permutation.h)*

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

**牛顿迭代法快速寻找平方根 **  
Ref: https://www.zhihu.com/question/20690553（详细介绍了牛顿-拉弗森方法的原理以及收敛的充分条件）   
Ref: http://www.matrix67.com/blog/archives/361   

求根号 a，也就是求解 `x^2 - a = 0` 的非负解。   
这种算法的原理很简单，我们仅仅是不断用 (x,f(x)) 的切线来逼近方程 `x^2 - a = 0` 的根。   
根号a实际上就是 `x^2-a=0` 的一个正实根，这个函数的导数是 2x。也就是说，函数上任一点 (x,f(x)) 处的切线斜率是 2x。   
那么，x-f(x)/(2x) 就是一个比x更接近的近似值。代入 `f(x)=x^2-a` 得到 `x-(x^2-a)/(2x)`，也就是 `(x+a/x)/2`。   

迭代式为：

x[k+1] = (x[k] + n/x[k])/2, k >= 0, x[0] > 0

```c++
// 迭代求根号 n
double NewtonsMethod(double n)
{
	if (n == 0)
		return n;
	int k = 10;			// 控制迭代次数
	double result = n;
	for (int i = 0; i < k; ++i)
		result = (result + n / result) / 2;
	return result;
}
```

**牛顿迭代法快速寻找整数的整数平方根  **
Ref: https://en.wikipedia.org/wiki/Integer_square_root#Using_only_integer_division

另外，运用牛顿迭代法，可以快速计算整数 a 的整数平方根 x。即`x * x <= a,(x+1) * (x+1)>a`。   
运用带余除法改写上面的迭代式（好处是，这里中间结果只需要用整型值进行存储，不需要进行复杂的浮点数计算）：

x[k+1] = floor((x[k] + floor(n/x[k]))/2), k >= 0, x[0] > 0, x[0] 是整数（x[k]也为整数）

start at x = a, the root candidate will decrease monotonically and never get too small, till x * x <= a, x is the answer.

```c++
// leetcode 69, 计算 isqrt
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