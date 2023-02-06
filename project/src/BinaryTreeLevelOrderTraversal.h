#pragma once

/*

102. Binary Tree Level Order Traversal

Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]

Approach:
BFS
queue，每次出队一层节点，入队下一层节点

Approach v2:
DFS
In each function call (dfs), we pass in the current node and its level. 
If this level does not yet exist in the output container, then we should add a new empty level. 
Then, we add the current node to the end of the current level, 
and recursively call the function passing the two children of the current node at the next level.

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
	vector<vector<int>> levelOrder(TreeNode* root)
	{
		vector<vector<int>> result;
		if (root == nullptr)
			return result;
		queue<TreeNode*> Q;		// 保存一层节点
		Q.push(root);
		while (!Q.empty())
		{
			int size = Q.size();
			vector<int> curr_layer;
			// 出队当前一层节点，并添加下一层节点
			for (int i = 0; i < size; ++i)
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
		return result;
	}
};

class Solution_v2 {
public:
	vector<vector<int>> result;

	vector<vector<int>> levelOrder(TreeNode* root)
	{
		dfs(root, 0);
		return result;
	}

	void dfs(TreeNode* root, int level)
	{
		if (root == nullptr)
			return;
		if (level == result.size())				// The level does not exist in output
			result.push_back(vector<int>());	// Create a new level
		result[level].push_back(root->val);		// Add the current value to its level
		dfs(root->left, level + 1);				// Go to the next level
		dfs(root->right, level + 1);
	}
};
