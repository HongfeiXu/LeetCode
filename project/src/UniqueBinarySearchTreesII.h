#pragma once

/*

95. Unique Binary Search Trees II

Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3


Approach:

Ref: https://leetcode.com/problems/unique-binary-search-trees-ii/discuss/31563

�ݹ�ʵ�� vector<TreeNode*> generateTree(int from, int to)
���� 1...n �У��� i Ϊ���ڵ�ʱ��
�ݹ鹹������п��� 1...i-1 ��������i...n ��������
Ȼ����ȡһ����������һ���������������һ�����ڵ㣬����õ�һ�� 1...n ���� i Ϊ���ڵ�� UBST���ɼ����� 96. Unique Binary Search Trees ��˼������ͨ�ġ�

�ݹ�ķ��������ǣ�
�� from > to���򷵻�һ���սڵ�
�� from == to���򷵻�һ���� from Ϊֵ��Ҷ�ӽڵ�

��Ȼ����Ҫע����ǣ��������ڹ�������������ʱ��û�н��и��Ʋ��������Դ��ڶ����������ͬ�ڵ�����⡣

Approach:
MyApproach
DP
DP[n]:
for(int k = 1; k <=n ; ++k)
	DP[k-1] x DP[n-k]���� DP[n-k] ��ÿһ�����Ľڵ�ֵ + k
	new TreeNode, DP[n].push_back()


*/

#include <vector>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) { }
};

class Solution {
public:
	// �� from...to ����� UBST���������� UBST
	vector<TreeNode*> generateTree(int from, int to)
	{
		vector<TreeNode*> ret;
		if (from > to)
			ret.push_back(nullptr);
		else if (from == to)
			ret.push_back(new TreeNode(from));
		else
		{
			// �� i Ϊ���ڵ�
			for (int i = from; i <= to; ++i)
			{
				// �ݹ�������п��ܵ�������
				vector<TreeNode*> left_subtree = generateTree(from, i - 1);
				// �ݹ�������п��ܵ�������
				vector<TreeNode*> right_subtree = generateTree(i + 1, to);

				// ������x���������ڼ��ϸ��ڵ㣬����һ�� from...to ��UBST
				// ����������ѭ��ʵ����������������ϡ�
				for (int j = 0; j < left_subtree.size(); ++j)
				{
					for (int k = 0; k < right_subtree.size(); ++k)
					{
						TreeNode* root = new TreeNode(i);
						//����Ĳ����ᵼ�¹�������������� ���Ҫ��û�й������������������Ҫ���п���������
						root->left = left_subtree[j];
						root->right = right_subtree[k];
						ret.push_back(root);
					}
				}
			}
		}
		return ret;
	}

	vector<TreeNode*> generateTrees(int n)
	{
		if (n == 0)
			return vector<TreeNode*>();
		return generateTree(1, n);
	}
};


class Solution_v2 {
public:
	vector<TreeNode*> generateTrees(int n)
	{
		if (n == 0)
			return vector<TreeNode*>();
		// dp[i] ���� 1...i �����γɵ����� UBST
		vector<vector<TreeNode*>> dp(n + 1, vector<TreeNode*>());
		// dp[0] �а���һ����ָ�룬�������ɿ�����
		dp[0].push_back(nullptr);
		for (int i = 1; i <= n; ++i)
		{
			vector<TreeNode*> currI;
			// �� j Ϊ���ڵ�
			for (int j = 1; j <= i; ++j)
			{
				for (int a = 0; a < dp[j - 1].size(); ++a)
				{
					for (int b = 0; b < dp[i - j].size(); ++b)
					{
						TreeNode* root = new TreeNode(j);
						TreeNode* left = copyAdd(dp[j - 1][a], 0);	 // ������������ dp �����õ��������ڶ����������ͬ�ڵ�����
						TreeNode* right = copyAdd(dp[i - j][b], j);	
						root->left = left;
						root->right = right;
						currI.push_back(root);
					}
				}
			}
			dp[i] = currI;
		}
		return dp[n];
	}

	// �� 1...n �� j ��Ϊ���ڵ㣬�����Ϊ������(1..j-1)��������(n-j)
	// �����������п������Ϊ dp[j-1]
	// ��������Ҫ��ÿ���ڵ���� offset���� dp[n-j] + j(��ÿ������ÿ���ڵ� + j)
	// ʹ��ǰ�����������������
	TreeNode* copyAdd(TreeNode* ori_tree, int k)
	{
		if (ori_tree == nullptr)
			return nullptr;

		TreeNode* root = new TreeNode(ori_tree->val + k);
		if (ori_tree->left != nullptr)
			root->left = copyAdd(ori_tree->left, k);
		if (ori_tree->right != nullptr)
			root->right = copyAdd(ori_tree->right, k);
		return root;
	}
};