#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include "HelpFunc.h"

#include "RepeatedStringMatch.h"

using namespace std;

int main()
{

	Solution solution;
	
	string A("ba");
	string B("ab");

	cout << solution.repeatedStringMatch_v3(A, B) << endl;
	
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