#pragma once

/*

387. First Unique Character in a String

Given a string, find the first non-repeating character in it and return it's index. If it doesn't exist, return -1.

Examples:

s = "leetcode"
return 0.

s = "loveleetcode",
return 2.
Note: You may assume the string contain only lowercase letters.

Approach:

从前向后遍历，如果当前字母在后面也出现，则放入 unordered_set 中，
对于之后每个字母，访问时，首先判断是否以及在上述容器中，如果已经存在，则其一定是非unique的，直接跳到下一次迭代
如果当前访问的字母与之后的每个字母都不同，则一定是第一个 unique 的。
*/

#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
	int firstUniqChar(string s)
	{
		unordered_set<char> non_unique_chars;
		for (int i = 0; i < s.size(); ++i)
		{
			// 如果当前字符以及确定不是 unique 的，则进行下一次迭代
			if (non_unique_chars.find(s[i]) != non_unique_chars.end())
				continue;
			int j;
			for (j = i + 1; j < s.size(); ++j)
			{
				if (s[i] == s[j])
				{
					non_unique_chars.insert(s[i]);
					break;
				}
			}
			if (j == s.size())
				return i;
		}
		return -1;
	}
};