#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include <iterator>
#include <chrono>
#include <utility>
#include <bitset>
#include <unordered_map>

#include "HelpFunc.h"

#include "CourseScheduleII.h"

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

	vector < pair<int, int > > edges;
	int numCourses = 2;
	edges.push_back({ 1,0 });
	
	auto result = solu.findOrder(numCourses, edges);
	
	PrintVector(result);


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
�밴���������. . .

*/

