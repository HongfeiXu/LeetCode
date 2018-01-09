#pragma once

/*

720. Longest Word in Dictionary

Given a list of strings words representing an English Dictionary, 
find the longest word in words that can be built one character at a time by other words in words. 
If there is more than one possible answer, return the longest word with the smallest lexicographical order.

If there is no answer, return the empty string.

Example 1:
Input:
words = ["w","wo","wor","worl", "world"]
Output: "world"
Explanation:
The word "world" can be built one character at a time by "w", "wo", "wor", and "worl".
Example 2:
Input:
words = ["a", "banana", "app", "appl", "ap", "apply", "apple"]
Output: "apple"
Explanation:
Both "apply" and "apple" can be built from other words in the dictionary. However, "apple" is lexicographically smaller than "apply".

Note:

All the strings in the input will only contain lowercase letters.
The length of words will be in the range [1, 1000].
The length of words[i] will be in the range [1, 30].

Approach:

ʹ�� unordered_set ��¼��Щ�Լ�ȷ������ÿ�����һ����ĸ���ɵĵ���
�ȶ� words ����Ȼ����ڳ���Ϊ 1 �ĵ��ʣ�ֱ�ӷ��� unordered_set �У�
���ڳ���Ϊ n �ĵ��ʣ�����ǰ n-1 ���ַ����ɵ��Ӵ��� unordered_set �У���õ���Ҳ���� unordered_set �С�

*/

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Solution {
public:

	string longestWord(vector<string>& words)
	{
		// ���յ��ʵĳ��ȶ� words ���д�С��������
		sort(words.begin(), words.end());
		
		unordered_set<string> built;		// ��¼��Щ�Լ�ȷ������ÿ�����һ����ĸ���ɵĵ���
		for (int i = 0; i < words.size(); ++i)
		{
			if (words[i].size() == 1)		// ���ڳ���Ϊ 1 �ĵ��ʣ�ֱ�ӷ��� unordered_set ��
				built.insert(words[i]);
			else if(words[i].empty())		
				continue;
			else							// ���ڳ���Ϊ n �ĵ��ʣ�����ǰ n-1 ���ַ����ɵ��Ӵ��� unordered_set �У���õ���Ҳ���� unordered_set ��
			{
				string temp = words[i].substr(0, words[i].size() - 1);
				if (built.find(temp) != built.end())
					built.insert(words[i]);
			}
		}

		string result = "";
		for (auto it = built.begin(); it != built.end(); ++it)
		{
			if (it->size() > result.size())
				result = *it;
			else if (it->size() == result.size())
				result = min(result, *it);
		}
		return result;
	}
};
