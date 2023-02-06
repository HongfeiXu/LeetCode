#include "AdjListGraph.h"

void addSingleEdge(AdjListGraph& graph, int u, int v, int weight /*= 0*/)
{
	auto newNode = make_shared<AdjListNode>(v, weight);
	// the newNode is add at the beginning of this AdjList
	newNode->next = graph.array[u].head;
	graph.array[u].head = newNode;
}

void addDoubleEdge(AdjListGraph& graph, int u, int v, int weight /*= 0*/)
{
	auto newNode = make_shared<AdjListNode>(v, weight);
	// the newNode is add at the beginning of this AdjList
	newNode->next = graph.array[u].head;
	graph.array[u].head = newNode;

	auto newNode_2 = make_shared<AdjListNode>(u, weight);
	// the newNode is add at the beginning of this AdjList
	newNode_2->next = graph.array[v].head;
	graph.array[v].head = newNode_2;
}

void printGraph(AdjListGraph& graph)
{
	for (int u = 0; u < graph.V; ++u)
	{
		auto pv = graph.array[u].head;
		cout << "Adjacency list of vertex " << u << endl;
		cout << "head";
		while (pv != nullptr)
		{
			cout << " -> " << pv->dest << "(" << pv->weight << ")";
			pv = pv->next;
		}
		cout << endl;
	}
}

std::vector<int> BFS(const AdjListGraph& G, int start)
{
	assert(start < G.V && start >= 0);
	vector<int> result;
	queue<int> Q;
	unordered_set<int> visited;
	Q.push(start);
	visited.insert(start);
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		result.push_back(u);
		auto pv = G.array[u].head;
		while (pv != nullptr)
		{
			// 若顶点 v 没有被访问，则放入Q中，并标记为已访问
			if (visited.find(pv->dest) == visited.end())
			{
				Q.push(pv->dest);
				visited.insert(pv->dest);
			}
			pv = pv->next;
		}
	}
	return result;
}

void DFSUtil(const AdjListGraph& G, int start, unordered_set<int>& visited, vector<int>& result)
{
	// 记录结果，并标记为已访问
	result.push_back(start);
	visited.insert(start);
	auto pv = G.array[start].head;
	while (pv != nullptr)
	{
		// 如果节点 v 没有被访问，则对其进行深度遍历
		if (visited.find(pv->dest) == visited.end())
			DFSUtil(G, pv->dest, visited, result);
		pv = pv->next;
	}
}

std::vector<int> DFS(const AdjListGraph& G, int start)
{
	assert(start < G.V && start >= 0);
	vector<int> result;
	unordered_set<int> visited;
	DFSUtil(G, start, visited, result);
	return result;
}

int minKeyVertex(const vector<int>& key, const vector<bool>& mstSet)
{
	int min_key = INT_MAX;
	int min_key_vertex;
	for (int i = 0; i < key.size(); ++i)
	{
		if (mstSet[i] == false && key[i] <= min_key)		
		{
			min_key = key[i];
			min_key_vertex = i;
		}
	}
	return min_key_vertex;
}

void printPrimMST(const vector<int>& parent)
{
	cout << "Edges of Prim MST" << endl;
	for (int i = 0; i < parent.size(); ++i)
	{
		cout << parent[i] << " - " << i << endl;	// 输出每个节点以及其父节点所组成的边
	}
}

void primMST(const AdjListGraph& G, int start)
{
	if (G.V == 0)
		return;
	vector<int> parent(G.V);
	vector<int> key(G.V, INT_MAX);
	vector<bool> mstSet(G.V, false);		// 标记顶点是否已经加入 MST 中
	key[start] = 0;			// 以 start 为根构造 MST
	parent[start] = -1;
	for (int count = 0; count < G.V - 1; ++count)
	{
		// 寻找不在 MST 中、key 值最小的节点，加入 MST 中
		int u = minKeyVertex(key, mstSet);
		mstSet[u] = true;
		// 更新 u 的邻居节点
		auto pv = G.array[u].head;
		while (pv != nullptr)
		{
			if (mstSet[pv->dest] == false && key[pv->dest] > pv->weight)
			{
				key[pv->dest] = pv->weight;
				parent[pv->dest] = u;
			}

			pv = pv->next;
		}
	}
	printPrimMST(parent);
}

void printKruskalMST(const vector<Edge>& edges_of_MST)
{
	cout << "Edges of Kruskal MST" << endl;
	for (const auto& edge : edges_of_MST)
	{
		cout << edge.start << " - " << edge.end << endl;
	}
}

void kruskalMST(const AdjListGraph& G)
{
	auto cmp = [](const Edge& lhs, const Edge& rhs)
	{
		return lhs.weight < rhs.weight;
	};

	// 存储 MST 中的边
	vector<Edge> edges_of_MST;
	// 存储所有G的边（每条边存储了两次）
	vector<Edge> edges_of_G;
	for (int i = 0; i < G.V; ++i)
	{
		auto pv = G.array[i].head;
		while (pv != nullptr)
		{
			edges_of_G.push_back({ i, pv->dest, pv->weight });
			pv = pv->next;
		}
	}
	sort(edges_of_G.begin(), edges_of_G.end(), cmp);
	DisjointSet disjoint_set(G.V);
	for (int i = 0; i < edges_of_G.size(); ++i)
	{
		int u = edges_of_G[i].start;
		int v = edges_of_G[i].end;
		if (disjoint_set.findSet(u) != disjoint_set.findSet(v))
		{
			edges_of_MST.push_back(edges_of_G[i]);
			disjoint_set.unionSet(u, v);
		}
	}
	printKruskalMST(edges_of_MST);
}

void dijkstra(const AdjListGraph& G, int start)
{
	assert(start < G.V && start >= 0);
	vector<int> parent(G.V, -1);			// 记录每个顶点的父节点，用来输出最短路径树，只要求输出最短路径的长度，则不需要 parent
	vector<bool> sptSet(G.V, false);		// 标记顶点是否已经加入 sptSet 中
	vector<int> dist(G.V, INT_MAX);			// 每个顶点到起始顶点的距离初始为 INT_MAX
	dist[start] = 0;
	parent[start] = -1;
	// 进行 G.V - 1 次迭代即可，因为若在进行第 G.V 次迭代，对于这个最后的节点，所有相邻的节点已经被加入 SPT 中了，没有必要再进行此次访问，
	// 我们根据 G.V - 1 次迭代所更新的 parent 的信息就可以确定 SPT 
	for (int count = 0; count < G.V - 1; ++count)
	{
		int u = minDistanceVertex(dist, sptSet);
		sptSet[u] = true;
		auto pv = G.array[u].head;
		while (pv != nullptr)
		{
			// 若邻居节点 v 未被访问且距离值大于 dist[u] + pv->weight，则更新其 dist 值
			// 这里 dist[u] != INT_MAX  是保证 u 当前是可以与 MST 连通的，
			// 如果当前具有最小距离的节点 u 与 MST 不连通，则其邻居节点的 dist 值将依然为 INT_MAX
			if (sptSet[pv->dest] == false && dist[u] != INT_MAX && dist[u] + pv->weight < dist[pv->dest])
			{
				dist[pv->dest] = dist[u] + pv->weight;
				parent[pv->dest] = u;
			}
			pv = pv->next;
		}
	}
	printDijkstraSPT(parent, dist);
}

void printDijkstraSPT(const vector<int>& parent, const vector<int>& dist)
{
	cout << "Edges of Dijkstra SPT" << endl;
	for (int i = 0; i < parent.size(); ++i)
		cout << parent[i] << " -> " << i << ": " << dist[i] << endl;
}

int minDistanceVertex(const vector<int>& dist, const vector<bool>& sptSet)
{
	int min_dist = INT_MAX;
	int min_dist_vert;
	for (int i = 0; i < dist.size(); ++i)
	{
		// 寻找没有加入 SPT 中的节点中，具有最小 dist 值的节点
		// 这里采用 <= 号，是为了在当前余下节点的 dist 值均为 INT_MAX 时，返回其中的一个节点，如果为 < 号，则返回值无效
		if (dist[i] <= min_dist && sptSet[i] == false)
		{
			min_dist = dist[i];
			min_dist_vert = i;
		}
	}
	return min_dist_vert;
}



void test()
{
	AdjListGraph g(5);
	addDoubleEdge(g, 0, 1, 2);
	addDoubleEdge(g, 0, 3, 6);
	addDoubleEdge(g, 1, 2, 3);
	addDoubleEdge(g, 1, 3, 8);
	addDoubleEdge(g, 1, 4, 5);
	addDoubleEdge(g, 2, 4, 7);
	addDoubleEdge(g, 3, 4, 9);
	printGraph(g);
	cout << "BFS_result: " << endl;
	auto BFS_result = BFS(g, 2);
	copy(BFS_result.begin(), BFS_result.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << "DFS_result: " << endl;
	auto DFS_result = DFS(g, 2);
	copy(DFS_result.begin(), DFS_result.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	primMST(g, 0);

	kruskalMST(g);

	AdjListGraph g_2(6);
	addSingleEdge(g_2, 0, 1, 4);
	addSingleEdge(g_2, 0, 2, 1);
	addSingleEdge(g_2, 2, 1, 2);
	addSingleEdge(g_2, 1, 3, 1);
	addSingleEdge(g_2, 2, 3, 7);
	addSingleEdge(g_2, 4, 5, 1);

	printGraph(g_2);
	dijkstra(g_2, 0);
}


/*

Adjacency list of vertex 3
head -> 4(9) -> 1(8) -> 0(6)
Adjacency list of vertex 4
head -> 3(9) -> 2(7) -> 1(5)
BFS_result:
2 4 1 3 0
DFS_result:
2 4 3 1 0
Edges of Prim MST
-1 - 0
0 - 1
1 - 2
0 - 3
1 - 4
Edges of Kruskal MST
0 - 1
1 - 2
1 - 4
0 - 3
Adjacency list of vertex 0
head -> 2(1) -> 1(4)
Adjacency list of vertex 1
head -> 3(1)
Adjacency list of vertex 2
head -> 3(7) -> 1(2)
Adjacency list of vertex 3
head
Adjacency list of vertex 4
head -> 5(1)
Adjacency list of vertex 5
head
Edges of Dijkstra SPT
-1 -> 0: 0
2 -> 1: 3
0 -> 2: 1
1 -> 3: 4
-1 -> 4: 2147483647
-1 -> 5: 2147483647
请按任意键继续. . .

*/