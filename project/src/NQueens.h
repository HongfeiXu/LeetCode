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

####################################################
Approach: 
Backtracking

由于每一行一定会有一个 queen。
我们的思路是，
依次安排第 i 行的 queen 到第 0,1,2,3,...,n-1 列，如果安排到第 j 列后，该 queen 与前 i-1 行的 queen 没有冲突，则继续向下递归安排第 i+1 行的 queen。

####################################################
Approach_v2:
Naive Algorithm
Generate all possible configurations of queens on board and print a configuration that satisfies the given constraints.
use std::next_permutation to get all configurations

Ref: http://blog.csdn.net/hackbuteer1/article/details/7462447

*/

#include <vector>
#include <string>
#include <algorithm>
#include "HelpFunc.h"

using namespace std;

class Solution {
private:
	// i: 正在处理第 i 行的 queen，寻找一个合适的列位置，不与前面的 i-1 行的 queen 冲突
	// matrix: 保存第 i 行的 queen 所在的列位置
	// n: queen 的个数
	// result: 保存结果
	void solveNQueensAux(int i, vector<int> &matrix, int n, vector<vector<string>> &result)
	{
		// 所有 queen 都找到了合适的位置（互相不会攻击）
		if (i == n)
		{
			vector<string> currSolution;
			matrixToVectorString(matrix, currSolution);
			result.push_back(currSolution);
			return;
		}

		// 将当前第i行的 queen 试探性的安排在第 0,1,2,...,n-1 列，如果合法，则递归向下安排第i-1行的queen
		for (int j = 0; j < n; j++)
		{
			matrix.push_back(j);
			if (isValid(matrix))	// Prune
				solveNQueensAux(i + 1, matrix, n, result);
			matrix.pop_back();		// backtrack
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
	void matrixToVectorString(const vector<int> &matrix, vector<string> &curr_result)
	{
		int len = matrix.size();
		for (unsigned i = 0; i < len; i++)
		{
			string curr_row(len, '.');
			curr_row[matrix[i]] = 'Q';
			curr_result.push_back(curr_row);
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

class Solution_v2 {
public:
	vector<vector<string>> solveNQueens(int n)
	{
		// 初始化 matrix 为 {0,1,2,3,...,n-1}，表示第 i 行的皇后在第 matrix[i] 列
		// 由于我们是用不同的数字初始化数组中的数字，因此任意两个皇后肯定不同列。
		// 我们只需要判断得到的每一个排列对应的八个皇后是不是在同一对角斜线上，
		vector<int> matrix(n);
		for (int i = 0; i < n; ++i)
			matrix[i] = i;

		vector<int> curr_result;
		vector<vector<string>> results;

		// 遍历所有 0,...,n-1 的排列，i0,i1,...,i_n-1，表示当前第 0 行的皇后在 i0 列，以此类推。
		// next_permutation 会得到下一个排列，并且当不存在升序的排列时
		do
		{
			if (isValid(matrix))
			{
				vector<string> curr_result_string;
				matrixToVecString(matrix, curr_result_string);
				results.push_back(curr_result_string);
			}
		} while (next_permutation(matrix.begin(), matrix.end()));
		return results;
	}

	// 判断任意两个皇后是否在同一正或副对角线上
	bool isValid(const vector<int>& matrix)
	{
		for (int i = 0; i < matrix.size() - 1; ++i)
		{
			for (int j = i + 1; j < matrix.size(); ++j)
			{
				if (matrix[j] - matrix[i] == j - i || matrix[j] - matrix[i] == i - j)
					return false;
			}
		}
		return true;
	}

	void matrixToVecString(const vector<int>& matrix, vector<string>& curr_result_string)
	{
		int len = matrix.size();
		for (int i = 0; i < len; ++i)
		{
			string curr_row(len, '.');
			curr_row[matrix[i]] = 'Q';
			curr_result_string.push_back(curr_row);
		}
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
