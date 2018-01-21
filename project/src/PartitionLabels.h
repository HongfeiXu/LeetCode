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
1~7��ÿ���ַ��ĳ��ַ�Χ���� 0~8 �ڣ��� 0~8 Ϊһ�� partition����Ϊ9

d_first = 9, d_last = 14
9~14��
e_first = 10, e_last = 15�� 15 > 14
9~15��ÿ���ַ��ĳ��ַ�Χ���� 9~15 �ڣ��� 9~15 Ϊһ�� partition����Ϊ7

h_first = 16, h_last = 19
16~19��
i_first = 17, i_last = 22, 22 > 19
16~22��
j_first = 18, i_last = 23, 23 > 22
16~23��ÿ���ַ��ĳ��ַ�Χ���� 16~23 �ڣ��� 16~23 Ϊһ�� partition����Ϊ8

Worst Time: O(n^2) abcdefghijk ʱ���������ʱ�临�Ӷ�
������Ҫ����Щû��ȷ����Χ���ַ������������������ǱȽϺ�ʱ�ģ����ǿ��Կ���ʹ�� Sliding Window ��ʽ�����д���

Approach_v2
Sliding Window

The idea is to use sliding window to add all the chars which are not exhausted yet
use a unordered_map ����ÿ���ַ������ָ���
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
		// ÿ�ε���ȷ��һ�� partition��
		while (curr_first != len)
		{
			unordered_set<char> visited;	// �����Ѿ�ȷ���˷�Χ���ַ�����Χ����һ�γ��ֵ�λ�õ����һ�γ��ֵ�λ�ã�
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
					// ���� curr_first ~ curr_last ��Χ�ڵ��ַ���û��ȷ����Χ�������һ�γ��ֵ�λ���Ƿ��ڷ�Χ֮�ڣ������ڣ�����Ҫ����Χ
					if (visited.find(S[j]) == visited.end())
					{
						visited.insert(S[j]);
						int temp_last = S.find_last_of(S[j]);
						// �� S[j] ���ֵ����һ��λ���ڵ�ǰ��Χ֮�⣬����� curr_last������Χ
						if (temp_last > curr_last)
							curr_last = temp_last;
					}
				}
				// ���浱ǰ�ҵ���һ�� partition �ĳ���
				result.push_back(curr_last - curr_first + 1);
				// ���� curr_first��ȷ����һ�� partition
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
		unordered_set<char> visited;	// ���浱ǰ�����е�δ�����������ĸ
		while (right != S.length())
		{
			char curr = S[right];
			++right;
			// ����һ�η��ʵ���ĸ��ӵ� visited ��
			if (visited.find(curr) == visited.end())
				visited.insert(curr);
			// ÿ����һ����ĸ�ͼ�ȥ����ֵĴ���
			--char2int[curr];
			// ֱ������ĸȫ�������ʣ��� visited ��ɾȥ����ĸ
			if (char2int[curr] == 0)
				visited.erase(curr);
			// ����ǰ��������ĸ������������0��˵�����д����ڵ���ĸ���ڽ������ڴ����ڣ����ڴ�����֣��򹹳�һ�� partition
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