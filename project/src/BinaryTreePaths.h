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
		// ��ǰ�ڵ�ת��Ϊ�ַ���
		string to_append;

		// ���·����Ϊ�գ������ "->" ������Ϊ���ڵ㣬ǰ�治�ü� "->"
		if (!curr_path.empty())
			to_append.append("->");
		to_append.append(to_string(root->val));
		curr_path.append(to_append);

		// �� root ΪҶ�ڵ㣬���ҵ���һ���Ӹ���Ҷ��·������ӵ� all_paths ��
		if (root->left == nullptr && root->right == nullptr)
		{
			all_paths.push_back(curr_path);
			return;
		}
		// �� root ����Ҷ�ڵ㣬��������±�����Ϊ�յ�����
		if (root->left != nullptr)
			dfs(root->left, curr_path, all_paths);
		if (root->right != nullptr)
			dfs(root->right, curr_path, all_paths);
	}
};

