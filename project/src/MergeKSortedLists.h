#pragma once

/*

23. Merge k Sorted Lists

Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

Example:

Input:
[
  1->4->5,
  1->3->4,
  2->6
]
Output: 1->1->2->3->4->4->5->6


====================================
Approach1: Merge lists one by one

使用 mergeTwoLists 的方法进行 mergeKLists。每一次添加一个 list 到结果 result 中。
即，将 merge k lists 的问题转化为 k-1 次 merge 2 lists 问题。

Time: O(kN), k 是链表的数目，N是节点的数目。
Space: O(1)

====================================
Approach2: Brute Force
Ref: https://leetcode.com/problems/merge-k-sorted-lists/solution/

遍历所有链表，将元素放入一个vector中，排序，并最终构造list

Time: O(Nlog(N))，N是节点的数目。
Space: O(N)

====================================
Approach3: Prioriy Queue
Ref: https://leetcode.com/problems/merge-k-sorted-lists/solution/

类似于 mergeTwoLists 的方法（每次从2个list的第一个元素中，选择较小的节点链接到结果链表末尾），
每次从 k 个 list 的第一个元素中，选择最小的节点放入结果链表中。直到所有链表中都没有元素位置。

Time: O(Nlog(k))
Space: O(1)

====================================
Approach4: Merge with Divide and Conquer
Ref: https://leetcode.com/problems/merge-k-sorted-lists/solution/

Approach1 的改进，1中，会有很多次重复的比较。
这里，我们进行分而治之的方式。（归并排序）例如：

list0, list1, list2, list3, list4, list5
=>
list0+1, list2+3, list4+5
记为：
list_a, list_b, list_c
=>
list_a+b, list_c
记为：
list_x, list_y
=>
list_x+y

每个节点会被合并 log(k) 次。

Time: O(Nlog(k))
Space: O(1)

*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

#include "MyList.h"

using namespace std;

// ================Approach 1==================
class Solution {
public:
	ListNode* mergeKLists(vector<ListNode*>& lists)
	{
		ListNode* result = nullptr;
		if (lists.empty())
			return result;
		result = lists.front();
		for (int i = 1; i < lists.size(); ++i)
		{
			result = mergeTwoLists(result, lists[i]);
		}
		return result;
	}

	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
	{
		ListNode* dummy = new ListNode(-1);
		ListNode* curr = dummy;
		while (l1 != nullptr && l2 != nullptr)
		{
			if (l1->val < l2->val)
			{
				curr->next = l1;
				l1 = l1->next;
			}
			else
			{
				curr->next = l2;
				l2 = l2->next;
			}
			curr = curr->next;
		}
		if (l1 == nullptr)
			curr->next = l2;
		else
			curr->next = l1;
		ListNode* result = dummy->next;
		delete dummy;
		return result;
	}
};

// ================Approach 2==================
class SolutionBruteForce {
public:
	ListNode* mergeKLists(vector<ListNode*>& lists)
	{
		vector<int> numbers;
		for (auto a_list : lists)
		{
			while (a_list != nullptr)
			{
				numbers.push_back(a_list->val);
				a_list = a_list->next;
			}
		}
		sort(numbers.begin(), numbers.end());
		ListNode* result = vectorToList(numbers.begin(), numbers.end());
		return result;
	}

	ListNode* vectorToList(vector<int>::const_iterator b, vector<int>::const_iterator e)
	{
		if (b == e)
			return nullptr;
		ListNode* head = new ListNode(*b);
		ListNode* pre = head;	// 指向链表的最后一个节点
		++b;
		while (b != e)
		{
			ListNode* curr = new ListNode(*b);
			pre->next = curr;
			pre = pre->next;
			++b;
		}
		return head;
	}
};

// ================Approach 3==================
class SolutionPriorityQueue {
public:
	ListNode* mergeKLists(vector<ListNode*>& lists)
	{
		if (lists.empty())
			return nullptr;

		auto cmp = [](ListNode* lhs, ListNode* rhs) { return lhs->val > rhs->val; };
		priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> q(cmp);
		
		// 初始化优先级队列，将各个链表的第一个节点插入优先级队列
		for (int i = 0; i < lists.size(); ++i)
		{
			if (lists[i] != nullptr)
			{
				q.push(lists[i]);
				lists[i] = lists[i]->next;
			}
		}

		// 结果链表的头结点（不包含有效数据）
		ListNode* dummy = new ListNode(-1);
		ListNode* last = dummy;	// 当前结果链表的最后一个节点

		while (!q.empty())
		{
			// 最小的节点链接到结果链表末尾
			last->next = q.top();
			// 从优先级队列中删除该节点
			q.pop();
			// 更新 last 指向新的结果链表最后节点
			last = last->next;
			// 如果该最小节点不是所在链表的最后一个节点，则向优先级队列中插入其下一个邻居节点
			if (last->next != nullptr)
				q.push(last->next);
		}

		ListNode* result = dummy->next;
		delete dummy;
		return result;
	}
};

// ================Approach 4==================
class SolutionDC {
public:
	ListNode* mergeKLists(vector<ListNode*>& lists)
	{
		if (lists.empty())
			return nullptr;

		// 分治法
		int amount = lists.size();
		int interval = 1;
		for (interval = 1; interval < amount; interval *= 2)
		{
			for (int i = 0; i < amount - interval; i += 2 * interval)
			{
				lists[i] = mergeTwoLists(lists[i], lists[i + interval]);
			}
		}
		return lists[0];
	}

	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
	{
		ListNode* dummy = new ListNode(-1);
		ListNode* curr = dummy;
		while (l1 != nullptr && l2 != nullptr)
		{
			if (l1->val < l2->val)
			{
				curr->next = l1;
				l1 = l1->next;
			}
			else
			{
				curr->next = l2;
				l2 = l2->next;
			}
			curr = curr->next;
		}
		if (l1 == nullptr)
			curr->next = l2;
		else
			curr->next = l1;
		ListNode* result = dummy->next;
		delete dummy;
		return result;
	}
};

void driver()
{
	list<int> l1 = { 1,4,5 };
	list<int> l2 = { 1,3,4 };
	list<int> l3 = { 2,6 };
	ListNode* ll1 = makeList(l1.begin(), l1.end());
	ListNode* ll2 = makeList(l2.begin(), l2.end());
	ListNode* ll3 = makeList(l3.begin(), l3.end());
	vector<ListNode*> lists { ll1, ll2, ll3 };
	SolutionDC solu;
	ListNode* result = solu.mergeKLists(lists);
	printList(result);
	cout << endl;
	destroyList(result);
}