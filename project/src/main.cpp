#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include "HelpFunc.h"

#include "ArrayPartitionI.h"

using namespace std;

int main()
{

	Solution solution;
	
	vector<int> input { 1,4,3,2 };

	cout << solution.arrayPairSum_Bucket(input) << endl;



	
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