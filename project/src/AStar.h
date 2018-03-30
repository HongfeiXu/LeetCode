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

// ����ͼ�е�ÿ���ڵ㣬�ؼ���Ϊ pos������
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

// �������������Ϊŷ����þ���Euclidean Distance
// TODO: ���������پ��룬�б�ѩ�����
double calculateHValue(const pair<int, int>& curr, const pair<int, int>& des)
{
	return sqrt((curr.first - des.first)*(curr.first - des.first) + (curr.second - des.second) * (curr.second - des.second));
}

// �� des ��ǰ���� parent_pos ȷ��·����ֱ������ src ֹͣ
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

// Ѱ���ھӽڵ㣬�������� block �Լ��Ƿ���λ�ã�����grid��λ�ã���
// ���⣬��������·����ǽͨ�������ŶԽ���ͨ����
// ���������� neighbor_nodes
void calculateNeighborNodes(const vector<vector<int>>& grid, const pair<int, int>& curr, vector<pair<int, int>>& neighbor_nodes)
{
	// ����8������ĺ�ѡ�ھӽڵ�
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
		// ע�⣬Ҫ���ж��Ƿ�Ϸ���Ȼ�����ж��Ƿ� block
		if(isInvalid(grid, candidates[i]) ||isBlocked(grid, candidates[i]))
			continue;
		neighbor_nodes.push_back(candidates[i]);
	}
}

// ���� curr �ڵ� ���ھӽڵ�֮��ľ��룬�Խ��߷�����ھӾ���Ϊ 1.4������Ϊ1.0
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

	// �洢��ǰ�Ѿ����ֵ�û�������Ľڵ㣬���� f ֵ �ͽڵ��� grid �е�λ��
	set<pair<double, pair<int, int>>> open_set;
	// �洢�Ѿ��������Ľڵ�
	set<pair<int, int>> closed_set;
	// �洢���нڵ����Ϣ�������ڵ�ĸ��ڵ�λ�ã��ڵ��g,h,fֵ��
	// Ĭ�Ͻڵ��g,f,hֵ��Ϊ FLT_MAX
	vector<vector<Node>> cells(m, vector<Node>(n));

	cells[src.first][src.second].g = 0;
	cells[src.first][src.second].h = calculateHValue(src, des);
	cells[src.first][src.second].f = cells[src.first][src.second].g + cells[src.first][src.second].h;
	open_set.insert({ cells[src.first][src.second].f, src });
	while (!open_set.empty())
	{
		pair<int, int> curr_pos = (*open_set.begin()).second;
		// �����ж�
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
			// neighbor ���� open_set �У�fֵδ�����£�
			if (cells[neighbor.first][neighbor.second].f == FLT_MAX)
			{
				cells[neighbor.first][neighbor.second].parent_pos = curr_pos;
				cells[neighbor.first][neighbor.second].g = cells[curr_pos.first][curr_pos.second].g + distanceBetween(curr_pos, neighbor);
				cells[neighbor.first][neighbor.second].h = calculateHValue(neighbor, des);
				cells[neighbor.first][neighbor.second].f = cells[neighbor.first][neighbor.second].g + cells[neighbor.first][neighbor.second].h;
				// �� neighbor ���� open_set ��
				open_set.insert({ cells[neighbor.first][neighbor.second].f, neighbor });
			}
			// neighbor �� open_set ��
			else
			{
				double tentative_g = cells[curr_pos.first][curr_pos.second].g + distanceBetween(curr_pos, neighbor);
				// �����curr��neighor�Ⱦ��и�С��gֵ������� neighbor �ĸ��ڵ㣬�Լ� g,h,f ֵ
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
