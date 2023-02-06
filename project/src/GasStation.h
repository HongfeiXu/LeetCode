#pragma once

/*

134. Gas Station

There are N gas stations along a circular route, where the amount of gas at station i is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station (i+1). 
You begin the journey with an empty tank at one of the gas stations.

Return the starting gas station's index if you can travel around the circuit once, otherwise return -1.

Note:
The solution is guaranteed to be unique.

Approach:

Greedy
每经过一个加油站就加完加油站所有的汽油。
用 cost - gas 得到 gap 数组，表示每个加油站汽油量相对于接下来一段路程消耗汽油量所剩余的汽油。
参考Largest Sum Contiguous Subarray 问题 Kadane 算法的思想，找到正确的起始位置。
注：一个结论是，如果所有加油站的总油量不小于总耗油量，则一定存在一个正确的起始位置，可以走完整个路程。

*/

#include <vector>
#include <numeric>

using namespace std;

class Solution {
public:
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost)
	{
		int len = gas.size();
		vector<int> gap(len, 0);		// gas[i] - cost[i]
		for (int i = 0; i < len; ++i)
			gap[i] = gas[i] - cost[i];
		// 如果总的消耗大于总的汽油量，则一定不能完成循环
		if (accumulate(gap.begin(), gap.end(), 0) < 0)
			return -1;
		// 反之，则一定能完成循环，需要寻找起始位置
		int start = 0;
		while (1)
		{
			// 若第一个gap值就是负数，则跳到下一个汽油站
			int currSum = gap[start];
			if (currSum < 0)
			{
				start = (start + 1) % len;
				continue;
			}
			// 从 start+1 开始走一个循环
			for (int i = (start + 1) % len; i != start; i = (i + 1) % len)
			{
				currSum += gap[i];
				// 遇到一个跨不过去的坎（汽油不足够）
				if (currSum < 0)
				{
					start = (i + 1) % len;
					break;
				}
			}
			// 若最终 currSum >= 0，则说明从 start 处开始完成了一个循环
			if (currSum >= 0)
				return start;
		}
	}
};