#pragma once

/*

696. Count Binary Substrings

Give a string s, count the number of non-empty (contiguous) substrings that have the same number of 0's and 1's, and all the 0's and all the 1's in these substrings are grouped consecutively.

Substrings that occur multiple times are counted the number of times they occur.

Example 1:
Input: "00110011"
Output: 6
Explanation: There are 6 substrings that have equal number of consecutive 1's and 0's: "0011", "01", "1100", "10", "0011", and "01".

Notice that some of these substrings repeat and are counted the number of times they occur.

Also, "00110011" is not a valid substring because all the 0's (and 1's) are not grouped together.
Example 2:
Input: "10101"
Output: 4
Explanation: There are 4 substrings: "10", "01", "10", "01" that have equal number of consecutive 1's and 0's.
Note:

s.length will be between 1 and 50,000.
s will only consist of "0" or "1" characters.

Approach:
通过观察发现，
	00011001
-->	000 11 00 1
--> 3 + 2 + 2 + 1
--> _____
        _____
		    _____
--> 2 + 2 + 1 = 5

*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int countBinarySubstrings(string s)
	{
		if (s.empty())
			return 0;

		int result = 0;

		// 先计算出所有连续的0或者1的个数
		vector<int> consecutive_cnt;
		for (int i = 0; i < s.size();)
		{
			int j = i + 1;
			while (j < s.size() && s[i] == s[j])
				++j;
			consecutive_cnt.push_back(j - i);
			i = j;
		}

		// 去相邻的小的那个数加入 result
		for (int i = 0; i < consecutive_cnt.size() - 1; ++i)
			result += min(consecutive_cnt[i], consecutive_cnt[i + 1]);

		return result;
	}
};