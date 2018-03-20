#pragma once

/*

51. N-Queens

Related Topics: Backtracking

The n-queens puzzle is the problem of placing n queens on an n��n chessboard such that no two queens attack each other.
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

����ÿһ��һ������һ�� queen��
���ǵ�˼·�ǣ�
���ΰ��ŵ� i �е� queen ���� 0,1,2,3,...,n-1 �У�������ŵ��� j �к󣬸� queen ��ǰ i-1 �е� queen û�г�ͻ����������µݹ鰲�ŵ� i+1 �е� queen��

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
	// i: ���ڴ���� i �е� queen��Ѱ��һ�����ʵ���λ�ã�����ǰ��� i-1 �е� queen ��ͻ
	// matrix: ����� i �е� queen ���ڵ���λ��
	// n: queen �ĸ���
	// result: ������
	void solveNQueensAux(int i, vector<int> &matrix, int n, vector<vector<string>> &result)
	{
		// ���� queen ���ҵ��˺��ʵ�λ�ã����಻�ṥ����
		if (i == n)
		{
			vector<string> currSolution;
			matrixToVectorString(matrix, currSolution);
			result.push_back(currSolution);
			return;
		}

		// ����ǰ��i�е� queen ��̽�Եİ����ڵ� 0,1,2,...,n-1 �У�����Ϸ�����ݹ����°��ŵ�i-1�е�queen
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
		// ��ʼ�� matrix Ϊ {0,1,2,3,...,n-1}����ʾ�� i �еĻʺ��ڵ� matrix[i] ��
		// �����������ò�ͬ�����ֳ�ʼ�������е����֣�������������ʺ�϶���ͬ�С�
		// ����ֻ��Ҫ�жϵõ���ÿһ�����ж�Ӧ�İ˸��ʺ��ǲ�����ͬһ�Խ�б���ϣ�
		vector<int> matrix(n);
		for (int i = 0; i < n; ++i)
			matrix[i] = i;

		vector<int> curr_result;
		vector<vector<string>> results;

		// �������� 0,...,n-1 �����У�i0,i1,...,i_n-1����ʾ��ǰ�� 0 �еĻʺ��� i0 �У��Դ����ơ�
		// next_permutation ��õ���һ�����У����ҵ����������������ʱ
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

	// �ж����������ʺ��Ƿ���ͬһ���򸱶Խ�����
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

�밴���������. . .

*/
