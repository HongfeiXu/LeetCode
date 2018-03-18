#pragma once

/*

110. Balanced Binary Tree

Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as:

a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

Example 1:

Given the following tree [3,9,20,null,null,15,7]:

    3
   / \
  9  20
    /  \
   15   7
Return true.

Example 2:

Given the following tree [1,2,2,3,3,null,null,4,4]:

       1
      / \
     2   2
    / \
   3   3
  / \
 4   4
Return false.

Approach:
DFS

Time: O(n)

Approach_v2:
思想与法一相同，只是增加了一些判断语句，当确定子树不平衡时，直接返回-1表示子树不平衡
dfsHeight 函数功能为：若该树平衡，则返回树的高度（从根到叶子的节点个数），否则，返回-1表示树不平衡。
相比法一，省去了变量 is_balanced 

Time: O(n)

*/

#include <algorithm>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) { }
};

class Solution {
public:
	bool isBalanced(TreeNode* root) 
	{
		bool result = true;
		dfs(root, result);
		return result;
	}
	
	int dfs(TreeNode* root, bool& is_balanced)				// 求当前子树高度，并且判断是否平衡，不平衡则设 is_balanced 为 false
	{
		if (root == nullptr)
			return 0;
		int height_left = dfs(root->left, is_balanced);		// 左子树高度
		int height_right = dfs(root->right, is_balanced);	// 右子树高度
		if (is_balanced && abs(height_right - height_left) > 1)	// 若左右子树高度差 > 1，则 is_balanced 设为 false
			is_balanced = false;
		return max(height_left, height_right) + 1;			// 返回当前子树的高度
	}
};

class Solution_v2 {
public:
	bool isBalanced(TreeNode* root)
	{
		return dfsHeight(root) != -1;
	}

	// 若该树平衡，则返回树的高度（从根到叶子的节点个数），否则，返回-1表示树不平衡。
	int dfsHeight(TreeNode* root)			
	{
		if (root == nullptr)
			return 0;
		int height_left = dfsHeight(root->left);
		if (height_left == -1)				
			return -1;
		int height_right = dfsHeight(root->right);
		if (height_right == -1)
			return -1;
		if (abs(height_left - height_right) > 1)
			return -1;
		return max(height_left, height_right) + 1;
	}
};

