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

傻方法：扫描所有网格，对每个网格，找到其4个相邻网格的坐标，通过这4个坐标确定该网格的海岸线长度。

Approach_v2:

island
neighbor
return island * 4 -  2 * neighbor
从上到下，从左到右，扫描每个网格，若该网格为陆地，则 island++，并且看其右邻居、下邻居是否为陆地，若是则 ++neighbor

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

	// 对于每一块陆地，求它的海岸线长度
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