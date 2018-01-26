#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include <iterator>
#include <chrono>
#include <utility>
#include <bitset>

#include "HelpFunc.h"

#include "OnesAndZeros.h"

using namespace std;

int main()
{
	Solution_v4 solu;

	auto t0 = chrono::high_resolution_clock::now();

	vector<string> input = { "10", "0001", "111001", "1", "0" };
	int m = 5, n = 3;
	cout << solu.findMaxForm(input, m, n) << endl;

	auto t1 = chrono::high_resolution_clock::now();
	cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() << "ms" << endl;
	
	return 0;
}
