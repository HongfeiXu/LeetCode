#pragma once

/*

606. Construct String from Binary Tree

You need to construct a string consists of parenthesis and integers from a binary tree with the preorder traversing way.

The null node needs to be represented by empty parenthesis pair "()". 
And you need to omit all the empty parenthesis pairs that don't affect the one-to-one mapping relationship between the string and the original binary tree.

Example 1:
Input: Binary tree: [1,2,3,4]
       1
     /   \
    2     3
   /    
  4     

Output: "1(2(4))(3)"

Example 2:
Input: Binary tree: [1,2,3,null,4]
       1
     /   \
    2     3
     \  
      4 
Output: "1(2()(4))(3)"

Approach:

使用递归的方法，按照先序遍历的思想，每次访问一个节点，之后递归访问其左子树、右子树。
并且根据左右子树是否为空来选择添加括号。

*/

#include <string>
#include <iostream>

using namespace std;

class TreeNode {
public:
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) { }
};

class Solution {
public:
	string tree2str(TreeNode* t)
	{
		string result;
		tree2str_aux(t, result);
		return result;
	}

	void tree2str_aux(TreeNode* t, string& result)
	{
		
		if (t != nullptr)
		{
			string temp_number = to_string(t->val);
			result.append(temp_number);
		}
		else  // 若 t 为空，直接返回
		{
			return;
		}

		// 若左子树不空，则需要加括号，括号中放入左子树节点信息
		if (t->left != nullptr)
		{
			result.push_back('(');
			// 递归访问左子树
			tree2str_aux(t->left, result);
			result.push_back(')');

			// 若右子树也不为空，则需要添加括号，括号中放入右子树节点信息
			// 另外，在左子树不为空，右子树为空的情况下，不需要为右子树添加空的括号
			if (t->right != nullptr)
			{
				result.push_back('(');
				tree2str_aux(t->right, result);
				result.push_back(')');
			}
		}
		else	// 若左子树为空，则需要根据右子树的情况来确定是否需要为左子树添加空的括号
		{
			// 若右子树不为空，则需要添加左子树空括号，再对右子树进行访问
			// 若右子树为空，则都不添加左子树
			if (t->right != nullptr)
			{
				result.push_back('(');
				result.push_back(')');
				result.push_back('(');
				tree2str_aux(t->right, result);
				result.push_back(')');
			}
		}
	}
};