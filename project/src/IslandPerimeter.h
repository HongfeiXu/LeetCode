#pragma once

/*

463. Island Perimeter

You are given a map in form of a two-dimensional integer grid where 1 represents land and 0 represents water. 
Grid cells are connected horizontally/vertically (not diagonally). The grid is completely surrounded by water, 
and there is exactly one island (i.e., one or more connected land cells). The island doesn't have "lakes" 
(water inside that isn't connected to the water around the island). One cell is a square with side length 1. 
The grid is rectangular, width and height don't exceed 100. Determine the perimeter of the island.

Example:

[[0,1,0,0],
 [1,1,1,0],
 [0,1,0,0],
 [1,1,0,0]]

Answer: 16
Explanation: The perimeter is the 16 yellow stripes in the image below:

https://leetcode.com/static/images/problemset/island.png

Approach:

ɵ������ɨ���������񣬶�ÿ�������ҵ���4��������������꣬ͨ����4������ȷ��������ĺ����߳��ȡ�

Approach_v2:

island
neighbor
return island * 4 -  2 * neighbor
���ϵ��£������ң�ɨ��ÿ��������������Ϊ½�أ��� island++�����ҿ������ھӡ����ھ��Ƿ�Ϊ½�أ������� ++neighbor

*/

#include <vector>
#include <utility>

using namespace std;

class Solution {
public:
	int islandPerimeter(vector<vector<int>>& grid)
	{
		if (grid.empty())
			return 0;

		int row = grid.size();
		int column = grid[0].size();
		int result = 0;
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < column; ++j)
			{
				if (grid[i][j] == 1)
					result += oneGridPerimeter(grid, i, j);
			}
		}

		return result;
	}

	// ����ÿһ��½�أ������ĺ����߳���
	int oneGridPerimeter(vector<vector<int>>& grid, int i, int j)
	{
		int result = 0;

		int row = grid.size();
		int column = grid[0].size();

		vector<pair<int, int>> neighbor_grids;
		neighbor_grids.push_back({ i - 1, j });
		neighbor_grids.push_back({ i + 1, j });
		neighbor_grids.push_back({ i, j - 1 });
		neighbor_grids.push_back({ i, j + 1 });
		
		for (auto& item : neighbor_grids)
		{
			if (item.first == -1)
				++result;
			if (item.first == row)
				++result;
			if (item.second == -1)
				++result;
			if (item.second == column)
				++result;

			if (item.first != -1 && item.first != row && item.second != -1 && item.second != column)
			{
				if (grid[item.first][item.second] == 0)
					++result;
			}
		}

		return result;
	}
};

class Solution_v2 {
public:
	int islandPerimeter(vector<vector<int>>& grid)
	{
		if (grid.empty())
			return 0;
		int row = grid.size();
		int column = grid[0].size();
		int island = 0;
		int neighbor = 0;

		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < column; ++j)
			{
				if (grid[i][j] == 1)
				{
					++island;
					if (i < row - 1 && grid[i + 1][j] == 1)
						++neighbor;
					if (j < column - 1 && grid[i][j + 1] == 1)
						++neighbor;
				}
			}
		}
		return island * 4 - neighbor * 2;
	}
};