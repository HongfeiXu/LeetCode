#pragma once

/*

6. ZigZag Conversion

The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"
Write the code that will take a string and make this conversion given a number of rows:

string convert(string text, int nRows);
convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".

Approach:

用 vector<string> row_string 来保存转换后的每一个行字符串。
这里我们只需要顺序遍历原来的字符串，用 row 来确定当前更新的位置，将当前字符加入到 row_string[row] 的末尾，
并且用 down 来控制操作的方向（向下或者向上），从而更新 row 值。（向下 ++row，向上 --row）。
且当 row == 0 时，更新 down 为 true，表示向下；
当 row == numRows - 1 时，更新 down 为 false，表示向上。

Time: O(s.size())
Space: O(s.size())

*/

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	string convert(string s, int numRows)
	{
		if (numRows == 1)
			return s;
		vector<string> row_string(numRows, "");
		bool down = true;
		int row = 0;
		for (int i = 0; i < s.size(); ++i)
		{
			row_string[row].push_back(s[i]);
			// update direction
			if (row == 0)
				down = true;
			else if (row == numRows - 1)
				down = false;
			// update row
			if (down)
				++row;
			else
				--row;
		}
		string result = "";
		for (int i = 0; i < numRows; ++i)
			result.append(row_string[i]);
		return result;
	}
};