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

N ���ڵ�Ĵ�Ȩ����ͼ������Ϣ�� times ������Ҫ��Դ��㵽���нڵ����̾�������ֵ��
���Դӱ���Ϣ�����ͼ���ڽӾ����ʾ
����ʹ�� Dijkstra��s shortest path algorithm ������⡣
ע�⣺����ڵ��1��ʼ��100�����Ǵ�0��ʼ��99

*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	// ȡ����ǰ���� SPT ���Ҿ�����С distance �Ķ���
	int minDistVertex(const vector<int>& dist, const vector<bool>& sptSet)
	{
		int min_dist = INT_MAX;
		int min_dist_vertex;
		for (int i = 1; i < dist.size(); ++i)
		{
			if (sptSet[i] == false && dist[i] <= min_dist)
			{
				min_dist = dist[i];
				min_dist_vertex = i;
			}
		}
		return min_dist_vertex;
	}

	int networkDelayTime(vector<vector<int>>& times, int N, int K)
	{
		// ��times��������Ϣ�õ�ͼ���ڽӾ����ʾ
		vector<vector<int>> graph(N+1, vector<int>(N+1, INT_MAX));		
		for (int i = 0; i < times.size(); ++i)
			graph[times[i][0]][times[i][1]] = times[i][2];

		vector<int> dist(N+1, INT_MAX);		// ���ж��㵽 K ����̾���
		dist[K] = 0;
		vector<bool> sptSet(N+1, false);
		// ���� dist
		for (int i = 0; i < N - 1; ++i)		// ��Ҫ���� N-1 �ε����õ� SPT �����ﲻ��Ҫ��� SPT �Ľṹ������û�м�¼ parent ��Ϣ��
		{
			int u = minDistVertex(dist, sptSet);
			sptSet[u] = true;				// ����ǰδ���� SPT ���Ҿ�����С distance �Ķ������ SPT
			for (int v = 1; v <= N; ++v)
			{
				if (sptSet[v] == false && graph[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
					dist[v] = dist[u] + graph[u][v];
			}
		}
		int result = 0;
		for (int i = 1; i <= N; ++i)
			result = max(result, dist[i]);
		if (result == INT_MAX)				// ���ڽڵ��޷����ͼ����ͨ��
			return -1;
		else
			return result;
	}
};
