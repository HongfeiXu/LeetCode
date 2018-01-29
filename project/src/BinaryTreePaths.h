#pragma once

/*

257. Binary Tree Paths

Given a binary tree, return all root-to-leaf paths.

For example, given the following binary tree:

   1
 /   \
2     3
 \
  5

All root-to-leaf paths are:

["1->2->5", "1->3"]

Approach:

DP
      1
  ->2  ->3
->5

*/


#include <vector>
#include <string>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
	vector<string> binaryTreePaths(TreeNode* root)
	{
		vector<string> result;
		if (root == nullptr)
			return result;
		dfs(root, "", result);
		return result;
	}

	void dfs(TreeNode* root, string curr_path, vector<string>& all_paths)
	{
		// 当前节点转换为字符串
		string to_append;

		// 如果路径不为空，则添加 "->" ，否则，为根节点，前面不用加 "->"
		if (!curr_path.empty())
			to_append.append("->");
		to_append.append(to_string(root->val));
		curr_path.append(to_append);

		// 若 root 为叶节点，则找到了一条从根到叶的路径，添加到 all_paths 中
		if (root->left == nullptr && root->right == nullptr)
		{
			all_paths.push_back(curr_path);
			return;
		}
		// 若 root 不是叶节点，则继续向下遍历不为空的子树
		if (root->left != nullptr)
			dfs(root->left, curr_path, all_paths);
		if (root->right != nullptr)
			dfs(root->right, curr_path, all_paths);
	}
};

