#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include <iterator>
#include <chrono>
#include <utility>
#include <bitset>

#include "HelpFunc.h"

#include "SymmetricTree.h"

using namespace std;

int main()
{
	Solution_v2 solu;

	auto t0 = chrono::high_resolution_clock::now();

	TreeNode a(1);
	TreeNode b(2);
	TreeNode c(2);
	TreeNode d(3);
	a.left = &b;
	a.right = &c;
	b.left = &d;

	cout << boolalpha << solu.isSymmetric(&a) << endl;
	
	auto t1 = chrono::high_resolution_clock::now();
	cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() << "ms" << endl;
	
	return 0;
}
