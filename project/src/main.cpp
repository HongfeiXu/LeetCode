#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include <iterator>
#include <chrono>

#include "HelpFunc.h"

#include "JumpGame.h"

using namespace std;

int main()
{
	Solution solu;

	auto t0 = chrono::high_resolution_clock::now();

	vector<int> input {  };
	cout << boolalpha << solu.canJump(input) << endl;

	auto t1 = chrono::high_resolution_clock::now();
	cout << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() << endl;
	
	return 0;
}
