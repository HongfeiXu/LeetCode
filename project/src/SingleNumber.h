#pragma once

/*

136. Single Number

Given an array of integers, every element appears twice except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

Approach:

����һ�� unordered_map
key: nums[i]
value: nums[i] ���ֵĴ���

Time:O(n)
Space:O(n)

Approach_v2:
Math
2 * (a+b+c) - (a+a+b+b+c) = c

Approach_v3:
Bit Manipulation

0^n = n
n^n = 0
���⣺������㽻���ɺͽ����

ref: https://leetcode.com/problems/single-number/solution/


*/

#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<numeric>
#include<functional>

using namespace std;

class Solution {
public:
	int singleNumber(vector<int>& nums)
	{
		unordered_map<int, int> um;
		for (int i = 0; i < nums.size(); ++i)
		{
			if (um[nums[i]] == 1)	// �������Ѿ����ֹ�һ�Σ����ٴγ���ʱ�� unordered_map ��ɾ��
				um.erase(nums[i]);
			else					// ���������ֵ�һ�γ��֣��� value ��Ϊ1
				um[nums[i]] = 1;
		}
		return um.begin()->first;	// ��� um ��ֻʣ���Ǹ����ֽ�һ�ε�����
	}
};

class Solution_v2 {
public:
	int singleNumber(vector<int>& nums)
	{
		unordered_set<int> unique_numbers;
		for (int i = 0; i < nums.size(); ++i)
			unique_numbers.insert(nums[i]);

		return 2 * accumulate(unique_numbers.begin(), unique_numbers.end(), 0) - accumulate(nums.begin(), nums.end(), 0);
	}
};



class Solution_v3 {
public:
	int singleNumber(vector<int>& nums)
	{
		//return accumulate(nums.begin(), nums.end(), 0, [](int a, int b) { return a ^ b; });
		return accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
	}
};
