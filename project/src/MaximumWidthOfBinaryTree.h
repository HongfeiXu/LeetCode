#pragma once

/*

662. Maximum Width of Binary Tree

Given a binary tree, write a function to get the maximum width of the given tree. 
The width of a tree is the maximum width among all levels. 
The binary tree has the same structure as a full binary tree, but some nodes are null.

The width of one level is defined as the length between the end-nodes 
(the leftmost and right most non-null nodes in the level, where the null nodes between the end-nodes are also counted into the length calculation.

Example 1:
Input: 

           1
         /   \
        3     2
       / \     \  
      5   3     9 

Output: 4
Explanation: The maximum width existing in the third level with the length 4 (5,3,null,9).
Example 2:
Input: 

          1
         /  
        3    
       / \       
      5   3     

Output: 2
Explanation: The maximum width existing in the third level with the length 2 (5,3).
Example 3:
Input: 

          1
         / \
        3   2 
       /        
      5      

Output: 2
Explanation: The maximum width existing in the second level with the length 2 (3,2).
Example 4:
Input: 

          1
         / \
        3   2
       /     \  
      5       9 
     /         \
    6           7
Output: 8
Explanation:The maximum width existing in the fourth level with the length 8 (6,null,null,null,null,null,null,7).

Note: Answer will in the range of 32-bit signed integer.

Approach:
��α�����BFS��

���ڶ��У� �����б��浱ǰ��Ľڵ�
���⣬�½�һ�����У������б��浱ǰ��ڵ��ڶ�Ӧ�����������е��±�
�Ƚ�ÿһ��ĵ�һ���ڵ�����һ���ڵ���±�֮��Ĳ�ֵ��ȡ����Ϊ���

Time: O(n)
Space: O(n)

Approach v2:
DFS
��dfsʱ�����ݵ�ǰ�ڵ�Ĳ������Լ���ǰ�ڵ���±꣨�����������еģ������ҵ�һ�˷��ʵ���ǰ��Ľڵ�Ϊ����ڵ�
֮��
for each node, a candidate width is index - leftmost_index[layer] + 1
we take the maximum of the candidate answers

*/

#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
	int widthOfBinaryTree(TreeNode* root)
	{
		if (root == nullptr)
			return 0;
		int result = 0;
		queue<TreeNode*> q;
		queue<int> index_queue;		// ���浱ǰ��ڵ��ڶ�Ӧ�����������е��±꣬�Դ˶��� index_ queue �ĸ���Ӧ���� q �Ĳ�������һ��
		q.push(root);
		index_queue.push(1);
		while (!q.empty())
		{
			int cnt_of_layer = q.size();
			int width_of_layer = index_queue.back() - index_queue.front() + 1;	// ���㵱ǰ��Ŀ��
			for (int i = 0; i < cnt_of_layer; ++i)
			{
				TreeNode* temp_node = q.front();
				q.pop();
				int temp_index = index_queue.front();
				index_queue.pop();
				if (temp_node->left != nullptr)
				{
					q.push(temp_node->left);
					index_queue.push(temp_index * 2);		// ���ӵ��±�Ϊ���ڵ��±�Ķ���
				}
				if (temp_node->right != nullptr)
				{
					q.push(temp_node->right);
					index_queue.push(temp_index * 2 + 1);	// �Һ��ӵ��±�Ϊ���ڵ��±�Ķ���+1
				}
			}
			// ���� result ֵΪ���Ŀ��
			result = max(width_of_layer, result);
		}
		return result;
	}
};

class Solution_v2 {
public:
	vector<int> leftmost_index;
	int ans;
	int widthOfBinaryTree(TreeNode* root)
	{
		ans = 0;
		dfs(root, 0, 1);
		return ans;
	}

	void dfs(TreeNode* root, int layer, int index)
	{
		if (root == nullptr)
			return;
		// ��ǰ���һ�α����ʣ�����ʵ��Ľڵ�Ϊ��ǰ�������ڵ�
		if (leftmost_index.size() == layer)		
			leftmost_index.push_back(index);
		// for each node, a candidate width is index - leftmost_index[layer] + 1
		// we take the maximum of the candidate answers
		ans = max(index - leftmost_index[layer] + 1, ans);	
		dfs(root->left, layer + 1, 2 * index);
		dfs(root->right, layer + 1, 2 * index + 1);
	}
};

