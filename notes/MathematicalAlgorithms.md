# Mathematical Algorithms

>Ref: https://www.geeksforgeeks.org/fundamentals-of-algorithms/#MathematicalAlgorithms

## Some Basic Problems

### 1. Write an Efficient Method to Check if a Number is Multiple of 3

TODO...

### 2. 字符串的全排列

>Ref: https://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/

Below are the permutations of string ABC.   
ABC ACB BAC BCA CBA CAB

![NewPermutation](https://github.com/HongfeiXu/LeetCode/blob/master/images/NewPermutation.gif?raw=true)

**a. 递归求字符串的全排列，包含重复**   

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

**b. 递归求字符串的全排列，不包含重复**  

```c++
/*
去掉重复的全排列的递归实现（基于SolutionRaw）
在全排列中去掉重复的规则：去重的全排列就是从第一个数字起每个数分别与它后面非重复出现的数字交换。
下面给出完整代码：
*/
class SolutionHandleDup_v1 {
public:
	// 在 [left, right) 区间中查找是或否有与 a[right] 相同的字符，若有了，则不能进行 swap，以此来避免重复的排列。
	bool canSwap(string& a, int left, int right)
	{
		for (int i = left; i < right; ++i)
		{
			if (a[i] == a[right])
				return false;
		}
		return true;
	}

	// 排列 a[left,left+1,...,right]
	void permuteAux(string& a, int left, int right, vector<string>& result)
	{
		// 若 left == right，说明所有字符的位置已经确定，则为一个排列结果。
		if (left == right)
			result.push_back(a);
		// i 从 left 开始到 right 结束，选择一个数字作为 a[left]。
		for (int i = left; i <= right; ++i)
		{
			if (canSwap(a, left, i))
			{
				swap(a[left], a[i]);
				permuteAux(a, left + 1, right, result);
				swap(a[left], a[i]);	// backtrack
			}
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

**c. 非递归求字符串的全排列，去除重复** 

```c++
/*
去掉重复的全排列的非递归实现（自己写 nextPermutation()）
Ref: http://en.cppreference.com/w/cpp/algorithm/next_permutation
Ref: http://blog.csdn.net/hackbuteer1/article/details/7462447
Ref: 《STL源码剖析》
Time: O(n*n!)
*/
class SolutionHandleDup_v4 {
public:
	vector<string> permute(string a)
	{
		sort(a.begin(), a.end());
		vector<string> result;
		result.push_back(a);
		while (nextPermutation(a.begin(), a.end()))
			result.push_back(a);
		return result;
	}
	/*
	参考STL next_permutation() 的写法
	nextPermutation 会取得 [first, last) 所标示序列的下一个排列组合。
	如果没有下一个排列组合，则返回 false；否则返回 true。
	*/
	bool nextPermutation(string::iterator first, string::iterator last)
	{
		// 若字符串为空，则没有下一个排列，返回 false
		if (first == last)
			return false;
		auto i = last;
		// 若字符串中只有一个字符，则没有下一个排列，返回 false
		if (first == --i)
			return false;
		while (true)
		{
			auto i1 = i;
			// 从后向前寻找替换数，即前一个元素i小于后一个元素i1，i即为要替换的数字，i即为替换点
			if (*(--i) < *i1)
			{
				// 从后向前寻找第一个比 *i 大的数字 *i2
				auto i2 = last;
				while (!(*i < *--i2))
					;

				// 构造下一个排列
				iter_swap(i, i2);	// 替换 *i, *i2
				reverse(i1, last);	// 替换点 i 后的数全部反转
				return true;
			}
			// i到最前面了，没有找到替换数，当前字符串为最大排列，颠倒得到最小排列，并返回 false。
			if (i == first)
			{
				reverse(first, last);
				return false;
			}
		}
	}
};
```

**总结**

至此我们已经运用了递归与非递归的方法解决了全排列问题，总结一下就是：
1. 全排列就是从第一个数字起每个数分别与它后面的数字交换。
2. 去重的全排列就是从第一个数字起每个数分别与它后面非重复出现的数字交换。
3. 全排列的非递归就是由后向前找替换数和替换点，然后由后向前找第一个比替换数大的数与替换数交换，最后颠倒替换点后的所有数据。

*更多的内容看代码：[Permutation.h](https://github.com/HongfeiXu/LeetCode/blob/master/notes/src/Permutation.h)*

### 3. 字符串的组合

输入一个字符串，输出该字符串中字符的所有组合。举个例子，如果输入abc，它的组合有a、b、c、ab、ac、bc、abc。

和求解全排列类似，这里也使用回溯法的思路。

**法一**

```c++
/*
对于字符串中每一个字符，在每个组合中只有两种情况，要么存在，要么不存在。
从首字符开始，递归得到包括该字符的组合，不包括该字符的组合。
最终得到长度为1,2,3,...,s.size()的组合
*/
class Solution {
public:
	vector<string> combine(string s)
	{
		vector<string> result;
		string curr = "";
		combineAux(s, 0, curr, result);
		return result;
	}

	// a 为输入的字符串
	// i 表示当前要选择的字符 a[i]，要么放入当前组合，要么不放入
	// curr 表示当前组合
	// result 保存所有组合
	void combineAux(const string& a, int i, string& curr,  vector<string>& result)
	{
		if (i == a.size())
		{
			// 跳过空组合
			if (curr.empty())
				return;
			result.push_back(curr);
			return;
		}

		// 将 a[i] 放入当前组合
		curr.push_back(a[i]);
		combineAux(a, i + 1, curr, result);
		curr.pop_back();	// backtrack
		// 不把 a[i] 放入当前组合
		combineAux(a, i + 1, curr, result);
	}
};
```

**法二**
>Ref: http://blog.csdn.net/hackbuteer1/article/details/7462447

```c++
/*
假设我们想在长度为n的字符串中求m个字符的组合。我们先从头扫描字符串的第一个字符。
针对第一个字符，我们有两种选择：
第一是把这个字符放到组合中去，接下来我们需要在剩下的n-1个字符中选取m-1个字符；
第二是不把这个字符放到组合中去，接下来我们需要在剩下的n-1个字符中选择m个字符。

求s中长度为1,2,3,...,s.size()的组合，则，只需要调用 combineAux 传入不同的长度作为参数即可。
*/
class Solution_v2 {
public:
	// 求s中长度为m的组合
	void combineAux(string s, int m, string& curr, vector<string>& result)
	{
		if (m == 0)
		{
			result.push_back(curr);
			return;
		}
		// 如果s已经为空，说明没有字符可供选择，而此时m不为0，说明还未能选够足够的字符，返回
		if (s.empty())
			return;
		// 把这个字符放到组合中去，接下来我们需要在剩下的s.size()-1个字符中选取m-1个字符
		curr.push_back(s[0]);
		combineAux(s.substr(1), m - 1, curr, result);
		curr.pop_back();	// backtrack
		// 不把这个字符放到组合中去，接下来我们需要在剩下的s.size() - 1个字符中选择m个字符
		combineAux(s.substr(1), m, curr, result);
	}

	vector<string> combine(string s)
	{
		vector<string> result;
		string curr = "";
		for(int i = 1; i <= s.size(); ++i)
			combineAux(s, i, curr, result);
		return result;
	}
};
```

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

**牛顿迭代法快速寻找平方根**

>Ref: https://www.zhihu.com/question/20690553（详细介绍了牛顿-拉弗森方法的原理以及收敛的充分条件）   
>Ref: http://www.matrix67.com/blog/archives/361   

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

**牛顿迭代法快速寻找整数的整数平方根**

>Ref: https://en.wikipedia.org/wiki/Integer_square_root#Using_only_integer_division

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