#pragma once

/*

112. Path Sum

Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.

For example:
Given the below binary tree and sum = 22,

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \      \
        7    2      1

return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.

Approach:
DFS
因为是判断满足条件的 root-to-leaf 的路径是否存在，所以使用DFS进行深度优先的遍历比较合适
递归的实现

Approach_v2:
preorder traverse
基于 stack 的非递归实现


*/

#include <stack>

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
    bool hasPathSum(TreeNode* root, int sum) {
		return dfs(root, sum);
    }

	bool dfs(TreeNode* root, int sum)
	{
		// base case
		// 若当前节点为空节点，返回 false
		if (root == nullptr)
			return false;

		// 若 root->val < sum，则继续向下遍历
		if (root->val != sum)
			return dfs(root->left, sum - root->val) || dfs(root->right, sum - root->val);
		// 若 root->val == sum
		else
		{
			// 且该节点为叶节点，则存在 root-to-leaf path 满足条件
			if (root->left == nullptr && root->right == nullptr)
				return true;
			// 若该节点不是叶节点，则继续向下遍历
			else
				return dfs(root->left, sum - root->val) || dfs(root->right, sum - root->val);
		}
	}
};

class Solution_v2 {
public:
	bool hasPathSum(TreeNode* root, int sum)
	{
		if (root == nullptr)
			return false;

		stack<TreeNode*> S;
		S.push(root);
		while (!S.empty())
		{
			TreeNode* curr = S.top();
			S.pop();
			if (curr->left == nullptr && curr->right == nullptr)
			{
				if (curr->val == sum)
					return true;
			}
			if (curr->right != nullptr)
			{
				curr->right->val += curr->val;
				S.push(curr->right);
			}
			if (curr->left != nullptr)
			{
				curr->left->val += curr->val;
				S.push(curr->left);
			}
		}
		return false;
	}
};

