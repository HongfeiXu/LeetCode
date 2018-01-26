#pragma once

/*

42. Trapping Rain Water

Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

For example,
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.

Approach:
Time Limit Exceeded
射线法
对每一个高度，做一条水平射线，找到交点，然后确定交点间的空区间，计算区间长度，加到最终的 result 上。
最后一个测试没通过 :<

Approach v2:
Ref: https://leetcode.com/problems/trapping-rain-water/solution/
Brute force
对于每一个数组的元素，该出能够盛水的量由三个数字决定，
1. 左边的最高的高度 left_max
2. 右边的最高的高度 right_max
3. 自身的高度 height[i]
盛水的量为：max(0, min(left_max, right_max) - height[i])  ####清楚这点，则问题就很好解决了
因此，关键就是就算出每个数组的元素其左右两边的最高高度


Approach v3:
Ref: https://leetcode.com/problems/trapping-rain-water/solution/
DP
使用动态规划方法加速求出每个数组的元素其左右两边的最高高度
left_max[0...n-1]，left_max[i]表示从0到i的最高高度
right_max[0...n-1]，right_max[i]表示从i到n-1的最高高度

left_max[i] = max(left_max[i-1], height[i]);
right_max[i] = max(right_max[i+1], height[i])
盛水的量为：max(0, min(left_max[i-1], right_max[i+1]) - height[i])

Approach v4:
Ref: https://leetcode.com/problems/trapping-rain-water/solution/
Stack
TODO...

*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int trap(vector<int>& height)
	{
		int len = height.size();
		if (len < 3)
			return 0;
		int result = 0;
		int max_height = height[0];
		for (int i = 1; i < len; ++i)
		{
			if (max_height < height[i])
				max_height = height[i];
		}
		for (int i = 1; i <= max_height; ++i)
		{
			for (int j = 0; j < len;)
			{
				int first = find_first(height, j, i);
				if(first == -1)
					break;
				int last = find_last(height, first + 1, i);
				if(last == -1)
					break;
				result += last - first - 1;
				j = last;
			}
		}
		return result;
	}

	// 找寻从 start 位置开始，高度达到或者超过 target 且下一个位置低于 target 的位置
	int find_first(vector<int>& height, int start, int target)
	{
		int len = height.size();
		for (int i = start; i < len-1; ++i)
		{
			if (height[i] >= target && height[i+1] < target)
				return i;
		}
		return -1;		// 未找到高度达到或超过 target 的位置
	}
	// 找寻从 start 位置开始，高度达到或者超过 target 的位置
	int find_last(vector<int>& height, int start, int target)
	{
		int len = height.size();
		for (int i = start; i < len; ++i)
		{
			if (height[i] >= target)
				return i;
		}
		return -1;		// 未找到高度达到或超过 target 的位置
	}
};

class Solution_v2 {
public:
	int trap(vector<int>& height)
	{
		int len = height.size();
		if (len < 3)
			return 0;
		int result = 0;
		for (int i = 1; i < len - 1; ++i)
		{
			int left_max = maxHeight(height, 0, i - 1);
			int right_max = maxHeight(height, i + 1, len-1);
			result += max(min(left_max, right_max) - height[i], 0);
		}
		return result;
	}

	// hight[] 中 [start...finish] 位置的最大高度
	int maxHeight(vector<int>& height, int start, int finish)
	{
		int result = 0;
		for (int i = start; i <= finish; ++i)
			result = max(result, height[i]);
		return result;
	}
};

class Solution_v3 {
public:
	int trap(vector<int>& height)
	{
		int len = height.size();
		if (len < 3)
			return 0;
		int result = 0;

		vector<int> left_max(len, 0);
		vector<int> right_max(len, 0);
		// 从左往右
		left_max[0] = height[0];
		for (int i = 1; i < len; ++i)
			left_max[i] = max(left_max[i - 1], height[i]);
		// 从右往左
		right_max[len - 1] = height[len - 1];
		for (int i = len - 2; i >= 0; --i)
			right_max[i] = max(right_max[i + 1], height[i]);
		// i == 0 或 len-1 时，无法盛水
		for (int i = 1; i < len - 1; ++i)
		{
			int lmax = left_max[i - 1];
			int rmax = right_max[i + 1];
			result += max(min(lmax, rmax) - height[i], 0);
		}
		return result;
	}
};

