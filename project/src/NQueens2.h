#pragma once

/*

52. N-Queens II

Related Topics: Backtracking

Follow up for N-Queens problem.

Now, instead outputting board configurations, return the total number of distinct solutions.

Approach: Backtracking

*/

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
private:
	int cnt = 0;

	bool hasSolutionAux(int i, vector<int> &matrix, int n)
	{
		if (i == n)
		{
			if (isValid(matrix))
				return true;
			else
				return false;
		}
		for (int j = 0; j < n; j++)
		{
			matrix.push_back(j);
			if (isValid(matrix))	// Prune
			{
				if (hasSolutionAux(i + 1, matrix, n))
					return true;
			}
			matrix.pop_back();
		}
		return false;
	}

	void totalNQueensAux(int i, vector<int> &matrix, int n)
	{
		if (i == n)
		{
			if (isValid(matrix))	// Prune
				cnt++;
			return;
		}

		for (int j = 0; j < n; j++)
		{
			matrix.push_back(j);
			if (isValid(matrix))
				totalNQueensAux(i + 1, matrix, n);
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

public:
	bool hasSolution(int n)
	{
		vector<int> matrix;		// matrix[i] stores the i th row's Queen's column number.
								// i from 0 to n-1
		return hasSolutionAux(0, matrix, n);
	}

	int totalNQueens(int n)
	{
		vector<int> matrix;
		totalNQueensAux(0, matrix, n);

		return cnt;
	}
};