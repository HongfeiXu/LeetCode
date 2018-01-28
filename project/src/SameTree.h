#pragma once

/*

100. Same Tree

Given two binary trees, write a function to check if they are the same or not.

Two binary trees are considered the same if they are structurally identical and the nodes have the same value.

Example 1:

Input:     1         1
          / \       / \
         2   3     2   3

        [1,2,3],   [1,2,3]

Output: true
Example 2:

Input:     1         1
          /           \
         2             2

        [1,2],     [1,null,2]

Output: false
Example 3:

Input:     1         1
          / \       / \
         2   1     1   2

        [1,2,1],   [1,1,2]

Output: false

Approach:
Wrong Answer
对于二叉树，前序遍历的结果序列与中序遍历的结果序列可以唯一确定这个二叉树。
我们可以分别对两棵树进行前序遍历以及中序遍历，比较遍历结果是否完全相同。
上述理论对于没有重复节点的树是可行的，但对于一些特殊情况，如下，则会无法区分两个不同的二叉树
[1,1]
[1,null,1]

Approach_v2:

前序遍历，得到二叉树的括号表示序列如：
Input:     1         1
          / \       / \
         2   1     1   2
"1(2,1)"
"1(1,2)"

Input:     1         1
          /           \
         2             2

"1(2,)"
"1(,2)"

Approach_v3:
一起 dfs 访问这两个 tree，若遇到节点情况不同，则返回 false
否则，最终返回 true

Approach_v4:
精简版 v3

*/

#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>

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
	bool isSameTree(TreeNode* p, TreeNode* q)
	{
		vector<int> preorder_result_p;
		vector<int> preorder_result_q;
		preorder(p, preorder_result_p);
		preorder(q, preorder_result_q);
		if (preorder_result_p != preorder_result_q)
			return false;

		vector<int> midorder_result_p;
		vector<int> midorder_result_q;
		midorder(p, midorder_result_p);
		midorder(q, midorder_result_q);

		return midorder_result_p == midorder_result_q;
	}
	void preorder(TreeNode* root, vector<int>& result)
	{
		if (root == nullptr)
			return;
		result.push_back(root->val);
		preorder(root->left, result);
		preorder(root->right, result);
	}
	void midorder(TreeNode* root, vector<int>& result)
	{
		if (root == nullptr)
			return;
		midorder(root->left, result);
		result.push_back(root->val);
		midorder(root->right, result);
	}
};

class Solution_v2 {
public:
	bool isSameTree(TreeNode* p, TreeNode* q)
	{
		string p_seq;
		treeToSequence(p, p_seq);
		string q_seq;
		treeToSequence(q, q_seq);

		return p_seq == q_seq;
	}

	void treeToSequence(TreeNode* root, string& result)
	{
		if (root == nullptr)
			return;
		result.append(to_string(root->val));
		if (root->left != nullptr || root->right != nullptr)
		{
			result.append("(");
			treeToSequence(root->left, result);
			result.append(",");
			treeToSequence(root->right, result);
			result.append(")");
		}
	}
};

class Solution_v3 {
public:
	bool isSameTree(TreeNode* p, TreeNode* q)
	{
		// base case
		if (p == nullptr && q == nullptr)
			return true;

		if (p != nullptr && q != nullptr)
		{
			if (p->val != q->val)
				return false;
			else
				// 若 p->val 和 q->val 相同，则判断它们的左右子树是否对应相同
				return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
		}
		else
			return false;
	}
};

class Solution_v4 {
public:
	bool isSameTree(TreeNode* p, TreeNode* q)
	{
		// base case
		if (p == nullptr || q == nullptr)
			return p == q;
		return (p->val == q->val
				&& isSameTree(p->left, q->left)
				&& isSameTree(p->right, q->right));
	}
};
