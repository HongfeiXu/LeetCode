# Slinding Window Algorithm Template (to solve LeetCode substring search problem)

## Part 1. The Template

```c++
class Solution {
public:
	vector<int> SlidingWindowTemplate(string s, string p)
	{
		// init a vector to save the result according the question
		vector<int> result;

		if (p.size() > s.size())
			return result;

		// create a unorderd_map to save the Characters of the target substring.
		// (K, V) = (Character, Frequence of the Characters)
		unordered_map<char, int> stillneed;
		for (auto c : p)
			++stillneed[c];
		
		// Two pointers: begin - left pointer of the window; end - right pointer of the window
		int begin = 0, end = 0;

		// maintain a counter to check whether match the target string.
		int counter = stillneed.size();		// must be the map size, NOT the string size because the char may be duplicate.

		// loop at the begining of the source string
		while (end < s.size())
		{
			if (stillneed.find(s[end]) != stillneed.end())
			{
				--stillneed[s[end]];				// plus or minus one
				if (stillneed[s[end]] == 0)		// modify the counter according the requirement(different condition).
					--counter;
			}
			++end;

			//increase begin pointer to make it invalid/valid again
			while (counter == 0)	// counter condition. different question may have different condition
			{
				// save / update (min/max) the result if find a target
				// result collections or result in value
				// example:
				// 在字符串s中，寻找具有p中所有字符的子串位置
				if (end - begin == p.size())
					result.push_back(begin);

				if (stillneed.find(s[begin]) != stillneed.end())
				{
					++stillneed[s[begin]];		// plus or minus one
					if (stillneed[s[begin]] > 0)// modify the counter accoding the requirement(different condition).
						++counter;
				}
				++begin;
			}
		}
		
		return result;
	}
};
```

## Part 2. The Similar Questions

https://leetcode.com/problems/find-all-anagrams-in-a-string/
https://leetcode.com/problems/minimum-window-substring/
https://leetcode.com/problems/longest-substring-without-repeating-characters/
https://leetcode.com/problems/substring-with-concatenation-of-all-words/
https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/
https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/

## Part 3. My Solution for Above Questions

**438. Find All Anagrams in a String**

```c++
class Solution {
public:
	vector<int> findAnagrams(string s, string p)
	{
		vector<int> result;

		if (p.size() > s.size())
			return result;

		unordered_map<char, int> stillneed;
		for (auto c : p)
			++stillneed[c];

		int begin = 0, end = 0;
		// maintain a counter to check whether match the target string.
		int counter = stillneed.size(); 

		// loop at the begining of the source string
		while (end < s.size())
		{
			if (stillneed.find(s[end]) != stillneed.end())
			{
				--stillneed[s[end]];
				if (stillneed[s[end]] == 0)
					--counter;
			}
			++end;

			//increase begin pointer to make it invalid/valid again
			while (counter == 0)
			{
				if (end - begin == p.size())
					result.push_back(begin);
				if (stillneed.find(s[begin]) != stillneed.end())
				{
					++stillneed[s[begin]];
					if (stillneed[s[begin]] > 0)
						++counter;
				}
				++begin;
			}
		}
		
		return result;
	}
};
```

**76. Minimum Window Substring**

>与上面的问题 `438. Find All Anagrams in a String` 只有四行代码的差别

```c++
class Solution {
public:
	string minWindow(string s, string t)
	{
		string result;

		if (t.size() > s.size())
			return result;
		
		unordered_map<char, int> stillneed;
		for (auto c : t)
			++stillneed[c];

		int begin = 0, end = 0;
		int counter = stillneed.size();

		int len = INT_MAX;		// 保存满足条件的窗口的最小长度

		// loop at the begining of the source string
		while (end < s.size())
		{
			if (stillneed.find(s[end]) != stillneed.end())
			{
				--stillneed[s[end]];
				if (stillneed[s[end]] == 0)
					--counter;
			}
			++end;

			// increase begin pointer to make it invalid/valid again
			while (counter == 0)
			{
				if (end - begin < len)
				{
					len = end - begin;
					result = s.substr(begin, len);
				}
				
				if (stillneed.find(s[begin]) != stillneed.end())
				{
					++stillneed[s[begin]];
					if (stillneed[s[begin]] > 0)
						++counter;
				}
				++begin;
			}
		}

		return result;
	}
};
```

**3. Longest Substring Without Repeating Characters**

```c++
class Solution {
public:
	int lengthOfLongestSubstring(string s)
	{
		if (s.empty())
			return 0;

		unordered_map<char, int> um;
		int begin = 0, end = 0;			// [begin, end) 为当前窗口
		int max_len = 0, counter = 0;

		while (end < s.length())
		{
			char c = s[end];
			++um[c];
			if (um[c] > 1)
				++counter;
			++end;

			// 若窗口中有重复字母（最多只有两个字母是相同的），通过移动窗口始端删除字母
			while (counter > 0)
			{
				char c = s[begin];
				if (um[c] > 1)	// 找到重复字母，此次循环后不再接着删除，而是去接着移动窗口末端
					--counter;
				--um[s[begin]];
				++begin;
			}

			max_len = max(max_len, end - begin);
		}
		max_len = max(max_len, end - begin);
	
		return max_len;
	}
};
```

**30. Substring with Concatenation of All Words**

>类似于 `438. Find All Anagrams in a String`，只是把字符换成了长度相同的单词。
另外，需要一个大的循环，控制窗口的起始位置 [0, word_len)

```c++
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
```

**159. Longest Substring with At Most Two Distinct Characters**

```c++
class Solution {
public:
	int lengthOfLongestSubstringTwoDistinct(string s)
	{
		int begin = 0, end = 0;
		int counter = 0;		// 记录当前窗口中有多少个不同的字母
		
		int max_len = INT_MIN;
		int curr_len;

		unordered_map<char, int> um;	// 记录当前窗口中字母出现的个数，若 value 为0，表示当前窗口中不存在该数字

		while (end < s.size())
		{
			++um[s[end]];
			if (um[s[end]] == 1)
				++counter;

			curr_len = end - begin;
			max_len = max(max_len, curr_len);

			++end;

			while (counter > 2)
			{
				--um[s[begin]];
				if (um[s[begin]] == 0)
					--counter;
				++begin;
			}
		}

		max_len = max(max_len, curr_len);
		return max_len;
	}
};
```

**340. Longest Substring with At Most K Distinct Characters**

```c++
class Solution {
public:
	int lengthOfSubstringKDistance(string s, int k)
	{
		int begin = 0, end = 0;
		int counter = 0;			// 记录当前窗口中有多少个不同的字母
		
		int max_len = INT_MIN;
		int curr_len;

		unordered_map<char, int> um;	// 记录当前窗口中每个字母出现的个数，若 value 为0，表示当前窗口中不存在该数字

		while (end < s.size())
		{
			++um[s[end]];
			if (um[s[end]] == 1)
				++counter;
			curr_len = end - begin;
			max_len = max(curr_len, max_len);

			++end;

			while (counter > k)
			{
				--um[s[begin]];
				if (um[s[begin]] == 0)
					--counter;
				++begin;
			}
		}

		curr_len = end - begin;
		max_len = max(curr_len, max_len);
		return max_len;
	}
};
```