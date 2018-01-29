#pragma once

/*

99. Recover Binary Search Tree

Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?

Approach:

将数字取出，排序，然后对树进行中序遍历，依次赋值，即可得到正确的树。
Time: O(nlgn)
Space: O(n)

Approach v2:

*/

#include <vector>
#include <algorithm>

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
