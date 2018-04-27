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

ʹ�� mergeTwoLists �ķ������� mergeKLists��ÿһ�����һ�� list ����� result �С�
������ merge k lists ������ת��Ϊ k-1 �� merge 2 lists ���⡣

Time: O(kN), k ���������Ŀ��N�ǽڵ����Ŀ��
Space: O(1)

====================================
Approach2: Brute Force
Ref: https://leetcode.com/problems/merge-k-sorted-lists/solution/

��������������Ԫ�ط���һ��vector�У����򣬲����չ���list

Time: O(Nlog(N))��N�ǽڵ����Ŀ��
Space: O(N)

====================================
Approach3: Prioriy Queue
Ref: https://leetcode.com/problems/merge-k-sorted-lists/solution/

������ mergeTwoLists �ķ�����ÿ�δ�2��list�ĵ�һ��Ԫ���У�ѡ���С�Ľڵ����ӵ��������ĩβ����
ÿ�δ� k �� list �ĵ�һ��Ԫ���У�ѡ����С�Ľڵ�����������С�ֱ�����������ж�û��Ԫ��λ�á�

Time: O(Nlog(k))
Space: O(1)

====================================
Approach4: Merge with Divide and Conquer
Ref: https://leetcode.com/problems/merge-k-sorted-lists/solution/

Approach1 �ĸĽ���1�У����кܶ���ظ��ıȽϡ�
������ǽ��зֶ���֮�ķ�ʽ�����鲢�������磺

list0, list1, list2, list3, list4, list5
=>
list0+1, list2+3, list4+5
��Ϊ��
list_a, list_b, list_c
=>
list_a+b, list_c
��Ϊ��
list_x, list_y
=>
list_x+y

ÿ���ڵ�ᱻ�ϲ� log(k) �Ρ�

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
		ListNode* pre = head;	// ָ����������һ���ڵ�
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
		
		// ��ʼ�����ȼ����У�����������ĵ�һ���ڵ�������ȼ�����
		for (int i = 0; i < lists.size(); ++i)
		{
			if (lists[i] != nullptr)
			{
				q.push(lists[i]);
				lists[i] = lists[i]->next;
			}
		}

		// ��������ͷ��㣨��������Ч���ݣ�
		ListNode* dummy = new ListNode(-1);
		ListNode* last = dummy;	// ��ǰ�����������һ���ڵ�

		while (!q.empty())
		{
			// ��С�Ľڵ����ӵ��������ĩβ
			last->next = q.top();
			// �����ȼ�������ɾ���ýڵ�
			q.pop();
			// ���� last ָ���µĽ���������ڵ�
			last = last->next;
			// �������С�ڵ㲻��������������һ���ڵ㣬�������ȼ������в�������һ���ھӽڵ�
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

		// ���η�
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