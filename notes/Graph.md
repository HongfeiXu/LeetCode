# Graph Algorithms

>Ref: https://www.geeksforgeeks.org/graph-data-structure-and-algorithms/

- Graph and its representations
- DFS and BFS
- Minimum Spanning Tree
- Shortest Paths
- Graph Cycle
- Topological Sorting
- BackTracking
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

![Adjaceny Matrix](https://github.com/HongfeiXu/LeetCode/blob/master/images/adjacency_matrix_representation.png?raw=true)

Pros: Representation is easier to implement and follow. Removing an edge takes `O(1)` time. Queries like whether there is an edge from vertex ��u�� to vertex ��v�� are efficient and can be done `O(1)`.

Cons: Consumes more space `O(V^2)`. Even if the graph is sparse(contains less number of edges), it consumes the same space. Adding a vertex is `O(V^2)` time.

**Adjacency List:**

![Adjaceny List](https://github.com/HongfeiXu/LeetCode/blob/master/images/adjacency_list_representation.png?raw=true)

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

ע�������ʵ���У�BFS��ʵ�ֻ�õ��� start �ڵ��ܹ���������������ڵ�Ĺ���������У�����֤��G�����ж��㡣DFS��ʵ�֣��������ѭ�������е�ǰδ�����ʵĽڵ���� DFSUtil ���� DFS_Iteartive_Util������G�����нڵ㶼�ᱻ���ʵ���

```c++
vector<int> BFS(const AdjListGraph& G, int start)
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

std::vector<int> DFS(const AdjListGraph& G)
{
	vector<int> result;
	unordered_set<int> visited;
	for (int i = 0; i < G.V; ++i)
	{
		if (visited.find(i) == visited.end())
			DFSUtil(G, i, visited, result);
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

std::vector<int> DFS_Iteartive(const AdjListGraph& G)
{
	unordered_set<int> visited;
	vector<int> result;
	for (int i = 0; i < G.V; ++i)
	{
		if (visited.find(i) == visited.end())
			DFS_Iterative_Util(G, i, visited, result);
	}
	return result;
}

void DFS_Iterative_Util(const AdjListGraph& G, int start, unordered_set<int>& visited, vector<int>& result)
{
	stack<int> S;

	S.push(start);
	while (!S.empty())
	{
		// ��ջջ��Ԫ�أ�����֮
		int u = S.top();
		S.pop();
		result.push_back(u);
		visited.insert(u);
		auto pv = G.array[u].head;
		while (pv != nullptr)
		{
			if (visited.find(pv->dest) == visited.end())
				S.push(pv->dest);
			pv = pv->next;
		}
	}
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
// ���鼯
// ���鼯
struct DisjointSet {
	int node_num;
	vector<int> parent;
	vector<int> rank;
	DisjointSet(int node_num_): node_num(node_num_)
	{
		assert(node_num_ >= 0);
		parent.assign(node_num_, 0);
		rank.assign(node_num_, 0);
		for (int i = 0; i < node_num; ++i)
			parent[i] = i;
	}
	int findSet(int x)
	{
		assert(x < node_num);
		if (x != parent[x])
			// ·��ѹ��
			parent[x] = findSet(parent[x]);
		return parent[x];
	}
	// �ϲ� x y ���ڵ���������Ϊһ��
	void unionSet(int x, int y)
	{
		x = findSet(x);
		y = findSet(y);
		// ���Ⱥϲ�
		if (rank[x] > rank[y])
			parent[y] = x;
		else if (rank[x] < rank[y])
			parent[x] = y;
		else
		{
			parent[x] = y;
			++rank[y];
		}
	}	
};

struct Edge {
	int start;
	int end;
	int weight;
};

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
  ---a. Pick a vertex u which is not there in sptSet and has minimum distance value.   
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

## 5. Graph Cycle

### I. Detect Cycle in a Directed Graph

Ref: https://www.geeksforgeeks.org/detect-cycle-in-a-graph/

![cycle](https://github.com/HongfeiXu/LeetCode/blob/master/images/cycle.png?raw=true)

**��һ**

DFS ����ͼ�нڵ㣬���Ƿ����**�����**�����������л��������޻���Ϊ���ж��Ƿ���ں���ߣ���������ͨ����¼��ǰ�ݹ�ջ�еĽڵ�ķ�ʽ�����в��������������ϸ���ͣ�

For a disconnected graph, we get the DFS forrest as output. To detect cycle, we can check for cycle in individual trees by checking back edges.

To detect a back edge, we can keep track of vertices currently in **recursion stack** of function for DFS traversal. If we reach a vertex that is already in the recursion stack, then there is a cycle in the tree. **The edge that connects current vertex to the vertex in the recursion stack is back edge.** We have used recStack[] array to keep track of vertices in the recursion stack.

Below is C++ implementation based on above idea.

```c++
// Returns true if the graph contains a cycle, else false.
// This function is a variation of DFS()
bool isCyclicDirectGraph(const AdjListGraph& G)
{
	// Mark all the vertices as not visited and not part of recursion
	// stack
	vector<bool> visited(G.V, false);
	vector<bool> recusive_stack(G.V, false);

	// Call the recursive helper function to detect cycle in different
	// DFS trees
	for (int i = 0; i < G.V; ++i)
	{
		if (isCylicUtilDirectGraph(i, G, visited, recusive_stack))
			return true;
	}
	return false;
}

// This function is a variation of DFSUytil()
bool isCylicUtilDirectGraph(int u, const AdjListGraph& G, vector<bool>& visited, vector<bool>& recusive_stack)
{
	if (!visited[u])
	{
		// Mark the current node as visited and part of recursion stack
		visited[u] = true;
		recusive_stack[u] = true;

		// Recur for all the vertices adjacent to this vertex
		auto pv = G.array[u].head;
		while (pv != nullptr)
		{
			if (!visited[pv->dest] && isCylicUtilDirectGraph(pv->dest, G, visited, recusive_stack))
				return true;
			else if (recusive_stack[pv->dest])
				return true;
			pv = pv->next;
		}
		recusive_stack[u] = false;
	}
	return false;
}
```

Time Complexity of this method is same as time complexity of DFS traversal which is O(V+E).

**����**

��ȷ�һ��ֱ��

Detect Cycle in a directed graph using colors. The solution is from CLRS book. 

**The idea is to do DFS of given graph and while doing traversal, assign one of the below three colors to every vertex.**


```
WHITE : Vertex is not processed yet.  Initially
        all vertices are WHITE.

GRAY : Vertex is being processed (DFS for this 
       vertex has started, but not finished which means
       that all descendants (ind DFS tree) of this vertex
       are not processed yet (or this vertex is in function
       call stack)

BLACK : Vertex and all its descendants are 
        processed.

While doing DFS, if we encounter an edge from current 
vertex to a GRAY vertex, then this edge is back edge 
and hence there is a cycle.
```

![cycle](https://github.com/HongfeiXu/LeetCode/blob/master/images/DFS_color.png?raw=true)


Below is C++ implementation based on above idea.

```c++
bool isCyclicDirectGraphColor(const AdjListGraph& G)
{
	// Initialize color of all vertices as WHITE
	vector<color> colors(G.V, WHITE);

	// Do a DFS traversal beginning with all
	// vertices
	for (int i = 0; i < G.V; ++i)
	{
		if (colors[i] == WHITE)
			if (isCyclicUtilDirectGraphColor(i, G, colors))
				return true;
	}
	return false;
}

bool isCyclicUtilDirectGraphColor(int u, const AdjListGraph& G, vector<color>& colors)
{
	// GRAY :  This vertex is being processed (DFS
	//         for this vertex has started, but not
	//         ended (or this vertex is in function
	//         call stack)
	colors[u] = GREY;

	// Iterate through all adjacent vertices
	auto pv = G.array[u].head;
	while (pv != nullptr)
	{
		// If v is not processed and there is a back
		// edge in subtree rooted with v
		if (colors[pv->dest] == WHITE && isCyclicUtilDirectGraphColor(pv->dest, G, colors))
			return true;
		// If there is
		else if (colors[pv->dest] == GREY)
			return true;
		pv = pv->next;
	}
	// Mark this vertex as processed
	colors[u] = BLACK;
	return false;
}
```

**����**

Ѱ�����Ϊ0�ĵ㣬��ɾ�����������亢�ӽڵ����ȣ�������ȫ���ڵ���ȶ�Ϊ0���򲻴��ڻ������򣬴��ڻ�����΢�޸����Ϊ Topological Sorting �ķ�����ע�����µĽڵ㲻һ��ȫ�ڻ��ϡ������л��Ͻڵ�u��������Ҷ�ӽڵ�v��v����Ȳ��ᱻ����0.

**�� DFS �������ð���**

```c++
bool isCyclicDirectGraphInDegree(const AdjListGraph& G)
{
	vector<int> in_degree(G.V, 0);
	for (int i = 0; i < G.V; ++i)
	{
		auto p = G.array[i].head;
		while (p != nullptr)
		{
			++in_degree[p->dest];
			p = p->next;
		}
	}

	int count = 0;
	queue<int> q;
	for (int i = 0; i < G.V; ++i)
	{
		if (in_degree[i] == 0)
			q.push(i);
	}
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		++count;
		auto pv = G.array[u].head;
		while (pv != nullptr)
		{
			--in_degree[pv->dest];
			if (in_degree[pv->dest] == 0)
				q.push(pv->dest);
			pv = pv->next;
		}
	}
	// ������ջ��нڵ����Ȳ�Ϊ0��˵�����ڻ��������޻�
	return G.V != count;
}
```

### II. Detect Cycle in an Undirected Graph

Ref: https://www.geeksforgeeks.org/union-find/

**Union-Find Algorithm** can be used to check whether an undirected graph contains cycle or not.This method assumes that graph doesn��t contain any self-loops.
We can keeps track of the subsets in a 1D array, lets call it parent[].

For each edge, make subsets using both the vertices of the edge. If both the vertices are in the same subset, a cycle is found.

```c++
bool isCycleUndirectedGraph(const AdjListGraph& G)
{
	// AdjListGraph -> AdjMatGraph -> Edges
	vector<vector<int>> AdjMatGraph(G.V, vector<int>(G.V, 0));
	for (int u = 0; u < G.V; ++u)
	{
		auto pv = G.array[u].head;
		while (pv != nullptr)
		{
			AdjMatGraph[u][pv->dest] = 1;
			pv = pv->next;
		}
	}
	vector<Edge> edges;
	for (int i = 0; i < G.V; ++i)
	{
		for (int j = i + 1; j < G.V; ++j)
		{
			if (AdjMatGraph[i][j] == 1)
				edges.push_back({ i, j, 1 });
		}
	}

	// Iterate through all edges of graph, find subset of both
	// vertices of every edge, if both subsets are same, then 
	// there is cycle in graph.
	DisjointSet disjoint_set(G.V);
	for (auto edge : edges)
	{
		int u = edge.start;
		int v = edge.end;
		if (disjoint_set.findSet(u) == disjoint_set.findSet(v))
			return true;
		else
			disjoint_set.unionSet(u, v);
	}
	return false;
}
```

## 5. Topological Sorting

Ref: https://www.geeksforgeeks.org/topological-sorting/

Topological sorting for **Directed Acyclic Graph (DAG)** is a linear ordering of vertices such that for every directed edge uv, vertex u comes before v in the ordering. Topological Sorting for a graph is not possible if the graph is not a DAG.

**��һ DFS + a temporary stack**

Algorithm to find Topological Sorting:

We can modify DFS to find Topological Sorting of a graph. In DFS, we start from a vertex, we first print it and then recursively call DFS for its adjacent vertices. In topological sorting, **we use a temporary stack**. We don��t print the vertex immediately, we first recursively call topological sorting for all its adjacent vertices, then push it to a stack. Finally, print contents of stack. **Note that a vertex is pushed to stack only when all of its adjacent vertices (and their adjacent vertices and so on) are already in stack.**

![topologicalSort](https://github.com/HongfeiXu/LeetCode/blob/master/images/topologicalSort.png?raw=true)

```c++
void topologicalSort(const AdjListGraph& G)
{
	stack<int> S;
	// Mark all the vertices as not visited
	vector<bool> visited(G.V, false);

	// Call the recursive helper function to store Topological
	// Sort starting from all vertices one by one
	for (int i = 0; i < G.V; ++i)
	{
		if (!visited[i])
			topologicalSortUtil(G, i, visited, S);
	}

	// Print contents of stack
	while (!S.empty())
	{
		cout << S.top() << " ";
		S.pop();
	}
	cout << endl;
}

void topologicalSortUtil(const AdjListGraph& G, int u, vector<bool>& visited, stack<int>& S)
{
	// Mark the current node as visited.
	visited[u] = true;

	// Recur for all the vertices adjacent to this vertex
	auto pv = G.array[u].head;
	while (pv != nullptr)
	{
		if (!visited[pv->dest])
			topologicalSortUtil(G, pv->dest, visited, S);
		pv = pv->next;
	}

	// Push current vertex to stack which stores result
	S.push(u);
}
```


**Time Complexity:** The above algorithm is simply DFS with an extra stack. So time complexity is same as DFS which is O(V+E).

**���� BFS + ���**

Ref: https://www.geeksforgeeks.org/topological-sorting-indegree-based-solution/

Algorithm:   
Steps involved in finding the topological ordering of a DAG:

Step-1: Compute in-degree (number of incoming edges) for each of the vertex present in the DAG and initialize the count of visited nodes as 0.

Step-2: Pick all the vertices with in-degree as 0 and add them into a queue (Enqueue operation)

Step-3: Remove a vertex from the queue (Dequeue operation) and then.

1. Increment count of visited nodes by 1. Add this vertex to result.
2. Decrease in-degree by 1 for all its neighboring nodes.
3. If in-degree of a neighboring nodes is reduced to zero, then add it to the queue.


Step-4: Repeat Step 3 until the queue is empty.

Step-5: If count of visited nodes is not equal to the number of nodes in the graph then the topological sort is not possible for the given graph.

**ע�������ܴ�������ͼ�а���������������ҽ� DFS �ķ������á�**

```c++
void topologicalSortInDegree(const AdjListGraph& G)
{
	vector<int> top_order;
	vector<int> in_degree(G.V, 0);
	for (int i = 0; i < G.V; ++i)
	{
		auto p = G.array[i].head;
		while (p != nullptr)
		{
			++in_degree[p->dest];
			p = p->next;
		}
	}

	int count = 0;
	queue<int> q;
	for (int i = 0; i < G.V; ++i)
	{
		if (in_degree[i] == 0)
			q.push(i);
	}
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		top_order.push_back(u);
		++count;
		auto pv = G.array[u].head;
		while (pv != nullptr)
		{
			--in_degree[pv->dest];
			if (in_degree[pv->dest] == 0)
				q.push(pv->dest);
			pv = pv->next;
		}
	}

	// Check if there was a cycle
	if (count != G.V)
	{
		cout << "There exists a cycle in the graph\n" << endl;
		return;
	}

	for (auto i : top_order)
		cout << i << " ";
	cout << endl;
}
```

## 6. Hard Problems

### a. Graph Coloring

Ref: https://www.geeksforgeeks.org/graph-coloring-applications/

Graph coloring problem is to assign colors to certain elements of a graph subject to certain constraints.

**Vertex coloring** is the most common graph coloring problem. The problem is, given m colors, find a way of coloring the vertices of a graph such that no two adjacent vertices are colored using same color. The other graph coloring problems like Edge Coloring (No vertex is incident to two edges of same color) and Face Coloring (Geographical Map Coloring) can be transformed into vertex coloring.

**Chromatic Number:** The smallest number of colors needed to color a graph G is called its chromatic number. For example, the following can be colored minimum 3 colors.

![GraphColoring](https://github.com/HongfeiXu/LeetCode/blob/master/images/GraphColoring.png?raw=true)

>The problem to find chromatic number of a given graph is NP Complete.

#### Applications of Graph Coloring:

1. Making Schedule or Time Table
2. Bipartite Graphs. We can check if a graph is Bipartite or not by coloring the graph using two colors. If a given graph is 2-colorable, then it is Bipartite, otherwise not. 
3. Map Coloring
4. ...

#### Basic Greedy Coloring Algorithm

Unfortunately, there is no efficient algorithm available for coloring a graph with minimum number of colors as the problem is a known NP Complete problem. There are approximate algorithms to solve the problem though. Following is the basic Greedy Algorithm to assign colors. **It doesn��t guarantee to use minimum colors, but it guarantees an upper bound on the number of colors. The basic algorithm never uses more than d+1 colors where d is the maximum degree of a vertex in the given graph.**

```
1. Color first vertex with first color.
2. Do following for remaining V-1 vertices.
��.. a) Consider the currently picked vertex and color it with the
lowest numbered color that has not been used on any previously
colored vertices adjacent to it. If all previously used colors
appear on vertices adjacent to v, assign a new color to it.
```
 
 ```c++
 std::vector<int> greedyColoring(const AdjListGraph& G)
{
	vector<int> result(G.V, -1);
	vector<bool> avaliable(G.V, true);  // ��¼��ɫi�Ƿ�û�б���ǰ�ڵ�����ڽڵ�ʹ��

	result[0] = 0;		// ���ڵ�0��һ����ɫ0
	// �������µ� G.V - 1 ���ڵ�
	for (int u = 1; u < G.V; ++u)
	{
		auto pv = G.array[u].head;
		while (pv != nullptr)
		{
			// �� pv->dest ����ɫ��������ɫ�� avaliable �б��Ϊ�޷�ʹ��
			if (result[pv->dest] != -1)
				avaliable[result[pv->dest]] = false;
			pv = pv->next;
		}
		// �� avaliable  ���ҳ���һ�����Ա�ʹ�õ���ɫ���� u
		for (int i = 0; i < avaliable.size(); ++i)
		{
			if (avaliable[i])
			{
				result[u] = i;
				avaliable.assign(G.V, true);
				break;
			}
		}
	}

	return result;
}
 ```

 #### Check whether a given graph is Bipartite or not

 >�ж�һ������ͼ�Ƿ�Ϊ����ͼ�� ���жϴ�����ͼ���� 2-colorable �ġ� 
 >Ref: https://www.geeksforgeeks.org/bipartite-graph/
 >Ref: https://www.geeksforgeeks.org/backttracking-set-5-m-coloring-problem/

 A bipartite graph is possible if the graph coloring is possible using two colors such that vertices in a set are colored with the same color. 

 ![bipartite_graph](https://github.com/HongfeiXu/LeetCode/blob/master/images/bipartitegraph-1.jpg?raw=true)

** ��һ��BFS**

 ```
 Following is a simple algorithm to find out whether a given graph is Birpartite or not using Breadth First Search (BFS).
1. Assign RED color to the source vertex (putting into set U).
2. Color all the neighbors with BLUE color (putting into set V).
3. Color all neighbor��s neighbor with RED color (putting into set U).
4. This way, assign color to all vertices such that it satisfies all the constraints of m way coloring problem where m = 2.
5. While assigning colors, if we find a neighbor which is colored with same color as current vertex, then the graph cannot be colored with 2 vertices (or graph is not Bipartite)
 ```

 ```c++
 bool isBipartite(vector<vector<int>>& g)
{
	int n = g.size();
	// Create a color vector to store colors assigned to all vertices.
	// -1: no color, 1: first color, 0: second color.
	vector<int> color_vec(n, -1);
	for (int i = 0; i < n; ++i)
	{
		if (color_vec[i] == -1)
		{
			if (!isBipartiteAux(g, i, color_vec))
				return false;
		}
	}
	return true;
}

bool isBipartiteAux(vector<vector<int>>& g, int start, vector<int>& color_vec)
{
	int n = g.size();
	// Assign first color to source
	color_vec[start] = 1;
	queue<int> Q;
	Q.push(start);
	while (!Q.empty())
	{
		// Dequeue a vertex from queue
		int u = Q.front();
		Q.pop();

		// Return false if there is a self-loop
		if (g[u][u] == 1)
			return false;

		// Find all non-colored adjacent vertices
		for (int v = 0; v < n; ++v)
		{
			// v is not colored, assign alternate color to v
			if (g[u][v] == 1 && color_vec[v] == -1)
				color_vec[v] = 1 - color_vec[u];
			// v is colored with same color as u, return false
			else if (g[u][v] == 1 && color_vec[v] == color_vec[u])
				return false;
		}
	}
	return true;
}

void test()
{
	vector<vector<int>> g = {
		{0,1,0,1},
		{1,0,1,0 },
		{0,1,0,1 },
		{1,0,1,0 }
	};
	cout << boolalpha << isBipartite(g) << endl;
}
 ```

**Time Complexity** of the above approach is same as that Breadth First Search. In above implementation is O(V^2) where V is number of vertices. If graph is represented using adjacency list, then the complexity becomes O(V+E).

**������DFS**

TODO

**������Backtracking algorithm m coloring problem**

TODO


#### A* search algorthm

>Ref: https://blog.csdn.net/hitwhylz/article/details/23089415
>Ref: https://zh.wikipedia.org/wiki/A*%E6%90%9C%E5%AF%BB%E7%AE%97%E6%B3%95

A*�����㷨���׳�A���㷨������һ����ͼ��ƽ���ϣ��ж���ڵ��·����������ͨ���ɱ����㷨����������Ϸ�е�NPC���ƶ����㣬��������Ϸ��BOT���ƶ������ϡ�

���㷨�ۺ���Best-First Search��Dijkstra�㷨���ŵ㣺�ڽ�������ʽ��������㷨Ч�ʵ�ͬʱ�����Ա�֤�ҵ�һ������·��������������������

�ڴ��㷨�У������`g(n)`��ʾ����㵽���ⶥ��`n`��ʵ�ʾ��룬`h(n)`��ʾ���ⶥ��`n`��Ŀ�궥��Ĺ�����루���������õ����������Ĳ�ͬ���仯������ôA*�㷨�Ĺ��㺯��Ϊ��

`f(n) = g(n) + h(n)`

�����ʽ��ѭ�������ԣ�

1. ���`g(n)`Ϊ0����ֻ�������ⶥ��n��Ŀ�����������`h(n)`������������㵽����`n`�ľ��룬���㷨ת��Ϊʹ��̰�Ĳ��Ե�Best-First Search���ٶ���죬�����ܵò������Ž⣻
2. ���`h(n)`������ʵ�ʵ�Ŀ�궥��ľ��룬��һ������������Ž⣬����`h(n)`ԽС����Ҫ����Ľڵ�Խ�࣬�㷨Ч��Խ�ͣ����������������С���ŷ����þ��롢�����پ��롢�б�ѩ����룻
3. ���`h(n)`Ϊ0����ֻ�������㵽���ⶥ��`n`�����·��`g(n)`�����������κ���������`h(n)`����ת��Ϊ��Դ���·�����⣬��Dijkstra�㷨����ʱ��Ҫ�������Ķ��㣻
4. ���`h(n)`����ʵ�ʵ�Ŀ�궥��ľ��룬����֤���ҵ����·�������ٶȱȽϿ졣

```c
function A*(start, goal)
    // The set of nodes already evaluated
    closedSet := {}

    // The set of currently discovered nodes that are not evaluated yet.
    // Initially, only the start node is known.
    openSet := {start}

    // For each node, which node it can most efficiently be reached from.
    // If a node can be reached from many nodes, cameFrom will eventually contain the
    // most efficient previous step.
    cameFrom := an empty map

    // For each node, the cost of getting from the start node to that node.
    gScore := map with default value of Infinity

    // The cost of going from start to start is zero.
    gScore[start] := 0

    // For each node, the total cost of getting from the start node to the goal
    // by passing by that node. That value is partly known, partly heuristic.
    fScore := map with default value of Infinity

    // For the first node, that value is completely heuristic.
    fScore[start] := heuristic_cost_estimate(start, goal)

    while openSet is not empty
        current := the node in openSet having the lowest fScore[] value
        if current = goal
            return reconstruct_path(cameFrom, current)

        openSet.Remove(current)
        closedSet.Add(current)

        for each neighbor of current
            if neighbor in closedSet
                continue		// Ignore the neighbor which is already evaluated.

            if neighbor not in openSet	// Discover a new node
                openSet.Add(neighbor)
            
            // The distance from start to a neighbor
            //the "dist_between" function may vary as per the solution requirements.
            tentative_gScore := gScore[current] + dist_between(current, neighbor)
            if tentative_gScore >= gScore[neighbor]
                continue		// This is not a better path.

            // This path is the best until now. Record it!
            cameFrom[neighbor] := current
            gScore[neighbor] := tentative_gScore
            fScore[neighbor] := gScore[neighbor] + heuristic_cost_estimate(neighbor, goal) 

    return failure

function reconstruct_path(cameFrom, current)
    total_path := [current]
    while current in cameFrom.Keys:
        current := cameFrom[current]
        total_path.append(current)
    return total_path
```

C++ʵ�����£�

```c++
#pragma once

/*

Just Implement A* Search Algorithm!

*/

#include <set>
#include <utility>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <unordered_set>
#include <cmath>

using namespace std;

// ����ͼ�е�ÿ���ڵ㣬�ؼ���Ϊ pos������
class Node {
public:
	pair<int, int> parent_pos;
	double g;
	double h;
	double f;
	Node() : parent_pos({ -1,-1}), g(FLT_MAX), h(FLT_MAX), f(FLT_MAX)
	{
	}
};

bool isInvalid(const vector<vector<int>>& grid, const pair<int, int>& pos)
{
	if (pos.first < 0 || pos.second < 0 || pos.first >= grid.size() || pos.second >= grid[0].size())
		return true;
	else
		return false;
}

bool isBlocked(const vector<vector<int>>& grid, const pair<int, int>& pos)
{
	return grid[pos.first][pos.second] == 0;
}

bool isDestination(const pair<int, int>& pos, const pair<int, int>& des)
{
	return pos == des;
}

// �������������Ϊŷ����þ���Euclidean Distance
// TODO: ���������پ��룬�б�ѩ�����
double calculateHValue(const pair<int, int>& curr, const pair<int, int>& des)
{
	return sqrt((curr.first - des.first)*(curr.first - des.first) + (curr.second - des.second) * (curr.second - des.second));
}

// �� des ��ǰ���� parent_pos ȷ��·����ֱ������ src ֹͣ
void reconstructPath(const vector<vector<Node>>& cells, const pair<int, int>& src, const pair<int, int>& des)
{
	vector<pair<int, int>> path;
	
	pair<int, int> temp = des;
	while (temp != src)
	{
		path.push_back(temp);
		temp = cells[temp.first][temp.second].parent_pos;
	}
	path.push_back(src);
	for (auto it = path.rbegin(); it != path.rend(); ++it)
	{
		if (it != path.rend() - 1)
			cout << "(" << it->first << ", " << it->second << ")->";
		else
			cout << "(" << it->first << ", " << it->second << ")";
	}
	cout << endl;
}

// Ѱ���ھӽڵ㣬�������� block �Լ��Ƿ���λ�ã�����grid��λ�ã���
// ���⣬��������·����ǽͨ�������ŶԽ���ͨ����
// ���������� neighbor_nodes
void calculateNeighborNodes(const vector<vector<int>>& grid, const pair<int, int>& curr, vector<pair<int, int>>& neighbor_nodes)
{
	// ����8������ĺ�ѡ�ھӽڵ�
	vector<pair<int, int>> candidates(8, { 0,0 });
	candidates[0] = { curr.first - 1, curr.second };
	candidates[1] = { curr.first + 1, curr.second };
	candidates[2] = { curr.first, curr.second - 1 };
	candidates[3] = { curr.first, curr.second + 1 };
	candidates[4] = { curr.first - 1, curr.second - 1 };
	candidates[5] = { curr.first - 1, curr.second + 1 };
	candidates[6] = { curr.first + 1, curr.second - 1 };
	candidates[7] = { curr.first + 1, curr.second + 1 };
	for (int i = 0; i < 8; ++i)
	{
		// ע�⣬Ҫ���ж��Ƿ�Ϸ���Ȼ�����ж��Ƿ� block
		if(isInvalid(grid, candidates[i]) ||isBlocked(grid, candidates[i]))
			continue;
		neighbor_nodes.push_back(candidates[i]);
	}
}

// ���� curr �ڵ� ���ھӽڵ�֮��ľ��룬�Խ��߷�����ھӾ���Ϊ 1.4������Ϊ1.0
double distanceBetween(const pair<int, int>& curr, const pair<int, int>& neighbor)
{
	if (abs(curr.first - neighbor.first) == 1 && abs(curr.second - neighbor.second) == 1)
		return 1.4;
	else
		return 1.0;
}

void aStarSearch(const vector<vector<int>>& grid, const pair<int, int>& src, const pair<int, int>& des)
{
	if(grid.empty() || grid[0].empty())
	{
		cout << "grid invalid" << endl;
		return;
	}
	if (isInvalid(grid, src) || isInvalid(grid, des))
	{
		cout << "src or des invalid" << endl;
		return;
	}
	if (isBlocked(grid, src) || isBlocked(grid, des))
	{
		cout << "src or des blocked" << endl;
		return;
	}

	int m = grid.size(), n = grid[0].size();

	// �洢��ǰ�Ѿ����ֵ�û�������Ľڵ㣬���� f ֵ �ͽڵ��� grid �е�λ��
	set<pair<double, pair<int, int>>> open_set;
	// �洢�Ѿ��������Ľڵ�
	set<pair<int, int>> closed_set;
	// �洢���нڵ����Ϣ�������ڵ�ĸ��ڵ�λ�ã��ڵ��g,h,fֵ��
	// Ĭ�Ͻڵ��g,f,hֵ��Ϊ FLT_MAX
	vector<vector<Node>> cells(m, vector<Node>(n));

	cells[src.first][src.second].g = 0;
	cells[src.first][src.second].h = calculateHValue(src, des);
	cells[src.first][src.second].f = cells[src.first][src.second].g + cells[src.first][src.second].h;
	open_set.insert({ cells[src.first][src.second].f, src });
	while (!open_set.empty())
	{
		pair<int, int> curr_pos = (*open_set.begin()).second;
		// �����ж�
		if (curr_pos == des)
		{
			cout << "Reconstruct path: " << endl;
			reconstructPath(cells, src, des);
			return;
		}
		open_set.erase(open_set.begin());
		closed_set.insert(curr_pos);

		vector<pair<int, int>> neighbor_nodes;
		calculateNeighborNodes(grid, curr_pos, neighbor_nodes);
		for (const auto& neighbor : neighbor_nodes)
		{
			if (closed_set.find(neighbor) != closed_set.end())
				continue;
			// neighbor ���� open_set �У�fֵδ�����£�
			if (cells[neighbor.first][neighbor.second].f == FLT_MAX)
			{
				cells[neighbor.first][neighbor.second].parent_pos = curr_pos;
				cells[neighbor.first][neighbor.second].g = cells[curr_pos.first][curr_pos.second].g + distanceBetween(curr_pos, neighbor);
				cells[neighbor.first][neighbor.second].h = calculateHValue(neighbor, des);
				cells[neighbor.first][neighbor.second].f = cells[neighbor.first][neighbor.second].g + cells[neighbor.first][neighbor.second].h;
				// �� neighbor ���� open_set ��
				open_set.insert({ cells[neighbor.first][neighbor.second].f, neighbor });
			}
			// neighbor �� open_set ��
			else
			{
				double tentative_g = cells[curr_pos.first][curr_pos.second].g + distanceBetween(curr_pos, neighbor);
				// �����curr��neighor�Ⱦ��и�С��gֵ������� neighbor �ĸ��ڵ㣬�Լ� g,h,f ֵ
				if (tentative_g < cells[neighbor.first][neighbor.second].g)
				{
					cells[neighbor.first][neighbor.second].parent_pos = curr_pos;
					cells[neighbor.first][neighbor.second].g = tentative_g;
					cells[neighbor.first][neighbor.second].h = calculateHValue(neighbor, des);
					cells[neighbor.first][neighbor.second].f = cells[neighbor.first][neighbor.second].g + cells[neighbor.first][neighbor.second].h;
				}
			}
		}
	}
	cout << "Rescontruct path failed!" << endl;
}

void test()
{
	/* Description of the Grid-
	1--> The cell is not blocked
	0--> The cell is blocked    */
	vector<vector<int>> grid = 
	{
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
		{ 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
		{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
		{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
		{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } 
	};

	aStarSearch(grid, { 8, 0 }, { 0 ,0 });
}

```