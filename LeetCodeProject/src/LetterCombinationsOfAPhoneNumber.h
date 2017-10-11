#pragma once

/*

17. Letter Combinations of a Phone Number

Related Topics: String, BackTracking

Given a digit string, return all possible letter combinations that the number could represent.

Approach Recurisive: Just like 22. Generate Parentheses

Approach Iterative: See letterCombinations_v2

*/

#include <vector>
#include <string>

using namespace std;

class Solution {
private:
	void letterCombine(vector<string> &words, string word, string digits, vector<string> &dictionary)
	{
		if (digits.empty())
		{
			if (!word.empty())
				words.push_back(word);
			return;
		}

		string candidate = dictionary[digits[0] - '0'];
		if (!candidate.empty())
		{
			for (unsigned i = 0; i < candidate.size(); i++)
			{
				letterCombine(words, word + candidate[i], string(digits.begin() + 1, digits.end()), dictionary);
			}
		}
		else  // jump this empty candidate
		{
			letterCombine(words, word, string(digits.begin() + 1, digits.end()), dictionary);
		}
	}

public:
	vector<string> letterCombinations(string digits)
	{
		// 2->"abc", 3->"def"...
		vector<string> dicitionary = { "", "", "abc", "def","ghi","jkl","mno","pqrs","tuv","wxyz" };

		vector<string> result;
		letterCombine(result, "", digits, dicitionary);

		return result;
	}

	vector<string> letterCombinations_v2(string digits)
	{
		vector<string> dicitionary = { "", "", "abc", "def","ghi","jkl","mno","pqrs","tuv","wxyz" };
		vector<string> result;

		if (digits.empty())
			return result;

		result.push_back("");
		for (int i = 0; i < digits.size(); i++)
		{
			vector<string> temp_result;
			string candidate = dicitionary[digits[i] - '0'];
			for (int j = 0; j < candidate.size(); j++)
			{
				for (int k = 0; k < result.size(); k++)
				{
					temp_result.push_back(result[k] + candidate[j]);
				}
			}
			result = temp_result;
		}
		return result;
	}
};