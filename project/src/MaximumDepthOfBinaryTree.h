#pragma once

/*

104. Maximum Depth of Binary Tree

Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

For example:
Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7

return its depth = 3.

Approach:
DFS

Approach v2:
DFS 精简版

Approach v3:
BFS

使用 queue 保存当前层的节点，然后出队掉这一层的节点，添加下一层的节点，
并且每去掉一层节点，++depth，直到队列为空

*/

#include <algorithm>
#include <queue>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) { }
};

class Solution {
public:
	int maxDepth(TreeNode* root)
	{
		int curr_depth = 0;
		int max_depth = 0;
		dfs(root, curr_depth, max_depth);
		return max_depth;
	}

	void dfs(TreeNode* root, int curr_depth, int& max_depth)
	{
		// base case
		if (root == nullptr)
			return;

		++curr_depth;
		max_depth = max(curr_depth, max_depth);
		dfs(root->left, curr_depth, max_depth);
		dfs(root->right, curr_depth, max_depth);
	}
};

class Solution_v2 {
public:
	int maxDepth(TreeNode* root)
	{
		if (root == nullptr)
			return 0;
		return max(maxDepth(root->left), maxDepth(root->right)) + 1;
	}
};

class Solution_v3 {
public:
	int maxDepth(TreeNode* root)
	{
		if (root == nullptr)
			return 0;
		int depth = 0;
		queue<TreeNode*> layer;
		layer.push(root);
		while (!layer.empty())
		{
			++depth;
			int pre_size = layer.size();		// 存储上一层的节点个数
			for (int i = 0; i < pre_size; ++i)	// 依次出队 pre_size 个节点（将上一层的节点出完），并在出队的时候插入下一层的节点
			{
				TreeNode* curr = layer.front();
				layer.pop();
				if (curr->left != nullptr)
					layer.push(curr->left);
				if (curr->right != nullptr)
					layer.push(curr->right);
			}
		}
		return depth;
	}
};