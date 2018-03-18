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

�� vector<string> row_string ������ת�����ÿһ�����ַ�����
��������ֻ��Ҫ˳�����ԭ�����ַ������� row ��ȷ����ǰ���µ�λ�ã�����ǰ�ַ����뵽 row_string[row] ��ĩβ��
������ down �����Ʋ����ķ������»������ϣ����Ӷ����� row ֵ�������� ++row������ --row����
�ҵ� row == 0 ʱ������ down Ϊ true����ʾ���£�
�� row == numRows - 1 ʱ������ down Ϊ false����ʾ���ϡ�

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