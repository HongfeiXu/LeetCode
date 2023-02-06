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
用当前的 tree 构造出一个和它对称的 tree_symmetric，然后判断这两个树 是否相等
若相等，则说明 tree 对称，否则不对称

Time: O(n)
Space: O(n)

Approach_v2:
这里我们只需要判断左子树与右子树是否对称，若对称则 tree 对称
使用 dfs 的方法同时遍历左子树和右子树，类似 100. Same Tree Approach_v4 的遍历方式，
只是这里是将 l 的左子树与 r 的右子树，l 的右子树与 r 的左子树进行比较。
若l->val == r->val && l->left == r->right && l->right == r->left
则说明 l 与 r 对称

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
		// 拷贝当前根节点
		TreeNode* p = new TreeNode(root->val);
		// 拷贝左子树，作为右子树
		p->right = copySymmetricTree(root->left);
		// 拷贝右子树，作为左子树
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

	// 判断两个二叉树是否对称
	bool isSymmetric(TreeNode* l, TreeNode* r)
	{
		// 若l，r中有空节点，则两者相同返回true，不同返回false
		if (l == nullptr || r == nullptr)
			return l == r;
		// 当前节点相同，且l的左子树等于r的右子树，l的右子树等于r的左子树，则l和r对称
		return (l->val == r->val && isSymmetric(l->left, r->right) && isSymmetric(l->right, r->left));
	}
};

