#pragma once

/*

690. Employee Importance

You are given a data structure of employee information, which includes the employee's unique id, 
his importance value and his direct subordinates' id.

For example, employee 1 is the leader of employee 2, and employee 2 is the leader of employee 3. 
They have importance value 15, 10 and 5, respectively. 
Then employee 1 has a data structure like [1, 15, [2]], and employee 2 has [2, 10, [3]], and employee 3 has [3, 5, []]. 
Note that although employee 3 is also a subordinate of employee 1, the relationship is not direct.

Now given the employee information of a company, and an employee id, 
you need to return the total importance value of this employee and all his subordinates.

Example 1:
Input: [[1, 5, [2, 3]], [2, 3, []], [3, 3, []]], 1
Output: 11
Explanation:
Employee 1 has importance value 5, and he has two direct subordinates: employee 2 and employee 3. 
They both have importance value 3. So the total importance value of employee 1 is 5 + 3 + 3 = 11.

Note:
One employee has at most one direct leader and may have several subordinates.
The maximum number of employees won't exceed 2000.


Approach:
hash table + BFS

Approach_v2: 
hash table + DFS 好像更快些。

*/

#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

// Employee info
class Employee {
	public:
	// It's the unique ID of each node.
	// unique id of this employee
	int id;
	// the importance value of this employee
	int importance;
	// the id of direct subordinates
	vector<int> subordinates;
};

class Solution {
public:
	int getImportance(vector<Employee*> employees, int id)
	{
		int total_importance = 0;

		// 使用 hash table 加速查找下级人员节点的速度，id为key，对应的employees中的指针为value
		unordered_map<int, Employee*> um;
		for (int i = 0; i < employees.size(); ++i)
			um[employees[i]->id] = employees[i];

		// 使用广度优先的方式遍历以id为根的人员上下级树
		queue<int> employee_id_queue;
		employee_id_queue.push(id);
		while (!employee_id_queue.empty())
		{
			int curr_id = employee_id_queue.front();
			employee_id_queue.pop();

			total_importance += um[curr_id]->importance;

			for (int j = 0; j < um[curr_id]->subordinates.size(); ++j)
				employee_id_queue.push(um[curr_id]->subordinates[j]);
		}

		return total_importance;
	}
};

class Solution_v2 {
public:
	int getImportance(vector<Employee*> employees, int id)
	{
		int total_importance = 0;

		// 使用 hash table 加速查找下级人员节点的速度，id为key，对应的employees中的指针为value
		unordered_map<int, Employee*> id_to_employee;
		for (int i = 0; i < employees.size(); ++i)
			id_to_employee[employees[i]->id] = employees[i];

		return calculateImportance(id_to_employee, id);
		
		return total_importance;
	}

	// 深度优先遍历
	int calculateImportance(unordered_map<int, Employee*>& id_to_employee, int id)
	{
		Employee* curr_employee = id_to_employee[id];
		int importance = curr_employee->importance;

		for (int subordinate_id : curr_employee->subordinates)
			importance += calculateImportance(id_to_employee, subordinate_id);

		return importance;
	}
};

