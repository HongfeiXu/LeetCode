#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include <iterator>
#include <chrono>

#include "HelpFunc.h"

#include "UniqueBinarySearchTrees.h"

using namespace std;

int main()
{
	Solution solu;

	auto t0 = chrono::high_resolution_clock::now();
	cout << solu.numTrees(4) << endl;
	auto t1 = chrono::high_resolution_clock::now();

	cout << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() << endl;
	
	return 0;
}
