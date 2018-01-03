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

ʹ�õݹ�ķ������������������˼�룬ÿ�η���һ���ڵ㣬֮��ݹ����������������������
���Ҹ������������Ƿ�Ϊ����ѡ��������š�

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
		else  // �� t Ϊ�գ�ֱ�ӷ���
		{
			return;
		}

		// �����������գ�����Ҫ�����ţ������з����������ڵ���Ϣ
		if (t->left != nullptr)
		{
			result.push_back('(');
			// �ݹ����������
			tree2str_aux(t->left, result);
			result.push_back(')');

			// ��������Ҳ��Ϊ�գ�����Ҫ������ţ������з����������ڵ���Ϣ
			// ���⣬����������Ϊ�գ�������Ϊ�յ�����£�����ҪΪ��������ӿյ�����
			if (t->right != nullptr)
			{
				result.push_back('(');
				tree2str_aux(t->right, result);
				result.push_back(')');
			}
		}
		else	// ��������Ϊ�գ�����Ҫ�����������������ȷ���Ƿ���ҪΪ��������ӿյ�����
		{
			// ����������Ϊ�գ�����Ҫ��������������ţ��ٶ����������з���
			// ��������Ϊ�գ��򶼲����������
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