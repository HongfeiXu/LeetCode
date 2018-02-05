#pragma once

/*

基于图的邻接链表表示实现图的一些基本算法
BFS,DFS,Prim MST, Kruskal MST

*/

#include <vector>
#include <iostream>
#include <memory>
#include <cassert>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <iterator>

using namespace std;

//////////////////////////////////////////////////////////////////////////
// AdjListGraph
//////////////////////////////////////////////////////////////////////////

struct AdjListNode {
	int dest;
	int weight;
	shared_ptr<AdjListNode> next;			// 使用智能指针来进行动态内存分配，不会出现内存泄漏
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

//////////////////////////////////////////////////////////////////////////
// BFS and DFS
//////////////////////////////////////////////////////////////////////////

vector<int> BFS(const AdjListGraph& G, int start);

vector<int> DFS(const AdjListGraph& G, int start);
void DFSUtil(const AdjListGraph& G, int start, unordered_set<int>& visited, vector<int>& result);

//////////////////////////////////////////////////////////////////////////
// Prim and Kruskal, MST
// （对象：带权无向连通图）
//////////////////////////////////////////////////////////////////////////

void primMST(const AdjListGraph& G, int start);
int minKeyVertex(const vector<int>& key, const vector<bool>& mstSet);
void printPrimMST(const vector<int>& parent);

// 并查集
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
			parent[x] = findSet(parent[x]);
		return parent[x];
	}
	void unionSet(int x, int y)
	{
		x = findSet(x);
		y = findSet(y);
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

void kruskalMST(const AdjListGraph& G);
void printKruskalMST(const vector<Edge>& edges_of_MST);

//////////////////////////////////////////////////////////////////////////
// Dijkstra’s shortest path algorithm
//////////////////////////////////////////////////////////////////////////

void dijkstra(const AdjListGraph& G, int start);
int minDistanceVertex(const vector<int>& dist, const vector<bool>& sptSet);
void printDijkstraSPT(const vector<int>& parent, const vector<int>& dist);




//////////////////////////////////////////////////////////////////////////
// test
//////////////////////////////////////////////////////////////////////////

void test();
