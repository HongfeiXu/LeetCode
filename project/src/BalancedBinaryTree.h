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
˼���뷨һ��ͬ��ֻ��������һЩ�ж���䣬��ȷ��������ƽ��ʱ��ֱ�ӷ���-1��ʾ������ƽ��
dfsHeight ��������Ϊ��������ƽ�⣬�򷵻����ĸ߶ȣ��Ӹ���Ҷ�ӵĽڵ�����������򣬷���-1��ʾ����ƽ�⡣
��ȷ�һ��ʡȥ�˱��� is_balanced 

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
	
	int dfs(TreeNode* root, bool& is_balanced)				// ��ǰ�����߶ȣ������ж��Ƿ�ƽ�⣬��ƽ������ is_balanced Ϊ false
	{
		if (root == nullptr)
			return 0;
		int height_left = dfs(root->left, is_balanced);		// �������߶�
		int height_right = dfs(root->right, is_balanced);	// �������߶�
		if (is_balanced && abs(height_right - height_left) > 1)	// �����������߶Ȳ� > 1���� is_balanced ��Ϊ false
			is_balanced = false;
		return max(height_left, height_right) + 1;			// ���ص�ǰ�����ĸ߶�
	}
};

class Solution_v2 {
public:
	bool isBalanced(TreeNode* root)
	{
		return dfsHeight(root) != -1;
	}

	// ������ƽ�⣬�򷵻����ĸ߶ȣ��Ӹ���Ҷ�ӵĽڵ�����������򣬷���-1��ʾ����ƽ�⡣
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

