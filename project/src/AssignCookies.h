#pragma once

/*

455. Assign Cookies

Assume you are an awesome parent and want to give your children some cookies. 
But, you should give each child at most one cookie. 
Each child i has a greed factor gi, which is the minimum size of a cookie that the child will be content with; 
and each cookie j has a size sj. If sj >= gi, we can assign the cookie j to the child i, and the child i will be content. 
Your goal is to maximize the number of your content children and output the maximum number.

Note:
You may assume the greed factor is always positive.
You cannot assign more than one cookie to one child.

Example 1:
Input: [1,2,3], [1,1]

Output: 1

Explanation: You have 3 children and 2 cookies. The greed factors of 3 children are 1, 2, 3.
And even though you have 2 cookies, since their size is both 1, you could only make the child whose greed factor is 1 content.
You need to output 1.

Input: [1,2], [1,2,3]

Output: 2

Explanation: You have 2 children and 3 cookies. The greed factors of 2 children are 1, 2.
You have 3 cookies and their sizes are big enough to gratify all of the children,
You need to output 2.

Approach:

Greedy.
先满足最小需求的小孩，并且尽可能使用最小的饼干。这样能够最终满足最多的小孩。
Time: O(nlogn), n 为 max(g.size(), s.size())

*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int findContentChildren(vector<int>& g, vector<int>& s)
	{
		sort(s.begin(), s.end());
		sort(g.begin(), g.end());

		int g_i = 0;
		int s_i = 0;
		while (s_i != s.size() && g_i != g.size())
		{
			if (g[g_i] <= s[s_i])
				++g_i;
			++s_i;
		}

		return g_i;
	}
};
