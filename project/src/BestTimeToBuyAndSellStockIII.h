#pragma once

/*

123. Best Time to Buy and Sell Stock III

Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. You may complete at most two transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

Approach:
最多进行两次交易，可以将 prices 数组分为左右两个部分，对左边和右边分别最多进行一次交易，并分别计算最大交易额，并求和。
最终会比较得出最大的总交易额。
Time Limit Exceeded
Time: O(n^2)

Approach_v2:
Ref: http://blog.csdn.net/fightforyourdream/article/details/14503469
Ref: http://blog.csdn.net/li563868273/article/details/51073838

prices[0...n-1]
找寻一个点 j，用来将 prices[0...n-1] 分割为左右 prices[0...i] 和 prices[i+1...j] 两个部分
分别求两段的最大profit。
O(n^2)的算法很容易想到，就是Apporach_1

进行优化：
对于点j+1，求price[0..j+1]的最大profit时，很多工作是重复的，在求price[0..j]的最大profit中已经做过了。
类似于Best Time to Buy and Sell Stock，可以在O(1)的时间从price[0..j]推出price[0..j+1]的最大profit。
但是如何从price[j..n-1]推出price[j+1..n-1]？反过来思考，我们可以用O(1)的时间由price[j+1..n-1]推出price[j..n-1]。

最终算法：
数组 dp_left[i] 记录了 price[0..i] 的最大 profit，
数组 dp_right[i] 记录了 price[i..n] 的最大 profit。
已知 dp_left[i]，求 dp_left[i+1]是简单的，同样已知 dp_right[i]，求 dp_right[i-1]也很容易。
dp_left[i+1] = max(dp_left[i], prices[i+1] - min_price)
dp_right[i-1] = max(dp_right[i], max_price - prices[i-1])

最后，我们再用 O(n) 的时间找出最大的 dp_left[i]+dp_right[i+1]，即为题目所求。

思考：将问题推广到最多进行k次交易时，能获得的最大收益。

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
		int result = 0;
		for (int i = 0; i < prices.size(); ++i)
			result = max(result, maxProfitAux(prices, 0, i) + maxProfitAux(prices, i + 1, prices.size() - 1));
		return result;
	}

	// 只进行最多一次交易的最大收益
	int maxProfitAux(vector<int>& prices, int left, int right)
	{
		if (right - left <= 0)
			return 0;
		int curr_profit = 0;
		int max_profit = 0;
		for (int i = left + 1; i <= right; ++i)
		{
			curr_profit += prices[i] - prices[i - 1];
			curr_profit = max(0, curr_profit);
			max_profit = max(max_profit, curr_profit);
		}
		return max_profit;
	}
};

class Solution_v2 {
public:
	int maxProfit(vector<int>& prices)
	{
		int len = prices.size();
		if (len == 0)
			return 0;

		vector<int> dp_left(len, 0);
		vector<int> dp_right(len, 0);

		// 求出 dp_left
		int min_price = prices[0];	// 最低价买入
		dp_left[0] = 0;
		for (int i = 1; i < len; ++i)
		{
			// price[0...i] 最多交易一次的最大利润位 price[0...i-1] 的最大利润和“当前卖出价与之前最低买入价之差”的较大值
			dp_left[i] = max(dp_left[i - 1], prices[i] - min_price);	
			// 更新最低价
			min_price = min(min_price, prices[i]);			
		}

		// 求出 dp_right
		int max_price = prices[len - 1];
		for (int i = len - 2; i >= 0; --i)
		{
			dp_right[i] = max(dp_right[i + 1], max_price - prices[i]);
			max_price = max(max_price, prices[i]);
		}
		
		// 计算分割位置为 i 时的最大 profit，取最大值
		int result = 0;
		for (int i = 0; i < len; ++i)
		{
			if (i == len - 1)
				result = max(result, dp_left[i]);
			else
				result = max(result, dp_left[i] + dp_right[i+1]);
		}
		return result;
	}
};
