#pragma once

/*

Just Implement A* Search Algorithm!

*/

#include <set>
#include <utility>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <unordered_set>
#include <cmath>

using namespace std;

// 代表图中的每个节点，关键字为 pos，用来
class Node {
public:
	pair<int, int> parent_pos;
	double g;
	double h;
	double f;
	Node() : parent_pos({ -1,-1}), g(FLT_MAX), h(FLT_MAX), f(FLT_MAX)
	{
	}
};

bool isInvalid(const vector<vector<int>>& grid, const pair<int, int>& pos)
{
	if (pos.first < 0 || pos.second < 0 || pos.first >= grid.size() || pos.second >= grid[0].size())
		return true;
	else
		return false;
}

bool isBlocked(const vector<vector<int>>& grid, const pair<int, int>& pos)
{
	return grid[pos.first][pos.second] == 0;
}

bool isDestination(const pair<int, int>& pos, const pair<int, int>& des)
{
	return pos == des;
}

// 这里的评估函数为欧几里得距离Euclidean Distance
// TODO: 尝试曼哈顿距离，切比雪夫距离
double calculateHValue(const pair<int, int>& curr, const pair<int, int>& des)
{
	return sqrt((curr.first - des.first)*(curr.first - des.first) + (curr.second - des.second) * (curr.second - des.second));
}

// 从 des 向前按照 parent_pos 确定路径，直到到达 src 停止
void reconstructPath(const vector<vector<Node>>& cells, const pair<int, int>& src, const pair<int, int>& des)
{
	vector<pair<int, int>> path;
	
	pair<int, int> temp = des;
	while (temp != src)
	{
		path.push_back(temp);
		temp = cells[temp.first][temp.second].parent_pos;
	}
	path.push_back(src);
	for (auto it = path.rbegin(); it != path.rend(); ++it)
	{
		if (it != path.rend() - 1)
			cout << "(" << it->first << ", " << it->second << ")->";
		else
			cout << "(" << it->first << ", " << it->second << ")";
	}
	cout << endl;
}

// 寻找邻居节点，（不包括 block 以及非法的位置（超出grid的位置））
// 另外，这里允许路径穿墙通过（沿着对角线通过）
// 不负责清理 neighbor_nodes
void calculateNeighborNodes(const vector<vector<int>>& grid, const pair<int, int>& curr, vector<pair<int, int>>& neighbor_nodes)
{
	// 保存8个方向的候选邻居节点
	vector<pair<int, int>> candidates(8, { 0,0 });
	candidates[0] = { curr.first - 1, curr.second };
	candidates[1] = { curr.first + 1, curr.second };
	candidates[2] = { curr.first, curr.second - 1 };
	candidates[3] = { curr.first, curr.second + 1 };
	candidates[4] = { curr.first - 1, curr.second - 1 };
	candidates[5] = { curr.first - 1, curr.second + 1 };
	candidates[6] = { curr.first + 1, curr.second - 1 };
	candidates[7] = { curr.first + 1, curr.second + 1 };
	for (int i = 0; i < 8; ++i)
	{
		// 注意，要先判断是否合法，然后在判断是否 block
		if(isInvalid(grid, candidates[i]) ||isBlocked(grid, candidates[i]))
			continue;
		neighbor_nodes.push_back(candidates[i]);
	}
}

// 计算 curr 节点 和邻居节点之间的距离，对角线方向的邻居距离为 1.4，其余为1.0
double distanceBetween(const pair<int, int>& curr, const pair<int, int>& neighbor)
{
	if (abs(curr.first - neighbor.first) == 1 && abs(curr.second - neighbor.second) == 1)
		return 1.4;
	else
		return 1.0;
}

void aStarSearch(const vector<vector<int>>& grid, const pair<int, int>& src, const pair<int, int>& des)
{
	if(grid.empty() || grid[0].empty())
	{
		cout << "grid invalid" << endl;
		return;
	}
	if (isInvalid(grid, src) || isInvalid(grid, des))
	{
		cout << "src or des invalid" << endl;
		return;
	}
	if (isBlocked(grid, src) || isBlocked(grid, des))
	{
		cout << "src or des blocked" << endl;
		return;
	}

	int m = grid.size(), n = grid[0].size();

	// 存储当前已经发现但没有评估的节点，包括 f 值 和节点在 grid 中的位置
	set<pair<double, pair<int, int>>> open_set;
	// 存储已经评估过的节点
	set<pair<int, int>> closed_set;
	// 存储所有节点的信息，包括节点的父节点位置，节点的g,h,f值。
	// 默认节点的g,f,h值均为 FLT_MAX
	vector<vector<Node>> cells(m, vector<Node>(n));

	cells[src.first][src.second].g = 0;
	cells[src.first][src.second].h = calculateHValue(src, des);
	cells[src.first][src.second].f = cells[src.first][src.second].g + cells[src.first][src.second].h;
	open_set.insert({ cells[src.first][src.second].f, src });
	while (!open_set.empty())
	{
		pair<int, int> curr_pos = (*open_set.begin()).second;
		// 出队判断
		if (curr_pos == des)
		{
			cout << "Reconstruct path: " << endl;
			reconstructPath(cells, src, des);
			return;
		}
		open_set.erase(open_set.begin());
		closed_set.insert(curr_pos);

		vector<pair<int, int>> neighbor_nodes;
		calculateNeighborNodes(grid, curr_pos, neighbor_nodes);
		for (const auto& neighbor : neighbor_nodes)
		{
			if (closed_set.find(neighbor) != closed_set.end())
				continue;
			// neighbor 不在 open_set 中（f值未被更新）
			if (cells[neighbor.first][neighbor.second].f == FLT_MAX)
			{
				cells[neighbor.first][neighbor.second].parent_pos = curr_pos;
				cells[neighbor.first][neighbor.second].g = cells[curr_pos.first][curr_pos.second].g + distanceBetween(curr_pos, neighbor);
				cells[neighbor.first][neighbor.second].h = calculateHValue(neighbor, des);
				cells[neighbor.first][neighbor.second].f = cells[neighbor.first][neighbor.second].g + cells[neighbor.first][neighbor.second].h;
				// 将 neighbor 加入 open_set 中
				open_set.insert({ cells[neighbor.first][neighbor.second].f, neighbor });
			}
			// neighbor 在 open_set 中
			else
			{
				double tentative_g = cells[curr_pos.first][curr_pos.second].g + distanceBetween(curr_pos, neighbor);
				// 如果从curr到neighor比具有更小的g值，则更新 neighbor 的父节点，以及 g,h,f 值
				if (tentative_g < cells[neighbor.first][neighbor.second].g)
				{
					cells[neighbor.first][neighbor.second].parent_pos = curr_pos;
					cells[neighbor.first][neighbor.second].g = tentative_g;
					cells[neighbor.first][neighbor.second].h = calculateHValue(neighbor, des);
					cells[neighbor.first][neighbor.second].f = cells[neighbor.first][neighbor.second].g + cells[neighbor.first][neighbor.second].h;
				}
			}
		}
	}
	cout << "Rescontruct path failed!" << endl;
}

void test()
{
	/* Description of the Grid-
	1--> The cell is not blocked
	0--> The cell is blocked    */
	vector<vector<int>> grid = 
	{
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
		{ 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
		{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
		{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
		{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } 
	};

	aStarSearch(grid, { 8, 0 }, { 0 ,0 });
}
