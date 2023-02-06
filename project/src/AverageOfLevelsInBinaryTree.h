#pragma once

/*

637. Average of Levels in Binary Tree

Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.
Example 1:
Input:
    3
   / \
  9  20
    /  \
   15   7
Output: [3, 14.5, 11]
Explanation:
The average value of nodes on level 0 is 3,  on level 1 is 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].

Note:
The range of node's value is in the range of 32-bit signed integer.

Approach:
BFS
Time: O(n)  n 为节点总数
Space: O(m) m 为最大的一层节点数

Approach v2:
DFS
Time: O(n)
Space: O(h) h 为树的节点层数（因为递归层数也最多为h）
Ref: https://leetcode.com/problems/average-of-levels-in-binary-tree/solution/

*/

#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
	vector<double> averageOfLevels(TreeNode* root)
	{
		vector<double> result;
		if (root == nullptr)
			return result;
		queue<TreeNode*> Q;
		Q.push(root);
		while (!Q.empty())
		{
			int size = Q.size();
			double total = 0;				// 当前一层的总和
			for(int i = 0; i < size; ++i)
			{
				TreeNode* temp = Q.front();
				Q.pop();
				total += temp->val;
				if (temp->left != nullptr)
					Q.push(temp->left);
				if (temp->right != nullptr)
					Q.push(temp->right);
			}
			result.push_back(total / static_cast<double>(size));
		}
		return result;
	}
};

class Solution_v2 {
public:
	vector<double> sum_of_each_layer;
	vector<int> count_of_each_layer;
	vector<double> averageOfLevels(TreeNode* root)
	{
		dfs(root, 0);
		for (int i = 0; i < sum_of_each_layer.size(); ++i)
			sum_of_each_layer[i] /= count_of_each_layer[i];
		return sum_of_each_layer;
	}

	void dfs(TreeNode* root, int level)
	{
		if (root == nullptr)
			return;
		if (level == sum_of_each_layer.size())
		{
			sum_of_each_layer.push_back(root->val);
			count_of_each_layer.push_back(1);
		}
		else
		{
			sum_of_each_layer[level] += root->val;
			++count_of_each_layer[level];
		}
		dfs(root->left, level + 1);
		dfs(root->right, level + 1);
	}
};

