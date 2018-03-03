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

�������пγ̵����У���ÿһ�����У�������ѡ�����Ŀγ̡�

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
	// ѡ��ǰ�γ������£��ӿγ� i ���γ� courses.size() - 1�����ܹ����ŵ����γ���
	taken = 1  + schedule(courses, i + 1, time + duration_i)
// ��ѡ��ǰ�γ������£��ӿγ� i ���γ� courses.size() - 1�����ܹ����ŵ����γ���
not_taken = schedule(courses, i + 1, time)

�� memo[i][j] ��¼ schedule(courses, i, j, memo) �Ľ����
This helps to prune the search space to a great extent.

Complexity Analysis:
Time: O(n*d)
Space: O(n*d)

########################################################################
Approach #3 Iterative Solution [Time Limit Exceeded]

As discussed in the previous approaches, we need to sort the given courses array based on the end days. 
Thus, we consider the courses in the ascending order of their end days.
��ע����������
time: current time
count: the number of courses taken till now

�Ե�ǰ�γ� i, 
if time + duration_i <= end_day_i
	time = time + duration_i
	++count
else
	��ǰ����Ѿ���ӵĿγ����ҵ�������� duration �Ŀγ� j
	if duration_j > duration_i
		// �ÿγ� i �滻�γ� j��ʹ�����¸����ʱ���������� i+1...n-1 ��Щ�γ�
		time = time - (duration_j - duration_i)

Complexity Analysis:
Time: O(n*n)
Space: O(1)

########################################################################
Approach #4 Optimized Iterative [Accepted]
Time: O(n * count)
Space: O(1)

˼���� Approach #3 ��ͬ
�ڸ��� count ʱ������ courses[count]��ʹ��ǰ��� count+1 ���γ̾��ǵ�ǰ������˵Ŀγ�

########################################################################
Approach #5 Using Extra List [Accepted]

˼���� Approach #3 ��ͬ
ֻ���������һ�����������������Ѿ�����˵Ŀγ�

########################################################################
Approach #6 Iterative Solution With priority_queue [Accepted]

˼���� Approach #3 ��ͬ����ǰ����Ѿ���ӵĿγ����ҵ�������� duration �Ŀγ� j �Ϻ�ʱ��������տγ̵ĳ���ʱ�乹���󶥶ѡ�
�󶥶��д���Ѿ���ӵĿγ̡�
������� O(1) ���ٶ��ҵ� j�������Ҫ�滻����ɾ�� j����� i ��ʱ��Ϊ O(log(n))
�ʣ�
Time: O(nlog(n))�����ķ�ʽ
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
		// ���γ̵���ٽ�ֹ���ڽ�������
		auto cmp = [](const vector<int>& lhs, const vector<int>& rhs)
		{
			return lhs.back() < rhs.back();
		};
		sort(courses.begin(), courses.end(), cmp);
		vector<vector<int>> memo(courses.size(), vector<int>(courses.back().back() + 1, -1));
		return schedule(courses, 0, 0, memo);	// course ��š�ʱ�䶼�� 0 ��ʼ
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
		// ���γ̵���ٽ�ֹ���ڽ�������
		auto cmp = [](const vector<int>& lhs, const vector<int>& rhs)
		{
			return lhs.back() < rhs.back();
		};
		sort(courses.begin(), courses.end(), cmp);
		int time = 0, count = 0;
		vector<bool> ban(courses.size(), false);
		for (int i = 0; i < courses.size(); ++i)
		{
			// i �������
			if (courses[i].front() + time <= courses[i].back())
			{
				time += courses[i].front();
				++count;
			}
			// i �޷�ֱ����ɣ�����ɾ��ǰ��Ŀγ̣�Ȼ������ӿγ� i
			else
			{
				// ����ǰ�������� duration �� duration > duration_i �Ŀγ�
				int max_j = i;
				for (int j = 0; j < i; ++j)
				{
					if (!ban[j] && courses[j].front() > courses[max_j].front())
						max_j = j;
				}
				// ����ҵ����������� max_j
				if (max_j != i)
				{
					time -= (courses[max_j].front() - courses[i].front());
					ban[max_j] = true;	// ֮���ڿ��� max_j �γ�
				}
				// ���򣬲������滻
				else
					ban[i] = true;		// ֮���ڿ��� i �γ�
			}
		}
		return count;
	}
};


class Solution_v4 {
public:
	int scheduleCourse(vector<vector<int>>& courses)
	{
		// ���γ̵���ٽ�ֹ���ڽ�������
		auto cmp = [](const vector<int>& lhs, const vector<int>& rhs)
		{
			return lhs.back() < rhs.back();
		};
		sort(courses.begin(), courses.end(), cmp);
		int time = 0, count = 0;
		for (int i = 0; i < courses.size(); ++i)
		{
			// i �������
			if (courses[i].front() + time <= courses[i].back())
			{
				time += courses[i].front();
				// ���� courses[count]��ʹ��ǰ��� count+1 ���γ̾��ǵ�ǰ������˵Ŀγ�
				courses[count++] = courses[i];
			}
			// i �޷�ֱ����ɣ�����ɾ��ǰ��Ŀγ̣�Ȼ������ӿγ� i
			else
			{
				// ���Ѿ���ӵĿγ��У����Ҿ������ duration �� duration > duration_i �Ŀγ�
				int max_j = i;
				for (int j = 0; j < count; ++j)
				{
					if (courses[j].front() > courses[max_j].front())
						max_j = j;
				}
				// ����ҵ����������� max_j
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
		// ���γ̵���ٽ�ֹ���ڽ�������
		auto cmp = [](const vector<int>& lhs, const vector<int>& rhs)
		{
			return lhs.back() < rhs.back();
		};
		sort(courses.begin(), courses.end(), cmp);
		int time = 0;
		vector<vector<int>> valid_list;
		for (int i = 0; i < courses.size(); ++i)
		{
			// i �������
			if (courses[i].front() + time <= courses[i].back())
			{
				time += courses[i].front();
				valid_list.push_back(courses[i]);
			}
			// i �޷�ֱ����ɣ�����ɾ��ǰ��Ŀγ̣�Ȼ������ӿγ� i
			else
			{
				// ���Ѿ���ӵĿγ��У����Ҿ������ duration �� duration > duration_i �Ŀγ�
				int max_j = 0;
				for (int j = 1; j < static_cast<int>(valid_list.size()); ++j)
				{
					if (valid_list[j].front() > valid_list[max_j].front())
						max_j = j;
				}
				// ����ҵ����������� max_j
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
		// ���γ̵���ٽ�ֹ���ڽ�������
		auto cmp = [](const vector<int>& lhs, const vector<int>& rhs)
		{
			return lhs.back() < rhs.back();
		};
		sort(courses.begin(), courses.end(), cmp);
		auto cmp_2 = [](const vector<int>& lhs, const vector<int>& rhs)
		{
			return lhs.front() < rhs.front();
		};
		// ���ǰ���Ѿ���ӵĿγ̣����ճ���ʱ�乹���󶥶�
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
				// ���ǰ���Ѿ���ӵĿγ��У����ڳ���ʱ����ڵ�ǰ�γ̵Ŀγ̣����滻֮��������ǰ�γ���ӵ��󶥶��У�����������ܵ��滻
				if (!q.empty() && courses[i].front() < q.top().front())
				{
					time += (courses[i].front() - q.top().front());
					q.pop();
					q.push(courses[i]);
				}
				// ��������ڳ���ʱ����ڵ�ǰ�γ̵Ŀγ̣���ǰ�γ��޷����
			}
		}
		return q.size();
	}
};