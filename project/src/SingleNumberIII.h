#pragma once

/*

260. Single Number III

Given an array of numbers nums, in which exactly two elements appear 
only once and all the other elements appear exactly twice. 
Find the two elements that appear only once.

For example:

Given nums = [1, 2, 1, 3, 2, 5], return [3, 5].

Note:
The order of the result is not important. So in the above example, [5, 3] is also correct.
Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?

Approach:
unordered_map
Time: O(n)
Space: O(n)

Approach v2:
Ref: https://www.geeksforgeeks.org/find-two-non-repeating-elements-in-an-array-of-repeating-elements/
Bit Manipulation

Let us see an example.
arr[] = {2, 4, 7, 9, 2, 4}
1) Get the XOR of all the elements.
xor = 2^4^7^9^2^4 = 14 (1110)
2) Get a number which has only one set bit of the xor.
Since we can easily get the rightmost set bit, let us use it.
set_bit_no = xor & ~(xor-1) = (1110) & ~(1101) = 0010
Now set_bit_no will have only set as rightmost set bit of xor.
3) Now divide the elements in two sets and do xor of
elements in each set, and we get the non-repeating
elements 7 and 9. Please see implementation for this
step.


*/

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
	vector<int> singleNumber(vector<int>& nums)
	{
		unordered_map<int, int> count;
		for (const auto& item : nums)
			++count[item];
		vector<int> result;

		for (auto it = count.begin(); it != count.end(); ++it)
		{
			if (it->second == 1)
				result.push_back(it->first);
		}
		return result;
	}
};

class Solution_v2 {
public:
	vector<int> singleNumber(vector<int>& nums)
	{
		int xor_ = 0;
		for (const auto & item : nums)
			xor_ ^= item;
		//int rightmost_set_bit = xor_ & ~(xor_ -1);		// 110110 的 rightmost_set_bit 为 000010
		int rightmost_set_bit = xor_ & -xor_;			// 与上面等价
		int x = 0, y = 0;
		// use rightmost_set_bit divide the elements of the array in two sets 
		// – one set of elements with same bit set and other set with same bit not set.
		for (const auto & item : nums)
		{
			if (item & rightmost_set_bit)
				x ^= item;
			else
				y ^= item;
		}
		return vector<int>{x, y};
	}
};
