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

按照 k 的大小进行升序排序，若 k 相同，则按照 h 值进行升序排序，得到需进一步处理的一组数据
每次从这组数据中拿出第一个数据(hi,ki)，插入到结果{(h0, k0), ..., {he, ke}}中，
	若 ki == ke，则由于 hi > he（前面的排序保证这一点），直接将(hi,ki)插到末尾位置
	若 ki != ke，则需要遍历结果{(h0, k0), ..., {he, ke}}，直到找到有 ki 个数字大于等于 hi的位置x位置，
	此时需要注意，若在该位置x后面的数据(ha, ka) 具有 ka == ki，则需要继续向后移动，直到末尾或者不等于数据不等于 ki，在该位置插入
	否则，此数据的插入会影响之前插入的(ha,ka)，使得 ka 小于实际上的值。

证明这样是对的？？

Approach_v2:
Ref: https://discuss.leetcode.com/topic/60417/java-solution-using-arrays-sort-and-insert-sorting-idea/2
Nasty!!!

关键是要想到，先插入身高较高的人，在插入身高矮的人，因为插入身高矮的人不会影响之前已经插入的身高高的人的 k 值。

1. 按照身高值 h 降序排序，若 h 相同，则按照 k 值升序排序
2. 按照类似插入排序的方式，调整位置，得到最终结果。
	对于当前带插入的人(hi, ki)，前面已经插入的人的身高都更高，或者相同身高但具有更小的 k 值，
	所以我们可以直接插入该人到“正确”的位置使得前面有 ki 个人具有更高或者相同的身高但更小的k值
	因为这个人的身高比其他人都矮，（或者相同但具有更大的k值，因此会被查到那些人的后面），因此他的插入不会影响到前面的人的 k 值，保证了最终插入的正确性。
	
	Ref: https://discuss.leetcode.com/topic/60470/6-lines-concise-c
	注：由于每个人在插入时，前面已经插入的人身高都更高或至少具有相同的身高但更小的k值，
	因此，我们可以直接按照这个人的k值作为插入位置直接插入，即得到了前面具有k个人身高高于或者等于这个人的结果。并且不会影响到后面的人。
	相对法一快很多

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
