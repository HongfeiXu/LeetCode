#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include <iterator>
#include <chrono>
#include <utility>
#include <bitset>

#include "HelpFunc.h"

#include "BestTimeToBuyAndSellStockIV.h"

using namespace std;

int main()
{
	Solution_v3 solu;

	auto t0 = chrono::high_resolution_clock::now();

	vector<int> input { 48,12,60,93,97,42,25,64,17,56,85,93,9,48,52,42,58,85,81,84,69,36,1,54,23,15,72,15,11,94 };
	cout << solu.maxProfit(11000000, input) << endl;

	auto t1 = chrono::high_resolution_clock::now();
	cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() << "ms" << endl;
	
	return 0;
}
