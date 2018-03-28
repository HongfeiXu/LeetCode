#pragma once

/*

11. Container With Most Water

Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). 
n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). 
Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container and n is at least 2.

Container(ai, aj) = (j -i) * min(ai, aj)������ i <= j

Approach [TLE]: 
Brute Force
���������߶ε���ϣ�ȡ�����ݻ���

Time: O(n^2)
Space: O(1)

Approach_v2:

Ref: https://leetcode.com/problems/container-with-most-water/solution/
Ref: https://leetcode.com/problems/container-with-most-water/discuss/6099/yet-another-way-to-see-what-happens-in-the-on-algorithm

��Ȼ�������߶ε��ݻ����߶εľ����Լ���̵��߶εĳ��Ⱦ�����
�������µ�����

	1 8 6 2 5 4 8 3 7
	|				|
	left			right

������������ָ�룬һ��ָ��ʼ����һ��ָ���β������¼��ʱ���ݻ��������Ը��� maxarea��
���ţ����������ƶ�ָ��϶̳��ȵ�ָ�룬����Ϊ�������ƶ�ָ��ϳ����ȵ�ָ�룬���ڸ߶�δ�ı䣬��ȱ�С���ݻ�ֻ����١�����¼��ʱ���ݻ������Ը��� maxarea��
ֱ��ָ��λ���غϣ����� maxarea��

����ÿ������ֻ����һ�Σ�����ʱ�临�Ӷ�Ϊ
Time: O(n)
Space: O(1)

*/

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
	int maxArea(vector<int>& height)
	{
		int result = 0;
		int n = height.size();
		for (int i = 0; i < n; ++i)
		{
			for (int j = i + 1; j < n; ++j)
			{
				int curr_capacity = (j - i) * min(height[i], height[j]);
				result = max(curr_capacity, result);
			}
		}
		return result;
	}
};

class Solution_v2 {
public:
	int maxArea(vector<int>& height)
	{
		int result = 0;
		int left = 0, right = static_cast<int>(height.size()) - 1;
		while (left < right)
		{
			int curr_capacity = (right - left) * min(height[left], height[right]);
			result = max(result, curr_capacity);
			if (height[left] < height[right])
				++left;
			else
				--right;
		}
		return result;
	}
};


void test()
{
	Solution_v2 solu;
	vector<int> height_1 { 2,0,4 };
	cout << solu.maxArea(height_1) << endl;
	vector<int> height_2 { 1,2,3 };
	cout << solu.maxArea(height_2) << endl;
	vector<int> height_3 { };
	cout << solu.maxArea(height_3) << endl;
}