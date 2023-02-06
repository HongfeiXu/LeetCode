#pragma once

/*

107. Binary Tree Level Order Traversal II

Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its bottom-up level order traversal as:
[
  [15,7],
  [9,20],
  [3]
]

Approach:

BFS，返回的时候逆转顺序

Approach v2:

DFS，返回时逆转顺序

*/

#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
	vector<vector<int>> levelOrderBottom(TreeNode* root)
	{
		vector<vector<int>> result;
		if (root == nullptr)
			return result;
		queue<TreeNode*> Q;
		Q.push(root);
		while (!Q.empty())
		{
			int curr_layer_size = Q.size();
			vector<int> curr_layer;
			for (int i = 0; i < curr_layer_size; ++i)
			{
				TreeNode* temp = Q.front();
				Q.pop();
				curr_layer.push_back(temp->val);
				if (temp->left != nullptr)
					Q.push(temp->left);
				if (temp->right != nullptr)
					Q.push(temp->right);
			}
			result.push_back(curr_layer);
		}
		return vector<vector<int>>(result.rbegin(), result.rend());
	}
};

class Solution_v2 {
public:
	vector<vector<int>> result;

	vector<vector<int>> levelOrderBottom(TreeNode* root)
	{
		dfs(root, 0);
		return vector<vector<int>>(result.rbegin(), result.rend());
	}

	void dfs(TreeNode* root, int level)
	{
		if (root == nullptr)
			return;
		if (level == result.size())				// The level does not exist in output
			result.push_back(vector<int>());
		result[level].push_back(root->val);
		dfs(root->left, level + 1);
		dfs(root->right, level + 1);
	}
};
