#pragma once

/*

652. Find Duplicate Subtrees

Given a binary tree, return all duplicate subtrees. For each kind of duplicate subtrees, you only need to return the root node of any one of them.

Two trees are duplicate if they have the same structure with same node values.

Example 1: 
        1
       / \
      2   3
     /   / \
    4   2   4
       /
      4
The following are two duplicate subtrees:
      2
     /
    4
and
    4
Therefore, you need to return above trees' root in the form of a list.

Approach:
受到 ConstructStringFromBinaryTree 的启发，我们可以用一个字符串表示出一棵二叉树的所有信息，比如

   1
  / \
 2   3
    / \
   4   5
可表示为：1(2()())(3(4()())(5()()))

那么我们可以在程序中记录每个子树对应的字符串，
然后寻找具有相同字符串的子树，保存为结果。

Approach 2 （use unordered_map）:
类似的，因为是根据字符串的相同来寻找重复的子树，我们可以使用 unordered_map 这一数据结构，
unordered_map<string, vector<TreeNode*>>
将结果信息存储到此容器中的好处是，最后通过查看哪些 string 对应的 vector 中不止一个元素，即为重复的子树信息。
使用 unordered_map 避免了定义关于 NodeString 的比较运算符。

*/

#include <string>
#include <iostream>
#include <utility>
#include <algorithm>
#include <unordered_map>

using namespace std;

class TreeNode {
public:
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) { }
};

struct NodeString {
	TreeNode* node;
	string s;
};

bool operator<(const NodeString &lhs, const NodeString &rhs)
{
	return lhs.s < rhs.s;
}

bool operator==(const NodeString &lhs, const NodeString &rhs)
{
	return lhs.s == rhs.s;
}

class Solution {
public:
	vector<TreeNode*> findDuplicateSubtrees(TreeNode* root)
	{
		vector<TreeNode*> result;

		vector<NodeString> node_string_vec;				// 保存所有子树在先序遍历下形成的字符串
		preorder_traverse(root, node_string_vec);		// 与 ConstructStringFromBinaryTree 思想相同，生成所有子树的字符串
		// 将所有子树对应的字符串信息按照字符串大小排序，然后寻找重复字符串
		sort(node_string_vec.begin(), node_string_vec.end());
		for (int i = 0; i < node_string_vec.size();)
		{
			int j = i + 1;
			while ((j < node_string_vec.size()) && node_string_vec[i] == node_string_vec[j])
				++j;
			// 如果有超过1个 node 子树对应的字符串相同，则该子树为重复子树，添加到结果中，并跳过相同的子树
			if (j - i > 1)	
				result.push_back(node_string_vec[i].node);
			i = j;
		}
		return result;
	}

	// 访问node，将node为根的子树转换为先序访问的字符串，其标志出其中的空节点。
	string preorder_traverse(TreeNode* node, vector<NodeString>& node_string_vec)
	{
		string subtree_string;
		if (node == nullptr)
			return string("");

		subtree_string.append(to_string(node->val));
		subtree_string = "(" + preorder_traverse(node->left, node_string_vec) + ")" + "(" + preorder_traverse(node->right, node_string_vec) + ")";
		node_string_vec.push_back({ node, subtree_string });

		return subtree_string;
	}
};

class Solution_v2 {
public:
	vector<TreeNode*> findDuplicateSubtrees(TreeNode* root)
	{
		vector<TreeNode*> dups;

		unordered_map<string, vector<TreeNode*>> string2node;		// 很好的一个使用 unordered_map 的例子
		preorder_traverse(root, string2node);

		for (auto it = string2node.begin(); it != string2node.end(); ++it)
		{
			if (it->second.size() > 1)
				dups.push_back(it->second[0]);
		}
		return dups;
	}

	string preorder_traverse(TreeNode* root, unordered_map<string, vector<TreeNode*>>& string2node)
	{
		if (root == nullptr)
			return string("");
		string result;

		result.append(to_string(root->val));
		result = "(" + preorder_traverse(root->left, string2node) + ")" + "(" + preorder_traverse(root->right, string2node) + ")";
		
		string2node[result].push_back(root);

		return result;
	}
};

/*

#include <iostream>
#include <vector>
#include <iterator>

#include "HelpFunc.h"

#include "FindDuplicateSubtrees.h"

using namespace std;

int main()
{
	Solution_v2 solution;
	
	TreeNode a(1);
	TreeNode b(2);
	TreeNode c(3);
	TreeNode d(4);
	TreeNode e(2);
	TreeNode f(4);
	TreeNode g(4);

	a.left = &b;
	a.right = &c;
	b.left = &d;
	c.left = &e;
	c.right = &f;
	e.left = &g;

	auto result = solution.findDuplicateSubtrees(&a);
	for (auto item : result)
	{
		cout << item << " " << item->val << endl;
	}
	
	return 0;
}

*/