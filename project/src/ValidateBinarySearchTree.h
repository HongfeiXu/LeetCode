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
中序遍历BST，得到严格升序序列。（题目中要求必须为严格升序）
若序列非升序，则说明不是BST

Approach v2:
依然使用中序遍历的方法，但这里不保存遍历序列，
而是在遍历的时候保存前一个访问节点的指针pre，与当前访问节点所在子树进行比较。

Approach v3:
Wrong Answer
DFS
判断当前节点与左子树根节点、右子树根节点是否满足 BST。
如果不满足则返回 false。
如果满足则继续向下判断其子树。
逻辑不正确，比如下面这个例子，不满足BST，但按照这个方法判断会返回 true。
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
		// 若 traverse_seq 有序，则返回 true，否则返回 false
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
	// pre 保存中序遍历访问到当前 root 子树时的前一个节点的地址
	bool midorderTraverse(TreeNode* root, TreeNode* &pre)
	{
		if (root == nullptr)
			return true;
		// 若左子树不满足BST，返回 false
		if (!midorderTraverse(root->left, pre))
			return false;
		// 若当前节点不满足BST,返回 false
		if (pre != nullptr && root->val <= pre->val)
			return false;
		// 更新 pre
		pre = root;
		// 若右子树不满足BST，返回 false
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
		// 若左子树存在，则判断当前节点和左子树的根节点是否满足 BST，不满足则返回 false，满足则继续判断
		if (root->left != nullptr && root->left->val >= root->val)
			return false;
		// 若右子树存在，则判断当前节点和右子树的根节点是否满足 BST，不满足则返回 false，满足则继续向下判断
		if (root->right != nullptr && root->right->val <= root->val)
			return false;
		// 继续向下判断左子树、右子树的情况
		return isValidBST(root->left) && isValidBST(root->right);
	}
};