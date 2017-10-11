#pragma once

/*

51. N-Queens

Related Topics: Backtracking

The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.
Given an integer n, return all distinct solutions to the n-queens puzzle.
Each solution contains a distinct board configuration of the n-queens' placement,
where 'Q' and '.' both indicate a queen and an empty space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:

[
[".Q..",  // Solution 1
"...Q",
"Q...",
"..Q."],

["..Q.",  // Solution 2
"Q...",
"...Q",
".Q.."]
]

Approach: Backtracking

*/

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
private:
	void solveNQueensAux(int i, vector<int> &matrix, int n, vector<vector<string>> &result)
	{
		if (i == n)
		{
			if (isValid(matrix))
			{
				vector<string> currSolution;
				matrixToVectorString(matrix, currSolution);
				result.push_back(currSolution);
			}
			return;
		}

		for (int j = 0; j < n; j++)
		{
			matrix.push_back(j);
			if (isValid(matrix))	// Prune
				solveNQueensAux(i + 1, matrix, n, result);
			matrix.pop_back();
		}
	}

	// judge the last row is not conflicate with other rows
	bool isValid(vector<int> matrix)
	{
		int row = matrix.size() - 1;
		int col = matrix[row];
		for (int i = 0; i < row; i++)
		{
			int row1 = i;
			int col1 = matrix[i];
			if (col == col1)		// differernt column
				return false;
			if (col - col1 == row - row1)	// different down diagonal
				return false;
			if (col - col1 == row1 - row)	// different up diagonal
				return false;
		}
		return true;
	}

	// transform a valid matrix to vector<string>
	void matrixToVectorString(const vector<int> &matrix, vector<string> &currSolution)
	{
		int dimension = matrix.size();
		for (unsigned i = 0; i < dimension; i++)
		{
			string temp_string(dimension, '.');
			temp_string[matrix[i]] = 'Q';
			currSolution.push_back(temp_string);
		}
	}

public:
	vector<vector<string>> solveNQueens(int n)
	{
		vector<vector<string>> result;
		vector<int> matrix;
		solveNQueensAux(0, matrix, n, result);

		return result;
	}
};

/*

int main()
{
	Solution solution;

	vector<vector<string>> result;

	result = solution.solveNQueens(4);

	for (int i = 0; i < result.size(); i++)
	{
		PrintVector(result[i], '\n');
		cout << endl;
	}

	return 0;
}

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
