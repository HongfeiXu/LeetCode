#pragma once

/*

406. Queue Reconstruction by Height

Suppose you have a random list of people standing in a queue. 
Each person is described by a pair of integers (h, k), 
where h is the height of the person and k is the number of people 
in front of this person who have a height greater than or equal to h. 
Write an algorithm to reconstruct the queue.

Note:
The number of people is less than 1,100.

Example

Input:
[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]

Output:
[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]

Approach:

���� k �Ĵ�С�������������� k ��ͬ������ h ֵ�����������򣬵õ����һ�������һ������
ÿ�δ������������ó���һ������(hi,ki)�����뵽���{(h0, k0), ..., {he, ke}}�У�
	�� ki == ke�������� hi > he��ǰ�������֤��һ�㣩��ֱ�ӽ�(hi,ki)�嵽ĩβλ��
	�� ki != ke������Ҫ�������{(h0, k0), ..., {he, ke}}��ֱ���ҵ��� ki �����ִ��ڵ��� hi��λ��xλ�ã�
	��ʱ��Ҫע�⣬���ڸ�λ��x���������(ha, ka) ���� ka == ki������Ҫ��������ƶ���ֱ��ĩβ���߲��������ݲ����� ki���ڸ�λ�ò���
	���򣬴����ݵĲ����Ӱ��֮ǰ�����(ha,ka)��ʹ�� ka С��ʵ���ϵ�ֵ��

֤�������ǶԵģ���

Approach_v2:
Ref: https://discuss.leetcode.com/topic/60417/java-solution-using-arrays-sort-and-insert-sorting-idea/2
Nasty!!!

�ؼ���Ҫ�뵽���Ȳ�����߽ϸߵ��ˣ��ڲ�����߰����ˣ���Ϊ������߰����˲���Ӱ��֮ǰ�Ѿ��������߸ߵ��˵� k ֵ��

1. �������ֵ h ���������� h ��ͬ������ k ֵ��������
2. �������Ʋ�������ķ�ʽ������λ�ã��õ����ս����
	���ڵ�ǰ���������(hi, ki)��ǰ���Ѿ�������˵���߶����ߣ�������ͬ��ߵ����и�С�� k ֵ��
	�������ǿ���ֱ�Ӳ�����˵�����ȷ����λ��ʹ��ǰ���� ki ���˾��и��߻�����ͬ����ߵ���С��kֵ
	��Ϊ����˵���߱������˶�������������ͬ�����и����kֵ����˻ᱻ�鵽��Щ�˵ĺ��棩��������Ĳ��벻��Ӱ�쵽ǰ����˵� k ֵ����֤�����ղ������ȷ�ԡ�
	
	Ref: https://discuss.leetcode.com/topic/60470/6-lines-concise-c
	ע������ÿ�����ڲ���ʱ��ǰ���Ѿ����������߶����߻����پ�����ͬ����ߵ���С��kֵ��
	��ˣ����ǿ���ֱ�Ӱ�������˵�kֵ��Ϊ����λ��ֱ�Ӳ��룬���õ���ǰ�����k������߸��ڻ��ߵ�������˵Ľ�������Ҳ���Ӱ�쵽������ˡ�
	��Է�һ��ܶ�

*/

#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;

class Solution {
public:
	vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people)
	{
		vector<pair<int, int>> result;
		if (people.empty())
			return result;
		int len = people.size();
		auto cmp = [](const pair<int, int>& p1, const pair<int, int>& p2)
		{ return p1.second < p2.second || (p1.second == p2.second && p1.first < p2.first); };
		sort(people.begin(), people.end(), cmp);

		result.push_back(people[0]);;
		for (int i = 1; i < len; ++i)
		{
			if (people[i].second == result.back().second)
				result.push_back(people[i]);
			else
			{
				int j = 0;
				int cnt = people[i].second;
				for (; j < i; ++j)
				{
					if (result[j].first >= people[i].first)
						--cnt;
					if(cnt == 0)
						break;
				}
				int x = j + 1;
				while (x < result.size() && result[x].second == people[i].second)
					++x;
				result.insert(result.begin() + x, people[i]);
			}
		}
		return result;
	}
};

class Solution_v2 {
public:
	vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people)
	{
		vector<pair<int, int>> result;
		auto cmp = [](const pair<int, int>& p1, const pair<int, int>& p2)
		{
			return p1.first > p2.first || (p1.first == p2.first && p1.second < p2.second);
		};
		sort(people.begin(), people.end(), cmp);
		for (int i = 0; i < people.size(); ++i)
			result.insert(result.begin() + people[i].second, people[i]);
		return result;
	}
};
