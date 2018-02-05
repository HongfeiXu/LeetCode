#pragma once

/*

743. Network Delay Time

There are N network nodes, labelled 1 to N.

Given times, a list of travel times as directed edges times[i] = (u, v, w), 
where u is the source node, v is the target node, and w is the time it takes for a signal to travel from source to target.

Now, we send a signal from a certain node K. How long will it take for all nodes to receive the signal? If it is impossible, return -1.

Note:
N will be in the range [1, 100].
K will be in the range [1, N].
The length of times will be in the range [1, 6000].
All edges times[i] = (u, v, w) will have 1 <= u, v <= N and 1 <= w <= 100.

Approach:

N ���ڵ�Ĵ�Ȩ����ͼ���ҽڵ��ϵ���ڽӾ��� times ��ʾ��Ҫ��Դ��㵽���нڵ����̾�������ֵ��
����ʹ�� Dijkstra��s shortest path algorithm ������⡣

*/

#include <vector>

using namespace std;

class Solution {
public:
	int networkDelayTime(vector<vector<int>>& times, int N, int K)
	{

	}
};

