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
这题类似于 621. Task Scheduler
先安排出现次数最多的字母，然后将其他字母均匀插入其中，不过这里需要求出最终字符的一种可能排列情况（如果存在的话），如果不存在就返回空字符串。

先判断能否实现，如果不能直接返回空串
若能实现，进行结果的构造。
构造过程如下所示
aaaabbbbccd
=> ab*ab*ab* + ab				分块 + 尾部
=> abcabcab* + ab				依次均匀的插入 c c d
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
		int cnt_of_most = 0;	// 记录具有 most_letter 次出现的 letter 的个数，如 aaabbbc，i = 2
		while (cnt_of_each_letter[cnt_of_most].second == most_letter)
			++cnt_of_most;
		// 若具有 most_letter 次出现的 ltter 只有 1 个，则可能出现无法 reorganize 的情况，如果多于1个，则一定可以 reorganize
		if (cnt_of_most == 1)
		{
			int gap = most_letter - 1;
			int letter_left = S.size() - most_letter;
			if (gap > letter_left)	// 此时无法完成 reorganize
				return "";
		}

		vector<vector<char>> parts(most_letter - 1, vector<char>());	// 保存每个模块内的字符
		vector<char> tail;												// 保存尾部的字符
		for (int i = 0; i < cnt_of_most; ++i)
			tail.push_back(cnt_of_each_letter[i].first);
		for (int i = 0; i < parts.size(); ++i)							// 将出现次数最多的字符分别存入每个模块中，这些字符也即为尾部字符
			parts[i].insert(parts[i].end(), tail.begin(), tail.end());

		int curr_part_id = 0;	// 使用 curr_part_id 指向要添加字符的模块
								// 按数量从高到低遍历除了最多的字符之外的其他字符，依次平均的向各模块中添加字符
		for (int i = cnt_of_most; i < cnt_of_each_letter.size(); ++i)
		{
			for (int j = 0; j < cnt_of_each_letter[i].second; ++j)
			{
				parts[curr_part_id].push_back(cnt_of_each_letter[i].first);
				curr_part_id = (curr_part_id + 1) % (parts.size());
			}
		}

		// 将所有模块的字符一次连接在一起，并且加上 tail 中的字符
		string result;
		for (int i = 0; i < parts.size(); ++i)
			result.insert(result.end(), parts[i].begin(), parts[i].end());
		result.insert(result.end(), tail.begin(), tail.end());

		return result;
	}
};