# Binary Tree

```c++
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
```


## ���������������

### 1. Recursive Approach

Time: O(n)
Space: Worst case O(n), average case O(log(n))��ע������ռ临�ӶȲ�����������������������Ŀռ䡣����ͬ��

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
			// �ӵ�ǰ�ڵ㿪ʼ�������ӷ�����ջ��ֱ��������
			while (p != nullptr)
			{
				S.push(p);
				p = p->left;
			}
			// ��ջ�õ�������
			p = S.top();
			S.pop();
			// ���ʽڵ�
			result.push_back(p->val);
			// ת��������ӵ�������
			p = p->right;
		}
		return result;
	}
};
```

### 3. Morris Traversal

In this method, we have to use a new data structure-Threaded Binary Tree��������������, and the strategy is as follows:

Step 1: Initialize current as root   
Step 2: While current is not NULL,   
If current has left child   
1. In current's left subtree, make current the right child of the rightmost node   
2. Go to this left child, i.e., current = current.left   

Else   
1. Add current��s value   
2. Go to the right, i.e., current = current.right   

Time: O(n) էһ���� O(nlogn)����������ÿ�������������Σ�ʱ�临�Ӷ�Ϊ O(n)
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
			// ����������Ϊ�գ����ж������ı��β���
			if (p->left != nullptr)
			{
				TreeNode* q = p->left;		// q ���浱ǰ�ڵ� p �������������ҽڵ�
				while (q->right != nullptr)
					q = q->right;
				q->right = p;				// �� p �Լ�������������Ϊ q ��������
				TreeNode* temp = p->left;
				p->left = nullptr;			// �� p ��������Ϊ�գ���ֹ����ѭ��
				p = temp;					// p ����Ϊ�µĸ��ڵ�
			}
			// ��������Ϊ�գ����з��ʲ���
			else
			{
				result.push_back(p->val);	// ���ʵ�ǰ�ڵ�
				p = p->right;				// p ����Ϊ��ǰ�ڵ���Һ���
			}
		}
		return result;
	}
};
```

��������ʵ�ַ�������ı����Ľṹ������ķ�����ͨ�������������ǰ���ڵ���Һ��ӵķ�ʽ����ʹ�����Ľṹ���ʼʱ��ͬ��   
��һЩҪ�󲻵øı�����ṹ��������ʹ�á�

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
				while (pre->right != nullptr && pre->right != curr)	// ע�������� Approach_v3 �Ĳ�ͬ
					pre = pre->right;
				// pre->right == nullptr��˵�������������ҽڵ㻹û�аѵ�ǰ�ڵ���Ϊ�Һ���
				// Make current as right child of its inorder predecessor
				if (pre->right == nullptr)
				{
					pre->right = curr;
					curr = curr->left;
				}
				// pre->right == curr��˵�������������ҽڵ���Һ����Ѿ��ǵ�ǰ�ڵ��ˣ���Ҫ�������û�ȥ����Ϊpre��Ȼ�ڵ�ǰ�ڵ�֮ǰ�������ˣ��������Һ�����Ϊ�ա�
				// ͬʱ��ֱ�ӷ��ʵ�ǰ�ڵ㣬��Ϊ�ڵ�ǰ�ڵ�֮ǰ�Ľڵ��Ѿ������ʹ��ˡ�
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


## �������Ĳ�α���


### ��Ŀ������
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

### 1. BFS�����ڶ��У�

```c++
class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root)
	{
		vector<vector<int>> result;
		if (root == nullptr)
			return result;
		queue<TreeNode*> Q;		// ����һ��ڵ�
		Q.push(root);
		while (!Q.empty())
		{
			int size = Q.size();
			vector<int> curr_layer;
			// ���ӵ�ǰһ��ڵ㣬�������һ��ڵ�
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

### 2. DFS����������Ϊ�������ݣ�

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
