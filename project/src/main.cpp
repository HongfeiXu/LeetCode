#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include <iterator>
#include <chrono>
#include <utility>
#include <bitset>

#include "HelpFunc.h"

#include "TheMaze.h"

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

	Solution_v2 solu;
	vector<vector<int>> maze = 
	{
		{ 0, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 0 },
		{ 1, 1, 0, 1, 1 },
		{ 0, 0, 0, 0, 0 }
	};
	vector<int> start { 0, 4 };
	//vector<int> dest { 4,4 };
	vector<int> dest { 3,2 };

	cout << boolalpha << solu.hasPath(maze, start, dest) << endl;


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

