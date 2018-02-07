#pragma once

/*

529. Minesweeper

You are given a 2D char matrix representing the game board. 'M' represents an unrevealed mine, 'E' represents an unrevealed empty square, 'B' represents a revealed blank square that has no adjacent (above, below, left, right, and all 4 diagonals) mines, digit ('1' to '8') represents how many mines are adjacent to this revealed square, and finally 'X' represents a revealed mine.

Now given the next click position (row and column indices) among all the unrevealed squares ('M' or 'E'), return the board after revealing this position according to the following rules:

1. If a mine ('M') is revealed, then the game is over - change it to 'X'.
2. If an empty square ('E') with no adjacent mines is revealed, then change it to revealed blank ('B') and all of its adjacent unrevealed squares should be revealed recursively.
3. If an empty square ('E') with at least one adjacent mine is revealed, then change it to a digit ('1' to '8') representing the number of adjacent mines.
4. Return the board when no more squares will be revealed.

Example 1:
Input:

[['E', 'E', 'E', 'E', 'E'],
['E', 'E', 'M', 'E', 'E'],
['E', 'E', 'E', 'E', 'E'],
['E', 'E', 'E', 'E', 'E']]

Click : [3,0]

Output:

[['B', '1', 'E', '1', 'B'],
['B', '1', 'M', '1', 'B'],
['B', '1', '1', '1', 'B'],
['B', 'B', 'B', 'B', 'B']]

Explanation:
https://leetcode.com/static/images/problemset/minesweeper_example_1.png

Example 2:
Input:

[['B', '1', 'E', '1', 'B'],
['B', '1', 'M', '1', 'B'],
['B', '1', '1', '1', 'B'],
['B', 'B', 'B', 'B', 'B']]

Click : [1,2]

Output:

[['B', '1', 'E', '1', 'B'],
['B', '1', 'X', '1', 'B'],
['B', '1', '1', '1', 'B'],
['B', 'B', 'B', 'B', 'B']]

Explanation:
https://leetcode.com/static/images/problemset/minesweeper_example_2.png

Note:
The range of the input matrix's height and width is [1,50].
The click position will only be an unrevealed square ('M' or 'E'), which also means the input board contains at least one clickable square.
The input board won't be a stage when game is over (some mines have been revealed).
For simplicity, not mentioned rules should be ignored in this problem. For example, you don't need to reveal all the unrevealed mines when the game is over, consider any cases that you will win the game or flag any squares.

Approach:
If click position is a 'M'
If click position is a 'E'

BFS

*/

#include <vector>
#include <unordered_set>
#include <utility>
#include <queue>

using namespace std;

class Solution {
public:
	vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click)
	{
		if (board[click[0]][click[1]] == 'M')
		{
			board[click[0]][click[1]] = 'X';
			return board;
		}

		// board[click[0]][click[1]] == 'E'
		queue<pair<int, int>> Q;
		int height = board.size();
		int width = board[0].size();
		vector<vector<bool>> visited(height, vector<bool>(width, false));
		Q.push({ click[0], click[1] });
		visited[click[0]][click[1]] = true;
		while (!Q.empty())
		{
			pair<int, int> curr_pos = Q.front();
			Q.pop();
			int curr_num_of_adjacent_mine = numOfAdjacentMine(board, curr_pos.first, curr_pos.second);
			if (curr_num_of_adjacent_mine > 0)
				board[curr_pos.first][curr_pos.second] = curr_num_of_adjacent_mine + '0';
			// curr_num_of_adjacent == 0
			else
			{
				board[curr_pos.first][curr_pos.second] = 'B';
				vector<pair<int, int>> candidate_pos;
				candidate_pos.push_back({ curr_pos.first - 1, curr_pos.second - 1 });
				candidate_pos.push_back({ curr_pos.first - 1, curr_pos.second });
				candidate_pos.push_back({ curr_pos.first - 1, curr_pos.second + 1 });
				candidate_pos.push_back({ curr_pos.first, curr_pos.second - 1 });
				candidate_pos.push_back({ curr_pos.first, curr_pos.second + 1 });
				candidate_pos.push_back({ curr_pos.first + 1, curr_pos.second - 1 });
				candidate_pos.push_back({ curr_pos.first + 1, curr_pos.second });
				candidate_pos.push_back({ curr_pos.first + 1, curr_pos.second + 1 });
				for (int i = 0; i < candidate_pos.size(); ++i)
				{
					if (candidate_pos[i].first >= 0 && candidate_pos[i].first <= height - 1 &&
						candidate_pos[i].second >= 0 && candidate_pos[i].second <= width - 1)
					{
						if (visited[candidate_pos[i].first][candidate_pos[i].second] == false)
						{
							visited[candidate_pos[i].first][candidate_pos[i].second] = true;
							Q.push(candidate_pos[i]);
						}
					}
				}
			}
		}
		return board;
	}

	// 相邻的八个空格中炸弹个数
	int numOfAdjacentMine(vector<vector<char>>& board, int pos_x, int pos_y)
	{
		int height = board.size();
		int width = board[0].size();
		int result = 0;
		if (pos_x > 0 && board[pos_x - 1][pos_y] == 'M')
			++result;
		if (pos_x < height - 1 && board[pos_x + 1][pos_y] == 'M')
			++result;
		if (pos_y > 0 && board[pos_x][pos_y - 1] == 'M')
			++result;
		if (pos_y < width - 1 && board[pos_x][pos_y + 1] == 'M')
			++result;
		if (pos_x > 0 && pos_y > 0 && board[pos_x - 1][pos_y - 1] == 'M')
			++result;
		if (pos_x > 0 && pos_y < width - 1 && board[pos_x - 1][pos_y + 1] == 'M')
			++result;
		if (pos_x < height - 1 && pos_y > 0 && board[pos_x + 1][pos_y - 1] == 'M')
			++result;
		if (pos_x < height - 1 && pos_y < width - 1 && board[pos_x + 1][pos_y + 1] == 'M')
			++result;
		return result;
	}
};