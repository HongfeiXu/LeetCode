#pragma once

/*

376. Wiggle Subsequence

A sequence of numbers is called a wiggle sequence if the differences 
between successive numbers strictly alternate between positive and negative. 
The first difference (if one exists) may be either positive or negative. 
A sequence with fewer than two elements is trivially a wiggle sequence.

For example, [1,7,4,9,2,5] is a wiggle sequence because the differences 
(6,-3,5,-7,3) are alternately positive and negative. In contrast, 
[1,4,7,2,5] and [1,7,4,5,5] are not wiggle sequences, the first 
because its first two differences are positive and the second because its last difference is zero.

Given a sequence of integers, return the length of the longest subsequence that is a wiggle sequence. 
A subsequence is obtained by deleting some number of elements (eventually, also zero) from the original sequence, 
leaving the remaining elements in their original order.

Examples:
Input: [1,7,4,9,2,5]
Output: 6
The entire sequence is a wiggle sequence.

Input: [1,17,5,10,13,15,10,5,16,8]
Output: 7
There are several subsequences that achieve this length. One is [1,17,10,13,10,16,8].

Input: [1,2,3,4,5,6,7,8,9]
Output: 2

Follow up:
Can you do it in O(n) time?

##########################################
Approach:
DP
Time: O(n^2)
Space: O(n)
Input: nums[0...n-1]
Def: LWS[0...n-1] {len, pre}
LWS[i] 表示以 nums[i] 为最后一个元素的最长波动子序列的长度以及其倒数第二个元素的值 <len, pre>
则，LWS[k].len = max{LWS[i].len + 1}，其中 nums[LWS[i].pre], nums[i], nums[k] 为一个波动, i = 0...k-1，记录具有最大值的 i 为 I，则
LWS[k].pre = nums[i]
LWS[0] = {1, -1}

##########################################
Approach_v2:
Ref: https://leetcode.com/problems/wiggle-subsequence/solution/

Brute Force
Time Limit Exceeded

##########################################
Approach_v3:
Ref: https://leetcode.com/problems/wiggle-subsequence/solution/
COOL
DP
Time: O(n^2)
Space: O(n)

Def:
up[i] 第 i 个元素作为子序列最后一个元素时，以上升波动结束的 LWS 的长度
down[i] 第 i 个元素作为子序列最后一个元素时，以下降波动结束的 LWS 的长度

up[k] = max(down[i] + 1), i = 0...k-1, 且 nums[i] < nums[k]
同理
down[k] = max(up[i] + 1), i = 0...k-1, 且 nums[i] > nums[k]

##########################################
Approach_v4:
Ref: https://leetcode.com/problems/wiggle-subsequence/solution/

Linear DP
Time: O(n)
Space: O(n)

Any element in the array could correspond to only one of the three possible states:

1. up position, nums[i] > nums[i-1]
2. down position, nums[i] < nums[i-1]
3. equal to position, nums[i] == nums[i-1]

up[i] 第 i 个元素作为子序列最后一个元素时，以上升波动结束的 LWS 的长度
down[i] 第 i 个元素作为子序列最后一个元素时，以下降波动结束的 LWS 的长度

If nums[i] > nums[i-1], wiggles up, the element before it must be a down position.
So up[i] = down[i-1] + 1, down[i] = down[i-1]
If nums[i] < nums[i-1], wiggles down, the element before it must be a up position.
So down[i] = up[i-1] + 1, up[i] = up[i-1]
If nums[i] == nums[i-1]
up[i] = up[i-1], down[i] = down[i-1]

##########################################
Approach_v5:
Ref: https://leetcode.com/problems/wiggle-subsequence/solution/

Space-Optimized DP
Time: O(n)
Space: O(1)


##########################################
Approach_v6:
Ref: https://leetcode.com/problems/wiggle-subsequence/solution/
Greedy Approach

只要找到上升下降的次数即可，所以需要记录之前的状态，然后同当前的状态比较，若不同，则++，否则继续向后更新当前状态

We need not necessarily need dp to solve this problem. 
This problem is equivalent to finding the number of alternating max. and min. peaks in the array. 
Since, if we choose any other intermediate number to be a part of the current wiggle subsequence, 
the maximum length of that wiggle subsequence will always be less than or equal to the one obtained 
by choosing only the consecutive max. and min. elements.

*/

#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

// My DP
class Solution {
public:
	int wiggleMaxLength(vector<int>& nums)
	{
		if (nums.size() < 2)
			return nums.size();

		struct Info {
			int len;
			int pre;
		};

		vector<Info> LWS;
		LWS.push_back({ 1,-1 });	// LWS[0] = {1, -1}
		int result = 1;
		for (int i = 1; i < nums.size(); ++i)
		{
			Info curr { 1,-1 };	// 对第i个元素的 LWS 值，初始为 {1,-1}
			for (int j = 0; j < i; ++j)
			{
				// 若第 j 个元素为最后一个元素的LWS没有前驱节点，则只要第 i 个元素与之不等，即可构成 WS
				if (LWS[j].pre == -1)
				{
					if (nums[j] != nums[i] && curr.len < LWS[j].len + 1)
					{
						curr.len = LWS[j].len + 1;
						curr.pre = j;
					}
				}
				// 若第 j 个元素具有前驱节点，则首先判断添加第 i 个元素能否构成摆动，形成新的 WS，然后取构成最长 WS 的 j 作为 i 的 pre
				else
				{
					// 构成波动
					if ((nums[i] - nums[j]) * (nums[j] - nums[LWS[j].pre]) < 0)
					{
						if (curr.len < LWS[j].len + 1)
						{
							curr.len = LWS[j].len + 1;
							curr.pre = j;
						}
					}
				}

			}
			LWS.push_back(curr);
			result = max(result, curr.len);
		}

		return result;
	}
};

// Brute force
class Solution_v2 {
public:
	int wiggleMaxLength(vector<int>& nums)
	{
		if (nums.size() < 2)
			return nums.size();

		return 1 + max(calculate(nums, 0, true), calculate(nums, 0, false));
	}

	int calculate(const vector<int>& nums, int index, bool isUp)
	{
		int max_count = 0;
		for (int i = index + 1; i < nums.size(); ++i)
		{
			if (isUp && nums[i] > nums[index] || !isUp && nums[i] < nums[index])
				max_count = max(max_count, 1 + calculate(nums, i, !isUp));
		}

		return max_count;
	}
};

// DP
class Solution_v3 {
public:
	int wiggleMaxLength(vector<int>& nums)
	{
		if (nums.size() < 2)
			return nums.size();

		vector<int> up(nums.size(), 1);
		vector<int> down(nums.size(), 1);

		for (int i = 1; i < nums.size(); ++i)
		{
			for (int j = 0; j < i; ++j)
			{
				// update up[]
				if (nums[j] < nums[i])
					up[i] = max(up[i], down[j] + 1);
				// update down[]
				else if (nums[j] > nums[i])
					down[i] = max(down[i], up[j] + 1);
			}
		}

		return max(up.back(), down.back());
	}
};

// Linear DP
class Solution_v4 {
public:
	int wiggleMaxLength(vector<int>& nums)
	{
		if (nums.size() < 2)
			return nums.size();

		vector<int> up(nums.size(), 1);
		vector<int> down(nums.size(), 1);

		for (int i = 1; i < nums.size(); ++i)
		{
			if (nums[i] > nums[i - 1])
			{
				up[i] = down[i - 1] + 1;
				down[i] = down[i - 1];
			}
			else if(nums[i] < nums[i-1])
			{
				down[i] = up[i - 1] + 1;
				up[i] = up[i - 1];
			}
			else
			{
				up[i] = up[i - 1];
				down[i] = down[i - 1];
			}
		}

		return max(up.back(), down.back());
	}
};

// Space-Optimized DP
class Solution_v5 {
public:
	int wiggleMaxLength(vector<int>& nums)
	{
		if (nums.size() < 2)
			return nums.size();

		int up = 1, down = 1;

		for (int i = 1; i < nums.size(); ++i)
		{
			if (nums[i] > nums[i - 1])
				up = down + 1;
			else if(nums[i] < nums[i-1])
				down = up + 1;
		}

		return max(up, down);
	}
};

// Greedy
class Solution_v6 {
public:
	int wiggleMaxLength(vector<int>& nums)
	{
		if (nums.size() < 2)
			return nums.size();

		int prev_diff = nums[1] - nums[0];
		int cnt = (prev_diff == 0) ? 1 : 2;
		for (int i = 2; i < nums.size(); ++i)
		{
			int diff = nums[i] - nums[i - 1];
			if (prev_diff <= 0 && diff > 0 || prev_diff >= 0 && diff < 0)
			{
				prev_diff = diff;
				++cnt;
			}
		}
		return cnt;
	}
};
