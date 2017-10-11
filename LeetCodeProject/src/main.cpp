#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include "HelpFunc.h"

#include "ShortestUnsortedContinuousSubarray.h"

using namespace std;

int main()
{

	Solution solution;
	
	vector<int> input { 1,2,3,3,3 };

	cout << solution.findUnsortedSubarray(input) << endl;

	
	return 0;
}

/*

.Q..
...Q
Q...
..Q.

..Q.
Q...
...Q
.Q..

请按任意键继续. . .

*/