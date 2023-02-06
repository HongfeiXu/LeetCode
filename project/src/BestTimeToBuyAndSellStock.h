#pragma once


/*

121. Best Time to Buy and Sell Stock

Related Topics: Array

Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), 
design an algorithm to find the maximum profit.

Example 1:
Input: [7, 1, 5, 3, 6, 4]
Output: 5

max. difference = 6-1 = 5 (not 7-1 = 6, as selling price needs to be larger than buying price)
Example 2:
Input: [7, 6, 4, 3, 1]
Output: 0

In this case, no transaction is done, i.e. max profit = 0.

Approach(Time Limit Exceeded):
2 for loop, time O(n*n)

Approach v2: WOW

Notice day0 buy and day3 sell, the profit = (prices[1] - prices[0]) + (prices[2] - prices[1]) + (prices[3] - prices[2])

The logic to solve this problem is same as "max subarray problem" using Kadane's Algorithm

https://discuss.leetcode.com/topic/19853/kadane-s-algorithm-since-no-one-has-mentioned-about-this-so-far-in-case-if-interviewer-twists-the-input/2

Here, the logic is to calculate the difference (max_curr += prices[i+1] - prices[i]) of the original array, 
and find a contiguous subarray giving maximum profit. If the difference falls below 0, reset it to zero.

Approach v3:
DP
dp[i] 记录从 prices[0...i] 进行一次交易获得的最大收益，用 min_price 保存 prices[0...i] 的最低价格
则
dp[i+1] = max(dp[i], prices[i+1] - min_price)

Approach v4:
相当于时 Approach v3 的 Space Optimized 版本
只需要遍历一次数组，通过一个变量记录当前最低价格，同时算出此次交易利润，并与当前最大值比较就可以了。

*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	int maxProfit(vector<int>& prices)
	{
		int result = 0;

		int size = static_cast<int>(prices.size());

		for (int i = 0; i < size-1; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				if (prices[j] - prices[i] > result)
					result = prices[j] - prices[i];
			}
		}

		return result;
	}

	int maxProfit_v2(vector<int>& prices)
	{
		int max_curr = 0;
		int max_so_far = 0;

		for (int i = 1; i < static_cast<int>(prices.size()); i++)
		{
			max_curr = max(0, max_curr + prices[i] - prices[i - 1]);
			max_so_far = max(max_curr, max_so_far);
		}
		return max_so_far;
	}

	int maxProfit_v3(vector<int>& prices)
	{
		int len = prices.size();
		if (len == 0)
			return 0;
		vector<int> dp(len, 0);			// dp[i] 记录从 prices[0...i] 进行一次交易获得的最大收益
		int min_price = prices[0];		// 低价买入
		for (int i = 1; i < len; ++i)
		{
			dp[i] = max(dp[i - 1], prices[i] - min_price);
			min_price = min(min_price, prices[i]);
		}
		return dp[len - 1];
	}
	
	int maxProfit_v4(vector<int>& prices)
	{
		int len = prices.size();
		if (len == 0)
			return 0;
		int min_price = prices[0];		// 低价买入
		int result = 0;
		for (int i = 1; i < len; ++i)
		{
			result = max(result, prices[i] - min_price);
			min_price = min(min_price, prices[i]);
		}
		return result;
	}
};