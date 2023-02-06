#pragma once

/*

133. Clone Graph

Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.

OJ's undirected graph serialization:
Nodes are labeled uniquely.

We use # as a separator for each node, and , as a separator for node label and each neighbor of the node.
As an example, consider the serialized graph {0,1,2#1,2#2,2}.

The graph has a total of three nodes, and therefore contains three parts as separated by #.

1. First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
2. Second node is labeled as 1. Connect node 1 to node 2.
3. Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self-cycle.

Visually, the graph looks like the following:

       1
      / \
     /   \
    0 --- 2
         / \
         \_/




思路：和 138. Copy List with Random Pointer 那题的思路一样。

***用一个 hash table 记录原图节点和复制图节点间的对应关系，以防止重复建立节点。***

和那题的不同在于遍历原图相对比linked list的情况复杂一点。可以用BFS或DFS来遍历原图。
而 hash table 本身除了记录对应关系外，还有记录原图中每个节点是否已经被visit的功能。

Approach:
BFS

利用队列，每次遍历队列头结点所有的邻居，如果其某个邻居还没有被创建，那就创建一个，并且将其加入到队列中去．
否则说明这个结点已经被创建，而我们“只在一个结点刚被创建时才将其加入到队列中去”，因此这个结点已经被创建我们就没必要将其入队列了．
每次遍历完之后就克隆好了一个结点和其邻居．然后直到队列为空，我们就完成了克隆的操作．

Ref: http://blog.csdn.net/qq508618087/article/details/50806972
Ref: http://bangbingsyb.blogspot.com/2014/11/leetcode-clone-graph.html

Approach:
DFS

DFS利用递归一般可以写出比BFS更优雅整洁的代码．

每次搜索的时候看这个结点是不是已经被创建，是的话就返回其copy，否则就创建，然后再依次深度遍历其邻居结点并将其加入邻居集合中去

*/

#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// Definition for undirected graph.
struct UndirectedGraphNode {
	int label;
	vector<UndirectedGraphNode *> neighbors;
	UndirectedGraphNode(int x) : label(x) { };
};
class Solution {
public:
	UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node)
	{
		if (node == nullptr)
			return nullptr;
		unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> hash_table;
		UndirectedGraphNode* p1 = node;
		UndirectedGraphNode* p2 = new UndirectedGraphNode(p1->label);
		hash_table[p1] = p2;
		queue<UndirectedGraphNode*> q;
		q.push(p1);
		while (!q.empty())
		{
			p1 = q.front();
			p2 = hash_table[p1];
			q.pop();
			for (auto neighbor : p1->neighbors)
			{
				// 如果其某个邻居还没有被创建，那就创建一个，并且将其加入到队列中去
				// 否则说明这个结点已经被创建，而我们只在一个结点刚被创建时才将其加入到队列中去，因此这个结点已经被创建我们就没必要将其入队列了．
				if (hash_table.find(neighbor) == hash_table.end())
				{
					hash_table[neighbor] = new UndirectedGraphNode(neighbor->label);
					q.push(neighbor);
				}
				p2->neighbors.push_back(hash_table[neighbor]);
			}
		}
		return hash_table[node];
	}
};

class Solution_v2 {
public:
	UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node)
	{
		if (node == nullptr)
			return nullptr;
		unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> hash_table;
		return dfs(node, hash_table);
	}

	UndirectedGraphNode* dfs(UndirectedGraphNode* node, unordered_map<UndirectedGraphNode*, UndirectedGraphNode*>& hash_table)
	{
		if (hash_table.find(node) != hash_table.end())
			return hash_table[node];
		hash_table[node] = new UndirectedGraphNode(node->label);
		for (auto neighbor : node->neighbors)
			hash_table[node]->neighbors.push_back(dfs(neighbor, hash_table));
		return hash_table[node];
	}
};