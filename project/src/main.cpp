#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include <iterator>

#include "HelpFunc.h"

#include "MinCostClimbingStairs.h"

using namespace std;

int main()
{
	Solution solu;

	//vector<int> input { 1,100,1,1,1,100,1,1,100,1 };
	vector<int> input { 10,15,20 };
	cout << solu.minCostClimbingStairs(input) << endl;

	return 0;
}
