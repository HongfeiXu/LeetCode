#pragma once

/*

447. Number of Boomerangs

Given n points in the plane that are all pairwise distinct, a "boomerang" is a tuple of points (i, j, k) such that the distance between i and j equals the distance between i and k (the order of the tuple matters).

Find the number of boomerangs. You may assume that n will be at most 500 and coordinates of points are all in the range [-10000, 10000] (inclusive).

Example:
Input:
[[0,0],[1,0],[2,0]]

Output:
2

Explanation:
The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]]

Approach:
为了避免求根运算，我们使用距离值得平方。
计算顶点之间的距离平方，按照距离平方建立hash表，表的每一行中存放具有相同距离的顶点对。
依次处理每一个表行，计数可以构成 Boomerang 的顶点元组数，由于重复计数的原因最后除以2为结果。
很慢，很原始的一种做法。
O(n^2)




*/

#include <vector>
#include <utility>
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution {
public:
	int numberOfBoomerangs(vector<pair<int, int>>& points)
	{
		unordered_map<int, vector<pair<int, int>>> um;	// 记录每个距离以及具有该距离值的顶点对
		int result = 0;

		// 计算所有顶点之间的距离值
		for (int i = 0; i < points.size(); ++i)
		{
			for (int j = 0; j < points.size(); ++j)
			{
				if (i != j)
				{
					int sd = squareDistance(points[i], points[j]);
					um[sd].push_back({ i, j });
				}
			}


		}
		//for (auto item : um)
		//{
		//	cout << item.first << ": ";
		//	for (auto pt_pair : item.second)
		//		cout << "(P" <<pt_pair.first << ", P" << pt_pair.second << ") ";
		//	cout << endl;
		//}

		for (const auto& line : um)
		{
			if (line.second.size() > 2)
			{
				for (int i = 0; i < line.second.size(); ++i)
				{
					for (int j = i + 1; j < line.second.size(); ++j)
					{
						// 若两个顶点对完全相同或者完全不同，跳过
						if((line.second[i].first == line.second[j].second && 
						    line.second[i].second == line.second[j].first) ||
						   (line.second[i].first != line.second[j].first &&
						    line.second[i].first != line.second[j].second &&
						    line.second[i].second != line.second[j].first &&
						    line.second[i].second != line.second[j].second))
							continue;
						// 若两个顶点对中有一个顶点相同，则可以构成 Boomerangs
						++result;
					}
				}
			}
		}
		return result / 2;
	}

	int squareDistance(const pair<int, int>& pointA, const pair<int, int>& pointB)
	{
		return (pointA.first - pointB.first) * (pointA.first - pointB.first) + (pointA.second - pointB.second) * (pointA.second - pointB.second);
	}
};


class Solution_v2 {
public:
	int numberOfBoomerangs(vector<pair<int, int>>& points)
	{
		int result = 0;

		// 计算所有顶点之间的距离值
		for (int i = 0; i < points.size(); ++i)
		{
			unordered_map<int, int> um;			// 存储当前顶点与其他顶点的距离值，以及具有该距离值的顶点的个数
			for (int j = 0; j < points.size(); ++j)
			{
				if(i == j)
					continue;
				int d = squareDistance(points[i], points[j]);
				++um[d];
			}
			for (auto item : um)
				result += item.second * (item.second - 1);	// 对于每一个相同的距离值d，如果有k个顶点与 points[i]的距离为d，则可以构成 k * (k-1) 个 Boomrangs（排列问题）
		}
		return result;
	}

	int squareDistance(const pair<int, int>& pointA, const pair<int, int>& pointB)
	{
		return (pointA.first - pointB.first) * (pointA.first - pointB.first) + (pointA.second - pointB.second) * (pointA.second - pointB.second);
	}
};