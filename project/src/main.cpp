#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include <iterator>

#include "HelpFunc.h"

#include "LongestWordInDictionary.h"

using namespace std;

int main()
{
	Solution solu;

	vector<string> input { "w", "wo", "wor", "worl", "world" };
	cout << solu.longestWord(input) << endl;

	return 0;
}
