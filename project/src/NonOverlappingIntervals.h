#pragma once

/*

435. Non-overlapping Intervals

Given a collection of intervals, find the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.

Note:
1. You may assume the interval's end point is always bigger than its start point.
2. Intervals like [1,2] and [2,3] have borders "touching" but they don't overlap each other.

Example 1:
Input: [ [1,2], [2,3], [3,4], [1,3] ]

Output: 1

Explanation: [1,3] can be removed and the rest of intervals are non-overlapping.
Example 2:
Input: [ [1,2], [1,2], [1,2] ]

Output: 2

Explanation: You need to remove two [1,2] to make the rest of intervals non-overlapping.
Example 3:
Input: [ [1,2], [2,3] ]

Output: 0

Explanation: You don't need to remove any of the intervals since they're already non-overlapping.

Approach:

CLRS chapter 16，第一个例子活动安排问题的变形，把每个区间看成一个活动所需占用的时间
先求出最大能够安排的活动数a，然后用总的活动数减去a就得到需要被删除的活动数。

*/

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
		Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
public:
	int eraseOverlapIntervals(vector<Interval>& intervals)
	{
		auto compare = [](const Interval& lhs, const Interval& rhs) { return lhs.end < rhs.end; };
		sort(intervals.begin(), intervals.end(), compare);
		int result = 0;
		int curr_end = INT_MIN;
		for (int i = 0; i < intervals.size(); ++i)
		{
			if (intervals[i].start >= curr_end)
				curr_end = intervals[i].end;
			else
				++result;
		}
		return result;
	}
};

void test()
{
	vector<Interval> intervals;
	intervals.push_back(Interval(1, 2));
	intervals.push_back(Interval(2, 3));
	intervals.push_back(Interval(3, 4));
	intervals.push_back(Interval(1, 3));

	Solution solu;
	cout << solu.eraseOverlapIntervals(intervals) << endl;
}