#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include <iterator>
#include <chrono>

#include "HelpFunc.h"

#include "GasStation.h"

using namespace std;

int main()
{
	Solution solu;

	auto t0 = chrono::high_resolution_clock::now();

	vector<int> gas { 4,3,2,5,7,0,1 };
	vector<int> cost { 3,2,5,3,6,2,1 };
	cout << solu.canCompleteCircuit(gas, cost) << endl;


	auto t1 = chrono::high_resolution_clock::now();
	cout << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() << endl;
	
	return 0;
}
