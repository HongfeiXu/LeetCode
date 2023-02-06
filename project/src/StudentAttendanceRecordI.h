#pragma once

/*

551. Student Attendance Record I

You are given a string representing an attendance record for a student. The record only contains the following three characters:

1. 'A' : Absent.
2. 'L' : Late.
3. 'P' : Present.

A student could be rewarded if his attendance record doesn't contain more than one 'A' (absent) or more than two continuous 'L' (late).

You need to return whether the student could be rewarded according to his attendance record.

Example 1:
Input: "PPALLP"
Output: True
Example 2:
Input: "PPALLL"
Output: False

Approach:
遍历

*/

#include <string>

using namespace std;

class Solution {
public:
	bool checkRecord(string s)
	{
		int cnt_A = 0;
		for (int i = 0; i < s.size(); )
		{
			int cnt_continuous_L = 0;

			if (s[i] == 'A')
			{
				++cnt_A;
				if (cnt_A > 1)
					return false;
				++i;
			}
			else if (s[i] == 'L')
			{
				++cnt_continuous_L;
				int j = i + 1;
				while (j < s.size() && s[i] == s[j])
				{
					++cnt_continuous_L;
					++j;
				}
				if (j - i > 2)
					return false;
				i = j;
			}
			else // s[i] == 'P'
			{
				++i;
			}
		}

		return true;
	}
};
