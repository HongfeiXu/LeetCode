#pragma once

/*

111. Minimum Depth of Binary Tree

Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

Approach:
DFS

Approach v2:

Conscise Code


*/

#include <algorithm>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
	int minDepth(TreeNode* root)
	{
		int result;
		if (root == nullptr)
			return 0;
		// depth 为左右子树中具有更短的从根节点到叶节点路径的长度加上1，也就是当前树的最短的根节点到叶节点的路径长度
		int depth_left = minDepth(root->left);
		int depth_right = minDepth(root->right);

		// 若左子树为空，则返回右子树中具有最短的从根节点到叶节点路径的长度加上1
		// 而不能直接返回两者的路径长度较小值加1，如下，最短路径长度应该为2，而不是1
		//     1
		//      \
		//       2
		if (depth_left == 0)
			result = depth_right + 1;
		// 若右子树为空，类似的
		else if (depth_right == 0)
			result = depth_left + 1;
		else
			result = min(depth_left, depth_right) + 1;
		return result;
	}
};

class Solution_v2 {
public:
	int minDepth(TreeNode* root)
	{
		int result;
		if (root == nullptr)
			return 0;
		if (root->left == nullptr)
			return minDepth(root->right) + 1;
		if (root->right == nullptr)
			return minDepth(root->left) + 1;
		result = min(minDepth(root->left), minDepth(root->right)) + 1;
		return result;
	}
};

