#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include <iterator>
#include <chrono>
#include <utility>
#include <bitset>
#include <unordered_map>
#include <cassert>

#include "HelpFunc.h"

#include "ContainerWithMostWater.h"

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


	auto t1 = chrono::high_resolution_clock::now();
	cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() << "ms" << endl;
	
	return 0;
}

/*

[]
5
5

0000 1000 1100 1200 1201 1202 0202
Time: 238ms
请按任意键继续. . .

*/

