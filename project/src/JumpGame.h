#pragma once

/*

55. Jump Game

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

For example:
A = [2,3,1,1,4], return true.

A = [3,2,1,0,4], return false.

Approach:
��������������ֵΪ0��λ�ã����һ��Ԫ��֮ǰ��0��Ҫ�ܹ�Խ���������һ��Ԫ��Ϊ0������ҪԽ����
�����������У�����ֵΪ0��λ�ã���ǰ������Խ�����0����Ծ�����Ҳ������򷵻� false�����򣬼������Ѱ����һ��0��
ֱ��ȷ�����е�0�������һ��λ��֮��ģ�����Խ��Ϊֹ������ true��

���磺
2,3,1,1,4 û��0���϶��ܵ��ִ����һ��λ��
3,2,1,0,4 ��һ��0����ǰ����Խ�����0����Ծ��1-(3-2) == 0, 2-(3-1) == 0, 3-(3-0) == 0������û���ܹ��������0����Ծ������ false
0,0,0,0,4 

*/

#include <vector>

using namespace std;

class Solution {
public:
	bool canJump(vector<int>& nums)
	{
		// �Գ������һ��Ԫ�ص�����Ԫ��
		for (int i = 0; i < static_cast<int>(nums.size()) - 1; ++i)
		{
			if (nums[i] == 0)
			{
				// ��ǰѰ����û���ܹ�Խ����ǰ0����Ծλ��
				int j = i - 1;
				while (j >= 0)
				{
					if (nums[j] - (i - j) <= 0)
						--j;
					// ���ҵ�����������ǰ while ѭ��
					else
						break;
				}
				// ����� 0 �޷�Խ�������޷��������
				if (j == -1)
					return false;
			}
		}
		return true;
	}
};