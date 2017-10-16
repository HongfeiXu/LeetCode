#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include "HelpFunc.h"

#include "NextClosestTime.h"

using namespace std;

int main()
{

	Solution solution;
	
	string input("19:34");

	cout << solution.nextClosestTime_v2(input) << endl;
	
	return 0;
}
