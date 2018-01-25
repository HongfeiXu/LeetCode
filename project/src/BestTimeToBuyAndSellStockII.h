#pragma once

/*

122. Best Time to Buy and Sell Stock II

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. 
You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). 
However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	int maxProfit(vector<int>& prices)
	{
		if (prices.empty())
			return 0;
		
		int start = 0;
		int end = 0;
		
		int max_profit = 0;

		// 找到 prices 中非递减的若干段，段首买入，段尾卖出。
		while (start < prices.size() - 1)
		{
			if (prices[start] < prices[start + 1])
			{
				end = start + 1;
				while (end + 1 < prices.size() && prices[end] <= prices[end + 1])
					++end;
				max_profit += prices[end] - prices[start];
				start = end + 1;
			}
			else
			{
				++start;
			}
		}

		return max_profit;
	}

	int maxProfit_v2(vector<int>& prices)
	{
		if (prices.empty())
			return 0;

		int max_profit = 0;
		
		// 对于 7 1 5 6 2
		// 1 买 6 出，相当于 5-1+6-5，即只要相邻两天的价格是上涨的就可以直接加入 max_profit 中，结果是正确的。
		for (int i = 1; i < prices.size(); i++)
		{
			max_profit += max(0, prices[i] - prices[i - 1]);
		}

		return max_profit;
	}

	int maxProfit_v3(vector<int>& prices)
	{
		int maxProfit = 0;
		for (int i = 0; i < prices.size();)
		{
			// 寻找极小值
			int j = i;
			while (j + 1 < prices.size() && prices[j] > prices[j + 1])
				++j;
			int k = j;
			// 寻找极大值
			while (k + 1 < prices.size() && prices[k] < prices[k + 1])
				++k;
			maxProfit += prices[k] - prices[j];
			i = k + 1;
		}
		return maxProfit;
	}
};