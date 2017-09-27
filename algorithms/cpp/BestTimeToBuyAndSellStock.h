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
};