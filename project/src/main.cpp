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

#include "EvaluateDivision.h"

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

	vector<pair<string, string>> equations = { {"f", "c"}, {"c", "a"}, {"c", "b"}, {"b", "a"}, { "b", "d" }, {"d", "e"}, {"d", "g"}, {"o", "p"} };
	vector<double> values = { 2,3,3,1,4,2,1, 3 };
	vector<pair<string, string>> queries = { {"f", "e"}, {"e", "f"}, {"c", "d"}, {"d", "c"}, {"c", "o"} };

	auto result = solu.calcEquation(equations, values, queries);
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
请按任意键继续. . .

*/

