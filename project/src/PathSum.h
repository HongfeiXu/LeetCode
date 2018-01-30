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
��Ϊ���ж����������� root-to-leaf ��·���Ƿ���ڣ�����ʹ��DFS����������ȵı����ȽϺ���
�ݹ��ʵ��

Approach_v2:
preorder traverse
���� stack �ķǵݹ�ʵ��


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
		// ����ǰ�ڵ�Ϊ�սڵ㣬���� false
		if (root == nullptr)
			return false;

		// �� root->val < sum����������±���
		if (root->val != sum)
			return dfs(root->left, sum - root->val) || dfs(root->right, sum - root->val);
		// �� root->val == sum
		else
		{
			// �Ҹýڵ�ΪҶ�ڵ㣬����� root-to-leaf path ��������
			if (root->left == nullptr && root->right == nullptr)
				return true;
			// ���ýڵ㲻��Ҷ�ڵ㣬��������±���
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

