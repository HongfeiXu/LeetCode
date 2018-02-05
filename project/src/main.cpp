#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include <iterator>
#include <chrono>
#include <utility>
#include <bitset>

#include "HelpFunc.h"

#include "BinaryTreeZigzagLevelOrderTraversal.h"

using namespace std;

//void midorder(TreeNode* root)
//{
//	if (root == nullptr)
//		return;
//	midorder(root->left);
//	cout << root->val << " ";
//	midorder(root->right);
//}

int main()
{

	auto t0 = chrono::high_resolution_clock::now();

	Solution solu;
	
	TreeNode a(1);
	TreeNode b(2);
	TreeNode c(3);
	TreeNode d(4);
	TreeNode e(5);
	a.left = &b;
	a.right = &c;
	b.left = &d;
	b.right = &e;

	auto result = solu.zigzagLevelOrder(&a);
	for (int i = 0; i < result.size(); ++i)
	{
		copy(result[i].begin(), result[i].end(), ostream_iterator<int>(cout, " "));
		cout << endl;
	}


	auto t1 = chrono::high_resolution_clock::now();
	cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() << "ms" << endl;
	
	return 0;
}

/*

0000 1000 1100 1200 1201 1202 0202
Time: 238ms
请按任意键继续. . .

*/

