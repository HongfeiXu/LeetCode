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
���ڶ�������ǰ������Ľ����������������Ľ�����п���Ψһȷ�������������
���ǿ��Էֱ������������ǰ������Լ�����������Ƚϱ�������Ƿ���ȫ��ͬ��
�������۶���û���ظ��ڵ�����ǿ��еģ�������һЩ������������£�����޷�����������ͬ�Ķ�����
[1,1]
[1,null,1]

Approach_v2:

ǰ��������õ������������ű�ʾ�����磺
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
һ�� dfs ���������� tree���������ڵ������ͬ���򷵻� false
�������շ��� true

Approach_v4:
����� v3

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
				// �� p->val �� q->val ��ͬ�����ж����ǵ����������Ƿ��Ӧ��ͬ
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
