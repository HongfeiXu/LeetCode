#pragma once

/*

30. Substring with Concatenation of All Words

You are given a string, s, and a list of words, words, that are all of the same length. 
Find all starting indices of substring(s) in s that is a concatenation of each word 
in words exactly once and without any intervening characters.

For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).

Approach:

类似于 438. Find All Anagrams in a String，只是把字符换成了长度相同的单词。
另外，需要一个大的循环，控制窗口的起始位置 [0, word_len)

*/

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:
	vector<int> findSubstring(string s, vector<string>& words)
	{
		vector<int> result;

		int word_len = words[0].size();
		int total_len = word_len * words.size();
		if (total_len > s.size())
			return result;

		unordered_map<string, int> stillneed;
		for (int i = 0; i < words.size(); ++i)
			++stillneed[words[i]];

		for (int startpos = 0; startpos < word_len; ++startpos)
		{
			auto curr_stillneed = stillneed;
			int begin = startpos, end = startpos;
			int counter = curr_stillneed.size();

			while (end < s.size())
			{
				string temp = s.substr(end, word_len);
				if (curr_stillneed.find(temp) != curr_stillneed.end())
				{
					--curr_stillneed[temp];
					if (curr_stillneed[temp] == 0)
						--counter;
				}
				end += word_len;

				while (counter == 0)
				{
					if (end - begin == total_len)
						result.push_back(begin);
					string temp = s.substr(begin, word_len);
					if (curr_stillneed.find(temp) != curr_stillneed.end())
					{
						++curr_stillneed[temp];
						if (curr_stillneed[temp] > 0)
							++counter;
					}
					begin += word_len;
				}
			}
		}

		return result;
	}
};