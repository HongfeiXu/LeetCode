#pragma once

/*

443. String Compression

Given an array of characters, compress it in-place.

The length after compression must always be smaller than or equal to the original array.

Every element of the array should be a character (not int) of length 1.

After you are done modifying the input array in-place, return the new length of the array.

Follow up:
Could you solve it using only O(1) extra space?

Example 1:
Input:
["a","a","b","b","c","c","c"]

Output:
Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]

Explanation:
"aa" is replaced by "a2". "bb" is replaced by "b2". "ccc" is replaced by "c3".
Example 2:
Input:
["a"]

Output:
Return 1, and the first 1 characters of the input array should be: ["a"]

Explanation:
Nothing is replaced.
Example 3:
Input:
["a","b","b","b","b","b","b","b","b","b","b","b","b"]

Output:
Return 4, and the first 4 characters of the input array should be: ["a","b","1","2"].

Explanation:
Since the character "a" does not repeat, it is not compressed. "bbbbbbbbbbbb" is replaced by "b12".
Notice each digit has it's own entry in the array.
Note:
All characters have an ASCII value in [35, 126].
1 <= len(chars) <= 1000.

Approach:
两个指针，一个读字符，一个写压缩后的字符
这里在处理字符出现次数的 int 类型数字，使用了 to_string 函数

*/

#include <vector>
#include <string>

using namespace std;


class Solution {
public:
	int compress(vector<char>& chars)
	{
		int curr = 0;
		int end = 0;
		int len = chars.size();
		while (curr != len)
		{
			int j = curr + 1;
			while (j < len && chars[curr] == chars[j])
			{
				++j;
			}
			int consecutive_char_cnt = j - curr;	// 当前字符 chars[curr] 连续出现的次数
			if (consecutive_char_cnt == 1)
			{
				chars[end] = chars[curr];
				++end;
				
			}
			else
			{
				chars[end] = chars[curr];
				++end;
				// 这里使用了 to_string 将数字转换为字符串，使得最大额外空间为 O(lgN)
				string consecutive_char_cnt_str = to_string(consecutive_char_cnt);
				for (int k = 0; k < consecutive_char_cnt_str.size(); ++k)
				{
					chars[end + k] = consecutive_char_cnt_str[k];
				}
				end += consecutive_char_cnt_str.size();
			}
			curr = j;
		}

		chars.erase(chars.begin() + end, chars.end());
		return chars.size();
	}
};