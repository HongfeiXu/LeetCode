#pragma once

/*

11. Container With Most Water

Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). 
n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). 
Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container and n is at least 2.

Container(ai, aj) = (j -i) * min(ai, aj)，其中 i <= j

Approach [TLE]: 
Brute Force
考虑所有线段的组合，取最大的容积。

Time: O(n^2)
Space: O(1)

Approach_v2:

Ref: https://leetcode.com/problems/container-with-most-water/solution/
Ref: https://leetcode.com/problems/container-with-most-water/discuss/6099/yet-another-way-to-see-what-happens-in-the-on-algorithm

显然，两个线段的容积由线段的距离以及最短的线段的长度决定。
对于如下的例子

	1 8 6 2 5 4 8 3 7
	|				|
	left			right

我们设置两个指针，一个指向开始处，一个指向结尾处，记录此时的容积，并尝试更新 maxarea。
接着，我们向内移动指向较短长度的指针，（因为若向内移动指向较长长度的指针，由于高度未改变，宽度变小，容积只会减少。）记录此时的容积，尝试更新 maxarea。
直到指针位置重合，返回 maxarea。

由于每个顶点只遍历一次，所以时间复杂度为
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