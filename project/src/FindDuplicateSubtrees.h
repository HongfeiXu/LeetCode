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
�ܵ� ConstructStringFromBinaryTree �����������ǿ�����һ���ַ�����ʾ��һ�ö�������������Ϣ������

   1
  / \
 2   3
    / \
   4   5
�ɱ�ʾΪ��1(2()())(3(4()())(5()()))

��ô���ǿ����ڳ����м�¼ÿ��������Ӧ���ַ�����
Ȼ��Ѱ�Ҿ�����ͬ�ַ���������������Ϊ�����

Approach 2 ��use unordered_map��:
���Ƶģ���Ϊ�Ǹ����ַ�������ͬ��Ѱ���ظ������������ǿ���ʹ�� unordered_map ��һ���ݽṹ��
unordered_map<string, vector<TreeNode*>>
�������Ϣ�洢���������еĺô��ǣ����ͨ���鿴��Щ string ��Ӧ�� vector �в�ֹһ��Ԫ�أ���Ϊ�ظ���������Ϣ��
ʹ�� unordered_map �����˶������ NodeString �ıȽ��������

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

		vector<NodeString> node_string_vec;				// ������������������������γɵ��ַ���
		preorder_traverse(root, node_string_vec);		// �� ConstructStringFromBinaryTree ˼����ͬ�����������������ַ���
		// ������������Ӧ���ַ�����Ϣ�����ַ�����С����Ȼ��Ѱ���ظ��ַ���
		sort(node_string_vec.begin(), node_string_vec.end());
		for (int i = 0; i < node_string_vec.size();)
		{
			int j = i + 1;
			while ((j < node_string_vec.size()) && node_string_vec[i] == node_string_vec[j])
				++j;
			// ����г���1�� node ������Ӧ���ַ�����ͬ���������Ϊ�ظ���������ӵ�����У���������ͬ������
			if (j - i > 1)	
				result.push_back(node_string_vec[i].node);
			i = j;
		}
		return result;
	}

	// ����node����nodeΪ��������ת��Ϊ������ʵ��ַ��������־�����еĿսڵ㡣
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

		unordered_map<string, vector<TreeNode*>> string2node;		// �ܺõ�һ��ʹ�� unordered_map ������
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