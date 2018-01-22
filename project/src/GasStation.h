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
ÿ����һ������վ�ͼ������վ���е����͡�
�� cost - gas �õ� gap ���飬��ʾÿ������վ����������ڽ�����һ��·��������������ʣ������͡�
�ο�Largest Sum Contiguous Subarray ���� Kadane �㷨��˼�룬�ҵ���ȷ����ʼλ�á�
ע��һ�������ǣ�������м���վ����������С���ܺ���������һ������һ����ȷ����ʼλ�ã�������������·�̡�

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
		// ����ܵ����Ĵ����ܵ�����������һ���������ѭ��
		if (accumulate(gap.begin(), gap.end(), 0) < 0)
			return -1;
		// ��֮����һ�������ѭ������ҪѰ����ʼλ��
		int start = 0;
		while (1)
		{
			// ����һ��gapֵ���Ǹ�������������һ������վ
			int currSum = gap[start];
			if (currSum < 0)
			{
				start = (start + 1) % len;
				continue;
			}
			// �� start+1 ��ʼ��һ��ѭ��
			for (int i = (start + 1) % len; i != start; i = (i + 1) % len)
			{
				currSum += gap[i];
				// ����һ���粻��ȥ�Ŀ������Ͳ��㹻��
				if (currSum < 0)
				{
					start = (i + 1) % len;
					break;
				}
			}
			// ������ currSum >= 0����˵���� start ����ʼ�����һ��ѭ��
			if (currSum >= 0)
				return start;
		}
	}
};