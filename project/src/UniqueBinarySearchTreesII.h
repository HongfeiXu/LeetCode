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

递归实现 vector<TreeNode*> generateTree(int from, int to)
对于 1...n 中，以 i 为根节点时，
递归构造出所有可能 1...i-1 左子树，i...n 右子树，
然后任取一个左子树和一个右子树，再添加一个根节点，构造得到一个 1...n 的以 i 为根节点的 UBST。可见，与 96. Unique Binary Search Trees 的思想是相通的。

递归的返回条件是：
若 from > to，则返回一个空节点
若 from == to，则返回一个以 from 为值的叶子节点

当然，需要注意的是，这里由于构造左右子树的时候，没有进行复制操作，所以存在多个树共用相同节点的问题。

Approach:
MyApproach
DP
DP[n]:
for(int k = 1; k <=n ; ++k)
	DP[k-1] x DP[n-k]，对 DP[n-k] 中每一个树的节点值 + k
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
	// 对 from...to 构造出 UBST，返回所有 UBST
	vector<TreeNode*> generateTree(int from, int to)
	{
		vector<TreeNode*> ret;
		if (from > to)
			ret.push_back(nullptr);
		else if (from == to)
			ret.push_back(new TreeNode(from));
		else
		{
			// 以 i 为根节点
			for (int i = from; i <= to; ++i)
			{
				// 递归求解所有可能的左子树
				vector<TreeNode*> left_subtree = generateTree(from, i - 1);
				// 递归求解所有可能的右子树
				vector<TreeNode*> right_subtree = generateTree(i + 1, to);

				// 左子树x右子树，在加上根节点，构成一个 from...to 的UBST
				// 这里用两层循环实现了左右子树的组合。
				for (int j = 0; j < left_subtree.size(); ++j)
				{
					for (int k = 0; k < right_subtree.size(); ++k)
					{
						TreeNode* root = new TreeNode(i);
						//下面的操作会导致共用子树的情况。 如果要求没有共用子树的情况，则需要进行拷贝操作。
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
		// dp[i] 保存 1...i 所能形成的所有 UBST
		vector<vector<TreeNode*>> dp(n + 1, vector<TreeNode*>());
		// dp[0] 中包含一个空指针，用来生成空子树
		dp[0].push_back(nullptr);
		for (int i = 1; i <= n; ++i)
		{
			vector<TreeNode*> currI;
			// 以 j 为根节点
			for (int j = 1; j <= i; ++j)
			{
				for (int a = 0; a < dp[j - 1].size(); ++a)
				{
					for (int b = 0; b < dp[i - j].size(); ++b)
					{
						TreeNode* root = new TreeNode(j);
						TreeNode* left = copyAdd(dp[j - 1][a], 0);	 // 所有子树均由 dp 拷贝得到，不存在多个树共用相同节点的情况
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

	// 对 1...n 用 j 作为根节点，将其分为左子树(1..j-1)，右子树(n-j)
	// 左子树的所有可能情况为 dp[j-1]
	// 右子树需要对每个节点加入 offset，即 dp[n-j] + j(对每个树的每个节点 + j)
	// 使用前序遍历法遍历整个树
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