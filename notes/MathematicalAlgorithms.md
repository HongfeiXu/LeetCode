# Mathematical Algorithms

>Ref: https://www.geeksforgeeks.org/fundamentals-of-algorithms/#MathematicalAlgorithms

## Some Basic Problems

### 1. Write an Efficient Method to Check if a Number is Multiple of 3

TODO...

### 2. �ַ�����ȫ����

>Ref: https://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/

Below are the permutations of string ABC.   
ABC ACB BAC BCA CBA CAB

![NewPermutation](https://github.com/HongfeiXu/LeetCode/blob/master/images/NewPermutation.gif?raw=true)

**a. �ݹ����ַ�����ȫ���У������ظ�**   

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

**b. �ݹ����ַ�����ȫ���У��������ظ�**  

```c++
/*
ȥ���ظ���ȫ���еĵݹ�ʵ�֣�����SolutionRaw��
��ȫ������ȥ���ظ��Ĺ���ȥ�ص�ȫ���о��Ǵӵ�һ��������ÿ�����ֱ�����������ظ����ֵ����ֽ�����
��������������룺
*/
class SolutionHandleDup_v1 {
public:
	// �� [left, right) �����в����ǻ������ a[right] ��ͬ���ַ��������ˣ����ܽ��� swap���Դ��������ظ������С�
	bool canSwap(string& a, int left, int right)
	{
		for (int i = left; i < right; ++i)
		{
			if (a[i] == a[right])
				return false;
		}
		return true;
	}

	// ���� a[left,left+1,...,right]
	void permuteAux(string& a, int left, int right, vector<string>& result)
	{
		// �� left == right��˵�������ַ���λ���Ѿ�ȷ������Ϊһ�����н����
		if (left == right)
			result.push_back(a);
		// i �� left ��ʼ�� right ������ѡ��һ��������Ϊ a[left]��
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

**c. �ǵݹ����ַ�����ȫ���У�ȥ���ظ�** 

```c++
/*
ȥ���ظ���ȫ���еķǵݹ�ʵ�֣��Լ�д nextPermutation()��
Ref: http://en.cppreference.com/w/cpp/algorithm/next_permutation
Ref: http://blog.csdn.net/hackbuteer1/article/details/7462447
Ref: ��STLԴ��������
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
	�ο�STL next_permutation() ��д��
	nextPermutation ��ȡ�� [first, last) ����ʾ���е���һ��������ϡ�
	���û����һ��������ϣ��򷵻� false�����򷵻� true��
	*/
	bool nextPermutation(string::iterator first, string::iterator last)
	{
		// ���ַ���Ϊ�գ���û����һ�����У����� false
		if (first == last)
			return false;
		auto i = last;
		// ���ַ�����ֻ��һ���ַ�����û����һ�����У����� false
		if (first == --i)
			return false;
		while (true)
		{
			auto i1 = i;
			// �Ӻ���ǰѰ���滻������ǰһ��Ԫ��iС�ں�һ��Ԫ��i1��i��ΪҪ�滻�����֣�i��Ϊ�滻��
			if (*(--i) < *i1)
			{
				// �Ӻ���ǰѰ�ҵ�һ���� *i ������� *i2
				auto i2 = last;
				while (!(*i < *--i2))
					;

				// ������һ������
				iter_swap(i, i2);	// �滻 *i, *i2
				reverse(i1, last);	// �滻�� i �����ȫ����ת
				return true;
			}
			// i����ǰ���ˣ�û���ҵ��滻������ǰ�ַ���Ϊ������У��ߵ��õ���С���У������� false��
			if (i == first)
			{
				reverse(first, last);
				return false;
			}
		}
	}
};
```

**�ܽ�**

���������Ѿ������˵ݹ���ǵݹ�ķ��������ȫ�������⣬�ܽ�һ�¾��ǣ�
1. ȫ���о��Ǵӵ�һ��������ÿ�����ֱ�������������ֽ�����
2. ȥ�ص�ȫ���о��Ǵӵ�һ��������ÿ�����ֱ�����������ظ����ֵ����ֽ�����
3. ȫ���еķǵݹ�����ɺ���ǰ���滻�����滻�㣬Ȼ���ɺ���ǰ�ҵ�һ�����滻����������滻�����������ߵ��滻�����������ݡ�

*��������ݿ����룺[Permutation.h](https://github.com/HongfeiXu/LeetCode/blob/master/notes/src/Permutation.h)*

### 3. �ַ��������

����һ���ַ�����������ַ������ַ���������ϡ��ٸ����ӣ��������abc�����������a��b��c��ab��ac��bc��abc��

�����ȫ�������ƣ�����Ҳʹ�û��ݷ���˼·��

**��һ**

```c++
/*
�����ַ�����ÿһ���ַ�����ÿ�������ֻ�����������Ҫô���ڣ�Ҫô�����ڡ�
�����ַ���ʼ���ݹ�õ��������ַ�����ϣ����������ַ�����ϡ�
���յõ�����Ϊ1,2,3,...,s.size()�����
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

	// a Ϊ������ַ���
	// i ��ʾ��ǰҪѡ����ַ� a[i]��Ҫô���뵱ǰ��ϣ�Ҫô������
	// curr ��ʾ��ǰ���
	// result �����������
	void combineAux(const string& a, int i, string& curr,  vector<string>& result)
	{
		if (i == a.size())
		{
			// ���������
			if (curr.empty())
				return;
			result.push_back(curr);
			return;
		}

		// �� a[i] ���뵱ǰ���
		curr.push_back(a[i]);
		combineAux(a, i + 1, curr, result);
		curr.pop_back();	// backtrack
		// ���� a[i] ���뵱ǰ���
		combineAux(a, i + 1, curr, result);
	}
};
```

**����**
>Ref: http://blog.csdn.net/hackbuteer1/article/details/7462447

```c++
/*
�����������ڳ���Ϊn���ַ�������m���ַ�����ϡ������ȴ�ͷɨ���ַ����ĵ�һ���ַ���
��Ե�һ���ַ�������������ѡ��
��һ�ǰ�����ַ��ŵ������ȥ��������������Ҫ��ʣ�µ�n-1���ַ���ѡȡm-1���ַ���
�ڶ��ǲ�������ַ��ŵ������ȥ��������������Ҫ��ʣ�µ�n-1���ַ���ѡ��m���ַ���

��s�г���Ϊ1,2,3,...,s.size()����ϣ���ֻ��Ҫ���� combineAux ���벻ͬ�ĳ�����Ϊ�������ɡ�
*/
class Solution_v2 {
public:
	// ��s�г���Ϊm�����
	void combineAux(string s, int m, string& curr, vector<string>& result)
	{
		if (m == 0)
		{
			result.push_back(curr);
			return;
		}
		// ���s�Ѿ�Ϊ�գ�˵��û���ַ��ɹ�ѡ�񣬶���ʱm��Ϊ0��˵����δ��ѡ���㹻���ַ�������
		if (s.empty())
			return;
		// ������ַ��ŵ������ȥ��������������Ҫ��ʣ�µ�s.size()-1���ַ���ѡȡm-1���ַ�
		curr.push_back(s[0]);
		combineAux(s.substr(1), m - 1, curr, result);
		curr.pop_back();	// backtrack
		// ��������ַ��ŵ������ȥ��������������Ҫ��ʣ�µ�s.size() - 1���ַ���ѡ��m���ַ�
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

**ţ�ٵ���������Ѱ��ƽ����**

>Ref: https://www.zhihu.com/question/20690553����ϸ������ţ��-����ɭ������ԭ���Լ������ĳ��������   
>Ref: http://www.matrix67.com/blog/archives/361   

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

**ţ�ٵ���������Ѱ������������ƽ����**

>Ref: https://en.wikipedia.org/wiki/Integer_square_root#Using_only_integer_division

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