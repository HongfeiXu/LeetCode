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

��Ŀ����˼�ǣ�������ͬ������A��CPU������һ��A֮����Ҫ���پ���n��ʱ��������������һ��A�����м�ļ������ִ������������߿��С�

Approach:

Greedy
������Ŀ�й涨��������ͬ����֮������ټ��Ϊn�����������Ȱ��ų��ִ�����������Ȼ���ٰ��ų��ִ�����֮������
�������F���ִ�����࣬Ϊk�Σ���������n���ո�ÿ����F����ָ�����Ȼ��˳�򣨳��ִ������򣩲���������Ƶ������

�� AAAAABBBEEFFGG n=3
=> A---A---A---A	A���ִ�����࣬��ÿ��������֮����3����λ�ֿ�	
=> AB--AB--AB--A	����B
=> ABE-ABE-AB--A	����E
=> ABEFABE-ABF-A	����F��ÿ�ξ��������������Ǿ������
=> ABEFABEGABFGA	����G

�� ACCCEEE n = 2
=> C--C--C
=> CE-CE-CE
=> CEACE-CE

������Ŀ���ǿ�֪��
	interval ��Ŀ = idle��Ŀ + task��Ŀ
task��Ŀ��֪������ֻ��Ҫ�� idle ��Ŀ
	idle ��Ŀ = max(0, Ϊ������������ task ���������м� interval ��Ŀ - ����������������ṩ����Ч�� interval ��Ŀ)
1. Ϊ������������ task ���������м� interval ��Ŀ = (�������� task �Ĵ��� - 1) * n
2. ����������������ṩ����Ч�� interval ��Ŀ:
��������Ŀ��task��ֹһ��������ڶ��������е�C��E����ʱ����E��C�м����ṩ����Ч�� interval ��ĿΪ task ��Ŀ - 1����Ϊ���һ������嵽���һ��λ�á�
���ڳ��ִ���С�������Ŀ task ������ task����ֱ�ӽ��о�����䣬ȫ��������Ϊ��Ч�� interval��

���⣬���ṩ�� interval ��Ŀ > ��Ҫ�� interval ��Ŀ����˵��û�� idle �����interval

tasks.size() = M
Time: O(MlogM)
Space: O(1)

Approach v2:

Ref: http://www.cnblogs.com/grandyang/p/7098764.html

���������з�Ϊģ�鴦����������˼·�����ױ��
������ϸ�۲������������ӿ��Է��֣����ֳ���(mx - 1)�飬�ټ�����������ĸ
����������ĸ�ɳ��ִ���������ĸ��ɣ������ж��������ͬ�����ִ�������ĸ��������mxΪ�����ִ�����
��������1�У�A������4�Σ�������A---ģ�������3�Σ��ټ�������A��ÿ��ģ��ĳ���Ϊ4��
����2�У�CE-������2�Σ��ټ�������CE��ÿ��ģ�鳤��Ϊ3�����ǿ��Է��֣�ģ�����ĿΪ������������1��
ģ��ĳ���Ϊn+1�������ϵ���ĸ����Ϊ���ִ�������������Ϊ�����ж�����У���
�͵õ�������ʹ�ó��ִ��������������Էָ�������С interval ��Ŀ��ȡ����Ŀ����������Ŀ�Ľϴ�ֵΪ�����

Approach v3:
ģ��Ƕȣ�Ӧ�� Approach v1 �ķ������������Ҫ�� idle ��Ŀ��Ȼ������ܵ�������Ŀ��Ϊ���
������ idle ��Ŀ�ķ�ʽ�� Approach v1 ������ͬ������μ�����

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
		if (n == 0)		// n == 0 ʱ����ͬ�������������ִ�У�����Ҫ idle
			return len;
		if (len < 2)	// �� 0 ������ 1 ������ʱ������Ҫ idle
			return len;

		vector<int> cnt_of_each_task(26, 0);
		for (int i = 0; i < tasks.size(); ++i)
			++cnt_of_each_task[tasks[i] - 'A'];
		sort(cnt_of_each_task.begin(), cnt_of_each_task.end(), greater<int>());	// �Ӵ�С����
		int most_task = cnt_of_each_task[0];
		int interval_need = n * (most_task - 1);		// �����ִ������� task ���������Ҫ�� interval ��Ŀ
		int interval_support = 0;						// ��������task����ķ�ʽ����Ϊ interval ����Ŀ
		for (int i = 1; i < cnt_of_each_task.size(); ++i)
		{
			// ��ĳ�� task �ĸ����� most_task ��ȣ����ܹ��𵽼�����õ�ֻ�� most_task-1 ������Ϊ���һ���� task �ᱻ�ŵ����λ�ã�
			// ���� AAABBB  -> ABABAB ��B�����A��ʱ��֮��2��B�ܳ䵱���
			if (cnt_of_each_task[i] == most_task)		
				interval_support += most_task - 1;
			else
				interval_support += cnt_of_each_task[i];
		}
		int interval_idle = max(interval_need - interval_support, 0);	// �� interval_support > interval_need������Ҫ����� idle interval
		int result = interval_idle + tasks.size();

		return result;
	}
};

class Solution_v2 {
public:
	int leastInterval(vector<char>& tasks, int n)
	{
		int len = tasks.size();
		if (n == 0)		// n == 0 ʱ����ͬ�������������ִ�У�����Ҫ idle
			return len;
		if (len < 2)	// �� 0 ������ 1 ������ʱ������Ҫ idle
			return len;

		vector<int> cnt_of_each_task(26, 0);
		for (int i = 0; i < tasks.size(); ++i)
			++cnt_of_each_task[tasks[i] - 'A'];
		sort(cnt_of_each_task.begin(), cnt_of_each_task.end(), greater<int>());	// �Ӵ�С����
		
		int most_task = cnt_of_each_task[0];
		int i = 0;	// ��¼����Ϊ most_task �����������
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
		if (n == 0)		// n == 0 ʱ����ͬ�������������ִ�У�����Ҫ idle
			return len;
		if (len < 2)	// �� 0 ������ 1 ������ʱ������Ҫ idle
			return len;

		vector<int> cnt_of_each_task(26, 0);
		for (int i = 0; i < tasks.size(); ++i)
			++cnt_of_each_task[tasks[i] - 'A'];
		sort(cnt_of_each_task.begin(), cnt_of_each_task.end(), greater<int>());	// �Ӵ�С����

		int most_task = cnt_of_each_task[0];
		int i = 0;	// ��¼����Ϊ most_task �����������
		while (cnt_of_each_task[i] == most_task)
			++i;

		int part_cnt = most_task - 1;		// ģ������
		int part_len = n - (i - 1);			// ȥ�� most_task �����񣨿����ж���������֮�����µ�ģ���λ����
		int empty_slots = part_cnt * part_len;	// �ܵĿ�λ����
		int task_left = tasks.size() - most_task * i;	// ȥ�� most_task ������֮�⣬���µ����������
		int idles = max(0, empty_slots - task_left);	// �� task_left ��� empty_slots������������ idles = 0������Ϊ empty_slots-task_left
		return idles + tasks.size();		// idles ���� �� task ����֮�ͼ�Ϊ�ܵ� interval ����
	}
};
