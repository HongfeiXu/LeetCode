#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include <iterator>
#include <chrono>
#include <utility>
#include <bitset>

#include "HelpFunc.h"

#include "TrappingRainWater.h"

using namespace std;

int main()
{
	Solution_v3 solu;

	auto t0 = chrono::high_resolution_clock::now();

	vector<int> input { 0,1,0,2,1,0,1,3,2,1,2,1 };
	cout << solu.trap(input) << endl;

	auto t1 = chrono::high_resolution_clock::now();
	cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() << "ms" << endl;
	
	return 0;
}
