#pragma once

/*

98. Validate Binary Search Tree

Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.

Example 1:
    2
   / \
  1   3
Binary tree [2,1,3], return true.
Example 2:
    1
   / \
  2   3
Binary tree [1,2,3], return false.

Approach:
�������BST���õ��ϸ��������С�����Ŀ��Ҫ�����Ϊ�ϸ�����
�����з�������˵������BST

Approach v2:
��Ȼʹ����������ķ����������ﲻ����������У�
�����ڱ�����ʱ�򱣴�ǰһ�����ʽڵ��ָ��pre���뵱ǰ���ʽڵ������������бȽϡ�

Approach v3:
Wrong Answer
DFS
�жϵ�ǰ�ڵ������������ڵ㡢���������ڵ��Ƿ����� BST��
����������򷵻� false��
�����������������ж���������
�߼�����ȷ����������������ӣ�������BST����������������жϻ᷵�� true��
       10
      /   \
	 5     15
	      /  \
		 6    20

*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
	bool isValidBST(TreeNode* root)
	{
		vector<int> traverse_seq;
		midorderTraverse(root, traverse_seq);
		// �� traverse_seq �����򷵻� true�����򷵻� false
		for (int i = 1; i < traverse_seq.size(); ++i)
		{
			if (traverse_seq[i] <= traverse_seq[i - 1])
				return false;
		}
		return true;
	}

	void midorderTraverse(TreeNode* root, vector<int>& traverse_seq)
	{
		if (root == nullptr)
			return;
		if (root->left != nullptr)
			midorderTraverse(root->left, traverse_seq);
		traverse_seq.push_back(root->val);
		if (root->right != nullptr)
			midorderTraverse(root->right, traverse_seq);
	}
};

class Solution_v2 {
public:
	bool isValidBST(TreeNode* root)
	{
		TreeNode* pre = nullptr;
		return midorderTraverse(root, pre);
	}
	// pre ��������������ʵ���ǰ root ����ʱ��ǰһ���ڵ�ĵ�ַ
	bool midorderTraverse(TreeNode* root, TreeNode* &pre)
	{
		if (root == nullptr)
			return true;
		// ��������������BST������ false
		if (!midorderTraverse(root->left, pre))
			return false;
		// ����ǰ�ڵ㲻����BST,���� false
		if (pre != nullptr && root->val <= pre->val)
			return false;
		// ���� pre
		pre = root;
		// ��������������BST������ false
		if (!midorderTraverse(root->right, pre))
			return false;
		return true;
	}
};

// WRONG ANSWER
class Solution_v3 {
public:
	bool isValidBST(TreeNode* root)
	{
		if (root == nullptr)
			return true;
		// �����������ڣ����жϵ�ǰ�ڵ���������ĸ��ڵ��Ƿ����� BST���������򷵻� false������������ж�
		if (root->left != nullptr && root->left->val >= root->val)
			return false;
		// �����������ڣ����жϵ�ǰ�ڵ���������ĸ��ڵ��Ƿ����� BST���������򷵻� false����������������ж�
		if (root->right != nullptr && root->right->val <= root->val)
			return false;
		// ���������ж��������������������
		return isValidBST(root->left) && isValidBST(root->right);
	}
};