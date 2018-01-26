#pragma once

/*

714. Best Time to Buy and Sell Stock with Transaction Fee

Your are given an array of integers prices, for which the i-th element is the price of a given stock on day i; 
and a non-negative integer fee representing a transaction fee.

You may complete as many transactions as you like, 
but you need to pay the transaction fee for each transaction. 
You may not buy more than 1 share of a stock at a time 
(ie. you must sell the stock share before you buy again.)

Return the maximum profit you can make.

Example 1:

Input: prices = [1, 3, 2, 8, 4, 9], fee = 2
Output: 8
Explanation: The maximum profit can be achieved by:
Buying at prices[0] = 1
Selling at prices[3] = 8
Buying at prices[4] = 4
Selling at prices[5] = 9
The total profit is ((8 - 1) - 2) + ((9 - 4) - 2) = 8.

Note:

0 < prices.length <= 50000.
0 < prices[i] < 50000.
0 <= fee < 50000.

Approach:
DP
交易次数不限，但加入了交易费的条件，受 《309. Best Time to Buy and Sell Stock with Cooldown》 的启发，很容易写出下面的定义以及递推式
buy[i] means till day i what is the maxProfit for any sequence end with buy.
sell[i] means till day i what is the maxProfit for any sequence end with sell.
递推式如下：
buy[i] = max(sell[i-1] - prices[i], buy[i-1])			// 若在i天买入，则减去售价，若不在i天出售，则收益为 buy[i-1]，取两者中较大的
sell[i] = max(buy[i-1] + prices[i] - fee, sell[i-1])	// 若在i天出售，则加上售价并减去交易费，buy[i-1]+prices[i]-fee，若不在i天出售，则收益为 sell[i-1]，取两者中较大的
buy[0] = -prices[0]
sell[0] = 0

Time: O(n)
Space: O(n)

Approach v2:

DP with Space Optimizing

Time: O(n)
Space: O(1)

*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int maxProfit(vector<int>& prices, int fee)
	{
		int len = prices.size();
		if (len < 2)
			return 0;
		vector<int> buy(len, 0);
		vector<int> sell(len, 0);
		buy[0] = -prices[0];
		for (int i = 1; i < len; ++i)
		{
			buy[i] = max(sell[i - 1] - prices[i], buy[i - 1]);
			sell[i] = max(buy[i - 1] + prices[i] - fee, sell[i - 1]);
		}
		return sell[len - 1];
	}
};

class Solution_v2 {
public:
	int maxProfit(vector<int>& prices, int fee)
	{
		int len = prices.size();
		if (len < 2)
			return 0;
		int buy = -prices[0], sell = 0, pre_buy = 0;
		for (int i = 1; i < len; ++i)
		{
			pre_buy = buy;
			buy = max(sell - prices[i], pre_buy);
			sell = max(pre_buy + prices[i] - fee, sell);
		}
		return sell;
	}
};
