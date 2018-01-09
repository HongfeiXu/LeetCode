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
Ϊ�˱���������㣬����ʹ�þ���ֵ��ƽ����
���㶥��֮��ľ���ƽ�������վ���ƽ������hash�����ÿһ���д�ž�����ͬ����Ķ���ԡ�
���δ���ÿһ�����У��������Թ��� Boomerang �Ķ���Ԫ�����������ظ�������ԭ��������2Ϊ�����
��������ԭʼ��һ��������
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
		unordered_map<int, vector<pair<int, int>>> um;	// ��¼ÿ�������Լ����иþ���ֵ�Ķ����
		int result = 0;

		// �������ж���֮��ľ���ֵ
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
						// �������������ȫ��ͬ������ȫ��ͬ������
						if((line.second[i].first == line.second[j].second && 
						    line.second[i].second == line.second[j].first) ||
						   (line.second[i].first != line.second[j].first &&
						    line.second[i].first != line.second[j].second &&
						    line.second[i].second != line.second[j].first &&
						    line.second[i].second != line.second[j].second))
							continue;
						// ���������������һ��������ͬ������Թ��� Boomerangs
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

		// �������ж���֮��ľ���ֵ
		for (int i = 0; i < points.size(); ++i)
		{
			unordered_map<int, int> um;			// �洢��ǰ��������������ľ���ֵ���Լ����иþ���ֵ�Ķ���ĸ���
			for (int j = 0; j < points.size(); ++j)
			{
				if(i == j)
					continue;
				int d = squareDistance(points[i], points[j]);
				++um[d];
			}
			for (auto item : um)
				result += item.second * (item.second - 1);	// ����ÿһ����ͬ�ľ���ֵd�������k�������� points[i]�ľ���Ϊd������Թ��� k * (k-1) �� Boomrangs���������⣩
		}
		return result;
	}

	int squareDistance(const pair<int, int>& pointA, const pair<int, int>& pointB)
	{
		return (pointA.first - pointB.first) * (pointA.first - pointB.first) + (pointA.second - pointB.second) * (pointA.second - pointB.second);
	}
};