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

N 个节点的带权有向图，边信息由 times 给出，要求源结点到所有节点的最短距离的最大值。
可以从边信息构造出图的邻接矩阵表示
可以使用 Dijkstra’s shortest path algorithm 求此问题。
注意：这里节点从1开始到100，不是从0开始到99

*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	// 取出当前不在 SPT 中且具有最小 distance 的顶点
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
		// 由times所带边信息得到图的邻接矩阵表示
		vector<vector<int>> graph(N+1, vector<int>(N+1, INT_MAX));		
		for (int i = 0; i < times.size(); ++i)
			graph[times[i][0]][times[i][1]] = times[i][2];

		vector<int> dist(N+1, INT_MAX);		// 所有顶点到 K 的最短距离
		dist[K] = 0;
		vector<bool> sptSet(N+1, false);
		// 计算 dist
		for (int i = 0; i < N - 1; ++i)		// 需要进行 N-1 次迭代得到 SPT （这里不需要求出 SPT 的结构，所以没有记录 parent 信息）
		{
			int u = minDistVertex(dist, sptSet);
			sptSet[u] = true;				// 将当前未加入 SPT 中且具有最小 distance 的顶点加入 SPT
			for (int v = 1; v <= N; ++v)
			{
				if (sptSet[v] == false && graph[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
					dist[v] = dist[u] + graph[u][v];
			}
		}
		int result = 0;
		for (int i = 1; i <= N; ++i)
			result = max(result, dist[i]);
		if (result == INT_MAX)				// 存在节点无法到达（图不连通）
			return -1;
		else
			return result;
	}
};
