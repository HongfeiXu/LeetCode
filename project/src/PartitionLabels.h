#pragma once

/*

763. Partition Labels

A string S of lowercase letters is given. We want to partition this 
string into as many parts as possible so that each letter appears 
in at most one part, and return a list of integers representing the size of these parts.

Example 1:

Input: S = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits S into less parts.

Note:

S will have length in range [1, 500].
S will consist of lowercase letters ('a' to 'z') only.

Approach:

ababcbacadefegdehijhklij

a_first = 0, a_last = 8
1~7中每个字符的出现范围都在 0~8 内，则 0~8 为一个 partition，长为9

d_first = 9, d_last = 14
9~14中
e_first = 10, e_last = 15， 15 > 14
9~15中每个字符的出现范围都在 9~15 内，则 9~15 为一个 partition，长为7

h_first = 16, h_last = 19
16~19中
i_first = 17, i_last = 22, 22 > 19
16~22中
j_first = 18, i_last = 23, 23 > 22
16~23中每个字符的出现范围都在 16~23 内，则 16~23 为一个 partition，长为8

Worst Time: O(n^2) abcdefghijk 时会遇到最坏的时间复杂度
这里需要对那些没有确定范围的字符进行搜索操作，还是比较耗时的，我们可以考虑使用 Sliding Window 方式来进行处理。

Approach_v2
Sliding Window

The idea is to use sliding window to add all the chars which are not exhausted yet
use a unordered_map 保存每个字符及出现个数
use a unordered_set to know if current char is new or we have seen it before in the current window
if we find new char c, we insert it into the unordered_set, and --unordered_map[c]
if we exhausted all char c, unordered_map[c] == 0, then, we erase it from unordered_set
if unordered_set become empty, it means that current window is a partition, add it to the result vector and update the window

O(n)

*/

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Solution {
public:
	vector<int> partitionLabels(string S)
	{
		vector<int> result;
		if (S.empty())
			return result;
		int len = S.size();
		int curr_first = 0, curr_last = 0;
		// 每次迭代确定一个 partition，
		while (curr_first != len)
		{
			unordered_set<char> visited;	// 保存已经确定了范围的字符（范围：第一次出现的位置到最后一次出现的位置）
			curr_last = S.find_last_of(S[curr_first]);
			if (curr_last == curr_first)
			{
				result.push_back(1);
				curr_first = curr_last + 1;
			}
			else
			{
				visited.insert(S[curr_first]);
				for (int j = curr_first + 1; j < curr_last; ++j)
				{
					// 若在 curr_first ~ curr_last 范围内的字符，没有确定范围，则看最后一次出现的位置是否在范围之内，若不在，则需要扩大范围
					if (visited.find(S[j]) == visited.end())
					{
						visited.insert(S[j]);
						int temp_last = S.find_last_of(S[j]);
						// 若 S[j] 出现的最后一个位置在当前范围之外，则更新 curr_last，扩大范围
						if (temp_last > curr_last)
							curr_last = temp_last;
					}
				}
				// 保存当前找到的一个 partition 的长度
				result.push_back(curr_last - curr_first + 1);
				// 更新 curr_first，确定下一个 partition
				curr_first = curr_last + 1;
			}
		}
		return result;
	}
};

class Solution_v2 {
public:
	vector<int> partitionLabels(string S)
	{
		vector<int> result;
		if (S.empty())
			return result;
		unordered_map<char, int> char2int;
		for (auto c : S)
			++char2int[c];

		int left = 0, right = 0;
		unordered_set<char> visited;	// 保存当前窗口中的未被遍历完的字母
		while (right != S.length())
		{
			char curr = S[right];
			++right;
			// 将第一次访问的字母添加到 visited 中
			if (visited.find(curr) == visited.end())
				visited.insert(curr);
			// 每访问一个字母就减去其出现的次数
			--char2int[curr];
			// 直到该字母全部被访问，从 visited 中删去该字母
			if (char2int[curr] == 0)
				visited.erase(curr);
			// 若当前窗口中字母个数个数减至0，说明所有窗口内的字母都在仅出现在窗口内，不在窗外出现，则构成一个 partition
			if (visited.size() == 0)
			{
				result.push_back(right - left);
				// update window
				left = right;
			}
		}
		return result;
	}
};