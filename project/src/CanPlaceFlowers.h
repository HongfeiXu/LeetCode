#pragma once

/*

605. Can Place Flowers

Related Topics: Array

Suppose you have a long flowerbed in which some of the plots are planted and some are not. 
However, flowers cannot be planted in adjacent plots - they would compete for water and both would die.
Given a flowerbed (represented as an array containing 0 and 1, where 0 means empty and 1 means not empty), 
and a number n, return if n new flowers can be planted in it without violating the no-adjacent-flowers rule.

Example 1:
Input: flowerbed = [1,0,0,0,1], n = 1
Output: True
Example 2:
Input: flowerbed = [1,0,0,0,1], n = 2
Output: False
Note:
The input array won't violate no-adjacent-flowers rule.
The input array size is in the range of [1, 20000].
n is a non-negative integer which won't exceed the input array size.

Approach:

Consider 0000
Consider 00001
consider 10000
Consider 100001
we get canPlaceFlowers(int consecutiveZero, bool startWithOne, bool endWithOne)
we iterate through flowerbed, for each consecutiveZeros, we get the canPlanceFlowers, and add to sum
if sum >= n return true

and we should take care of some special case like n=0

Time O(n)
extral Space O(1)

*/

#include <vector>
#include <cmath>

using namespace std;

class Solution {
	int canPlaceFlowers(int consecutiveZero, bool startWithOne, bool endWithOne)
	{
		if (startWithOne)
			consecutiveZero--;
		if (endWithOne)
			consecutiveZero--;
		return (consecutiveZero + 1) / 2;
	}

public:
	bool canPlaceFlowers(vector<int>& flowerbed, int n)
	{
		// special case, [111] 0
		if (n == 0)
			return true;

		int sum = 0;		// m new flowers can be planted in the flowerbed
		int consecutiveZeros = 0;	// current consecutiveZeros

		for (unsigned i = 0; i < flowerbed.size(); i++)
		{
			bool startWithOne = true;
			bool endWithOne = true;
			if (flowerbed[i] == 0)
			{
				if (i == 0)
					startWithOne = false;
				while (i < flowerbed.size() && flowerbed[i] == 0)
				{
					consecutiveZeros++;
					i++;
				}
				if (i == flowerbed.size())
					endWithOne = false;

				sum += canPlaceFlowers(consecutiveZeros, startWithOne, endWithOne);
				consecutiveZeros = 0;
				if (sum >= n)
					return true;
			}
		}
		return false;
	}
};
