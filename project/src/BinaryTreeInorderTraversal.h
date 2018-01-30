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
	a. Add current��s value
	b. Go to the right, i.e., current = current.right

Time: O(n)
Space: O(1)
�ı������Ľṹ

Approach v4:
Morris Traversal

���ı����Ľṹ�����պ�ԭʼ����ͬ���м���ܻ�ı䣩
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
			// �ӵ�ǰ�ڵ㿪ʼ�����ӷ�����ջ��ֱ��������
			while (p != nullptr)
			{
				S.push(p);
				p = p->left;
			}
			// ��ջ�õ�������
			p = S.top();
			S.pop();
			// ���ʽڵ�
			result.push_back(p->val);
			// ת��������ӵ�������
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
			// ��������Ϊ�գ����з��ʲ���
			if (curr->left == nullptr)
			{
				result.push_back(curr->val);	// ���ʵ�ǰ�ڵ�
				curr = curr->right;				// p ����Ϊ��ǰ�ڵ���Һ���
			}
			// ����������Ϊ�գ����ж������ı��β���
			else
			{
				TreeNode* pre = curr->left;		// q ���浱ǰ�ڵ� p �������������ҽڵ�
				while (pre->right != nullptr)
					pre = pre->right;
				pre->right = curr;				// �� p �Լ�������������Ϊ q ��������
				TreeNode* temp = curr->left;
				curr->left = nullptr;			// �� p ��������Ϊ�գ���ֹ����ѭ��
				curr = temp;					// p ����Ϊ�µĸ��ڵ�
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
				while (pre->right != nullptr && pre->right != curr)	// ע�������� Approach_v3 �Ĳ�ͬ
					pre = pre->right;
				// pre->right == nullptr��˵�������������ҽڵ㻹û�аѵ�ǰ�ڵ���Ϊ�Һ���
				// Make current as right child of its inorder predecessor
				if (pre->right == nullptr)
				{
					pre->right = curr;
					curr = curr->left;
				}
				// pre->right == curr��˵�������������ҽڵ���Һ����Ѿ��ǵ�ǰ�ڵ��ˣ���Ҫ�������û�ȥ����Ϊpre��Ȼ�ڵ�ǰ�ڵ�֮ǰ�������ˣ��������Һ�����Ϊ�ա�
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
