#pragma once

/*

137. Single Number II

Given an array of integers, every element appears three times except for one, which appears exactly once. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

Approach:
Use unorderd_map
it has the worst case time complexity of O(n), but requires extra space.

Approach_v2:
Ref: https://www.geeksforgeeks.org/find-the-element-that-appears-once/

使用位运算，对于所有数字的位，每出现三次就删除，最终剩下的就是只出现一次的数字。
ones 记录出现了1次、4次、7次...的位
twos 记录出现了2次、5次、8次...的位
common_bit_mask 记录出现了3次的位，然后将改位设为0，并与 ones、twos 进行与操作，从而删除那些出现3次、6次、9次...的位
最终 ones 中记录了只出现一次的数字

Time Complexity: O(n)
Auxiliary Space: O(1)

Approach_v3:

依然使用位运算，但这次我们用不同的思路：
Let us consider the example array {5, 5, 5, 8}. The 101, 101, 101, 1000
Sum of first bits%3 = (1 + 1 + 1 + 0)%3 = 0;
Sum of second bits%3 = (0 + 0 + 0 + 0)%3 = 0;
Sum of third bits%3 = (1 + 1 + 1 + 0)%3 = 0;
Sum of fourth bits%3 = (1)%3 = 1;

Hence number which appears once is 1000

Approach_v4:
Math

Array [] : [a, a, a, b, b, b, c, c, c, d]
Mathematical Equation = ( 3*(a+b+c+d) – (a + a + a + b + b + b + c + c + c + d) ) / 2
In more simple words: ( 3*(sum_of_array_without_duplicates) – (sum_of_array) ) / 2

*/

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <numeric>

using namespace std;

class Solution {
public:
	int singleNumber(vector<int>& nums)
	{
		unordered_map<int, int> um;
		for (const auto& item : nums)
			++um[item];
		for (auto it = um.begin(); it != um.end(); ++it)
		{
			if (it->second == 1)
				return it->first;
		}
	}
};

class Solution_v2 {
public:
	int singleNumber(vector<int>& nums)
	{
		int ones = 0;
		int twos = 0;
		int common_bit_mask;

		for (const auto & elem : nums)
		{
			twos |= ones & elem;
			ones ^= elem;
			common_bit_mask = ~(ones & twos);
			ones &= common_bit_mask;
			twos &= common_bit_mask;
		}
		return ones;
	}
};

class Solution_v3 {
public:
	int singleNumber(vector<int>& nums)
	{
		int result = 0;
		for (int i = 0; i < sizeof(int) * 8; ++i)
		{
			int sum = 0;	// 二进制位的第i位上的和
			int x = (1 << i);
			
			for (int j = 0; j < nums.size(); ++j)
			{
				// 若 nums[j] 的第 i 位为1，则增加 sum
				if (nums[j] & x)
					++sum;
			}
			// 若 sum 除以 3 余 1，则只出现一次的数字在该位为1
			if (sum % 3 == 1)
			{
				result |= x;
			}
		}
		return result;
	}
};

class Solution_v4 {
public:
	int singleNumber(vector<int>& nums)
	{
		unordered_set<int> s;
		for (const auto & i : nums)
			s.insert(i);
		long sum_of_array_without_duplicates = accumulate(s.begin(), s.end(), 0L);	// 这里为了防止有大数求和超过int的表示范围，将结果存为 long 类型
		long sum_of_array = accumulate(nums.begin(), nums.end(), 0L);
		return (sum_of_array_without_duplicates * 3 - sum_of_array) / 2;
	}
};