#pragma once

/*

94. Binary Tree Inorder Traversal

Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree [1,null,2,3],
   1
    \
     2
    /
   3
return [1,3,2].

Note: Recursive solution is trivial, could you do it iteratively?

Approach:
Recursive solution

Time: O(n)
Space: The worst case space required is O(n), and in the average case it's O(log(n)) where nn is number of nodes.


Approach v2:
Iterating method using Stack

Time: O(n)
Space: O(n)

Approach v3:
Morris Traversal

In this method, we have to use a new data structure-Threaded Binary Tree, and the strategy is as follows:

Step 1: Initialize current as root
Step 2: While current is not NULL,
If current has left child
	a. In current's left subtree, make current the right child of the rightmost node
	b. Go to this left child, i.e., current = current.left
Else
	a. Add current’s value
	b. Go to the right, i.e., current = current.right

Time: O(n)
Space: O(1)
改变了树的结构

Approach v4:
Morris Traversal

不改变树的结构（最终和原始的相同，中间可能会改变）
Time: O(n)
Space: O(1)

*/

#include <vector>
#include <stack>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
	vector<int> inorderTraversal(TreeNode* root)
	{
		vector<int> result;
		inorder(root, result);
		return result;
	}

	void inorder(TreeNode* root, vector<int>& result)
	{
		if (root == nullptr)
			return;
		if (root->left != nullptr)
			inorder(root->left, result);
		result.push_back(root->val);
		if (root->right != nullptr)
			inorder(root->right, result);
	}
};

class Solution_v2 {
public:
	vector<int> inorderTraversal(TreeNode* root)
	{
		vector<int> result;
		stack<TreeNode*> S;
		TreeNode* p = root;
		while (p != nullptr || !S.empty())
		{
			// 从当前节点开始，左孩子方向入栈，直到最左孩子
			while (p != nullptr)
			{
				S.push(p);
				p = p->left;
			}
			// 出栈得到最左孩子
			p = S.top();
			S.pop();
			// 访问节点
			result.push_back(p->val);
			// 转向该最左孩子的右子树
			p = p->right;
		}
		return result;
	}
};

class Solution_v3 {
public:
	vector<int> inorderTraversal(TreeNode* root)
	{
		vector<int> result;
		TreeNode* curr = root;
		while (curr != nullptr)
		{
			// 若左子树为空，进行访问操作
			if (curr->left == nullptr)
			{
				result.push_back(curr->val);	// 访问当前节点
				curr = curr->right;				// p 更新为当前节点的右孩子
			}
			// 若左子树不为空，进行二叉树的变形操作
			else
			{
				TreeNode* pre = curr->left;		// q 保存当前节点 p 的左子树的最右节点
				while (pre->right != nullptr)
					pre = pre->right;
				pre->right = curr;				// 将 p 以及其右子树，作为 q 的右子树
				TreeNode* temp = curr->left;
				curr->left = nullptr;			// 将 p 的左孩子设为空，防止无限循环
				curr = temp;					// p 更新为新的根节点
			}

		}
		return result;
	}
};

class Solution_v4 {
public:
	vector<int> inorderTraversal(TreeNode* root)
	{
		vector<int> result;
		TreeNode* curr = root;
		while (curr != nullptr)
		{
			if (curr->left == nullptr)
			{
				result.push_back(curr->val);
				curr = curr->right;
			}
			else
			{
				// Find the inorder predecessor of current
				TreeNode* pre = curr->left;
				while (pre->right != nullptr && pre->right != curr)	// 注意这里与 Approach_v3 的不同
					pre = pre->right;
				// pre->right == nullptr，说明左子树的最右节点还没有把当前节点作为右孩子
				// Make current as right child of its inorder predecessor
				if (pre->right == nullptr)
				{
					pre->right = curr;
					curr = curr->left;
				}
				// pre->right == curr，说明左子树的最右节点的右孩子已经是当前节点了，需要把它重置回去（因为pre显然在当前节点之前被访问了），即将右孩子设为空。
				// Revert the changes made in if part to restore the original
				// tree i.e., fix the right child of predecssor
				else
				{
					pre->right = nullptr;
					result.push_back(curr->val);
					curr = curr->right;
				}
			}
		}
		return result;
	}
};
