# Graph Algorithms

>Ref: https://www.geeksforgeeks.org/graph-data-structure-and-algorithms/

- Graph and its representations
- DFS and BFS
- Graph Cycle
- Topological Sorting
- Minimum Spanning Tree
- BackTracking
- Shortest Paths
- Connectivity
- Hard Problems
- Maximum Flow
- STL Implementation of Algorithms
- Misc

## 1. Graph and its representations

Graph is a data structure that consists of following two components:
1. A finite set of vertices also called as nodes.
2. A finite set of ordered pair of the form (u, v) called as edge. The pair is ordered because (u, v) is not same as (v, u) in case of directed graph(di-graph). The pair of form (u, v) indicates that there is an edge from vertex u to vertex v. The edges may contain weight/value/cost.

Following two are the most commonly used representations of graph.
1. Adjacency Matrix
2. Adjacency List

**Adjacency Matrix:**

![]()

Pros: Representation is easier to implement and follow. Removing an edge takes `O(1)` time. Queries like whether there is an edge from vertex ��u�� to vertex ��v�� are efficient and can be done `O(1)`.

Cons: Consumes more space `O(V^2)`. Even if the graph is sparse(contains less number of edges), it consumes the same space. Adding a vertex is `O(V^2)` time.

**Adjacency List:**

![]()

Pros: Saves space `O(|V|+|E|)` . In the worst case, there can be `C(V, 2)` number of edges in a graph thus consuming `O(V^2)` space. Adding a vertex is easier.

Cons: Queries like whether there is an edge from vertex u to vertex v are not efficient and can be done `O(V)`.

```c++
//////////////////////////////////////////////////////////////////////////
// AdjListGraph
//////////////////////////////////////////////////////////////////////////

struct AdjListNode {
	int dest;
	int weight;
	shared_ptr<AdjListNode> next;			// ʹ������ָ�������ж�̬�ڴ���䣬��������ڴ�й©
	AdjListNode(int dest_, int weight_ = 0) : dest(dest_), weight(weight_), next(nullptr) { }
};

struct AdjList {
	shared_ptr<AdjListNode> head;
	AdjList() : head(nullptr) { }
};

struct AdjListGraph {
	int V;
	vector<AdjList> array;
	AdjListGraph(int V_) : V(V_), array(V) { }
};

void addSingleEdge(AdjListGraph& graph, int u, int v, int weight = 0);
void addDoubleEdge(AdjListGraph& graph, int u, int v, int weight = 0);
void printGraph(AdjListGraph& graph);
```



## 2. BFS and DFS

```c++
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
			// ������ v û�б����ʣ������Q�У������Ϊ�ѷ���
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
	// ��¼����������Ϊ�ѷ���
	result.push_back(start);
	visited.insert(start);
	auto pv = G.array[start].head;
	while (pv != nullptr)
	{
		// ����ڵ� v û�б����ʣ�����������ȱ���
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
```



## 3. Minimum Spanning Tree

**What is Minimum Spanning Tree?**   
Given a **connected and undirected graph**, a spanning tree of that graph is a subgraph that is a tree and connects all the vertices together. A single graph can have many different spanning trees. A minimum spanning tree (MST) or minimum weight spanning tree for a weighted, connected and undirected graph is a spanning tree with weight less than or equal to the weight of every other spanning tree. The weight of a spanning tree is the sum of weights given to each edge of the spanning tree.

### Kruskal��s Minimum Spanning Tree Algorithm

1. Sort all the edges in non-decreasing order of their weight.
2. Pick the smallest edge. Check if it forms a cycle with the spanning tree formed so far. If cycle is not formed, include this edge. Else, discard it.
3. Repeat step#2 until there are (V-1) edges in the spanning tree.

The step#2 uses **Union-Find algorithm** to detect cycle. So we recommend to read following post as a prerequisite.

```c++
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

	// �洢 MST �еı�
	vector<Edge> edges_of_MST;
	// �洢����G�ıߣ�ÿ���ߴ洢�����Σ�
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
```



### Prim��s Minimum Spanning Tree

**How does Prim��s Algorithm Work?** Like Kruskal��s algorithm, Prim��s algorithm is also a Greedy algorithm. It starts with an empty spanning tree. The idea is to maintain two sets of vertices. The first set contains the vertices already included in the MST, the other set contains the vertices not yet included. **At every step, it considers all the edges that connect the two sets, and picks the minimum weight edge from these edges.** After picking the edge, it moves the other endpoint of the edge to the set containing MST.

**Algorithm**
1. Create a set mstSet that keeps track of vertices already included in MST.
2. Assign a key value to all vertices in the input graph. Initialize all key values as INFINITE. Assign key value as 0 for the first vertex so that it is picked first.
3. While mstSet doesn��t include all vertices   
  ---a. Pick a vertex u which is not there in mstSet and has minimum key value.   
  ---b. Include u to mstSet.   
  ---c. Update key value of all adjacent vertices of u. To update the key values, iterate through all adjacent vertices. For every adjacent vertex v, if weight of edge u-v is less than the previous key value of v, update the key value as weight of u-v.

```c++
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
		cout << parent[i] << " - " << i << endl;	// ���ÿ���ڵ��Լ��丸�ڵ�����ɵı�
	}
}

void primMST(const AdjListGraph& G, int start)
{
	if (G.V == 0)
		return;
	vector<int> parent(G.V);
	vector<int> key(G.V, INT_MAX);
	vector<bool> mstSet(G.V, false);		// ��Ƕ����Ƿ��Ѿ����� MST ��
	key[start] = 0;			// �� start Ϊ������ MST
	parent[start] = -1;
	for (int count = 0; count < G.V - 1; ++count)
	{
		// Ѱ�Ҳ��� MST �С�key ֵ��С�Ľڵ㣬���� MST ��
		int u = minKeyVertex(key, mstSet);
		mstSet[u] = true;
		// ���� u ���ھӽڵ�
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
```



## 4. Shortest Paths

### Dijkstra��s shortest path algorithm

>Ref: https://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/

Given a directed and weighted graph and a source vertex in graph, find shortest paths from source to all vertices in the given graph.   

�Ͽ�˹�����㷨ʹ���˹���������������Ȩ����ͼ�ĵ�Դ���·�����⡣

**Dijkstra��s algorithm is very similar to Prim��s algorithm for minimum spanning tree.** Like Prim��s MST, we generate a SPT (shortest path tree) with given source as root. We maintain two sets, one set contains vertices included in shortest path tree, other set includes vertices not yet included in shortest path tree. **At every step of the algorithm, we find a vertex which is in the other set (set of not yet included) and has minimum distance from source.**

**Algorithm**
1. Create a set sptSet (shortest path tree set) that keeps track of vertices included in shortest path tree, i.e., whose minimum distance from source is calculated and finalized. Initially, this set is empty.
2. Assign a distance value to all vertices in the input graph. Initialize all distance values as INFINITE. Assign distance value as 0 for the source vertex so that it is picked first.
3. While sptSet doesn��t include all vertices   
  ---a. Pick a vertex u which is not there in sptSetand has minimum distance value.   
  ---b. Include u to sptSet.   
  ---c. Update distance value of all adjacent vertices of u. To update the distance values, iterate through all adjacent vertices. For every adjacent vertex v, if sum of distance value of u (from source) and weight of edge u-v, is less than the distance value of v, then update the distance value of v.   


```c++
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
		// Ѱ��û�м��� SPT �еĽڵ��У�������С dist ֵ�Ľڵ�
		// ������� <= �ţ���Ϊ���ڵ�ǰ���½ڵ�� dist ֵ��Ϊ INT_MAX ʱ���������е�һ���ڵ㣬���Ϊ < �ţ��򷵻�ֵ��Ч
		if (dist[i] <= min_dist && sptSet[i] == false)
		{
			min_dist = dist[i];
			min_dist_vert = i;
		}
	}
	return min_dist_vert;
}

void dijkstra(const AdjListGraph& G, int start)
{
	assert(start < G.V && start >= 0);
	vector<int> parent(G.V, -1);			// ��¼ÿ������ĸ��ڵ㣬����������·������ֻҪ��������·���ĳ��ȣ�����Ҫ parent
	vector<bool> sptSet(G.V, false);		// ��Ƕ����Ƿ��Ѿ����� sptSet ��
	vector<int> dist(G.V, INT_MAX);			// ÿ�����㵽��ʼ����ľ����ʼΪ INT_MAX
	dist[start] = 0;
	parent[start] = -1;
	// ���� G.V - 1 �ε������ɣ���Ϊ���ڽ��е� G.V �ε���������������Ľڵ㣬�������ڵĽڵ��Ѿ������� SPT ���ˣ�û�б�Ҫ�ٽ��д˴η��ʣ�
	// ���Ǹ��� G.V - 1 �ε��������µ� parent ����Ϣ�Ϳ���ȷ�� SPT 
	for (int count = 0; count < G.V - 1; ++count)
	{
		int u = minDistanceVertex(dist, sptSet);
		sptSet[u] = true;
		auto pv = G.array[u].head;
		while (pv != nullptr)
		{
			// ���ھӽڵ� v δ�������Ҿ���ֵ���� dist[u] + pv->weight��������� dist ֵ
			// ���� dist[u] != INT_MAX  �Ǳ�֤ u ��ǰ�ǿ����� MST ��ͨ�ģ�
			// �����ǰ������С����Ľڵ� u �� MST ����ͨ�������ھӽڵ�� dist ֵ����ȻΪ INT_MAX
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
```



