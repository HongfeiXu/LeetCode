#pragma once

/*

515. Find Largest Value in Each Tree Row

You need to find the largest value in each row of a binary tree.

Example:
Input: 

          1
         / \
        3   2
       / \   \  
      5   3   9 

Output: [1, 3, 9]

Approach:

BFS

Approach:

DFS with level count

*/

#include <vector>
#include <queue>
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
	vector<int> largestValues(TreeNode* root)
	{
		vector<int> result;
		if (root == nullptr)
			return result;
		queue<TreeNode*> Q;		// Q 中保存树一行的节点
		Q.push(root);
		while (!Q.empty())
		{
			int curr_layer_size = Q.size();
			int curr_layer_max = INT_MIN;
			for (int i = 0; i < curr_layer_size; ++i)
			{
				TreeNode* p = Q.front();
				Q.pop();
				curr_layer_max = max(curr_layer_max, p->val);
				if (p->left != nullptr)
					Q.push(p->left);
				if (p->right != nullptr)
					Q.push(p->right);
			}
			result.push_back(curr_layer_max);
		}
		return result;
	}
};

class Solution_v2 {
public:
	vector<int> largestValues(TreeNode* root)
	{
		vector<int> result;
		if (root == nullptr)
			return result;
		dfs(root, 0, result);
		return result;
	}

	void dfs(TreeNode* root, int level, vector<int>& result)
	{
		if (root == nullptr)
			return;
		if (result.size() == level)
			result.push_back(root->val);
		else
			result[level] = max(result[level], root->val);
		dfs(root->left, level + 1, result);
		dfs(root->right, level + 1, result);
	}
};