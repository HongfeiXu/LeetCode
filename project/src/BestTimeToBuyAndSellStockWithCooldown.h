#pragma once

/*

309. Best Time to Buy and Sell Stock with Cooldown

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like 
(ie, buy one and sell one share of the stock multiple times) with the following restrictions:

You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)

Example:

prices = [1, 2, 3, 0, 2]
maxProfit = 3
transactions = [buy, sell, cooldown, buy, sell]

Approach:
Ref: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/discuss/75927
DP
The natural states for this problem is the 3 possible transactions : buy, sell, rest. Here rest means no transaction on that day (aka cooldown).
buy[i] means till day i what is the maxProfit for any sequence end with buy.
sell[i] means till day i what is the maxProfit for any sequence end with sell.
rest[i] means till day i what is the maxProfit for any sequence end with rest.

Then we want to deduce the transition functions for buy sell and rest. By definition we have:

buy[i] = max(rest[i-1] - prices[i], buy[i-1])
sell[i] = max(buy[i-1] + prices[i], sell[i-1])
rest[i] = max(sell[i-1], rest[i-1])

All of these are very straightforward. They simply represents : 'buy' before 'sell' before 'rest' before 'buy'
Because of sell[i] >= rest[i] >= buy[i],
rest[i] = sell[i-1]
=>
Now have 2 functions instead of 3:
buy[i] = max(sell[i-2] - prices[i], buy[i-1])
sell[i] = max(buy[i-1] + prices[i], sell[i-1])
buy[0] = -prices[0]
sell[0] = 0

Approach:
DP, space optimized

理解题目的话，可以直接写出如下递推式，不需要 rest[i] 作为中间变量
buy[i] = max(sell[i-2] - prices[i], buy[i-1])
sell[i] = max(buy[i-1] + prices[i], sell[i-1])
buy[0] = -prices[0]
sell[0] = 0

*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int maxProfit(vector<int>& prices)
	{
		int len = prices.size();
		if (len < 2)
			return 0;

		vector<int> buy(len, 0);
		vector<int> sell(len, 0);

		buy[0] = -prices[0];
		buy[1] = max(buy[0], -prices[1]);
		sell[1] = max(buy[0] + prices[1], sell[0]);	// 另外：sell[0] = 0

		for (int i = 2; i < len; ++i)
		{
			buy[i] = max(sell[i - 2] - prices[i], buy[i - 1]);
			sell[i] = max(buy[i - 1] + prices[i], sell[i - 1]);
		}
		return sell[len - 1];
	}
};

class Solution_v2 {
public:
	int maxProfit(vector<int>& prices)
	{
		int len = prices.size();
		if (len < 2)
			return 0;

		int buy = -prices[0], sell = 0, pre_buy = 0, pre_sell = 0;

		for (const auto& p : prices)
		{
			pre_buy = buy;
			buy = max(pre_sell - p, pre_buy);
			pre_sell = sell;
			sell = max(pre_buy + p, pre_sell);
		}

		return sell;
	}
};