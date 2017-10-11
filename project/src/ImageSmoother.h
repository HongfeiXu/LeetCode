#pragma once

/*

661. Image Smoother

Given a 2D integer matrix M representing the gray scale of an image, 
you need to design a smoother to make the gray scale of each cell 
becomes the average gray scale (rounding down) of all the 8 surrounding 
cells and itself. If a cell has less than 8 surrounding cells, then 
use as many as you can.

Example 1:
Input:
[[1,1,1],
 [1,0,1],
 [1,1,1]]
Output:
[[0, 0, 0],
 [0, 0, 0],
 [0, 0, 0]]
Explanation:
For the point (0,0), (0,2), (2,0), (2,2): floor(3/4) = floor(0.75) = 0
For the point (0,1), (1,0), (1,2), (2,1): floor(5/6) = floor(0.83333333) = 0
For the point (1,1): floor(8/9) = floor(0.88888889) = 0
Note:
The value in the given matrix is in the range of [0, 255].
The length and width of the given matrix are in the range of [1, 150].

Approach my:
for and for, and use mark[3][3] denote the all the 8 surrounding cells and itself's exists

Approach:
simple, direct, and more effective

*/

#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

class Solution {
private:
	int pointGrayScale(vector<vector<int>> & M, int a, int b, int i, int j)
	{
		assert(i < a && j < b);

		// use mark to denote the all the 8 surrounding cells and itself's exists
		// 1 exist, 0 do not exist
		// mark[1][1] always be 1
		
		vector<vector<int>> mark(3, vector<int>(3, 1));	// init mark 3x3 matrix, each elem is 1
		if (i == 0)
		{
			mark[0][0] = 0;
			mark[0][1] = 0;
			mark[0][2] = 0;
		}
		if (i == a-1)
		{
			mark[2][0] = 0;
			mark[2][1] = 0;
			mark[2][2] = 0;
		}
		if (j == 0)
		{
			mark[0][0] = 0;
			mark[1][0] = 0;
			mark[2][0] = 0;
		}
		if (j == b-1)
		{
			mark[0][2] = 0;
			mark[1][2] = 0;
			mark[2][2] = 0;
		}

		int total = 0;
		int cnt = 0;
		for (int m = 0; m < 3; m++)
		{
			for (int n = 0; n < 3; n++)
			{
				if (mark[m][n] == 1)
				{
					total += M[i + m - 1][j + n - 1];
					cnt++;
				}
			}
		}
		return total / cnt;
	}

public:
	vector<vector<int>> imageSmoother(vector<vector<int>>& M)
	{
		int a = M.size();
		if (a == 0)
			return M;
		int b = M[0].size();	// so the matrix M is a axb matrix

		vector<vector<int>> result(a, vector<int>(b, 0));	// result is a 3x4 matrix, each elem is 0

		for (int i = 0; i < a; i++)
		{
			for (int j = 0; j < b; j++)
			{
				result[i][j] = pointGrayScale(M, a, b, i, j);
			}
		}

		return result;
	}

	void pointGrayScale_v2(vector<vector<int>>& M, int a, int b, int i, int j, int &cnt, int &sum)
	{
		if (i < 0 || i >= a || j < 0 || j >= b)
		{
			return;
		}
		else
		{
			sum += M[i][j];
			cnt++;
		}
	}

	vector<vector<int>> imageSmoother_v2(vector<vector<int>>& M)
	{
		if (M.size() == 0)
			return M;
		int a = M.size();
		int b = M[0].size();
		vector<vector<int>> result(a, vector<int>(b, 0));
		for (int i = 0; i < a; i++)
		{
			for (int j = 0; j < b; j++)
			{
				int sum = 0;
				int cnt = 0;
				pointGrayScale_v2(M, a, b, i - 1, j - 1, cnt, sum);
				pointGrayScale_v2(M, a, b, i - 1, j - 0, cnt, sum);
				pointGrayScale_v2(M, a, b, i - 1, j + 1, cnt, sum);
				pointGrayScale_v2(M, a, b, i - 0, j - 1, cnt, sum);
				pointGrayScale_v2(M, a, b, i - 0, j - 0, cnt, sum);
				pointGrayScale_v2(M, a, b, i - 0, j + 1, cnt, sum);
				pointGrayScale_v2(M, a, b, i + 1, j - 1, cnt, sum);
				pointGrayScale_v2(M, a, b, i + 1, j - 0, cnt, sum);
				pointGrayScale_v2(M, a, b, i + 1, j + 1, cnt, sum);
				result[i][j] = sum / cnt;
			}
		}
		return result;
	}
};
