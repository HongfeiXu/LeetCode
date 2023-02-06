#pragma once

/*

733. Flood Fill

An image is represented by a 2-D array of integers, each integer representing the pixel value of the image (from 0 to 65535).

Given a coordinate (sr, sc) representing the starting pixel (row and column) of the flood fill, and a pixel value newColor, "flood fill" the image.

To perform a "flood fill", consider the starting pixel, plus any pixels connected 4-directionally to the starting pixel of the same color as the starting pixel, plus any pixels connected 4-directionally to those pixels (also with the same color as the starting pixel), and so on. Replace the color of all of the aforementioned pixels with the newColor.

At the end, return the modified image.

Example 1:
Input:
image = [[1,1,1],[1,1,0],[1,0,1]]
sr = 1, sc = 1, newColor = 2
Output: [[2,2,2],[2,2,0],[2,0,1]]
Explanation:
From the center of the image (with position (sr, sc) = (1, 1)), all pixels connected
by a path of the same color as the starting pixel are colored with the new color.
Note the bottom corner is not colored 2, because it is not 4-directionally connected
to the starting pixel.

Note:

The length of image and image[0] will be in the range [1, 50].
The given starting pixel will satisfy 0 <= sr < image.length and 0 <= sc < image[0].length.
The value of each color in image[i][j] and newColor will be an integer in [0, 65535].

Approach:
使用广度优先搜索

Approach:
使用深度优先搜索

*/

#include <vector>
#include <queue>
#include <utility>

using namespace std;

class Solution {
public:
	vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor)
	{
		int m = image.size();
		int n = image[0].size();
		int oldColor = image[sr][sc];

		vector<vector<bool>> already_walk(m);
		for (auto &line : already_walk)
		{
			line.assign(n, false);
		}

		// BFS
		using POSITION = pair<int, int>;
		queue<POSITION> Q;
		Q.push({ sr, sc });

		while (!Q.empty())
		{
			POSITION curr = Q.front();
			already_walk[curr.first][curr.second] = true;
			// 节点出队列时改变颜色
			image[curr.first][curr.second] = newColor;
			Q.pop();


			vector<POSITION> curr_neighbor;
			curr_neighbor.push_back(POSITION(curr.first - 1, curr.second));
			curr_neighbor.push_back(POSITION(curr.first + 1, curr.second));
			curr_neighbor.push_back(POSITION(curr.first, curr.second - 1));
			curr_neighbor.push_back(POSITION(curr.first, curr.second + 1));
			for (auto &neighbor : curr_neighbor)
			{
				// 边界合法性检测
				if (neighbor.first < 0 || neighbor.first >= m || neighbor.second < 0 || neighbor.second >= n)
					continue;

				// 避免重复访问一个位置
				if(already_walk[neighbor.first][neighbor.second])
					continue;

				// 如果边界合法，且没有被访问过，
				// 若颜色如果与初始颜色相同，标记该点为已经访问，则将该节点入队
				if (image[neighbor.first][neighbor.second] == oldColor)
				{
					already_walk[neighbor.first][neighbor.second] = true;
					Q.push({ neighbor.first, neighbor.second });
				}
			}
		}
		return image;
	}
};

class Solution_v2 {
public:
	vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor)
	{
		isSymmetric(image, sr, sc, image[sr][sc], newColor);
		return image;
	}

	// 此方法的问题在于，如果 oldColor 和 newColor 相同，则会无限递归下去。
	void isSymmetric(vector<vector<int>>& image, int r, int c, int oldColor, int newColor)
	{
		int R = image.size();
		int C = image[0].size();
		if (image[r][c] == oldColor)
		{
			image[r][c] = newColor;
			if (r >= 1) isSymmetric(image, r - 1, c, oldColor, newColor);
			if (r + 1 < R) isSymmetric(image, r + 1, c, oldColor, newColor);
			if (c >= 1) isSymmetric(image, r, c - 1, oldColor, newColor);
			if (c + 1 < C) isSymmetric(image, r, c + 1, oldColor, newColor);
		}
		
	}
};