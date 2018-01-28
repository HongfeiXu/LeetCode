#pragma once

/*

101. Symmetric Tree

Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3
But the following [1,2,2,null,3,null,3] is not:
    1
   / \
  2   2
   \   \
   3    3

Note:
Bonus points if you could solve it both recursively and iteratively.

Approach:
�õ�ǰ�� tree �����һ�������ԳƵ� tree_symmetric��Ȼ���ж��������� �Ƿ����
����ȣ���˵�� tree �Գƣ����򲻶Գ�

Time: O(n)
Space: O(n)

Approach_v2:
��������ֻ��Ҫ�ж����������������Ƿ�Գƣ����Գ��� tree �Գ�
ʹ�� dfs �ķ���ͬʱ������������������������ 100. Same Tree Approach_v4 �ı�����ʽ��
ֻ�������ǽ� l ���������� r ����������l ���������� r �����������бȽϡ�
��l->val == r->val && l->left == r->right && l->right == r->left
��˵�� l �� r �Գ�

Time: O(n)
Space: O(1)

*/

#include <algorithm>
#include <string>

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
	bool isSymmetric(TreeNode* root)
	{
		TreeNode* root_symmetric = copySymmetricTree(root);
		return isSame(root, root_symmetric);
	}

	bool isSame(TreeNode* p, TreeNode* q)
	{
		if (p == nullptr || q == nullptr)
			return p == q;
		return (p->val == q->val && isSame(p->left, q->left) && isSame(p->right, q->right));
	}

	TreeNode* copySymmetricTree(TreeNode* root)
	{
		if (root == nullptr)
			return nullptr;
		// ������ǰ���ڵ�
		TreeNode* p = new TreeNode(root->val);
		// ��������������Ϊ������
		p->right = copySymmetricTree(root->left);
		// ��������������Ϊ������
		p->left = copySymmetricTree(root->right);
		return p;
	}
};

class Solution_v2 {
public:
	bool isSymmetric(TreeNode* root)
	{
		if (root == nullptr)
			return true;
		return isSymmetric(root->left, root->right);
	}

	// �ж������������Ƿ�Գ�
	bool isSymmetric(TreeNode* l, TreeNode* r)
	{
		// ��l��r���пսڵ㣬��������ͬ����true����ͬ����false
		if (l == nullptr || r == nullptr)
			return l == r;
		// ��ǰ�ڵ���ͬ����l������������r����������l������������r������������l��r�Գ�
		return (l->val == r->val && isSymmetric(l->left, r->right) && isSymmetric(l->right, r->left));
	}
};

