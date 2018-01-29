#pragma once

/*

108. Convert Sorted Array to Binary Search Tree

Given an array where elements are sorted in ascending order, 
convert it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as 
a binary tree in which the depth of the two subtrees of every 
node never differ by more than 1.

Given the sorted array: [-10,-3,0,5,9],

One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:

      0
     / \
   -3   9
   /   /
 -10  5

 Approach:
 由于序列以及有序，所以为了构造平衡二叉树，取序列的中间节点作为根，左部接着递归构造左子树，右部接着递归构造右子树。

 Time: O(n)

*/

#include <vector>

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
	TreeNode* sortedArrayToBST(vector<int>& nums)
	{
		return dfs(nums, 0, nums.size() - 1);
	}

	TreeNode* dfs(vector<int>& nums, int start, int finish)
	{
		if (start > finish)
			return nullptr;
		int mid = (start + finish) / 2;
		TreeNode* root = new TreeNode(nums[mid]);
		root->left = dfs(nums, start, mid - 1);
		root->right = dfs(nums, mid + 1, finish);
		return root;
	}
};
