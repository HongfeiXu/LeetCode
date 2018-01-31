# Binary Tree

```c++
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
```


## 二叉树的中序遍历

### 1. Recursive Approach

Time: O(n)
Space: Worst case O(n), average case O(log(n))，注：这里空间复杂度不包括用来保存遍历结果所需的空间。（下同）

```c++
class Solution {
public:
	vector<int> inorderTraversal(TreeNode* root)
	{
		vector<int> result;
		inorder(root, result);
		return result;
	}

	void inorder(TreeNode* root, vector<int>& result)
	{
		if (root == nullptr)
			return;
		if (root->left != nullptr)
			inorder(root->left, result);
		result.push_back(root->val);
		if (root->right != nullptr)
			inorder(root->right, result);
	}
};
```

### 2. Iterating method using Stack 

Time: O(n)
Space: O(n)

```c++
class Solution_v2 {
public:
	vector<int> inorderTraversal(TreeNode* root)
	{
		vector<int> result;
		stack<TreeNode*> S;
		TreeNode* p = root;
		while (p != nullptr || !S.empty())
		{
			// 从当前节点开始，沿左孩子方向入栈，直到最左孩子
			while (p != nullptr)
			{
				S.push(p);
				p = p->left;
			}
			// 出栈得到最左孩子
			p = S.top();
			S.pop();
			// 访问节点
			result.push_back(p->val);
			// 转向该最左孩子的右子树
			p = p->right;
		}
		return result;
	}
};
```

### 3. Morris Traversal

In this method, we have to use a new data structure-Threaded Binary Tree（线索二叉树）, and the strategy is as follows:

Step 1: Initialize current as root   
Step 2: While current is not NULL,   
If current has left child   
1. In current's left subtree, make current the right child of the rightmost node   
2. Go to this left child, i.e., current = current.left   

Else   
1. Add current’s value   
2. Go to the right, i.e., current = current.right   

Time: O(n) 乍一看是 O(nlogn)，但是由于每条边最多访问两次，时间复杂度为 O(n)
Space: O(1)

```c++
class Solution_v3 {
public:
	vector<int> inorderTraversal(TreeNode* root)
	{
		vector<int> result;
		TreeNode* p = root;
		while (p != nullptr)
		{
			// 若左子树不为空，进行二叉树的变形操作
			if (p->left != nullptr)
			{
				TreeNode* q = p->left;		// q 保存当前节点 p 的左子树的最右节点
				while (q->right != nullptr)
					q = q->right;
				q->right = p;				// 将 p 以及其右子树，作为 q 的右子树
				TreeNode* temp = p->left;
				p->left = nullptr;			// 将 p 的左孩子设为空，防止无限循环
				p = temp;					// p 更新为新的根节点
			}
			// 若左子树为空，进行访问操作
			else
			{
				result.push_back(p->val);	// 访问当前节点
				p = p->right;				// p 更新为当前节点的右孩子
			}
		}
		return result;
	}
};
```

上述这种实现方法，会改变树的结构，下面的方法则通过修正中序遍历前驱节点的右孩子的方式最终使得树的结构与初始时相同。   
在一些要求不得改变二树结构的情形下使用。

```c++
class Solution_v4 {
public:
	vector<int> inorderTraversal(TreeNode* root)
	{
		vector<int> result;
		TreeNode* curr = root;
		while (curr != nullptr)
		{
			if (curr->left == nullptr)
			{
				result.push_back(curr->val);
				curr = curr->right;
			}
			else
			{
				// Find the inorder predecessor of current
				TreeNode* pre = curr->left;
				while (pre->right != nullptr && pre->right != curr)	// 注意这里与 Approach_v3 的不同
					pre = pre->right;
				// pre->right == nullptr，说明左子树的最右节点还没有把当前节点作为右孩子
				// Make current as right child of its inorder predecessor
				if (pre->right == nullptr)
				{
					pre->right = curr;
					curr = curr->left;
				}
				// pre->right == curr，说明左子树的最右节点的右孩子已经是当前节点了，需要把它重置回去（因为pre显然在当前节点之前被访问了），即将右孩子设为空。
				// 同时，直接访问当前节点，因为在当前节点之前的节点已经被访问过了。
				// Revert the changes made in if part to restore the original
				// tree i.e., fix the right child of predecssor
				else
				{
					pre->right = nullptr;
					result.push_back(curr->val);
					curr = curr->right;
				}
			}
		}
		return result;
	}
};

```


1. https://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion-and-without-stack/   
2. http://www.cnblogs.com/AnnieKim/archive/2013/06/15/morristraversal.html   
3. https://leetcode.com/problems/binary-tree-inorder-traversal/solution/


## 二叉树的层次遍历


### 题目叙述：
```
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]
```

### 1. BFS（基于队列）

```c++
class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root)
	{
		vector<vector<int>> result;
		if (root == nullptr)
			return result;
		queue<TreeNode*> Q;		// 保存一层节点
		Q.push(root);
		while (!Q.empty())
		{
			int size = Q.size();
			vector<int> curr_layer;
			// 出队当前一层节点，并添加下一层节点
			for (int i = 0; i < size; ++i)
			{
				TreeNode* temp = Q.front();
				Q.pop();
				curr_layer.push_back(temp->val);
				if (temp->left != nullptr)
					Q.push(temp->left);
				if (temp->right != nullptr)
					Q.push(temp->right);
			}
			result.push_back(curr_layer);
		}
		return result;
	}
};
```

### 2. DFS（将层数作为参数传递）

```c++
class Solution_v2 {
public:
	vector<vector<int>> result;

	vector<vector<int>> levelOrder(TreeNode* root)
	{
		dfs(root, 0);
		return result;
	}

	void dfs(TreeNode* root, int level)
	{
		if (root == nullptr)
			return;
		if (level == result.size())				// The level does not exist in output
			result.push_back(vector<int>());	// Create a new level
		result[level].push_back(root->val);		// Add the current value to its level
		dfs(root->left, level + 1);				// Go to the next level
		dfs(root->right, level + 1);
	}
};
```
