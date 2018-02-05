#pragma once

/*

103. Binary Tree Zigzag Level Order Traversal

Given a binary tree, return the zigzag level order traversal of its nodes' values. 
(ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
return its zigzag level order traversal as:
[
  [3],
  [20,9],
  [15,7]
]

Approach:
BFS

Approach v2:
DFS

*/

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) { }
};

class Solution {
public:
	vector<vector<int>> zigzagLevelOrder(TreeNode* root)
	{
		vector<vector<int>> result;
		if (root == nullptr)
			return result;
		queue<TreeNode*> Q;
		Q.push(root);
		int level = 0;		// 记录当前的层次数
		while (!Q.empty())
		{
			int curr_layer_size = Q.size();
			vector<int> curr_layer_nodes;
			for (int i = 0; i < curr_layer_size; ++i)
			{
				TreeNode* curr_node = Q.front();
				Q.pop();
				if (level % 2 == 0)
					curr_layer_nodes.push_back(curr_node->val);
				else
					curr_layer_nodes.insert(curr_layer_nodes.begin(), curr_node->val);
				if (curr_node->left != nullptr)
					Q.push(curr_node->left);
				if (curr_node->right != nullptr)
					Q.push(curr_node->right);
			}
			result.push_back(curr_layer_nodes);
			++level;		// 递增层次数
		}
		return result;
	}
};

class Solution_v2 {
public:
	vector<vector<int>> zigzagLevelOrder(TreeNode* root)
	{
		vector<vector<int>> result;
		dfs(root, 0, result);
		return result;
	}

	void dfs(TreeNode* root, int level, vector<vector<int>>& result)
	{
		if (root == nullptr)
			return;
		if (result.size() == level)
			result.push_back(vector<int>{root->val});
		else if (level % 2 == 0)
			result[level].push_back(root->val);
		else
			result[level].insert(result[level].begin(), root->val);
		dfs(root->left, level + 1, result);
		dfs(root->right, level + 1, result);
	}
};
