#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include <iterator>

#include "HelpFunc.h"

#include "PalindromePairs.h"

using namespace std;

int main()
{
	Solution_v2 solu;

	vector<string> input = { "abcd", "dcba", "lls", "s", "sssll" };
	auto result = solu.palindromePairs(input);

	for (auto item : result)
	{
		cout << item[0] << ", " << item[1] << endl;
	}

	return 0;
}
