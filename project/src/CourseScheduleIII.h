#pragma once

/*

630. Course Schedule III

There are n different online courses numbered from 1 to n. 
Each course has some duration(course length) t and closed on dth day. 
A course should be taken continuously for t days and must be finished before or on the dth day. 
You will start at the 1st day.

Given n online courses represented by pairs (t,d), 
your task is to find the maximal number of courses that can be taken.

Example:
Input: [[100, 200], [200, 1300], [1000, 1250], [2000, 3200]]
Output: 3
Explanation:
There're totally 4 courses, but you can take 3 courses at most:
First, take the 1st course, it costs 100 days so you will finish it on the 100th day, and ready to take the next course on the 101st day.
Second, take the 3rd course, it costs 1000 days so you will finish it on the 1100th day, and ready to take the next course on the 1101st day.
Third, take the 2nd course, it costs 200 days so you will finish it on the 1300th day.
The 4th course cannot be taken now, since you will finish it on the 3300th day, which exceeds the closed date.
Note:
The integer 1 <= d, t, n <= 10,000.
You can't take two courses simultaneously.

########################################################################
Approach #1 Brute Force [Time Limit Exceeded]:

考虑所有课程的排列，对每一种排列，尽可能选择最多的课程。

Time: O((n+1)!)
Spcae: O(n)

########################################################################
Approach #2 Using Recursion with memoization [Time Limit Exceeded]:

Very Good Ref: https://leetcode.com/problems/course-schedule-iii/solution/

Analyse:

(a, x), (b, y), x < y, a <= x, b <= y

	1. (a + b) <= x

	Both the courses can be taken irrespective of the order in which the courses are taken.

	2. (a + b) > x, a > b, (a + b) <= y

	In this case, as is evident from the figure, both the courses can be taken only by taking course a before b.

	3. (a + b) > x, b > a, (a + b) <= y

	In this case also, both the courses can be taken only by taking course a before b.

	4. (a + b) > y

	In this case, irrespective of the order in which we take the courses, only one course can be taken.

From the above example, we can conclude that it is always profitable to take the course with a smaller end day prior to a course with a larger end day. 
This is because, the course with a smaller duration, if can be taken, can surely be taken only if it is taken prior to a course with a larger end day.


schedule(courses, i, time) = max(taken, not_taken) 

if(time + duration_i <= end_day_i)
	// 选择当前课程条件下（从课程 i 到课程 courses.size() - 1）所能够安排的最大课程数
	taken = 1  + schedule(courses, i + 1, time + duration_i)
// 不选择当前课程条件下（从课程 i 到课程 courses.size() - 1）所能够安排的最大课程数
not_taken = schedule(courses, i + 1, time)

用 memo[i][j] 记录 schedule(courses, i, j, memo) 的结果。
This helps to prune the search space to a great extent.

Complexity Analysis:
Time: O(n*d)
Space: O(n*d)

########################################################################
Approach #3 Iterative Solution [Time Limit Exceeded]

As discussed in the previous approaches, we need to sort the given courses array based on the end days. 
Thus, we consider the courses in the ascending order of their end days.
关注两个变量：
time: current time
count: the number of courses taken till now

对当前课程 i, 
if time + duration_i <= end_day_i
	time = time + duration_i
	++count
else
	从前面的已经添加的课程中找到具有最大 duration 的课程 j
	if duration_j > duration_i
		// 用课程 i 替换课程 j，使得余下更多的时间用来安排 i+1...n-1 这些课程
		time = time - (duration_j - duration_i)

Complexity Analysis:
Time: O(n*n)
Space: O(1)

########################################################################
Approach #4 Optimized Iterative [Accepted]
Time: O(n * count)
Space: O(1)

思想与 Approach #3 相同
在更新 count 时，更新 courses[count]，使得前面的 count+1 个课程就是当前被添加了的课程

########################################################################
Approach #5 Using Extra List [Accepted]

思想与 Approach #3 相同
只是这里采用一个额外的链表来存放已经添加了的课程

########################################################################
Approach #6 Iterative Solution With priority_queue [Accepted]

思想与 Approach #3 相同，从前面的已经添加的课程中找到具有最大 duration 的课程 j 较耗时，如果按照课程的持续时间构建大顶堆。
大顶堆中存放已经添加的课程。
则可以以 O(1) 的速度找到 j，如果需要替换，则删除 j、添加 i 的时间为 O(log(n))
故，
Time: O(nlog(n))，最快的方式
Space: O(n)

*/

#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <queue>
#include <list>

using namespace std;

class Solution_v2 {
public:
	int scheduleCourse(vector<vector<int>>& courses)
	{
		// 按课程的最迟截止日期进行排序
		auto cmp = [](const vector<int>& lhs, const vector<int>& rhs)
		{
			return lhs.back() < rhs.back();
		};
		sort(courses.begin(), courses.end(), cmp);
		vector<vector<int>> memo(courses.size(), vector<int>(courses.back().back() + 1, -1));
		return schedule(courses, 0, 0, memo);	// course 编号、时间都从 0 开始
	}
	// memo[i][j] is used to store the result of the function call schedule(courses, i, time)
	int schedule(vector<vector<int>>& courses, int i, int t, vector<vector<int>>& memo)
	{
		if (i == courses.size())
			return 0;
		if (memo[i][t] != -1)
			return memo[i][t];
		int taken = 0, not_taken = 0;
		if (courses[i].front() + t <= courses[i].back())
			taken = 1 + schedule(courses, i + 1, t + courses[i].front(), memo);
		not_taken = schedule(courses, i + 1, t, memo);
		memo[i][t] = max(taken, not_taken);
		return memo[i][t];
	}
};

class Solution_v3 {
public:
	int scheduleCourse(vector<vector<int>>& courses)
	{
		// 按课程的最迟截止日期进行排序
		auto cmp = [](const vector<int>& lhs, const vector<int>& rhs)
		{
			return lhs.back() < rhs.back();
		};
		sort(courses.begin(), courses.end(), cmp);
		int time = 0, count = 0;
		vector<bool> ban(courses.size(), false);
		for (int i = 0; i < courses.size(); ++i)
		{
			// i 可以完成
			if (courses[i].front() + time <= courses[i].back())
			{
				time += courses[i].front();
				++count;
			}
			// i 无法直接完成，尝试删除前面的课程，然后再添加课程 i
			else
			{
				// 查找前面具有最大 duration 且 duration > duration_i 的课程
				int max_j = i;
				for (int j = 0; j < i; ++j)
				{
					if (!ban[j] && courses[j].front() > courses[max_j].front())
						max_j = j;
				}
				// 如果找到满足条件的 max_j
				if (max_j != i)
				{
					time -= (courses[max_j].front() - courses[i].front());
					ban[max_j] = true;	// 之后不在考虑 max_j 课程
				}
				// 否则，不进行替换
				else
					ban[i] = true;		// 之后不在考虑 i 课程
			}
		}
		return count;
	}
};


class Solution_v4 {
public:
	int scheduleCourse(vector<vector<int>>& courses)
	{
		// 按课程的最迟截止日期进行排序
		auto cmp = [](const vector<int>& lhs, const vector<int>& rhs)
		{
			return lhs.back() < rhs.back();
		};
		sort(courses.begin(), courses.end(), cmp);
		int time = 0, count = 0;
		for (int i = 0; i < courses.size(); ++i)
		{
			// i 可以完成
			if (courses[i].front() + time <= courses[i].back())
			{
				time += courses[i].front();
				// 更新 courses[count]，使得前面的 count+1 个课程就是当前被添加了的课程
				courses[count++] = courses[i];
			}
			// i 无法直接完成，尝试删除前面的课程，然后再添加课程 i
			else
			{
				// 在已经添加的课程中，查找具有最大 duration 且 duration > duration_i 的课程
				int max_j = i;
				for (int j = 0; j < count; ++j)
				{
					if (courses[j].front() > courses[max_j].front())
						max_j = j;
				}
				// 如果找到满足条件的 max_j
				if (max_j != i)
				{
					time -= (courses[max_j].front() - courses[i].front());
					courses[max_j] = courses[i];
				}
			}
		}
		return count;
	}
};

class Solution_v5 {
public:
	int scheduleCourse(vector<vector<int>>& courses)
	{
		// 按课程的最迟截止日期进行排序
		auto cmp = [](const vector<int>& lhs, const vector<int>& rhs)
		{
			return lhs.back() < rhs.back();
		};
		sort(courses.begin(), courses.end(), cmp);
		int time = 0;
		vector<vector<int>> valid_list;
		for (int i = 0; i < courses.size(); ++i)
		{
			// i 可以完成
			if (courses[i].front() + time <= courses[i].back())
			{
				time += courses[i].front();
				valid_list.push_back(courses[i]);
			}
			// i 无法直接完成，尝试删除前面的课程，然后再添加课程 i
			else
			{
				// 在已经添加的课程中，查找具有最大 duration 且 duration > duration_i 的课程
				int max_j = 0;
				for (int j = 1; j < static_cast<int>(valid_list.size()); ++j)
				{
					if (valid_list[j].front() > valid_list[max_j].front())
						max_j = j;
				}
				// 如果找到满足条件的 max_j
				if (!valid_list.empty() && valid_list[max_j].front() > courses[i].front())
				{
					time -= (valid_list[max_j].front() - courses[i].front());
					valid_list[max_j] = courses[i];
				}
			}
		}
		return valid_list.size();
	}
};


class Solution_v6 {
public:
	int scheduleCourse(vector<vector<int>>& courses)
	{
		// 按课程的最迟截止日期进行排序
		auto cmp = [](const vector<int>& lhs, const vector<int>& rhs)
		{
			return lhs.back() < rhs.back();
		};
		sort(courses.begin(), courses.end(), cmp);
		auto cmp_2 = [](const vector<int>& lhs, const vector<int>& rhs)
		{
			return lhs.front() < rhs.front();
		};
		// 存放前面已经添加的课程，按照持续时间构建大顶堆
		priority_queue<vector<int>, vector<vector<int>>, decltype(cmp_2)> q(cmp_2);	

		int time = 0;
		for (int i = 0; i < courses.size(); ++i)
		{
			if (courses[i].front() + time <= courses[i].back())
			{
				time += courses[i].front();
				q.push(courses[i]);
			}
			else
			{
				// 如果前面已经添加的课程中，存在持续时间大于当前课程的课程，则替换之，并将当前课程添加到大顶堆中，留待后面可能的替换
				if (!q.empty() && courses[i].front() < q.top().front())
				{
					time += (courses[i].front() - q.top().front());
					q.pop();
					q.push(courses[i]);
				}
				// 如果不存在持续时间大于当前课程的课程，则当前课程无法添加
			}
		}
		return q.size();
	}
};