#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include <iterator>
#include <chrono>
#include <utility>
#include <bitset>

#include "HelpFunc.h"

#include "SlidingWindowMaximum.h"

using namespace std;

int main()
{
	Solution solu;

	auto t0 = chrono::high_resolution_clock::now();

	vector<int> nums {  8,3,4,2,2,5,-2,6,7};
	int k = 4;
	auto result = solu.maxSlidingWindow(nums, k);
	copy(result.begin(), result.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	auto t1 = chrono::high_resolution_clock::now();
	cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() << "ms" << endl;
	
	return 0;
}
