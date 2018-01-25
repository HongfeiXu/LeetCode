#pragma once

/*

123. Best Time to Buy and Sell Stock III

Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. You may complete at most two transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

Approach:
���������ν��ף����Խ� prices �����Ϊ�����������֣�����ߺ��ұ߷ֱ�������һ�ν��ף����ֱ��������׶����͡�
���ջ�Ƚϵó������ܽ��׶
Time Limit Exceeded
Time: O(n^2)

Approach_v2:
Ref: http://blog.csdn.net/fightforyourdream/article/details/14503469
Ref: http://blog.csdn.net/li563868273/article/details/51073838

prices[0...n-1]
��Ѱһ���� j�������� prices[0...n-1] �ָ�Ϊ���� prices[0...i] �� prices[i+1...j] ��������
�ֱ������ε����profit��
O(n^2)���㷨�������뵽������Apporach_1

�����Ż���
���ڵ�j+1����price[0..j+1]�����profitʱ���ܶ๤�����ظ��ģ�����price[0..j]�����profit���Ѿ������ˡ�
������Best Time to Buy and Sell Stock��������O(1)��ʱ���price[0..j]�Ƴ�price[0..j+1]�����profit��
������δ�price[j..n-1]�Ƴ�price[j+1..n-1]��������˼�������ǿ�����O(1)��ʱ����price[j+1..n-1]�Ƴ�price[j..n-1]��

�����㷨��
���� dp_left[i] ��¼�� price[0..i] ����� profit��
���� dp_right[i] ��¼�� price[i..n] ����� profit��
��֪ dp_left[i]���� dp_left[i+1]�Ǽ򵥵ģ�ͬ����֪ dp_right[i]���� dp_right[i-1]Ҳ�����ס�
dp_left[i+1] = max(dp_left[i], prices[i+1] - min_price)
dp_right[i-1] = max(dp_right[i], max_price - prices[i-1])

����������� O(n) ��ʱ���ҳ����� dp_left[i]+dp_right[i+1]����Ϊ��Ŀ����

˼�����������ƹ㵽������k�ν���ʱ���ܻ�õ�������档

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

	// ֻ�������һ�ν��׵��������
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

		// ��� dp_left
		int min_price = prices[0];	// ��ͼ�����
		dp_left[0] = 0;
		for (int i = 1; i < len; ++i)
		{
			// price[0...i] ��ཻ��һ�ε��������λ price[0...i-1] ���������͡���ǰ��������֮ǰ��������֮��Ľϴ�ֵ
			dp_left[i] = max(dp_left[i - 1], prices[i] - min_price);	
			// ������ͼ�
			min_price = min(min_price, prices[i]);			
		}

		// ��� dp_right
		int max_price = prices[len - 1];
		for (int i = len - 2; i >= 0; --i)
		{
			dp_right[i] = max(dp_right[i + 1], max_price - prices[i]);
			max_price = max(max_price, prices[i]);
		}
		
		// ����ָ�λ��Ϊ i ʱ����� profit��ȡ���ֵ
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
