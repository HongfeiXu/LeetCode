#pragma once

/*

490. The Maze

Ref: https://leetcode.com/articles/the-maze/

There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by rolling up, down, left or right, but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.

Given the ball's start position, the destination and the maze, determine whether the ball could stop at the destination.

The maze is represented by a binary 2D array. 1 means the wall and 0 means the empty space. You may assume that the borders of the maze are all walls. The start and destination coordinates are represented by row and column indexes.

Example 1

Input 1: a maze represented by a 2D array

0 0 1 0 0
0 0 0 0 0
0 0 0 1 0
1 1 0 1 1
0 0 0 0 0

Input 2: start coordinate (rowStart, colStart) = (0, 4)
Input 3: destination coordinate (rowDest, colDest) = (4, 4)

Output: true
Explanation: One possible way is : left -> down -> left -> down -> right -> down -> right.
https://leetcode.com/static/images/problemset/maze_1_example_1.png

Example 2

Input 1: a maze represented by a 2D array

0 0 1 0 0
0 0 0 0 0
0 0 0 1 0
1 1 0 1 1
0 0 0 0 0

Input 2: start coordinate (rowStart, colStart) = (0, 4)
Input 3: destination coordinate (rowDest, colDest) = (3, 2)

Output: false
Explanation: There is no way for the ball to stop at the destination.
https://leetcode.com/static/images/problemset/maze_1_example_2.png

Note:
1. There is only one ball and one destination in the maze.
2. Both the ball and the destination exist on an empty space, and they will not be at the same position initially.
3. The given maze does not contain border (like the red rectangle in the example pictures), but you could assume the border of the maze are all walls.
4. The maze contains at least 2 empty spaces, and both the width and height of the maze won't exceed 100.

Approach:
Ref: https://leetcode.com/articles/the-maze/

DFS
dfs(maze, start, destination, visited)
从起始位置开始，有四个方向可以选择，使用深度搜索的方式

Approach_v2:
Ref: https://leetcode.com/articles/the-maze/
BFS

*/

#include <vector>
#include <utility>
#include <queue>

using namespace std;

class Solution {
public:
	int M, N;
	bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination)
	{
		M = maze.size();
		N = maze[0].size();
		vector<vector<bool>> visited(M, vector<bool>(N, false));	// 记录被访问了的节点，防止重复访问
		return(dfs(maze, { start[0], start[1] }, { destination[0], destination[1] }, visited));
	}

	vector<pair<int, int>> dirs { {0,-1}, {0, 1}, {-1, 0}, {1, 0} };
	bool dfs(vector<vector<int>>& maze, pair<int, int> start, pair<int, int> destination, vector<vector<bool>>& visited)
	{
		if (visited[start.first][start.second])
			return false;
		if (start == destination)
			return true;
		visited[start.first][start.second] = true;
		for (auto dir : dirs)
		{
			pair<int, int> end = start;
			// 滚球
			while (end.first >= 0 && end.first < M && end.second >= 0 && end.second < N && maze[end.first][end.second] != 1)
				end.first += dir.first, end.second += dir.second;
			end.first -= dir.first;
			end.second -= dir.second;

			if (dfs(maze, end, destination, visited))
				return true;
		}
		return false;
	}
};

class Solution_v2 {
public:
	int M, N;
	vector<pair<int, int>> dirs { { 0,-1 }, { 0, 1 }, { -1, 0 }, { 1, 0 } };

	bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination)
	{
		M = maze.size();
		N = maze[0].size();
		vector<vector<bool>> visited(M, vector<bool>(N, false));
		queue<pair<int, int>> Q;
		Q.push({ start[0], start[1] });
		visited[start[0]][start[1]] = true;
		while (!Q.empty())
		{
			pair<int, int> curr = Q.front();
			Q.pop();
			if (curr.first == destination[0] && curr.second == destination[1])
				return true;
			for (auto dir : dirs)
			{
				pair<int, int> next = curr;
				// 滚球
				while (next.first >= 0 && next.first < M && next.second >= 0 && next.second < N && maze[next.first][next.second] != 1)
				{
					next.first += dir.first;
					next.second += dir.second;
				}
				next.first -= dir.first;
				next.second -= dir.second;

				// 若未被访问，则入队
				if (!visited[next.first][next.second])
				{
					Q.push(next);
					visited[next.first][next.second] = true;
				}
			}
		}
		return false;
	}
};