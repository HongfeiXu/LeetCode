#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include <iterator>
#include <chrono>
#include <utility>
#include <bitset>

#include "HelpFunc.h"

#include "ConvertSortedArrayToBinarySearchTree.h"

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

	Solution solu;

	vector<int> input { -10,-3,0,5,9 };
	TreeNode* root = solu.sortedArrayToBST(input);
	midorder(root);
	cout << endl;
	auto t1 = chrono::high_resolution_clock::now();
	cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() << "ms" << endl;
	
	return 0;
}


