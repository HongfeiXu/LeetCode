#pragma once

/*

767. Reorganize String

Given a string S, check if the letters can be rearranged so that two characters that are adjacent to each other are not the same.

If possible, output any possible result.  If not possible, return the empty string.

Example 1:

Input: S = "aab"
Output: "aba"
Example 2:

Input: S = "aaab"
Output: ""
Note:

S will consist of lowercase letters and have length in range [1, 500].

Approach:
���������� 621. Task Scheduler
�Ȱ��ų��ִ���������ĸ��Ȼ��������ĸ���Ȳ������У�����������Ҫ��������ַ���һ�ֿ������������������ڵĻ�������������ھͷ��ؿ��ַ�����

���ж��ܷ�ʵ�֣��������ֱ�ӷ��ؿմ�
����ʵ�֣����н���Ĺ��졣
�������������ʾ
aaaabbbbccd
=> ab*ab*ab* + ab				�ֿ� + β��
=> abcabcab* + ab				���ξ��ȵĲ��� c c d
=> abcabcabd + ab
=> bcabcabdab

Approach Sort by Count
Ref: https://leetcode.com/problems/reorganize-string/solution/
TODO...

Approach Greedy with Heap
Ref: https://leetcode.com/problems/reorganize-string/solution/
TODO...

*/

#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>

using namespace std;

class Solution {
public:
	string reorganizeString(string S)
	{
		int len = S.size();
		if (len == 0)
			return "";
		else if (len == 1)
			return S;

		vector<pair<char, int>> cnt_of_each_letter;
		for (int cnt_of_most = 0; cnt_of_most < 26; ++cnt_of_most)
			cnt_of_each_letter.push_back({ 'a' + cnt_of_most, 0 });
		for (auto c : S)
			++cnt_of_each_letter[c - 'a'].second;
		auto cmp = [](const pair<char, int>& lhs, const pair<char, int>& rhs) { return lhs.second > rhs.second; };
		sort(cnt_of_each_letter.begin(), cnt_of_each_letter.end(), cmp);

		int most_letter = cnt_of_each_letter[0].second;
		int cnt_of_most = 0;	// ��¼���� most_letter �γ��ֵ� letter �ĸ������� aaabbbc��i = 2
		while (cnt_of_each_letter[cnt_of_most].second == most_letter)
			++cnt_of_most;
		// ������ most_letter �γ��ֵ� ltter ֻ�� 1 ��������ܳ����޷� reorganize ��������������1������һ������ reorganize
		if (cnt_of_most == 1)
		{
			int gap = most_letter - 1;
			int letter_left = S.size() - most_letter;
			if (gap > letter_left)	// ��ʱ�޷���� reorganize
				return "";
		}

		vector<vector<char>> parts(most_letter - 1, vector<char>());	// ����ÿ��ģ���ڵ��ַ�
		vector<char> tail;												// ����β�����ַ�
		for (int i = 0; i < cnt_of_most; ++i)
			tail.push_back(cnt_of_each_letter[i].first);
		for (int i = 0; i < parts.size(); ++i)							// �����ִ��������ַ��ֱ����ÿ��ģ���У���Щ�ַ�Ҳ��Ϊβ���ַ�
			parts[i].insert(parts[i].end(), tail.begin(), tail.end());

		int curr_part_id = 0;	// ʹ�� curr_part_id ָ��Ҫ����ַ���ģ��
								// �������Ӹߵ��ͱ������������ַ�֮��������ַ�������ƽ�������ģ��������ַ�
		for (int i = cnt_of_most; i < cnt_of_each_letter.size(); ++i)
		{
			for (int j = 0; j < cnt_of_each_letter[i].second; ++j)
			{
				parts[curr_part_id].push_back(cnt_of_each_letter[i].first);
				curr_part_id = (curr_part_id + 1) % (parts.size());
			}
		}

		// ������ģ����ַ�һ��������һ�𣬲��Ҽ��� tail �е��ַ�
		string result;
		for (int i = 0; i < parts.size(); ++i)
			result.insert(result.end(), parts[i].begin(), parts[i].end());
		result.insert(result.end(), tail.begin(), tail.end());

		return result;
	}
};