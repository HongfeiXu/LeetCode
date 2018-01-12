#pragma once

/*

575. Distribute Candies

Given an integer array with even length, where different numbers in this array represent different kinds of candies. 
Each number means one candy of the corresponding kind. You need to distribute these candies equally in number to brother and sister. 
Return the maximum number of kinds of candies the sister could gain.

Example 1:
Input: candies = [1,1,2,2,3,3]
Output: 3
Explanation:
There are three different kinds of candies (1, 2 and 3), and two candies for each kind.
Optimal distribution: The sister has candies [1,2,3] and the brother has candies [1,2,3], too.
The sister has three different kinds of candies.

Example 2:
Input: candies = [1,1,2,3]
Output: 2
Explanation: For example, the sister has candies [2,3] and the brother has candies [1,1].
The sister has two different kinds of candies, the brother has only one kind of candies.

Note:
The length of the given array is in range [2, 10,000], and will be even.
The number in given array is in range [-100,000, 100,000].

Approach:
对于 N 个糖果
首先确定糖的种类数 M，
若 M >= N / 2，则妹妹能得到最多 N/2 种糖果
若 M < N / 2，则妹妹做多能得到 M 中糖果

*/

#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
	int distributeCandies(vector<int>& candies)
	{
		unordered_set<int> types;
		for_each(candies.begin(), candies.end(), [&types](int candy) { types.insert(candy); });
		return min(types.size(), candies.size() / 2);
	}
};