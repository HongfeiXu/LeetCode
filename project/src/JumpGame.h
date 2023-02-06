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
分析：不能跳到值为0的位置，最后一个元素之前的0需要能够越过。若最后一个元素为0，不需要越过。
遍历数字序列，对于值为0的位置，向前查找能越过这个0的跳跃，若找不到，则返回 false，否则，继续向后寻找下一个0，
直到确定所有的0（除最后一个位置之外的）都能越过为止，返回 true。

例如：
2,3,1,1,4 没有0，肯定能到抵达最后一个位置
3,2,1,0,4 有一个0，向前找能越过这个0的跳跃，1-(3-2) == 0, 2-(3-1) == 0, 3-(3-0) == 0，所以没有能够跳过这个0的跳跃，返回 false
0,0,0,0,4 

*/

#include <vector>

using namespace std;

class Solution {
public:
	bool canJump(vector<int>& nums)
	{
		// 对除了最后一个元素的所有元素
		for (int i = 0; i < static_cast<int>(nums.size()) - 1; ++i)
		{
			if (nums[i] == 0)
			{
				// 向前寻找有没有能够越过当前0的跳跃位置
				int j = i - 1;
				while (j >= 0)
				{
					if (nums[j] - (i - j) <= 0)
						--j;
					// 若找到，则跳出当前 while 循环
					else
						break;
				}
				// 若这个 0 无法越过，则无法跳到最后
				if (j == -1)
					return false;
			}
		}
		return true;
	}
};