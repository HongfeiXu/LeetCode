#pragma once

/*

99. Recover Binary Search Tree

Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?

####################################################
Approach:

将数字取出，排序，然后对树进行中序遍历，依次赋值，即可得到正确的树。
Time: O(nlgn)
Space: O(n)

####################################################
Approach v2:

In Order Traverse

有序序列中两个元素被错放，主要关注在中序遍历时，第一个大于之后节点的节点，最后一个小于之前节点的节点，即为别错放的两个元素

1,2,3,4,5,6 => 1,5,3,4,2,6

第一个大于之后节点的节点5
最后一个小于之前节点的节点2（第一个数字小于之前的节点为3）
swap(5,2)

1,2,3 => 2,1,3
第一个大于之后节点的节点2
最后一个小于之前节点的节点1
swap(2,1)

进行中序遍历，用 pre,first,second 这三个指针分别记录访问当前节点之前的节点，第一个数字大于之后节点的节点，最后一个数字小于之前节点的节点

Time: O(N)
Space: 平均 O(logN)，最坏 O(N), cause the recursion

####################################################
Approach v3: COOOOOOL

思路与v2相同，只是这里使用 Morris Traversal 的方式进行中序遍历，既不是基于栈的也不是递归实现。使得空间复杂度降为 O(1)。
Time: O(N)
Space: O(1)

*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
	void recoverTree(TreeNode* root)
	{
		vector<int> vals;
		getVals(root, vals);
		sort(vals.begin(), vals.end());
		int pos = 0;
		recoverTreeAux(root, vals, pos);
	}

	void recoverTreeAux(TreeNode* root, vector<int>& vals, int& pos)
	{
		if (root == nullptr)
			return;
		if (root->left != nullptr)
			recoverTreeAux(root->left, vals, pos);
		// 依次赋值
		root->val = vals[pos];
		++pos;
		if (root->right != nullptr)
			recoverTreeAux(root->right, vals, pos);
	}
	
	void getVals(TreeNode* root, vector<int>& vals)
	{
		if (root == nullptr)
			return;
		vals.push_back(root->val);
		getVals(root->left, vals);
		getVals(root->right, vals);
	}
};

class Solution_v2 {
private:
	TreeNode* pre;
	TreeNode* first;		// 第一个大于之后节点的节点
	TreeNode* second;		// 最后一个小于之前节点的节点

public:
	void recoverTree(TreeNode* root)
	{
		pre = first = second = nullptr;
		inorderTraverse(root);
		swap(first->val, second->val);
	}

	void inorderTraverse(TreeNode* root)
	{
		if (root == nullptr)
			return;
		inorderTraverse(root->left);
		if (pre != nullptr && first == nullptr && pre->val > root->val)
			first = pre;
		if (first != nullptr && pre->val > root->val)
			second = root;
		pre = root;
		inorderTraverse(root->right);
	}
};

class Solution_v3 {
private:
	TreeNode* pre;			// 用来辅助进行 Morris Traversal，寻找左子树的最右节点

	TreeNode* previous;		// 记录前一个被访问的节点
	TreeNode* first;		// 第一个大于之后节点的节点
	TreeNode* second;		// 最后一个小于之前节点的节点

public:
	void recoverTree(TreeNode* root)
	{

		previous = pre = first = second = nullptr;
		inorderTraverse(root);
		swap(first->val, second->val);
	}

	void inorderTraverse(TreeNode* curr)
	{
		while (curr != nullptr)
		{
			if (curr->left == nullptr)
			{
				// 将当前要遍历的节点 curr 与前一个遍历的节点 previous 做比较，寻找 first 和 second
				if (previous != nullptr && previous->val > curr->val)
				{
					if (first == nullptr)
						first = previous;
					second = curr;
				}
				// 更新 previous 以及 curr
				previous = curr;
				curr = curr->right;
			}
			else
			{
				pre = curr->left;
				while (pre->right != nullptr && pre->right != curr)
					pre = pre->right;
				if (pre->right == nullptr)
				{
					pre->right = curr;
					curr = curr->left;
				}
				else
				{
					// 断开线索，恢复树的原来形状
					pre->right = nullptr;
					// 将当前要遍历的节点 curr 与前一个遍历的节点 previous 做比较，寻找 first 和 second
					if (previous->val > curr->val)
					{
						if (first == nullptr)
							first = previous;
						second = curr;
					}
					previous = curr;
					curr = curr->right;
				}
			}
		}
	}
};
