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
		// depth Ϊ���������о��и��̵ĴӸ��ڵ㵽Ҷ�ڵ�·���ĳ��ȼ���1��Ҳ���ǵ�ǰ������̵ĸ��ڵ㵽Ҷ�ڵ��·������
		int depth_left = minDepth(root->left);
		int depth_right = minDepth(root->right);

		// ��������Ϊ�գ��򷵻��������о�����̵ĴӸ��ڵ㵽Ҷ�ڵ�·���ĳ��ȼ���1
		// ������ֱ�ӷ������ߵ�·�����Ƚ�Сֵ��1�����£����·������Ӧ��Ϊ2��������1
		//     1
		//      \
		//       2
		if (depth_left == 0)
			result = depth_right + 1;
		// ��������Ϊ�գ����Ƶ�
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

