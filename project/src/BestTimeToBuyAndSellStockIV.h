#pragma once

/*

188. Best Time to Buy and Sell Stock IV

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most k transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

#########################################################
Approach:
Time Limit Exceeded

11
[48,12,60,93,97,42,25,64,17,56,85,93,9,48,52,42,58,85,81,84,69,36,1,54,23,15,72,15,11,94]

递归
对于 prices[start...finish] 中进行 k 次交易得到的最大收益为：
result = max(result, dp[i] + maxProfitAux(k - 1, prices, i + start + 1, finish));
dp[i] 表示 prices[start...start+i] 中进行 1 次交易得到的最大收益

太多子问题被重复的计算

#########################################################
Approach_v2:

Ref: http://blog.csdn.net/linhuanmars/article/details/23236995
Ref: http://blog.csdn.net/fightforyourdream/article/details/14503469###;
DP
局部最优与全局最优
global[i][j]：当前到达第 i 天，可以最多进行 j 次交易，最多的收益为 global[i][j]
local[i][j]: 当前到达第 i 天，可以最多进行 j 次交易，并且最后一次交易在第 i 天完成，做多的收益为 local[i][j]

全局的递推式：
global[i][j] = max{local[i][j], global[i-1][j]}
也就是取当前局部最好的，和过往全局最好的中大的那个（因为最后一次交易如果包含当前天一定在局部最好的里面，否则一定在过往全局最优的里面）。
全局（到达第i天进行j次交易的最大收益） = max{局部（在第i天交易后，恰好满足j次交易），全局（到达第i-1天时已经满足j次交易）}

局部的递推式：
local[i][j] = max{local[i-1][j] + diff, global[i-1][j-1] + max(0, diff)}

也就是看两个量，第一个是全局到i-1天进行j-1次交易，然后加上今天的交易，如果今天是赚钱的话（也就是前面只要j-1次交易，最后一次交易取当前天），
第二个量则是取local第i-1天j次交易，然后加上今天的差值（这里因为local[i-1][j]比如包含第i-1天卖出的交易，所以现在变成第i天卖出，并不会增加交易次数，
而且这里无论diff是不是大于0都一定要加上，因为否则就不满足local[i][j]必须在最后一天卖出的条件了）。

局部（在第i天交易后，总共交易了j次） =  max{情况2，情况1}

情况1：在第i-1天时，恰好已经交易了j次（local[i-1][j]），那么如果i-1天到i天再交易一次：即在第i-1天买入，第i天卖出（diff），则这不并不会增加交易次数！
例如我在第一天买入，第二天卖出；然后第二天又买入，第三天再卖出的行为  和  第一天买入，第三天卖出  的效果是一样的，其实只进行了一次交易！因为有连续性

情况2：第i-1天后，共交易了j-1次（global[i-1][j-1]），因此为了满足“第i天过后共进行了j次交易，且第i天必须进行交易”的条件：
我们可以选择1：在第i-1天买入，然后再第i天卖出（diff），或者选择在第i天买入，然后同样在第i天卖出（收益为0）。

Runtime Error Message:
terminate called after throwing an instance of 'std::bad_alloc'
what():  std::bad_alloc

#########################################################
Approach v3:
针对 Approach v2 的 Runtime Error

考虑 k >= prices.size()/2 的情况，此时可以在任意时候做交易，问题变成了与 BestTimeToBuyAndSellStockII 等价，可以直接以 O(n) 计算得到
若 k < prices.size()/2，则 Time: O(kn)，Space: O(2k)

*/

#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;

// Time Limit Exceeded
class Solution {
public:
	int maxProfit(int k, vector<int>& prices)
	{
		return maxProfitAux(k, prices, 0, prices.size() - 1);
	}

	// prices[start...finish] 进行最多 k 次交易获得的最大收益
	int maxProfitAux(int k, vector<int>& prices, int start, int finish)
	{
		if (start >= finish)
			return 0;
		if (k == 0)
			return 0;
		else if (k == 1)
		{
			int result = 0;
			int min_prices = prices[start];
			for (int i = 1; i <= finish - start; ++i)
			{
				result = max(result, prices[start + i] - min_prices);
				min_prices = min(min_prices, prices[start + i]);
			}
			return result;
		}
		else if (k == 2)
		{
			int len_minus_one = finish - start;
			int result = 0;
			// 从左往右
			vector<int> dp_left(len_minus_one + 1, 0);
			int min_price = prices[start];
			for (int i = 1; i <= len_minus_one; ++i)
			{
				dp_left[i] = max(dp_left[i - 1], prices[i + start] - min_price);
				min_price = min(min_price, prices[i + start]);
			}
			//cout << "dp_left: ";
			//copy(dp_left.begin(), dp_left.end(), ostream_iterator<int>(cout, " "));
			//cout << endl;
			// 从右往左
			vector<int> dp_right(len_minus_one + 1, 0);
			int max_price = prices[finish];
			for (int i = len_minus_one - 1; i >= 0; --i)
			{
				dp_right[i] = max(dp_right[i + 1], max_price - prices[i + start]);
				max_price = max(max_price, prices[i + start]);
			}
			//cout << "dp_right: ";
			//copy(dp_right.begin(), dp_right.end(), ostream_iterator<int>(cout, " "));
			//cout << endl;
			for (int i = 0; i <= len_minus_one; ++i)
			{
				if (i == len_minus_one)
					result = max(result, dp_left[i]);
				else
					result = max(result, dp_left[i] + dp_right[i + 1]);
			}
			return result;
		}
		else
		{
			vector<int> dp(finish - start + 1, 0);
			int min_prices = prices.at(start);
			for (int i = 1; i <= finish - start; ++i)
			{
				dp[i] = max(dp[i - 1], prices.at(i + start) - min_prices);
				min_prices = min(min_prices, prices.at(i + start));
			}
			//copy(dp.begin(), dp.end(), ostream_iterator<int>(cout, " "));
			//cout << endl;
			int result = 0;
			for (int i = 0; i <= finish - start; ++i)
			{
				result = max(result, dp[i] + maxProfitAux(k - 1, prices, i + start + 1, finish));
			}
			return result;
		}
	}
};

// Run Time Error std::bad_alloc
class Solution_v2 {
public:
	int maxProfit(int k, vector<int>& prices)
	{
		int len = prices.size();
		if (len < 2)
			return 0;
		// 这里优化了空间占用，原始的话为 vector<vector<int>> global(len, vector<int>(k + 1, 0));
		vector<vector<int>> global(2, vector<int>(k + 1, 0));
		vector<vector<int>> local(2, vector<int>(k + 1, 0));

		for (int i = 1; i < len; ++i)
		{
			int diff = prices[i] - prices[i - 1];
			for (int j = 1; j <= k; ++j)
			{
				local[i % 2][j] = max(local[(i - 1 + 2) % 2][j] + diff, global[(i - 1 + 2) % 2][j - 1] + max(0, diff));
				global[i % 2][j] = max(local[i % 2][j], global[(i - 1 + 2) % 2][j]);
			}
		}
		return global[(len - 1) % 2][k];
	}
};

class Solution_v3 {
public:
	int maxProfitAll(vector<int>& prices)
	{
		int result = 0;
		for (int i = 1; i < prices.size(); ++i)
		{
			if (prices[i] > prices[i - 1])
				result += prices[i] - prices[i - 1];
		}
		return result;
	}

	int maxProfit(int k, vector<int>& prices)
	{
		int len = prices.size();
		if (len < 2)
			return 0;
		// if k >= n/2, we can have transactions any time, it can be solved by O(n).
		// 防止 k 过大影响空间消耗
		if (k >= len / 2)
			return maxProfitAll(prices);

		vector<vector<int>> global(2, vector<int>(k + 1, 0));
		vector<vector<int>> local(2, vector<int>(k + 1, 0));

		for (int i = 1; i < len; ++i)		// 0~0天进行k次交易，收益为0，故i从1开始
		{
			int diff = prices[i] - prices[i - 1];
			for (int j = 1; j <= k; ++j)	// 0~i天进行0次交易，收益为0，故j从1开始
			{
				local[i % 2][j] = max(local[(i - 1 + 2) % 2][j] + diff, global[(i - 1 + 2) % 2][j - 1] + max(0, diff));
				global[i % 2][j] = max(local[i % 2][j], global[(i - 1 + 2) % 2][j]);
			}
		}
		return global[(len - 1) % 2][k];
	}
};

