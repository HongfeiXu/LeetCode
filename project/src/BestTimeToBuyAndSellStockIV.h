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

�ݹ�
���� prices[start...finish] �н��� k �ν��׵õ����������Ϊ��
result = max(result, dp[i] + maxProfitAux(k - 1, prices, i + start + 1, finish));
dp[i] ��ʾ prices[start...start+i] �н��� 1 �ν��׵õ����������

̫�������ⱻ�ظ��ļ���

#########################################################
Approach_v2:

Ref: http://blog.csdn.net/linhuanmars/article/details/23236995
Ref: http://blog.csdn.net/fightforyourdream/article/details/14503469###;
DP
�ֲ�������ȫ������
global[i][j]����ǰ����� i �죬���������� j �ν��ף���������Ϊ global[i][j]
local[i][j]: ��ǰ����� i �죬���������� j �ν��ף��������һ�ν����ڵ� i ����ɣ����������Ϊ local[i][j]

ȫ�ֵĵ���ʽ��
global[i][j] = max{local[i][j], global[i-1][j]}
Ҳ����ȡ��ǰ�ֲ���õģ��͹���ȫ����õ��д���Ǹ�����Ϊ���һ�ν������������ǰ��һ���ھֲ���õ����棬����һ���ڹ���ȫ�����ŵ����棩��
ȫ�֣������i�����j�ν��׵�������棩 = max{�ֲ����ڵ�i�콻�׺�ǡ������j�ν��ף���ȫ�֣������i-1��ʱ�Ѿ�����j�ν��ף�}

�ֲ��ĵ���ʽ��
local[i][j] = max{local[i-1][j] + diff, global[i-1][j-1] + max(0, diff)}

Ҳ���ǿ�����������һ����ȫ�ֵ�i-1�����j-1�ν��ף�Ȼ����Ͻ���Ľ��ף����������׬Ǯ�Ļ���Ҳ����ǰ��ֻҪj-1�ν��ף����һ�ν���ȡ��ǰ�죩��
�ڶ���������ȡlocal��i-1��j�ν��ף�Ȼ����Ͻ���Ĳ�ֵ��������Ϊlocal[i-1][j]���������i-1�������Ľ��ף��������ڱ�ɵ�i�����������������ӽ��״�����
������������diff�ǲ��Ǵ���0��һ��Ҫ���ϣ���Ϊ����Ͳ�����local[i][j]���������һ�������������ˣ���

�ֲ����ڵ�i�콻�׺��ܹ�������j�Σ� =  max{���2�����1}

���1���ڵ�i-1��ʱ��ǡ���Ѿ�������j�Σ�local[i-1][j]������ô���i-1�쵽i���ٽ���һ�Σ����ڵ�i-1�����룬��i��������diff�������ⲻ���������ӽ��״�����
�������ڵ�һ�����룬�ڶ���������Ȼ��ڶ��������룬����������������Ϊ  ��  ��һ�����룬����������  ��Ч����һ���ģ���ʵֻ������һ�ν��ף���Ϊ��������

���2����i-1��󣬹�������j-1�Σ�global[i-1][j-1]�������Ϊ�����㡰��i����󹲽�����j�ν��ף��ҵ�i�������н��ס���������
���ǿ���ѡ��1���ڵ�i-1�����룬Ȼ���ٵ�i��������diff��������ѡ���ڵ�i�����룬Ȼ��ͬ���ڵ�i������������Ϊ0����

Runtime Error Message:
terminate called after throwing an instance of 'std::bad_alloc'
what():  std::bad_alloc

#########################################################
Approach v3:
��� Approach v2 �� Runtime Error

���� k >= prices.size()/2 ���������ʱ����������ʱ�������ף����������� BestTimeToBuyAndSellStockII �ȼۣ�����ֱ���� O(n) ����õ�
�� k < prices.size()/2���� Time: O(kn)��Space: O(2k)

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

	// prices[start...finish] ������� k �ν��׻�õ��������
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
			// ��������
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
			// ��������
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
		// �����Ż��˿ռ�ռ�ã�ԭʼ�Ļ�Ϊ vector<vector<int>> global(len, vector<int>(k + 1, 0));
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
		// ��ֹ k ����Ӱ��ռ�����
		if (k >= len / 2)
			return maxProfitAll(prices);

		vector<vector<int>> global(2, vector<int>(k + 1, 0));
		vector<vector<int>> local(2, vector<int>(k + 1, 0));

		for (int i = 1; i < len; ++i)		// 0~0�����k�ν��ף�����Ϊ0����i��1��ʼ
		{
			int diff = prices[i] - prices[i - 1];
			for (int j = 1; j <= k; ++j)	// 0~i�����0�ν��ף�����Ϊ0����j��1��ʼ
			{
				local[i % 2][j] = max(local[(i - 1 + 2) % 2][j] + diff, global[(i - 1 + 2) % 2][j - 1] + max(0, diff));
				global[i % 2][j] = max(local[i % 2][j], global[(i - 1 + 2) % 2][j]);
			}
		}
		return global[(len - 1) % 2][k];
	}
};

