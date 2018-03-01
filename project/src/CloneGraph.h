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




˼·���� 138. Copy List with Random Pointer �����˼·һ����

***��һ�� hash table ��¼ԭͼ�ڵ�͸���ͼ�ڵ��Ķ�Ӧ��ϵ���Է�ֹ�ظ������ڵ㡣***

������Ĳ�ͬ���ڱ���ԭͼ��Ա�linked list���������һ�㡣������BFS��DFS������ԭͼ��
�� hash table ������˼�¼��Ӧ��ϵ�⣬���м�¼ԭͼ��ÿ���ڵ��Ƿ��Ѿ���visit�Ĺ��ܡ�

Approach:
BFS

���ö��У�ÿ�α�������ͷ������е��ھӣ������ĳ���ھӻ�û�б��������Ǿʹ���һ�������ҽ�����뵽������ȥ��
����˵���������Ѿ��������������ǡ�ֻ��һ�����ձ�����ʱ�Ž�����뵽������ȥ��������������Ѿ����������Ǿ�û��Ҫ����������ˣ�
ÿ�α�����֮��Ϳ�¡����һ���������ھӣ�Ȼ��ֱ������Ϊ�գ����Ǿ�����˿�¡�Ĳ�����

Ref: http://blog.csdn.net/qq508618087/article/details/50806972
Ref: http://bangbingsyb.blogspot.com/2014/11/leetcode-clone-graph.html

Approach:
DFS

DFS���õݹ�һ�����д����BFS����������Ĵ��룮

ÿ��������ʱ���������ǲ����Ѿ����������ǵĻ��ͷ�����copy������ʹ�����Ȼ����������ȱ������ھӽ�㲢��������ھӼ�����ȥ

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
				// �����ĳ���ھӻ�û�б��������Ǿʹ���һ�������ҽ�����뵽������ȥ
				// ����˵���������Ѿ���������������ֻ��һ�����ձ�����ʱ�Ž�����뵽������ȥ������������Ѿ����������Ǿ�û��Ҫ����������ˣ�
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