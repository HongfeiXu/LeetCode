#pragma once

/*

99. Recover Binary Search Tree

Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?

####################################################
Approach:

������ȡ��������Ȼ���������������������θ�ֵ�����ɵõ���ȷ������
Time: O(nlgn)
Space: O(n)

####################################################
Approach v2:

In Order Traverse

��������������Ԫ�ر���ţ���Ҫ��ע���������ʱ����һ������֮��ڵ�Ľڵ㣬���һ��С��֮ǰ�ڵ�Ľڵ㣬��Ϊ���ŵ�����Ԫ��

1,2,3,4,5,6 => 1,5,3,4,2,6

��һ������֮��ڵ�Ľڵ�5
���һ��С��֮ǰ�ڵ�Ľڵ�2����һ������С��֮ǰ�Ľڵ�Ϊ3��
swap(5,2)

1,2,3 => 2,1,3
��һ������֮��ڵ�Ľڵ�2
���һ��С��֮ǰ�ڵ�Ľڵ�1
swap(2,1)

��������������� pre,first,second ������ָ��ֱ��¼���ʵ�ǰ�ڵ�֮ǰ�Ľڵ㣬��һ�����ִ���֮��ڵ�Ľڵ㣬���һ������С��֮ǰ�ڵ�Ľڵ�

Time: O(N)
Space: ƽ�� O(logN)��� O(N), cause the recursion

####################################################
Approach v3:

TODO...

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
		// ���θ�ֵ
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
	TreeNode* first;		// ��һ������֮��ڵ�Ľڵ�
	TreeNode* second;		// ���һ��С��֮ǰ�ڵ�Ľڵ�

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
