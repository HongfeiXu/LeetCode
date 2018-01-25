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

ʹ��λ���㣬�����������ֵ�λ��ÿ�������ξ�ɾ��������ʣ�µľ���ֻ����һ�ε����֡�
ones ��¼������1�Ρ�4�Ρ�7��...��λ
twos ��¼������2�Ρ�5�Ρ�8��...��λ
common_bit_mask ��¼������3�ε�λ��Ȼ�󽫸�λ��Ϊ0������ ones��twos ������������Ӷ�ɾ����Щ����3�Ρ�6�Ρ�9��...��λ
���� ones �м�¼��ֻ����һ�ε�����

Time Complexity: O(n)
Auxiliary Space: O(1)

Approach_v3:

��Ȼʹ��λ���㣬����������ò�ͬ��˼·��
Let us consider the example array {5, 5, 5, 8}. The 101, 101, 101, 1000
Sum of first bits%3 = (1 + 1 + 1 + 0)%3 = 0;
Sum of second bits%3 = (0 + 0 + 0 + 0)%3 = 0;
Sum of third bits%3 = (1 + 1 + 1 + 0)%3 = 0;
Sum of fourth bits%3 = (1)%3 = 1;

Hence number which appears once is 1000

Approach_v4:
Math

Array [] : [a, a, a, b, b, b, c, c, c, d]
Mathematical Equation = ( 3*(a+b+c+d) �C (a + a + a + b + b + b + c + c + c + d) ) / 2
In more simple words: ( 3*(sum_of_array_without_duplicates) �C (sum_of_array) ) / 2

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
			int sum = 0;	// ������λ�ĵ�iλ�ϵĺ�
			int x = (1 << i);
			
			for (int j = 0; j < nums.size(); ++j)
			{
				// �� nums[j] �ĵ� i λΪ1�������� sum
				if (nums[j] & x)
					++sum;
			}
			// �� sum ���� 3 �� 1����ֻ����һ�ε������ڸ�λΪ1
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
		long sum_of_array_without_duplicates = accumulate(s.begin(), s.end(), 0L);	// ����Ϊ�˷�ֹ�д�����ͳ���int�ı�ʾ��Χ���������Ϊ long ����
		long sum_of_array = accumulate(nums.begin(), nums.end(), 0L);
		return (sum_of_array_without_duplicates * 3 - sum_of_array) / 2;
	}
};