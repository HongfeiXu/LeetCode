#pragma once

/*

21. Merge Two Sorted Lists

Merge two sorted linked lists and return it as a new list. 
The new list should be made by splicing together the nodes of the first two lists.

Example:

Input: 1->2->4, 1->3->4
Output: 1->1->2->3->4->4

============================================================
Approach1, �� l1 �в��� l2 �еĽڵ㣬��Ҫ���������ҵ�����λ��

Time: O(n+m)
Space: O(1)

============================================================
Approach2, �ݹ鷨

�Ѻϲ������������� l1��l2�Ĺ��̿�Ϊ���ҵ�l1��l2��ͷ���node_1��Ȼ�������µĽڵ����� l1', l2' ������ͷ���node_2�����ӵ�ǰ���node_1���棬��˵ݹ�

============================================================
Approach3, ������

�½�һ��������dummyΪͷ��㣬ѡ��ǰl1��l2�н�С�Ľڵ㣬���ӵ�dummy�����ĩβ������l1��l2��ֱ��������������һ��Ϊ�գ������һ��������ӵ�ĩβ��

��ɢ��23. Merge k Sorted Lists

*/

#include <algorithm>
#include <iostream>

#include "MyList.h"

using namespace std;

// ====================Approach 1===========================
class Solution {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
	{
		if (l1 == nullptr)
			return l2;
		if (l2 == nullptr)
			return l1;

		// l1����Ԫ�ز�����l2����Ԫ�أ����������еĵ�һ��Ԫ��һ���� *l1
		if (l1->val > l2->val)
			swap(l1, l2);
		
		// ��l1���������l2�е�Ԫ��
		ListNode* pre = nullptr;	// pre ָ�� curr ��ǰһ���ڵ�
		ListNode* curr = l1;		// curr ָ��ǰ�ϲ������������������һ���ڵ�
		ListNode* r_node = l2;
		while (r_node != nullptr)
		{
			// Ѱ�� r_node Ҫ���뵽 lhs �е�λ�ã���lhs����Ѱ��һ����r_node��Ľڵ�curr��
			while (curr != nullptr && r_node->val >= curr->val)
			{
				pre = curr;
				curr = curr->next;
			}

			// ����ǰ�ڵ�r_node��������lhs�����µĽڵ㣬��ֱ�ӽ�rhs�ӵ�lhs��β��
			if (curr == nullptr)
			{
				pre->next = r_node;
				return l1;
			}

			// ����ǰ�ڵ�r_node����pre���棬����preָ��
			pre->next = r_node;
			r_node = r_node->next;
			pre->next->next = curr;
			pre = pre->next;
		}
		return l1;
	}
};

// ====================Approach 2===========================
class SolutionRecursive {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
	{
		if (l1 == nullptr)
			return l2;
		if (l2 == nullptr)
			return l1;
		// �� l1 �ĵ�һ���ڵ�ֵ��С����ýڵ�Ϊ��ǰ l1��l2��ͷ��㣬�ݹ�����ͷ������һ���ڵ�
		if (l1->val < l2->val)
		{
			l1->next = mergeTwoLists(l1->next, l2);
			return l1;
		}
		else
		{
			l2->next = mergeTwoLists(l1, l2->next);
			return l2;
		}
	}
};

// ====================Approach 3===========================
class SolutionIterative {
public:
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
	list<int> l1 = { 1,2,4 };
	list<int> l2 = { 1,3,4 };

	ListNode* ll1 = makeList(l1.begin(), l1.end());
	ListNode* ll2 = makeList(l2.begin(), l2.end());


	SolutionIterative solu;
	ListNode* l3 = solu.mergeTwoLists(ll1, ll2);
	for (ListNode* p = l3; p != nullptr; p = p->next)
	{
		cout << p->val << " ";
	}
	cout << endl;
}