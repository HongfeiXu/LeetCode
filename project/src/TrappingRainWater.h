#pragma once

/*

42. Trapping Rain Water

Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

For example,
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.

Approach:
Time Limit Exceeded
���߷�
��ÿһ���߶ȣ���һ��ˮƽ���ߣ��ҵ����㣬Ȼ��ȷ�������Ŀ����䣬�������䳤�ȣ��ӵ����յ� result �ϡ�
���һ������ûͨ�� :<

Approach v2:
Ref: https://leetcode.com/problems/trapping-rain-water/solution/
Brute force
����ÿһ�������Ԫ�أ��ó��ܹ�ʢˮ�������������־�����
1. ��ߵ���ߵĸ߶� left_max
2. �ұߵ���ߵĸ߶� right_max
3. ����ĸ߶� height[i]
ʢˮ����Ϊ��max(0, min(left_max, right_max) - height[i])  ####�����㣬������ͺܺý����
��ˣ��ؼ����Ǿ����ÿ�������Ԫ�����������ߵ���߸߶�


Approach v3:
Ref: https://leetcode.com/problems/trapping-rain-water/solution/
DP
ʹ�ö�̬�滮�����������ÿ�������Ԫ�����������ߵ���߸߶�
left_max[0...n-1]��left_max[i]��ʾ��0��i����߸߶�
right_max[0...n-1]��right_max[i]��ʾ��i��n-1����߸߶�

left_max[i] = max(left_max[i-1], height[i]);
right_max[i] = max(right_max[i+1], height[i])
ʢˮ����Ϊ��max(0, min(left_max[i-1], right_max[i+1]) - height[i])

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

	// ��Ѱ�� start λ�ÿ�ʼ���߶ȴﵽ���߳��� target ����һ��λ�õ��� target ��λ��
	int find_first(vector<int>& height, int start, int target)
	{
		int len = height.size();
		for (int i = start; i < len-1; ++i)
		{
			if (height[i] >= target && height[i+1] < target)
				return i;
		}
		return -1;		// δ�ҵ��߶ȴﵽ�򳬹� target ��λ��
	}
	// ��Ѱ�� start λ�ÿ�ʼ���߶ȴﵽ���߳��� target ��λ��
	int find_last(vector<int>& height, int start, int target)
	{
		int len = height.size();
		for (int i = start; i < len; ++i)
		{
			if (height[i] >= target)
				return i;
		}
		return -1;		// δ�ҵ��߶ȴﵽ�򳬹� target ��λ��
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

	// hight[] �� [start...finish] λ�õ����߶�
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
		// ��������
		left_max[0] = height[0];
		for (int i = 1; i < len; ++i)
			left_max[i] = max(left_max[i - 1], height[i]);
		// ��������
		right_max[len - 1] = height[len - 1];
		for (int i = len - 2; i >= 0; --i)
			right_max[i] = max(right_max[i + 1], height[i]);
		// i == 0 �� len-1 ʱ���޷�ʢˮ
		for (int i = 1; i < len - 1; ++i)
		{
			int lmax = left_max[i - 1];
			int rmax = right_max[i + 1];
			result += max(min(lmax, rmax) - height[i], 0);
		}
		return result;
	}
};

