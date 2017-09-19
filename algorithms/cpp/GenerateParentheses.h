#pragma once

/*

22. Generate Parentheses

Given n pairs of parentheses, write a function to 
generate all combinations of well-formed parentheses.

方法都很新颖

Related Topics: String, Backtracking

Approach Recurisive:

https://discuss.leetcode.com/topic/4485/concise-recursive-c-solution

The idea is intuitive. Use two integers to count the remaining left parenthesis (n) 
and the right parenthesis (m) to be added. At each function call add a left parenthesis
if n >0 and add a right parenthesis if m>0. 
Append the result and terminate recursive calls when both m and n are zero.

初始时，可加入的左括号数目为n,可加入的右括号数目为0
每加入一个"("，可以加入的")"数字会加1。可加入的"("数字会减1。
每加入一个")"，可加入的")"数字会减1。
直到没有可加入的括号为止。

Approach DP:

https://discuss.leetcode.com/topic/3474/an-iterative-method

My method is DP. First consider how to get the result f(n) from previous result f(0)...f(n-1).
Actually, the result f(n) will be put an extra () pair to f(n-1). Let the "(" always at the first position, to produce a valid result, we can only put ")" in a way that there will be i pairs () inside the extra () and n - 1 - i pairs () outside the extra pair.

Let us consider an example to get clear view:

f(0): ""
f(1): "("f(0)")"
f(2): "("f(0)")"f(1), "("f(1)")"
f(3): "("f(0)")"f(2), "("f(1)")"f(1), "("f(2)")"
So f(n) = "("f(0)")"f(n-1) , "("f(1)")"f(n-2) "("f(2)")"f(n-3) ... "("f(i)")"f(n-1-i) ... "(f(n-1)")"


*/

#include <vector>
#include <string>

using namespace std;

class Solution {
private:
	void addPara(vector<string> & v, string s, int leftRemain, int rightRemain)
	{
		if (leftRemain == 0 && rightRemain == 0)
		{
			v.push_back(s);
			return;
		}
		if (leftRemain > 0)
		{
			addPara(v, s + "(", leftRemain - 1, rightRemain + 1);
		}
		if (rightRemain > 0)
		{
			addPara(v, s + ")", leftRemain, rightRemain - 1);
		}
	}

public:
	vector<string> generateParenthesis(int n)
	{
		vector<string> result;
		addPara(result, "", n, 0);

		return result;
	}

	vector<string> generateParenthesis_v2(int n)
	{
		vector<vector<string>> dp(n + 1);
		dp[0] = vector<string> { "" };
		for (int i = 1; i <= n; i++)
		{
			for (int j = 0; j < i; j++)
			{
				for (string part1 : dp[j])
				{
					for (string part2 : dp[i - j - 1])
					{
						string p = string("(") + part1 + string(")") + part2;
						dp[i].push_back(p);
					}
				}
			}
		}
		return dp[n];
	}
};