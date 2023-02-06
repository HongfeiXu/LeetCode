#pragma once

/*

383. Ransom Note

Given an arbitrary ransom note string and another string containing letters from all the magazines, 
write a function that will return true if the ransom note can be constructed from the magazines ; 
otherwise, it will return false.

Each letter in the magazine string can only be used once in your ransom note.

Note:
You may assume that both strings contain only lowercase letters.

canConstruct("a", "b") -> false
canConstruct("aa", "ab") -> false
canConstruct("aa", "aab") -> true

Approach:
使用 unordered_map 记录 ransomNote/magazine 中每个字符以及其出现的次数，方便后面的查找，比较

*/

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>

using namespace std;

class Solution {
public:
	bool canConstruct(string ransomNote, string magazine)
	{
		sort(ransomNote.begin(), ransomNote.end());
		unordered_map<char, int> ransomNoteInfo;	// 存储 ransomNote 中每个字母以及其出现的次数
		for (int i = 0; i < ransomNote.size();)
		{
			int j = i + 1;
			while (j < ransomNote.size() && ransomNote[j] == ransomNote[i])
				++j;
			//ransomNoteInfo.push_back({ ransomNote[i], j - i });
			ransomNoteInfo[ransomNote[i]] = j - i;
			i = j;
		}

		sort(magazine.begin(), magazine.end());
		unordered_map<char, int> magazineInfo;		// 存储 magazineInfo 中每个字母以及其出现的次数
		for (int i = 0; i < magazine.size();)
		{
			int j = i + 1;
			while (j < magazine.size() && magazine[j] == magazine[i])
				++j;
			//magazineInfo.push_back({ magazine[i], j - i });
			magazineInfo[magazine[i]] = j - i;
			i = j;
		}

		for (const auto & item : ransomNoteInfo)
		{
			// 如果 ransomNote 中字符在 magazineInfo中没有出现，则返回 false
			if (magazineInfo.find(item.first) == magazineInfo.end())
				return false;
			// 若 ransomNote 中字符在 magazineInfo 中出现，但 magazineInfo 中出现次数不够，则返回 false
			else if (magazineInfo[item.first] < item.second)
				return false;
		}
	
		return true;
	}
};