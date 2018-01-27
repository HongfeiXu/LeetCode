#pragma once

/*

621. Task Scheduler

Given a char array representing tasks CPU need to do. It contains capital letters A to Z 
where different letters represent different tasks.Tasks could be done without original order. 
Each task could be done in one interval. For each interval, CPU could finish one task or just be idle.

However, there is a non-negative cooling interval n that means between two same tasks, 
there must be at least n intervals that CPU are doing different tasks or just be idle.

You need to return the least number of intervals the CPU will take to finish all the given tasks.

Example 1:
Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: A -> B -> idle -> A -> B -> idle -> A -> B.
Note:
1. The number of tasks is in the range [1, 10000].
2. The integer n is in the range [0, 100].

题目的意思是：对于相同的任务A，CPU在做了一次A之后需要至少经过n个时间间隔才能再做下一次A任务，中间的间隔可以执行其他任务或者空闲。

Approach:

Greedy
由于题目中规定了两个相同任务之间的最少间隔为n，则我们首先安排出现次数最多的任务，然后再安排出现次数次之的任务。
如果任务F出现次数最多，为k次，则我们用n个空格将每两个F任务分隔开，然后按顺序（出现次数降序）插入其他低频的任务。

如 AAAAABBBEEFFGG n=3
=> A---A---A---A	A出现次数最多，在每两个相邻之间用3个空位分开	
=> AB--AB--AB--A	加入B
=> ABE-ABE-AB--A	加入E
=> ABEFABE-ABF-A	加入F，每次尽可能填满或者是均匀填充
=> ABEFABEGABFGA	加入G

如 ACCCEEE n = 2
=> C--C--C
=> CE-CE-CE
=> CEACE-CE

分析题目我们可知：
	interval 数目 = idle数目 + task数目
task数目已知，我们只需要求 idle 数目
	idle 数目 = max(0, 为了让最多次数的 task 完成所需的中间 interval 数目 - 其他任务插入所能提供的有效的 interval 数目)
1. 为了让最多次数的 task 完成所需的中间 interval 数目 = (最多次数的 task 的次数 - 1) * n
2. 其他任务插入所能提供的有效的 interval 数目:
如果最大数目的task不止一个，比如第二个例子中的C和E，这时插入E到C中间能提供的有效的 interval 数目为 task 数目 - 1，因为最后一个将会插到最后一个位置。
对于出现次数小于最大数目 task 的其他 task，则直接进行均匀填充，全部都能作为有效的 interval。

另外，若提供的 interval 数目 > 需要的 interval 数目，则说明没有 idle 情况的interval

tasks.size() = M
Time: O(MlogM)
Space: O(1)

Approach v2:

Ref: http://www.cnblogs.com/grandyang/p/7098764.html

将任务序列分为模块处理。会比上面的思路更容易编程
我们仔细观察上面两个例子可以发现，都分成了(mx - 1)块，再加上最后面的字母
（最后面的字母由出现次数最大的字母组成，可能有多个具有相同最大出现次数的字母），其中mx为最大出现次数。
比如例子1中，A出现了4次，所以有A---模块出现了3次，再加上最后的A，每个模块的长度为4。
例子2中，CE-出现了2次，再加上最后的CE，每个模块长度为3。我们可以发现，模块的数目为任务最大次数减1，
模块的长度为n+1，最后加上的字母个数为出现次数最多的任务（因为可能有多个并列），
就得到了正好使得出现次数做多的任务得以分隔开的最小 interval 数目，取该数目与总任务数目的较大值为结果。

Approach v3:
模块角度，应用 Approach v1 的方法，即求出需要的 idle 数目，然后加上总的任务数目即为结果
这里求 idle 数目的方式与 Approach v1 有所不同，具体参见代码

*/

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>

using namespace std;

class Solution {
public:
	int leastInterval(vector<char>& tasks, int n)
	{
		int len = tasks.size();
		if (n == 0)		// n == 0 时，相同的任务可以连续执行，则不需要 idle
			return len;
		if (len < 2)	// 有 0 个或者 1 个任务时，不需要 idle
			return len;

		vector<int> cnt_of_each_task(26, 0);
		for (int i = 0; i < tasks.size(); ++i)
			++cnt_of_each_task[tasks[i] - 'A'];
		sort(cnt_of_each_task.begin(), cnt_of_each_task.end(), greater<int>());	// 从大到小排序
		int most_task = cnt_of_each_task[0];
		int interval_need = n * (most_task - 1);		// 将出现次数最多的 task 间隔开所需要的 interval 数目
		int interval_support = 0;						// 计算其他task插入的方式能作为 interval 的数目
		for (int i = 1; i < cnt_of_each_task.size(); ++i)
		{
			// 若某个 task 的个数和 most_task 相等，则能够起到间隔作用的只有 most_task-1 个，因为最后一个该 task 会被放到最后位置，
			// 比如 AAABBB  -> ABABAB 用B来间隔A的时候，之后2个B能充当间隔
			if (cnt_of_each_task[i] == most_task)		
				interval_support += most_task - 1;
			else
				interval_support += cnt_of_each_task[i];
		}
		int interval_idle = max(interval_need - interval_support, 0);	// 若 interval_support > interval_need，则不需要额外的 idle interval
		int result = interval_idle + tasks.size();

		return result;
	}
};

class Solution_v2 {
public:
	int leastInterval(vector<char>& tasks, int n)
	{
		int len = tasks.size();
		if (n == 0)		// n == 0 时，相同的任务可以连续执行，则不需要 idle
			return len;
		if (len < 2)	// 有 0 个或者 1 个任务时，不需要 idle
			return len;

		vector<int> cnt_of_each_task(26, 0);
		for (int i = 0; i < tasks.size(); ++i)
			++cnt_of_each_task[tasks[i] - 'A'];
		sort(cnt_of_each_task.begin(), cnt_of_each_task.end(), greater<int>());	// 从大到小排序
		
		int most_task = cnt_of_each_task[0];
		int i = 0;	// 记录次数为 most_task 的任务的数量
		while (cnt_of_each_task[i] == most_task)
			++i;

		return max(len, (most_task - 1) * (n + 1) + i);
	}
};

class Solution_v3 {
public:
	int leastInterval(vector<char>& tasks, int n)
	{
		int len = tasks.size();
		if (n == 0)		// n == 0 时，相同的任务可以连续执行，则不需要 idle
			return len;
		if (len < 2)	// 有 0 个或者 1 个任务时，不需要 idle
			return len;

		vector<int> cnt_of_each_task(26, 0);
		for (int i = 0; i < tasks.size(); ++i)
			++cnt_of_each_task[tasks[i] - 'A'];
		sort(cnt_of_each_task.begin(), cnt_of_each_task.end(), greater<int>());	// 从大到小排序

		int most_task = cnt_of_each_task[0];
		int i = 0;	// 记录次数为 most_task 的任务的数量
		while (cnt_of_each_task[i] == most_task)
			++i;

		int part_cnt = most_task - 1;		// 模块数量
		int part_len = n - (i - 1);			// 去除 most_task 的任务（可能有多个）的填充之后，余下的模块空位数量
		int empty_slots = part_cnt * part_len;	// 总的空位数量
		int task_left = tasks.size() - most_task * i;	// 去除 most_task 的任务之外，余下的任务的总量
		int idles = max(0, empty_slots - task_left);	// 用 task_left 填充 empty_slots，若能填满则 idles = 0，否则为 empty_slots-task_left
		return idles + tasks.size();		// idles 数量 与 task 数量之和即为总的 interval 数量
	}
};
