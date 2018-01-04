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
ʹ�� unordered_map ��¼ ransomNote/magazine ��ÿ���ַ��Լ�����ֵĴ������������Ĳ��ң��Ƚ�

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
		unordered_map<char, int> ransomNoteInfo;	// �洢 ransomNote ��ÿ����ĸ�Լ�����ֵĴ���
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
		unordered_map<char, int> magazineInfo;		// �洢 magazineInfo ��ÿ����ĸ�Լ�����ֵĴ���
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
			// ��� ransomNote ���ַ��� magazineInfo��û�г��֣��򷵻� false
			if (magazineInfo.find(item.first) == magazineInfo.end())
				return false;
			// �� ransomNote ���ַ��� magazineInfo �г��֣��� magazineInfo �г��ִ����������򷵻� false
			else if (magazineInfo[item.first] < item.second)
				return false;
		}
	
		return true;
	}
};