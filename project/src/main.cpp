#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include <iterator>
#include <chrono>
#include <utility>
#include <bitset>

#include "HelpFunc.h"

#include "BinaryTreeInorderTraversal.h"

using namespace std;

void midorder(TreeNode* root)
{
	if (root == nullptr)
		return;
	midorder(root->left);
	cout << root->val << " ";
	midorder(root->right);
}

int main()
{

	auto t0 = chrono::high_resolution_clock::now();

	Solution_v4 solu;

	TreeNode a(1);
	TreeNode b(2);
	TreeNode c(3);

	a.left = &b;
	a.right = &c;

	auto result = solu.inorderTraversal(&a);
	copy(result.begin(), result.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	auto t1 = chrono::high_resolution_clock::now();
	cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() << "ms" << endl;
	
	return 0;
}


