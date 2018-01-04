#pragma once

/*

434. Number of Segments in a String

Count the number of segments in a string, where a segment is defined to be a contiguous sequence of non-space characters.

Please note that the string does not contain any non-printable characters.

Example:

Input: "Hello, my name is John"
Output: 5


*/

#include <string>
#include <sstream>

using namespace std;

class Solution {
public:
	int countSegments(string s)
	{
		int result = 0;
		stringstream ss;
		ss << s;
		string temp;
		while (ss >> temp)
			++result;
		return result;
	}
};